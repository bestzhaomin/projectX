SYSTEM ARCHITECTURE OVERVIEW 系统架构预览
=======================================

IA-32架构（从Intel 386处理器家族开始）为操作系统和系统软件开发提供了广泛的支持。这种支持提供了多种操作模式，包括：
* Real mode（实模式）, protected mode（保护模式）, virtual 8086 mode（虚拟8086模式）, and system management mode（系统管理模式）。这些模式有时被简称为传统模式。

Intel64架构几乎支持所有IA-32架构的系统规则，并且把他们扩展到一个支持64位程序运行环境的新模式（IA-32e）。IA-32e模式允许软件操作一下两个模式中的一个：
* 64位模式，支持64位的操作系统和应用程序；
* 兼容模式，兼容大多数传统模式下的软件。它与64位操作模式下的64位操作系统共存。

IA-32系统层架构包含以下几个辅助功能：
* 内存管理；
* 保护软件模块；
* 多任务；
* 异常和中断处理；
* 多进程；
* 缓存管理;
* 硬件资源和电源管理；
* 调试和性能监视。

系统层架构预览
------------
System-level（系统层）架构包含一组寄存器、数据结构和设计好的指令，这些指令被用于支持基础系统层操作，例如内存管理，中断和异常处理，任务管理和多处理器控制。

Global and Local Descriptor Tables 全局和本地描述符表
-------------------------------------------------
当在保护模式下操作时，所有的内存访问都要经过Global Descriptor Table（GDT，全局描述符表）或可选的Local Descriptor Table（LDT，本地描述符表）。这些表包含他们的入口-段描述符。段描述符提供了段基地址以及入口修正（进入真实物理地址的修正）、类型和使用信息。

每个段描述符关联一个段选择器。段选择器被软件使用，为软件进入GDT或LDT提供了索引（偏移量和与它关联的段描述符），提供了一个全局/本地标志（确认选择器指向的是GDT还是LDT），还提供了进入真实物理地址的修正信息。

要访问段中的一个字节，必须提供段选择器和偏移量。段选择器为段（GDT或LDT）提供了段描述符的一个入口。处理器从段描述符获得了线性地址空间中段的基址，偏移量提供了字节相对与基址的位置。这个机制可以被用于访问任何有效的代码，数据或栈段，provided the segment is accessible from the current privilege level (CPL) at which the processor is operating。CPL被定义为当前执行代码段的保护级别。

GDT基址的线性地址包含在GDT register（GDTR，GDT寄存器）中；LDT基址的线性地址包含在LDT register（LDTR，LDT寄存器）。

System Segments, Segment Descriptors, and Gates
-----------------------------------------------
除了构成程序或程序执行的代码、数据和堆栈段，架构还定义了两个系统段：task-state segment（任务状态段）和LDT。这儿不考虑GDT，因为它不是通过段选择器和段描述符来访问的。TSS和LDT有为其定义的段描述符。

架构通常还定义一组特殊的描述符，叫做gate（call gates, interrupt gates, trap gates, and task gates）。这些gate为系统程序和系统处理提供了受保护的网关，可以在不同于应用程序的特权级别下操作。例如，CALL指令可以访问与当前代码段中相同或数字级别较低的代码段中的过程。访问一个过程要通过call gate，被访问的过程为call gate提供选择器。处理器在call gate时执行访问权限检查，比较CPL和call gate的特权级别。

如果访问目标代码段被允许，处理器从call gate得到进入代码段的目标代码段选择器和偏移量。If the call requires a change in privilege level, the processor also switches to the stack for the targeted privilege level. The segment selector for the new stack is obtained from the TSS for the currently running task. Gates also facilitate transitions between 16-bit and 32-bit code segments, and vice versa.

Task-State Segments and Task Gates
----------------------------------
TSS定义了可执行环境中任务的状态。它包含的状态有：通用寄存器，段寄存器，EFLAGS寄存器，EIP寄存器和三个堆栈段的段选择器。