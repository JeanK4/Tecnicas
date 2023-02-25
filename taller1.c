/* Integrantes
- Kevin Yavari Yoshioka
- Julian Galvis
- Jean Karlo */

/* Librerias */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Constantes definidas */ 
#define BOSSES 5
#define INV 10
#define ARES 2500
#define BAGAN 3000
#define CULEX 2000
#define DOOM 3500
#define ENGOLO 10000
#define ESTAMINA 1500

/* Arreglos */
int vidapj = 10000, damagepj = 100, agility = 50, velocity = 60, stamina = 1500;
int Bossestats[BOSSES] = {2500,3000,2000,3500,10000};
char Bosses[BOSSES][7] = {"Ares","Bagan","Culex","Doom","Engolo"};
char Bossesdata[BOSSES][70] = {"Monstruo hecho de lava, debil contra la magia","Mago que domina el agua, debil contra ataque ligero","Asesino de la aldea perdida, debil contra ataque pesados","Un ciclope gigante, sus ataques son lentos","Un duende asesino de niños, no tiene debilidad"};
char objetos[7][15] = {"antorcha","espada","escudo","fuente","nada","pocion de vida","baston magico"};
char inv[INV][15];

/* Prototipos */
void menu();
void juegonuevo();
void bestiario();
void inventario();
void explorar();

/* Definiciones */
void inventario(){
    int i;
    for(i = 0; i < INV; i++){
        printf("%s\n", inv[i]);
    }
}

void combate(){
    srand(time(0));
    int damage, boss = rand() % 5, flag = 1;
    printf("Se ha encontrado con: %s\n" ,Bosses[boss]);    
    while(Bossestats[boss] > 0 && vidapj > 0){ 
        int opcion2 = 8, probabilidadgolpe = rand() % 3, probabilidadesquivar = rand() % 2, bossdamage = rand() % (100-150+1) + 100;
        if(stamina > 0){
            printf("\n1. Ataque ligero\n2. Ataque pesado\n3. Ataque magico\n4. Esquivar\n5. Parry\n6. Regenerar\n7. Escapar\nElige una opcion > ");
            scanf("%d",&opcion2);
        }
        else{
            printf("\nSin estamina, turno Perdido\n");
        }
        switch(opcion2){
        case 1:
            damage = damagepj;
            Bossestats[boss] = Bossestats[boss] - damage;
            stamina = stamina - 375;
            
            break;
        case 2:
            if(probabilidadgolpe != 0){
                printf("\nAtaque exitoso\n");
                damage = damagepj * 2;
                Bossestats[boss] = Bossestats[boss] - damage;
            }
            else{
                printf("\nAtaque fallido\n");
            }
            vidapj = vidapj - bossdamage;
            stamina = stamina - 410;
            
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
            stamina = stamina - 450;
            
            break;
        case 5:
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
        stamina = stamina + (ESTAMINA * 0,25);
        vidapj = vidapj - bossdamage;
        printf("\nYour health:%d  Boss health:%d\n", vidapj, Bossestats[boss]);
        printf("Your stamina: %d\n",stamina);
    
    }
}

void explorar(){
    srand(time(0));
    char valor[3];
    int counter = 0, numero = rand() % 101;
    if(numero <= 5){
        printf("Se ha encontrado: %s\n", objetos[0]);
    }
    else if(numero <=12){
        printf("Se ha encontrado: %s\n", objetos[1]);   
    }
    else if(numero <= 19){
        printf("Se ha encontrado: %s\n", objetos[2]);   
    }
    else if(numero <= 24){
        printf("Se ha encontrado: %s\n", objetos[3]);
    }
    else if(numero <= 39){
        printf("Se ha encontrado: %s\n", objetos[5]);
    }
    else if(numero <= 46){
        printf("Se ha encontrado: %s\n", objetos[6]);
    }
    else{
        printf("Se ha encontrado: %s\n", objetos[4]);
    }
    if(numero <= 46 && counter < 10){
        if(numero <= 5){
            inv[0], &objetos[0];
            counter++;
        }
        else if(numero <= 12){
            inv[1], &objetos[1];
            counter++;
        }
        else if(numero <= 19){
            inv[2], &objetos[2];
            counter++;
        }
        else if(numero <= 24){
            inv[3], &objetos[3];
            counter++;
        }
        else if(numero <= 39){
            inv[5], &objetos[5];
            counter++;
        }
        else{
            inv[6], &objetos[6];
            counter++;
        }
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
    char nombre, class;
    printf("Digite el nombre de su personaje\n");
    scanf("%s", &nombre);
    printf("- Asesino\n");
    printf("- Guerrero\n");
    printf("- Mago\n");
    printf("- Tanque\n");
    printf("Seleccione su clase:\n");
    scanf("%s",&class);
}

void bestiario(){
    int i, contador = 0;
    for(i = 0; i < BOSSES; i++){
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
    if(contador == BOSSES){
        printf("Ningun jefe ha sido derrotado\n");
    }
}

void menu(){
    int opcion1 = 0;
    while(opcion1 != 6){
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
