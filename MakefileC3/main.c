#include "librairies.h"
#include "fonctions.h"

int x;
int y;
int dir;
int* xp=&x;
int* yp=&y;
int orientation;

int main(){
	x=20;
	y=30;
	dir=-1;
	orientation=0;
	int move=0;
	char key;
	system("clear");
	system("setterm -cursor off");
	system("stty -echo");
	remplir_obstacles();
	charger_map();
	charger_tanks();
	afficher_map();
	gotoxy(x,y);
	printf("╔╗");
	gotoxy(x+1,y);
	printf("╚╝\n");
	srand(time(NULL));
	while((key=key_pressed()) != 'q'){
		switch(key){
			case 'A':
				move=1;
				if(orientation==0){
					dir=0;
				}
				else{
					orientation=0;
				}
				break;
			case 'B':
				move=1;
				if(orientation==1){
					dir=1;
				}
				else{
					orientation=1;
				}
				break;
			case 'C':
				move=1;
				if(orientation==2){
					dir=2;
				}
				else{
					orientation=2;
				}
				break;
			case'D':
				move=1;
				if(orientation==3){
					dir=3;
				}
				else{
					orientation=3;
				}
				break;
			case 'c':
				test();
				//creer_obus(x,y,orientation);
				break;
			case 't':
				system("stty echo");
				system("setterm -cursor on");
				break;
			case 'h':
				gotoxy(50,50);
				printf("%d %d %d",x,y,dir);
				break;
		}
		afficher(xp,yp,dir,orientation,move);
		dir=-1;
		move=0;
		//afficher(x,y,dir);
	}
        return 0;
}
