#include <stdio.h>
#include <string.h>

#define AATEST "/mnt/qcflash/"
#define AATEST_prefix AATEST "cpeimage_"

char* init()
{
	//char tmp[100];
	//strcpy(tmp, pchar);
	unsigned short li=1;
	static char buf[100];
	sprintf(buf, "%s%d", AATEST_prefix, li);
	return buf;
}

int main()
{
	//unsigned short li=1;
	//char buf[100];
	//sprintf(buf, "%s%d", AATEST, li);
	printf("init buffer is %s\n", init()); 

	//init(buf);

	//printf("init buffer ok\n"); 
	return 0;
}
