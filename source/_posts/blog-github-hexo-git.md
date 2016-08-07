---
title: blog=github+hexo+git
categories:
  - 教程
tags:
  - 笔记
toc: true
date: 2016-08-07 09:43:51
---

本来不想写建站教程的因为网上 so much 各种详细
但是前几天自己用git 管理blog原文档的时候，hexo崩溃
了，只好重新搞了一遍，发现，我需要好几个人的教程
才把东西重新弄好，然后增加了使用git管理，source/_posts/
下面的源文档，和自己主题的，这样再也不用担心误删源文档了。

<!--more-->

------
# github
这一步就是注册github账号，创建仓库，添加ssh-key。

## 注册
https://github.com
没有账号会提示你注册的，按照步骤注册就可以了，这个一个没有问题。

## 建仓
1. 根据照片的提示走就可以了，我觉得图文并茂比较好，所以直接
把文件跟照片结合了哈。这里假设你仓库名字为： name_rep_pages
![第一步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/0.jpg)
![第二步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/1.jpg)
![第三步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/2.jpg)
![第四步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/3.jpg)
![第五步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/4.jpg)

2. 建完第一个仓库，选择我们来建立第二个仓库，第一个仓库是用来
存放你的网站的，第二仓库是用来管理你写的博客的原文档，和你的一些
配置文件，主要目的是，以后你换 电脑了 或者 重装系统了，你可以
一步还原你当初的配置，你的原文档也不会丢失，是不是很棒啊，再也不用
怕误删哪个文件，因为git 可以帮你一键恢复哈哈。按照第一步的步骤创建
一个仓库,但是不要开启github pages ，因为不需要
名字随意，假设名字是： name_rep_sources 

## 添加key 到github
声明： 如果你已经把本地对ssh 的key 添加到github就可以省略这一步
为了以后使用的时候，不每次手动输入密码，我们需要添加一个ssh-keys
把我们本地的公钥，拷贝到github 里面，以后通过公钥进行登陆，即安全
又方便。

1. 安装git ，ubuntu linux 系统自带的有git window的话按照这个安装
吧：https://git-scm.com/book/zh/v1/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-Git
这个里面有 windows mac linux ，window在最下面很简单，下载安装包 ，双击就行了。

