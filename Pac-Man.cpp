/*
 ------------------------------------------------------------------------------
 =       Metropolitan University, Caracas - Venezuela                         =
 =       Systems Engineering                                                  =
 =       Algorithms and Programming                                                   =
 =       * Professor:   Nicolas Araque                                        =
 =       * Creators:    Marcos De Andrade, Samuel Boada                       =
 =       Proyect  N°2 - PacMan                                       		  =
 =       Period  1718-2 (febrero 2018)                                        =
 ------------------------------------------------------------------------------
 */

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <time.h>
#include <math.h>

#define UP     	72  
#define DOWN    80
#define LEFT  	75
#define RIGHT   77
#define ESC		27

#define	UNO		49
#define	DOS		50
#define	TRES	51	
#define CUATRO	52

using namespace std;

/*========================================= VARIABLES GLOBALES   =========================================   */

int  puntos  = 20;
int  dirMenu = 0;
int  dir     = 0;
int  vida    = 3;
int  cedula;
int  nivel   = 1;

char tecla;
char opcion;
char respuesta = 's';

//Vector con los colores a utilizar en el programa
int color[8] = {
    14, 	//[0]	Color PacMan 	(Amarillo)
    12, 	//[1]	Color Blinky 	(Rojo)
    13, 	//[2]	Color Pinky		(Rosado)
    10, 	//[3]	Color Inky		(Verde)
    11, 	//[4]	Color Clyde		(Azul Claro)
    15, 	//[5]	Color 			(Blanco Brillante)
    9 ,		//[6]	Color Mapa		(Azul)
    7		//[7]	Color Monedas	(Blanco Palido)
};

/*========================================= VARIABLES DE SONIDO   =========================================   */

char soundPacManInicio[] = "C:/Users/Marcos/Desktop/Proyecto 2 Pac Man/Pac-Man Start.wav" ; 


//Funcion para usar gotoxy
void gotoxy(int x,int y){  
	HANDLE hCon;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hCon,dwPos);  
} 

//Funcion para eliminar el cursor de la ventaja de ejecucion
void ocultarCursor(){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos; 
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize =100;
	cci.bVisible= FALSE;	//EL FALSE hace que no se vea, con TRUE se vera con el tamano que indique dwSize
	SetConsoleCursorInfo(hcon,&cci);
}

//Funcion para definir colores (pasando como parametro el vector "color")
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),color);
}


/*=====================================  MATRICES DE MENU  =====================================*/


/*===========  MATRIZ PAC-MAN   =========== */	   //Ubicada en Menu Principal
char titulo[6][43] = {
"PPPPP PPPPP PPPPPO      P   P PPPPP P   P",
"P   P P   P P PP        PP PP P   P PP  P",
"PPPPP PPPPP PPP    PPP  P P P PPPPP P P P",
"P     P   P PPPP        P   P P   P P  PP",
"P     P   P PPPPPQ      P   P P   P P   P"  
}; 

/*===========  MATRIZ FANTASMAS   =========== */   //Ubicada en Menu Principal
char tituloFantasmas[4][35] = {
" aXXXa    eWWWe    gTTTg    iUUUi ",
"aXdcXdc  eWdcWdc  gTdcTdc  iUdcUdc",
"XXXXXXX  WWWWWWW  TTTTTTT  UUUUUUU",
"XbXbXbX  WfWfWfW  ThThThT  UjUjUjU"
};

/*==============  MATRIZ TECLADO  ============== */   //Ubicada en AYUDA
char teclado[6][22] = {
"      a---b     ",
"      I e I     ",
"      c---d     ",
"a---b a---b a---b",
"I f I I h I I g I",
"c---d c---d c---d"
};

/*========  MATRIZ FANTASMAS AZULES  ========= */  //Ubicada en CREDITOS
char fantasmasAzules[4][35] = {
" cYYYc             aXXXa    aXXXa ",
"YYYd       ee     aXaXaXa  aXaXaXa",
"YYYc       ff     XbababX  XbababX",
" dYYYd            XbXbXbX  XbXbXbX"
};


//Funcion para LLENAR MATRIZ TITULO PACMAN (titulo en el menu)
void llenarTitulo()
{
	for(int i=0; i<43; i++)
	{
		for(int j=0; j<6; j++)
		{
			gotoxy(12+i,5+j);
			if		(titulo[j][i]=='P'){setColor(color[0]);cout<<char(219);}
			else if (titulo[j][i]=='O'){setColor(color[0]);cout<<char(223);}
			else if (titulo[j][i]=='Q'){setColor(color[0]);cout<<char(220);}
			else{cout<<char();}
		}
	}
}

//Funcion para LLENAR MATRIZ FANTASMAS (en el menu)
void llenarFantasmas()
{
	for(int i=0; i<35; i++)
	{
		for(int j=0; j<4; j++)
		{
			gotoxy(14+i,25+j);
			
			//Blinky
			if		(tituloFantasmas[j][i]=='X')	{setColor(color[1]); cout<<char(219);}
			else if	(tituloFantasmas[j][i]=='a')	{setColor(color[1]); cout<<char(220);}
			else if	(tituloFantasmas[j][i]=='b')	{setColor(color[1]); cout<<char(223);}
			
			//Pinky
			else if	(tituloFantasmas[j][i]=='W')	{setColor(color[2]); cout<<char(219);}
			else if	(tituloFantasmas[j][i]=='e')	{setColor(color[2]); cout<<char(220);}
			else if	(tituloFantasmas[j][i]=='f')	{setColor(color[2]); cout<<char(223);}
			
			//Clyde
			else if	(tituloFantasmas[j][i]=='T')	{setColor(color[4]); cout<<char(219);}
			else if	(tituloFantasmas[j][i]=='g')	{setColor(color[4]); cout<<char(220);}
			else if	(tituloFantasmas[j][i]=='h')	{setColor(color[4]); cout<<char(223);}
			
			//Inky
			else if	(tituloFantasmas[j][i]=='U')	{setColor(color[3]); cout<<char(219);}
			else if	(tituloFantasmas[j][i]=='i')	{setColor(color[3]); cout<<char(220);}
			else if	(tituloFantasmas[j][i]=='j')	{setColor(color[3]); cout<<char(223);}
			
			//Ojos
			else if	(tituloFantasmas[j][i]=='c')	{setColor(color[5]); cout<<char(223);}
			else if	(tituloFantasmas[j][i]=='d')	{setColor(color[5]); cout<<char(219);}
			
			else{cout<<char();}
		}
	}
}	

