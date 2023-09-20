### RedMagicProbe on RZ/G2

本篇作为现阶段的总结，目前实现了在 PC 端通过 RZ/G2 使用 arm-none-eabi-gdb 完成对 stm32f103 控制器的探测和调试。项目的硬件结构框图如下：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/misc-Page-37.drawio.png)

本次项目设计到软件部分涉及到两个层次，分别是内核态和用户态，内核太涉及到 USB gadget 驱动的开发，实现了设备端点在PC端枚举成 tty 设备，用户态涉及到 blackmagic 的移植，官方这部分功能是运行在 stm32 这类处理器上的，我将这部分功能移植到了 Linux 的用户态。系统软件结构框图如下：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/misc-Page-38.drawio.png)

整个软件的开发都采用 git 进行代码托管，内核态的开发仓库为 [https://github.com/iysheng/myir-renesas-linux](https://github.com/iysheng/myir-renesas-linux)，代码提交记录截图如下：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/2023-09-20_19-27.png)


用户态的代码开发在仓库 [https://github.com/iysheng/blackmagic](https://github.com/iysheng/blackmagic)， 对应的提交记录截图如下：
![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/2023-09-20_19-30.png)

因为前面大部分时间都在围绕 USB gadget 进行，所以用户态代码这部分的开发显示非常急促，还好我之前有对 blackmagic 这个项目的代码有过一定的拜读，所以基本功能还是实现了，目前可以探测外接芯片的信息，测试可以擦除 stm32f1 的内部 flash。

有关 blackmagic 这个调试器，我自己还是 DIY 过一个实际的调试器的，硬件我也已经开源了 [https://gitee.com/iysheng/RedMagicProbe](https://gitee.com/iysheng/RedMagicProbe)：

实物是这个样子的：
![](/home/red/Downloads/1868410768.jpg)

现场使用 RZ/G2 实现 blackmagic probe 的工具还是有一定的挑战的，测试的现场图片如下：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/real.jpg)

从图中可以看出

最终的效果如图所示：

![](/home/red/Codes_of_pro/blackmagic4RZ/assets/final/ans.png)

