MEMORY ORGANIZATION 内存组织
===========================

The memory that the processor addresses on its bus is called physical memory. Physical memory is organized as a sequence of 8-bit bytes. Each byte is assigned a unique address, called a physical address. The physical address space ranges from zero to a maximum of 2 36 − 1 (64 GBytes) if the processor does not support Intel 64 architecture. 

处理器在其总线（bus）上寻址的内存称为物理内存。物理内存被组织成一个8字节的序列。每个字节分配一个唯一的地址，这个地址被称为物理地址。如果处理器不支持 Intel 64架构，物理地址的范围从0到64GBytes。

Virtually any operating system or executive designed to work with an IA-32 or Intel 64 processor will use the processor’s memory management facilities to access memory. These facilities provide features such as segmentation and paging, which allow memory to be managed efficiently and reliably.

通常，任何操作系统或者为IA-32和Intel 64处理设计的可执行程序都将使用处理器内存管理工具来访问内存。这些工具提供了许多功能，比如分段和分页，以便内存能够有效和可靠的进行管理。


IA-32 Memory Models IA-32 内存模型
---------------------------------
When employing the processor’s memory management facilities, programs do not directly address physical memory. Instead, they access memory using one of three memory models: flat, segmented, or real address mode:
* Flat memory model — Memory appears to a program as a single, continuous address space . This space is called a linear address space.      Code, data, and stacks are all contained in this address space. Linear address space is byte addressable, with addresses running          contiguously from 0 to 2 32 - 1 (if not in 64-bit mode). An address for any byte in linear address space is called a linear address.
* Segmented memory model — Memory appears to a program as a group of independent address spaces called segments. Code, data, and stacks     are typically contained in separate segments. To address a byte in a segment, a program issues a logical address. This consists of a      segment selector and an offset (logical addresses are often referred to as far pointers). The segment selector identifies the segment     to be accessed and the offset identifies a byte in the address space of the segment. Programs running on an IA-32 processor can address   up to 16,383 segments of different sizes and types, and each segment can be as large as 2^32 bytes.

  Internally, all the segments that are defined for a system are mapped into the processor’s linear address space.To access a memory location, the processor thus translates each logical address into a linear address. This translation is transparent to the application program. 

  The primary reason for using segmented memory is to increase the reliability of programs and systems. For example, placing a program’s stack in a separate segment prevents the stack from growing into the code or data space and overwriting instructions or data, respectively.
* Real-address mode memory model — This is the memory model for the Intel 8086 processor. It is supported to provide compatibility with     existing programs written to run on the Intel 8086 processor. The real-address mode uses a specific implementation of segmented memory    in which the linear address space for the program and the operating system/executive consists of an array of segments of up to 64         KBytes in size each.The maximum size of the linear address space in real-address mode is 2 20 bytes.

当采用处理器内存管理工具时，程序都不能够直接访问物理地址。作为替代，它们能够使用三个模型来访问内存：flat（平面？），segmented（段），real address mode（实模式）：
* Flat memory model — 内存在程序中出现在一个单一且连续的地址空间，这个空间被称为线性地址空间。代码，数据以及栈都包含在此地址空间中。线性地址空间能够以字节寻址，   并且是连续的从0到2的32次方-1（不是64位）。在线性空间里的每个字节的地址被称为线性地址。
* 段内存模型 — 内存在程序中出现在一组独立的地址空间，这个空间被称为段。代码，数据和栈通常被包含在各自独立的段中。为了访问段中的字节，程序需要提供一个逻辑地址。这个   逻辑地址包括段选择器和偏移量（逻辑地址通常被称为远指针，far pointer）。段选择器标识了要访问的段，偏移量表示了字节在段中的地址空间。在IA-32架构的处理器上，程序   能够访问多达16383个不同大小和类型的段，每个段最多能有2^32个字节。
  
  本质上，为系统定义的所有段都被映射到处理器的线性地址空间上。为了访问内存，处理器把每个逻辑地址翻译成线性地址。这个翻译对程序是透明的。

  使用段内存模型是为了提高程序和系统的可靠性。例如，将程序的栈分配到一个段中，防止栈数据增长到代码或数据空间而覆盖了指令或数据。
* 实地址内存模型 — 这是Intel 8086处理器的内存模型。它运行在Intel 8086处理器上已存在的程序提供兼容。实地址模式由一个特定的段内存实现，用于程序和操作系统的线性地   址空间由一组每个大小为64K的段组成。实地址模式的线性地址空间最大为2^20。

Paging and Virtual Memory 页和虚拟内存
------------------------------------
With the flat or the segmented memory model, linear address space is mapped into the processor’s physical address space either directly or through paging. When using direct mapping (paging disabled), each linear address has a one-to-one correspondence with a physical address. Linear addresses are sent out on the processor‘s address lines without translation.

When using the IA-32 architecture’s paging mechanism (paging enabled), linear address space is divided into pages which are mapped to virtual memory. The pages of virtual memory are then mapped as needed into physical memory. When an operating system or executive uses paging, the paging mechanism is transparent to an applica-tion program. All that the application sees is linear address space.

In addition, IA-32 architecture’s paging mechanism includes extensions that support:
* Physical Address Extensions (PAE) to address physical address space greater than 4 GBytes.
* Page Size Extensions (PSE) to map linear address to physical address in 4-MBytes pages.


使用flat或段内存模型，线性地址空间可以直接或通过分页来映射到处理的物理地址。当使用真实映射时，每个线性地址与物理地址一一对应。线性地址与物理地址之间的传输不需要转义。

当使用IA-32架构的分页机制时，线性地址空间被划分到许多页中，页被映射到虚拟内存。虚拟内存的页根据需要被映射到物理内存。当操作系统或可执行程序使用分页时，分机制对程序来说时透明的。所有的应用程序看到的都是线性地址空间。

