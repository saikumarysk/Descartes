#include<stdio.h>

int main()
{
    FILE *fp;
    fp= fopen("diff_table_4.txt","w");
    int i,j,k,t;
    int sbox4[64]={13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};// The sbox proposed
    int x[64],x1[64],x2[64];//x is the input difference, x', x1 is x and x2 is x*
    int y[64],y1[64],y2[64];//y is the output difference, y', y1 is y and y2 is y*
    int table[64][16]={0};// The differential table
    int b[2][64] = {0};
    char str[16];
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
            y1[j]=sbox4[x1[j]];
            y2[j]=sbox4[x[j]];
            y[j]=y1[j]^y2[j];// The corresponding output differences
            table[t][y[j]]++;// Updating the table
        }
    }
    for(i=0;i<64;i++)
    {
        for(j=0;j<15;j++)
        {
            if(table[i][j]>=table[i][j+1])
            {
                if(table[i][j]>table[1][i])
                {
                    b[0][i]=j;
                    b[1][i]=table[i][j];
                }
            }
            else
            {
                if(table[i][j+1]>table[1][i])
                {
                    b[0][i]=j+1;
                    b[1][i]=table[i][j+1];
                }
            }
        }
    }
    for(i=0;i<2;i++)
    {
        for(j=0;j<64;j++)
        {   
            sprintf(str, "%d", b[i][j]);
            fputs(str,fp);
            fputc(',',fp);
        }
        fputs("\n",fp);
    }
    fclose(fp); 
    printf("We are printing the index and the value where maximum bias is occuring\n");
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
    // The cliche printing of 2d array
    printf("\n\n\n    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
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