#include<stdio.h>
#include<stdlib.h>
#define INF 999

struct vector
{
int cost;
int via;
};

int i,j,n;
struct vector c[6][6];
void findpath1(int,int);
void matrix(void);

int main()
{
printf("\nEnter the no of nodes:");
scanf("%d",&n);
printf("\nEnter the distance matrix:cost and via node");
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
scanf("%d",&c[i][j].cost);
c[i][j].via=INF;
}
}
printf("\nStarting vertex:cost and via node");
for(i=1;i<=n;i++)
{
printf("\nrow %d\t",i);
for(j=1;j<=n;j++)
{
printf("%d,%d\t",c[i][j].cost,c[i][j].via);
}
printf("\n");
}
matrix();
return 0;
}

void matrix()
{
int cost,t,x,n1,n2,k,next,final;
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
cost=INF;
if(i!=j)
{
for(k=1;k<=n;k++)
{
if(i!=k)
{
x=c[i][k].cost+c[k][j].cost;
if(cost>x)
{
cost=x;
t=k;
}
}}
c[i][j].cost=cost;
c[i][j].via=t;
}
else
{
c[i][j].cost=0;
c[i][j].via=i;
}
}
}
printf("\nFinal matrix:cost and via node\n");
for(i=1;i<=n;i++)
{
for(j=1;j<=n;j++)
{
printf("%d,%d\t",c[i][j].cost,c[i][j].via);
}
printf("\n");
}
next=1;
while(next)
{
printf("\nEnter the source node:");
scanf("%d",&n1);
printf("\nEnter the destination node:");
scanf("%d",&n2);
printf("\nShortest path from %d to %d has %d cost\n",n1,n2,c[n1][n2].cost);
printf("\nPath is :");
final=c[n1][n2].via;
printf("%d-->",n1);
findpath1(n1,n2);
printf("%d",n2);
printf("\nWould you like to continue?(0 or 1)");
scanf("%d",&next);
}}

void findpath1(int n1,int n2)
{
int t1,t2;
t1=c[n1][n2].via;
if(t1<n2)
findpath1(n1,t1);
if(t1!=n2)
printf("%d-->",t1);
}
