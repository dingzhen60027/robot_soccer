#include "rclcomm_log.h"
#include <rclcpp/qos.hpp>
rclcomm_log::rclcomm_log()
{
    node = std::make_shared<rclcpp::Node>("rclcomm_log_node");
    _subscription_log = node->create_subscription<rcl_interfaces::msg::Log>(
        "/rosout", 
        1,    // QoS: 使用 keep_all 以确保不错过日志
        std::bind(&rclcomm_log::log_callback, this, std::placeholders::_1));

    isToStop = 0; //线程停止 标志位
        
    this->start();  // 启动线程 会调用 run 方法
}

void rclcomm_log::log_callback(const rcl_interfaces::msg::Log::ConstSharedPtr msg)
{
    QString logMessage = QString::fromStdString(msg->msg);
    int logLevel = msg->level;
     // 过滤ANSI转义序列
    // 正则表达式匹配ANSI转义序列（如\033[32m、\033[0m等）
    QRegularExpression ansiRegex("\\033\\[[0-9;]*[a-zA-Z]");
    logMessage = logMessage.remove(ansiRegex);
    emit TopicData_rosout(logMessage, logLevel);  // 发射信号，携带日志内容和级别
}

void rclcomm_log::run()
{
    qDebug() << "gui_robosoccer_Log_monitor_thread:" << QThread::currentThreadId();
    while (rclcpp::ok() && this->isToStop == 0)
    {
        rclcpp::spin_some(node);
    }
    quit();  // 退出线程
}