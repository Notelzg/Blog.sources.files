---
title: disamy-mbr
toc: true
tags:
  - 反汇编 
  - MBR
  - 引导部分详解
categories:
  - 学习笔记
date: 2016-07-17 19:10:38
---

 今天把我们每次开机都用到的MBR，反汇编看看里面的引导代码是怎么样的顺便说一下
 MBR 相关的开机过程。以及我们经常用的U盘自启动
 程序到底值怎么玩的。

<!--more-->
-------------------
# window开机流程
## 流程
    加电-->BIOS--> MBR--> DPT--> pbr--> Bootmgr--> bcd--> Winload.exe---
----> 内核加载--> 整个windows7系统
## 细节

在CPU上电之后，若由硬盘启动，则BIOS将硬盘的主引导记录（位于0柱面、0磁道、1扇区）读入7C00处
然后将控制权交给主引导代码。主引导代码的任务包括：
扫描分区表，找到一个激活(可引导)分区；
找到激活分区的起始扇区；
将激活分区的引导扇区装载到内存7C00处；
将控制权交给引导扇区代码；
 
如果主引导代码无法完成上述任务，它将显示以下错误信息之一：
No active partition.
Invalid partition table.
Error loading operating system.
Missing operating system.
 
机器加电或按reset键后都要进行系统复位，复位后CS=FFFFH，IP=0000H，那么自然就从FFFF:0000H
处开始执行指令，这个地方只有一条JMP指令跳转到系统自检程序处，系统自检完成后把软盘的第一
个扇区（如果由软盘启动）或者硬盘的第一个扇区，即MBR扇区（如果由硬盘启动）读入到0:7C00H处
然后把控制权交出，从0:7C00H处继续执行。  
 
下面就是硬盘的MBR代码分析： 
其中的引导扇区是指硬盘相应分区的第一个扇区，是和操作系统有关的。操作系统的引导是由它来完成的，而MBR并不负责，MBR和操作系统无关。引导扇区的任务是把控制权转交给操作系统的引导程序。 
 
程序流程： 
1 将程序代码由0:7C00H移动到0:0600H（注，BIOS把MBR放在0:7C00H处） 
2 搜索可引导分区，即80H标志 
成功：goto 3 
失败：跳入ROM BASIC 
无效分区表：goto 5 
3 读引导扇区 
失败：goto 5 
成功：goto 4 
4 验证引导扇区最后是否为55AAH 
失败：goto 5 
成功：goto 6 
5 打印错误进入无穷循环 
6 跳到0:7C00H进行下一步启动工作

# 获取
## 获取mbr
```
window可以直接用hex打开，然后直接拷贝成文件
linux一条dd 命令搞定，参数不明白就 --help look

dd if=/dev/sda of=~/Desktop/mbr.bin bs=512 count=1
```
## 安装 
```
安装nasm 
sudo apt-get install nasms 
```

