#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;

double eval(int *pj){
       int arr[100];
       bool flag = true;
       srand((unsigned)time(0)); 
       for(int i=0; i<100; i++){ 
        arr[i] = rand()%2;
       }
       for(int i=0; i<100; i++)
	{
		for(int j=0; j<100; j++)
		{
			if(pj[i] == arr[j])
			{
				
			}

			else
			{
				flag = false;
			}
			break;
		}
		break;
	}
        if (flag == true){
            return 100;
         }
        else{
             return rand()%99;  
            }
};


