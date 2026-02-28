from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    """launch内容描述函数,由ros2 launch 扫描调用"""
    vision = Node(
        package="vision_robosoccer",
        executable="vision",
        parameters=[{'is_simulation': True}]  # False for real robot, True for simulation
    )
    vision_processing = Node(
        package="vision_robosoccer",
        executable="vision_processing"
    )
    communication = Node(
        package="communication_robosoccer",
        executable="communication",
        parameters=[{'team_color': 1}]  # 0 for yellow, 1 for blue
    )
    strategy = Node(
         package="strategy_robosoccer",
         executable="strategy"
    )
    gui = Node(
        package="gui_robosoccer",
        executable="gui_robosoccer"
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription(
        [vision,vision_processing,communication,gui, strategy])
    # 返回让ROS2根据launch描述执行节点
    return launch_description

