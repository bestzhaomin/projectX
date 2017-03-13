Boot sequence 启动顺序
=====================

Post 电源启动-设备自检
-------------------
When a computer is switched on or reset, it runs through a series of diagnostics called POST - Power-On Self-Test. This sequence culminates in locating a bootable device, such as a Floppy disk, CD-ROM or a Hard disk in the order that the firmware is configured to.

当一个电脑启动或重启时，它需要运行一连串的诊断，这被称为POST（Power-On Self-Test），这个顺序的终点是探测到一个可引导的设备,
例如软盘、光驱或者硬盘等等，它们是已经配置好的启动顺序。

Master Boot Record 主启动记录
---------------------------
The (legacy) BIOS checks bootable devices for a boot signature, a so called magic number. The boot signature is in a boot sector (sector number 0) and it contains the byte sequence 0x55, 0xAA at byte offsets 510 and 511 respectively. When the BIOS finds such a boot sector, it is loaded into memory at 0x0000:0x7c00 (segment 0, address 0x7c00). (However, some BIOS' load to 0x7c0:0x0000 (segment 0x07c0, offset 0), which resolves to the same physical address, but can be surprising. A good practice is to enforce CS:IP at the very start of your boot sector.)

BIOS检查可引导设备的引导签名，所谓的幻数（magic number）。引导签名在引导扇区（扇区号是0）中，并且它包含了字节偏移510和511处的字节序列0x55、0xAA。当BIOS找到这样的引导扇区时，它被加载到内存0x0000:0x7c00（段0,地址0x7c00）处。但是一些BIOS会加载到0x7c00:0x0000（段0x7c00,偏移0），令人惊讶的是它们被解析到相同的物理地址。一个好的做法是在启动扇区的开始执行CS:IP。

然后将会执行新装入的启动记录。在软盘上，引导记录的所有512个字节可能包含所有的可执行代码。在硬盘上，主引导记录（MRB）在偏移0x000-0x01bd处保存可执行代码，然后是4个主分区的table entry，每个entry使用16字节（0x01be-0x01fd）和两个字节的签名（0x01fe-0x01ff）。

Early Environment 早期的执行环境
------------------------------
This early execution environment is highly implementation defined, meaning the implementation of your particular BIOS. Never make any assumptions on the contents of registers: They might be initialized to 0, but they might contain a spurious value just as well.

早期的执行环境是高度定义的，意思是它由你自己特定的BIOS实现。不要对寄存器做任何假设，它可能被初始化为0,也可能包含伪值。

The CPU is currently in Real Mode. (Unless you are running on one of those rare BIOS' which believe they're doing you a favor by activating Protected Mode for you. Which means you not only have to write code for activating protected mode on any other hardware, but should also add a test condition if it's already activated.)

CPU在这时处于Real Mode（实模式）。（？。。？）

Kernel 内核
-----------
Finally, the bootloader loads the kernel into memory and passes control to it.

最终，启动器把内核读入内存，并且把控制权交给内核。

Loading 载入
------------
If booting from hard drive, you have only 446 bytes available for your boot record. Looking at the list of things to do before your kernel image can run, you will agree that this is not much:
*determine which partition to boot from (either by looking for the active partition, or by presenting the user with a selection of installed operating systems to chose from);
*determine where your kernel image is located on the boot partition (either by interpreting the file system, or by loading the image from a fixed position);
*load the kernel image into memory (requires basic disk I/O);
*enable protected mode;
*preparing the runtime environment for the kernel (e.g. setting up stack space);

如果从硬盘引导，你只有446个字节可用于引导记录。看看内核镜像在可运行之前要的事情：
*确定从哪个分区引导（通过寻找激活的分区，或者向用户提供已安装的操作系统，让用户来选择）；
*确定你的内核镜像在启动分区的位置（通过解释文件系统，或者通过固定的位置来装载）；
*把内核镜像加载到内存（需要基本磁盘I/O)；
*启用保护模式；
*为内核准备运行时环境（例如设置堆栈空间等）；

You don't have to do things in this order, but all of this has to be done before you can call kmain().
To make things worse, GCC generates protected mode executables only, so the code for this early environment is one of the Things You Cannot Do With C.
There are several approaches to this problem:
*Geek loading: Squeeze everything from the above list into the boot record. This is next to impossible, and does not leave room for any special-case handling or useful error messages.
*One-stage loading: Write a stub program for making the switch, and link that in front of your kernel image. Boot record loads kernel image (below the 1mb memory mark, because in real mode that's the upper memory limit!), jumps into the stub, stub makes the switch to Protected Mode and runtime preparations, jumps into kernel proper.
*Two-stage loading: Write a separate stub program which is loaded below the 1mb memory mark, and does everything from the above list.

你不必按这个顺序来做，但在你调用kmain()之前，这一切应该完成。
糟糕的是GCC只能生成保护模式下运行的可执行代码，所以早期环境中的代码你不能使用C语言来编写。
这个问题的几种解决方法：
*Geek loading:将上述的步骤压缩到引导记录。这是不可能的，并且没有为任何特殊情况或有用的错误信息留出空间。
*一步加载：编写一个用与切换的stub程序，并链接到你的内核镜像前面。引导记录装载内核（低于1M的内存标记，因为这是real mode的内存极限），跳转到stub，stub完成保护模式的切换和运行环境的准备，然后跳转到合适的内核。
*两步加载：编写一个单独的stub程序，它被标记加载到1M以内的内存中，然后执行上面所有的内容。

The Traditional Way 传统方式
---------------------------
Traditionally, the MBR relocates itself to 0x0000:0x0600, determines the active partition from the partition table, loads the first sector of that partition (the "partition boot record") to 0x0000:0x7c00 (hence the previous relocation), and jumps to that address. This is called "chain loading". If you want your self-written boot record to be capable of dual-booting e.g. Windows, it should mimic this behaviour.

传统的，MBR将自身重定位到0x0000:0x0600，从分区表确定活动的分区，将该分区的第一扇区（引导记录分区）加载到0x0000:0x7c00，并跳转到这个地址。这被称为Chain load。如果你希望你自己写的引导记录能够实现双引导，例如Windows，你应该参照这个行为。

Easy Way Out 简单的办法
----------------------
Unless you really want to be Rolling Your Own Bootloader (record / stubs) for the educational value, we recommend using readily available bootloaders.

除非你想为了教育的价值实现你自己的Bootloader，我们建议使用随时可用的bootloaders。

The most prominent one is GRUB, a two-stage bootloader that not only provides a boot menu with chainloading capability, but initializes the early environment to a well-defined state (including Protected Mode and reading various interesting information from the BIOS), can load generic executables as kernel images (instead of requiring flat binaries like most other bootloaders), supports optional kernel modules, various file systems, and if ./configure'd correctly, Diskless Booting.

最突出的是GRUB，一个两步加载bootloader，它不仅仅提供了具有Chain load功能的引导菜单，还将早期的环境初始化为良好定义的状态（包括保护模式以及从BIOS读取各种有趣的信息），可以加载通用可执行文件作为内核镜像（不像其他bootloader需要二进制文件），支持可选的内核模块，各种文件系统，以及./configure正确的情况下的无盘引导。
