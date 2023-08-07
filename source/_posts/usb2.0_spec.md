---
title: USB2.0基础规格
date: 2023.8.2
tags: [USB2.0]
---

USB2.0基础规格的学习记录

<!-- more -->

# 1 USB规格的简介

## 1.1 原动力(Motivation)

### A 电话和电脑互联(Connection of the PC to the telephone)

* [电话(telephone)]是[通信(communication)]的代表，[电脑(PC)]是[计算(computing)]的代表，
    - 他们的互联，也代表着计算和通信的融合，几乎所有人已经有这样的共识，这是下一代生产力应用，工作的基础。而从USB被广泛使用的今天来说，这无疑被证明是正确的。
* 从一方面来说，
    - [面向人类(human-oriented)]的数据，和[面向机器(machine-oriented)]的数据，他们的交互，依赖的是[无处不在(ubiquitous)]的[便宜(cheap)]的连接。
* 另一方面来说，
    - 他们早期的发展是相互独立的，并且可以预想，以后也会独立发展，隔绝相关性来说，对双方都有好处，而关联，可以交给融合来发展。
* 于是USB应运而生。
    - USB连接当初的电话和PC，以及后来的各种设备和PC，甚至手机和各种存储设备，或许以后的各种计算设备也能使用。
* 这里的电话和电脑以及连接的概念都可以延申开去，基于现在的技术发展：
    - 与人类交互的设备都能定义成电话，比如说将要大力发展的可穿戴设备。
    - 与机器交互的设备都能定义成电脑，比如说已有极大发展的各种计算云服务，和存储云服务。
    - 网络基础设施，无疑充当了连接的重任，不管是有线连接还是无线连接。

### B 使得易于使用(Ease-of-use)

相较于其他连接方式，对于更广泛的部署来说，PC端配置的缺少灵活性，
已经被公认为是[阿喀琉斯之踵(Achilles’ heel, 致命缺点)]，
整合用户友好的界面和软硬件之后，新一代的总线(USB2.0)架构，
可以使得电脑端减少[迷惑性(confrontational)]并且易于被配置。
同时，站在用户的视角上看，有很多[接口(interfaces)]，并不需要热插拔的属性，比如PC的I/O接口，
如串口/并口、键盘/鼠标/操纵杆接口等

### C 提高端口的扩展性(Port expansion)

相较于其他连接方式，因为端口常被被设计成一对一或一对二的优化，导致端口的可重用性不高，
    比如由于缺乏双向、低成本、中低速度的外设总线，
    导致诸如电话/传真/调制解调器适配器、答录机、扫描仪、PDA、键盘、鼠标等外设的连接受到了阻碍。
现在，你可以通过新增[接口(interfaces)]，来非常容易的使这些设备可以工作起来。

## 1.2 推动力

为了适应电脑和设备的快速发展，比如个人电脑的处理能力和储存能力大幅提高，同时，PC外围设备也增加了更多的性能和功能。
而且用户应用需要PC和这些日益复杂的外围设备之间更高性能的连接，比如[数字成像(digital imaging)]。
在USB1.0的1.5Mb/s和12Mb/s的基础上，新增USB2.0的480Mb/s的带宽，来满足这些需求。
USB2.0可以称为USB1.0的自然演变，在提供所需的带宽增加的同时，保留USB的原始设计理念，并保持与现有外设的完全的兼容性。

## 1.3 USB特性综述

从设计原则上来说，在今天和目前可预知的未来的时间尺度上，它仍然是PC与外部设备连接的答案。
它是一种
- [快速(fast)], 
- [双向(bi-directional)], 
- [支持同步(isochronous)], 
- [低成本(low-cost)], 
- [动态可连接(dynamically attachable)], 
的[串行接口(serial interface)]

## 1.4 文档目的

* 此规格的内容
    - 定义了一个业内标准的USB，包含
        + [总线属性(the bus attributes)],
        + [协议定义(the protocol definition)],
        + [事务类型(types of transactions)],
        + [总线管理(bus management)],
    - 并且，设计和构建了符合该标准的系统和外设所需的[编程接口(the programming interface)]。
