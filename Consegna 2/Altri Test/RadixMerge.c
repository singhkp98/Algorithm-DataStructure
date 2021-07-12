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

int getMax(int* A, int n){
  int i;
  int max = A[0];
  ct_op++; 
  for (i = 1; i < n; i++)
    if (A[i] > max)
      max = A[i];
    ct_op++;
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

void merge(int* A, int p, int q, int r, int* L, int* R){

  int i=0;
  int j=0;
  int k=0;
  
  for (i=0;i<q-p+1;i++){
    L[i]=A[p + i];
    ct_op=ct_op+2;
  }
  L[i]=1000000;
  ct_op++;
  
  for (i=0;i<r-q;i++){
    R[i]=A[q+1 + i];
    ct_op=ct_op+2; 
  }
  R[i]=1000000;
  ct_op++; 

  i=0;
  j=0;

  for (k=p;k<=r;k++){
    if (L[i]<=R[j]){
      A[k]=L[i];
      i++;
      ct_op=ct_op+2; 
    }
    else{
      A[k]=R[j];
      j++;
      ct_op=ct_op+2; 
    }
    ct_op=ct_op+2; 
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


void sorting(int* A, int p, int r, int* L, int* R, int* B, int* C, int k){
  if(p<r){
    int q=(p+r)/2; 
    radix_sort(A,B,C,q);
    merge_sort(A,q+1,r,L,R);
    for(int j=0; j<=q; j++){
      A[j]=B[j];
      ct_op=ct_op+2;
    }
    merge(A,p,q,r,L,R);
  }
}

int main(int argc, char **argv) {

  int n,i;
  int k=0; //valore max nell'array di input
  int* A;
  int* B;  
  int* C;  
  int* L;  
  int* R;  

  n = atoi(argv[1]);

  max_dim = atoi(argv[1]);
  A = new int[max_dim];
  B = new int[max_dim];
  C = new int[MAX_COUNT];
  L = new int[max_dim+1];
  R = new int[max_dim+1];

  srand((unsigned) time(NULL));

  /// inizializzazione array
  for (i=0; i<(n/2)-1; i++) {
    A[i]=rand()%n/10;
    if(k<A[i])
      k=A[i];
    ct_op++;
  }

  for (i=n/2; i<n; i++) {
    A[i]=(n-i)*(n-i);
    ct_op++;
  }

  /// input
   printf("L'input e':\n");
    for (i=0; i<n; i++) {
      printf("%d ",A[i]);
    } 
    printf("\n");

  /// sort
  sorting(A,0,n-1,L,R,B,C,k);

  /// output
  printf("L'output e':\n");
   for (i=0; i<n-1; i++) {
     printf("%d ",A[i]);
    }
  printf("\n");

  printf("Totale accessi alla memoria = %d\n",ct_op);
  
  return 0;
}
