#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *lista = (List*)malloc(sizeof(List)); // se reserva memoria para la lista
  return lista;
}

// Función para obtener el primer elemento de la lista
void * firstList(List * list) {
    if (list->head == NULL) { // La lista está vacía
        return NULL; 
    }

    list->current = list->head; // Se establece el nodo actual como el primer nodo
    return list->current->data; // Se devuelve el dato del nodo actual
}

// Función para obtener el siguiente elemento de la lista
void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL){
    return NULL; // No hay un siguiente elemento
  }
  
  list->current = list->current->next; // se mueve al siguiente de nodo
  return list->current->data; // retorna e; dato del nodo actual
}

// Función para obtener el último elemento de la lista
void * lastList(List * list) { 
  Node *actual = list->head;
  if (actual == NULL){
    return NULL; // La lista está vacía
  }
  
  while (actual->next != NULL){ // itera hasta el ultimo elemento
    actual = actual->next;
  }

  list->current = actual; // Se establece el nodo actual como el último nodo
  //printf("%d",*((int*)list->current->data)); esto lo use para comprobar la lectura de data
  return list->current->data; // Se devuelve el dato del nodo actual
}

// Función para obtener el elemento previo al nodo actual
void * prevList(List * list) { //
  if (list->current == NULL || list->current == list->head){
    return NULL; // No hay un elemento previo
  }
  //printf("current:%d prev:%d",*((int*)list->current->data),*((int*)list->current->prev->data)); esto lo use para comprobar la lectura de data 
  list->current = list->current->prev; // Se mueve al nodo previo
  return list->current->data; // Se devuelve el dato del nodo actual
}

// Función para agregar un elemento al frente de la lista
void pushFront(List * list, void * data) {
  Node *nuevoNodo = createNode(data); // Se crea un nuevo nodo con el dato
  if (list->head == NULL){ // Si la lista está vacía, el nuevo nodo se convierte en la cabeza y la cola
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } else { // en caso contrario se hacen las conexiones necesarias entre los nodos (cabeza y nuevo nodo)
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail; 
    pushCurrent(list,data); 
}

void pushCurrent(List * list, void * data) {
  if (list == NULL){
    return; // La lista es nula, no se puede agregar el elemento
  }
  
  Node *nuevoNodo = createNode(data); // Se crea un nuevo nodo con el dato

  if (list->current == NULL){ // Si la lista está vacía, el nuevo nodo se convierte en la cabeza y la cola
    list->head = nuevoNodo; 
    list->tail = nuevoNodo;
    list->current = nuevoNodo;
  } else {
    nuevoNodo->next = list->current->next; // El nuevo nodo apunta al siguiente nodo del nodo actual
    if (list->current->next != NULL)
    {
      list->current->next->prev = nuevoNodo; // El nodo siguiente al nodo actual apunta al nuevo nodo como previo
    }
    nuevoNodo->prev = list->current; // El nuevo nodo apunta al nodo actual como previo
    list->current->next = nuevoNodo; // El nodo actual apunta al nuevo nodo como siguiente
    list->tail = nuevoNodo; // El nuevo nodo se convierte en la nueva cola
    list->current = nuevoNodo; // El nuevo nodo se convierte en el nodo actual
  }

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// Función para eliminar el elemento actual de la lista
void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL){
    return NULL; // La lista o el nodo actual son nulos, no se puede eliminar el elemento
  }
   
  Node *eliminado = list->current; // Se guarda una referencia al nodo actual
  void *data_local = eliminado->data; // Se guarda el dato del nodo actual
  
  if (eliminado->prev != NULL){
    eliminado->prev->next = eliminado->next; // El nodo previo apunta al siguiente nodo
  } else {
    list->head = eliminado->next; // Si no hay nodo previo, el siguiente nodo se convierte en la cabeza
  }
  
  if (eliminado->next != NULL){
    eliminado->next->prev = eliminado->prev; // El nodo siguiente apunta al nodo previo
  } else {
    list->tail = eliminado->prev; // Si no hay nodo siguiente, el nodo previo se convierte en la cola
  }
  
  list->current = eliminado->next; // El nodo siguiente al eliminado se convierte en el nodo actual
  free(eliminado); // se libera el nodo
  return data_local; // se devuelve el dato del nodo anteriormente eliminado
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}