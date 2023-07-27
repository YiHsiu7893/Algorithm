// Ex3 - Dynamic Programming
#include <iostream>
#include <cstdlib>
using namespace std;

int main(void)
{
  int n,m;              	  // n projects and m resources
  cin >> n >> m;
  int profit[n][m+1];   	  // table profit
  int max[n][m+1];      	  // table max

  int i,j,k;
  for(i=0;i<n;i++)      	  // fill in the profit table
    for(j=0;j<=m;j++)
      cin >> profit[i][j];
  
  for(j=0;j<=m;j++)           	  // the first row (i=0), max[0][j]=profit[0][j]
    max[0][j]=profit[0][j];
    
  for(i=1;i<n;i++)            	  // the second row to the last row
    for(j=0;j<=m;j++)         	  // the first column to the last column
    {
      int tmp=-1000;          	  // initialize tmp as a very small number 
    	for(k=0;k<=j;k++)     	  // the new added project with 0~j resources
        {
      	  if(profit[i][k]+max[i-1][j-k]>tmp)
      	    tmp=profit[i][k]+max[i-1][j-k];
	    }
	  max[i][j]=tmp;          // tmp is the maximal profit of 0th~ith projects with j resources now
	}
	
  cout << endl << max[n-1][m];    // 0th~(n-1)th projects with m resources is the answer
  
  return 0;
}
