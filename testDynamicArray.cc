#include <stdio.h>
#include <iostream>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <typename T, size_t N>
inline size_t Count(  T ( & arr )[N] ) {
    return N;
}

int main()
{
    int i1[]={1,2};
    int i2[]={3,4};
    int i3[]={5,6};
    const char *char_arrays[] = {"aaa","bbb","ccc"};
    int *int_arrays[] = {i1,i2,i3};
    
    string str1 = "hello";
    string str2 = "world";
    string str3 ="hi";
    string str_array[3] = {str1,str2,str3}; 

    cout << "char array size is: " << sizeof(char_arrays)/sizeof(*char_arrays) << endl;
    cout << "int array size is: " << sizeof(int_arrays)/sizeof(*int_arrays) << endl;
    
    for(const auto& n : char_arrays) {
        //cout << "type of n is " << typeid(n).name() << endl;
        std::cout << n << '\n';
    }

    for(const auto& n : int_arrays) {
        //cout << "type of n is " << typeid(n).name() << endl;
	//cout << "size of n is " << sizeof(n)/sizeof(*n) << endl;
        std::cout << n[0] << "," << n[1] << '\n';
    }

    cout << "template deduction length is " << Count(char_arrays) << endl;
    cout << "template deduction length is " << Count(i1) << endl;
    return 0;
}