//Funcion para LLENAR MATRIZ TECLADOo (teclas en Ayuda)
void llenarTeclado()
{
	
	for(int i=0; i<22; i++)
	{
		for(int j=0; j<6; j++)
		{
			gotoxy(40+i,22+j);
			if(teclado[j][i]=='a')			{setColor(color[0]);cout<<char(201);}
			else if (teclado[j][i]=='b')	{setColor(color[0]);cout<<char(187);}
			else if (teclado[j][i]=='c')	{setColor(color[0]);cout<<char(200);}					
			else if (teclado[j][i]=='d')	{setColor(color[0]);cout<<char(188);}
			else if (teclado[j][i]=='e')	{setColor(color[0]);cout<<char(94);}
			else if (teclado[j][i]=='f')	{setColor(color[0]);cout<<char(60);}
			else if (teclado[j][i]=='g')	{setColor(color[0]);cout<<char(62);}
			else if (teclado[j][i]=='h')	{setColor(color[0]);cout<<'v';}
			else if (teclado[j][i]=='-')	{setColor(color[0]);cout<<char(205);}
			else if (teclado[j][i]=='I')	{setColor(color[0]);cout<<char(186);}
			else{cout<<char();}
		}
	}
}

//Funcion para LLENAR MATRIZ FANTASMAS AZULES 
void llenarFantasmasAzules()
{

	for(int i=0; i<35; i++)
	{
		for(int j=0; j<4; j++)
		{
			gotoxy(14+i,30+j);
			
			//Fantasmas
			if		(fantasmasAzules[j][i]=='X')	{setColor(color[6]); cout<<char(219);}
			else if	(fantasmasAzules[j][i]=='a')	{setColor(color[6]); cout<<char(220);}
			else if	(fantasmasAzules[j][i]=='b')	{setColor(color[6]); cout<<char(223);}
			
			//PacMan
			else if	(fantasmasAzules[j][i]=='Y')	{setColor(color[0]); cout<<char(219);}
			else if	(fantasmasAzules[j][i]=='c')	{setColor(color[0]); cout<<char(220);}
			else if	(fantasmasAzules[j][i]=='d')	{setColor(color[0]); cout<<char(223);}
			
			//Punto
			else if	(fantasmasAzules[j][i]=='e')	{setColor(color[5]); cout<<char(220);}
			else if	(fantasmasAzules[j][i]=='f')	{setColor(color[5]); cout<<char(223);}	
			else{cout<<char();}
		}
	}
}	
	

/*=====================================  TABLERO PRINIPAL  =====================================*/

// tablero [filas][columnas]
char tablero[29][44] = {
     "AxxxxxxxxxxxxxxxxxxxB AxxxxxxxxxxxxxxxxxxxB",
     "I________+__________I I__________+________I",
     "I_AxxxxxB_AxxxxxxxB_I I_AxxxxxxxB_AxxxxxB_I",
     "I_I     I_I       I_I I_I       I_I     I_I",
     "I_DxxxxxC_DxxxxxxxC_DxC_DxxxxxxxC_DxxxxxC_I",
     "I+_______+___+_____+___+_____+___+_______+I",
     "I_AxxxxxB_AxB_AxxxxxxxxxxxxxB_AxB_AxxxxxB_I",
     "I_DxxxxxC_I I_DxxxxB   AxxxxC_I I_DxxxxxC_I",
     "I________+I I______I   I______I I+________I",
     "DxxxxxxxB_I DxxxxB I   I AxxxxC I_AxxxxxxxC",
     "        I_I AxxxxC DxxxC DxxxxB I_I        ",
     "        I_I I                 I I_I        ",
     "xxxxxxxxC_DxC Axxxxxx xxxxxxB DxC_Dxxxxxxxx",
     "         +    I      *      I    +         ",
     "xxxxxxxxB_AxB DxxxxxxxxxxxxxC AxB_Axxxxxxxx",
     "        I_I I                 I I_I        ",
     "        I_I I AxxxxxxxxxxxxxB I I_I        ",
     "AxxxxxxxC_DxC DxxxxB   AxxxxC DxC_DxxxxxxxB",
     "I________+_________I   I_________+________I",
     "I_AxxxxxB_AxxxxxxB_I   I_AxxxxxxB_AxxxxxB_I",
     "I_DxxxB I_DxxxxxxC_DxxxC_DxxxxxxC_I AxxxC_I",
     "I_____I I+________+_____+________+I I_____I",
     "DxxxB_I I_AxB_AxxxxxxxxxxxxxB_AxB_I I_AxxxC",
     "AxxxC_DxC_I I_DxxxxB   AxxxxC_I I_DxC_DxxxB",
     "I____+____I I______I   I______I I____+____I",
     "I_AxxxxxxxC DxxxxB_I   I_AxxxxC DxxxxxxxB_I",
     "I_DxxxxxxxxxxxxxxC_DxxxC_DxxxxxxxxxxxxxxC_I",
     "I_________________+_____+_________________I",
     "DxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxC",
};

int  space [29][44];
int  comida[29][44];

/*
	=============================  SIGNIFICADO DE LOS VALORES DE LAS MATRICES  =============================

		* MATRIZ TABLERO (Matriz base)
			El x : Se encuentra un muro horizontal en ese espacio
			El _ : Se encuentra un punto de comida
			El' ': Se encuentra un espacio vacio
			El I : Se encuentra un muro vertical
			El A : Se encuentra una esquina superio izquierda del muro
			El B : Se encuentra una esquina superio derecha del muro
			El C : Se encuentra una esquina inferior derecha del muro
			El D : Se encuentra una esquina inferior izquierda del muro
			El * : Se encuentra la salida de la Guarida de los Fantasmas
			El + : Se encuentra un cruce de 3 alternativas, no hay punto de comida
		* MATRIZ SPACE
			El 1: Se encuentra un muro en ese espacio
			El 2: Se encuentra un cruce de 3 alternativas
			El 3: Se encuentra el comienzo del pasadio
			El 4: Se encuentra la salida de la Guarida de los Fantasmas
		* MATRIZ COMIDA
			El 0: Ese espacio no contiene ningun punto
			El 1: Se encuentra un punto de comida
			El 2: Se encuentra una muro
			El 3: 
*/

