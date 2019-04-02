#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h> 

int main(int argc, char **argv) 
{ 
	if (argc != 3) 
	{ 
		printf("Usage: %s $SUM $RATE\n", argv[0]); 
		exit(1); 
	} 

	struct sockaddr_in server_addr; 
	memset(&server_addr, 0, sizeof(server_addr)); 
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server_addr.sin_port = htons(4020); 
	int fd = socket(AF_INET, SOCK_DGRAM, 0); 
	if (fd < 0) 
	{ 
		printf("create socket failed: %s\n", strerror(errno)); 
		exit(2); 
	} 

	struct timeval start; 
	gettimeofday(&start, NULL); 
	unsigned long ustart = start.tv_sec*1000000 + start.tv_usec; 
	usleep(1); 

	struct timeval now; 
	memset(&now, 0, sizeof(struct timeval)); 
	unsigned long unow = 0; 
	int totalUdp = atoi(argv[1]);	//total send msg number
	int maxRate = atoi(argv[2]); 	//send msg number per second

	// caps 
	printf("totalUdp: %d\n", totalUdp);
 	printf("maxRate: %d\n", maxRate); 
 	int sum = 0; 		  
 	double rate = 0.0;    
 	char buff[1024*16] = ""; 
 	while (sum < totalUdp) 
 	{ 
 		gettimeofday(&now, NULL); 
 		unow = now.tv_sec*1000000 + now.tv_usec; 
 		rate = sum/(unow - ustart + 0.0); 
 	
 		if (maxRate > 0 && rate * 1000000 > maxRate) 
 		{ 
 			usleep(1000); // sleep 0.001 second 
 			continue; 
 		} 
 		sprintf(buff, "%ld %ld %d\n", now.tv_sec, now.tv_usec, sum); 
 		int res = sendto(fd, buff, strlen(buff), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
 		if (res < 0) 
 		{ 
 			printf("sendto error: %s\n", strerror(errno)); 
 			exit(3); 
 		} 
 		
 		sum ++; 
 	}	 
 	close(fd); 
 	printf("finish %d in %.3f, rate: %.f\n", sum, (unow-ustart+0.0)/1000000, rate*1000000); 
 	exit(0); 
}
