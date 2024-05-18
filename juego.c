#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "feria.h"
#include "feria.c"


/*
PRE CONDICIONES:
    - Pasar como parametro un dato de tipo bool
POS CONDICIONES:
    - Imprime por pantalla el estado de camuflaje
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
    - Pasar como parametro el struct juego
POS CONDICIONES:
    - Imprimir por pantalla los datos de Perry
*/

void imprimir_datos(juego_t juego){
    printf("\nVidas de Perry: %d\n", juego.perry.vida);
    printf("\nVidas de Perry: %d\n", juego.perry.energia);
    verificar_camuflaje(juego.perry.camuflado);
}


int main(){
    
    juego_t juego;

    char respuesta_jugador;
    int juego_terminado = estado_juego(juego);


    inicializar_juego(&juego);

    imprimir_terreno(juego);

    printf("\nINSTRUCCIONES : \n - W para moverse ARRIBA \n - A para moverse IZQUIERDA \n - S para moverse ABAJO \n - D para moverse DERECHA \n- Q para moverse CAMUFLARSE \n");
    
    printf("\nPor favor elija una tecla para ejecutar una accion del Agente P\n");
    scanf(" %c", &respuesta_jugador);

    while (juego_terminado == 0){
    
        realizar_jugada(&juego, respuesta_jugador); 

        imprimir_terreno(juego);
        imprimir_datos(juego);

        printf("\nINSTRUCCIONES : \n - W para moverse ARRIBA \n - A para moverse IZQUIERDA \n - S para moverse ABAJO \n - D para moverse DERECHA \n- Q para moverse CAMUFLARSE \n");
        
        printf("\nPor favor elija otra tecla para ejecutar una accion\n");
        scanf(" %c", &respuesta_jugador);
    }

    printf("Termino el juego...");
    
    return 0;
}