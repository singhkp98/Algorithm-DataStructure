#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

// compilazione: g++ -xc++ lezione8-1-list-double.c 
//
// Obiettivo:
// 1) analisi allocazioni
// ./a.out -verbose 


int ct_swap=0;
int ct_cmp=0;
int ct_op=0;  /// operazioni per la ricerca

int max_dim=0;
int ntests=1;
int ndiv=1;
int details=0;
int graph=0;


int n=0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione=0; /// contatore di operazioni per visualizzare i vari step


//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int val;
    struct node * next;
    struct node * prev; 
} node_t;


/// struct per la lista
typedef struct list {
     node *head;
     node *tail; /// per lista doubly linked
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista///
//////////////////////////////////////////////////



list_t* global_ptr_ref=NULL;  /// usato per memorizzare il puntatore alla prima lista allocata

//funzione alla quale se do in input un nodo mi restituisce la differenza in byte fra
//il nodo e il nodo globale (in poche parole la distanza fra il nodo che abbiamo allocato per primo e il 
//nodo che viene passo per parametro)
int get_address( void* node){
  return (int)((long)node-(long)global_ptr_ref);
}


void list_print(list_t *l){
  printf("Stampa lista\n");
  node_t* current = l->head;
  while(current != NULL) {
    printf("%d ",current->val);
    current = current->next;
  }
  printf("\n");
}


list_t * list_new(void){
  list_t* l=new list;
  if (details){
    printf("Lista creata\n");
  }
  
  l->head=NULL;
  l->tail=NULL;
  if (details){
    printf("Imposto a NULL head e tail\n");
  }

  return l;
}

void list_insert_front(list_t *l, int elem){
  /// inserisce un elemento all'inizio della lista
  node_t* new_node = new node_t;
  new_node->val = elem; 

  if(l->head==NULL && l->tail==NULL){
    new_node->next = NULL;
    new_node->prev = NULL;

    l->head=new_node;
    l->tail=new_node;
  }

  new_node->next = l->head;
  new_node->prev  = NULL; 
  l->head->prev = new_node; 
  l->head = new_node;
}

  
void print_array(int* A, int dim){
  for (int j=0; j<dim; j++) {
    printf("%d ",A[j]);
  }
  printf("\n");
}


void swap(int &a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
  /// aggiorno contatore globale di swap 
  ct_swap++;
}


int parse_cmd(int argc, char **argv){
  /// controllo argomenti
  int ok_parse=0;
  for (int i=1;i<argc;i++){
    if (argv[i][1]=='v'){
      details=1;
      ok_parse=1;
    }
    if (argv[i][1]=='g'){
      graph=1;
      ok_parse=1;
    }
  }

  if (argc > 1 && !ok_parse) {
    printf("Usage: %s [Options]\n",argv[0]);
    printf("Options:\n");
    printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
    printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
    return 1;
  }

  return 0;
}

int main(int argc, char **argv) {
  int i,test;

  if (parse_cmd(argc,argv))
    return 1;

  if (graph){
    output_graph.open("graph.dot");
    /// preparo header
    output_graph << "digraph g"<<endl; 
    output_graph << "{ "<<endl;
    output_graph << "node [shape=none]"<<endl;
    output_graph << "rankdir=\"LR\""<<endl;;
    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;    
  }
  
  list_t* list = list_new();
  global_ptr_ref=list;
  
  list_insert_front(list,3);
  printf("Inserimento riuscito! Il Valore inserito e' %d \n ", list->head->val);
  list_insert_front(list,5);
  printf("Inserimento riuscito! Il Valore inserito e' %d \n ", list->head->val);
  list_insert_front(list,8);
  printf("Inserimento riuscito! Il Valore inserito e' %d \n ", list->head->val);
  list_insert_front(list,12);
  printf("Inserimento riuscito! Il Valore inserito e' %d \n ", list->head->val);
  list_insert_front(list,17);
  printf("Inserimento riuscito! Il Valore inserito e' %d \n ", list->head->val);
  
  list_print(list);
    
  // init random
  srand((unsigned) time(NULL));


  if (graph){
    /// preparo footer e chiudo file
    output_graph << "}"<<endl; 
    output_graph.close();
    cout << " File graph.dot scritto" << endl<< "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf"<<endl;
  }

  return 0;
}
