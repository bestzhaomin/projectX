MEMORY ORGANIZATION 内存组织
===========================

The memory that the processor addresses on its bus is called physical memory. Physical memory is organized as a sequence of 8-bit bytes. Each byte is assigned a unique address, called a physical address. The physical address space ranges from zero to a maximum of 2 36 − 1 (64 GBytes) if the processor does not support Intel 64 architecture. 

在处理器在其总线（bus）上寻址的内存称为物理内存。物理内存被组织成一个8字节的序列。每个字节分配一个唯一的地址，这个地址被称为物理地址。如果处理器不支持 Intel 64架构，物理地址的范围从0到64GBytes。

Virtually any operating system or executive designed to work with an IA-32 or Intel 64 processor will use the processor’s memory management facilities to access memory. These facilities provide features such as segmentation and paging, which allow memory to be managed efficiently and reliably.

通常，任何操作系统或者为IA-32和Intel 64处理设计的可执行程序都将使用处理器内存管理工具来访问内存。这些工具提供了许多功能，比如分段和分页，以便内存能够有效和可靠的进行管理。


IA-32 Memory Models IA-32 内存模型
---------------------------------
When employing the processor’s memory management facilities, programs do not directly address physical memory. Instead, they access memory using one of three memory models: flat, segmented, or real address mode:
* Flat memory model — Memory appears to a program as a single, continuous address space . This space is called a linear address space.      Code, data, and stacks are all contained in this address space. Linear address space is byte addressable, with addresses running          contiguously from 0 to 2 32 - 1 (if not in 64-bit mode). An address for any byte in linear address space is called a linear address.
* Segmented memory model — Memory appears to a program as a group of independent address spaces called segments. Code, data, and stacks     are typically contained in separate segments. To address a byte in a segment, a program issues a logical address. This consists of a      segment selector and an offset (logical addresses are often referred to as far pointers). The segment selector identifies the segment     to be accessed and the offset identifies a byte in the address space of the segment. Programs running on an IA-32 processor can address   up to 16,383 segments of different sizes and types, and each segment can be as large as 2 32 bytes.

  Internally, all the segments that are defined for a system are mapped into the processor’s linear address space.To access a memory location, the processor thus translates each logical address into a linear address. This translation is transparent to the application program. 

  The primary reason for using segmented memory is to increase the reliability of programs and systems. For example, placing a program’s stack in a separate segment prevents the stack from growing into the code or data space and overwriting instructions or data, respectively.
* Real-address mode memory model — This is the memory model for the Intel 8086 processor. It is supported to provide compatibility with     existing programs written to run on the Intel 8086 processor. The real-address mode uses a specific implementation of segmented memory    in which the linear address space for the program and the operating system/executive consists of an array of segments of up to 64         KBytes in size each.The maximum size of the linear address space in real-address mode is 2 20 bytes.

当采用处理器内存管理工具时，程序部不能够直接访问物理地址。作为替代，它们能够使用三个模型来访问内存：flat（平面？），segmented（段），real address mode（实地址）：
* Flat memory model — 内存在程序中出现在一个单一且连续的地址空间，这个空间被称为线性地址空间。代码，数据以及栈都包含在此地址空间中。线性地址空间能够以字节寻址，   并且是连续的从0到2的32次方-1（不是64位）。在线性空间里的每个字节的地址被称为线性地址。
* 段内存模型 — 内存在程序中出现在一组独立的地址空间，这个空间被称为段。代码，数据和栈通常被包含在各自独立的段中。为了访问段中的字节，程序需要提供一个逻辑地址。这个   逻辑地址包括段选择器和偏移量（逻辑地址通常被称为原指针，far pointer）。段选择器标识了要访问的段，偏移量表示了字节在段中的地址空间。在IA-32架构的处理器上，程序   能够访问多达16383个不同大小和类型的段，每个段最多能有2^32个字节。
  
  本质上，为系统定义的所有段都被映射到处理器的线性地址空间上。为了访问内存，处理器把每个逻辑地址翻译成线性地址。这个翻译对程序是透明的。

  使用段内存模型是为了提高程序和系统的可靠性。例如，将程序的栈分配到一个段中，防止栈数据增长到代码或数据空间而覆盖了指令或数据。
* 实地址内存模型 — 这是Intel 8086处理器的内存模型。它运行在Intel 8086处理器上已存在的程序提供兼容。实地址模式由一个特定的段内存实现，用于程序和操作系统的线性地   址空间由一组每个大小为64K的段组成。实地址模式的线性地址空间最大为2^20。


