#include <stdio.h>
#include <string.h>
#include <math.h>

int mult(unsigned int x, unsigned int y, unsigned int n) {
  unsigned long int k=1;
  int j;
  for (j=1; j<=y; j++) k = (k * x) % n;
  return (unsigned int) k;
}

int main () {
  char msg[100];
  unsigned int pt[100], ct[100], n, d, e, p, q, i;
  printf("Enter message : ");
  gets(msg);
  for(i=0;i<strlen(msg);i++)
   pt[i]=msg[i];
  n = 253; d = 17; e = 13;
  printf("\nCT = ");
  for(i=0; i<strlen(msg); i++) ct[i] = mult(pt[i], e,n);
  for(i=0; i<strlen(msg); i++) printf("%d ", ct[i]);
  printf("\nDecrypting...");
  for(i=0; i<strlen(msg); i++)
  pt[i] = mult(ct[i], d,n) ;
  printf("\nPT = ");
  for(i=0; i<strlen(msg); i++)
  printf("%c", pt[i]);
  return 0;
}
