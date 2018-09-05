#include<unistd.h>
#include<stdlib.h>

int main()
{
    if(( write(1, "experiment\n",10) ) != 10)
            write(2, "write error has occurred on file descriptor 1\n",50);

    exit(0);
}
