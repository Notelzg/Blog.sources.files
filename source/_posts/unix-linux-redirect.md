---
title: unix&linux-redirect
categories:
  - 学习笔记
  - 教程
tags:
  - Unix&Linux
  - 笔记
toc: true
date: 2016-09-09 11:32:47
---

重定向是一个非常牛逼的技能，有了它你就可以飞檐走壁了哈。
<!--more-->

------
# I/O重定向（适用于Bash shell）
重定向就是重新定位标准输出输入错误。
cat file1 file2 # 命令会把file1 file2 的内容输出到屏幕，
## >
cat file1 file2 > file3 #会把合并的内容输出到file3 文件中，如果文件不存
在则创建 > 会把标准输出重新定位  >> 以追加的方式
## <
cat < file3 # 会把file3 内容输出到屏幕，< 重定向标准输入
## 2>
ls /etc # 执行这条命令的时候我们总会遇见一些错误信息，为了不看这些错误信息
ls /etc 2> /dev/null #会把错误信息输入到 /dev/null 设备文件里面什么也不返回
                   # 2> 重定向错误信息, 与此同时 ： > 同 1>  ， < 同0< 
                # 其实和 c c++ 里面的 0 1 2 ， stdin stdout stderr 是一样的  
## other                
```
2&>1 将标准错误冲定向到标准输出
>& 重定向个标准输出+标准错误
```
# 管道
## |
 cat file | less # 管道"|"把，cat file的标准输出 连接到 less 程序，作为less
 程序的标准输入，这就是管道的作用，相当于把把俩个水管连接成一个水管，一个水管
 的输出作为另外一条水管的输入。
## tee
  cat file tee file2 | less # file文件保存到file2 并且传递给less
  tee -a file ... # tee 是一个管道线分流器，类似我们水管的T型接口可以连接俩条
  水管，-a 是以追加的方式写入到文件。
# 条件执行
条件执行，写过代码的应该都使用过的 and 和 or 一般都c语言是 && || 
在shell 里面其实也一样，&& || 
command1 && command2
command2 || command2
也没有想到比较好的例子你有了 ，告诉我啊
# summary
就这样结束了，好快啊哈哈！
