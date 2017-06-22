#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
//#include <SDL_image.h>
#include <SDL_ttf.h>
#include "S_Robo.h"
#include "Rendering.h"
#include "UtilsDG.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

/*
* Initialize the structures and the windows as render
*	W=width and H= heigth
*	returns true if succesful
*/
Rend_Struct *init(int W, int H){

	Rend_Struct *Vars = nullptr;


	Vars = (Rend_Struct *)malloc(sizeof(Rend_Struct));
	
	if(Vars){
		Vars->RoboData = nullptr;

				if(!initRender(Vars,W,H))
					return nullptr;
	}
	else
		return nullptr;

	return Vars;
}

int main( int argc, char* args[] )
{
	Rend_Struct* Vars = nullptr;
	if( !(Vars = init(SCREEN_WIDTH, SCREEN_HEIGHT)) ){
		printf("Fail\n");
	}
	else
	{
		//main_Robo(Vars->RoboData);
		MainLoopRender(Vars);

	}
	Destroy(Vars);
	return 0;
}