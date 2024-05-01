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

void verificar_camuflaje(bool esta_camuflado){
    if (esta_camuflado)
    {
        printf("\nCamuflaje: Activado\n");
    }
    else
    {
        printf("\nCamuflaje: Desactivado\n");
    }
    
}

void inicializar_personaje(personaje_t* personaje){
    srand((unsigned)time(NULL));

    personaje->vida = 3;
    personaje->energia = 100;
    personaje->camuflado = false;
    personaje->posicion = asignar_posicion();
}

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

void inicializar_herramientas(herramienta_t* herramientas, bomba_t* bombas, personaje_t* personaje, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_herramientas = 8;

    for (int i = 0; i < juego->tope_herramientas; i++){

        do
        {
            juego->herramientas[i].posicion = asignar_posicion();
        } while (herramientas->posicion.fil == bombas->posicion.fil && herramientas->posicion.col == bombas->posicion.col || herramientas->posicion.fil == personaje->posicion.fil && herramientas->posicion.col == personaje->posicion.col);
        
        if (i < 5){ 
            juego->herramientas[i].tipo = 'G';
        } 
        
        else {
            juego->herramientas[i].tipo = 'S';
        }
    }    
}


void inicializar_familiares(familiar_t * familiares, herramienta_t* herramientas, bomba_t* bombas, personaje_t* personaje, juego_t* juego){
    srand((unsigned)time(NULL));

    juego->tope_familiares = 3;

    for (int i = 0; i < juego->tope_familiares; i++){

         do
        {
            juego->familiares[i].posicion = asignar_posicion();
        } while (familiares->posicion.fil == bombas->posicion.fil && familiares->posicion.col == bombas->posicion.col || familiares->posicion.fil == personaje->posicion.fil && familiares->posicion.col == personaje->posicion.col || familiares->posicion.fil == herramientas->posicion.fil && familiares->posicion.col == herramientas->posicion.col);
        
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

void inicializar_juego(juego_t* juego){

    inicializar_personaje(&juego->perry);
    inicializar_bombas(juego->bombas, &(juego->perry), juego);
    inicializar_herramientas(&(juego->herramientas), &(juego->bombas), &(juego->perry), juego);
    inicializar_familiares(&(juego->familiares), &(juego->herramientas), &(juego->bombas), &(juego->perry), juego);

    imprimir_terreno(*juego);
}


void imprimir_terreno(juego_t juego){

    char terreno[FILAS][COLUMNAS];

    for(int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            terreno[i][j] = '.';
        }
    }
    
   
    //Asignamos primero posicion en terreno a perry
    terreno[juego.perry.posicion.fil][juego.perry.posicion.col] = 'P';


    //Asignamos las bombas
    for (int i = 0; i < juego.tope_bombas; i++){
        terreno[juego.bombas[i].posicion.fil][juego.bombas[i].posicion.col]= 'B'; 
    }

    //Asignamos herramientas
    for (int i = 0; i < juego.tope_herramientas; i++){
        terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas->tipo;
    }

    //Asignamos familiares
    for (int i = 0; i < juego.tope_familiares; i++){
        terreno[juego.familiares[i].posicion.fil][juego.familiares[i].posicion.col] = juego.familiares->inicial_nombre;
    }

    //imprimo mi matriz con los elementos en el terreno ya sin repetir
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%c ", terreno[i][j]);
        }
        printf("\n");
    }

    //Imprimo datos de Perry
    printf("\nVidas de Perry: %d\n", juego.perry.vida);
    printf("\nVidas de Perry: %d\n", juego.perry.energia);
    verificar_camuflaje(juego.perry.camuflado);
}






void camuflar_personaje(juego_t juego){
    if (juego.perry.camuflado == false){
        juego.perry.camuflado == true;
    }
    else{
        juego.perry.camuflado == false;
    }
    
}

void realizar_jugada(juego_t* juego, char accion){
    printf("\nFila del agente: %d -- Col del agente: %d\n", juego->perry.posicion.fil, juego->perry.posicion.col);
    if (juego->perry.posicion.fil <= 20 && juego->perry.posicion.col <= 20){
        switch (accion){
            case 'W':
                juego->perry.posicion.fil -= 1;
                imprimir_terreno(*juego);
                break;

            case 'A':
                juego->perry.posicion.col -= 1;
                imprimir_terreno(*juego);
                break;

            case 'S':
                juego->perry.posicion.fil += 1;
                imprimir_terreno(*juego);
                break;

            case 'D':
                juego->perry.posicion.col += 1;
                imprimir_terreno(*juego);
                break;

            case 'Q':
                camuflar_personaje(*juego);
                imprimir_terreno(*juego);
                break;
            
            default:
                printf("\nMovimiento NO EXISTENTE! Elegi otro movimiento para el Agente P\n");
                imprimir_terreno(*juego);
                break;
        }
    }
    else{
        printf("\nNo podes salirte del mapa! Elegi otro movimiento!\n");
        imprimir_terreno(*juego);
    }
}