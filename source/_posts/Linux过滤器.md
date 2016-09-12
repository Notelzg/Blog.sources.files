---
title: Linux过滤器
categories:
  - 学习笔记
  - 教程
tags:
  - 笔记
toc: true
date: 2016-09-02 07:58:01
---
  最近在看《unix & Linux 大学教程》这本书 ，觉得看完鸟哥再看这本书收获
还是很多的，鸟哥告诉你how do，这本书告诉你why do ，很多命令很多设置是非常
容易忘记的，因为linux or unix 的高度可定制化的哈。今天就记录一下过滤器的
相关命令，以备自己的查看，毕竟这些东西就是我的小工具箱。

<!--more-->
------
# 过滤器是什么
过滤器就是从标准输入按行读取内容，并且把内容写到标准输出，这是最简单的过滤器
没有任何过滤功能的过滤器，当然了也有各种功能的过滤器在等着你哈。你想喝什么样
的水，就得用什么的源or过滤网，这个完全取决有你自己。

# 基本行过滤器
    面向行的过滤器。
## cat
cat [-nbs] file... 
cat 可以把一个至多个文件连接在一起，然后输出到屏幕。
-n number 在每行输出添加行号
-b blank  和-n一起使用时，空白行不编号
-s squeeze 将多个空白行替换为一个
## tac
tac 是 cat 的反向拼写，所以功能刚好是相反的，再把读到的内容写入到表准输出时
把行的顺序翻转过来,当然了也可以是多个文件，这个在看日志文件的时候很方便。
下面是t.txt 文件内容
hello word
you
are
me
cat t.txt
me
are
you
hello word
## split
    前面的tac cat 都可以把多个文件合并起来，同样的有程序可以把文件分割开来
根据行数，split 默认分割行数是1000 行    
split [-d] [-a num] [-l lines] [file [prefix]]
-d 表示分割的文件名从0 开始编号 # 默认的文件名字是字母
-a 表示使用-d 数字的位数
-l 表示分割的行数
prefix 表示分割文件名字的前缀
## rev
    rev reverse 反转每一行字符的顺序，跟字符串反转是一样的，不过按行处理
## head
    head [-n lines ] 
    head 从标准输入读取数据，输出数据的前 n 行默认显示前十行    
## tail
    tail [-n lines]
    从标准输入读取数据，输出数据的后n 行，默认显示后十行
## less
    less files..
    默认显示一个屏幕的数据。
# 列过滤器
## colrm
    colrm 速记 column remove 列删除
    colrm [startcol [endcol]] startcol endcol 列的开始和结尾，列数从1开始
    colrm 1 2 < t  # 删除第一列和第二列
    llo word
    u
    e
## cut
   colrm 是从标准输入中删除选定的列，cut 是从标准输入中选择列作为标准输出
   cut [-cd list] file... 
   -c (column 列)是跟colrm 一样按列选择 可以使用 "," 组成list
   -d (delimiter 分隔符) 根据特殊符号分割行，然后使用 -f (field 域)选择分割的列
   cut -c 1-2,3-5 t
   cut -f 1 -d ";" t 
## paste
    colrm cut 都是对列进行选择，paste 刚好相反，paste是组合文件按照列
    paste [-d delimiter] file...  #按照分隔符组合文件 
# 比较过滤器
## cmp
cmp file1 file2 
比较俩个文件按照字节，所以文件可以是二进制或者文本
## comm
comm [-123] file1 file2
comm 比较俩个相似的文件，并且文件是有序的文件，输出分为三列，第一列显示只有第一个
文件所有的行，第二列显示第二个文件中有的行，第三列显示俩个文件中都有的行。
使用 -123 组合可以屏蔽，不想看到的列。
-1 不显示第一列 
## diff
diff [-iwbBc]  file1 file2
不要求俩个文件是有序的还是无序的
-i 忽略大小写这个好像在很多地方都用到了
-w 忽略所有的空白符 ab, a   b, 竟然是一样的太可怕了
-b 忽略空白符，不过是把多个空白符合并成一个
-B 忽略空白行，不过是把多个空白行合并成一个
-c 输出不同的时候，显示上下文比较容易理解
diff 的输出，刚开始真的很不熟悉不过因为按照行来的，其实如果你经常使用git 的话，你会
发现git 里面显示文件的差别用的应该就是diff因为我看输出的格式什么的都一样。
```
    diff t1 t2
    输出：
        1d0 #表示删除第一个文件第一行才和第二个文件一样 内容是 hello word
        < hello word
        4a4 # 表示第一个文件第四行需要append 追加一行 内容是li
        > li
```
# 统计
wc [-clLw] [ file...]
-c 统计字节
-l 统计行数
-w 统计单词
-L 显示文件中的最长行
# 排序
sort [-cu] [file]
-c check 检测数据是否是有序的
-u unique 只显示所有的行是唯一行，消除重复行
# 重复行
uniq 默认显示重复行中的一行，也可以只显示重复行，or 只显示唯一行，更可以统计重复次数
uniq [-cdu] [inffile [outfile]]
-c count 统计每行出现的次数，并且加上行的前面
-d repeated 输出重复的行
-u unique 只显示唯一行，不显示重复行
# grep 
http://blog.csdn.net/li740207611/article/details/50783367 
可以看看这个
# 格式化文件
## fold
fold 主要用来格式化文件，保证文档的长度不超过定义的长度，如果超过则在让超出部分换行
fold [-s] [-w width] file...
-s  不分割单词
-w width 行的长度按字符处理
## fmt
fmt [-su] [-w width] [file..]
fmt 格式化段落，使每一行的长度跟规定的一样长，自动合并断行
-s 不合并短行
-u uniform spacing 统一空格，如果有多个空格只保留一个
-w 和fold 一样
