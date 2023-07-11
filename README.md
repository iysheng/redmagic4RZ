
1. 根据手册安装完 SDK 后，需要执行该脚本，用来测试 SDK 环境变量是否正常。
``source /xxxxx/environment-setup-aarch64-poky-linux``

2. 内核编译指令
``` bash
$ make distclean
$ make ARCH=arm64 defconfig
$ make ARCH=arm64 Image dtbs -j16
```

3. RZ/G2L 核心
	![](assets/LSI_Bus.png)
	![](assets/LSI_Bus_overall.png)
	* LSI Internal Bus (34 bit address 以及 16GB 内存空间)
		1. ACPU bus : A55
		2. MCPU bus : M33
		3. System bus : 
	* USB2.0 接口,包含1路 USB2.0 OTG/DRD(Host/Function)和1路 USB2.0 Host接口。
启动参数配置：

![](assets/boot_rz2.png)
