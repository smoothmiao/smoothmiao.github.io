---
title: ssh
date: 2023-08-08 09:41:10
tags: [SSH]
---
本意记录下ssh相关使用方式和经验，发散了一下，变成了密码学概论。

<!-- more -->

# ssh是什么

ssh(Secure Shell)[安全外壳]
是一种目前被广泛使用的加密登录协议，在此协议基础上通过不同的[ssh-SC服务对]实现了对远程主机的控制

先列举一些学习资料
[加密算法](https://zhuanlan.zhihu.com/p/347114235)
[SSH与GPG](https://zhuanlan.zhihu.com/p/137801979)
[远程控制](https://www.cnblogs.com/zcg-cpdd/p/14654492.html)
[SSL/TSL](https://zhuanlan.zhihu.com/p/133375078)
[http/https](https://www.zhihu.com/tardis/zm/art/72616216)



# ssh的产生
ssh key-gen

# ssh 的config 文件
在 /usr/.ssh/config 中配置可以访问的主机
通过 ssh hostname 来访问

典型的配置项如下

Host [name]
	HostName 172.21.2.160
	User sonix
	Port 22
	HostKeyAlgorithms +ssh-rsa
	PubkeyAcceptedKeyTypes +ssh-rsa
	IdentityFile C:\Users\[user]\.ssh\[name]_rsa

此时访问可直接使用
 ssh [name]

通过 -vNTL 转发其他端口数据

eg: ssh -vNTL 8080:192.168.37.1:80 [name]

