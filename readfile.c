#include <stdio.h>
#include <string.h>

#define MAX_VERSION_SIZE 128
//#define CELLULAR_FILENAME    "/mnt/qc_flash/Download/CellularWanNatPortmapping.txt"
#define CELLULAR_FILENAME       "/home/weixw/code_sample/readfile/readme"
#define CELLULAR_SEPERATE_TAG   ","

int main()
{
    FILE *fp = NULL;
    char l_lineStr[MAX_VERSION_SIZE];
   
    if((fp = fopen(CELLULAR_FILENAME, "r")) == NULL)
    {
    	printf("fail to open cellular router table file.\n");
        return 0;
    }

    while(!feof(fp))
    {
        memset(l_lineStr, 0x00, sizeof(l_lineStr));
        fgets(l_lineStr, sizeof(l_lineStr), fp);
		
		printf("%s", l_lineStr);
        //printf("strlen is : %zd\n", strlen(l_lineStr));
        //printf("sizeof is : %zd\n", sizeof(l_lineStr));

        l_lineStr[strlen(l_lineStr)-1] = '\0';

        char* l_subStr = NULL;
        if(strlen(l_lineStr)>0)
        {
		  l_subStr = strtok(l_lineStr, CELLULAR_SEPERATE_TAG);
		  while(l_subStr!=NULL)
		  {
			printf("%s\n", l_subStr);
			l_subStr = strtok(NULL, CELLULAR_SEPERATE_TAG);
		  }
        }         
    }

    fclose(fp);
}
