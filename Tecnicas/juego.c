#include "juego.h"

List* crearLista(){
    List* lista = (List*) malloc(sizeof(List));
    lista->head = NULL;
    lista->size = 0;
    return lista;
}

void agregarObjeto(List* lista, Objeto objeto){
    Node* nuevoNodo = (Node*) malloc(sizeof(Node));
    nuevoNodo->object = objeto;
    nuevoNodo->next = NULL;

    if(lista->head == NULL){
        lista->head = nuevoNodo;
    }
    else{
        Node* ultimoNodo = lista->head;
        while(ultimoNodo->next != NULL){
            ultimoNodo = ultimoNodo->next;
        }
        ultimoNodo->next = nuevoNodo;
    }
  
    lista->size++;
}

void imprimirObjeto(Node* nodo){
    printf("Nombre: %s, Estadisticas: %d\n", nodo->object.name, nodo->object.stats);
}

void imprimirLista(List* lista){
    Node* nodoActual = lista->head;
    int i = 1;
    while(nodoActual != NULL){
        printf("%d. ", i);
        imprimirObjeto(nodoActual);
        nodoActual = nodoActual->next;
        i++;
    }
}
