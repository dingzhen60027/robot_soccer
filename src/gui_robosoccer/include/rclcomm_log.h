/*
  2025-11-20
  @author:  wjg
  @version: 1.0
  @description: 日志类，用于显示节点调试信息
*/
#pragma once
#include "rclcpp/rclcpp.hpp"
// 引入 rosout 消息类型
#include <rcl_interfaces/msg/log.hpp>
#include <iostream>
#include <string>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QRegularExpression>
class rclcomm_log : public QThread
{
    Q_OBJECT                // 必须包含这个宏才能使用信号槽机制
public:
    rclcomm_log();
    void log_callback(const rcl_interfaces::msg::Log::ConstSharedPtr msg);
    bool isToStop;

protected:
    void run();

private:
    rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr _subscription_log;
    std::shared_ptr<rclcpp::Node> node;  //节点，作为 rclcomm类 的 成员 来操作，将原本节点内需要定义的成员放在rclcomm类下，节点只需要负责初始化发布者/订阅者和其运行即可

signals:
    void TopicData_rosout(QString logMessage, int logLevel);  // 信号携带日志内容和级别

public slots:
};


