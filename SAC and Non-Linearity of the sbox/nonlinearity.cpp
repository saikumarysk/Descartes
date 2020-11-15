#include<stdio.h>

int main()
{
        int sbox[64]={15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,11,7,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,5,0,14,9};//The sbox
        int x1[64],x2[64],x3[64],x4[64],x5[64],x6[64];//Inputs to the sbox from left to right
        int y1[64],y2[64],y3[64],y4[64],out[64];//output of the sbox from left to right
        int table[1024];
        int i,j;
        for(i=0;i<64;i++)
        {
                //Creating all possibilities for input
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

                //Creating all outputs
                y1[i]=(sbox[i]/8)%2;
                y2[i]=(sbox[i]/4)%2;
                y3[i]=(sbox[i]/2)%2;
                y4[i]=(sbox[i])%2;
        }
        int k;
        for(i=0;i<64;i++)
        {
                k=0;
                for(j=0;j<64;j++)
                {
                        //We are calculating the distance for all possible affine functions
                        out[j]=(((i/32)%2)*x1[j])^(((i/16)%2)*x2[j])^(((i/8)%2)*x3[j])^(((i/4)%2)*x4[j])^(((i/2)%2)*x5[j])^((i%2)*x6[j]);//^ is xor in c++
                        if(out[j]!=y1[j])
                        {
                                k=k+1;
                        }
                }
                table[i]=k;
         }
         for(i=0;i<63;i++)
         {
                int x;
                if(table[i]<table[i+1])
                {
                        table[i+1]=table[i];
                }
        }
        printf("The non-linearity in y1 is %d\n",table[63]);
        for(i=0;i<64;i++)
        {
                k=0;
                for(j=0;j<64;j++)
                {
                        //We are calculating the distance for all possible affine functions
                        out[j]=(((i/32)%2)*x1[j])^(((i/16)%2)*x2[j])^(((i/8)%2)*x3[j])^(((i/4)%2)*x4[j])^(((i/2)%2)*x5[j])^((i%2)*x6[j]);//^ is xor in c++
                        if(out[j]!=y2[j])
                        {
                                k=k+1;
                        }
                }
                table[i]=k;
         }
         for(i=0;i<63;i++)
         {
                int x;
                if(table[i]<table[i+1])
                {
                        table[i+1]=table[i];
                }
        }
        printf("The non-linearity in y2 is %d\n",table[63]);
        for(i=0;i<64;i++)
        {
                k=0;
                for(j=0;j<64;j++)
                {
                        //We are calculating the distance for all possible affine functions
                        out[j]=(((i/32)%2)*x1[j])^(((i/16)%2)*x2[j])^(((i/8)%2)*x3[j])^(((i/4)%2)*x4[j])^(((i/2)%2)*x5[j])^((i%2)*x6[j]);//^ is xor in c++
                        if(out[j]!=y3[j])
                        {
                                k=k+1;
                        }
                }
                table[i]=k;
         }
         for(i=0;i<63;i++)
         {
                int x;
                if(table[i]<table[i+1])
                {
                        table[i+1]=table[i];
                }
        }
        printf("The non-linearity in y3 is %d\n",table[63]);
        for(i=0;i<64;i++)
        {
                k=0;
                for(j=0;j<64;j++)
                {
                        //We are calculating the distance for all possible affine functions
                        out[j]=(((i/32)%2)*x1[j])^(((i/16)%2)*x2[j])^(((i/8)%2)*x3[j])^(((i/4)%2)*x4[j])^(((i/2)%2)*x5[j])^((i%2)*x6[j]);//^ is xor in c++
                        if(out[j]!=y4[j])
                        {
                                k=k+1;
                        }
                }
                table[i]=k;
         }
         for(i=0;i<63;i++)
         {
                int x;
                if(table[i]<table[i+1])
                {
                        table[i+1]=table[i];
                }
        }
        printf("The non-linearity in y4 is %d\n",table[63]);
        return 0;
}

