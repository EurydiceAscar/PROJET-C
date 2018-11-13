#include "librairies.h"

#define gotoxy(l,m) printf("\033[%d;%dH", l, m)

char key_pressed();
void remplir_obstacles();
void charger_map();
void afficher_map();
void effacer_tank(int X,int Y);
void afficher(int* XP,int* YP, int dir,int orientation,int MOVE);
void charger_tanks();
void test();
//void creer_obus(int X,int Y);