//Funcion para LLENAR EL TABLERO (recorre Primero las columnas y luego cada fila)
void llenarMapa()
{
     for(int i = 0 ; i < 29 ; i++){
         for(int j = 0 ; j < 43 ; j++){
         	
         	   //COLOCAR(11+J)(4+I)
               gotoxy(11+j,4+i); 		 
               
               if		(tablero[i][j] == 'x') 	{setColor(color[6]); cout<<char(205);	space[i][j]=1;	comida[i][j]= 2;}
               else if	(tablero[i][j] == '_') 	{setColor(color[7]); cout<<char(250);	space[i][j]=0;	comida[i][j]= 1;}
               else if	(tablero[i][j] == ' ') 	{										space[i][j]=0;	comida[i][j]= 0;}
			   else if	(tablero[i][j] == 'I') 	{setColor(color[6]); cout<<char(186);	space[i][j]=1;	comida[i][j]= 2;}
	           else if	(tablero[i][j] == 'A') 	{setColor(color[6]); cout<<char(201);	space[i][j]=1;	comida[i][j]= 2;}
		       else if	(tablero[i][j] == 'B') 	{setColor(color[6]); cout<<char(187);	space[i][j]=1;	comida[i][j]= 2;}
			   else if	(tablero[i][j] == 'C') 	{setColor(color[6]); cout<<char(188);	space[i][j]=1;	comida[i][j]= 2;}
			   else if	(tablero[i][j] == 'D') 	{setColor(color[6]); cout<<char(200);	space[i][j]=1;	comida[i][j]= 2;}
			   else if	(tablero[i][j] == '*') 	{setColor(color[5]); cout<<char(32) ; 	space[i][j]=4;  comida[i][j]= 0;}
			   else if	(tablero[i][j] == '+') 	{setColor(color[5]); cout<<char(250); 	space[i][j]=2;  comida[i][j]= 1;}		   			   	
         }
     }
	//Valor para Pasadizo
    space[13][0]  = 3;
	space[13][42] = 3;
	//space[13][26] = 5;
}

	/*===================================  IMPRIMIR MATRICES NO VISIBLES  ===================================*/


void imprimirSpace(){
	
	
	for(int i = 0 ; i < 29 ; i++){
         for(int j = 0 ; j < 43 ; j++){
         	gotoxy(11+j,4+i);							//COLOCAR(11+J)(4+I)
         	
         		if(space[i][j]==0)
         		{
         			setColor(color[5]);
				}
				else if (space[i][j]==1){
					setColor(color[1]);
				}
				else if (space[i][j]==3){
					setColor(color[3]);
				}
				else if (space[i][j]==4){
					setColor(color[4]);
				}
				cout<<space[i][j];
		}
		cout<<endl;
	}
}


/*
void imprimirComida(){
	
	for(int i = 0 ; i < 29 ; i++){
         for(int j = 0 ; j < 43 ; j++){
         	gotoxy(11+j,4+i);							//COLOCAR(11+J)(4+I)
         	
         		if(comida[i][j]==0)
         		{
         			setColor(color[0]);
				}
				else if (comida[i][j]==1){
					setColor(color[1]);
				}
				else if (comida[i][j]==2){
					setColor(color[4]);
				}
				else if (comida[i][j]==3){
					setColor(color[3]);
				}
				cout<<comida[i][j];
		}
		cout<<endl;
	}
}
*/


	/*=====================================  TECLADO  =====================================*/

//Funcion TECLAS EN MENU
void teclearMenu(){
	
    opcion = getch();
    switch(opcion){
      case UNO:
         dirMenu = 1;	//Jugar
         break;

      case DOS:
         dirMenu = 2;	//Ayuda
         break;

      case TRES:
         dirMenu = 3;	//Creditos
         break;
         
      case CUATRO:	   //Salir	  
      	dirMenu  = 4;
      	  break;
	}
}

//Funcion TECLAS EN JUEGO
void teclear(){
    if(kbhit()){
      tecla = getch();
      switch(tecla){
      case UP:
         dir = 0;
         break;

      case DOWN:
         dir = 1;
         break;

      case RIGHT:
         dir = 2;
         break;

      case LEFT:
         dir = 3;
         break;
        
      case ESC:
      	dir = 4;
      	break;
      }
   }
}
	/*==================================   Validaciones ==================================*/

//Funcion para VALIDAR CEDULA
void validarCedula(){
	
	while(cedula<=0)
	{
		setColor(color[0]);
		gotoxy(25,22);
		cout<<"Valor invalido!"; 
		gotoxy(13,23);
		cout<<"Por favor Introduzca un valor mayor a 0."<<endl;
		
		setColor(color[5]);
		gotoxy(0,18);
		cout<<"                                                                 ";
		gotoxy(28,18);
		cin>>cedula;
	}
}

	/*===================================  FUNCIONES MENU  =====================================*/
	
// Funcion para MENU-CEDULA
void menuCedula()
{
	llenarTitulo();
	
	setColor(color[0]);
	gotoxy(24,14);
	cout<<"INGRESE SU CEDULA";
	
	setColor(color[0]);
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	setColor(color[5]);
	gotoxy(28,18);
	cin>>cedula;
	validarCedula();
}
	
