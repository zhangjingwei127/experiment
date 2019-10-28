#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

typedef enum
{
    UP,DOWN,CMD
}Ser_Type;

typedef struct value
{
    Ser_Type type;
    char data[128];
}Ser_Val;

void Up_File(int acceptfd,Ser_Val val)
{
    char filename[128] = {0};
    strcpy(filename,val.data);
    //printf("UP == %s\n",filename);
    char *p = strtok(filename,"###");
    char *q = strtok(NULL,"\0");
    int fw = open(p,O_WRONLY|O_CREAT|O_TRUNC,0664);
    //assert(fw != -1);
    if(fw == -1)
    {
        return;
    }
    if(q != NULL)
    {
        q += 2;
        write(fw,q,strlen(q));
    }
    while(1)
    {
        memset(filename,0,128);
        //char buff[128] = {0};
        int n = recv(acceptfd,filename,127,0);
        if(strncmp(filename+strlen(filename)-3,"###",3) == 0)
        {
            close(fw);
            break;
        }
        write(fw,filename,n);
    }
    //printf("UP is finish\n");
}

void Down_File(int acceptfd,Ser_Val val)
{
    char filename[128] = {0};
    strcpy(filename,val.data);
    int fr = open(filename,O_RDONLY);
    if(fr == -1)
    {
        send(acceptfd,"ERROR\n###",9,0);
        return;
    }
    struct stat st;
    fstat(fr,&st);
    char buff[128] = {0};
    sprintf(buff,"%d",st.st_size);
    strcat(buff,"###");
    send(acceptfd,buff,strlen(buff),0);
    while(1)
    {
        memset(buff,0,sizeof(buff));
        int n = read(fr,buff,127);
        if(n <= 0)
        {
            close(fr);
            break;
        }
        send(acceptfd,buff,n,0);
    }
}

void Make_Cmd(int acceptfd,Ser_Val val)
{
    char buff[128] = {0};
    strcpy(buff,val.data);
    char *p = strtok(buff," ");
    char *cmd[10] = {0};
    //printf("cmd[0]:%s p:%s\n",cmd[0],p);
    int i = 0;
    while(p != NULL)
    {
        cmd[i++] = p;
        p = strtok(NULL," ");
    }

    if(strncmp(cmd[0],"cd",2) == 0)
    {
        if(cmd[1] != NULL)
        {
            if(chdir(cmd[1]) != -1)
            {
                send(acceptfd,"seccess5\n###",12,0);
                return;
            }
            send(acceptfd,"ERROR4\n###",10,0);
            return;
        }
        int fds[2];
        pipe(fds);
        pid_t pid = fork();
        assert(pid != -1);

        if(pid == 0)
        {
            close(1);
            close(2);
            close(fds[0]);

            dup(fds[1]);
            
            char path[128] = "/bin/";
            strcat(path,cmd[0]);
            //printf("path == %s\n",path);
            execv(path,cmd);
            send(acceptfd,"ERROR2\n###",10,0);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fds[1]);

            while(1)
            {
                char tmp[128] = {0};
                int n = read(fds[0],tmp,127);
                if(n==0)
                {
                    close(fds[0]);
                    send(acceptfd,"###",3,0);
                    break;
                }
                send(acceptfd,tmp,n,0);
            }
        }
    }
}
    void Deal_client(acceptfd)
    {
        while(1)
        {
            Ser_Val val;
            memset(val.data,0,128);
            int n = recv(acceptfd,&val,sizeof(val)-1,0);
            //printf("Deal == %s\n",val.data);
            if(val.type == UP)
            {
                //printf("i am UP\n");
            }
            if(n == 0)
            {
                close(acceptfd);
                break;
            }

            switch(val.type)
            {
                case UP:
                    Up_File(acceptfd,val);
                    break;
                case DOWN:
                    Down_File(acceptfd,val);
                    break;
                case CMD:
                    Make_Cmd(acceptfd,val);
                    break;
                default:
                    send(acceptfd,"ERROR1#",6,0);
            }
        }
    }
    
    void main()
    {
        int socketfd = socket(AF_INET,SOCK_STREAM,0);
        assert(socketfd != -1);
        struct sockaddr_in ser,cli;
        memset(&ser,0,sizeof(ser));
        ser.sin_family = AF_INET;
        ser.sin_addr.s_addr = inet_addr("127.0.0.1");
        int bindfd = bind(socketfd,(struct sockaddr*)&ser,sizeof(ser));
        assert(bindfd != -1);

        int listenfd = listen(socketfd,5);
        assert(listenfd != -1);

        while(1)
        {
            int len = sizeof(cli);
            int acceptfd = accept(socketfd,(struct sockaddr*)&cli,&len);
            assert(acceptfd != -1);

            Deal_client(acceptfd);
        }
    }



