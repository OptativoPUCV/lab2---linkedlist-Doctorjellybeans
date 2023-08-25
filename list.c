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
    if (list->head == NULL) {
        return NULL; // La lista está vacía
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

void * prevList(List * list) { //
  if (list->current == NULL || list->current == list->head){
    return NULL;
  }
  //printf("current:%d prev:%d",*((int*)list->current->data),*((int*)list->current->prev->data));
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *nuevoNodo = createNode(data);
  if (list->head == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } else {
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
    return;
  }
  
  Node *nuevoNodo = createNode(data);

  if (list->current == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
    list->current = nuevoNodo;
  } else {
    nuevoNodo->next = list->current->next;
    if (list->current->next != NULL)
    {
      list->current->next->prev = nuevoNodo;
    }
    nuevoNodo->prev = list->current;
    list->current->next = nuevoNodo;

    
    list->tail = nuevoNodo;

    list->current = nuevoNodo;
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

void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL){
    return NULL; 
  }
   
  Node *eliminado = list->current;
  void *data_local = eliminado->data;
  
  if (eliminado->prev != NULL){
    eliminado->prev->next = eliminado->next;
  } else {
    list->head = eliminado->next;
  }
  
  if (eliminado->next != NULL){
    eliminado->next->prev = eliminado->prev;
  } else {
    list->tail = eliminado->prev;
  }
  
  list->current = eliminado->next;
  free(eliminado);
  return data_local;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}