//Funcion para MENU AYUDA
void menuAyuda()
{
	llenarTeclado();
	
	gotoxy(30,1);
	setColor(color[0]);
	cout<<"AYUDA";
	
	cout<<endl<<endl<<endl;
	setColor(color[5]);
	cout<<"          El objetivo del juego consiste en que Pacman logre"<<endl;
	cout<<"    comer todos los puntos de la pantalla, una vez conseguido"<<endl;
	cout<<"    se pasa al siguiente nivel. Sin embargo, no sera tan"<<endl;
	cout<<"    facil, cuatro fantasmas Blinky (rojo), Pinky (rosado),"<<endl;
	cout<<"    Inky (cian)y Clyde (verde), perseguiran a PacMan, con la"<<endl;
	cout<<"    finalidad de atraparlo. El juego comenzara con 3 vidas,"<<endl;
	cout<<"    y cada nivel le otorgara 3 vidas adicionales, siendo estas"<<endl;
	cout<<"    acumulativas. Si PacMan es alcanzado por alguno de los "<<endl;
	cout<<"    fantasmas, se le restara una vida, si se terminan las"<<endl;
	cout<<"    vidas el juego se dara por terminado."<<endl<<endl<<endl;
	
	cout<<"          En las cuatro esquinas del mapa se encuentran los "<<endl;
	cout<<"    llamados <<Puntos de Poder>>, y que proporcionan a Pac-Man"<<endl;
	cout<<"    la habilidad temporal de comerse a los fantasmas. Despues"<<endl;
	cout<<"    de haber sido tragados, los fantasmas se regeneraran en la"<<endl;
	cout<<"    guarida."<<endl<<endl<<endl;

	cout<<"          El usuario manejara al "<<endl;
	cout<<"    personaje de PacMan a traves "<<endl;
	cout<<"    de las flechas ubicadas en el"<<endl;
	cout<<"    teclado."<<endl;

	
	setColor(color[0]);
	gotoxy(19,31);
	cout<<"1.    EMPEZAR A JUGAR!";
		
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	teclearMenu();
		
	if(dirMenu == 1){
		system("cls");
		menuCedula();
	}
}

//Funcion para MENU CREDITOS
void menuCreditos(){
	
	llenarTitulo();
	llenarFantasmasAzules();
	
	gotoxy(28,12);
	setColor(color[0]);
	cout<<"CREDITOS";
	
	setColor(color[5]);
	cout<<endl<<endl<<endl;
	cout<<"\tEste es un juego de PacMan elaborado por Marcos"<<endl;
	cout<<"\t De Andrade y Samuel Boada, como Proyecto 2 de "<<endl;
	cout<<"\t del curso de Algoritmos y Programacion en el "<<endl;
	cout<<"\t  trimestre 2 del periodo 17-18 impartido por"<<endl;
	cout<<"\tel profesor Nicolas Araque en colaboracion con"<<endl;
	cout<<"\t      el preparador Alejandro Macari en la"<<endl;
	cout<<"\tUniversidad Metropolitana de Caracas Venezuela"<<endl;
	
	setColor(color[0]);
	gotoxy(19,24);
	cout<<"1.    EMPEZAR A JUGAR!";
	gotoxy(19,26);
	cout<<"2.    Ayuda";
	
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	teclearMenu();
	
	if(dirMenu == 1){
		system("cls");
		menuCedula();
	}
	else if(dirMenu == 2){
		system("cls");
		menuAyuda();
	}	
}

//Funcion para MENU PRINCIPAL
void menu(){
		
	llenarTitulo();
	llenarFantasmas();
	
	setColor(color[5]);
	gotoxy(21,15);
	cout<<"1.  Empezar a jugar";
	gotoxy(21,17);
	cout<<"2.  Ayuda";
	gotoxy(21,19);
	cout<<"3.  Creditos";

	setColor(color[0]);
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	teclearMenu();	
	
	if(dirMenu == 1){
		system("cls");
		menuCedula();
	}
	else if(dirMenu == 2){
		system("cls");
		menuAyuda();
	}
	else if(dirMenu == 3){
	 	system("cls");
		menuCreditos();
	}
}

	/*===================================  MARCADOR FIJO  ===================================*/

void marcadorFijo(){
	
	setColor(color[0]);
	
	gotoxy(29,1);
	cout<<"PAC-MAN";
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	setColor(color[5]);
	
	gotoxy(12,2);
	cout<<"SCORE";
	gotoxy(43,2);
	cout<<"TIME";
	gotoxy(12,34);
	cout<<"LIVES";

}

	/*================================== MARCADOR CAMBIABLE ==================================*/

void marcador(){
	
	//Puntos
	gotoxy(18,2);
	setColor(color[0]);
	cout<<puntos;
	
	//Vidas
	
	gotoxy(19,34);
	cout<<vida<<" < ";

	//Nivel
		
	gotoxy(29,3);
	cout<<"LEVEN "<<nivel;
	
}

	/*=====================================  PACMAN  =====================================*/

// Funcion para IMPRIMIR PAC-MAN
void imprimirPacman(int i , int j){
    setColor(color[0]);
    
    if		(dir==0)	{ tablero[i][j]=118;}
	else if	(dir==1)	{ tablero[i][j]=94; }
	else if	(dir==2)	{ tablero[i][j]=60; }
	else if	(dir==3)	{ tablero[i][j]=62; }
    
	gotoxy(11+i,4+j); cout<<tablero[i][j];
				
}

// Funcion para BORRAR PAC-MAN
void borrarPacman(int i, int j){
     tablero[i][j]=32; 
     gotoxy(11+i,4+j);cout<<tablero[i][j];
}


// Funcion para los PUNTOS DE COMIDA
void puntosComida(int i, int j){
	
	if(dir==0 && comida[j-1][i]==1){
		comida[j-1][i]=0;
		puntos=puntos+10;
	}
	else if (dir==1 && comida[j+1][i]==1){
		comida[j+1][i]=0;
		puntos=puntos+10;
	}
	else if (dir==2 && comida[j][i+1]==1){
		comida[j][i+1]=0;
		puntos=puntos+10;
	}
	else if (dir==3 && comida[j][i-1]==1){
		
		comida[j][i-1]=0;
		puntos=puntos+10;
	}
}

// Funcion MOVER ARRIBA PAC-MAN
void movArribaPacman(int &i, int &j){
	
	if (dir == 0  && ( space[j-1][i] == 0  || space[j-1][i] == 2 ) ){
		puntosComida(i,j);
		marcador();
		borrarPacman(i,j);
		j=j-1;
	}
}

//Funcion MOVER DERECHA PAC-MAN
void movAbajoPacman(int &i, int &j){
	
	if (dir == 1 && (space[j+1][i] == 0 || space[j+1][i] == 2 )){	
		puntosComida(i,j);
		marcador();
		borrarPacman(i,j);
		j=j+1;
	}
}

