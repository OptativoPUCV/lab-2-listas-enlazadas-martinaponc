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
    List *L = (List*) malloc (sizeof(List));
    if(L == NULL){
        return NULL;
    }
    L->head = NULL;
    L->current = NULL;
    return L;
}

void * firstList(List * list) {
    if(list->head == NULL)
        return NULL;

    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if(list->current == NULL || list->current->next == NULL){
        return NULL;
    }

    list->current = list->current->next;
    return list->current->data;
    
}

void * lastList(List * list) {
    if(list->head == NULL){
        return NULL;
    }
    list->current = list->head;
    while(list->current->next != NULL){
        list->current = list->current->next;
    }
    return list->current->data;
}

void * prevList(List * list) {
    if (list->head == NULL || list->current == NULL || list->current == list->head)
        return NULL;

    Node *temp = list->head;

    while(temp->next != NULL && temp->next != list->current){
        temp = temp->next;
    }
    list->current = temp;
    return list->current->data;
}    

void pushFront(List * list, void * data) {

    Node *nuevoNodo = createNode(data);
    if (list->head == NULL){
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
    }
    else{
        nuevoNodo->next = list->head;
        list->head = nuevoNodo;
    }
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    if(list->current->next == NULL){
        list->current->next = nuevoNodo;
        nuevoNodo->prev = list->current;
        list->tail = nuevoNodo;
    }
    else{
        nuevoNodo->next = list->current->next;
        nuevoNodo->prev = list->current;
        list->current->next = nuevoNodo;
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
    if(list->current == NULL){
        return NULL;
    }
    Node *nodoEliminado = list->current;
    void *data = nodoEliminado->data;

    //SI EL ELEMENTO A ELIMINAR ES EL UNICO

    if(list->current == list->head && list->current = list->tail){
        list->head = NULL;
        list->tail = NULL;
    }

    //SI EL ELEMENTO A ELIMINAR ESTA EN EL HEAD

    else if (list->current == list->head){
        list->head = list->current->next;
        list->head->prev = NULL;
    }
    
    // Si el nodo actual es el último nodo
    else if (list->current == list->tail){
        list->tail = list->current->prev;
        list->tail->next = NULL;
    }
    else {
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
    }

    Node *temp = list->current->next;
    free(nodoEliminado);
    list->current = temp;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}