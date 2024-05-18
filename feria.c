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
    - Asignara posicion de manera aleatoria con funcion rand
POS CONDICIONES:
    - Retorna coordenadas con la estructura del struct coordenada_t
*/
coordenada_t asignar_posicion(){
    coordenada_t posicion;
    posicion.col = rand() % 20;
    posicion.fil = rand() % 20;
    return posicion;
}


/*
PRE CONDICIONES:
    - Inicializara los datos de Perry cargando su info inicial, asignando posicion inicial, etc.
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t y en base a eso se actualiza el struct de Perry
*/

void inicializar_personaje(juego_t* juego){
    srand((unsigned)time(NULL));

    juego->perry.vida = 3;
    juego->perry.energia = 100;
    juego->perry.camuflado = false;
    juego->perry.posicion = asignar_posicion();
}


/*
PRE CONDICIONES:
    - Inicializara los datos de las bombas cargando su info inicial, asignando su posicion inicial, etc.
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t, de lemeentos anteriormente inicializados y en base a eso se actualiza el struct de cada bomba
*/

void inicializar_bombas(bomba_t* bombas, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_bombas = TOPE_BOMBAS;

    for (int i = 0; i < juego->tope_bombas; i++){

        juego->bombas[i].posicion = asignar_posicion();

        while (juego->bombas[i].posicion.fil == juego->perry.posicion.fil && juego->bombas[i].posicion.col == juego->perry.posicion.col){
            juego->bombas[i].posicion = asignar_posicion();
        }
        
        juego->bombas[i].timer = rand() % 250 + 50;
        juego->bombas[i].desactivada = false;
    }    
}


/*
PRE CONDICIONES:
    - Inicializara los datos de las herramientas cargando su info inicial, asignando su posicion inicial, etc.
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t, de elementos anteriormente incializados y en base a eso se actualiza el struct de cada herramienta
*/

void inicializar_herramientas(herramienta_t* herramientas, juego_t* juego){
    srand((unsigned)time(NULL));

    bool posiciones_iguales = true;

    juego->tope_herramientas = TOPE_HERRAMIENTAS;

    for (int i = 0; i < juego->tope_herramientas; i++){

        bool posiciones_iguales = true;

        while(posiciones_iguales){

            juego->herramientas[i].posicion = asignar_posicion();
            posiciones_iguales = false;

            for (int j = 0; j < juego->tope_bombas; j++){

                if ((juego->herramientas[i].posicion.fil == juego->bombas[j].posicion.fil && juego->herramientas[i].posicion.col == juego->bombas[j].posicion.col)){
                    posiciones_iguales = true;
                }

                if (juego->herramientas[i].posicion.fil == juego->perry.posicion.fil && juego->herramientas[i].posicion.col == juego->perry.posicion.col){
                    posiciones_iguales = true;
                }
            }
        }
        
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
    - Inicializara los datos de los familiares de Perry cargando su info inicial, asignando su posicion inicial, etc.
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t, de elementos anteriormente incializados y en base a eso se actualiza el struct de cada familiar
*/

void inicializar_familiares(familiar_t * familiares, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_familiares = TOPE_FAMILIARES;

    for (int i = 0; i < juego->tope_familiares; i++){

        bool posiciones_iguales = true;

        while(posiciones_iguales){

            juego->familiares[i].posicion = asignar_posicion();
            posiciones_iguales = false;

            for (int j = 0; j < juego->tope_bombas; j++){

                if ((juego->familiares[i].posicion.fil == juego->bombas[j].posicion.fil && juego->familiares[i].posicion.col == juego->bombas[j].posicion.col)){
                    posiciones_iguales = true;
                }
            }

            for (int k = 0; k < juego->tope_herramientas; k++){

                if ((juego->familiares[i].posicion.fil == juego->herramientas[k].posicion.fil && juego->familiares[i].posicion.col == juego->herramientas[k].posicion.col)){
                    posiciones_iguales = true;
                }
            }

            if ((juego->familiares[i].posicion.fil == juego->perry.posicion.fil && juego->familiares[i].posicion.col == juego->perry.posicion.col)){
                    posiciones_iguales = true;
            }

        }

        
        
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
    - En feria.h ya se aclararon
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t y se actualiza el struct completo de juego inicializando a Perry, las bombas, herramientas, etc.
*/

void inicializar_juego(juego_t* juego){

    inicializar_personaje(juego);
    inicializar_bombas(juego->bombas, juego);
    inicializar_herramientas(juego->herramientas, juego);
    inicializar_familiares(juego->familiares, juego);
}


/*
PRE CONDICIONES:
    - En feria.h ya se aclararon
POS CONDICIONES:
    - Se pasa como parametro el struct juego de tipo juego_t y se muestra por pantalla el terreno actualizado junto con sus datos de valor
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
    - Se pasa por refrencia el struct juego de tipo juego_t y se actualiza el estado de camuflaje de Perry
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
    - En feria.h ya se aclararon
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t y la accion del usuario de tipo char. Luego, se ejecuta la accion en base a la entrada del usuario
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