/* Integrantes
- Kevin Yavari Yoshioka
- Julian Galvis
- Jean Karlo */

/* Librerias */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estructuras */
typedef struct player{
    char name[30];
    int damage;
    int health;
    int agility;
    int stamina;
}Jugador;

typedef struct monster{
    char name[7];
    int damage;
    int health;
    int rewards;
}Monstruo;

/* Constantes definidas */ 
#define ARES 2500
#define BAGAN 3000
#define CULEX 2000
#define DOOM 3500
#define ENGOLO 10000

/* Arreglos */
int Bossestats[5] = {2500,3000,2000,3500,10000};
char Bosses[5][7] = {"Ares","Bagan","Culex","Doom","Engolo"};
char Bossesdata[5][70] = {"Monstruo hecho de lava, debil contra la magia","Mago que domina el agua, debil contra ataque ligero","Asesino de la aldea perdida, debil contra ataque pesados","Un ciclope gigante, sus ataques son lentos","Un duende asesino de niños, no tiene debilidad"};
char objetos[7][15] = {"antorcha","espada","escudo","fuente","nada","pocion de vida","baston magico"};
char invent[10][15] = {"","","","","","","","","",""};
int inventariosize = 0;
int abilitypoints = 0;
int flag = 0;
Jugador player;

/* Prototipos */
void menu();
void juegonuevo();
void bestiario();
void inventario();
void explorar();
void estadisticas();


/* Definiciones */
void inventario(){
    for(int i = 0; i < 10; i++)
        printf("%d. %s\n", i+1, invent[i]);
}

void estadisticas(){
    printf("Estadisticas de %s:\n", player.name);
    printf("Health = %d\n", player.health);
    printf("Damage = %d\n", player.damage);
    printf("Agility = %d\n", player.agility);
    printf("Stamina = %d\n", player.stamina);
    printf("Tienes %d punto/s disponible/s para asignar.\n", abilitypoints);
}

