#include<stdio.h>

int main()
{
	int sbox4[64]= {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
	int x1[64],x2[64],x3[64],x4[64],x5[64],x6[64],y1[64],y2[64],y3[64],y4[64],out[64],table[1024];
	int i,j,k,matrix[64][16];
	int b[2][64]={0};
	char str[16];
	FILE *fp;
	fp= fopen("lin_approx_table_4.txt","w");
	for(i=0;i<64;i++)
	{
		if(i%2==0)
		{
			x6[i]=0;
		}
		else
		{
			x6[i]=1;
		}
		if((i/2)%2==0)
		{
			x5[i]=0;
		}
		else
		{
			x5[i]=1;
		}
		if((i/4)%2==0)
		{
			x4[i]=0;
		}
		else
		{
			x4[i]=1;
		}
		if((i/8)%2==0)
		{
			x3[i]=0;
		}
		else
		{
			x3[i]=1;
		}
		if((i/16)%2==0)
		{
			x2[i]=0;
		}
		else
		{
			x2[i]=1;
		}
		if((i/32)%2==0)
		{
			x1[i]=0;
		}
		else
		{
			x1[i]=1;
		}
		y1[i]=(sbox4[i]/8)%2;
		y2[i]=(sbox4[i]/4)%2;
		y3[i]=(sbox4[i]/2)%2;
		y4[i]=(sbox4[i])%2;
	}
	for(i=0;i<1024;i++)
	{
		k=0;
		for(j=0;j<64;j++)
		{
			out[j]=(((i/512)%2)*y1[j])^(((i/256)%2)*y2[j])^(((i/128)%2)*y3[j])^(((i/64)%2)*y4[j])^(((i/32)%2)*x1[j])^(((i/16)%2)*x2[j])^(((i/8)%2)*x3[j])^(((i/4)%2)*x4[j])^(((i/2)%2)*x5[j])^((i%2)*x6[j]);
			if(out[j]==0)
			{
				k=k+1;
			}
		}
		table[i]=k;
	}
	for(i=0;i<16;i++)
	{
		for(j=0;j<64;j++)
		{
			matrix[j][i]=table[64*i+j];
		}
	}
	for(i=0;i<64;i++)
	{
		for(j=0;j<15;j++)
		{
			if(matrix[i][j]>=matrix[i][j+1])
			{
				if(matrix[i][j]>b[1][i])
				{
					b[0][i]=j;
					b[1][i]=matrix[i][j];
				}
			}
			else
			{
				if(matrix[i][j+1]>b[1][i])
				{
					b[0][i]=j+1;
					b[1][i]=matrix[i][j+1];
				}
			}
		}
	}
	printf("We are printing the index and the value where maximum bias is occuring in each row of linear approximation table\n\n");
	printf("Index             Maximum\n");
	printf("-----             -------\n");
	for(j=0;j<64;j++)
	{
		for(i=0;i<2;i++)
		{
			printf("%2d                  ",b[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<64;i++)
	{
		for(j=0;j<16;j++)
		{
			sprintf(str, "%d", matrix[i][j]);
			fputs(str,fp);
			fputc(',',fp);
		}
		fputs("\n",fp);
	}
	fclose(fp);
	printf("\n\n\n    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
	printf("   ------------------------------------------------\n");
	for(i=0;i<64;i++)
	{
		for(j=0;j<16;j++)
		{
			if(j==0)
			{
				if(i<=9)
				{
					printf(" %d|",i);
				}
				else
				{
					printf("%d|",i);
				}
			}
			printf("%d",matrix[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}