// Funcion para MOVER IZQUIERDA PAC-MAN
void movIzquierdaPacman(int &i, int &j){
	
	if (dir == 3  && (space[j][i-1] == 0 || space[j][i-1] == 2  || space[j][i-1] == 3)){
		puntosComida(i,j);
		marcador();
		borrarPacman(i,j);
		i=i-1;
	}
}

// Funcion para MOVER DERECHA PAC-MAN
void movDerechaPacman(int &i, int &j){
	
	if (dir == 2 && (space[j][i+1] == 0 || space[j][i+1] == 2 || space[j][i+1] == 3)){
		puntosComida(i,j);
		marcador();
		borrarPacman(i,j);
		i=i+1;
	}
}

// Funcion para MOVER PASADIZO IZQUIERDO PAC-MAN
void movPasadizoIzq(int &i, int &j)
{
	if(i == 0){
		borrarPacman(i,j);
		i=42;
		movIzquierdaPacman(i,j);
	}
}

// Funcion para MOVER PASADIZO DERECHO PAC-MAN
void movPasadizoDer(int &i, int &j)
{
	if(i == 42){		
		borrarPacman(i,j);
		i=0;
		movDerechaPacman	(i,j);
	}
}

// Funcion Mover Pacman
void mover(int &i, int &j)
{
			//Movimiento para Arriba
		movArribaPacman		(i,j);
		
			//Movimiento para Abajo
		movAbajoPacman		(i,j);
		
			//Movimiento para la Izquierda
		movIzquierdaPacman	(i,j);
		
			//Movimiento para la Derecha
		movDerechaPacman	(i,j);
		
		imprimirPacman(i,j);
		Sleep(100);
		
			//Movimiento por el pasadizo. Pasadizo por la izquierda
		movPasadizoIzq		(i,j);
		
			//Movimiento por el pasadizo. Pasadizo por la derecha
		movPasadizoDer		(i,j);

}
	
	/*=====================================  FANTASMAS  =====================================*/

	/*=======================================  CLYDE  =======================================*/

// Funcion para IMPRIMIR CLYDE
void imprimirClyde(int iC , int jC)
{
	setColor(color[4]);
	tablero[iC][jC] = 67;
	gotoxy(11+iC,4+jC); cout<<tablero[iC][jC];
	
}

//Hay veces en que deja una moneda sin imprimir, en movimientos horizontales, remplazar los borrarClyde por esta funcion para ver los errores

// Funcion para REIMPRIMIR COMIDA detras de CLYDE
void  imprimirComidaClyde(int iC, int jC, char movClyde){
	
	if(movClyde == UP){						//BUENA
		if(comida[jC+1][iC]== 1){
			setColor(color[7]);
			gotoxy(11+iC,4+(jC+1)); cout<<char(250);
		}
		else if(comida[jC+1][iC]== 0){
			setColor(color[7]);
			gotoxy(11+iC,4+(jC+1)); cout<<char(32);
		}
	}
	
	else if(movClyde == DOWN){				//BUENA
		if(comida[jC-1][iC]== 1){
			setColor(color[7]);
			gotoxy(11+iC,4+(jC-1)); cout<<char(250);
		}
		else if(comida[jC-1][iC]== 0){
			setColor(color[7]);
			gotoxy(11+iC,4+(jC-1)); cout<<char(32);
		}
		
	}
	
	else if(movClyde == LEFT){
		if(comida[jC][iC+1]== 1){
			setColor(color[7]);
			gotoxy(11+(iC+1),4+jC); cout<<char(250);
		}
		else if(comida[jC][iC+1]== 0){
			setColor(color[7]);
			gotoxy(11+(iC+1),4+jC); cout<<char(32);
		}
	}
	
	else if(movClyde == RIGHT){
		if(comida[jC][iC-1]== 1){
			setColor(color[7]);
			gotoxy(11+(iC-1),4+jC); cout<<char(250);
		}
		else if(comida[jC][iC-1]== 0){
			setColor(color[7]);
			gotoxy(11+(iC-1),4+jC); cout<<char(32);
		}
	}
}

// Funcion para BORRAR CLYDE
void borrarClyde(int iC, int jC){ 

	setColor(color[5]); 
	tablero[iC][jC] = 32; 
    gotoxy(11+iC,4+jC); 
	cout<<tablero[iC][jC];	
}

// Funcion RANDOM CLYDE
void randomClyde(int &movClydeAux, char &movClyde){
	
	movClydeAux = rand()%4;
	
	if      (movClydeAux == 0){movClyde = UP;}
	else if (movClydeAux == 1){movClyde = DOWN;}
	else if (movClydeAux == 2){movClyde = LEFT;}
	else if (movClydeAux == 3){movClyde = RIGHT;}
	
}

//Funcion CHOQUE CLYDE - PACMAN
	//ARREGLAR
void choqueClyde(int &i, int &j, int &iC, int &jC, int &dir, char movClyde, int anteriorpi, int anteriorpj){
	
	//if(i == iC && j == jC )
	
	if( i == iC && j == jC || (movClyde == UP && dir == 1 || movClyde == DOWN && dir == 0 || movClyde == LEFT && dir == 3 || movClyde == RIGHT && dir == 2 ) && (jC == anteriorpj && iC == anteriorpi))
	{
		if(comida[i][j]==0)
		{
			gotoxy(11+i,4+j); cout<<char(32);
		}
		
		i  = 21;
		j  = 21;
		iC = 26;
		jC = 13;
		dir = 5;
		vida = vida-1;
	}
}

// Funcion MOVER ARRIBA CLYDE
void movArribaClyde(int &iC, int &jC, int &movClydeAux, char &movClyde){
	
	if (movClyde==UP){
				
		if(space[jC-1][iC] == 0 || space[jC-1][iC] == 2 ){
			borrarClyde(iC,jC);
			jC=jC-1;
			
			if (space[jC-1][iC] == 2){
				randomClyde(movClydeAux,movClyde);
			}
		}
		else{
			randomClyde(movClydeAux,movClyde);
		}
	}
}