## 反汇编mbr
```
 //把mbr.bin 反汇编到mbr.asm
 ndisasm mbr.bin > mbr.asm
 
```
# 分析
## 二进制mbr
```
od -x mbr.bin
0000000 c033 d08e 00bc 8e7c 8ec0 bed8 7c00 00bf
0000020 b906 0200 f3fc 50a4 1c68 cb06 b9fb 0004
0000040 bebd 8007 007e 7c00 0f0b 0e85 8301 10c5
0000060 f1e2 18cd 5688 5500 46c6 0511 46c6 0010
0000100 41b4 aabb cd55 5d13 0f72 fb81 aa55 0975
0000120 c1f7 0001 0374 46fe 6610 8060 107e 7400
0000140 6626 0068 0000 6600 76ff 6808 0000 0068
0000160 687c 0001 1068 b400 8a42 0056 f48b 13cd
0000200 839f 10c4 eb9e b814 0201 00bb 8a7c 0056
0000220 768a 8a01 024e 6e8a cd03 6613 7361 fe1c
0000240 114e 0c75 7e80 8000 840f 008a 80b2 84eb
0000260 3255 8ae4 0056 13cd eb5d 819e fe3e 557d
0000300 75aa ff6e 0076 8de8 7500 fa17 d1b0 64e6
0000320 83e8 b000 e6df e860 007c ffb0 64e6 75e8
0000340 fb00 00b8 cdbb 661a c023 3b75 8166 54fb
0000360 5043 7541 8132 02f9 7201 662c 0768 00bb
0000400 6600 0068 0002 6600 0868 0000 6600 6653
0000420 6653 6655 0068 0000 6600 0068 007c 6600
0000440 6861 0000 cd07 5a1a f632 00ea 007c cd00
0000460 a018 07b7 08eb b6a0 eb07 a003 07b5 e432
0000500 0005 8b07 acf0 003c 0974 07bb b400 cd0e
0000520 eb10 f4f2 fdeb c92b 64e4 00eb 0224 f8e0
0000540 0224 49c3 766e 6c61 6469 7020 7261 6974
0000560 6974 6e6f 7420 6261 656c 4500 7272 726f
0000600 6c20 616f 6964 676e 6f20 6570 6172 6974
0000620 676e 7320 7379 6574 006d 694d 7373 6e69
0000640 2067 706f 7265 7461 6e69 2067 7973 7473
0000660 6d65 0000 6300 9a7b d681 4aef 0101 2080
0000700 0021 fe07 ffff 0800 0000 b000 0760 fe00
0000720 ffff fe07 ffff b800 0760 3800 001f 0000
0000740 0000 0000 0000 0000 0000 0000 0000 0000
0000760 0000 0000 0000 0000 0000 0000 0000 aa55
```
## 反汇编mbr
```
00000000  33C0              xor ax,ax  //设置ax寄存器的值为0
00000002  8ED0              mov ss,ax  
00000004  BC007C            mov sp,0x7c00 //设置开辟栈空间
/*
* copying the mbr from 0x7c00 to 0x600
* 200 转为十进制是 512
*/
00000007  8EC0              mov es,ax
00000009  8ED8              mov ds,ax
0000000B  BE007C            mov si,0x7c00
0000000E  BF0006            mov di,0x600
00000011  B90002            mov cx,0x200
00000014  FC                cld  // 设置寄存器为自增
00000015  F3A4              rep movsb  //拷贝
00000017  50                push ax  //入栈 16bit
00000018  681C06            push word 0x61c //入栈
0000001B  CB                retf //0x61c 出栈,并且调到0x61c即下一行代码处
0000001C  FB                sti

/* 下面开始循环扫描分区表(Partition Table)，寻找活动分区 0x80 总共4次 */
  
0000001D  B90400            mov cx,0x4 //总共四个分区表项
00000020  BDBE07            mov bp,0x7be  //分区表开始位置 偏移量是 1be + 600 = 7be
00000023  807E0000          cmp byte [bp+0x0],0x0 // 第一个字节和 0比较

/*
* jl 小于(有符号)，0x80 有符号是-8 成功表示找到活动分区，失败则是普通分区
* 找到活动分区，跳转到0x34 
*/

00000027  7C0B              jl 0x34 

//因为要么是 0x80 要么是0x0 别的情况表示分区表损坏输出错误信息
00000029  0F850E01          jnz word 0x13b 

0000002D  83C510            add bp,byte +0x10 
//每个分区16字节，也就是0x10 ，调到下一个分区

00000030  E2F1              loop 0x23 //跳转到循环开始的地方，继续检测

/*
* 没有发现活动分区，无法启动OS，按照规范调用Int 18h
* 早期的BIOS的Int 18h中断服务程序就是启动ROM-Basic，
* 现在的BIOS一般是打印错误信息
*/
00000032  CD18              int 0x18  //调用 终断 18

/*
* 找到活动分区后，还要检查剩余分区的启动标志是否为0
* 不允许存在多个活动分区
*/


/*
* 在 win7 的 MBR 中使用 int 0x13 扩展功能来读取磁盘
* http://m.wendangku.net/doc/29a5f911a76e58fafab00369-7.html 详细介绍int 13
* 因为找到0x80字段才调转的，因为dl是1byte，所以传送1byte数据到dl寄存器 
* dl 是磁盘驱动器号
*/
00000034  885600            mov [bp+0x0],dl 

00000037  55                push bp //入栈

/* 如果不成功的反复读 5 次 */
00000038  C6461105          mov byte [bp+0x11],0x5

/* 此处是一个标志位，用来记录是否支持int 0x13 扩展 */
0000003C  C6461000          mov byte [bp+0x10],0x0 

/* 测试是否支持 int 0x13 扩展功能 */
00000040  B441              mov ah,0x41 /* 设置扩展int 13的 参数固定 */
00000042  BBAA55            mov bx,0x55aa  /* 设置扩展int 13的 参数固定 */
00000045  CD13              int 0x13
00000047  5D                pop bp
00000048  720F              jc 0x59 /* 进位标志1 则表示不支持扩展int 13 */
0000004A  81FB55AA          cmp bx,0xaa55 /* bx 等于 0xaa55 则表示支持 */
0000004E  7509              jnz 0x59 /* 不支持 */
/*
* cx 等于 0x1 表示支持第一个子集
* 第一个子集提供了访问大硬盘所必须的功能,包括检查扩展In13H是否存在(41h)
* 扩展读(42h),扩展写(43h),校验扇区(44h),扩展定位(47h)和取得驱动器参数(48h)
*/
00000050  F7C10100          test cx,0x1 /* and cx, 0x1*/
00000054  7403              jz 0x59 /* 不支持 */
00000056  FE4610            inc byte [bp+0x10] /* 走到这一步表示支持 ,把标志位加1 */
00000059  6660              pushad /* 通用寄存器入栈，为了检查是否遍历完4个分区表 */
0000005B  807E1000          cmp byte [bp+0x10],0x0 /* 查看是否支持 */
0000005F  7426              jz 0x87 /* 不支持，则调用原始 int 13 0x87处是原始int 13 */

/*  以下是使用 int 0x13 扩展功能读 disk */

00000061  666800000000      push dword 0x0 /* 32bit 入栈*/

/* 
* 磁盘起始位置，我们知道dpt第八字节开始存放逻辑起始扇区号
* 这是要去读取活动分区的，第一个扇区分区表记录 即 ：ptr
* push 的数据，其实是一个数据结构
* 下面是用 c 描述为：
*/
```
struct buffer_packet
{
  short buffer_packet_size;/* struct's  size */
  short sectors; /* 读多少个 sectors */
  char *buffer; /* buffer address（segment:offset 形式）*/
  long long start_sectors; /* 从哪个 sector 开始读 */
} buffer;
```
00000067  66FF7608          push dword [bp+0x8]
0000006B  680000            push word 0x0 
0000006E  68007C            push word 0x7c00 /* 传输缓冲区地址 */
00000071  680100            push word 0x1 /* 读取扇区的个数 */
00000074  681000            push word 0x10 /* 数据包尺寸一般是/ 16字节 */

00000077  B442              mov ah,0x42 /* 读磁盘 */
00000079  8A5600            mov dl,[bp+0x0] /* 驱动器号 */
0000007C  8BF4              mov si,sp /* buffer_packet 的 address */

0000007E  CD13              int 0x13
00000080  9F                lahf
00000081  83C410            add sp,byte +0x10
00000084  9E                sahf
00000085  EB14              jmp short 0x9b /* 跳转到原int 13 之后 */
/* 使用 int 0x13 原有功能来读取磁盘 */
/* ah= 0x2 功能读 al=0x1 读一个扇区*/
00000087  B80102            mov ax,0x201 
0000008A  BB007C            mov bx,0x7c00   /* es:bx = buffer */
0000008D  8A5600            mov dl,[bp+0x0]  /* hard disk */
00000090  8A7601            mov dh,[bp+0x1]  /* 从哪个 head 开始读 */
00000093  8A4E02            mov cl,[bp+0x2]  /* 从哪个 sector 开始读 */
                             /* 其中低 6 bits 是 sector,高2位是cylinder */                                                       
00000096  8A6E03            mov ch,[bp+0x3]  /* 从哪个 cylinder 开始读 */
00000099  CD13              int 0x13

/* 活动分区已经找到，并且读取了活动分区的第一个分区表记录到 0x7c00 */

0000009B  6661              popad /* 通用寄存器出栈 */
0000009D  731C              jnc 0xbb /* 读取成功则跳转 */
0000009F  FE4E11            dec byte [bp+0x11] /* 5-1 ,通过这个变量来完成五次对磁盘的读 */
000000A2  750C              jnz 0xb0 /* 不等于0 就继续*/
/* 读完五次后 ，还找不到活动分区就输出错误信息*/
000000A4  807E0080          cmp byte [bp+0x0],0x80
000000A8  0F848A00          jz word 0x136
/* 找到则去读取分区表记录信息 */
000000AC  B280              mov dl,0x80
000000AE  EB84              jmp short 0x34 /* 读信息 */

000000B0  55                push bp /**/
000000B1  32E4              xor ah,ah
000000B3  8A5600            mov dl,[bp+0x0]
000000B6  CD13              int 0x13
000000B8  5D                pop bp
000000B9  EB9E              jmp short 0x59
/*
*代码中再次核对，是否 55aa 标志，如果不是将打印出错信息后 hlt
*代码中还将测试键盘读/写缓冲区，然后往键盘端口 0x60 写命令字。
*call word 0x156 这个子过程就是测试读/写缓冲区过程。
*代码最终将转去 0x127 执行
*/
000000BB  813EFE7D55AA      cmp word [0x7dfe],0xaa55
000000C1  756E              jnz 0x131  /* 不是，打印错信息，hlt */
000000C3  FF7600            push word [bp+0x0] 
000000C6  E88D00            call word 0x156 /* 从 64H 读 1 byte */
000000C9  7517              jnz 0xe2 /* 缓冲区满，不能写*/
000000CB  FA                cli
000000CC  B0D1              mov al,0xd1 
000000CE  E664              out 0x64,al
000000D0  E88300            call word 0x156
000000D3  B0DF              mov al,0xdf
000000D5  E660              out 0x60,al
000000D7  E87C00            call word 0x156
000000DA  B0FF              mov al,0xff
000000DC  E664              out 0x64,al
000000DE  E87500            call word 0x156
000000E1  FB                sti
000000E2  B800BB            mov ax,0xbb00
000000E5  CD1A              int 0x1a
000000E7  6623C0            and eax,eax
000000EA  753B              jnz 0x127
000000EC  6681FB54435041    cmp ebx,0x41504354
000000F3  7532              jnz 0x127
000000F5  81F90201          cmp cx,0x102
000000F9  722C              jc 0x127
/*
* 不明白 int 0x1a 中断的
*/
000000FB  666807BB0000      push dword 0xbb07
00000101  666800020000      push dword 0x200
00000107  666808000000      push dword 0x8
0000010D  6653              push ebx
0000010F  6653              push ebx
00000111  6655              push ebp
00000113  666800000000      push dword 0x0
00000119  6668007C0000      push dword 0x7c00
0000011F  6661              popad
00000121  680000            push word 0x0
00000124  07                pop es
00000125  CD1A              int 0x1a

/* 
* 代码最终回到0x7c00 ,继续执行从活动分区的第一个扇区拷贝的代码
*/
00000127  5A                pop dx
00000128  32F6              xor dh,dh
0000012A  EA007C0000        jmp word 0x0:0x7c00
0000012F  CD18              int 0x18 /* 不明白 */

/* 打印出错信息，hlt */
00000131  A0B707            mov al,[0x7b7]   /* 索引号为 9A */
00000134  EB08              jmp short 0x13e
00000136  A0B607            mov al,[0x7b6]    /* 索引号为 7B */
00000139  EB03              jmp short 0x13e
0000013B  A0B507            mov al,[0x7b5]     /* 索引号为 63 */
0000013E  32E4              xor ah,ah
00000140  050007            add ax,0x700
00000143  8BF0              mov si,ax
00000145  AC                lodsb
00000146  3C00              cmp al,0x0
00000148  7409              jz 0x153
0000014A  BB0700            mov bx,0x7
0000014D  B40E              mov ah,0xe
0000014F  CD10              int 0x10
00000151  EBF2              jmp short 0x145
00000153  F4                hlt
00000154  EBFD              jmp short 0x153


00000156  2BC9              sub cx,cx
00000158  E464              in al,0x64
0000015A  EB00              jmp short 0x15c
0000015C  2402              and al,0x2
0000015E  E0F8              loopne 0x158
00000160  2402              and al,0x2
00000162  C3                ret
/********** 下面的区域是 mbr 常量符： mbr_str　**************/
/*
* 163----1b2
char *mbr_str = "Invalid partition table."
"Error loading operation system."
"Missing operation system."
*/
00000163  49                dec cx
00000164  6E                outsb
00000165  7661              jna 0x1c8
00000167  6C                insb
00000168  6964207061        imul sp,[si+0x20],word 0x6170
0000016D  7274              jc 0x1e3
0000016F  6974696F6E        imul si,[si+0x69],word 0x6e6f
00000174  207461            and [si+0x61],dh
00000177  626C65            bound bp,[si+0x65]
0000017A  004572            add [di+0x72],al
0000017D  726F              jc 0x1ee
0000017F  7220              jc 0x1a1
00000181  6C                insb
00000182  6F                outsw
00000183  61                popaw
00000184  64696E67206F      imul bp,[fs:bp+0x67],word 0x6f20
0000018A  7065              jo 0x1f1
0000018C  7261              jc 0x1ef
0000018E  7469              jz 0x1f9
00000190  6E                outsb
00000191  67207379          and [ebx+0x79],dh
00000195  7374              jnc 0x20b
00000197  656D              gs insw
00000199  004D69            add [di+0x69],cl
0000019C  7373              jnc 0x211
0000019E  696E67206F        imul bp,[bp+0x67],word 0x6f20
000001A3  7065              jo 0x20a
000001A5  7261              jc 0x208
000001A7  7469              jz 0x212
000001A9  6E                outsb
000001AA  67207379          and [ebx+0x79],dh
000001AE  7374              jnc 0x224
000001B0  656D              gs insw

/*
* 下面是字符串索引值 
* 在出错处理过程里，根据索引值找到相应的出错信息
* 然后使用 int 0x10 打印出错信息，最后是 hlt 停机指令。
*/
000001B2  0000              add [bx+si],al
000001B4  00637B            add [bp+di+0x7b],ah
000001B7  9A81D6EF4A        call word 0x4aef:0xd681
000001BC  0101              add [bx+di],ax

/*
下面是磁盘分区表 64byte
*/
000001BE  802021            and byte [bx+si],0x21
000001C1  0007              add [bx],al
000001C3  FE                db 0xfe
000001C4  FF                db 0xff
000001C5  FF00              inc word [bx+si]
000001C7  0800              or [bx+si],al
000001C9  0000              add [bx+si],al
000001CB  B060              mov al,0x60
000001CD  07                pop es
000001CE  00FE              add dh,bh
000001D0  FF                db 0xff
000001D1  FF07              inc word [bx]
000001D3  FE                db 0xfe
000001D4  FF                db 0xff
000001D5  FF00              inc word [bx+si]
000001D7  B86007            mov ax,0x760
000001DA  0038              add [bx+si],bh
000001DC  1F                pop ds
000001DD  0000              add [bx+si],al
000001DF  0000              add [bx+si],al
000001E1  0000              add [bx+si],al
000001E3  0000              add [bx+si],al
000001E5  0000              add [bx+si],al
000001E7  0000              add [bx+si],al
000001E9  0000              add [bx+si],al
000001EB  0000              add [bx+si],al
000001ED  0000              add [bx+si],al
000001EF  0000              add [bx+si],al
000001F1  0000              add [bx+si],al
000001F3  0000              add [bx+si],al
000001F5  0000              add [bx+si],al
000001F7  0000              add [bx+si],al
000001F9  0000              add [bx+si],al
000001FB  0000              add [bx+si],al
000001FD  0055AA            add [di-0x56],dl
0x56u
```




