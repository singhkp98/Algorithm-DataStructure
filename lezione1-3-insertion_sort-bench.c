#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int ntests=1000;
int ct_swap=0;
int ct_cmp=0;

void swap(int* a, int* b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
  /// aggiorno contatore globale di swap 
  ct_swap++;
}

void insertion_sort(int* A, int n) {
  int i,j;
  for (i=0; i<n; i++) {
    for (j=i-1; j>=0; j--) {
      ct_cmp++;
      if (A[j]>A[j+1]) {
	swap (&A[j],&A[j+1]);
      } else {
	//// cosa succede se si rimuove questo break?
	break;
      }
    }
  }
}


int main(int argc, char **argv) {
  int n,i,test;
  int* A;

  /// controllo argomenti
  if (argc != 2) {
    printf("Usage: %s max-dim-array\n",argv[0]);
    return 1;
  }

  /// parsing argomento
  int max_dim_array = atoi(argv[1]);
      
  /// allocazione array
  A = (int*) malloc(max_dim_array*sizeof(int));

  // init random
  srand((unsigned) time(NULL));


  printf("Dim_array,N_test,min_swap,avg_swap,max_swap,worst_case_swap,min_cmp,avg_cmp,max_cmp,worst_case_cmp\n");

  //// inizio ciclo per calcolare 100 dimensioni di array crescenti
  for (n = max_dim_array/100;n<=max_dim_array;n+=max_dim_array/100){
    int swap_min=-1;
    int swap_max=-1;
    long swap_avg=-1;

    int cmp_min=-1;
    int cmp_max=-1;
    long cmp_avg=-1;

    //// lancio ntests volte per coprire diversi casi di input random
    for (test=0;test<ntests;test++){
  
      /// inizializzazione array: numeri random con range dimensione array
      for (i=0; i<n; i++) {
		A[i]= n-i;
		//A[i]= rand() % n;
      }

      ct_swap=0;
      ct_cmp=0;
      /// algoritmo di sorting
      insertion_sort(A,n);

      /// statistiche
      swap_avg+=ct_swap;
      if (swap_min<0 || swap_min>ct_swap) swap_min=ct_swap;
      if (swap_max<0 || swap_max<ct_swap) swap_max=ct_swap;
      cmp_avg+=ct_cmp;
      if (cmp_min<0 || cmp_min>ct_swap) cmp_min=ct_cmp;
      if (cmp_max<0 || cmp_max<ct_swap) cmp_max=ct_cmp;
    }

    printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
	   n,ntests,
	   swap_min,(int)round((0.0+swap_avg)/ntests),swap_max,n*(n-1)/2,
	   cmp_min ,(int)round((0.0+cmp_avg)/ntests) ,cmp_max ,n*(n-1)/2);
  }
  return 0;
}
