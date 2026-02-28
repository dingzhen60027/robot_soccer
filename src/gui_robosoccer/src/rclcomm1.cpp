#include "rclcomm1.h"
#include <rclcpp/qos.hpp>

rclcomm1::rclcomm1()
{
    node=rclcpp::Node::make_shared("gui_robosoccer_subImgBefore");
    RCLCPP_INFO(node->get_logger(), "gui_robosoccer_subImgBefore已创建!");

    isToStop = 0;
    Img_count = 0;


    /*使用Qos提高通信稳定性 wjg 2025-2-23
    **如果启用Qos请将 A-B 取消注释 同时将 C 下行注释
    */


    // 基础QoS配置（不修改发布方）
    rclcpp::QoS custom_qos(1); // 保持队列深度1
    custom_qos.reliability(rmw_qos_reliability_policy_t::RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);// 允许丢帧
    custom_qos.durability(rmw_qos_durability_policy_t::RMW_QOS_POLICY_DURABILITY_VOLATILE);  // 不保留历史消息
    // 创建图像订阅者（兼容原始发布方配置）
    _subscription_image_before = node->create_subscription<sensor_msgs::msg::Image>(
        "robot_image", 
        custom_qos,
        std::bind(
            &rclcomm1::recv_callback_i1,
            this,
            std::placeholders::_1 // 保持占位符传递消息
        )
    );
 


    //窗口抖动可尝试接收队列长度设为1或者降低帧率 **C
    //_subscription_image_before = node->create_subscription<sensor_msgs::msg::Image>("robot_image", 1, std::bind(&rclcomm1::recv_callback_i1, this, std::placeholders::_1));

    this->start();
}

void rclcomm1::run()
{
    qDebug() << "gui_robosoccer_subImgBefore thread:" << QThread::currentThreadId();
    while (rclcpp::ok() && this->isToStop == 0)
    {
        rclcpp::spin_some(node);
    }
    quit();
}

int rclcomm1::encoding2mat_type(std::string encoding)    // cv_8uc4 是bgr8 格式 c3是rgb8  
{
    if (encoding == "mono8") 
    {
        return CV_8UC1;
    } 
    else if (encoding == "bgr8")  //"rgb8"
    {
        return CV_8UC3;
    }
    else if (encoding == "mono16") 
    {
        return CV_16SC1;
    } 
    else if (encoding == "rgba8")  
    {
        return CV_8UC4;
    }
    else 
    {
        return CV_8UC3;
    }
}
void rclcomm1::recv_callback_i1(const sensor_msgs::msg::Image::SharedPtr msg)
{

    /*存在问题：QT界面显示卡顿  2024-12   **未解决**   2025-3-16 已解决 帧率过高会卡死 使用Qos-best_effort 保留最新帧
    **潜在原因：**1.ROS消息堆积 尝试修改订阅策略-Qos（服务质量）控制通信可靠性 
    **        2.isFinishDisp_1
    **        3.显示延迟
    **        4.线程阻塞
    **        5.图像格式转换 BGR -> RGB ? 猜测
    **          ..   
    */

    /**/
    if (isFinishDisp_1)
    {
        isFinishDisp_1 = false;
        QImage robot_image_before;
        QImage Image_Disp_before;
        cv::Mat msg_cvImage(msg->height, msg->width, encoding2mat_type(msg->encoding), const_cast<unsigned char *>(msg->data.data()));
        //图片尺寸修改后图像(1920x1200)*0.5
        if (msg_cvImage.empty() || msg_cvImage.cols != (IMAGE_WIDTH*0.5) || msg_cvImage.rows != (IMAGE_HEIGHT*0.5))
        {
            //RCLCPP_INFO(this->node->get_logger(), "原始图像接收错误!!丢失一帧图像!!");
            cv_bridge::CvImagePtr cv_ptr;
            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);//sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                RCLCPP_INFO(this->node->get_logger(), "图像转换错误:%s!!丢失一帧图像!!", e.what());
                return;
            }
            // 假设 cv_ptr->image 是从OpenCV获取的BGR格式图像
            cv::Mat rgbImage;
            if (msg->encoding == "bgr8")
            {
;
                // 使用 OpenCV 的 cvtColor 函数将 BGR 转换为 RGB
                cv::cvtColor(msg_cvImage, rgbImage, cv::COLOR_BGR2RGB);
            }
            else
            {
                rgbImage = msg_cvImage;
            }
            

            // 创建 QImage 对象，使用 RGB888 格式
            QImage robot_image_before((const uchar*)(rgbImage.data), rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);

            // 缩放图像以适应显示
            QImage Image_Disp_before = robot_image_before.scaled(DISP_WIDTH, DISP_HEIGHT, Qt::IgnoreAspectRatio, Qt::FastTransformation);

            // 发送信号以更新GUI显示
            emit TopicData_image_before(Image_Disp_before);
        }
        else
        {

            cv::Mat rgbImage;

            if (msg->encoding == "bgr8")
            {
;
                // 使用 OpenCV 的 cvtColor 函数将 BGR 转换为 RGB
                cv::cvtColor(msg_cvImage, rgbImage, cv::COLOR_BGR2RGB);
            }
            else
            {
                rgbImage = msg_cvImage;
            }
            
            
            

            // 创建 QImage 对象，使用 RGB888 格式
            QImage robot_image_before((const uchar*)(rgbImage.data), rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);

            // 创建图像的副本
            QImage Image_Disp_before = robot_image_before.copy();

            // 发送信号以更新GUI显示
            emit TopicData_image_before(Image_Disp_before);
        }
    }

    /*帧率统计 wjg 2025-2-23
    **测试gui显示帧率
    */

   static auto last_time = node->now();
   

   if ((node->now() - last_time).seconds() >= 1.0) {
       /* RCLCPP_INFO(node->get_logger(), 
       "\033[32m\n----------GUI显示正常! 当前帧率：%.2f FPS----------\033[0m", 
                  Img_count / (node->now() - last_time).seconds());
       */
       Img_count = 0;
       last_time = node->now();
   }
    Img_count++;

    //RCLCPP_INFO(this->node->get_logger(), "第%ld次收到图像,高度=%d,宽度=%d,图片ID=%s",Img_count, msg->height, msg->width, msg->header.frame_id.c_str());
    return;
}

