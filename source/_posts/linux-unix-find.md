---
title: linux&unix-find
categories:
  - 学习笔记
  - 教程
tags:
  - Unix&linux
  - 笔记
toc: true
date: 2016-09-09 08:03:06
---

说一下查找whereis locale find程序
主要说find 程序经常使用的部分命令。
<!--more-->

------
# whereis
    whereis 程序主要用来查看linux or unix 外部程序和帮助文档或者其他文档的位置
通过它，你可能发现一些没有听别人说过的文档，用法，主要是 通过查找/bin /usr/bin
等环境变量路径来查找。
```
    whersis ls 
    输出：
    ls: /bin/ls /usr/share/man/man1/ls.1.gz
    /bin/ls 是ls程序所在的位置
    ls.1.gz  就是我们使用man ls 看到的文档，在使用的时候解压
```
# locale
    locale程序的任务就是搜索一个特殊的数据库（该数据库中包含所有可公共访问的文件
的路径名)，查找所有包含特定模式的路径名。该数据库自动维护，并自动更新。locale程序
的语法为 locale [-bcirS] pattern 
-b base 匹配路径名的最后一部分，即所谓的文件名或基名
-c count 统计匹配文件的次数
-i ignore 匹配的时候忽略大小写
-r regex 匹配使用正则表达式，这个跟grep里面的一样
-S statistics 统计选择，显示系统上的locate数据库信息
这些选择都服合GNU规则，所以可以组合使用

```
    locale -rb '*temp$'
    locale：无效选项 -- r
    试用“locale --help”或“locale --usage”以获取更多信息。
    经过测试发现，ubuntu系统内置的locale 程序不支持上面的选项
    上面的选择在unix 上面的locale才支持，bsd的只支持
    locale [options] name 
    选择只有俩个，可以 man locale 看一下，反正我从来没有用locale
    得到我想想要的还是用find的吧，ubuntu用户
```
# find
find path... test... action...
通过观察我们可以发现路径可以有多个 test查找条件也可以有多个，action
也可以有多个find命令也继承了unix or linux的特点，学习困难使用容易哈哈。
## path
```
    find /etc /bin /usr  # 可以使用多个路径组合查询
    在bash shell 里面 如果不指定路径的话，则是默认的当前路径即 ./ 
    下面的命令是等价的：
    find test
    find ./ test
    find . test
```
## test
test 就是测试，这里就是查找条件主要的查找条件有
-type [df] #d  directory 路径，f file 文件
-name pattern # pattern 和 grep 的模式语法一样
-iname pattern # 忽略大小写
-size [-+]n[cbkMG] - 表示小于 +表示大于 默认是等于 c 字节 b 块 k 千字节 m g 大家应该很熟悉
-empty #空文件(等价于 -size 0c)
修改时间 min 分钟 time 天数 a access 访问 c change 状态改变 m modified 内容修改
-amin -5 五分钟之内访问
-amin +5 五分钟前访问
-atime -365 一年之内访问的
-atime +365 一年前访问的
修改a 为 [cm]就是改变的 or 内容修改的
这些条件可以并列使用 find /temp -type f -name test -size -10c -amin 5 
特别的可以通过使用！，条件取反，以为！ 在linux有特殊含义 需要转义字符 \! or 强引用 ’!‘
-------
find \! -name '*.jpg'  # 查找所有后缀名不是jpg的文件
## action
通过前面俩步找到了想要的文件or目录，下面可以对找到的东西进行处理了，可以显示 删除
等操作，反正你可以想到的命令都可以使用的哦。
```
    -print #将路径名写入到标准输出 这个是默认的
    -fprint file # 输出写入到文件
    -ls #显示长目录列表
    -fls file #写到文件
    -delete #删除文件
    -exec command {} \; #执行command，{}指示匹配的文件名 注意{} 和 \;之间的空格，没有会报错滴！
    -ok command {} \; #和exec 一样，只是在做操作前需要确认 输入y 回车确定，直接回车什么也不做
    做一个测试输出查找到的文件名使用echo
    find -name 't*' -exec echo {} \;
    修改查找到的文件权限为 700
    find -name 't*' -exec chmod 700 {} \;
    删除下面俩条语句都可以可以：
    find -name 't*' -exec rm {} \;
    find -name 't*' -delete 
```

# xargs
处理查找到的文件的时候使用 exec 处理command 有多个目标文件就会有执行command多少次，使用xargs可以
把找到的文件通过管道，当做参数一次处理
```
    xargs [-prt]  [-istring] [command [argument...]]
    find -name 't*' | xargs echo {} # 看看输出你就会发现和 exec 的不同
    {} . ./Linux过滤器.md ./深入理解计算机系统总结.md ./disamy-mbr.md
    -p 每次action前 请求确认 y 是 不输则否
    -t 输出命令本身意思是：tell me what are you doing
    -r 告诉xargs 如果没有输入参数，则不运行命令（xargs 默认运行一次）
    -i insert ，当你需要在xargs里面多次使用参数的时候比如
    find -name 't*' | xargs -i echo {} {} 
    find -name 't*' | xargs -i mv {} ~/backup/{}.old
```
# Summary
   我认为查找命令特别是find 命令，可以作为我们的重要的伙伴来培养，你越是熟悉它
它就可以提高你的工作效率，特别是在处理大量文件的时候，这个是必不可少的小伙伴了
以前我刚开始的时候总是不喜欢用find 因为老是记不住这些命令太长了，现在我就通过
记录来帮助自己更好的使用它，我想只要我们坚持，unix or linux 是不会令我们失望的
毕竟在20世纪70年代的东西还一直在影响着这个世界，一些工具程序30年前被使用 
30 年后照样被使用。希望学习一些，就像酒一样的技能，随着时间的延续，越来越吃香哈哈。