// Funcion MOVER ABAJO CLYDE
void movAbajoClyde(int &iC, int &jC, int &movClydeAux, char &movClyde){
	
	if (movClyde==DOWN ){
		
		if(space[jC+1][iC] == 0 || space[jC+1][iC] == 2 ){
			borrarClyde(iC,jC);
			jC=jC+1;
			
			if (space[jC+1][iC] == 2){
				randomClyde(movClydeAux,movClyde);
			}
				
		}
		else{
			randomClyde(movClydeAux,movClyde);
		}
	}
}

// Funcion MOVER IZQUIERDA CLYDE
void movIzquierdaClyde(int &iC, int &jC, int &movClydeAux, char &movClyde){
	
	if (movClyde==LEFT ){
		
		if(space[jC][iC-1] == 0 || space[jC][iC-1] == 2 ){
			borrarClyde(iC,jC);
			iC=iC-1;
			
			if (space[jC][iC-1] == 2){
				randomClyde(movClydeAux,movClyde);
			}
		}
		else if (space[jC][iC-1] == 4){
			borrarClyde(iC,jC);
			iC=iC-1;
			movClydeAux =  0;
			movClyde    = UP;
		}
		else{
			randomClyde(movClydeAux,movClyde);
		}
	}
}

// Funcion MOVER DERECHA CLYDE
void movDerechaClyde(int &iC, int &jC, int &movClydeAux, char &movClyde){
	
	if (movClyde==RIGHT){

		if(space[jC][iC+1] == 0 || space[jC][iC+1] == 2){
			borrarClyde(iC,jC);
			iC=iC+1;
			
			if (space[jC][iC+1] == 2){
				randomClyde(movClydeAux,movClyde);
			}
		}
		else{
			
			randomClyde(movClydeAux,movClyde);
		}
	}
}

// Funcion MOVER CLYDE
void moverClyde(int &iC, int &jC, char &movClyde,int &movClydeAux){
	
		//Mover Arriba Clyde
	movArribaClyde		(iC,jC, movClydeAux, movClyde);
	
		//Mover Abajo Clyde
	movAbajoClyde		(iC,jC, movClydeAux, movClyde);
	
		//Mover Izquierda Clyde
	movIzquierdaClyde	(iC,jC, movClydeAux, movClyde);
	
		//Mover Derecha
	movDerechaClyde(iC,jC, movClydeAux, movClyde);
	
	
	imprimirClyde(iC,jC);
	imprimirComidaClyde(iC,jC,movClyde);
}

	/*=======================================  BLINKY  =======================================*/

//Funcion IMPRIMIR BLINKY
void imprimirBlinky(int iB , int jB)
{
	setColor(color[1]);
	tablero[iB][jB] = 66;
	gotoxy(11+iB,4+jB); cout<<tablero[iB][jB];
	
}

// Funcion BORRAR BLINKY
void borrarBlinky(int iB, int jB){ 

	setColor(color[5]); 
	tablero[iB][jB] = 32; 
    gotoxy(11+iB,4+jB); 
	cout<<tablero[iB][jB];	
}

// Funcion MOVER IZQUIERDA BLINKY
void movIzquierdaBlinky(int &iB, int &jB, int i, int j){

	if(i<iB){
		if(space[jB][iB-1] == 0 || space[jB][iB-1] == 2){
			borrarClyde(iB,jB);
			iB=iB-1;
		}
		else if (space[jB][iB-1] == 1){
			
			//Igual a rutina movArribaBlinky
			if(j<jB){
				if(space[jB-1][iB] == 0 || space[jB-1][iB] == 2){
					borrarClyde(iB,jB);
					jB=jB-1;
				}
			}
			//Igual a rutina movAbajoBlinky
			else if(j>jB){
				if(space[jB+1][iB] == 0 || space[jB+1][iB] == 2){
					borrarClyde(iB,jB);
					jB=jB+1;
				}
			}
		}
	}
}

// Funcion MOVER DERECHA BLINKY
void movDerechaBlinky(int &iB, int &jB, int i, int j){

	if(i>iB){
		if(space[jB][iB+1] == 0 || space[jB][iB+1] == 2){
			borrarClyde(iB,jB);
			iB=iB+1;
		}
		else if (space[jB][iB+1] == 1){
			
			//Igual a rutina movArribaBlinky
			if(j<jB){
				if(space[jB-1][iB] == 0 || space[jB-1][iB] == 2){
					borrarClyde(iB,jB);
					jB=jB-1;
				}
			}
			//Igual a rutina movAbajoBlinky
			else if(j>jB){
				if(space[jB+1][iB] == 0 || space[jB+1][iB] == 2){
					borrarClyde(iB,jB);
					jB=jB+1;
				}
			}
		}
	}
}

// Funcion MOVER ARRIBA BLINKY
void movArribaBlinky(int &iB, int &jB, int i, int j){

	if(j<jB){
		if(space[jB-1][iB] == 0 || space[jB-1][iB] == 2){
			borrarClyde(iB,jB);
			jB=jB-1;
		}
		else if (space[jB-1][iB] == 1){
			movIzquierdaBlinky(iB, jB, i, j);
			movDerechaBlinky(iB, jB, i, j);
		}
	}
}

// Funcion MOVER ABAJO BLYNKY
void movAbajoBlinky(int &iB, int &jB, int i, int j){

	if(j>jB){
		if(space[jB+1][iB] == 0 || space[jB+1][iB] == 2){
			borrarClyde(iB,jB);
			jB=jB+1;
		}
		else if (space[jB+1][iB] == 1){
			movIzquierdaBlinky(iB, jB, i, j);
			movDerechaBlinky(iB, jB, i, j);
		}
	}
}

// Funcion MOVER BLINKY
void moverBlinky(int &iB, int &jB, int i, int j, int dir){
	
	// COLOCAR LO DEL CUADERNO Y ADEMAS COLOCAR CUANDO i=iB
	
	/*
	//Para Hacer que Blinky se mueva correctamente cuando comience el juego
	if(space[jB+2][iB]==4){
		if		(dir ==2 )				{movDerechaBlinky	(iB, jB, i, j);}
		else if	(dir ==3 )				{movIzquierdaBlinky	(iB, jB, i, j);}
		else if	(dir != 2 || dir != 3)	{movDerechaBlinky	(iB, jB, i, j);}
	}
	*/
	
		//Mover Arriba Blinky
	movArribaBlinky(iB, jB, i, j);
	
		//Mover Abajo Blinky
	movAbajoBlinky(iB, jB, i, j);
	
	if(j==jB)
	{
			//Mover Izquierda Blinky
		movIzquierdaBlinky(iB, jB, i, j);
		
			//Mover Derecha Blinky
		movDerechaBlinky(iB, jB, i, j);
	}
	
	imprimirBlinky(iB,jB);
	
}

	/*=======================================  PINKY  =======================================*/

