#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
int num = 0x12345678;
unsigned char* pc = (unsigned char*)(&num);
cout <<"local order"<<endl;
cout << "pc[0]=" << hex << int((unsigned char)pc[0]) << endl;
cout << "pc[1]=" << hex << int((unsigned char)pc[1]) << endl;
cout << "pc[2]=" << hex << int((unsigned char)pc[2]) << endl;
cout << "pc[3]=" << hex << int((unsigned char)pc[3]) << endl;

unsigned char testa[4]= {1,1,0,0};

cout<<"testa[0]="<<(int)(unsigned char)testa[0]<<endl;
cout<<"testa[1]="<<(int)(unsigned char)testa[1]<<endl;
cout<<"testa[2]="<<(int)(unsigned char)testa[2]<<endl;
cout<<"testa[3]="<<(int)(unsigned char)testa[3]<<endl;
void* l_tmp = &testa[0];
int teid = *(static_cast<int*>(l_tmp));
cout<<"teid="<<teid<<endl;

char testarray[127] = "hello world";
string teststr;

       teststr = string(testarray); 
       cout << "the string is:" << teststr << endl;

	return 0;
}
