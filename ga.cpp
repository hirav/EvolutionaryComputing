#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
 
using namespace std;

 
#define CROSSOVER_RATE            0.7
#define MUTATION_RATE             0.001
#define POP_SIZE                  100           
#define LENGTH                    150
#define MAX_GENERATIONS           20000000
 
 
//  Defined a data structure for type

struct type
{
    string    bits; 
    double    fitness;
 
    type(): bits(""), fitness(0.0){};
    type(string bts, double ftns): bits(bts), fitness(ftns){}
};
 
 
//      Function defination         
 
string  InitializePop(int length);
double  GetFitness(string bits);
void    PrintBits(string bits);
string  Roulette(int total_fitness, type* Population);
void    Mutate(string &bits);
void    Crossover(string &child1, string &child2);
double  eval(int *pj);

// main 

int main()
{
    // Seed for rand
    srand((int)time(NULL));
 
    type Population[POP_SIZE];
    type globalmax;
    type localmax;

    cout << endl << endl;

      // Initializing Parent population.
      for (int i=0; i<POP_SIZE; i++)
      {
          Population[i].bits      = InitializePop(LENGTH);
          Population[i].fitness = 0.0;
      }
      // Initializing global max
      for (int i=0; i<POP_SIZE; i++)
          {
             globalmax.bits      = InitializePop(LENGTH);
             globalmax.fitness = 0.0;
          }
      
       int GenerationCount = 0;
      //GA loop
      while(true)
      {
          double TotalFitness = 0.0;
          for (int i=0; i<POP_SIZE; i++)
          {
             localmax.bits      = InitializePop(LENGTH);
             localmax.fitness = 0.0;
          }

          // Check the fitness of this population and update Local max 
          for (int i=0; i<POP_SIZE; i++)
          {
              Population[i].fitness = GetFitness(Population[i].bits);
              if(localmax.fitness < Population[i].fitness){
		  localmax = type(Population[i].bits, Population[i].fitness);   
		 // cout<<"Current chromosome ="<<Population[i].fitness <<endl;
                  //cout<<"Local maximum ="<<localmax.fitness <<endl;
                 // PrintBits(localmax.bits);
	     }
              TotalFitness += Population[i].fitness;
          }
          
          // Check the local max fitness and update global max 
          if(globalmax.fitness <= localmax.fitness){
		globalmax = type(localmax.bits, localmax.fitness);   
		cout<<"Global maximum ="<< globalmax.fitness <<endl;
                PrintBits(globalmax.bits);
	     }
          
           
          //Temporary array of individuals for storing children
          type temp[POP_SIZE];
 
          int cPop = 0;
       
          //Creating Population sized children
          while (cPop < POP_SIZE)
          {
              string child1 = Roulette(TotalFitness, Population);
              string child2 = Roulette(TotalFitness, Population);
 
              //Do crossover
              Crossover(child1, child2);
 
              //mutate
              Mutate(child1);
              Mutate(child2);
 
              //Storing children in temp array
              temp[cPop++] = type(child1, 0.0);
              temp[cPop++] = type(child2, 0.0);
 
          }//end loop
 
          //Make children new parents
          for (int i=0; i<POP_SIZE; i++)
      	  {
              Population[i] = temp[i];
          }
 
          ++GenerationCount;
 
          // exit within the maximum allowable generations and return Global max
          
          if (GenerationCount > MAX_GENERATIONS)
          {
              cout << "Solution found is"<<endl;
              cout<<"Global maximum ="<< globalmax.fitness <<endl;
              PrintBits(globalmax.bits);
              return 0;
          }
 
      }
  
    return 0;
}
         
 
 
 

//  This function initializes parent population with random bits

string  InitializePop(int length)
{
    string bits;
   
    double randomNum;
    for (int i=0; i<length; i++)
    {
 	randomNum  = ((double)rand()/(RAND_MAX));
        if (randomNum > 0.5)
 
            bits += "1";
 
        else
 
            bits += "0";
    }
 
    return bits;
}
 
    

//  This function converts string to integer array and returns fitness from eval

double GetFitness(string bits)
{
    //cout<<"String = "<<bits<<endl;
    int buffer[LENGTH];
    double tempfitness;
    //cout<< "Array  =";
    std::transform( bits.begin(), bits.end(), buffer,[]( char c ) -> int { return ( c - '0' ); } );
   // cout<<endl;
    tempfitness = eval(buffer);
    //cout<<"Fitness = "<<tempfitness<<endl;
    return tempfitness;
    //  return result;
}
 

// prints bits of individual to screen

void PrintBits(string bits)
{  
    cout<< "Individual = "<<bits <<endl;
 
    return;
}
     


//  Mutates based on the MUTATION_RATE

void Mutate(string &bits)
{
    double randomNum;
    for (int i=0; i<bits.length(); i++)
    {
	randomNum  = ((double)rand()/(RAND_MAX));
        if (randomNum < MUTATION_RATE)
        {
            if (bits.at(i) == '1')
 
                bits.at(i) = '0';
 
            else
 
                bits.at(i) = '1';
        }
    }
 
    return;
}
 

//  Do crossover between parent based on crossover probability

void Crossover(string &child1, string &child2)
{
  double randomNum = ((double)rand()/(RAND_MAX));
  //cout<<"Entering crossover func"<<endl;
  //dependent on the crossover rate
  if (randomNum < CROSSOVER_RATE)
  {
    //create a random crossover point
    int crossover = (int) (randomNum * LENGTH);
    string t1 = child1.substr(0, crossover) + child2.substr(crossover, LENGTH);
    string t2 = child2.substr(0, crossover) + child1.substr(crossover, LENGTH);
 
    child1 = t1; child2 = t2;                
  }
  //cout<<"Exiting crossover func"<<endl;
}
 
 
// Roulette wheel selection

string Roulette(int total_fitness, type* Population)
{
    double randomNum = ((double)rand()/(RAND_MAX));
    //generate a random number between 0 & total fitness count
    double Slice = (double)(randomNum * total_fitness);
   //  cout << "Slice" << Slice<<endl;
    //go through the chromosones adding up the fitness so far
    double FitnessSoFar = 0.0;
     
    for (int i=0; i<POP_SIZE; i++)
    {
        FitnessSoFar += Population[i].fitness;
         //cout << "FitnessSoFar" << FitnessSoFar<<endl;
        //if the fitness so far > random number return the chromo at this point
        if (FitnessSoFar >= Slice)
 
            return Population[i].bits;
    }
 
    return "";
}
