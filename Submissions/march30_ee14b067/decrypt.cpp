#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
unsigned long int expansionBox(int a)
{
	unsigned long int b=0;
	int i,d=0;
	for(i=0;i<16;i++)
	{
		d=((int)(a/pow(2,i)))%2;
		if(i==0)
		{
			b=pow(2,23)*d+2*d;
		}
		else if((i%4==-1) || (i%4==0))
		{
			b+=( pow(2,i+1)*d+ pow(2,i+3)*d);
		}
		else if(i==14)
		{
			b+= d+ pow(2,22)*d;
		}
		else
		{
			int c=i/4;
			b += d*pow(2,i+1+2*c);
		}	
	}
	return b;
}
unsigned long long int rotateLeft(unsigned long long int Key)
{
	int i=0;
	int dummy;
	unsigned long long int dummyKey=0;
	for(i=0;i<64;i++)
	{
		dummy = (unsigned long long int)(Key/(pow(2,i)))%2;
		if(i != 63)
		{
			dummyKey += dummy*pow(2,i+1) ;
		}
		if(i==63)
		{
			dummyKey += dummy;
		} 
	}
	return dummyKey;
}
unsigned long int KeyGeneration(unsigned long long int Key,int a) //Didn't implement this
{
	return 1;
}
unsigned long int SBox(unsigned long int Expa)
{
	int SBox1[64]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,4,7,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,6,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}; //Once Check if this is the right SBox or not.
	int SBox2[64]={10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};
	int SBox3[64]= {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};
	int SBox4[64]={13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
	int a,b,c,d;
	int p,q,r,s;
	unsigned long int output=0;
	a= (int)(Expa/pow(2,18));
	b= ((int)(Expa/pow(2,12))%((int)pow(2,6)));
	c= ((int)(Expa/pow(2,6))%((int)pow(2,6)));
	d= (Expa%((int)pow(2,6)));
	p= SBox1[a];
	q= SBox2[b];
	r= SBox3[c];
	s= SBox4[d];
	output += (int)(p*pow(2,12));
	output += (int)(q*pow(2,8));
	output += (int)(r*pow(2,4));
	output += (int)(s);
	return output;
}
unsigned long int Diffusion(unsigned long int a)
{
	int arr[16]= {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
	unsigned long int b=0;
	int i,bit=0;
	for(i=0;i<16;i++)
	{
		bit= ((int)(a/pow(2,i)))%2;
		b+= bit*pow(2,arr[i]);
	}
	return b;
}
int main(int argc, char **argv)
{
	FILE *fp;
	fp= fopen("enc_alice.txt","r");
	FILE *fp1;
	fp1= fopen("dec_alice.txt","w");
	int i=0;
	unsigned long int ascii1=0,ascii2=0,ascii3=0,ascii4=0  ;//,ascii11=0,ascii12=0,ascii21=0,ascii22=0;
	unsigned long int expa=0;
	int rounds=10;
	unsigned long long int Key= 8166579974873000917;
	unsigned long int Keys;
	Keys = KeyGeneration(Key,rounds);
	int k=0;
	while(fscanf(fp,"%ld",&ascii4)==1)
	{		
		ascii1=ascii4;
		fscanf(fp,"%ld",&ascii2);
		for(i=0;i<rounds;i++) //Iteration over the given number of rounds.
		{				
			if(i==0)
			{
				ascii1= ascii1^Keys;  // Key Generation Algorithm
				ascii2= ascii2^Keys;  // Key Generation Algorithm
			}
			else
			{
				ascii3= ascii1;
				expa= expansionBox(ascii1); //ExpansionBox Already Written
				expa= expa^Keys;  // Key Generation Algorithm	
				ascii1= SBox(expa); //SBox already written
				ascii1= Diffusion(ascii1); //Diffusion also already written
				ascii1= ascii1^ascii2;
				ascii2= ascii3;
			}
		}
		fflush(NULL);
		char ascii11=ascii1/256;
		char ascii12=ascii1%256;
		char ascii21=ascii2/256;
		char ascii22=ascii2%256;
		fprintf(fp1,"%c",ascii11);
		fprintf(fp1,"%c",ascii12);
		fprintf(fp1,"%c",ascii21);
		fprintf(fp1,"%c",ascii22);
	}
	return 0;
}