#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>

const char* filename = "mytest.tar.gz";
//const char* filename = "mytest.txt";
const int splitsize = 8192;

int main()
{
	//open source file
	int fd_src = open(filename, O_RDONLY, S_IRWXU);
    if(fd_src<0)
    {
    	printf("failed to open source file %d!\n", fd_src); 
    	return fd_src;
    }		

    int fd_tgt;
    int readlen;
    int fileIndex=1;
    unsigned char file_buffer[10000];

    while(1)
    {
    	readlen = read(fd_src, file_buffer, splitsize);
    	if(readlen == -1)  
       	{  
           printf("File read error!\n");  
           return -1;  
       	}  
       else if(readlen == 0)  
       {  
           printf("File read Over!\n");  
           break;  
       }  
       else   
       {  
           printf("Read %d Byte From source file: ", readlen);  
           /*for(int i = 0; i < readlen; i++)  
           {  
                printf(" %02x",file_buffer[i]);  
           }  
           printf("\n");*/

           char l_filename[100];
           sprintf(l_filename, "%s%d", "mysplit_", fileIndex);

           fd_tgt = open(l_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    	   if(fd_tgt<0)
    	   {
    	   		printf("failed to open target file!\n"); 
    			return fd_tgt;
    	   }     

    	   int writelen;
    	   if(readlen<splitsize) 
    	   		writelen = readlen; 
    	   else
    	   		writelen = splitsize;

    	   write(fd_tgt, file_buffer, writelen); 
    	   close(fd_tgt);
    	   fileIndex++;
       }  
    }

	printf("successful to split files!\n"); 
	return 0;
}