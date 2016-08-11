---
title: ubuntu14-color-config
categories:
  - 教程
tags:
  - 笔记
  - Ubuntu
  - Solarized Colorscheme
  - gnome
toc: true
date: 2016-08-11 09:25:03
---

给gnome 终端，终端中的vim vi ls(命令) 终端模拟器
terminator 256颜色配置方案。让你的终端变的五颜六色
充满生机。前提终端是xterm类型
<!--more-->

------
# ls color
让ls ll 列出的目录颜色不一样，压缩包是紫色同类的文件
显示一样的颜色这样也有助于我们分辨。
## 下载颜色主题
```
git clone git://github.com/seebi/dircolors-solarized.git
```
## 设置主题为当前用户
```
 cp ~/dircolors-solarized/dircolors.256dark ~/.dircolors
 # 这里面有几种颜色配案，可以去[主页](https://github.com/seebi/dircolors-solarized)看看
 cd # to home dir
 eval 'dircolors .dircolors' #change .dircolors 文件内容
```
## 支持256颜色
1. 查看终端类型
```
 echo $TERM # 查看终端类型是不是 xterm 
 tput colors # 查看支持颜色如果是256就不用管，如果不是请修改为256
``` 
2. 修改xterm终端类型为256 
在 ~/.bashrc 文件添加
```
 if [ "$TERM" == "xterm" ]; then
       export TERM=xterm-256color
 fi
```
# Gnome Terminal 配色
```
     git clone https://github.com/Anthony25/gnome-terminal-colors-solarized.git
     cd   gnome-terminal-colors-solarized
     ./install.sh
```
# vim 配置

## Download
```
 git clone git@github.com:altercation/vim-colors-solarized.git
```
## install
```
cd vim-colors-solarized/colors
cp solarized.vim ~/.vim/colors/  # 如果文件不存在，那就创建
```
## 开启对256颜色支持
```
syntax enable "代码高亮
set t_Co=256 "开启256支持
set background=dark “暗黑
colorscheme solarized " 选择 Solarized 颜色主题
最后同样需要在 ~/.bashrc 文件里面设置 
export TERM=xterm-256color
# 已经设置过就不需要了
```
# terminator vi 配置Solarized 
因为Solarized的vi 命令行模式需要面板配置也是Solarized 的
terminator 在颜色设置里面有面板设置，直接选择 Solarized 
就行了。
有面板选项
# 总结
最后发现这个主题，ls 不错，别的还是用的自己以前配置的
颜色配置主要的还是选择自己看着顺眼的，不过重新弄了一次
发现，对vi 的配置更加熟悉了，这也是不错的的
就是在这样的倒腾中，得到提升。
