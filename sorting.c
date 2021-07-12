#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

#define MAX_COUNT 100000

int ct_op=0;
int max_dim=0;

void counting_sort(int* A, int* B, int* C, int n, int k) {

  for (int i=0;i<=k;i++){ 
    C[i]=0;
  }

  for (int j=0;j<n;j++){ 
    C[A[j]]++;
  }

  for (int i=1;i<=k;i++){
    C[i]+=C[i-1];
  }
  
  for (int j=n-1;j>=0;j--){ 
    
    B[C[A[j]]-1]=A[j];
    C[A[j]]=C[A[j]]-1;
  }
}

void merge(int* A, int p, int q, int r, int* L, int* R){

  int i=0;
  int j=0;
  int k=0;
  
  for (i=0;i<q-p+1;i++)
    L[i]=A[p + i];
  L[i]=1000000;
  
  for (i=0;i<r-q;i++)
    R[i]=A[q+1 + i];
  R[i]=1000000;

  i=0;
  j=0;

  for (k=p;k<=r;k++){
    if (L[i]<=R[j]){
      A[k]=L[i];
      i++;
    }
    else{
      A[k]=R[j];
      j++;
    }
  }
  
}

void merge_sort(int* A, int p, int r, int* L, int* R) {
  /// gli array L e R sono utilizzati come appoggio per copiare i valori: evita le allocazioni nella fase di merge
  if (p<r){
    int q=(p+r)/2;
    merge_sort(A,p,q,L,R);
    merge_sort(A,q+1,r,L,R);
    merge(A,p,q,r,L,R);
  }
}

int main(int argc, char **argv) {

  int n,i,nc,k;
  int* A;
  int* B;  
  int* C;  
  int* L;  
  int* R;  

  n = atoi(argv[1]);
  
  //A = (int*) malloc(n*sizeof(int));

  max_dim = atoi(argv[1]);
  A = new int[max_dim];
  B = new int[max_dim];
  C = new int[MAX_COUNT];
  nc = (n/2)-1;
  k = (n/10)-1;

  L = new int[max_dim+1];
  R = new int[max_dim+1];

  srand((unsigned) time(NULL));

  /// inizializzazione array
  for (i=0; i<(n/2)-1; i++) {
    A[i]=rand()%n/10;
  }
  for (i=n/2; i<n-1; i++) {
    A[i]=(n-i)*(n-i);
  }

  /// input
   printf("L'input e':\n");
    for (i=0; i<n; i++) {
      printf("%d ",A[i]);
    }
    printf("\n");

  /// sort
  counting_sort(A,B,C,n,k);
  merge_sort(A,0,n-1,L,R);

  /// output
  printf("L'output e':\n");
   for (i=0; i<n; i++) {
     printf("%d ",A[i]);
    }
  printf("\n");

  //printf("Totale accessi alla memoria = %d\n",ct_op);
  return 0;
}
