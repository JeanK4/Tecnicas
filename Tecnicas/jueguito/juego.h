#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef JUEGO_H
#define JUEGO_H
#define VERTEX_NUMBER 5

typedef struct object{
    char name[30];
    int stats;
}Objeto;

typedef struct NodeGraf{
	int zone;
	struct NodeGraf* next;
} NodeGraf;

typedef struct node{
    Objeto object;
    struct node* next;
}Node;

typedef struct ListGraf{
	int size;
	struct NodeGraf* head;	
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
    int clasep;
}Jugador;

typedef struct monster{
    char name[7];
    char data[70];
    int health1;
    int health2;
    int rewards;
}Monstruo;

/* Prototipos Acciones*/
void menu();
void juegonuevo();
void bestiario();
void imprimirinventario();
void explorar();
void estadisticas();
void combate();
void avanzar();

/* Prototipos Listas de Objetos */
void agregarObjeto();
void imprimirObjeto();
void imprimirLista();
List* crearLista();

/* Prototipos Listas del grafo */
NodeGraf* create_vertex_node(int zone);
ListGraf create_simple_list();
void add_node_to_list(ListGraf* list, int zone);
void print_simple_list(ListGraf list);

/* Prototipos para las funciones propias del grafo */
void create_graph(ListGraf* arr);
void add_node_to_graph(ListGraf* arr, int node, int zone);
void print_graph(ListGraf* graph);

#endif