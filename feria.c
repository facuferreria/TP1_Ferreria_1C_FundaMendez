#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "feria.h"

#define FILAS 20
#define COLUMNAS 20

coordenada_t asignar_posicion(){
    coordenada_t posicion;
    posicion.col = rand() % 20;
    posicion.fil = rand() % 20;
    return posicion;
}

void inicializar_personaje(personaje_t* personaje){
    srand((unsigned)time(NULL));

    personaje->vida = 3;
    personaje->energia = 100;
    personaje->camuflado = false;
    personaje->posicion = asignar_posicion();
    printf("Vida del personaje: %d\n", personaje->vida);
    printf("Posicion inicial personaje: %d, %d\n", personaje->posicion.fil, personaje->posicion.col);
}

void inicializar_bombas(bomba_t* bombas, int tope_bombas){
    srand((unsigned)time(NULL));

    tope_bombas = 10;

    for (int i = 0; i < tope_bombas; i++){

        bombas->posicion = asignar_posicion();
        bombas->timer = rand() % 250 + 50;
        bombas->desactivada = false;

        printf("Posicion inicial bomba %d: %d, %d con respectivo timer de %d\n", i, bombas->posicion.fil, bombas->posicion.col, bombas->timer);
    }    
}

void inicializar_herramientas(herramienta_t* herramientas, int tope_herramientas){
    srand((unsigned)time(NULL));

    tope_herramientas = 8;

    for (int i = 0; i < tope_herramientas; i++){

        herramientas->posicion = asignar_posicion();
        
        if (i < 5){ 
            herramientas->tipo = 'G';
        } 
        
        else {
            herramientas->tipo = 'S';
        }
        
        printf("Posicion inicial herramientas %d: %d, %d de tipo %c\n", i, herramientas->posicion.fil, herramientas->posicion.col, herramientas->tipo);
    }    
}


void inicializar_familiares(familiar_t * familiares, int tope_familiares){
    srand((unsigned)time(NULL));

    tope_familiares = 3;

    for (int i = 0; i < tope_familiares; i++){

        familiares->posicion = asignar_posicion();
        
        if (i ==  0){ 
            familiares->inicial_nombre = 'H';
        } 

        else if (i == 1)
        {
            familiares->inicial_nombre = 'F';
        }
        
        
        else {
            familiares->inicial_nombre = 'C';
        }
        
        printf("Posicion inicial familiar %d: %d, %d de familiar %c\n", i, familiares->posicion.fil, familiares->posicion.col, familiares->inicial_nombre);
    }    
}

void inicializar_juego(juego_t* juego){
    
    inicializar_personaje(&(juego->perry));
    inicializar_bombas((juego->bombas), (juego->tope_bombas));
    inicializar_herramientas((juego->herramientas), (juego->tope_herramientas));
    inicializar_familiares((juego->familiares), (juego->tope_familiares));
}


void imprimir_terreno(juego_t juego){
     char matriz[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = '.';
        }
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

void validar_posicion(posicion){
        /*for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = '.';
        }
    }*/
}