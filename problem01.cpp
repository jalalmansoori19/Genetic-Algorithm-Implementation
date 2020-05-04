/*
#include <iostream>
#include <math.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <bitset> 
*/
#include <bits/stdc++.h>
#define SIZE 6

using namespace std;

int gene1[SIZE];//={2, 4, 6, 8, 10, 12};
int gene2[SIZE];//={1, 3, 5, 7, 9, 11};
	
int getPredictedValueForGene(int gene[], int x);

int getBadnessValue(int y1, int y2, int predy1, int predy2);
string generateBinary(int gene[]);
string generateNewGene(string binary, int r);
void display(int gene[]);
void assignRandomNumtoGenes();
void printBinary(string binary);

int main()
{
	assignRandomNumtoGenes();
	// 2 Data Points
	int x1=1, x2=3, y1=2, y2=4;
	long long int pred_y1=0, pred_y2=0;
	long long int badness_1=0, badness_2=0;	
	
	cout<<"Genetic Algorithm by using mutation\n"<<endl;
	
	
	for(int i=0; i<60; i++)
	{
		//Badness For Gene1
		pred_y1= getPredictedValueForGene( gene1, x1); // For x1=1
		pred_y2= getPredictedValueForGene( gene1, x2); // For x2=3
		badness_1=getBadnessValue( y1, y2,  pred_y1,  pred_y2);
		
		cout<<"Iteration "<<i+1<<"\n\n";
		
		cout<<"Badness Value for Gene1 ";
		display( gene1);
		cout<<": "<<badness_1<<endl;
		
		//Badness For Gene2
		pred_y1= getPredictedValueForGene( gene2, x1); // For x1=1
		pred_y2= getPredictedValueForGene( gene2, x2); // For x2=3
		badness_2=getBadnessValue( y1, y2,  pred_y1,  pred_y2);
		
		cout<<"Badness Value for Gene2 ";
		display( gene2);
		cout<<": "<<badness_2<<endl;
		
		
		// For Solution if badness =0
		if(badness_2 == 0)
		{
			cout<<"Solution is Gene2 ";
			display( gene2);
			cout<<endl;
			break;
		}
		else if(badness_1 == 0)
		{
			cout<<"Solution is Gene1 ";
			display( gene1);
			cout<<endl;
			break;
		}
		
		//For Binary and mutation
		if(badness_2 <= badness_1)
		{
			int r=0;
    		//srand(time(0));  // Initialize random number generator.
   	
   			r = (rand() % 24) ;
    		
    		//Binary
			string binary=generateBinary(gene2);
			printBinary(binary);
			//Mutation
			cout<<"\nAfter Mutation and random number to toggle "<<r<<endl;
			
			string newbinaryGene= generateNewGene(binary, r-1);
			printBinary(newbinaryGene);
			
			cout<<"\nNew Gene { ";
			int start=0;
			string str="";
			for(int i=0; i<SIZE; i++)
			{
				str=newbinaryGene.substr(start,4);
				start=start+4;
				unsigned long decimal =bitset<4>(str).to_ulong();
				gene1[i]= decimal;
				cout<<gene1[i]<<" ";
			}	
			
			cout<<"}"<<endl;
					
		}
		else // if badness_1<badness2 
		{
			int r=0;
    		//srand(time(0));  // Initialize random number generator.
   	
   			r = (rand() % 24) ;
    		
    		//Binary
			string binary=generateBinary(gene1);
			printBinary(binary);
			//Mutation
			cout<<"\nAfter Mutation and random number to toggle "<<r<<endl;
			
			string newbinaryGene= generateNewGene(binary, r-1);
			printBinary(newbinaryGene);
			
			cout<<"\nNew Gene { ";
			int start=0;
			string str="";
			for(int i=0; i<SIZE; i++)
			{
				str=newbinaryGene.substr(start,4);
				start=start+4;
				unsigned long decimal =bitset<4>(str).to_ulong();
				gene2[i]= decimal;
				cout<<gene2[i]<<" ";
			}	
			
			cout<<"}"<<endl;
		}
				
		cout<<"\n";		
	}
		
	
	cout<<"Solution is : Gene ";
	 display(gene2);
	
		
	return 0;
}

int getPredictedValueForGene(int gene[], int x)
{
	int ans=0, index=0;
	
	for(int i=5; i>=1; i--)
	{
		ans= ans + ( gene[index] * pow(x , i)) ;
		index++;
	}
	
	ans=ans+gene[5];
	return (ans);
}

int getBadnessValue(int y1, int y2, int predy1, int predy2)
{
	int ans=0;
	
	ans= pow(y1 - predy1, 2) + pow(y2 - predy2, 2) ;
	
	return (ans);
}

string generateBinary(int gene[])
{
	string binary="";
	for(int i=0; i<SIZE; i++)
	{
		//string binary = bitset<4>(15).to_string(); //to binary
		binary=binary + bitset<4>(gene[i]).to_string(); // 4 bit binary
	}
	
	return binary;
}

string generateNewGene(string binary, int r)
{
	
    if(binary[r]== '1')
    {
    	binary[r]= '0';
	}
	else if(binary[r]== '0')
	{
		binary[r]= '1';
	}
	
	return (binary);
	
}

void printBinary(string binary)
{
	int start=0;
	
	cout<<"\n\n{ ";
	
	for(int i=0; i<6; i++)
	{
		cout<<binary.substr(start,4)<<" ";
		start=start+4;
	}
	
	cout<<" }"<<endl;
	
}

void display(int gene[])
{
	cout<<"{ ";
	for(int i=0; i<SIZE; i++)
	{
		cout<<gene[i]<<" ";
	}
	
	cout<<" }\t";
}

void assignRandomNumtoGenes()
{
	int r=0;
	
	for(int i=0; i<SIZE; i++)
	{
		r = (rand() % 5) +1;
		gene1[i]=r;
		
		r = (rand() % 3) +1;
		gene2[i]=r; 
	}
}
