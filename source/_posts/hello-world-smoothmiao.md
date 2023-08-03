---
title: Hello World Smoothmiao
date: 2023.8.1
tags: [GitPage, Hexo]
---
在Windows下，使用Hexo，部署GitPage，的经验分享(简易版).

<!-- more -->

# 1 安装依赖

## 1.1 安装nodejs和npm(nodejs自带)
``` bash
$ https://nodejs.org/zh-cn/download
```

## 1.2 安装git
``` bash
$ https://git-scm.com/downloads
```
这里省略git的配置，请参考网络上其他人的经验分享。

## 1.3 安装hexo，使用git工具 "Git Bash Here"
``` bash
$ npm install -g hexo
```
这里不安装hexo-cli，在我这里容易出错，你要是不会出错可以尝试安装它

# 2 产生网站源代码和静态网页

## 2.1 使用Hexo，先修改一下_config.yml中public_dir后参数为docs，方便Gitpage部署
``` bash
$ hexo init && npm install && hexo generate
```

## 2.2 提交除开node_modules文件夹的其他所有文件
``` bash
$ git add/commit/push
```

# 3 Git Page配置
找到Setting页的Pages项，将Build and deployment中的网站文件夹修改成docs，保存后，在Actions页pages-build-deployment项里重新build

成功后，就可以打开你的网址查看网页，比如说
``` bash
$ https://smoothmiao.github.io/
```

