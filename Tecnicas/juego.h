#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef JUEGO_H
#define JUEGO_H

typedef struct object{
    char name[30];
    int stats;
}Objeto;

typedef struct nodeGraf{
	int zone;
	struct Node* next;
} NodeGraf;

typedef struct node{
    Objeto object;
    struct node* next;
}Node;

typedef struct ListGraf{
	int size;
	struct Node* head;	
}ListGraf;

typedef struct list{
    Node* head;
    int size;
}List;

typedef struct player{
    char name[30];
    int damage;
    int health1;
    int health2;
    int agility;
    int stamina;
}Jugador;

typedef struct monster{
    char name[7];
    char data[70];
    int health1;
    int health2;
    int rewards;
}Monstruo;

/* Prototipos */

void menu();
void juegonuevo();
void bestiario();
void imprimirinventario();
void explorar();
void estadisticas();
void agregarObjeto();
void imprimirObjeto();
void imprimirLista();

#endif