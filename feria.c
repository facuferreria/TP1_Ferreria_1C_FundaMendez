#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "feria.h"

#define FILAS 20
#define COLUMNAS 20
#define ARRIBA 'W'
#define DERECHA 'D'
#define ABAJO 'S'
#define IZQUIERDA 'A'
#define CAMUFLAJE 'Q'

const char PERRY = 'P';
const char BOMBAS = 'B';
const char HERRAMIENTAS = 'T';
const char GOLOSINAS = 'G';
const char SOMBREROS = 'S';
const char PHINEAS = 'H';
const char FERB = 'F';
const char CANDACE = 'C';

const int GANO = 1;
const int PERDIO = -1;
const int SIGUE_JUGANDO = 0;

const int TOPE_BOMBAS = 10;
const int TOPE_GOLOSINAS = 5;
const int TOPE_HERRAMIENTAS = 8;
const int TOPE_FAMILIARES = 3;



/*
PRE CONDICIONES:
    - No recbe nada coo parametro
POS CONDICIONES:
    - Devuelve struct posicion con coordenadas aleatorias
*/
coordenada_t asignar_posicion(){
    coordenada_t posicion;
    posicion.col = rand() % 20;
    posicion.fil = rand() % 20;
    return posicion;
}


/*
PRE CONDICIONES:
    - Pasamos como parametro el struct juego por referencia
POS CONDICIONES:
    - Inicializa el struct de Perry
*/

void inicializar_personaje(juego_t* juego, char matriz_aux[FILAS][COLUMNAS]){

    juego->perry.vida = 3;
    juego->perry.energia = 100;
    juego->perry.camuflado = false;
    juego->perry.posicion = asignar_posicion();

    matriz_aux[juego->perry.posicion.fil][juego->perry.posicion.col] = PERRY;
}


/*
PRE CONDICIONES:
    - Pasamos como parametro el struct bombas y el struct juego por referencia
POS CONDICIONES:
    - Inicializa todas las bombas del vector bombas.
*/

void inicializar_bombas(bomba_t* bombas, juego_t* juego, char matriz_aux[FILAS][COLUMNAS]){

    juego->tope_bombas = TOPE_BOMBAS;

    for (int i = 0; i < juego->tope_bombas; i++){

        juego->bombas[i].posicion = asignar_posicion();
        
        while (matriz_aux[juego->bombas[i].posicion.fil][juego->bombas[i].posicion.col] != '.'){
            juego->bombas[i].posicion = asignar_posicion();
        }

        matriz_aux[juego->bombas[i].posicion.fil][juego->bombas[i].posicion.col] = BOMBAS;

        
        juego->bombas[i].timer = rand() % 250 + 50;
        juego->bombas[i].desactivada = false;
    }    
}


/*
PRE CONDICIONES:
    - Pasamos como parametro el struct herramientas y el struct juego por referencia
POS CONDICIONES:
    - Inicializa todas las herramientas del vector herramientas.
*/

void inicializar_herramientas(herramienta_t* herramientas, juego_t* juego,  char matriz_aux[FILAS][COLUMNAS]){

    juego->tope_herramientas = TOPE_HERRAMIENTAS;

    for (int i = 0; i < juego->tope_herramientas; i++){

        juego->herramientas[i].posicion = asignar_posicion();

        while (matriz_aux[juego->herramientas[i].posicion.fil][juego->herramientas[i].posicion.col] != '.'){
            juego->herramientas[i].posicion = asignar_posicion();
        }

        matriz_aux[juego->herramientas[i].posicion.fil][juego->herramientas[i].posicion.col] = HERRAMIENTAS;

        
        if (i < TOPE_GOLOSINAS){ 
            juego->herramientas[i].tipo = GOLOSINAS;
        } 
        
        else{
            juego->herramientas[i].tipo = SOMBREROS;
        }
    }    
}


/*
PRE CONDICIONES:
    - Pasamos como parametro el struct familiares y el struct juego por referencia
POS CONDICIONES:
    - Inicializa todas los familiares del vector familiares.
*/

