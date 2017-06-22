#ifndef RENDERING_H_INC
#define	RENDERING_H_INC
#include "S_Robo.h"
#include <SDL.h>
#include <SDL_ttf.h>

#define STARTINGCOLOR 230, 163, 69
#define WINDOWTITLE "Dg's G. Engine - WIP"



//Key press surfaces constants
enum ImgEnum
{
    OBST,
    ROBO_ON,
    ROBO_OFF,
	DIRTY,
	EMPTY,
    IMG_TOTAL
};

enum MenuOPT_enum
{
	PlayOPT,
	OptionOPT,
	ExitOPT,
	TotalOPT
};

enum PlayMode
{
	MenuMD,
	PlayMD,
	PauseMD

};

typedef struct stringlist
{
	char String[20];
}StringList;

typedef struct menuopt
{
	int OptionSelected;
	bool EnterPressed;
	StringList OPTArray[TotalOPT];

}MenuOPT;

typedef struct img_list
{
	SDL_Texture* Img_Texture;
	SDL_Surface* Img_Surf;
	int IMG_W;
	int IMG_H;
	char Path[51];

}IMG_List;

typedef struct rend_Structure
{
	SDL_Window* window; //The Window where stuff appears

	SDL_Surface* windowSurface; //The surface thats going to be used in the window (IF USING SW RENDERING)
	
	
	SDL_Renderer* gRenderer;//The window renderer, what will appear (IF USING HW RENDERING)

	SDL_Texture* mainTexture;//The texture main

	IMG_List imgArray[ IMG_TOTAL ];
	
	//Text Font
	TTF_Font* gFont;
	SDL_Texture* TextTexture;
	int TextW;
	int TextH;
	
	//All the info about robots
	Robo_Struct* RoboData;


	MenuOPT VarMenuOpt;

}Rend_Struct;

SDL_Surface *LoadBMP(char *Dir);

SDL_Texture* loadTexture(char *Dir, SDL_Renderer *Renderer, bool ColorK);

int SetWindowIcon(char *Dir, SDL_Window* Window);

void MainLoopRender(Rend_Struct *Vars);

bool initRender(Rend_Struct *Vars, int W ,int H);

void Destroy(Rend_Struct *Vars);
#endif // !RENDERING_H_INC
