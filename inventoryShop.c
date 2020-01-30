#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

struct Objet{
	int prix;
  char nom[20];
	};
typedef struct Objet objet;



void color(int t,int f){
  	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  	SetConsoleTextAttribute(H,f*16+t);
}

int main(){

return 0;
}
