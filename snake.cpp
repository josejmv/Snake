#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

#define arriba 72
#define izquierda 75
#define derecha 77
#define abajo 80
#define esc 27
#define enter 13

int cuerpo[200][2],n=1;
int tam=3;
int x=10,y=12;
int i;
int dir = 3;
int velocidad=100,cambio=1;
int puntuacion=0;
int xc=30,yc=15;
int a,b,c,d;

int p;

char tecla;

void gotoxy(int x1, int y1)
{
	HANDLE hcon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X=x1;
	dwpos.Y=y1;
	SetConsoleCursorPosition (hcon,dwpos);
}


void mapa()
{
	for (i=2;i<78;i++)
	{
		gotoxy(i,3);
		printf("%c",205);
		gotoxy(i,23);
		printf("%c",205);
	}
	
	for (i=4;i<23;i++)
	{
	gotoxy(2,i);
	printf("%c",186);
	gotoxy(77,i);
	printf("%c",186);
	}
	
	gotoxy(2,3);
	printf("%c",201);
	gotoxy(2,23);
	printf("%c",200);
	gotoxy(77,3);
	printf("%c",187);
	gotoxy(77,23);
	printf("%c",188);
}


void guardar_posicion()
{
	cuerpo[n][0] = x;
	cuerpo [n][1] = y;
	n++;

	if (n==tam)
	n=1;
}

void pintar_cuerpo()
{
	for (i=1;i<tam;i++)
	{
		gotoxy (cuerpo[i][0], cuerpo[i][1]);
		printf("*");
	}
}

void borrar_cuerpo()
{
	gotoxy (cuerpo[n][0], cuerpo[n][1]);
	printf(" ");
}

void teclear()
{
	if (kbhit())
		{
			tecla = getch();
			switch (tecla)
			{
				case arriba:
					if (dir!=2)
						dir=1;
						break;
			
				case abajo:
					if (dir!=1)
						dir=2;
						break;
			
				case derecha:
					if (dir!=4)
						dir=3;
						break;
						
				case izquierda:
					if (dir!=3)
						dir=4;
						break;
		}
	}
}

void puntos()
{
	gotoxy (3,1);
	printf("score %i",puntuacion);	
}

void cambiar_velocidad()
{
	if (puntuacion==cambio*20 && puntuacion<190)
	{
		velocidad-=10;
		cambio++;
	}
}

void comida()
{
	if (x==xc && y==yc)
	{
		xc=(rand()%73)+4;
		yc=(rand()%19)+4;
		tam++;
		puntuacion+=10;
		gotoxy(xc,yc);
		printf("%c",157);
		
		cambiar_velocidad();
	}
}

bool game_over()
{
	if (y==3 xor y==23 xor x==2 xor x==77)
	return true;
	for (int j=tam-1;j>0;j--)
	{
		if (cuerpo [j][0] == x && cuerpo[j][1]==y)
		return true;
	}
	
	return false;
}

void fin()
{
	if (puntuacion<240)
	{
	system ("color 0c");
	gotoxy (39,1);
	printf("~(u.u)~ GAME OVER ~(u.u)~ ");
	gotoxy (1,24);
	}
	
	if (puntuacion == 240)
	{
	system ("color 0a");
	gotoxy (39,1);
	printf("(~'-')~ VICTORIA ~('-'~)");
	gotoxy (1,24);
	}
}

int main()
{
	system ("color 0b");
	mapa();
	
	
	gotoxy(xc,yc);
	printf("%c",157);
	
	while (tecla!=esc && !game_over() && puntuacion!=250)
	{
		
	borrar_cuerpo();
	guardar_posicion();
	pintar_cuerpo();
	puntos();
	comida();
	teclear();
	teclear();
	teclear();
		
	if (dir==1) y--;
	if (dir==2) y++;
	if (dir==3) x++;
	if (dir==4) x--;
	
	
	if (puntuacion==50)
	system ("color 0b");
	if (puntuacion==100)
	system ("color 0d");
	if(puntuacion==150)
	system("color 0f");
	if (puntuacion==200)
	system("color 09");
	
	Sleep (velocidad);
	}	
	
	fin();
	
}