void combate(){
    srand(time(0));
    int damage, boss = rand() % 5;
    printf("Se ha encontrado con: %s\n" ,Bosses[boss]);    
    while(Bossestats[boss] > 0 && player.health > 0){ 
        int opcion2 = 8, probabilidadparry = rand() % 2, probabilidadgolpe = rand() % 3, probabilidadesquivar = rand() % 2, bossdamage = rand() % (100-150+1) + 100;
        if(player.stamina > 0){
            printf("\n1. Ataque ligero\n2. Ataque pesado\n3. Ataque magico\n4. Esquivar\n5. Parry\n6. Regenerar\n7. Escapar\nElige una opcion > ");
            scanf("%d",&opcion2);
        }
        else{
            printf("\nSin estamina, turno Perdido\n");
        }
        switch(opcion2){
        case 1:
            Bossestats[boss] = Bossestats[boss] - player.damage;
            player.stamina = player.stamina - 375;
            
            break;
        case 2:
            if(probabilidadgolpe != 0){
                printf("\nAtaque exitoso\n");
                damage = player.damage * 2;
                Bossestats[boss] = Bossestats[boss] - damage;
            }
            else{
                printf("\nAtaque fallido\n");
            }
            player.health = player.health - bossdamage;
            player.stamina = player.stamina - 390;  
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
            player.stamina = player.stamina - 410;
            break;
        case 5:
            if(probabilidadparry == 1){
                printf("\nParry exitoso\n");
                bossdamage *= 0;
                player.stamina = player.stamina - 500;
                Bossestats[boss] -= player.damage*4;
            }
            else{
                printf("\nParry fallido\n");
                player.stamina = player.stamina - 500;
            }
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
        player.stamina = player.stamina + (player.stamina * 0.25);
        player.health = player.health - bossdamage;
        printf("\nYour health:%d  Boss health:%d\n", player.health, Bossestats[boss]);
        printf("Your stamina: %d\n",player.stamina);
    
    }
    if(player.health < 0){
        flag = 1;
    }
}

void explorar(){
    srand(time(0));
    char valor[3];
    int counter = 0, j, numero = rand() % 101;
    if(numero <= 5){
        printf("Se ha encontrado: %s\n", objetos[0]);
    }
    else if(numero <=12){
        printf("Se ha encontrado: %s\n", objetos[1]);
        if(inventariosize < 11){
            strcpy(invent[inventariosize],objetos[1]);
            inventariosize++;
        }
    }
    else if(numero <= 19){
        printf("Se ha encontrado: %s\n", objetos[2]);
        if(inventariosize < 11){
            strcpy(invent[inventariosize],objetos[2]);
            inventariosize++;
        }
    }
    else if(numero <= 24){
        printf("Se ha encontrado: %s\n", objetos[3]);
        abilitypoints++;
    }
    else if(numero <= 39){
        printf("Se ha encontrado: %s\n", objetos[5]);
        if(inventariosize < 11){
            strcpy(invent[inventariosize],objetos[5]);
            inventariosize++;
        }
    }
    else if(numero <= 46){
        printf("Se ha encontrado: %s\n", objetos[6]);
        if(inventariosize < 11){
            strcpy(invent[inventariosize],objetos[6]);
            inventariosize++;
        }
    }
    else{
        printf("Se ha encontrado: %s\n", objetos[4]);
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
        player.health = 1400;
        player.agility = 100;
        player.stamina = 1200;
    }
    else if(clase == 2){
        strcpy(player.name, nombre);
        player.damage = 200;
        player.health = 2000;
        player.agility = 40;
        player.stamina = 1500;
    }
    else if(clase == 3){
        strcpy(player.name, nombre);
        player.damage = 500;
        player.health = 800;
        player.agility = 70;
        player.stamina = 2000;
    }
    else{
        strcpy(player.name, nombre);
        player.damage = 80;
        player.health = 3000;
        player.agility = 20;
        player.stamina = 1600;
    }
}

void bestiario(){
    int i, contador = 0;
    for(i = 0; i < 5; i++){
        if(Bossestats[i] <= 0){
            if(i == 0){
                printf("%s: %d %s \n\n",Bosses[i],ARES,Bossesdata[i]);    
            }
            else if(i == 1){
                printf("%s: %d %s \n\n",Bosses[i],BAGAN,Bossesdata[i]);
            }
            else if(i == 2){
                printf("%s: %d %s \n\n",Bosses[i],CULEX,Bossesdata[i]);
            }
            else if(i == 3){
                printf("%s: %d %s \n\n",Bosses[i],DOOM,Bossesdata[i]);
            }
            else{
                printf("%s: %d %s \n\n",Bosses[i],ENGOLO,Bossesdata[i]);
            }
        }
        else{
            contador += 1;
        }
    }
    if(contador == 5){
        printf("Ningun jefe ha sido derrotado\n");
    }
}

void menu(){
    int opcion1 = 0;
    while(opcion1 != 6 && flag == 0){
        printf("\n1. Explorar\n2. Avanzar\n3. Estadisticas\n4. Inventario\n5. Bestiario\n6. Salir\nElige una opcion > ");
        scanf("%d",&opcion1);
        switch(opcion1){
        case 1:
            printf("\nIniciando Exploracion...\n\n");
            explorar();
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
            inventario();
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

int main(){
    int option = 0;
    while(option != 3){
        printf("\n1. Juego Nuevo\n2. Continuar\n3. Salir\nElige una opcion > ");
        scanf("%d", &option); 
        switch (option){
        case 1:
            printf("\nIniciando Juego...\n\n");
            juegonuevo();
            menu();
            break;
        case 2:
            printf("\nReanudando Juego...\n\n");
            break;
        case 3:
            printf("\nSaliendo...\n\n");
            break; 
        default:
            printf("\nLa opcion ingresada no existe\n\n");
            break;
        }
    }
    return 0;
}