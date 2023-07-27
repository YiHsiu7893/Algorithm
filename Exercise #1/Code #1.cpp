// Ex1 - Divide and Conquer.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#define MAX_N 10000
using namespace std;

// function Find_Fake()
int Find_Fake(int n, int start, int* arr, int length)  
{
	/* n= number of coins in this group ; s= the start coin
	   arr= array of coin weights ;	length= length of arr*/
	// case1: n=1
	if(n==1) return start;
	
	// case2: n=2
	if(n==2)
	{
		int cg=(start+2)%length;	       // choose the next coin(a real one) as the control group
		if(arr[start]!=arr[cg]) return start;  // start is fake
		else return start+1;		       // start+1 is fake
	}
	
	// case3: n>=3
  	int A,B,C;                     		       // divide into 3 groups, A, B, C, evenly
  	A=B=C=0;
  	int k=n/3;				       // A, B, C are in size k, there may be one or two coins left
  	
  	int i;
  	for(i=start;i<start+k;i++)                     // Group A
	  A+=arr[i]; 
  	for(i=start+k;i<start+2*k;i++)                 // Group B
	  B+=arr[i];   
  	for(i=start+2*k;i<start+3*k;i++)               // Group C 
	  C+=arr[i]; 
	// recursive  
	if(A==B && B==C)					   // fake coin is not in A, B, C
	{
	  if(n%3==2) return Find_Fake(2, start+3*k, arr, length);  // last two coins
	  else return start+3*k;				   // last coin
	}
	if(A==B) return Find_Fake(k, start+2*k, arr, length);      // fake coin is in C
	else if(A==C) return Find_Fake(k, start+k, arr, length);   // fake coin is in B
	else return Find_Fake(k, start, arr, length);              // fake coin is in A
}

int main(void)
{
  int n, t, i;              				// n= number of coins ; t= the index of the fake coin
  int *Arr;                 				// Arr= array storing the weights of the coins

  while(cin >> n && !cin.eof() )  			// n coins in this testing data
  {
  	Arr=(int*) malloc(sizeof(int)*n);          	// arrange a space for Arr
  	
	for(i=0;i<n;i++)
	  cin >> Arr[i];
	  
  	t=Find_Fake(n, 0, Arr, n);           	   	// call the divide-and-conquer function
  	cout << t << endl;       		  
  	
  	free(Arr);                		        // free the space
  }
  
  return 0;
}
