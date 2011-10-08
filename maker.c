#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define NUM 20
#define NAME 256
#define TRANS 32
#define MAILL 60
#define INFO 1024
#define EASY 1
#define COMPLEX 2 

typedef struct complex
{
    int flag;
    char *str;
    char *auther;
    char *maill;
    char *info;
    char *path;
}head;

void trans(char *str)
{
    int size;
    int iloop;

    size=strlen(str);
    for(iloop=0;iloop<size;iloop++)
    {
        if(str[iloop]>='a' && str[iloop]<='z')
            str[iloop]=str[iloop]-TRANS;
    }
}
#if 1
int maker(head *p)                        //传进来的文件名以；隔开
{
    int iloop,jloop;
    int count=0;
    int num=0;
    int flag=0;
    char name[NUM][NAME]={{0}};
    char buf[NAME]={0};
    FILE *fd;
    DIR *dir_p;

    for(iloop=0;;iloop++)//分离名字
    {
        for(jloop=0;;jloop++)
        {
            if(p->str[jloop+count]=='\0')
            {
                flag=1;
                count=0;
                break;
            }

            if(p->str[jloop+count]==';')
            {
                count+=jloop+1;
                break;
            }

            name[iloop][jloop]=p->str[jloop+count];
        }

        num++;

        if(flag==1)//外层for循环跳出
        {
            flag=0;
            break;
        }
    }

    if((dir_p=opendir(p->path))==NULL)
    {
        printf("Can't find the path, please firstly determine it presence\n");
        return 1;
    }
    closedir(dir_p);

    for(iloop=0;iloop<num;iloop++)
    {
        /*创建c文件*/
        memset(buf,0,sizeof(buf));
        if(p->path[strlen(p->path)-1]!='/')
            p->path[strlen(p->path)]='/';
        sprintf(buf,"%s%s.c",p->path,name[iloop]);
        fd=fopen(buf,"w+");

        fprintf(fd,"/*FileName:%s.c*/\n",name[iloop]);

        if(p->flag==COMPLEX)
        {
            fprintf(fd,"/*Auther:%s*/\n",strlen(p->auther)==0?NULL:p->auther);
            fprintf(fd,"/*E-maill:%s*/\n",strlen(p->maill)==0?NULL:p->maill);
            fprintf(fd,"/*Infomation:%s*/\n",strlen(p->info)==0?NULL:p->info);
        }

        fputs("#include <stdio.h>\n\n",fd);
        fputs("int main(int argc, const char *argv[])\n",fd);
        fputs("{\n\n\treturn 0\n}",fd);
        fclose(fd);


        /*创建头文件*/
        memset(buf,0,sizeof(buf));
        if(p->path[strlen(p->path)-1]!='/')
            p->path[strlen(p->path)]='/';
        sprintf(buf,"%s%s.h",p->path,name[iloop]);
        fd=fopen(buf,"w+");

        fprintf(fd,"/*FileName:%s.h*/\n",name[iloop]);

        if(p->flag==COMPLEX)
        {
            fprintf(fd,"/*Auther:%s*/\n",strlen(p->auther)==0?NULL:p->auther);
            fprintf(fd,"/*E-maill:%s*/\n",strlen(p->maill)==0?NULL:p->maill);
            fprintf(fd,"/*Infomation:%s*/\n",strlen(p->info)==0?NULL:p->info);
        }

        trans(name[iloop]);
        fprintf(fd,"#ifndef %s_H\n#define %s_H\n\n\n#endif",name[iloop],name[iloop]);

        fclose(fd);
    }

    return 0;
}
#endif
int menu(head *p)
{
    printf("Please input file path:\n");
    read(0,p->path,NAME);
    p->path[strlen(p->path)-1]=0;
    printf("Please input file name:(more files are aparted by ';')\n");
    read(0,p->str,NAME);
    p->str[strlen(p->str)-1]=0;
    printf("Please input file auther:\n");
    read(0,p->auther,NAME);
    p->auther[strlen(p->auther)-1]=0;
    printf("Please input E-maill:\n");
    read(0,p->maill,MAILL);
    p->maill[strlen(p->maill)-1]=0;
    printf("Please input file infmation:(less than 1024 bit)\n");
    read(0,p->info,INFO);
    p->info[strlen(p->info)-1]=0;

    return 1;
}
int main(int argc, const char *argv[])
{
    int num;
    int iloop;
    head *p=NULL;

    p=malloc(sizeof(head));
    p->str=(char *)malloc(NAME);
    p->auther=(char *)malloc(NAME);
    p->maill=(char *)malloc(MAILL);
    p->info=(char *)malloc(INFO);
    p->path=(char *)malloc(NAME);

    if(argc>=2)
    {
        p->flag=EASY;
        num=argc-1;
        for(iloop=0;iloop<num;iloop++)
        {
            strcpy(p->str,argv[iloop+1]);
            //printf("%s\n",p->str);
            maker(p);
            memset(p->str,0,NAME);
        }
    }
#if 1
    else
    {
        p->flag=COMPLEX;
        menu(p);
        maker(p);
    }
#endif
    return 0;
}

