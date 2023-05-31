#include "juego.h"

const int graph = 5;

int abilitypoints = 0;
int flag = 0;
List grafo[graph];
create_Grafo(grafo);
Jugador player;

Objeto Index[6] = {
    {"Pocion de vida", 150},
    {"Pocion de stamina", 100},
    {"Baston magico", 200},
    {"Jeringa de adrenalina", 350},
    {"Espada", 200},
    {"Daga", 300}
};
Monstruo monst[5] = {
{"Ares","Monstruo hecho de lava, debil contra la magia",2500,2500,3},
{"Bagan","Mago que domina el agua, debil contra ataque ligero",3000,3000,4},
{"Culex","Asesino de la aldea perdida, debil contra ataque pesados",2000,2000,2},
{"Doom","Un ciclope gigante, sus ataques son lentos",3500,3500,5},
{"Engolo","Un duende asesino de niños, no tiene debilidad",10000,10000,10},
};

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

void imprimirinventario(List* inventario){
    imprimirLista(inventario);
}

void estadisticas(){
    int opcion3, answer, bandera = 0;
        printf("Estadisticas de %s:\n", player.name);
        printf("Health = %d\n", player.health1);
        printf("Damage = %d\n", player.damage);
        printf("Agility = %d\n", player.agility);
        printf("Stamina = %d\n", player.stamina);
    while(abilitypoints > 0 && bandera == 0){
        printf("Tienes %d punto/s disponible/s para asignar.\n\n", abilitypoints);
        printf("Deseas asignar tus puntos de habilidad?\n");
        printf("1. Si  2. No\n\nElige una opcion > ");
        scanf("%d", &answer);
        printf("\n");
        if(answer == 1){
            printf("1. Increase health\n2. Increase Damage\n3. Increase Agility\n4. Increase Stamina\n\nElige una opcion > ");
            scanf("%d", &opcion3);
            switch(opcion3){
            case 1:
                abilitypoints--;
                player.health1 += 100;
                printf("Tu estadistica de vida ha aumentado de %d a %d\n", player.health1-100, player.health1);
                break;
            case 2:
                abilitypoints--;
                player.damage += 100;
                printf("Tu estadistica de dano ha aumentado de %d a %d\n", player.damage-100, player.damage);
                break;
            case 3:
                abilitypoints--;
                player.agility += 100;
                printf("Tu estadistica de agilidad ha aumentado de %d a %d\n", player.agility-100, player.agility);
                break;
            case 4:
                abilitypoints--;
                player.stamina += 100;
                printf("Tu estadistica de stamina ha aumentado de %d a %d\n", player.stamina-100, player.stamina);
                break;
            case 5:
                break;
            default:
                printf("La opcion ingresada no existe\n");
                break;
            }
        }
        else{
            bandera = 1;
        }
    }
    if(abilitypoints == 0)
        printf("No tienes mas puntos para asignar\n");
}

void combate(){
    srand(time(0));
    int damage, boss = rand() % 5;
    printf("Se ha encontrado con: %s\n" , monst[boss].name);
    while(monst[boss].health2 > 0 && player.health2 > 0){ 
        int opcion2 = 0, probabilidadparry = rand() % 2, probabilidadgolpe = rand() % 3, probabilidadesquivar = rand() % 2, bossdamage = rand() % (100-150+1) + 100;
        if(player.stamina > 0){
            printf("\n1. Ataque ligero\n2. Ataque pesado\n3. Ataque magico\n4. Esquivar\n5. Parry\n6. Regenerar\n7. Escapar\nElige una opcion > ");
            scanf("%d",&opcion2);
            switch(opcion2){
            case 1:
                monst[boss].health2 = monst[boss].health2 - player.damage;
                player.stamina -= 375;
                break;
            case 2:
                if(probabilidadgolpe != 0){
                    printf("\nAtaque exitoso\n");
                    damage = player.damage * 2;
                    monst[boss].health2 = monst[boss].health2 - damage;
                }   
                else{
                    printf("\nAtaque fallido\n");
                }
                player.health2 = player.health2 - bossdamage;
                player.stamina -= 390;  
                break;
            case 3:
                break;
            case 4:
                if(probabilidadesquivar == 0){
                    printf("\nAtaque esquivado\n");
                    bossdamage = bossdamage * 0;
                }
                else{
                    printf("\nMuy lento\n");
                }
                player.stamina -= 410;
                break;
            case 5:
                if(probabilidadparry == 1){
                    printf("\nParry exitoso\n");
                    bossdamage *= 0;
                    monst[boss].health2 -= player.damage*4;
                }
                else{
                    printf("\nParry fallido\n");
                    
                }
                player.stamina -= 500;
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                printf("\nLa opcion ingresada no existe\n\n");
                break;
            }
        }
        else{
            printf("\nSin estamina, turno Perdido\n");
        }
        if(player.stamina < 0){
            player.stamina += 500;
        }
        else{
        player.stamina += (fabs(player.stamina) * 0.3);
        }
        player.health2 = player.health2 - bossdamage;
        printf("\nYour health:%d  Boss health:%d\n", player.health2, monst[boss].health2);
        printf("Your stamina: %d\n",player.stamina);
    
    }
    if(player.health2 < 0){
        flag = 1;
    }
}

