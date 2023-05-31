#include "juego.h"
#include <ctype.h>
#include <windows.h>

    int abilitypoints = 0;
    int flag1 = 0;
    int zona = 0;
    Jugador player;
    char zonas[5][10] = {"Avalon", "El Dorado", "Atlantis", "El Olimpo", "Narnia"};
    

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

   

    /* Definicion Listas de Objetos */

    List* crearLista(){
        List* lista = (List*) malloc(sizeof(List));
        lista->head = NULL;
        lista->size = 0;
        return lista;
    }

    void agregarObjeto(List* lista, Objeto objeto) {
        Node* nuevoNodo = (Node*) malloc(sizeof(Node));
        nuevoNodo->object = objeto;
        nuevoNodo->next = NULL;

        if (lista->head == NULL) {
            lista->head = nuevoNodo;
        } 
        else {
            Node* nodoActual = lista->head;
            Node* nodoAnterior = NULL;

            // Recorremos la lista hasta encontrar la posición correcta
            while (nodoActual != NULL && strcmp(objeto.name, nodoActual->object.name) > 0) {
                nodoAnterior = nodoActual;
                nodoActual = nodoActual->next;
            }

            // Insertamos el nuevo nodo en la posición correcta
            if (nodoAnterior == NULL) {
                nuevoNodo->next = lista->head;
                lista->head = nuevoNodo;
            } 
            else {
                nodoAnterior->next = nuevoNodo;
                nuevoNodo->next = nodoActual;
            }
        }

        lista->size++;
    }

    void imprimirObjeto(Node* nodo){
        printf("Nombre: %s, Estadisticas: %d\n", nodo->object.name, nodo->object.stats);
    }

    void imprimirLista(List* lista){
        Node* nodoActual = lista->head;
        printf("--------------------------------------------------------\n");
        printf("|                      INVENTARIO                      |\n");
        int i = 1;
        while(nodoActual != NULL){
            printf("--------------------------------------------------------\n");
            printf("| %d. ", i);
            imprimirObjeto(nodoActual);
            nodoActual = nodoActual->next;
            i++;
        }printf("--------------------------------------------------------\n");
    }

    /*Funciones de juego */

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
        int damage;
        printf("Se ha encontrado con: %s\n" , monst[zona].name);
        printf("%s no te dejara avanzar sin antes luchar...\n", monst[zona].name);
        printf("\nYour health:%d  Boss health:%d\n", player.health2, monst[zona].health2);
        printf("Your stamina: %d\n",player.stamina);
        while(monst[zona].health2 > 0 && player.health2 > 0){ 
            int opcion2 = 0, probabilidadparry = rand() % 2, probabilidadgolpe = rand() % 3, probabilidadesquivar = rand() % 2, bossdamage = rand() % (100-150+1) + 100;
            if(player.stamina > 0){
                printf("\n1. Ataque ligero\n2. Ataque pesado\n3. Ataque magico\n4. Esquivar\n5. Parry\n6. Regenerar\nElige una opcion > ");
                scanf("%d",&opcion2);
                switch(opcion2){
                case 1:
                    monst[zona].health2 = monst[zona].health2 - player.damage;
                    player.stamina -= 375;
                    break;
                case 2:
                    if(probabilidadgolpe != 0){
                        printf("\nAtaque exitoso\n");
                        damage = player.damage * 2;
                        monst[zona].health2 = monst[zona].health2 - damage;
                    }   
                    else{
                        printf("\nAtaque fallido\n");
                    }
                    player.health2 = player.health2 - bossdamage;
                    player.stamina -= 390;  
                    break;
                case 3:
                    if(player.clasep == 3){
                        damage = player.damage * 2.5;
                        monst[zona].health2 = monst[zona].health2 - damage;
                    }
                    else
                        printf("La clase de tu jugador es incompatible con magia\n");
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
                        monst[zona].health2 -= player.damage*4;
                    }
                    else{
                        printf("\nParry fallido\n"); 
                    }
                    player.stamina -= 500;
                    break;
                case 6:
                    player.stamina += 500;
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
            printf("\nYour health:%d  Boss health:%d\n", player.health2, monst[zona].health2);
            printf("Your stamina: %d\n",player.stamina);
        
        }
        if(player.health2 <= 0){
            flag1 = 1;
        }
        else if(monst[zona].health2 <= 0){
            printf("\nHas derrotado a %s\n", monst[zona].name);
            printf("Has sido recompensado con %d puntos de habilidad\n\n", monst[zona].rewards);
            abilitypoints += monst[zona].rewards;      
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
    
    void avanzar(ListGraf* graph, int *zona){
        print_simple_list(graph[*zona]);
        int caso;
        int flag = 1;
        while(flag == 1){
            if(*zona == 0){
                printf("Elige una opcion > ");
                scanf("%d", &caso);
                if(caso == 1){   
                    *zona = 1;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[1]);
                }
                else if(caso == 2){
                    *zona = 2;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[2]);
                }
                else{
                    printf("No hay camino a esa zona\n");
                }
            }
            else if(*zona == 1){
                printf("Elige una opcion > ");
                scanf("%d", &caso);
                if(caso == 0){   
                    *zona = 0;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[0]);
                }
                else if(caso == 3){
                    *zona = 3;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[3]);
                }
                else if(caso == 4){
                    *zona = 4;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[4]);
                }
                else{
                    printf("No hay camino a esa zona\n");
                }
            }
            else if(*zona == 2){
                printf("Elige una opcion > ");
                scanf("%d", &caso);
                if(caso == 0){   
                    *zona = 0;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[0]);
                }
                else if(caso == 4){
                    *zona = 4;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[4]);
                }
                else{
                    printf("No hay camino a esa zona\n");
                }
            }
            else if(*zona == 3){
                printf("Elige una opcion > ");
                scanf("%d", &caso);
                if(caso == 1){   
                    *zona = 1;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[1]);
                }
                else{
                    printf("No hay camino a esa zona\n");
                }
            }
            else if(*zona == 4){
                printf("Elige una opcion > ");
                scanf("%d", &caso);
                if(caso == 1){   
                    *zona = 1;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[1]);
                }
                else if(caso == 2){
                    *zona = 2;
                    flag = 0;
                    printf("\n");
                    printf("-------------|----|----|-\n");
                    printf("-------------)_)--)_)--)_)\n");
                    printf("------------)___))___))___)\n");
                    printf("-----------)____)____)_____)\n");
                    printf("---------_____|____|____|_____\n");
                    printf("---------\\-------------------/\n");
                    printf("--^^^^^-^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("----^^^^------^^^^-----^^^----^\n");
                    printf("---------^^^^------^^^\n");
                    printf("Navegando hacia la nacion de %s\n\n", zonas[2]);
                }
                else{
                    printf("No hay camino a esa zona\n");
                }
            }
        }
    }

    void juegonuevo(){
        char nombre[30];
        getchar();
        int clase;
        printf("Digite el nombre de su personaje > ");
        fgets(nombre, sizeof(nombre), stdin);
        if (nombre[strlen(nombre) - 1] == '\n') {
                nombre[strlen(nombre) - 1] = '\0';
            }
        while(isdigit(nombre[0])){
            printf("\n%cError! %c Se ha ingresado un numero en lugar de un string\n", 173, 175);
            printf("\nDigite el nombre de su personaje > ");
            fgets(nombre, sizeof(nombre), stdin);
            if (nombre[strlen(nombre) - 1] == '\n') {
                nombre[strlen(nombre) - 1] = '\0';
            }
        }
        printf("\n%cBienvenido %s!\n", 173, nombre);
        printf("\n1. Asesino\n");
        printf("2. Guerrero\n");
        printf("3. Mago\n");
        printf("4. Tanque\n");
        printf("Seleccione su clase > ");
        scanf("%d", &clase);
        if(clase == 1){
            printf("\nHas seleccionado la clase -> Asesino\n\n");
            Sleep(2000);
            system("cls");
            printf("%cBienvenido a la ciudad de Avalon!\n", 173);
            printf("Aqui comienza tu aventura...\n");
            Sleep(3000);
            system("cls");
            strcpy(player.name, nombre);
            player.damage = 400;
            player.health1 = 1400;
            player.health2 = 1400;
            player.agility = 100;
            player.stamina = 1200;
            player.clasep = 1;
        }
        else if(clase == 2){
            printf("\nHas seleccionado la clase -> Guerrero\n");
            Sleep(2000);
            system("cls");
            printf("%cBienvenido a la ciudad de Avalon!\n", 173);
            printf("Aqui comienza tu aventura...\n");
            Sleep(3000);
            system("cls");
            strcpy(player.name, nombre);
            player.damage = 200;
            player.health1 = 2000;
            player.health2 = 2000;
            player.agility = 40;
            player.stamina = 1500;
            player.clasep = 2;
        }
        else if(clase == 3){
            printf("\nHas seleccionado la clase -> Mago\n");
            Sleep(2000);
            system("cls");
            printf("%cBienvenido a la ciudad de Avalon!\n", 173);
            printf("Aqui comienza tu aventura...\n");
            Sleep(3000);
            system("cls");
            strcpy(player.name, nombre);
            player.damage = 500;
            player.health1 = 800;
            player.health2 = 800;
            player.agility = 70;
            player.stamina = 2000;
            player.clasep = 3;
        }
        else{
            printf("\nHas seleccionado la clase -> Tanque\n");
            Sleep(2000);
            system("cls");
            printf("%cBienvenido a la ciudad de Avalon!\n", 173);
            printf("Aqui comienza tu aventura...\n");
            Sleep(3000);
            system("cls");
            strcpy(player.name, nombre);
            player.damage = 80;
            player.health1 = 3000;
            player.health2 = 3000;
            player.agility = 20;
            player.stamina = 1600;
            player.clasep = 4;
        }
    }

    void bestiario(){
        int i, contador = 0;
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

    /*Funcion del menu*/

    void menu(){
        List* inventario = crearLista();
        int opcion1 = 0;
        ListGraf graph[5];
        create_graph(graph);   
        add_node_to_graph(graph, 0, 1);
        add_node_to_graph(graph, 0, 2);
        add_node_to_graph(graph, 1, 0);
        add_node_to_graph(graph, 1, 3);
        add_node_to_graph(graph, 1, 4);
        add_node_to_graph(graph, 2, 0);
        add_node_to_graph(graph, 2, 4);
        add_node_to_graph(graph, 3, 1);
        add_node_to_graph(graph, 4, 1);
        add_node_to_graph(graph, 4, 2);
        while(opcion1 != 6 && flag1 == 0){
            printf("Te encuentras en %s\n", zonas[zona]);
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
                if(player.health2 > 0)
                    avanzar(graph, &zona);
                else{
                    printf("Has sido derrotado\n");
                    monst[zona].health2 = monst[zona].health1;
                    zona = 0;
                }
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
        flag1 = 0;
    }

    /* Definicion funciones del grafo */

    NodeGraf* create_vertex_node(int zone) {
        NodeGraf* node = (NodeGraf*)malloc(sizeof(NodeGraf));
        node->zone = zone;
        node->next = NULL;
    
        return node;
    }

    ListGraf create_simple_list() {
        ListGraf list;
        list.size = 0;
        list.head = NULL;
    
        return list;
    }

    void add_node_to_list(ListGraf* list, int zone) {
        NodeGraf* node = create_vertex_node(zone);
    
        NodeGraf* temp = list->head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
    
        temp->next = node;
        list->size += 1;
    }

    void print_simple_list(ListGraf list) {
        NodeGraf* temp = list.head;
    
        if(temp->zone == 0){
            printf("Estas en Avalon: Puedes ir a -> 1.El Dorado 2.Atlantis\n");
        }
        else if(temp->zone == 1){
            printf("Estas en El Dorado: Puedes ir a -> 0.Avalon 3.El Olimpo 4.Narnia\n");
        }
        else if(temp->zone == 2){
            printf("Estas en Atlantis: Puedes ir a -> 0.Avalon 4.Narnia\n");
        }
        else if(temp->zone == 3){
            printf("Estas en El Olimpo: Puedes ir a -> 1.El Dorado\n");
        }
        else if(temp->zone == 4){
            printf("Estas en Narnia: Puedes ir a -> 1.El Dorado 2.Atlantis\n");
        }
        
    }

    void create_graph(ListGraf* arr) {
        for(int i = 0; i < VERTEX_NUMBER; i++) {
            ListGraf list = create_simple_list();
            list.head = create_vertex_node(i);
            list.size = 1;
        
            arr[i] = list;
        }
    }

    void add_node_to_graph(ListGraf* arr, int node, int zone) {
        ListGraf *list = &arr[node];
        add_node_to_list(list, zone);
    }

    void print_graph(ListGraf* graph) {
        for(int i = 0; i < VERTEX_NUMBER; i++) {
            print_simple_list(graph[i]);
            printf("\n");
        }
    }