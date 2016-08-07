#include <fcntl.h>             // 提供open()函数  
#include <unistd.h>  
#include <stdio.h>  
#include <dirent.h>            // 提供目录流操作函数  
#include <string.h>  
#include <sys/stat.h>        // 提供属性操作函数  
#include <sys/types.h>         // 提供mode_t 类型  
#include <stdlib.h> 
char  newname[100];
char  oldname[100];
static int  cnt = 0;//计数器
/*
dir 目录名字
depth 目录深度
p 添加前缀，在已有的文件名字前面，当然了也可以自己修改想改成啥 
*/
void scan_dir(char *dir, int depth, char *p)   // 定义目录扫描函数  
{  
    
    DIR *dp;                      // 定义子目录流指针  
    struct dirent *entry;         // 定义dirent结构指针保存后续目录  
    struct stat statbuf;          // 定义statbuf结构保存文件属性  
    if((dp = opendir(dir)) == NULL) // 打开目录，获取子目录流指针，判断操作是否成功  
    {  
        puts("can't open dir.");  
        return;  
    }  
    chdir (dir);                     // 切换到当前目录  
    while((entry = readdir(dp)) != NULL)  // 获取下一级目录信息，如果未否则循环  
    {  
        lstat(entry->d_name, &statbuf); // 获取下一级成员属性  
        if(S_IFDIR &statbuf.st_mode)    // 判断下一级成员是否是目录  
        {  
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)  
                continue;  

            printf("%*s%s/\n", depth, "", entry->d_name);  // 输出目录名称  
            scan_dir(entry->d_name, depth+4, p);              // 递归调用自身，扫描下一级目录的内容  
        }  
        else {  
                     
            sprintf(newname, "%s/%s_%s",getcwd(NULL, 0), p, entry->d_name);
            sprintf(oldname, "%s/%s",getcwd(NULL, 0),entry->d_name);
           
            
           if (rename(oldname, newname)) //output to stdout when rename failed: 
            printf("failed:  %*s%s %s \n", depth, "",oldname , newname); 
        }    
    }  
    chdir("..");                                                  // 回到上级目录  
    closedir(dp);                                                 // 关闭子目录流  
}  

/*
dir 目录名字
depth 目录深度
function: 修改目录下面的文件名字为一个从0自增的数字
*/
void rename_dir(char *dir, int depth)   // 定义目录扫描函数  
{  
    
    DIR *dp;                      // 定义子目录流指针  
    struct dirent *entry;         // 定义dirent结构指针保存后续目录  
    struct stat statbuf;          // 定义statbuf结构保存文件属性  
    if((dp = opendir(dir)) == NULL) // 打开目录，获取子目录流指针，判断操作是否成功  
    {  
        puts("can't open dir.");  
        return;  
    }  
    chdir (dir);                     // 切换到当前目录  
    while((entry = readdir(dp)) != NULL)  // 获取下一级目录信息，如果未否则循环  
    {  
        lstat(entry->d_name, &statbuf); // 获取下一级成员属性  
        if(S_IFDIR &statbuf.st_mode)    // 判断下一级成员是否是目录  
        {  
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)  
                continue;  

            printf("the child dir: %*s%s/\n", depth, "", entry->d_name);  // 输出目录名称  
            rename_dir(entry->d_name, depth+4);              // 递归调用自身，扫描下一级目录的内容  
        }  
        else {  
            sprintf(newname, "%s/%d%s", getcwd(NULL, 0), cnt++, strrchr(entry->d_name, '.'));
            sprintf(oldname, "%s/%s", getcwd(NULL, 0), entry->d_name);
           
            
           if (rename(oldname, newname)) //output to stdout when rename failed: 
            printf("failed:  %*s%s %s \n", depth, "",oldname , newname); 
//            printf("success:  %*s%s %s \n", depth, "",oldname , newname); 
        }    
    }  
    chdir("..");                                                  // 回到上级目录  
    closedir(dp);                                                 // 关闭子目录流  
}  



int main(int argc, char *argv[])  
{  
   int c ;
   int flag = 0;
   char * dir;
   if (argc > 5 || argc < 4 ) {
      printf("Please useage -f filename -p pattern\n ");
      printf("         or  -f filename -r  \n ");
      return;
   }
   while (--argc > 0 && (*++argv)[0] == '-')
   {    
       while (c = *++argv[0])  
            switch (c) {
            case 'f':
                dir = *(argv+1);
                argv+=2;
                argc-=2;
                flag++; 
                break;
            case 'p':  
               if (flag) {
                    scan_dir(dir, 0, *(1+argv));                           
                    argc--;
                    
                }    
              break;
            case 'r':  
               if (flag) {
                    rename_dir(dir, 0);
                    cnt = 0;
                    argc--;
                }    
              break;
            default: 
                printf("find : illegal option %c\n", c);
                argc = 0;
            }
   }
    return 0;  
}  
