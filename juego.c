#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "feria.h"
#include "feria.c"


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


void imprimir_datos(juego_t juego){
    printf("\nVidas de Perry: %d\n", juego.perry.vida);
    printf("\nVidas de Perry: %d\n", juego.perry.energia);
    verificar_camuflaje(juego.perry.camuflado);
}

int main(){

    char respuesta_jugador;
    juego_t juego;

    int juego_terminado = estado_juego(juego);

    printf("\nBienvenido jugador! Su mision es ayudar al Agente P que debe salvar a la feria de la ciudad desactivando las bombas del malvado Dr. Doofenshmirtz.\n Pero tengan cuidado,  la familia del Agente P esta en la feria tambien, por ende debe hacerlo siempre y cuando su identidad se mantenga oculta. \n Buena suerte Agentes... ");

    //ACA va la inicializacion del mapa, inicializacion de las bombas, objetos, familia y perry ya que solo va a pasar una vez

    printf("\nPor favor elija algunas de las siguientes teclas para mover al Agente P o camuflarlo: \n - W para moverse ARRIBA \n - A para moverse IZQUIERDA \n - S para moverse ABAJO \n - D para moverse DERECHA \n- Q para moverse CAMUFLARSE \n");

    printf("\n¿Queres salvar el mundo con el Agente P? Responde S para SI o N para NO si queres jugar \n");
    scanf(" %c", &respuesta_jugador);


    inicializar_juego(&juego);

    imprimir_terreno(juego);


    printf("\nPor favor elija una tecla para ejecutar una accion del Agente P\n");
    scanf("%c", &respuesta_jugador);

    while (juego_terminado == 0){
        

        realizar_jugada(&juego, respuesta_jugador);

        printf("\nPor favor elija otra tecla para ejecutar una accion\n");
        scanf("%c", &respuesta_jugador);

        imprimir_terreno(juego);
        imprimir_datos(juego);
    }

    printf("Termino el juego...");
    
    return 0;
}