#include <bits/stdc++.h> 
#define SIZE 6

using namespace std;

int gene1[SIZE];//={2, 4, 6, 8, 10, 12};
int gene2[SIZE];//={1, 3, 5, 7, 9, 11};
int gene3[SIZE];//={3, 7, 11,15, 13, 5 };

void assignRandomNumtoGenes();	
int getPredictedValueForGene(int gene[], int x);

int getBadnessValue(int y1, int y2, int predy1, int predy2);
string generateBinary(int gene[]);
string generateNewGene(string binary, int r);
void display(int gene[]);

int getMinimum(int value1, int value2);
void printBinary(string binary);

int *getGene(int lowValue, int badness_1, int badness_2, int badness_3);

string getC(string binaryA, string binaryB);
string getD(string binaryA, string binaryB);


int main()
{
	int size=3;
	long long int array[size];
	int *geneA;
	int *geneB;
		
	// 2 Data Points
	int x1=1, x2=3, y1=2, y2=4;
	long long int pred_y1=0, pred_y2=0;
	long long int badness_1=0, badness_2=0, badness_3=0;	
	long long int lowValue1=0, lowValue2=0;
	
	assignRandomNumtoGenes();
	
	cout<<"Genetic Algorithm by using Crossover\n"<<endl;
	
	
	for(int i=0; i<100; i++)
	{
		//Badness For Gene1
		pred_y1= getPredictedValueForGene( gene1, x1); // For x1=1
		pred_y2= getPredictedValueForGene( gene1, x2); // For x2=3
		badness_1=getBadnessValue( y1, y2,  pred_y1,  pred_y2);
		array[0]=badness_1;
		cout<<"Iteration "<<i+1<<"\n\n";
		
		cout<<"Badness Value for Gene1 ";
		display( gene1);
		cout<<": "<<badness_1<<endl;
		
		//Badness For Gene2
		pred_y1= getPredictedValueForGene( gene2, x1); // For x1=1
		pred_y2= getPredictedValueForGene( gene2, x2); // For x2=3
		badness_2=getBadnessValue( y1, y2,  pred_y1,  pred_y2);
		array[1]=badness_2;
		
		cout<<"Badness Value for Gene2 ";
		display( gene2);
		cout<<": "<<badness_2<<endl;
		
		//Badness For Gene3
		pred_y1= getPredictedValueForGene( gene3, x1); // For x1=1
		pred_y2= getPredictedValueForGene( gene3, x2); // For x2=3
		badness_3=getBadnessValue( y1, y2,  pred_y1,  pred_y2);
		array[2]=badness_3;
		
		cout<<"Badness Value for Gene3 ";
		display( gene3);
		cout<<": "<<badness_3<<endl;
		
			
		//Sort function 
		sort(array, array+size );
		
		//Two minimum badness value
		lowValue1= array[0]; 
		lowValue2= array[1];
		
		geneA= getGene(lowValue1,  badness_1,  badness_2,  badness_3);
		geneB= getGene(lowValue2,  badness_1,  badness_2,  badness_3);
		
		cout<<"LowValue1 : "<<lowValue1<<endl;
		display( geneA);
		cout<<"\nLowValue2 : "<<lowValue2<<endl;
		display( geneB);
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
		else if(badness_3 == 0)
		{
			cout<<"Solution is Gene3 ";
			display( gene3);
			cout<<endl;
			break;
		}
		
		//Binary Representation
		
		cout<<"\n\nGene A and B Binary "<<endl;
		string binaryA=generateBinary(geneA);
		printBinary(binaryA);
		
		string binaryB=generateBinary(geneB);
		printBinary(binaryB);
		
		cout<<"After CrossOver\n";
		cout<<"GeneC"<<endl;
		string binaryC=getC( binaryA,  binaryB);
		printBinary(binaryC);		
		
		cout<<"GeneD"<<endl;
		string binaryD=getD( binaryA,  binaryB);
		printBinary(binaryD);		
		
		cout<<"\nNew GeneC { ";
			int start=0;
			string str="";
			for(int i=0; i<SIZE; i++)
			{
				str=binaryC.substr(start,4);
				start=start+4;
				unsigned long decimal =bitset<4>(str).to_ulong();
				gene1[i]= decimal;
				cout<<gene1[i]<<" ";
			}	
			
			cout<<"}"<<endl;		
		
			cout<<"\nNew GeneD { ";
			int start1=0;
			string str1="";
			for(int i=0; i<SIZE; i++)
			{
				str1=binaryD.substr(start1,4);
				start1=start1+4;
				unsigned long decimal =bitset<4>(str1).to_ulong();
				gene2[i]= decimal;
				cout<<gene2[i]<<" ";
			}	
			
			cout<<"}"<<endl;
			
			int r=0;
			
			//FOR GENE3
			for(int i=0; i<SIZE; i++)
			{
				r = (rand() % 4) ;
				gene3[i]=r; 
				
			}
			
	}
		
	
		
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

int getMinimum(int value1, int value2)
{
	if(value1 < value2)
	{
		return value1;
	}
	return value2;
}

int *getGene(int lowValue, int badness_1, int badness_2, int badness_3)
{
	if(lowValue == badness_1)
	{
		return (gene1);
	}
	else if(lowValue == badness_2)
	{
		return (gene2);
	}
	else if(lowValue == badness_3)
	{
		return (gene3);
	}
}

string getC(string binaryA, string binaryB)
{
	string result="";
	
	result=binaryA.substr(0, 12) + binaryB.substr(12, 12);
	
	return result;

}

string getD(string binaryA, string binaryB)
{
	string result="";
	
	result=binaryB.substr(0, 12) + binaryA.substr(12, 12);
	
	return result;

}

void assignRandomNumtoGenes()
{
	int r=0;
	
	for(int i=0; i<SIZE; i++)
	{
		r = (rand() % 4 ) +1;
		gene1[i]=r;
		
		r = (rand() % 1) +1;
		gene2[i]=r;
				
		
		r = (rand() % 2)+1 ;
		gene3[i]=r;
		 
	}
}