2. 生成密钥
```
git config --global user.email "bu.ru@qq.com"  # 填写你github注册并且验证的邮箱
git config --global user.name "bruce-sha"  # github 用户名
ssh-keygen #  会出现下面的内容，一直按Enter键就行
Generating public/private rsa key pair.
Enter file in which to save the key (/home/logan/.ssh/id_rsa): 
/home/logan/.ssh/id_rsa already exists.
Overwrite (y/n)?  #因为我已经生成过了所以提示我，你就一直按就行 
最后在你的.ssh 目录下面生成 id_rsa(私钥) id_rsa.pub(公钥)俩个文件，
看见第二行没有会提示你在哪个目录下面生成文件
开id_rsa.pub，复制里面的内容,到github，按照下面图片操作就可以了
```
![第1步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/5.jpg)
![第2步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/6.jpg)
![第3步](http://o7gxd9g18.bkt.clouddn.com/2016/08/03/7.jpg)
3. test
```
ssh -T git@github.com  
# 输出 You've successfully authenticated 表示添加key 成功，
# 失败的话看看失败原因百度or 看看这个 https://help.github.com/articles/generating-an-ssh-key/
Hi Notelzg! You've successfully authenticated, 
but GitHub does not provide shell access
```

# hexo 
现在开始搞hexo

## 搭建环境
### hexo 需要node.js 支持
这个是node官网 https://nodejs.org/en/
下载安装最新版的node.js 就行，下载的是安装包，自己安装就行了。

###　安装
hexo存放在 npm仓库里面,但是现在被墙了，直接使用国内的镜像吧
```
npm config set registry http://registry.cnpmjs.org/ 
# node 的源有很多，切换方式也很多，可以自行选择
npm install -g hexo # 全局安装hexo
```
### 初始化 
```
mkdir hexo #创建一个文件夹，初始化hexo
cd  hexo 
hexo init # 初始化 hexo 文件夹 成功就会提示你的

说一下文件夹的作用
hexo/_config.yml #这个是hexo 配置文件
hexo/.deploy_git/ # 这个目录下面存放的是hexo 自带的git 配置
hexo/node_modules/ # hexo 需要的node js 模块
hexo/.npmignore # 文件里面存放的是npm需要忽略的文件
hexo/package.json # node.js 的配置文件
hexo/public/ # 存放要生成的静态网页
hexo/scaffolds/ # 生成文档的格式，用于 hexo new 命令 默认是post格式
hexo/source/ # 存放hexo new 生成的源文件，我们写的博客就是在这里
hexo/themes/ # hexo 的主题 都在这里面
```
### hexo 命令
``` 
1. hexo new [layout] "file_name"  # 新建 file_name 文章
# hexo new 文章名字 会创建个file_name.md 的文档
# 里面有一些默认的格式，文档的路径 hexo/source/_posts/
# layout 默认的是post 即scaffolds里面的的post文件
#  不写就是默认的，layout 可以自己配置
#  具体的作用可以看这个： http://www.liuzhixiang.com/hexo_site_cn/docs/writing.html

2. hexo generate # 生成静态文档，根据上面新建的文件，hexo g 是简写
 
3. hexo deploy # 发布到博客 简写 hexo d

4. hexo clean # 清理缓存文件 数据等

```

### 配置
打开 hexo/_config.yml
根据注释配置自己的
```
# Hexo Configuration
## Docs: https://hexo.io/docs/configuration.html
## Source: https://github.com/hexojs/hexo/

# Site
title: blogLi  #网站标题
subtitle: 学生，码农，工程师 # 副标题
description: Recoding my grow of technology. # 介绍
author: Logn Li # 作者
language: zh-CN # 语言
timezone: # 访问超时时间

# URL
## If your site is put in a subdirectory, set url as 'http://yoursite.com/child' and root as '/child/'
url: https://notelzg.github.io/ # 填写github pages 生成的那个网址就ok
root: /
permalink: :year/:month/:day/:title/
permalink_defaults:

# Directory  目录对应的文件
source_dir: source
public_dir: public
tag_dir: tags
archive_dir: archives
category_dir: categories
code_dir: downloads/code
i18n_dir: :lang
skip_render:

# Writing  这里也是 写文章相关的默认配置
new_post_name: :title.md # File name of new posts
default_layout: post #默认layout方式
titlecase: false # Transform title into titlecase
external_link: true # Open external links in new tab
filename_case: 0 #将文件名转换为小写或大写，1.小写，2.大写，0.不转换  
render_drafts: false # 渲染草稿
post_asset_folder: false # 开启Assert 文件夹
relative_link: false # 相对路径
future: true
highlight: # 代码高亮
  enable: true #是否启动
    line_number: true # 行号
      auto_detect: false # 自动检测语言类型
        tab_replace: # tab 键代替几个空格

        # Category & Tag  标签和分类
        default_category: uncategorized
        category_map:
        tag_map:

        # Date / Time format
        ## Hexo uses Moment.js to parse and display date
        ## You can customize the date format as defined in
        ## http://momentjs.com/docs/#/displaying/format/
        date_format: YYYY-MM-DD
        time_format: HH:mm:ss

        # Pagination
        ## Set per_page to 0 to disable pagination
        per_page: 10
        pagination_dir: page

        # Extensions
        ## Plugins: https://hexo.io/plugins/
        ## Themes: https://hexo.io/themes/
        theme: maupassant  # 这里配置主题直接写主题的名字就行

        # Deployment  我们需要注意就就是这里
        ## Docs: https://hexo.io/docs/deployment.html
        deploy:
        - type: git
          repo: git@github.com:Notelzg/notelzg.github.com.git 
        # repo 很多人说不会填写，其实很简单，到你的开启github pages的仓库
        # 页面，里面有一个 git clone 的git 地址，复制就可以了不会出错
        # 最后注意是 git 类型的，不要复制 https 开头的
```
**我们其实就注意最后的 deploy 选项就行了，最后配置完成可以测试一下**

# theme
我推荐的大道至简的 https://www.haomwei.com/technology/maupassant-hexo.html
可以看它的安装，也可以看我的哈哈，不过我建议看我，这样你的主题配置完成之后
以后再使用非常的方便不需要自己重新配置哈哈。

1. 打开链接：https://github.com/tufu9441/maupassant-hexo
2. 点击右上角的Fork 按钮，然后你的github 仓库就会出现这个主题了
3. git clone 你自己的仓库的主题 hexo/themes/maupassant 
   ** 路径要对，可以根据自己的情况，不过一定的是 themes 目录下的**
   ** maupassant 文件夹，这个文件夹肯定不存在，git 会自己创建的**
以后你对主题做的修改就不会丢失而且载搭建博客就会方便很多
修改完，记得 git push 就行，
4. npm install hexo-renderer-jade --save
5. npm install hexo-renderer-sass --save
6. 编辑Hexo目录下的 _config.yml，将theme的值改为maupassant

# script
每次hexo new 之后自己都要cd 到 source/_posts 目录然后再找到自己刚才
新建的文章，好麻烦啊，hexo 提供相应的js 脚本，可以在hexo new 之后
使用你想用的应用打开 新建的文章。

 **新建**
```
cd 到hexo目录
mkdir scripts
cd scripts
vi new_open.js 
# 如果使用vi的这样写 
# hexo 3.x 路径是[data.path] hexo 2.x 路径是 [path]
var editor = process.env.EDITOR || 'vi';
var child = require('child_process').spawn;
hexo.on('new', function(data){
 child(editor, [data.path], {
      stdio: 'inherit'});
        });
        
# 使用sublime 
var child = require('child_process').spawn;
hexo.on('new', function(data){
 child(subl, [data.pat);
        });
# window 平台 mac 平台还是不一样的，可以看看这个
如果不行，就自行百度 google 一下
[点击这里查看](https://notes.wanghao.work/2015-06-29-Hexo%E6%B7%BB%E5%8A%A0%E6%96%87%E7%AB%A0%E6%97%B6%E8%87%AA%E5%8A%A8%E6%89%93%E5%BC%80%E7%BC%96%E8%BE%91%E5%99%A8.html)
```

# 图床
**我们肯定需要图片哈哈，我使用的是七牛云，所以就介绍一下七牛**
## 注册
[点我](https://portal.qiniu.com/signin)
注册就送空间和流量基本够用，免费的

## 添加资源
选择对象存储，添加资源就行了
然后你可以设置图片的格式，大小水印，这个按照步骤一个没有问题
图片的添加，通过--》更多操作--》内容管理 --》上传文件
图片外链就在图片操作选项里，直接复制到你的blog就行了
图片样式需要在图片外链后加上 "?图片样式"
## qshell
qshell 是七牛云提供的，在本地上传图片到七牛云的工具使用很简单
[qshell 文档里面有下载链接自己看一下吧](https://github.com/qiniu/qshell)
我一般只是使用qupload 命令同步本地图片到七牛云仅此而已
[qupload文档](https://github.com/qiniu/qshell/wiki/qupload)
```
# 这是我的 config 配置文件
# config
{
    "src_dir"       :   "/home/logan/programeFIles/blog/resource/2016-07-15",
    "access_key"    :   ""  
    "secret_key"    :   "" 
    "bucket"        :   "blog",
    "check_exists"  :  true, 
    "overwrite"     :   true,
    "key_prefix"    :   "2016/07/15/",
    "rescan_local"  :   true
} 
具体每个是干啥的可以看看文档，了解一下。配置自己的config哈
```
# git
**这里就是使用git 管理博客的文章了
** 建立git仓库 **
```
cd hexo路径
git init
```
** gitignore **
```
vi .gitignore 
** 添加以下内容 **
.DS_Store  
Thumbs.db
db.json
*.log
node_modules
public
.deploy*
debug.log
index.html
.npmig*
themes
package.json
*~
# 保存 关闭文件
```
** 添加远程仓库 **
git remote add origin 此处填写我们第一步建立的第二个仓库的git clone 的那个git地址

** 添加文件夹,不会添加已经写在 .gitignore文件里面的文件 **
git add . 

** 提交 **
```
git commit -a -m "commit first"
git push origin master
```
# 小结
基本上就是这样，如果有问题欢迎提出来，我会修改的哈，希望可以帮到你。

# 参考
[不如的博客](http://ibruce.info/2013/11/22/hexo-your-blog/)
[hexo 官方文档中文](https://hexo.io/zh-cn/)
[大道至简主题](https://www.haomwei.com/technology/maupassant-hexo.html)
[七牛云](https://portal.qiniu.com/])



