#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
    char c;
    int in, out;

    in = open("/home/zjw/work/experiment/linux_c/file.in", O_RDONLY);
    out = open("/home/zjw/work/experiment/linux_c/file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    while(read(in,&c,1) == 1)
        write(out,&c,1);

    exit(0);
}