* 此规格的目标
    - 使来自不同供应商的设备，能够在一个开放的体系结构中，相互进行通信。
    - 不光，增强PC架构，涵盖可移植、商务桌面和家庭环境。
    - 也能，为系统oem和外设开发人员提供足够的空间，以实现产品的多功能性和市场差异化，而不会带来携带过时接口或失去兼容性的负担

## 1.5 文档范围

最主要的设计目标时，针对[外设开发人员(peripheral developers)]和[系统oem(system OEMs)]，
同时也可以为，平台操作系统/BIOS/设备(驱动,适配器ihv/isv,平台)/适配器的控制器供应商等，提供了有价值的信息。
也就是说，此文档可用于开发新产品及其相关软件的参考资料。

## 1.6 文档许可

USB2.0规范的采用者已经签署了USB2.0采用者协议，该协议使他们能够从发起人和其他采用者那里获得互惠的免版税许可，
以获得符合USB2.0规范的产品中包含的某些知识产权。采用者可以通过由USB实现者论坛定义的测试程序证明符合规范。
证明符合规范的产品将被授予使用USB实现者论坛徽标的特定权利，该徽标在徽标许可中定义。

## 1.7 文档结构

* Chapters 1 - 5  provide an overview for all readers.
    - 所有使用者都要应该重点阅读 Chapters 1 - 5
* Chapters 6 - 11 contain detailed technical information defining the USB.
    - 物理硬件实现者应该重点阅读 Chapters 5 - 11.
    - 主控驱动实现者应该重点阅读 Chapters 5 - 8, 10, 11.
    - 设备驱动实现者应该重点阅读 Chapters 5, 9, 10.

* 如果只是理解USB的基础协议
    - 看本文档就够了
* 要想某个设备正常工作起来，你需要在熟悉本文档的基础上，了解下面两个内容
    - (设备Device信息)通用串行总线设备类规范(Universal Serial Bus Device Class Specifications)中，和你使用的设备相关的规格。
    - (主控Host  信息)操作系统与USB相关的规格，或者你使用与USB通信的软件的规格。

# 2 USB术语和缩写

This chapter lists and defines terms and abbreviations used throughout this specification.

~~~
    ......
~~~

# 3 USB的先验知识

This chapter presents a brief description of the background of the Universal Serial Bus (USB), 
including design goals, features of the bus, and existing technologies.

## 3.1 USB设计的目标
USB被设计为PC架构扩展部分的行业标准，专注针对消费者和商业应用的PC架构的外设

* Ease-of-use for PC peripheral expansion.
* Low-cost solution that supports transfer rates up to 480 Mb/s.
* Full support for real-time data for voice, audio, and video.
* Protocol flexibility for mixed-mode isochronous data transfers and asynchronous messaging.
* Integration in commodity device technology.
* Comprehension of various PC configurations and form factors.
* Provision of a standard interface capable of quick diffusion into product.
* Enabling new classes of devices that augment the PC’s capability.
* Full backward compatibility of USB 2.0 for devices built to previous versions of the specification.

## 3.2 USB支持的应用
按应用所需的负载支持来[分类(Taxonomy)]，可以分为，低速/全速/高速，他们分别支持的应用及对应的功能属性(attributes)，可以见下图

![Application Space Taxonomy](/image/USB/application_space_taxonomy.png "Fig.3.2-1")

## 3.3 USB支持的特性
按特性产生的收益效果来![分类(categorized)]，如下
* Easy to use for end user
    - Single model for cabling and connectors
    - Electrical details isolated from end user (e.g., bus terminations)
    - Self-identifying peripherals, automatic mapping of function to driver and configuration
    - Dynamically attachable and reconfigurable peripherals
* Wide range of workloads and applications
    - Suitable for device bandwidths ranging from a few kb/s to several hundred Mb/s
    - Supports isochronous as well as asynchronous transfer types over the same set of wires
    - Supports concurrent operation of many devices (multiple connections)
    - Supports up to 127 physical devices
    - Supports transfer of multiple data and message streams between the host and devices
    - Allows compound devices (i.e., peripherals composed of many functions)
    - Lower protocol overhead, resulting in high bus utilization
