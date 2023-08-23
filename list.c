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
  List *lista = (List*)malloc(sizeof(List));
  return lista;
}

void * firstList(List * list) {
  if (list->head == NULL){
    return NULL;
  }
  
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL){
    return NULL;
  }
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  Node *actual = list->head;
  if (actual == NULL){
    return NULL;
  }
  
  while (actual->next != NULL){
    actual = actual->next;
  }

  list->current = actual;
  //printf("%d",*((int*)list->current->data));
  return list->current->data;
}

void * prevList(List * list) {
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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}