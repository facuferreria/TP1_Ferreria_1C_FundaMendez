#include <stdio.h>
#include <feria.c>

int main(){
    char respuesta_jugador[];

    printf("Bienvenido jugador! Su mision es ayudar al Agente P que debe salvar a la feria de la ciudad desactivando las bombas del malvado Dr. Doofenshmirtz.\n Pero tengan cuidado, 
        la familia del Agente P esta en la feria tambien, por ende debe hacerlo siempre y cuando su identidad se mantenga oculta. \n
        Buena suerte Agentes... ");

    //ACA va la inicializacion del mapa, inicializacion de las bombas, objetos, familia y perry ya que solo va a pasar una vez

    printf("Por favor elija algunas de las siguientes teclas para mover al Agente P o camuflarlo: \n
        - W para moverse ARRIBA \n
        - A para moverse IZQUIERDA \n
        - S para moverse ABAJO \n
        - D para moverse DERECHA \n
        - Q para moverse CAMUFLARSE \n");
    scanf("%s", &respuesta_jugador);

    printf("¿Queres salvar el mundo con el Agente P? Responde SI o NO si queres jugar \n");
    scanf("%s", &respuesta_jugador);

    while (respuesta_jugador != "NO"){
        
        //ACA van los movimientos del usuario con perry ya sea para moverse o cambiar de camuflaje


        printf("Por favor elija otra tecla para ejecutar una accion o escriba NO para salir del juego");
        scanf("%s", &respuesta_jugador);
    }

    printf("Termino el juego...");
    
    return 0;
}