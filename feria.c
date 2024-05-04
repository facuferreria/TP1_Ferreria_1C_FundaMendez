#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "feria.h"

#define FILAS 20
#define COLUMNAS 20

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
    - Verificara el estado de Perry para saber si esta camuflado o no
POS CONDICIONES:
    - Se le pasa un booleano como parametro y en base a el, dependiendo que sea, devolvera el estado actual de si Perry esta camuflado
*/

void verificar_camuflaje(bool esta_camuflado){
    if (esta_camuflado == true){
        printf("\nCamuflaje: Activado\n");
    }
    else{
        printf("\nCamuflaje: Desactivado\n");
    }
    
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

void inicializar_bombas(bomba_t* bombas, personaje_t* personaje, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_bombas = 10;

    for (int i = 0; i < juego->tope_bombas; i++){

        do
        {
            juego->bombas[i].posicion = asignar_posicion();
        } while (bombas->posicion.fil == personaje->posicion.fil && bombas->posicion.col == personaje->posicion.col);
        
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

void inicializar_herramientas(herramienta_t* herramientas, bomba_t* bombas, personaje_t* personaje, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_herramientas = 8;

    for (int i = 0; i < juego->tope_herramientas; i++){

        do
        {
            juego->herramientas[i].posicion = asignar_posicion();
        } while ((herramientas->posicion.fil == bombas->posicion.fil && herramientas->posicion.col == bombas->posicion.col) || (herramientas->posicion.fil == personaje->posicion.fil && herramientas->posicion.col == personaje->posicion.col));
        
        if (i < 5){ 
            juego->herramientas[i].tipo = 'G';
        } 
        
        else {
            juego->herramientas[i].tipo = 'S';
        }
    }    
}


/*
PRE CONDICIONES:
    - Inicializara los datos de los familiares de Perry cargando su info inicial, asignando su posicion inicial, etc.
POS CONDICIONES:
    - Se pasa por refrencia el struct juego de tipo juego_t, de elementos anteriormente incializados y en base a eso se actualiza el struct de cada familiar
*/

void inicializar_familiares(familiar_t * familiares, herramienta_t* herramientas, bomba_t* bombas, personaje_t* personaje, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_familiares = 3;

    for (int i = 0; i < juego->tope_familiares; i++){

         do
        {
            juego->familiares[i].posicion = asignar_posicion();
        } while ((familiares->posicion.fil == bombas->posicion.fil && familiares->posicion.col == bombas->posicion.col) || (familiares->posicion.fil == personaje->posicion.fil && familiares->posicion.col == personaje->posicion.col) || (familiares->posicion.fil == herramientas->posicion.fil && familiares->posicion.col == herramientas->posicion.col));
        
        if (i ==  0){ 
            juego->familiares[i].inicial_nombre = 'H';
        } 

        else if (i == 1)
        {
            juego->familiares[i].inicial_nombre = 'F';
        }
        
        
        else {
            juego->familiares[i].inicial_nombre = 'C';
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
    inicializar_bombas(juego->bombas, &(juego->perry), juego);
    inicializar_herramientas(juego->herramientas, juego->bombas, &(juego->perry), juego);
    inicializar_familiares(juego->familiares, juego->herramientas, juego->bombas, &(juego->perry), juego);
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
    
   
    terreno[juego.perry.posicion.fil][juego.perry.posicion.col] = 'P';


    for (int i = 0; i < juego.tope_bombas; i++){
        terreno[juego.bombas[i].posicion.fil][juego.bombas[i].posicion.col]= 'B'; 
    }

    for (int i = 0; i < juego.tope_herramientas; i++){
        terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas->tipo;
    }

    for (int i = 0; i < juego.tope_familiares; i++){
        terreno[juego.familiares[i].posicion.fil][juego.familiares[i].posicion.col] = juego.familiares->inicial_nombre;
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%c ", terreno[i][j]);
        }
        printf("\n");
    }

    printf("\nVidas de Perry: %d\n", juego.perry.vida);
    printf("\nVidas de Perry: %d\n", juego.perry.energia);
    verificar_camuflaje(juego.perry.camuflado);
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
            case 'W':
                if (juego->perry.posicion.fil > 0){

                    juego->perry.posicion.fil -= 1;
                    imprimir_terreno(*juego);
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                    imprimir_terreno(*juego);
                }
            break;

            case 'A':
                if (juego->perry.posicion.col > 0){

                    juego->perry.posicion.col -= 1;
                    imprimir_terreno(*juego);
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                    imprimir_terreno(*juego);
                }
            break;

            case 'S':
                if (juego->perry.posicion.fil < 19){

                    juego->perry.posicion.fil += 1;
                    imprimir_terreno(*juego);
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                    imprimir_terreno(*juego);
                }
            break;

            case 'D':
                if (juego->perry.posicion.col < 19){

                    juego->perry.posicion.col += 1;
                    imprimir_terreno(*juego);
                }
                else{
                    printf("\nTE VAS A SALIR DEL MAPA AGENTE P Y NO TE LO VOY A PERMITIR\n");
                    imprimir_terreno(*juego);
                }
            break;

            case 'Q':
                camuflar_personaje(juego);
                imprimir_terreno(*juego);
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

    int estado_actual;

    for (int i = 0; i < juego.tope_bombas; i++){
        if (juego.bombas[i].desactivada == true && juego.perry.vida > 0){
            estado_actual = 1;
        }
        else if (juego.perry.vida <= 0){
            estado_actual = -1;
        }
        else{
            estado_actual = 0;
        }
    }

    return estado_actual;
}