* Isochronous bandwidth
    - Guaranteed bandwidth and low latencies appropriate for telephony, audio, video, etc.
* Flexibility
    - Supports a wide range of packet sizes, which allows a range of device buffering options
    - Allows a wide range of device data rates by accommodating packet buffer size and latencies
    - Flow control for buffer handling is built into the protocol
* Robustness
    - Error handling/fault recovery mechanism is built into the protocol
    - Dynamic insertion and removal of devices is identified in user-perceived real-time
    - Supports identification of faulty devices
* Synergy with PC industry
    - Protocol is simple to implement and integrate
    - Consistent with the PC plug-and-play architecture
    - Leverages existing operating system interfaces
* Low-cost implementation
    - Low-cost sub-channel at 1.5 Mb/s
    - Optimized for integration in peripheral and host hardware
    - Suitable for development of low-cost peripherals
    - Low-cost cables and connectors
    - Uses commodity technologies
* Upgrade path
    - Architecture upgradeable to support multiple USB Host Controllers in a system

# 4 USB的结构综述

This chapter presents an overview of the Universal Serial Bus (USB) architecture and key concepts. 
The USB is a cable bus that supports data exchange between a host computer and a wide range of simultaneously accessible peripherals. 
The attached peripherals share USB bandwidth through a host-scheduled, token-based protocol. 
The bus allows peripherals to be attached, configured, used, and detached while the host and other peripherals are in operation.

## 4.1 系统结构

* USB系统的组成
    - A 连接，USB interconnect
        + [总线模型(Bus Topology)]：设备和主机的连接模型.
        + [层级模型(Inter-layer Relationships)]:
            In terms of a capability stack, the USB tasks that are performed at each layer in the system.
        + [数据模型(Data Flow Models)]:
            The manner in which data moves in the system over the USB between producers and consumers.
        + [时序模型(USB Schedule)]:
            The USB provides a shared interconnect. 
            Access to the interconnect is scheduled in order to support isochronous data transfers and to eliminate arbitration overhead.
    - B 设备，USB devices
        + 细节见第9章
    - C 主机，USB host
        + 细节见第10章

### 4.1.1 [总线模型(Bus Topology)]

USB连接设备和主机，USB的物理连接是一个分层的星形拓扑。每一层中的[集线器(Hub)]，是这一层的中心。
每根线段的两端连接着，主机 与 集线器/功能，集线器 与 集线器/功能。互联模型参考下图。

![USB Bus Topology](/image/USB/bus_topology.png "Fig.4.1.1-1")

* 由于集线器和电缆的传播时间的一些限制
    - 分层最多7层，包含根集线器
    - 主机和设备之间最多支持5个集线器，不包含根集线器
    - 复合设备会被视为两层，请保证其功能必须位于7层，否则可能不能正常使用
* 关于主机
    - 在每一个USB系统中，只能有一个Host，也就是[根集线器(root hub)]
    - 我们通常称Host端的一系列实现，包括软硬件和他们的中间层，为Host Controller
    - 根集线器通常集成在Host系统中，并提供一个或多个USB端口
    - 更多信息可以参考第4.9节和第10章
* 关于设备
    - 通常集线器和功能都被称为USB设备
        + [集线器(hub)]用来提供USB端口
        + [功能(Functions)]用来附加一些实际的[能力(capabilities)]，到USB系统中
    - 在以下方面，需要提供标准的USB接口
        + 对USB协议的理解上
        + 对标准USB的操作的响应上
        + 对自己的能力的描述上
        + 更多信息可以参考第4.8节和第9章

## 4.2 物理接口

这里简述电气特性和机械特性，详细请参考第7和第6章

![USB Cable](/image/USB/cable.png "Fig.4.2-1")

