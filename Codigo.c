/* Integrantes
- Kevin Yavari Yoshioka
- Julian Galvis
- Jean Karlo */
/* Queda pendiente el inventario, colocar el limite de vida y stamina en curación, en el combate añadir mensajes
claros de lo que sucede, añadir medidas de posibles errores*/
/* Librerias */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estructuras */
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

/* Arreglos */

char objetos[7][15] = {"antorcha","espada","escudo","fuente","nada","pocion de vida","baston magico"};
char invent[10][15] = {"","","","","","","","","",""};

/* Variables */

int inventariosize = 0;
int abilitypoints = 0;
int flag = 0;
Jugador player;
Monstruo Ares;
Monstruo Bagan;
Monstruo Culex;
Monstruo Doom;
Monstruo Engolo;

/* Prototipos */
void menu();
void juegonuevo();
void bestiario();
void inventario();
void explorar();
void estadisticas();
void bosses();

/* Definiciones */

void bosses(){
    /* Ares */    
    strcpy(Ares.name, "Ares");
    strcpy(Ares.data, "Monstruo hecho de lava, debil contra la magia");
    Ares.health1 = 2500;
    Ares.health2 = 2500;
    Ares.rewards = 3;
    /* Bagan */
    strcpy(Bagan.name, "Bagan");
    strcpy(Bagan.data, "Mago que domina el agua, debil contra ataque ligero");
    Bagan.health1 = 3000;
    Bagan.health2 = 3000;
    Bagan.rewards = 4;
    /* Culex */
    strcpy(Culex.name, "Culex");
    strcpy(Culex.data, "Asesino de la aldea perdida, debil contra ataque pesados");
    Culex.health1 = 2000;
    Culex.health2 = 2000;
    Culex.rewards = 2;
    /* Doom */
    strcpy(Doom.name, "Doom");
    strcpy(Doom.data, "Un ciclope gigante, sus ataques son lentos");
    Doom.health1 = 3500;
    Doom.health2 = 3500;
    Doom.rewards = 5;
    /* Engolo */
    strcpy(Engolo.name, "Engolo");
    strcpy(Engolo.data, "Un duende asesino de niños, no tiene debilidad");
    Engolo.health1 = 10000;
    Engolo.health2 = 10000;
    Engolo.rewards = 10;
}

void inventario(){
    for(int i = 0; i < 10; i++)
        printf("%d. %s\n", i+1, invent[i]);
}

void estadisticas(){
    int opcion3, answer, bandera = 0;
    while(abilitypoints > 0 && bandera == 0){
        printf("Estadisticas de %s:\n", player.name);
        printf("Health = %d\n", player.health1);
        printf("Damage = %d\n", player.damage);
        printf("Agility = %d\n", player.agility);
        printf("Stamina = %d\n", player.stamina);
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
    Monstruo* Variable;
    if(boss == 0){
        Variable = &Ares;
    }
    else if(boss == 1){
        Variable = &Bagan;
    }
    else if(boss == 2){
        Variable = &Culex;
    }
    else if(boss == 3){
        Variable = &Doom;
    }
    else{
        Variable = &Engolo;
    }
    printf("Se ha encontrado con: %s\n" , Variable->name);
    while(Variable->health2 > 0 && player.health2 > 0){ 
        int opcion2 = 0, probabilidadparry = rand() % 2, probabilidadgolpe = rand() % 3, probabilidadesquivar = rand() % 2, bossdamage = rand() % (100-150+1) + 100;
        if(player.stamina > 0){
            printf("\n1. Ataque ligero\n2. Ataque pesado\n3. Ataque magico\n4. Esquivar\n5. Parry\n6. Regenerar\n7. Escapar\nElige una opcion > ");
            scanf("%d",&opcion2);
        }
        else{
            printf("\nSin estamina, turno Perdido\n");
        }
        switch(opcion2){
        case 1:
            Variable->health2 = Variable->health2 - player.damage;
            player.stamina = player.stamina - 375;
            
            break;
        case 2:
            if(probabilidadgolpe != 0){
                printf("\nAtaque exitoso\n");
                damage = player.damage * 2;
                Variable->health2 = Variable->health2 - damage;
            }
            else{
                printf("\nAtaque fallido\n");
            }
            player.health2 = player.health2 - bossdamage;
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
                Variable->health2 -= player.damage*4;
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
        player.health2 = player.health2 - bossdamage;
        printf("\nYour health:%d  Boss health:%d\n", player.health2, Variable->health2);
        printf("Your stamina: %d\n",player.stamina);
    
    }
    if(player.health2 < 0){
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
    for(i = 0; i < 5; i++){
        if(i == 0 && Ares.health2 <= 0){
            contador++;
        }
        else if(i == 1 && Bagan.health2 <= 0){
            contador++;
        }
        else if(i == 2 && Culex.health2 <= 0){
            contador++;
        }
        else if(i == 3 && Doom.health2 <= 0){
            contador++;
        }
        else if(i == 4 && Engolo.health2 <= 0){
            contador++;
        }
    }
    Monstruo* jefes;
    jefes = (Monstruo*)malloc(contador*sizeof(Monstruo));
    for(i = 0; i < contador; i++){
        if(Ares.health2 <= 0 && aresf == 0){
            jefes[i] = Ares;
            aresf = 1;
        }
        else if(Bagan.health2 <= 0 && baganf == 0){
            jefes[i] = Bagan;
            baganf = 1;
        }
        else if(Culex.health2 <= 0 && culexf == 0){
            jefes[i] = Culex;
            culexf = 1;
        }
        else if(Doom.health2 <= 0 && doomf == 0){
            jefes[i] = Doom;
            doomf = 1;
        }
        else if(Engolo.health2 <= 0 && engolof == 0){
            jefes[i] = Engolo;
            engolof = 1;
        }
    }
    if(contador == 0){
        printf("Ningun jefe ha sido derrotado\n");
    }
    else{
        printf("-- BESTIARIO --\n\n");
        for(i = 0; i < contador; i++){
            printf("Jefe #%d\n", i+1);
            printf("Nombre: %s\n", jefes[i].name);
            printf("Vida Total: %d\n", jefes[i].health1);
            if(i != contador-1)
                printf("Informacion: %s\n\n", jefes[i].data);
            else{
                printf("Informacion: %s\n", jefes[i].data);
            }
        }
    }
    free(jefes);
    printf("\n");
    system("pause");
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
            bosses();
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