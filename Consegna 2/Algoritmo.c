#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

#define MAX_COUNT 1000000

int ct_op=0; 

int max_dim=0;

int getMax(int* A, int n){
  int i;
  int max = A[0];
  ct_op++; 
  for (i = 1; i < n; i++){
  	if (A[i] > max)
      max = A[i];
  	ct_op++;
  }

   return max;
}

void counting_sort(int* A, int* B, int* C, int n, int pos) {

  int i;

  for (i=0; i<=10; i++){
    C[i]=0;
    ct_op++;
  }

  for (i=0; i<n; i++){
    int v = (A[i]/pos)%10;
    C[v]++;
    ct_op=ct_op+3;
  }

  for (i=1; i<=10; i++){
    C[i]+=C[i-1];
    ct_op=ct_op+2; 
  }
  
  for (i=n-1; i>=0; i--){
    int v = (A[i]/pos)%10;
    ct_op++;
    B[C[v]-1]=A[i];
    ct_op=ct_op+3;
    C[v]--;
    ct_op=ct_op+2;
  }
  
  for(i=0; i<n; i++){
    A[i]=B[i]; 
    ct_op=ct_op+2;
  }
  
}

void radix_sort(int* A, int* B, int* C, int n){
  int max = getMax(A,n);
  for(int pos=1; max/pos>0; pos=pos*10)
    counting_sort(A,B,C,n,pos);
}

int main(int argc, char **argv) {

  int i,n; 
  int* A;
  int* B;  
  int* C;  

  max_dim = atoi(argv[1]);

  /// allocazione array
  A = new int[max_dim];
  B = new int[max_dim];
  C = new int[MAX_COUNT]; /// alloco l'array per i conteggi

  n = atoi(argv[1]);

  srand((unsigned) time(NULL));

  for (i=0; i<(n/2)-1; i++) {
    A[i]=rand()%n/10;
    //ct_op++;
  }

  for (i=n/2; i<n; i++) {
    A[i]=(n-i)*(n-i);
    //ct_op++;
  }
  
  ///input
  printf("L'input e':\n");
    for (i=0; i<n; i++) {
      printf("%d ",A[i]);
    } 
    printf("\n");

  /// algoritmo di sorting
  radix_sort(A,B,C,n);

  /// output
  printf("L'output e':\n");
   for (i=0; i<n-1; i++) {
     printf("%d ",A[i]);
    }
  printf("\n");

  delete [] A;
  delete [] B;
  delete [] C;

  printf("Totale accessi alla memoria = %d\n",ct_op);

  return 0;
}
