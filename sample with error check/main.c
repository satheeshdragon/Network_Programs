#include <stdio.h>
#include <stdlib.h>

int main()
{
   int data[10],sdata[10][3],rdata[10][3]={0,0,0,1,1,1,0,0,0,1,1,1},fdata[10],n,i,j;
   int c,count;
    printf("enter the number of bits in the original data\n");
    scanf("%d",&n);
    printf("enter the data\n");
    for(i=0;i<n;i++)
    scanf("%d",&data[i]);

    printf("appending the redundent values...\n");
    for(i=0;i<n;i++)
    for(j=0;j<3;j++)
    sdata[i][j]=data[i];

    printf("sending the data ......\n");
    //for(i=0;i<n;i++)
    //for(j=0;j<3;j++)
    //rdata[i][j]=sdata[i][j];

   for(i=0;i<n;i++)
   for(j=0;j<3;j++)
    {
       c=-2;
       if(rdata[i][j]!=data[i])
       c=-1;

       if(c==-1)
       {
           printf("one bit error occured at position %d of bit %d\n",j+1,i+1);

       }

    }

for(i=0;i<n;i++)
{
    count=0;
   for(j=0;j<3;j++)
    {

       if(rdata[i][j]!=sdata[i][j])
       count++;

       if(count>=2)
       {
           printf("More than one bit error. please resend the data \n");
           return 0;
       }

    }
}

    for(i=0;i<n;i++)
    {
       j=0;
       if(rdata[i][j]==rdata[i][j+1] && rdata[i][j+1]==rdata[i][j+2])
       c=rdata[i][j];
       else
       if (rdata[i][j]==rdata[i][j+1])
       c=rdata[i][j];
        else
       if (rdata[i][j]==rdata[i][j+2])
       c=rdata[i][j];
        else
       if (rdata[i][j+1]==rdata[i][j+2])
       c=rdata[i][j+1];

       fdata[i]=c;

    }
    printf("\nthe sent data is \n ");
    for(i=0;i<n;i++)
    printf("%d",data[i]);

    printf("\nthe data sent after appending is \n ");
    for(i=0;i<n;i++)
    for(j=0;j<3;j++)
    printf("%d",sdata[i][j]);

    printf("\nthe appending recieved is \n ");
    for(i=0;i<n;i++)
    for(j=0;j<3;j++)
    printf("%d",rdata[i][j]);

    printf("\nthe recieved data is \n");
    for(i=0;i<n;i++)
    printf("%d",fdata[i]);


    return 0;
}
