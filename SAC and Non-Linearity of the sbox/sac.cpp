#include<stdio.h>

int main()
{
	int y1[64] = {1,0,1,1,0,1,0,0,1,0,0,1,1,0,0,1,0,1,0,0,1,0,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1};//The values for y1
	int count1=0,count0=0,i;
	for(i=1;i<=64;i++)
	{
		if((y1[i]+y1[i-1])%2 == 0)
		{
			count0++;//Counting no. of zeros
		}
		else
		{
			count1++;//counting no. of ones
		}
	}
	printf("No. of zeros are %d\n",count0);
	printf("No. of ones are %d\n",count1);
	return 0;
}
