打包到另一台电脑需要进行的操作：

1. 确保 ubuntu 上安装了 ROS2
  #若需要使用自己安装的Qt，则还需要下列步骤
2. 确保 ubuntu 上安装了 Qt5
3. Qt5 需要安装到 ～/Qt/ 目录下
*4. 修改 gui_robosoccer 的 CMakeList.txt ，将 Qt5_DIR 中定位到自己安装的 Qt5 版本  Qt5 版本要在14.0以上
5. 工作空间下colcon build

若出现报错：__pthread_kill_implementation (no_tid=0, signo=6, threadid=140737130252352) at ./nptl/pthread_kill.c:44 44	./nptl/pthread_kill.c: 没有那个文件或目录.
可以尝试在编译时加上-pthread选项：CMakeLists.txt 中 add_compile_options(-Wall -Wextra -Wpedantic -pthread)


接口：

视觉部分： 
vision.cpp  采集图像并发布  发布图像话题：robot_image 图像格式：BGR 960*600 
	    订阅相机控制命令 话题：camera_control 由gui部分 rclcomm4 发布
