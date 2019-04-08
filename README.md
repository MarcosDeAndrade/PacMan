# PacMan (Game) (C++)

## ***Introducción***

Proyecto realizado por [Marcos De Andrade](https://github.com/MarcosDeAndrade) y [Samuel Boada](https://github.com/systems-multimedia).

Juego arcade de PacMan, con las funcionalidades parciales del juego original. El objetivo del juego consiste en comer el mayor número de puntos, sin dejarse atrapar por los fantasmas en el laberinto establecido.
> NOTA: NO todas las funcionalidades del juego se encuentran implementadas.

## ***Instrucciones***
1. Descarga el repositorio, en el encontaras el archivo ***Pac-Man***.
2. Ejecuta tu IDE deseado, se sugiere [Dev C++](https://sourceforge.net/projects/orwelldevcpp/).
3. Abre el archivo ***Pac-Man*** anteriormente mencionado con el IDE.
4. Compila y corre el programa.
5. Sigue las instrucciones en el menu de ***Instrucciones*** para aprender a jugar.

## ***Especificaciones***

> Software desarrollado en lenguaje C++, con el IDE DEV C++. 
 con el IDE NetBeans, en el lenguaje JAVA

Desarrollar un programa que permita jugar PacMan. Debe contar con las siguientes especificaciones.

***Funcionalidad***

  - El Jugador deberá ingresar su cédula de identidad como su ID.
  - El PacMan solo tendrá movimiento horizontal y vertical en cualquier sentido (izquierda o derecha, arriba o abajo, dependiendo de los espacios libres del tablero).
  - Al inicio de cada nivel se ubicará debajo de la guarida en el punto medio.
  - Cada nivel tendrá 3 vidas, siendo acumulativas de nivel en nivel.
  - Si el fantasma intercepta al PacMan perderá 1 vida hasta un máximo de 3, iniciando la siguiente ronda en el mismo lugar donde fue interceptado, estando los fantasmas de nuevo en su guarida.
  - En caso de perder las 3 vidas, el juego finalizará (Game Over) y desplegará el ID del Jugador, su score y el nivel a que llegó. Si el jugador completa los 5 niveles, igualmente desplegará el ID del Jugador, su score y un mensaje de felicitación. Para os 2 casos indicados, siempre preguntara si desea volver a jugar.
  - Si el jugador logra comerse la totalidad de los puntos sin haber perdido sus 3 vidas, automáticamente pasa de nivel (pausa) y se vuelve a generar de nuevo el tablero. El Juego tendrá solo 5 niveles disponibles.
  - Cada vez que pierda la vida, siempre estarán presentes los 4 fantasmas en la guarida.
  - Los fantasmas tienen su propio nombre y personalidad, nombrándose como sigue:
    *  Clyde: es de color naranja, y el más lento del grupo. Se moverá aleatoriamente
    *  Blinky: es de color rojo y es el líder de los fantasmas. Su movimiento estará basado en el la búsqueda del PacMan para interceptarlo. No es aleatorio.
  - El programa deberá contar con una “AYUDA”, donde se explique el objetivo y reglas del juego.

***Requerimientos (NO implementados)***

  - PacMan tendrá al inicio de cada nivel, 4 puntos de poder (identificados por su mayor tamaño y color blanco ubicados de forma fija – ver tablero), que en caso de comérselos, tendrá la posibilidad por 15 segundos de comerse también a los fantasmas. Todos los fantasmas cambian de color a blanco por esos 15 segundos. ***No esta Implemetado***.
  - Cada punto comido le otorgará al jugador 10 puntos a su score. Si logra comerse 1 fantasma se le abonaran 100 puntos, 2 fantasmas 300 puntos, 3 fantasmas 700 puntos y los cuatro fantasmas 1000 puntos sin haber perdido la vida. Se otorgaran 500 puntos por cada nivel completado. ***No esta Implemetado***.
  - Los fantasmas tienen su propio nombre y personalidad, nombrándose como sigue:
    *  Pinky: es de color rosa y es muy rápido. Él tratará de interceptar al PacMan por el lado contrario de donde Blinky lo intenta y mostrará gran interés por meterse en el túnel. ***No esta Implemetado***.
    *  Inky: es de color verde. Es conservador y a veces tratará de escapar del PacMan. ***No esta Implemetado***.
  - El programa deberá indicar el tiempo transcurrido hasta que el Jugador pierde. ***No esta Implemetado***.

## ***ScreenShoots***

### *Menu Principal*
![Menu Principal](https://i.ibb.co/M7sgtnM/Imagen1.png)

### *Creditos*
![Creditos](https://i.ibb.co/9cnP7hx/Imagen2.png)

### *Instrucciones*
![Instrucciones](https://i.ibb.co/dLGCG1D/Imagen3.png)

### *Ingresar ID*
![Ingresar ID](https://i.ibb.co/LJw61x4/Imagen4.png)

### *Inicio de Partida*
![Inicio de Partida](https://i.ibb.co/tLBfcPx/Imagen5.png)

### *Partida*
![Partida](https://i.ibb.co/f9KNmM8/Imagen6.png)

### *Game Over*
![Game Over](https://i.ibb.co/d5gZ4WD/Imagen7.png)
