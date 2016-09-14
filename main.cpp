#include <iostream>
#include<math.h>
using namespace std;

double eval(int *pj);

int main()
{
  int vec[100],curr[100],next[100],destvec[100];
  unsigned long int i;
  double currfit,nextfit;
  bool flag = false;
  int bit = 100;
  unsigned long int fspeed = 0;
  unsigned long int fspeedmax = 30;
  unsigned long int loop;

  //Initialize the starting point to all 0's
  for(i = 0; i < 100; i++)
  {
    vec[i] = 0;
  }
  for(i = 0; i < 100; i++)
  {
    destvec[i] = 1;
  }
  currfit = eval(vec);
  if(currfit == 100)
  {
    for(i = 0; i < 100; i++)
    {
      cout<<vec[i];
    }
    return 0;
  }
  std::copy ( vec, vec+100, curr );

  
  while(!flag)
  {
  //Loop to move forward depending on the fspeed variable
  loop = pow(2.0,fspeed);
  for (i=0; i<= loop; i++)
  {
    //cout<<"loop no"<<i<<endl;
    flag = true;
    while(flag && bit >=0)
    {
      if(vec[bit] == 0)
      {
	  vec[bit] = 1;
	  flag = false;
      }
      else
      {
	  vec[bit] = 0;
      }
      bit--;
    }
    if(flag){
      break;
    }
    bit = 100;
  }
  std::copy ( vec, vec+100, next );
  nextfit = eval(vec);
  cout << "fitness = " << nextfit << endl;
  if(nextfit == 100)
  {
    for(i = 0; i < 100; i++)
    {
      cout<<vec[i];
    }
    return 0;
  }
  if(nextfit> currfit)
  {
	std::copy ( next, next+100, curr );
	currfit = nextfit;
	fspeedmax>= fspeed ? :fspeed++;
  }
  if(nextfit == currfit && currfit < 100)
  {
	std::copy ( next, next+100, curr );
	currfit = nextfit;
  }
  if(nextfit<currfit && currfit < 100 && fspeed >=1)
  {
	fspeed--;
  }
  if(nextfit<currfit && currfit < 100 && fspeed ==0)
  {
	fspeed = 30;
  }
  
  std::copy ( curr, curr+100, vec );
  }
}

