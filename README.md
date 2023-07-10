
1. 根据手册安装完 SDK 后，需要执行该脚本，用来测试 SDK 环境变量是否正常。
``source /xxxxx/environment-setup-aarch64-poky-linux``

2. 内核编译指令
``` bash
$ make distclean
$ make ARCH=arm64 defconfig
$ make ARCH=arm64 Image dtbs -j16
```

启动参数配置：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/boot_rz2.png)
