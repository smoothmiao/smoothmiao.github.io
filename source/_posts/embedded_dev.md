---
title: 嵌入式开发
date: 2024-01-10 10:00:00
tags: [embedded]
---
总结嵌入式开发过程中需要了解的一些知识点。

<!-- more -->
# 嵌入式开发环境(Embedded Development Environment)
客机环境为主机环境服务，开发各种功能，到主机环境运行

## 1、 客机环境(开发环境)(上位机)
### 有且仅需要五类软件，即可进行嵌入式开发
有时，他们的界限并不是那么清晰，不一定由单独的软件完成某个功能
比如，会有一个大一统的开发环境，一般叫做集成开发环境(IDE)，集成了上述几种或所有功能。
- 编辑器(editor)
    通常需要结合代码进行，工程使用的源码管理、工程相关的资料管理
- 编译器(compiler)
- 链接器(linker)
    以上两个通常也可被称为编译工具链，通常需要对应不同的硬件环境选择相应的编译工具链
- 调试器(debugger)
- 下载器(downloader)
    以上两个通常也可被称为调试工具链，通常需要对应不同的硬件环境选择相应的调试工具链


### 以 SONIX EZ系列 的开发环境来看
- Sonix IDE 集成了上述 1/2/3/4/5 以及其他的功能
    Editor/Debugger/CInterpreter/Simulator/CComplier/Linker/
    EZComplier/LCDSimulator/Assembler/Disassembler and so on.
- 通用ELF格式管理bin中信息组成，取决于下载器

### 以 SONIX SA2 的开发环境来看
- keil5/keil6工程 实现了上述 1/2/3/4/5 的功能
- JLink 实现了上述 4/5 的功能
- SA Link 实现了上述 4/5 的功能
- 通用ELF格式管理bin中信息组成，取决于下载器

### 以 SONIX SA3 的开发环境来看
- keil3工程 实现了上述 1/2/3 的功能
- General Burning Tool 实现了上述 3/5 的功能
- XDATA Debug Tool 实现了上述 4 的功能
- Image Turning Tool 实现了上述 4 的功能
- 自定义格式管理bin中信息组成，自定义下载器

## 2、 主机环境(运行环境)(下位机)

### 硬件运行环境
主要是两类硬件环境
- 开发板
- 仿真器
通常这两类可能被集合成开发套件(Develop Kit)，也有可能是使用可编程硬件(FPGA)来进行硬件验证

### 软件运行环境
三类软件运行环境
- 无系统(none-os)(裸机)
- 实时系统(real time os)(FreeRTOS,uOS)
- 非实时系统(linux)
我把他们分别称为
- 二进制型  (需要编译成二进制文件并通过下载器进行烧录，才能运行的无系统型)
- 编译型    (需要编译成二进制文件并通过下载器进行烧录，才能运行的有系统型)
- 解释型    (不用编译成二进制文件，而通过脚本进行解释，即可运行的有系统型)

### 同步运行环境
- 硬件(HW)运行序列，通常由他们自己的控制单元控制
- 软件(SW)运行序列，通常由CPU进行控制
硬件和软件通常并行执行，不同的硬件之间也可能并行执行。
他们之间的状态同步和数据通信通常使用中断(Interrupt)，或者说，CPU和其他控制单元的通信和同步过程，通常被称作中断。
引申：其他的同步方式有，时钟同步，外设传输同步，内存共享同步，CPU多核同步，等等


## 3、 部署环境
一般来说，应该还有基于客户需求，进行合理裁剪的部署环境。
所有的功能在主机和客机环境中开发，用户需要的功能在部署环境中构建，然后进行系统性测试，方便针对不同客户进行功能定制与升级。
并提高主机和客机环境中的功能丰富性，便于综合给出更优化的解决方案给最终客户。
就目前我接触的来说，主机环境一般被作为部署环境，但我认为这两个环境应该进行切割，比较便于进行功能的管理和部署。

