#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main()
{
	open ("myfile", O_CREAT, S_IRUSR | S_IXOTH);
	
}
