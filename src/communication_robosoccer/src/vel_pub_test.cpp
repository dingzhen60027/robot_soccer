#include "rclcpp/rclcpp.hpp"
#include "message_interface_robosoccer/msg/velocity_robots.hpp"
#include <iostream>
#include <string>
#include <chrono>


class VelocityPub : public rclcpp::Node 
{
public:
    //基类的构造函数需要传入节点名称 使用成员初始化列表初始化车号 
    VelocityPub(std::string name, int car_num, int vel_left, int vel_right) : Node(name) , CarNum(car_num) , VelocityLeft(vel_left), VelocityRight(vel_right)
    {
        
        publisher_ = this->create_publisher<message_interface_robosoccer::msg::VelocityRobots>("robots_velocity_single", 10); 
        // 创建一个定时器，每20ms发送一次消息 
        timer_ = this->create_wall_timer(std::chrono::milliseconds(20), std::bind(&VelocityPub::timer_callback, this));

    }

private:
    int CarNum; //车号
    int VelocityLeft, VelocityRight;  //要发送的车速
    rclcpp::Publisher<message_interface_robosoccer::msg::VelocityRobots>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    message_interface_robosoccer::msg::VelocityRobots message;
    
    void timer_callback()
    {
        // 设置消息内容
        message.velocity[CarNum-1].left_wheel = VelocityLeft;
        message.velocity[CarNum-1].right_wheel = VelocityRight;

        // 发布消息
        publisher_->publish(message);

    }
};

int main(int argc, char **argv)
{
    // 初始化ROS2运行时环境
    rclcpp::init(argc, argv);

    // 检查命令行参数数量是否正确
    if (argc != 4) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), 
            "参数错误: 请按照以下格式运行\n"
            "ros2 run communication_robosoccer single_vel_pub <车号> <左轮速度> <右轮速度>");
        return EXIT_FAILURE;
    }

    try {
        // 解析命令行参数
        const int car_num = std::stoi(argv[1]);
        const int vel_left = std::stoi(argv[2]); 
        const int vel_right = std::stoi(argv[3]);

        // 参数合法性检查
        if(car_num <= 0 || car_num > 5) {
            throw std::out_of_range("车号必须在1-5之间");
        }

        // 创建并初始化节点
        auto node = std::make_shared<VelocityPub>(
            "single_velocity_pub_node",
            car_num,
            vel_left,
            vel_right
        );

        // 运行节点,直到收到终止信号
        rclcpp::spin(node);
    }
    catch(const std::exception& e) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "错误: %s", e.what());
        return EXIT_FAILURE;
    }

    // 清理ROS2资源
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}
