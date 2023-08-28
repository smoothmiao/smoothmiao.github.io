---
title: USB2.0基础规格(二)
date: 2023.8.8
tags: [USB2.0]
---

USB2.0基础规格的学习记录，标准规格的第5-x章。

<!-- more -->

# 5 USB数据模型(Data Flow Model)

This chapter presents information about how data is moved across the USB. The information in this chapter affects all implementers. 
本章会提供一些关于数据是怎样在USB上移动的信息，这些信息会影响所有的实现者。
The information presented is at a level above the signaling and protocol definitions of the system. 
Consult Chapter 7 and Chapter 8 for more details about their respective parts of the USB system. 
This chapter provides framework information that is further expanded in Chapters 9 through 11. 
All implementers should read this chapter so they understand the key concepts of the USB.

## 5.1 实现者的焦点

* In particular, there are four focus implementation areas:
    - USB Physical Device: 
        `与服务提供方式密切相关的部分`
        A piece of hardware on the end of a USB cable that performs some useful end user function.
    - Client Software: 
        `与用户应用密切相关的部分`
        Software that executes on the host, corresponding to a USB device. 
        This client software is typically supplied with the operating system or provided along with the USB device.
    - USB System Software: 
        `与操作系统密切相关的部分`
        Software that supports the USB in a particular operating system. 
        The USB System Software is typically supplied with the operating system, independently of particular USB devices or client software.
    - USB Host Controller (Host Side Bus Interface): 
        `与USB底层硬件密切相关的部分`
        The hardware and software that allows USB devices to be attached to a host.

![实现分类](/image/USB/implementation_areas.png "Fig.5.1-1")
上图描述了，USB设备和主机交互过程中，层级之间和实体之间的关系

* To describe and manage USB communication, the following concepts are important:
    - Bus Topology: 
        Section  5.2 presents the primary physical and logical components of the USB and how they interrelate.
    - Communication Flow Models: 
        Sections 5.3 through 5.8 describe how communication flows between the host and devices through the USB and defines the four USB transfer types.
    - Bus Access Management: 
        Section  5.11 describes how bus access is managed within the host to support a broad range of communication flows by USB devices.
    - Special Consideration for Isochronous Transfers: 
        Section  5.12 presents features of the USB specific to devices requiring isochronous data transfers. 
        Device implementers for non-isochronous devices do not need to read Section 5.12

## 5.2 总线拓扑结构

* There are four main parts to USB topology:
    - Host and Devices: 
        The primary components of a USB system
    - Physical Topology: 
        How USB elements are connected
    - Logical Topology: 
        The roles and responsibilities of the various USB elements and how the USB appears from the perspective of the host and a device
    - Client Software-to-function Relationships: 
        How client software and its related function interfaces on a USB device view each other

### 从主机的角度看