void inicializar_familiares(familiar_t * familiares, juego_t* juego,  char matriz_aux[FILAS][COLUMNAS]){
    srand((unsigned)time(NULL));

    juego->tope_familiares = TOPE_FAMILIARES;

    for (int i = 0; i < juego->tope_familiares; i++){

        juego->familiares[i].posicion = asignar_posicion();


        while (matriz_aux[juego->familiares[i].posicion.fil][juego->familiares[i].posicion.col] != '.'){
            juego->familiares[i].posicion = asignar_posicion();
        }


        matriz_aux[juego->familiares[i].posicion.fil][juego->familiares[i].posicion.col] = HERRAMIENTAS;

        
        if (i ==  0){ 
            juego->familiares[i].inicial_nombre = PHINEAS;
        } 

        else if (i == 1)
        {
            juego->familiares[i].inicial_nombre = FERB;
        }
        
        
        else {
            juego->familiares[i].inicial_nombre = CANDACE;
        }
    }    

}


/*
PRE CONDICIONES:
    - 
POS CONDICIONES:
    - Inicializa todos los datos iniciales del juego
*/

void inicializar_juego(juego_t* juego){

    char matriz_aux[FILAS][COLUMNAS];

    for(int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz_aux[i][j] = '.';
        }
    }

    inicializar_personaje(juego, matriz_aux);
    inicializar_bombas(juego->bombas, juego, matriz_aux);
    inicializar_herramientas(juego->herramientas, juego, matriz_aux);
    inicializar_familiares(juego->familiares, juego, matriz_aux);
}


/*
PRE CONDICIONES:
    - 
POS CONDICIONES:
    - Imprime el terreno por pantalla
*/

void imprimir_terreno(juego_t juego){

    char terreno[FILAS][COLUMNAS];

    for(int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            terreno[i][j] = '.';
        }
    }
    
   
    terreno[juego.perry.posicion.fil][juego.perry.posicion.col] = PERRY;


    for (int i = 0; i < juego.tope_bombas; i++){
        terreno[juego.bombas[i].posicion.fil][juego.bombas[i].posicion.col]= BOMBAS; 
    }

    for (int i = 0; i < juego.tope_herramientas; i++){
        terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;
    }

    for (int i = 0; i < juego.tope_familiares; i++){
        terreno[juego.familiares[i].posicion.fil][juego.familiares[i].posicion.col] = juego.familiares[i].inicial_nombre;
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%c ", terreno[i][j]);
        }
        printf("\n");
    }
}


/*
PRE CONDICIONES:
    - Se cambiara el estado de camuflaje de Perry en base a si estaba camuflado o no
POS CONDICIONES:
    - Cambia el estado de camuflaje de Perry
*/

void camuflar_personaje(juego_t* juego){

    if (juego->perry.camuflado == false){
        juego->perry.camuflado = true;
    }
    else{
        juego->perry.camuflado = false;
    }
}



/*
PRE CONDICIONES:
    - 
POS CONDICIONES:
    - Se realiza una jugada en base a lo que eligio el usuario
*/

void realizar_jugada(juego_t* juego, char accion){

    switch (accion){
            case ARRIBA:
                if (juego->perry.posicion.fil > 0){

                    juego->perry.posicion.fil -= 1;
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                }
            break;

            case IZQUIERDA:
                if (juego->perry.posicion.col > 0){

                    juego->perry.posicion.col -= 1;
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                }
            break;

            case ABAJO:
                if (juego->perry.posicion.fil < 19){

                    juego->perry.posicion.fil += 1;
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                }
            break;

            case DERECHA:
                if (juego->perry.posicion.col < 19){

                    juego->perry.posicion.col += 1;
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                }
            break;

            case CAMUFLAJE:
                camuflar_personaje(juego);
            break;
    }
    
}



/*
PRE CONDICIONES:
    - En feria.h ya se aclararon
POS CONDICIONES:
    - Se pasa como parametro el juego de tipo juego_t y se retorn un int que nos determina el estado actual del juego
*/

int estado_juego(juego_t juego){

    int estado_actual = 0;

    for (int i = 0; i < juego.tope_bombas; i++){
        if (juego.bombas[i].desactivada == true && juego.perry.vida > 0){
            estado_actual = GANO;
        }
        else if (juego.perry.vida <= 0){
            estado_actual = PERDIO;
        }
        else{
            estado_actual = SIGUE_JUGANDO;
        }
    }

    return estado_actual;
}