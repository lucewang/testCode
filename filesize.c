#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/statfs.h>

const char* disk = "/repo";
const int splitsize = 8192;

int main()
{
	struct statfs diskInfo;

    statfs(disk, &diskInfo);
    unsigned long free = diskInfo.f_bfree * diskInfo.f_bsize;

    printf("f_bsize = %ld\n", diskInfo.f_bsize); 
	printf("f_bfree*f_bsize = %ld\n", free); 

	free = diskInfo.f_bavail * diskInfo.f_bsize;
	printf("f_bavail*f_bsize = %ld\n", free); 

	return 0;
}