// Funcion Imprimir Pinky
void imprimirPinky(int iP , int jP)
{
	setColor(color[2]);
	tablero[iP][jP] = 80;
	gotoxy(11+iP,4+jP); cout<<tablero[iP][jP];
	
}

	/*=======================================  INKY  =======================================*/

// Funcion Imprimir Inky
void imprimirInky(int iI , int jI)
{
	setColor(color[3]);
	tablero[iI][jI] = 73;
	gotoxy(11+iI,4+jI); cout<<tablero[iI][jI];
	
}

	/*========================  PANTALLAS DE GANAR Y PERDER  ======================== */

//Pantalla de GANAR
void menuYouWin(){
	
	system("cls");

	llenarTitulo();
	llenarFantasmasAzules();
	
	gotoxy(28,15);
	setColor(color[0]);
	cout<<"YOU WIN!";
	
	
	setColor(color[0]);
	gotoxy(13,21);
	cout<<"SI QUIERES VOLVER A JUGAR PRECIONA s!";
	
	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	setColor(color[0]);
	gotoxy(21,18);
	cout<<"Su ID ES:     ";
	setColor(color[5]);
	cout<<cedula;
	
	setColor(color[0]);
	gotoxy(21,19);
	cout<<"Su SCORE ES:  ";
	setColor(color[5]);
	cout<<puntos;

	gotoxy(32,23);
	cin>>respuesta;
}

//Pantalla de PERDER
void menuYouLose(){
	
	system("cls");
	
	llenarTitulo();
	llenarFantasmas();
	
	gotoxy(27,15);
	setColor(color[0]);
	cout<<"GAME OVER!";
	
	setColor(color[0]);
	gotoxy(10,21);
	cout<<"SI QUIERES VOLVER A JUGAR PRECIONA s y ENTER!";

	gotoxy(0,36);
	cout<<char(184)<<"2017-2018 MDSB";
	
	setColor(color[0]);
	gotoxy(21,18);
	cout<<"Su ID ES:     ";
	setColor(color[5]);
	cout<<cedula;
	
	setColor(color[0]);
	gotoxy(21,19);
	cout<<"Su SCORE ES:  ";
	setColor(color[5]);
	cout<<puntos;

	gotoxy(32,23);
	cin>>respuesta;
}


	/*=================================  CUERPO PRINCIPAL  ==================================*/

