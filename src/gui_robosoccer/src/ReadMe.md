-文件说明
  所有文件共同组成一个GUI节点（内含若干小节点）

  main.cpp为整个程序的启动文件
  mainwindow.cpp为主界面文件

  rclcommx.cpp为ROS2节点文件，开启新线程运行（使用了1、3、4）

  globalVar.cpp/globalFun.cpp为全局变量/函数

  HSIslider.cpp、ImageLabelControl.cpp、ImageLabelEnlarge.cpp、ImageLabelColor.cpp、ImageLabelDrawI.cpp为界面部件的提升文件

  额外的文件 rclcomm.cpp 和 rclcomm2.cpp 为弃用或测试文件



-2025-10-31 新增usb权限修复
  问题描述：发射器插上后存在usb初始化失败问题， 问题根源在于linux系统对于usb设备的严格控制
  解决方法： 
        旧版：communication节点初始化usb失败时， 使用命令 sudo chmod -R 777 /dev/bus/usb/ 增加权限，但是不安全（该做法将所有设备均增加了权限）
        wjg： 用udev规则对发射器自动授予权限

-完整解释-wjg
  ### 为何需要“增加权限”
  - **问题根源**：Linux 把每个 USB 设备映射成`/dev`下的设备文件，这些文件默认通常归`root`所有，只允许特定用户组访问。你的普通用户没有读写权限，就会在程序里出现“USB初始化失败、权限不足（EACCES）”。
  - **不安全做法**：`chmod -R 777 /dev/bus/usb/`虽然能临时解决，但非常不安全，且重插/重启就失效。
  - **正确做法**：用 udev 规则对“特定设备（你的VID/PID）”自动授予权限，同时把用户加入允许访问的用户组。这样安全、持久、且只影响你的设备。

  ### 我具体做了什么（通俗版）
  - **定位你的设备**：你的设备ID是`VID=ffff`、`PID=0002`（来自`lsusb`）。
  - **生成一条 udev 规则**：让系统在检测到这款设备时，自动把设备文件权限设为“用户可读写、组可读写”，并把组设为`plugdev`：
    - 规则路径：`/etc/udev/rules.d/99-robosoccer-usb.rules`
    - 规则效果：仅对`ffff:0002`生效，权限`0660`，组`plugdev`
  - **让规则生效**：自动执行`udevadm control --reload && udevadm trigger`，无需重启。
  - **把当前用户加入组（如需要）**：若当前用户不在`plugdev`组，自动把他加入（下一次登录生效）。
  - **避免每次手工操作**：把以上动作做成了GUI里的“一键修复”，用户点一下就完成，后续插拔设备自动生效。

  ### 代码落点（你在哪能看到它）
  - 在`MainWindow`构造函数中，启动时会弹窗询问是否安装权限规则（不强制）。
  - 核心逻辑在`MainWindow::fixUsbPermissionsViaUdev()`：
    - 写入规则文件（只针对`ffff:0002`）
    - 重载并触发 udev
    - 通过`pkexec`提权执行脚本，稳健识别发起用户并尝试加入`plugdev`组

  ### 使用方式
  - 第一次运行 GUI 时选择“是”安装权限规则（会弹出管理员授权窗口）。
  - 完成后“拔插设备”即可生效。
  - 如果提示“用户加入plugdev组”，请“注销并重新登录”一次让组权限生效。

  ### 为什么这样更好
  - **更安全**：仅放开你的设备，不动其它USB设备；不使用`777`。
  - **更持久**：udev 规则会在设备每次插入时自动应用，不用重复设置。
  - **更易用**：集成到 GUI，一键完成，无需记命令。