* [电气特性(Electrical)]
    - 速度
        + 速度分为480/12/1.5 Mb/s
        + host和hub提供这样的功能，hub和设备之间的低速和全速数据，可以在host和hub之间以高速数据传输，减少高速设备可用带宽的影响
        + 
    - 时钟
        + 使用NRZI进行编码，通过SYNC来同步clock
    - 电缆
        + 使用VBUS和GND向设备供电，VBUS固定+5V
        + 长度可变，最长可达几米
    - 端口
        + [偏置电压终端(biased terminations)]
        + 检测连接和分离
        + 可区分 高速/全速/低速 设备
* [机械特性(Mechanical)]
    - 力学指标见第6章
    - USB传输信号使用4根导体，标准的双绞线信号对，和规格允许的电源对
    - 所有设备具有上游连接，上下游不能机械的互换，以消除集线器上的非法环回连接
    - 连接器需要四个点以支持4根线，并且包含 屏蔽外壳/坚固性/易于连接-分离

## 4.3 电力供给

* 与电力相关的内容由两方面构成，通过这两种特性，允许USB被设计成电力敏感的系统，比如基于电池的手提电脑
    - 电力分配相关
        + 主要解决，USB设备端，怎样更好的消耗主机提供的电力，的问题
        + 完全依赖线缆上的电力的设备叫，  bus-powered devices，第11章会详细描述其架构
        + 拥有可选择的电力来源的设备叫， self-powered devices
    - 电力管理相关
        + 主要解决，USB主机端，怎样更好的适应主机的电力系统，的问题
        + USB主机可能有一套独立于USB软件的电力管理系统，USB系统软件通常要实现电力管理系统抛出的事件，比如挂起/激活
        + 同样的，通常也会要求设备端实现，一些基于主机端的这些特性的功能

## 4.4 总线协议

* USB总线是轮询类型的，所有的传输都是由主机控制器启动的
    - 大多数的事务(transaction)，涉及最多由3类包(packet)的组成，
        + 一般，主机按照计划发出一个，带有描述这个事务的类型和方向，并带有指定设备地址以及端口编号信息的包，就表示事务的开始，我们称为令牌包(token packet)。
        + 然后，设备根据地址选择自己以响应令牌包。
        + 接着，会有一个数据包(data packet)被发出，设备发给主机还是主机发给设备，由令牌包中的信息决定。
        + 其中，事务源会在传输结束时，发送一个0长度的数据包，表示数据的结束。
        + 最后，事务目的地通常会在收到数据包后回应一个握手包(handshake packet)，来表示自己确实收下了数据，或者出现了其他状况。
    - 主机和集线器之间的事务，可能会涉及4类包的组成，用于管理主机和全速/低速设备的通信
    - 通常将主机上的源或目的地，和设备上的端点，之间的传输模型称为管道(pipe)，管道有两种类型
        + 流(stream)， 他的结构由其他规格定义
        + 消息(message)，他的结构由本规格定义
            + 有一个默认的消息管道在设备上电之后就会存在，以便提供对设备的配置/状态/控制等信息的访问
        + 管道常与 数据带宽/传输服务的类型/端点(endpoint)特性(比如方向性/缓冲大小) 等，密切相关
        + 通常，在USB设备被配置好之后，我们就可以说管道建立已经完成
        + 事务调度允许对流的管道进行流量控制。
            + 这可以从硬件级别实现，比如通过返回NAK握手包来限制速率，来防止缓冲区溢出或不足，当NAK结束时，主机就可以在总线空闲时重试事务。
            + 比如可以通过这样的方式实现摄像头自适应帧率的功能。
            + 流量控制机制通过构建灵活的时间表，来适应异构流管道混合的并发服务，可以让多个流管道以不同的间隔和大小的数据包来进行服务。

## 4.5 鲁棒性

* 安全保障
    - Signal integrity using differential drivers, receivers, and shielding
    - CRC protection over control and data fields
    - Detection of attach and detach and system-level configuration of resources
    - Self-recovery in protocol, using timeouts for lost or corrupted packets
    - Flow control for streaming data to ensure isochrony and hardware buffer management
    - Data and control pipe constructs for ensuring independence from adverse interactions between functions
* 错误侦测
    - 
* 错误控制
    - 

## 4.6 