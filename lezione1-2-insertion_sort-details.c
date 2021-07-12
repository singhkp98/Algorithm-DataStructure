#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int details=0;

int ct_swap=0;

void swap(int* a, int* b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
  ct_swap++;
}

void insertion_sort(int* A, int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=i-1; j>=0; j--) {
      if (A[j]>A[j+1]) {
	swap (&A[j],&A[j+1]);
      } else {
	break;
      }
    }

    /// stampa i passi dell'algoritmo
    if (details){
      printf("passo %d:\n",i);
      for (j=0; j<n; j++) {
	printf("%d ",A[j]);
      }
      printf("\n");

    }
    
  }
}


int main(int argc, char **argv) {
  int n,i;
  int* A;

  /// controllo argomenti
  if (argc < 2) {
    printf("Usage: %s dim-array [details=0/1]\n",argv[0]);
    return 1;
  }

  /// parsing argomento
  n = atoi(argv[1]);
  if (argc==3)
    details = atoi(argv[2]);
    
  
  /// allocazione array
  A = (int*) malloc(n*sizeof(int));

  /// inizializzazione array
  for (i=0; i<n; i++) {
    A[i]=n-i;
  }

  /// input
  if (details){
    printf("L'input e':\n");
    for (i=0; i<n; i++) {
      printf("%d ",A[i]);
    }
    printf("\n");
  }
  
  /// sort
  insertion_sort(A,n);

  /// output
  if (details){
    printf("L'output e':\n");
    for (i=0; i<n; i++) {
      printf("%d ",A[i]);
    }
    printf("\n");
  }

  printf("Totale swap = %d\n",ct_swap);
  return 0;
}
