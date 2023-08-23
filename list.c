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
    if (list->head == NULL) {
        return NULL; // La lista está vacía
    } else {
        list->current = list->head; // Actualizamos current para que apunte al primer nodo
        return &(list->head->data); // Retornamos un puntero al dato del primer nodo
    }
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) {
        return NULL; // No hay un nodo siguiente o current no está definido
    } else {
        list->current = list->current->next; // Actualizamos current para que apunte al siguiente nodo
        return &(list->current->data); // Retornamos un puntero al dato del siguiente nodo
    }
}

void * lastList(List * list) {
    return NULL;
}

void * prevList(List * list) {
    return NULL;
}

void pushFront(List * list, void * data) {
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