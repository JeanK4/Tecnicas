/* Integrantes
- Kevin Yavari Yoshioka
- Julian Galvis
- Jean Karlo */
#include "juego.h"
#include <windows.h>

int main(){

    printf("\n");
    printf("\n");
    printf("\n");

    char nombreG[5][89] = {"                                                               N   N  IIIII  OOOO  H   H\n",
                           "                                                               NN  N    I   O    O H   H\n",
                           "                                                               N N N    I   O    O HHHHH\n",
                           "                                                               N  NN    I   O    O H   H\n",
                           "                                                               N   N  IIIII  OOOO  H   H\n"};
    
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 89; j++) {
            printf("%c", nombreG[i][j]);
            fflush(stdout);
            Sleep(9);
        }
    }

    


    printf("\n");
    printf("\n");
    printf("                                  .-------------------------------------------------------------------------------------.\n");
    printf("                                  |                                                                                     |\n");
    printf("                                  |                                                                                     |\n");

    printf("                                  |    BBBBB   IIIII  EEEEEEE NN   NN V       V EEEEEEE NN   NN IIIII  DDDDD   OOOO     |   \n");
    printf("                                  |    B    B    I    E       NNN  NN  V     V  E       NNN  NN   I    D    D O    O    |     \n");
    printf("                                  |    BBBBB     I    EEEEE   NN N NN   V   V   EEEEE   NN N NN   I    D    D O    O    |   \n");
    printf("                                  |    B    B    I    E       NN  NNN    V V    E       NN  NNN   I    D    D O    O    |      \n");
    printf("                                  |    BBBBB   IIIII  EEEEEEE NN   NN     V     EEEEEEE NN   NN IIIII  DDDDD   OOOO     |    \n");

    printf("                                  |                                                                                     |     \n");
    printf("                                  |                                                                                     |     \n");
    printf("                                  |      .--.                                                                           |     \n");

    printf("                                  |     |    |                              |>>>                                        |\n");
    printf("                                  |      '--'               |>>>            |                |>>>                       | \n");
    printf("                                  |                         |           _  _|_  _            |                          | \n");
    printf("                                  |                     _  _|_  _      | |_| |_| |       _  _|_  _                      |\n");
    printf("                                  |                    | |_| |_| |     \\ .      /       | |_| |_| |                     |\n");
    printf("                                  |                    \\ .       /      \\  ,   /        \\ .       /                     | \n");
    printf("                                  |                     \\   ,   /        | .   |         \\   ,   /                      | \n");
    printf("                                  |                      | .   |       .-'.___.'-.        | .   |                       |\n");
    printf("                                  |                    .-'.___.'-.     /_________\\      .-'.___.'-.                     | \n");
    printf("                                  |                    /_________\\   _|___________|_    /_________\\                     |\n");
    printf("                                  |                  _|___________|_``|   |   |   | |`_|___________|_                   |\n");
    printf("                                  |            .--'` |   |   |   | |  |   |   |   | |  |   |   |   | |`'--.             |\n");
    printf("                                  |           /|     |   |   |   | |  |   |   |   | |  |   |   |   | |    |\\            |\n");
    printf("                                  |  .-------' |     |   |   |   | |  |   |   |   | |  |   |   |   | |    | '--------.  |\n");
    printf("                                  | /          |     |   |   |   | |  |   |   |   | |  |   |   |   | |    |           \\ |\n");
    printf("                                  '/___________|___.-'.__.'._.-'__.'.-'.__.'._.-'__.'-.'.__.'._.-'__.'-.__|____________\\'\n");

    printf("\n");
    printf("\n");
    printf("\n");

    ListGraf graph[VERTEX_NUMBER];
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
    
    print_graph(graph);



    int option = 0;
    while(option != 3){
        printf("\n1. Juego Nuevo\n2. Continuar\n3. Salir\nElige una opcion > ");
        scanf("%d", &option); 
        switch (option){
        case 1:
            printf("\nIniciando Juego...\n\n");
            system("cls");
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