此外，IA-32架构的分页机制包括以下扩展：
* 物理地址扩展（PAE），用于处理大于4GB的物理地址空间；
* 分页大小扩展（PSE），将线性地址映射到4MB大小的物理地址空间。

Memory Organization in 64-Bit Mode 64位模式下的内存组织
-----------------------------------------------------
Intel 64 architecture supports physical address space greater than 64 GBytes; the actual physical address size of IA-32 processors is implementation specific. In 64-bit mode, there is architectural support for 64-bit linear address space. However, processors supporting Intel 64 architecture may implement less than 64-bits. The linear address space is mapped into the processor physical address space through the PAE paging mechanism.

Intel 64架构支持的物理地址空间大于64GB，实际上是IA-32处理器物理地址大小的特殊实现。在64位模式下，有64位的线性地址空间。然而，支持Intel 64架构处理器的线性地址可能小于64位。线性地址空间通过PAE分页机制被映射到处理器的物理地址。

Modes of Operation vs. Memory Model 操作模式 vs 内存模型
------------------------------------------------------
When writing code for an IA-32 or Intel 64 processor, a programmer needs to know the operating mode the processor is going to be in when executing the code and the memory model being used. The relationship between operating modes and memory models is as follows:
* Protected mode — When in protected mode, the processor can use any of the memory models described in this section. (The real-addressing   mode memory model is ordinarily used only when the processor is in the virtual-8086 mode.) The memory model used depends on the design    of the operating system or executive. When multitasking is implemented, individual tasks can use different memory models.
* Real-address mode — When in real-address mode, the processor only supports the real-address mode memory model.
* System management mode — When in SMM, the processor switches to a separate address space, called the system management RAM (SMRAM). The   memory model used to address bytes in this address space is similar to the real-address mode model.
* Compatibility mode — Software that needs to run in compatibility mode should observe the same memory model as those targeted to run in    32-bit protected mode. The effect of segmentation is the same as it is in 32-bit protected mode semantics.
* 64-bit mode — Segmentation is generally (but not completely) disabled, creating a flat 64-bit linear-address space. Specifically, the     processor treats the segment base of CS, DS, ES, and SS as zero in 64-bit mode (this makes a linear address equal an effective address)   .Segmented and real address modes are not available in 64-bit mode.

在为IA-32或Intel 64架构编写代码时，程序员需要知道代码执行时处理器的操作模式和内存模型。操作模式和内存模型之间的关系如下：
* 保护模式。当使用保护模式时，处理器可以使用所有的内存模型。（实模式内存模型通常仅在处理器的virtual-8086模式使用）内存模型的使用取决与操作系统或可执行程序。当执行多任务时，各个任务可使用不同的内存模型。
* 实模式。当使用实模式时，处理器仅支持real-address mode模型。
* 系统管理模式。当使用系统管理模式时，处理器切换到单独的地址空间，叫做系统管理RAM，用于该空间的寻址模式类似实模式。
* 兼容模式。需要在兼容模式下运行的软件应该遵循32位保护模式下的内存模型。
* 64位模式。分段通常（但不完全）禁用，创建一个flat64位线性地址空间。特别的，在64位模式下处理器将CS、DS、ES和SS的段基址视为0（这使得线性地址等于真是地址）。段内    存模型和实地址模型在64位模式下不可用。

32-Bit and 16-Bit Address and Operand Sizes 32位、16位寻址和操作数大小
------------------------------------------------------------------
IA-32 processors in protected mode can be configured for 32-bit or 16-bit address and operand sizes. With 32-bit address and operand sizes, the maximum linear address or segment offset is FFFFFFFFH (2^32 -1); operand sizes are typically 8 bits or 32 bits. With 16-bit address and operand sizes, the maximum linear address or segment offset is FFFFH (2^16 -1); operand sizes are typically 8 bits or 16 bits.

在保护模型下的IA-32处理器可以设置32位或者16位寻址和操作数大小。在32位下，最大的线性地址或段偏移是FFFFFFFFH (2^32 -1)，操作数大小通常是8位或32位。在16位下，最大的线性地址或段偏移是FFFFH (2^16 -1)，操作数大小通常是8位或16位。

When using 32-bit addressing, a logical address (or far pointer) consists of a 16-bit segment selector and a 32-bit offset; when using 16-bit addressing, an address consists of a 16-bit segment selector and a 16-bit offset.

当使用32位寻址时，一个逻辑地址包含一个16位段选择器和一个32位偏移量。使用16位寻址时，一个地址包含一个16位段选择器你和一个16位偏移量。

Instruction prefixes allow temporary overrides of the default address and/or operand sizes from within a program.

指令前缀允许临时覆盖程序内的默认地址或操作数大小。

When operating in protected mode, the segment descriptor for the currently executing code segment defines the default address and operand size. A segment descriptor is a system data structure not normally visible to application code. Assembler directives allow the default addressing and operand size to be chosen for a program. The assembler and other tools then set up the segment descriptor for the code segment appropriately.

在保护模式下工作时，当前执行代码段的段描述定义了默认的地址和操作数大小。段描述是一个系统数据结构，通常应用程序是不可见的。汇编指令允许为程序选择默认的寻址和操作数大小，汇编器和其他工具然后适当的为代码段设置段描述符。

When operating in real-address mode, the default addressing and operand size is 16 bits. An address-size override can be used in real-address mode to enable 32-bit addressing. However, the maximum allowable 32-bit linear address is still 000FFFFFH (2^20 -1).

在实地址模式下，默认的寻址和操作数大小是16位。在实模式下可以使用地址覆盖来启用32位寻址。然而，最大的32位线性地址仍然是000FFFFFH (2^20 -1)。