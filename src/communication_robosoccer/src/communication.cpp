#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "message_interface_robosoccer/msg/velocity_robots.hpp"

#include "hidapi.h"

#define ROBOTNUM 5

//发射器基频2400, 频率范围2400-2525, 黄方频率402<2402>，蓝方频率418<2418>，发送修改频率值分别为2和18
#define YELLOW 2
#define BLUE 18

class Communication : public rclcpp::Node
{
public:
    Communication(std::string name) : Node(name)
    {
        // 变量初始化
        isOpenUSB = false;
        i = 0;
        CarNum = 1;
        // 参数服务器  此处没有使用参数变更回调函数 后续可以考虑
        //声明参数：定义参数名为team_color，类型为int，默认值为1
        this->declare_parameter("team_color", 1); //默认为蓝色方
        int team_color = 1;
        this->get_parameter("team_color", team_color);
        isBlue = team_color;
        RCLCPP_INFO(this->get_logger(), "\033[32m%s\033[0m",
        "\n上下位机通信节点已创建!");
        // 初始化USB 设定发送频率
        if(initUSB())
        {
            //RCLCPP_INFO(this->get_logger(), "USB初始化失败!!如果插上USB仍显示此错误请设置USB权限:命令窗口输入sudo chmod -R 777 /dev/bus/usb/");
            // \033[31m 和 \033[0m 是ANSI转义序列，用于给终端输出加颜色效果。\033[31m表示红色字体，\033[0m重置颜色；这样日志提示会以红色高亮显示。
            RCLCPP_ERROR(this -> get_logger(), "\033[31m%s\033[0m",
            "\nUSB初始化失败! 请检查发射器连接情况！");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "\033[32m%s\033[0m",
            "\nUSB初始化成功!发射器已连接");
        }
        // 初始化订阅者
        subscription_velocity_ = this->create_subscription<message_interface_robosoccer::msg::VelocityRobots>("robots_velocity", 1, std::bind(&Communication::velocity_sub_callback, this, std::placeholders::_1));
        subscription_velocity_single_ = this->create_subscription<message_interface_robosoccer::msg::VelocityRobots>("robots_velocity_single", 1, std::bind(&Communication::single_velocity_sub_callback, this, std::placeholders::_1));
    }
    
    ~Communication()
    {
        if (dev_handle)
        {
            hid_close(dev_handle);
            hid_exit();
        }
    }

private:
    // 多车速度订阅 用于多车控制 5vs5
    rclcpp::Subscription<message_interface_robosoccer::msg::VelocityRobots>::SharedPtr subscription_velocity_;
    // 单车速度订阅 用于单车控制
    rclcpp::Subscription<message_interface_robosoccer::msg::VelocityRobots>::SharedPtr subscription_velocity_single_; 
    unsigned char USB_Buffer[33];//需要比实际发送字节数多1个字节，多一个标头
    struct hid_device_info *devs, *cur_dev;
    hid_device* dev_handle;
    bool isOpenUSB;
    int i;
    int CarNum;
    int isBlue;

    int initUSB()
    {
        if (hid_init())
		    return -1;
        
        //-------------Check the useful drives---------------//
        /*
        devs = hid_enumerate(0x0, 0x0);
	    cur_dev = devs;
        while (cur_dev) 
        {
		    printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		    printf("\n");
		    printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		    printf("  Product:      %ls\n", cur_dev->product_string);
		    printf("  Release:      %hx\n", cur_dev->release_number);
		    printf("  Interface:    %d\n",  cur_dev->interface_number);
		    printf("\n");
		    cur_dev = cur_dev->next;
	    }
	    hid_free_enumeration(devs);
	    */
        //----------------------------------------------------//

        // Open the device using the VID, PID,
	    dev_handle = hid_open(0xffff, 0x2, NULL);
	    if (!dev_handle) 
	    {
		    printf("unable to open device!!\n");
     		hid_exit();
     		return 1;
	    }
	    else
	    {
	        // Init the launcher frequency.
	        memset(USB_Buffer,0x00,sizeof(USB_Buffer));
	        USB_Buffer[0] = 0x0; //hid_write标头Report ID
	        USB_Buffer[1] = 0xfc;
	        USB_Buffer[2] = 1;
            if (isBlue == 1)
                USB_Buffer[3] = BLUE;
            else
                USB_Buffer[3] = YELLOW;
            
            
	        //USB_Buffer[3] = YELLOW;
	        //USB_Buffer[3] = BLUE;
	        int r = hid_write(dev_handle,USB_Buffer,33);
            if(r<0)
            {
                std::cout << "修改频率失败：" << hid_error(dev_handle) << std::endl;
                return 1;
            }
            else
            {
                isOpenUSB = true;
            }
	    }
        
        return 0;
    }
    
    void velocity_sub_callback(const message_interface_robosoccer::msg::VelocityRobots::SharedPtr msg)
    {
        // RCLCPP_INFO(this->get_logger(), "| 1号车速度设定: L:%f R:%f|", 
        //                                 msg->velocity[0].left_wheel, msg->velocity[0].right_wheel);
        
        if (isOpenUSB)
        {
            int r;
            // Init the command buffer.
	        memset(USB_Buffer,0x00,sizeof(USB_Buffer));
	        USB_Buffer[0] = 0x0; //hid_write标头Report ID
	        USB_Buffer[1] = 0xfd;
	        USB_Buffer[2] = 11;
            for (CarNum = 1; CarNum<=ROBOTNUM; CarNum++)
            {
                USB_Buffer[CarNum*2+1] = msg->velocity[CarNum-1].left_wheel/2;//L_v / 2
                USB_Buffer[CarNum*2+2] = msg->velocity[CarNum-1].right_wheel/2;//R_v / 2
            }
            
            r = hid_write(dev_handle,USB_Buffer,33);
            if(r<0)
            {
                std::cout << "发送指令失败：" << hid_error(dev_handle) << std::endl;
            }
        }
    }


    void single_velocity_sub_callback(const message_interface_robosoccer::msg::VelocityRobots::SharedPtr msg)
    {
   
        if (i == 0)  //判断是否是第一次接收数据 如果是则打印一次
        {
            RCLCPP_INFO(this->get_logger(),"\033[31m%s\033[0m",
            "\n--------------单车控制模式启动--------------");
            i++;
        }
        if (isOpenUSB)
        {
            int r;
            // Init the command buffer.
	        memset(USB_Buffer,0x00,sizeof(USB_Buffer));
	        USB_Buffer[0] = 0x0; //hid_write标头Report ID
	        USB_Buffer[1] = 0xfd;
	        USB_Buffer[2] = 11;
            for (CarNum = 1; CarNum<=ROBOTNUM; CarNum++)
            {
                if (msg->velocity[CarNum-1].left_wheel != 0 || msg->velocity[CarNum-1].right_wheel != 0)
                {
                    USB_Buffer[CarNum*2+1] = msg->velocity[CarNum-1].left_wheel/2;//L_v / 2
                    USB_Buffer[CarNum*2+2] = msg->velocity[CarNum-1].right_wheel/2;//R_v / 2
                    break;
                }
        
            }
            
            r = hid_write(dev_handle,USB_Buffer,33);
            if(r<0)
            {
                std::cout << "发送指令失败：" << hid_error(dev_handle) << std::endl;
            }
            else
            {
                i++;
                if (i % 100 == 0)
                {
                    RCLCPP_INFO(this->get_logger(),"\033[32m%s\033[0m",
                    "\n----------Connected Successful!----------");
                }
            }
        }    //
    }


};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);



    auto node = std::make_shared<Communication>("communication");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
