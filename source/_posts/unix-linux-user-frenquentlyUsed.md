---
title: unix&linux-user-frenquentlyUsed
categories:
  - 学习笔记
  - 教程
tags:
  - unix&linux
  - 笔记
toc: true
date: 2016-09-09 10:28:44
---

读《unixu&linux大学教程》 记录
用户登陆系统，希望使用的命令，比如现在都有谁在登陆 
登陆了多长时间，我的系统的内核，或者我所使用的是什么
系统等。
<!--more-->

------
# 登陆
```
    users #显示登陆用户名
    who #当前登陆的账号和时间
    w # 更加详细的信息
    uptime #登陆了多长时间
    date #显示日期
    cal #显示日历 可以显示具体月 年 等 可以man cal 查看具体命令
    leave #设置备忘录，时间到了会输出信息告诉你，如果你不想忘记约会时间的话
    可以使用这条命令。
    last [-n] # 上次登陆的信息 
    uname -a # 输出信息关于系统 内核 硬件 信息下面是我的Linux logan-Lenovo 
             # 3.19.0-68-generic #76~14.04.1-Ubuntu 
             #SMP Fri Aug 12 $11:46:25 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux
    tty # 输出当然shell 设备
    echo $SHELL # 输出当前使用的shell
    set -o # 输出当前shell 的设置信息
    history #输出历史命令
```
# 文件大小
```
    ls -sh /etc  #显示/etc 目录下面的文件大小
    du -h /etc # 显示目录所占的总内存
    df -h #显示当前用户的磁盘，加上sudo 显示所有用户的磁盘使用情况以及挂载的硬盘
```
# 进程
## 查看
ps -axu #输出当前的所有进程可以和 grep 组合使用(ps -axu | grep "test")
pstree # 输出进程树
ps 输出的当然用户的进程，top 输出当前系统的进程
top -d 1 # 每隔一秒刷新一次 
top 是动态的 ，ps 是静态的是某时刻进程的快照
## 挂起
Ctrl+z 挂起当前进程，挂起之后会显示一个进程号那就是被挂起的进程号
使用jobs 可以查看所有挂起的作业或者进程
## 查看挂起进程
jobs #查看挂起的进程 or 作业(作业可以由多个进程组成)
## fg
fg 可以把上一个挂起的进程恢复到前台 如果有多个挂起的进程可以通过 fg %name 选择特定的
细节请看 man fg
## bg
bg 可以把一个前台的进程转到后台去运行，假如你运行了一个程序但是发现运行时间特别长
你就可以使用Ctrl+z 挂起进程，然后使用jobs 查看进程，然后使用bg % 选择挂起的进程。
## kill
kill [-signal] pid...
kill其实是给进程发信号的程序，不过因为默认的信号是STOP即关闭进程，所有就叫做kill了
kill 还有一些其他的选择，kill -9 pid 强制杀死一个进程,更多的选择请：man kill
其实这个有一个另外的名字：RTFM (reading the fuck manual) : 阅读这该死的手册
这个才是学习进阶的宝典。

# 环境变量
## 设置
env #会输出所有的环境变量
export PATH=$PATH:/home/logan/java7/bin; #设置java的环境变量，环境变量是用“:”作为分隔符
但是当前shell 关闭之后，这个变量就不会存在了，要想永久保存，bash shell ubuntu把这句话添加
到/etc/profile 里面，“;”可以去掉 ，或者添加到 ~/.bashrc 里面也可以
，然后使用 souce ~/.bashrc,使设置在当前shell 生效，下次重启在所有的shell 就生效了。
添加当然工作目录到path 是一件很有趣的事情，但是我要提醒你，最好把所有的自己环境变量都添加
到path的后面，而不是前面，除非你明白自己在做什么。
export PATH='$PATH:.' #
## 永久
/etc/profile #叫做登陆文件，只在登陆的时候运行一次，建议把环境变量 或者 只需要开机运行的
任务放到这里面
~/.bashrc # 叫做bash 配置文件，每次shell 启动的时候都会运行一次，一般会把 alias 别名的设置
放到这里面。

# 有用的程序
!! 运行上次的程序 
sudo !! # 超级用户运行上次的命令
fc -l #显示历史命令 全局的
fc -s id # 修改历史命令并且执行
history # 显示当前shell的历史命令
# summary
    我觉得这些命令or 程序在有的时候特别有用，但是我又记不住所以就留个底，备忘录哈。当然希望
帮助有需求的你！    

