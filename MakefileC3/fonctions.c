#include "librairies.h"
#include "fonctions.h"

#define gotoxy(l,m) printf("\033[%d;%dH", l, m)

int x;
int y;
int dir;
int orientation;
int obsx[398];
int obsy[398];
char loaded_map[48][158];
char tank_b[6][33];
char tank_h[6][33];
char tank_g[6][33];
char tank_d[6][33];

void test(){
	system("clear");
	gotoxy(1,1);
	for(int i=0;i<6;i++){
		gotoxy(1+i,1);
		for(int j=0;j<13;j++){
			printf("%c",tank_h[i][j]);
		}
		printf("\n");
	}
}

void charger_tanks(){
	FILE* fichier= fopen("tank_b","r");
	for(int i=0;i<6;i++){
		fgets(tank_b[i],33,fichier);
		fseek(fichier,0,SEEK_CUR);
	}
	fclose(fichier);

	FILE* fichier2= fopen("tank_h","r");
	for(int i=0;i<6;i++){
		fgets(tank_h[i],33,fichier2);
		fseek(fichier2,0,SEEK_CUR);
	}
	fclose(fichier2);

	FILE* fichier3= fopen("tank_g","r");
	for(int i=0;i<6;i++){
		fgets(tank_g[i],33,fichier3);
		fseek(fichier3,0,SEEK_CUR);
	}
	fclose(fichier3);

	FILE* fichier4= fopen("tank_d","r");
	for(int i=0;i<6;i++){
		fgets(tank_d[i],33,fichier4);
		fseek(fichier4,0,SEEK_CUR);
	}
	fclose(fichier4);
}

char key_pressed(){
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO,TCSANOW, &oldterm);
	if (c != EOF) {ungetc(c, stdin); result = getchar();}
	return result;
}

void remplir_obstacles(){
	for(int i=0;i<153;i++){
		obsy[i]=i;
		obsx[i]=0;
	}
	for(int i=153;i<200;i++){
		obsx[i]=i-152;
		obsy[i]=0;
	}
	for(int i=200;i<352;i++){
		obsx[i]=48;
		obsy[i]=i-199;
	}
	for(int i=352;i<398;i++){
		obsx[i]=i-351;
		obsy[i]=152;
	}
}

void charger_map(){
	FILE* fichier= fopen("map","r");
	for(int i=0;i<48;i++){
		fgets(loaded_map[i],158,fichier);
		fseek(fichier,0,SEEK_CUR);
	}
	fclose(fichier);
}

void afficher_map(){
	gotoxy(0,0);
	for(int i=0;i<48;i++){
		printf("%s",loaded_map[i]);
	}
}

void effacer_tank(int X,int Y){
	for(int i=0;i<6;i++){
		gotoxy(X+i,Y);
		for(int j=0;j<33;j++){
			printf("%c",loaded_map[X-1+i][Y-1+j]);
		}
		printf("\n");
	}
}

void afficher(int* XP,int* YP,int dir,int or,int MOVE){
	int bloque=0;
	int next_x=0;
	int next_y=0;
	switch(dir){
		case 0:
			next_x=-1;
			break;
		case 1:
			next_x=1;
			break;
		case 2:
			next_y=1;
			break;
		case 3:
			next_y=-1;
			break;
	}
	for(int i=0;i<sizeof(obsx)/sizeof(int);i++){
		if(obsx[i]==(*XP)+next_x*2 && obsy[i]==(*YP)+next_y*2){
			bloque=1;
			gotoxy(0,0);
			printf("BLOQUE\n");
		}
	}
	if(bloque==0){
		if(MOVE==1){
				effacer_tank(x,y);
		}
		(*XP)+=next_x;
		(*YP)+=next_y;
	}
	gotoxy(*XP,*YP);
	switch(or){
		case 0:
			for(int i=0;i<6;i++){
				gotoxy(*XP+i,*YP);
				for(int j=0;j<33;j++){
					printf("%c",tank_h[i][j]);
				}
				printf("\n");
			}
			break;
		case 1:
			for(int i=0;i<6;i++){
				gotoxy(*XP+i,*YP);
				for(int j=0;j<33;j++){
					printf("%c",tank_b[i][j]);
				}
				printf("\n");
			}
			break;
		case 2:
			for(int i=0;i<6;i++){
				gotoxy(*XP+i,*YP);
				for(int j=0;j<33;j++){
					printf("%c",tank_d[i][j]);
				}
				printf("\n");
			}
			break;
		case 3:
			for(int i=0;i<6;i++){
				gotoxy(*XP+i,*YP);
				for(int j=0;j<33;j++){
					printf("%c",tank_g[i][j]);
				}
				printf("\n");
			}
			break;
	}
}

