#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

//客户端与服务器匹配的指令集
typedef enum
{
    UP,DOWN,CMD
}Ser_Type;

//服务器和客户端命令传递的结构体
typedef struct value
{
    Ser_Type type;
    char data[128];
}Ser_Val;

void main()
{
    //创建一个文件描述符
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    assert(socketfd != -1);

    struct sockaddr_in ser,cli;
    memset(&ser,0,sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(7000);
    //“127.0.0.1”是回送地址，这里用来模拟网络传输测试所用
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    //用于建立与指定socket的连接
    int connect_fd = connect(socketfd,(struct sockaddr*)&ser,sizeof(ser));
    assert(connect_fd != -1);

    while(1)
    {
        //客户端提供给用户的操作界面
        printf("---------功能菜单-------------\n");
        printf("---ls  pwd  cd  up  down end---\n");
        printf("请输入：");
        fflush(stdout);

        char cmd[128] = {0};
        memset(cmd,0,128);
        //从文件结构体指针stream中读取数据，stream是fgets第三个参数将要读取的文件留
        fgets(cmd,128,stdin);
        //printf("cmd == %s\n",cmd);
        //字符串最后一个字符为'\0'作为结束标志
        cmd[strlen(cmd)-1] = 0;
        //是"end"命令结束客户端与服务器通信
        if(strncmp(cmd,"end",3) == 0)
        {
            close(socketfd);
            break;
        }
        //对于服务器目录操作的指令集，指令集在目录"\bin\"下
        if(strncmp(cmd,"ls",2) == 0 ||
                strncmp(cmd, "cd", 2) == 0 ||
                strncmp(cmd, "pwd", 3) == 0)
        {
            Ser_Val val;
            val.type = CMD;
            strcpy(val.data,cmd);
            //将用户输入的指令进行封装，与服务器进行匹配
            send(socketfd,&val,strlen(cmd)+sizeof(Ser_Type),0);
            //循环接收服务器发送过来的关于目录文件的信息
            while(1)
            {
                char buff[128] = {0};
                recv(socketfd,buff,127,0);
                if(strncmp(buff+strlen(buff)-3,"###",3) == 0)
                {
                    //对发送过来的数据进行标记检查
                    int i = 0;
                    for(;i<3;++i)
                    {
                        buff[strlen(buff)-1] = 0;
                    }
                    printf("%s\n",buff);
                    break;
                }
                printf("%s\n",buff);
            }
        }
        //用户输入与下载指令相匹配
        else if(strncmp(cmd,"down",4) == 0)
        {
            //指令封装
            Ser_Val val;
            val.type = DOWN;
            char *filename = strtok(cmd, " ");
            filename = strtok(NULL," ");
            if(filename == NULL)
            {
                printf("请重新输入\n");
                continue;
            }
            //由于实现下载功能，所以必须在本地创建一个文件用来接收文件内容
            int fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC,0664);
            if(fd == -1)
            {
                printf("open %s fail\n",filename);
                continue;
            }

            strcpy(val.data,filename);
            send(socketfd,&val,sizeof(val.type)+strlen(filename),0);

            char buff[128] = {0};
            recv(socketfd,buff,127,0);
            if(strncmp(buff,"ERROR\n###",9) == 0)
            {
                printf("ERROR\n");
                continue;
            }
            //继续对标记能容进行切割，把标记内容替换成'\0'
            char *stat = strtok(buff,"###");
            if(stat == NULL)
            {
                printf("ERROR\n");
                continue;
            }
            int size = 0;
            int count = 0;
            //把发送过来的文件信息提取出来
            sscanf(stat,"%d",&size);
            stat = strtok(NULL,"\0");

            stat += 2;
            count = strlen(stat);
            //连包问题的处理
            write(fd,stat,count);
            printf("\033[?25I");//隐藏光标

            while(1)
            {
                //对于下载的进度的模拟显示
                double sum = count* 1.0/size;
                fflush(stdout);
                //由于数据过于少，需模拟进度条，所以睡眠1秒
                sleep(1);
                memset(buff,0,128);
                int n = recv(socketfd,buff,127,0);
                count += n;
                write(fd,buff,n);
                printf("\033[10D\033[K");//光标左移n位并删除光标到行尾的内容
                //文件下载的总大小和发送过来的文件信息相匹配则下载完成
                if(count == size)
                {
                    close(fd);
                    break;
                }
            }
            printf("100.00%,The File finsh Down\n");
            printf("\033[?25h");//显示光标
        }
        //实现命令的客户端向服务器上传文件的功能实现
        else if(strncmp(cmd,"up",2) == 0)
        {
            Ser_Val val;
            val.type = UP;
            char *p = strtok(cmd," ");
            p = strtok(NULL," ");
            if(p == NULL)
            {
                printf("ERROR\n");
                continue;
            }
            strcpy(val.data,p);
            //必须加标记，不然会出现连包问题
            strcat(val.data,"###");
            send(socketfd,&val,strlen(val.data)+sizeof(val.type),0);
            int fr = open(p,O_RDONLY);
            if(fr == -1)
            {
                printf("ERROR\n");
                continue;
            }

            //获取本地的文件信息，进行进度条的实现
            struct stat st;
            fstat(fr,&st);
            int size = st.st_size;
            int count = 0;
            printf("\033[?25I");
            while(1)
            {
                //这里的实现功能思路与down类似
                char buff[128] = {0};
                read(fr,buff,127);
                send(socketfd,buff,strlen(buff),0);
                count += strlen(buff);
                printf("%0.2f%%",count*1.0/size *100);
                fflush(stdout);
                sleep(1);
                printf("\033[128D\033[K");;
                if(count == size)
                {
                    close(fr);
                    break;
                }
            }
            send(socketfd,"###",3,0);
            printf("100.00%,The File finish Up\n");
            printf("\033[?25h");
        }

        //输入命令不属于指令菜单，则给客户报出一个异常
        else
        {
            printf("非标准输入，请重新输入\n");
        }
    }
}
