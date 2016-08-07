---
title: create git rep
categories:
  - 教程
  - git
tags:
  - 笔记
toc: true
date: 2016-08-06 09:37:20
---

看完了 ，廖雪峰大神的，git教程，我想说的是这个教程
写的很好，但是有些细节对于我这样的菜鸟来说，可能不够
细，所以就会出现各种扯淡的事情，特别是最后一个搭建自己
git服务器的，出现了各种问题，不过最后通过google，还是弄
好了，所以就分享一个详细版的，绝对让你觉得写的够细哈哈。

<!--more-->

------
# 搭建git服务器
首先说一下我使用的的是ubuntu的14.04 LTS amd64 版本的系统
## add user
```
sudo adduser git
su - git //加上 - 可以直接切换到 git 工作目录
cd  //切换到用户主目录 即 cd ～ 
mkdir .ssh && chmod 700 .ssh
touch .ssh/authorized_keys && chmod 600 .ssh/authorized_keys
```

## add 公钥
Next，你需要添加一些公钥到 authorized_keys 文件里面，这样就
可以通过 公钥进入而不需要输入密码，假如你有一个公钥的文件
在 你的 test 账号下面，一般在 /home/test/.ssh/ 目录下面
有一个 id_rsa.pub这个就是你的公钥，没有的话通过 ssh-keygen
生成一个，就可以了，可以参考这个
https://git-scm.com/book/zh/v1/%E6%9C%8D%E5%8A%A1%E5%99%A8%E4%B8%8A%E7%9A%84-Git-%E7%94%9F%E6%88%90-SSH-%E5%85%AC%E9%92%A5

```
sudo cat /home/test/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
就把你test账号的公钥加进去了，如果你想添加别的可以直接
复制到authorized_keys文件就行了，注意：每一个公钥是一行

```
## add git  repo
```
cd 
mkdir git
mkdir git/test.git
cd git/test.git
git init --bare
# 一般提示
Initialized empty Git repository in /git/git/project.git/
表示成功
```
## test 
切换到test 账号测试一下
```
su - test
cd 
mkdir git
cd git 
git clone git@localhost:git/test.git
# 这里要注意使用 因为我们是本机到时候换成目标主机ip
或者域名就行了，还有注意 :git/test.git 对应的目录是
localhost/home/git/git/test.git 
如果你怕出错就这样写：
git clone git@server:/home/git/git/test.git 
如果成功你就会克隆成功了，不成功就会有一些提示
可以google,当然了我也很乐意看到你的评论哈哈
```
一定要注意写的路径对不对，如果不对，那还说啥呢
---

## 问题
这个时候其实有一个问题，那就是所以在authorized_keys 的公钥
都可以通过ssh 远程登陆我们的git 账号了，这样做就非常的不安全
了，毕竟我们只是想让他们访问我的git，但是并不想让他们控制我
们的用户是吧，这里需要把登陆成功之后的 shell 改为 git-shell
而不是bash shell 就行了

```
cat /etc/shells # 看看有木有git-shell 如果没有 那就添加
which git-shell # 如果你安装的有这里会显示shell的路径，安装git自带
sudo vim /etc/shells # 把上一步得到的路径添加到最后一行(另起一行)

sudo chsh git -s 路径 # 把git 用户的登陆shell 改为 git-shell
git-shell 一般在/usr/bin/git-shell 所以
sudo chsh git -s /usr/bin/git-shell # -s 后面是路径
如果修改成功的话，你可以打开passwd文件看一下
因为chsh命令修改的就是这个文件
cat /etc/passwd
一般情况下最后一行是我们的新添加的用户
这个是我的 git:x:1001:1001:,,,:/home/git:/usr/bin/git-shell
如果最后的 git-shell 表示修改成功，如果没有修改成功
你也可以直接修改这个文件，廖雪峰大神就是使用的这种方法

```
## test
``` 
ssh git@gitserver
出现下面的提示表示已经成功，ssh只能使用git命令了：
fatal: Interactive git shell is not enabled.
hint: ~/git-shell-commands should exist and have read and execute access.
Connection to gitserver closed.
``` 

## 小结
跟着廖雪峰大神的教程走完了，由于使用的是空闲时间所以基本上花费
了一个月的时间，很慢我知道，不过我觉得只要一直在进步就可以了毕
竟我们一直在进步这是很值得骄傲的哈。总得来说不管是使用git来进行
开发or 进行自己的文档 or 自己的一些配置 有很多东西都可以使用git
来管理，这样当我们出现问题的时候就可以一键恢复类似于vi一样
[Ctrl-u] 就可以回到我们想要回到的地方，不过git 不仅可以回滚还
可以前进哈哈，所以叫时光穿梭机。类似于vi 的 "." 重复上一步在insert 缓冲区做的操作，我觉得git 的clone 也是这种功能，我们可以把我们
的 vim git hexo .bashrc grub fstab 等 我们认为重要的东西通过git
管理起来，因为这是私人配置，并没有隐私我们可以push到github这样
我们换一台电脑，git clone 就可以恢复到自己的配置了，我觉得还是
想当有用的，总之一切都是为了提高工作效率，有些事情做一遍就可以了
剩下的我们可以 ..... ，这才是高效率，vim高级技巧的思想已经影响
我的思维了哈哈，这本书看的也好慢，看来我要抽出时间先把这本书看了
毕竟一直在用vim ，那就这样吧，送广大coder 一句话，身体是自己的
工作永远干不完，前一段北邮的coder 半夜在实验室猝死，我觉得也许我
花了你倆倍的时间干一件事，效率确实没有你高，但是我的身体很健康
我可以活的更久，干更多的事情，所谓不谋万世者，不足以谋一世，
coding ： 不谋一辈纸，不足以谋一时。

# 参考
http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/00137583770360579bc4b458f044ce7afed3df579123eca000

https://git-scm.com/book/ch4-4.html