void explorar(List* inventario){
    srand(time(0));
    char valor[3];
    int counter = 0, j, numero = rand() % 101;
    if(numero <= 5){
        printf("Se ha encontrado: Antorcha\n");
    }
    else if(numero <= 8){
        printf("Se ha encontrado: Fuente de habilidad\n");
        abilitypoints++;
    }
    else if(numero <= 19){
        printf("Se ha encontrado: %s\n", Index[0].name);
        agregarObjeto(inventario, Index[0]);
    }
    else if(numero <= 30){
        printf("Se ha encontrado: %s\n", Index[1].name);
        agregarObjeto(inventario, Index[1]);
    }
    else if(numero <= 40){
        printf("Se ha encontrado: %s\n", Index[2].name);
        agregarObjeto(inventario, Index[2]);
    }
    else if(numero <= 50){
        printf("Se ha encontrado: %s\n", Index[3].name);
        agregarObjeto(inventario, Index[3]);
    }
    else if(numero <= 60){
        printf("Se ha encontrado: %s\n", Index[4].name);
        agregarObjeto(inventario, Index[4]);
    }
    else if(numero <= 70){
        printf("Se ha encontrado: %s\n", Index[5].name);
        agregarObjeto(inventario, Index[5]);
    }
    else{
        printf("Se ha encontrado: nada\n");
    }
    if(numero <= 5){
        printf("\nDesea guardar la partida? ");
        scanf("%s",&valor);
        if(strcmp(valor,"si")== 0){
            printf("\nLa partida se ha guardado\n");
        }     
    }
}

void juegonuevo(){
    char nombre[30];
    int clase;
    printf("Digite el nombre de su personaje > ");
    scanf("%s", &nombre);
    printf("1. Asesino\n");
    printf("2. Guerrero\n");
    printf("3. Mago\n");
    printf("4. Tanque\n");
    printf("Seleccione su clase > ");
    scanf("%d", &clase);
    if(clase == 1){
        strcpy(player.name, nombre);
        player.damage = 400;
        player.health1 = 1400;
        player.health2 = 1400;
        player.agility = 100;
        player.stamina = 1200;
    }
    else if(clase == 2){
        strcpy(player.name, nombre);
        player.damage = 200;
        player.health1 = 2000;
        player.health2 = 2000;
        player.agility = 40;
        player.stamina = 1500;
    }
    else if(clase == 3){
        strcpy(player.name, nombre);
        player.damage = 500;
        player.health1 = 800;
        player.health2 = 800;
        player.agility = 70;
        player.stamina = 2000;
    }
    else{
        strcpy(player.name, nombre);
        player.damage = 80;
        player.health1 = 3000;
        player.health2 = 3000;
        player.agility = 20;
        player.stamina = 1600;
    }
}

void bestiario(){
    int i, contador = 0;
    int aresf = 0, baganf = 0, culexf = 0, doomf = 0, engolof = 0;
    printf("-- BESTIARIO --\n\n");
    for(i = 0; i < 5; i++){
        if(monst[i].health2 < 0){
            contador++;
            printf("Jefe #%d\n", contador);
            printf("Nombre: %s\n", monst[i].name);
            printf("Vida Total: %d\n", monst[i].health1);
            printf("Informacion: %s\n\n", monst[i].data);
            
        }
    }
    if(contador == 0)
        printf("Ningun jefe ha sido derrotado\n");
}

void menu(){
    List* inventario = crearLista();
    int opcion1 = 0;
    while(opcion1 != 6 && flag == 0){
        printf("\n1. Explorar\n2. Avanzar\n3. Estadisticas\n4. Inventario\n5. Bestiario\n6. Salir\nElige una opcion > ");
        scanf("%d",&opcion1);
        switch(opcion1){
        case 1:
            printf("\nIniciando Exploracion...\n\n");
            explorar(inventario);
            break;
        case 2:
            printf("\nAvanzando...\n\n");
            combate();
            break;
        case 3:
            printf("\nCargando Estadisticas...\n\n");
            estadisticas();
            break;
        case 4:
            printf("\nAbriendo Inventario...\n\n");
            imprimirinventario(inventario);
            break;
        case 5:
            printf("\nInspeccionando Bestiario...\n\n");
            bestiario();
            break;
        case 6:
            printf("\nSaliendo...\n\n");
            break;
        default:
            printf("\nLa opcion ingresada no existe\n\n");
            break;
        }
    }
    if(flag == 1)
        printf("Has sido derrotado\n");
}
