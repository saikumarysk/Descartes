#include<stdio.h>
int main()
{
	int i,j,k,t;
	int sbox[64]={15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,11,7,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,5,0,14,9};// The sbox proposed
	int x[64],x1[64],x2[64];//x is the input difference, x', x1 is x and x2 is x*
	int y[64],y1[64],y2[64];//y is the output difference, y', y1 is y and y2 is y*
	int table[64][16]={0};// The differential table
	for(i=0;i<64;i++)
	{
		//Computing all possible values for x and x*
		x1[i]=i;
		x2[i]=i;
	}
	for(t=0;t<64;t++)
	{
		for(j=0;j<64;j++)
		{
			x[j]=x1[j]^x2[t];//Computing all possible input differences 
			y1[j]=sbox[x1[j]];
			y2[j]=sbox[x[j]];
			y[j]=y1[j]^y2[j];// The corresponding output differences
			table[t][y[j]]++;// Updating the table
		}
	}
	// The cliche printing of 2d array
	printf("    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
	printf("   ------------------------------------------------\n");
	for(t=0;t<64;t++)
	{
		printf("%2d|",t);
		for(j=0;j<16;j++)
		{
			printf("%2d",table[t][j]);
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}