main()
{
	/*===========  VARIABLES ===========*/
	
	// Variable Posicion Inicial Pacman	
	
		//i=Columna j=Fila
	int  i  = 21 ,  j  = 21;
	
	int anteriorpi, anteriorpj;
		
	// Variables Posicion Inicial Fantasmas	
	
		//i=Columna j=Fila
	int   iC = 26 ,  jC = 13;	//iC,jC ----> Clyde
	int   iB = 21 ,  jB = 11; 	//iB,jB ----> BLinky
	int   iP = 19 ,  jP = 13;	//iP,jP ----> Pinky
	int   iI = 23 ,  jI = 13;	//iI,jI ----> Inky
	
		
	int hacerClyde  = 0;
	int hacerBlinky = 0;

	// Variables Movimiento Clyde
	char  movClyde ;
	int   movClydeAux;
	
	// Variable de Ciclo Juego
	bool game_over = false;
	
	ocultarCursor();
	
	while(respuesta == 's' || respuesta == 'S'){
		//Menu
		menu();
		
		if(dirMenu == 1 || dirMenu == 2 || dirMenu ==3)
		{
			system("cls");
			llenarMapa();
			marcadorFijo();
			
			/*=========== Impreciones de Matrices no Visibles ===========*/
			
				//imprimirSpace();
				//imprimirComida();
					
			/*===========  Impreciones Iniciales de Fantasmas y Pacman  ===========*/
			
			imprimirPacman	(i,j);
			imprimirClyde	(iC,jC);
			imprimirBlinky	(iB,jB);
				//imprimirPinky	(iP,jP);
				//imprimirInky	(iI,jI);
		
			randomClyde(movClydeAux, movClyde);
			
			/*===========  Imprimir Sonido Inicial  ===========*/
	
			gotoxy(0,0);
			cout<<PlaySound((LPCSTR)soundPacManInicio, NULL, SND_FILENAME | SND_ASYNC ); 
			gotoxy(0,0);
			cout<<" ";
			Sleep(4700);
			
			/*=========== Ciclo de Juego ===========*/
			
			while (game_over == false && vida>0 && dir != 4 && puntos<18600){
				
				//Reinicializar al pasar de nivel
				if(puntos == 3320 || puntos == 7140 || puntos == 10960 || puntos == 14780){
					puntos = puntos + 500 + 20; //Los 20 son del punto del lugar donde se encuentra el pcmn
					nivel  = nivel  + 1;
					vida   = vida   + 3;
					dir    = 0;
					
					i  = 21 ,  j  = 21;
			
					iC = 26 ,  jC = 13;	//iC,jC ----> Clyde
					iB = 21 ,  jB = 11; //iB,jB ----> BLinky
					iP = 19 ,  jP = 13;	//iP,jP ----> Pinky
					iI = 23 ,  jI = 13;	//iI,jI ----> Inky
					
					hacerClyde  = 0;
					hacerBlinky = 0;
					
					char tablero[29][44] = {
				     "AxxxxxxxxxxxxxxxxxxxB AxxxxxxxxxxxxxxxxxxxB",
				     "I________+__________I I__________+________I",
				     "I_AxxxxxB_AxxxxxxxB_I I_AxxxxxxxB_AxxxxxB_I",
				     "I_I     I_I       I_I I_I       I_I     I_I",
				     "I_DxxxxxC_DxxxxxxxC_DxC_DxxxxxxxC_DxxxxxC_I",
				     "I+_______+___+_____+___+_____+___+_______+I",
				     "I_AxxxxxB_AxB_AxxxxxxxxxxxxxB_AxB_AxxxxxB_I",
				     "I_DxxxxxC_I I_DxxxxB   AxxxxC_I I_DxxxxxC_I",
				     "I________+I I______I   I______I I+________I",
				     "DxxxxxxxB_I DxxxxB I   I AxxxxC I_AxxxxxxxC",
				     "        I_I AxxxxC DxxxC DxxxxB I_I        ",
				     "        I_I I                 I I_I        ",
				     "xxxxxxxxC_DxC Axxxxxx xxxxxxB DxC_Dxxxxxxxx",
				     "         +    I      *      I    +         ",
				     "xxxxxxxxB_AxB DxxxxxxxxxxxxxC AxB_Axxxxxxxx",
				     "        I_I I                 I I_I        ",
				     "        I_I I AxxxxxxxxxxxxxB I I_I        ",
				     "AxxxxxxxC_DxC DxxxxB   AxxxxC DxC_DxxxxxxxB",
				     "I________+_________I   I_________+________I",
				     "I_AxxxxxB_AxxxxxxB_I   I_AxxxxxxB_AxxxxxB_I",
				     "I_DxxxB I_DxxxxxxC_DxxxC_DxxxxxxC_I AxxxC_I",
				     "I_____I I+________+_____+________+I I_____I",
				     "DxxxB_I I_AxB_AxxxxxxxxxxxxxB_AxB_I I_AxxxC",
				     "AxxxC_DxC_I I_DxxxxB   AxxxxC_I I_DxC_DxxxB",
				     "I____+____I I______I   I______I I____+____I",
				     "I_AxxxxxxxC DxxxxB_I   I_AxxxxC DxxxxxxxB_I",
				     "I_DxxxxxxxxxxxxxxC_DxxxC_DxxxxxxxxxxxxxxC_I",
				     "I_________________+_____+_________________I",
				     "DxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxC",
					};
					
					system("cls");
					llenarMapa();
					marcadorFijo();	
					
					imprimirPacman	(i,j);
					imprimirClyde	(iC,jC);
					imprimirBlinky	(iB,jB);
	
					randomClyde(movClydeAux, movClyde);
					
					Sleep(2500);
				}
				
				//Aca comienza el ciclo 
				anteriorpi = i; anteriorpj = j;
				
				teclear();
				mover(i,j);
				
				choqueClyde(i, j, iC, jC, dir, movClyde, anteriorpi, anteriorpj);
				
				anteriorpi = i; anteriorpj = j;
				
				
				hacerClyde++;
				if(hacerClyde%3==0){	
					moverClyde(iC, jC, movClyde, movClydeAux);
				}
				
				
				hacerBlinky++;
				if(hacerBlinky%2==0){
					moverBlinky(iB,jB,i,j, dir);
				}
				
			}
		}
		
		
		if(puntos == 18600 ){
			menuYouWin();
		}
		else if(vida == 0){
			menuYouLose();
		}
		
		if(respuesta == 's' || respuesta == 'S')
		{
			system("cls");
			
			//reinicializacion de todo
			puntos  = 20;
			nivel   = 1;
			vida    = 3;
			dirMenu = 0;
			dir     = 0;
			cedula  = 0;
			char tecla  = '.';
			char opcion = '.';
			
			
			i  = 21 ,  j  = 21;
	
			iC = 26 ,  jC = 13;	//iC,jC ----> Clyde
			iB = 21 ,  jB = 11; //iB,jB ----> BLinky
			iP = 19 ,  jP = 13;	//iP,jP ----> Pinky
			iI = 23 ,  jI = 13;	//iI,jI ----> Inky
			
			hacerClyde  = 0;
			hacerBlinky = 0;
					
			char tablero[29][44] = {
		     "AxxxxxxxxxxxxxxxxxxxB AxxxxxxxxxxxxxxxxxxxB",
		     "I________+__________I I__________+________I",
		     "I_AxxxxxB_AxxxxxxxB_I I_AxxxxxxxB_AxxxxxB_I",
		     "I_I     I_I       I_I I_I       I_I     I_I",
		     "I_DxxxxxC_DxxxxxxxC_DxC_DxxxxxxxC_DxxxxxC_I",
		     "I+_______+___+_____+___+_____+___+_______+I",
		     "I_AxxxxxB_AxB_AxxxxxxxxxxxxxB_AxB_AxxxxxB_I",
		     "I_DxxxxxC_I I_DxxxxB   AxxxxC_I I_DxxxxxC_I",
		     "I________+I I______I   I______I I+________I",
		     "DxxxxxxxB_I DxxxxB I   I AxxxxC I_AxxxxxxxC",
		     "        I_I AxxxxC DxxxC DxxxxB I_I        ",
		     "        I_I I                 I I_I        ",
		     "xxxxxxxxC_DxC Axxxxxx xxxxxxB DxC_Dxxxxxxxx",
		     "         +    I      *      I    +         ",
		     "xxxxxxxxB_AxB DxxxxxxxxxxxxxC AxB_Axxxxxxxx",
		     "        I_I I                 I I_I        ",
		     "        I_I I AxxxxxxxxxxxxxB I I_I        ",
		     "AxxxxxxxC_DxC DxxxxB   AxxxxC DxC_DxxxxxxxB",
		     "I________+_________I   I_________+________I",
		     "I_AxxxxxB_AxxxxxxB_I   I_AxxxxxxB_AxxxxxB_I",
		     "I_DxxxB I_DxxxxxxC_DxxxC_DxxxxxxC_I AxxxC_I",
		     "I_____I I+________+_____+________+I I_____I",
		     "DxxxB_I I_AxB_AxxxxxxxxxxxxxB_AxB_I I_AxxxC",
		     "AxxxC_DxC_I I_DxxxxB   AxxxxC_I I_DxC_DxxxB",
		     "I____+____I I______I   I______I I____+____I",
		     "I_AxxxxxxxC DxxxxB_I   I_AxxxxC DxxxxxxxB_I",
		     "I_DxxxxxxxxxxxxxxC_DxxxC_DxxxxxxxxxxxxxxC_I",
		     "I_________________+_____+_________________I",
		     "DxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxC",
			};
		}
	}
	system("pause>nul"); 
}
