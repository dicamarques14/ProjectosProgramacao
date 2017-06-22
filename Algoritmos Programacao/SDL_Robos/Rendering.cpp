#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
//#include <SDL_image.h>
#include <string.h>
#include <SDL_ttf.h>
#include "Rendering.h"
#include "S_Robo.h"
#include <time.h>

SDL_Color WhiteIsh = {255,255,255};
SDL_Color OrangeIsh = {230, 163, 69};
SDL_Color PurpleIsh = {162,0,255};
SDL_Color GreenIsh = {126,176,17};

SDL_Surface *LoadBMP(char *Dir){
	SDL_Surface *ret = SDL_LoadBMP(Dir);
	if( !ret)
		printf("LoadBMP ERROR: Dir[%s] SDL_ERRRO: %s\n",Dir,SDL_GetError());
	
	return ret;
}

SDL_Texture* loadTexture(char *Dir, SDL_Renderer *Renderer, bool ColorK){
	
	SDL_Texture* newTexture = NULL;
	
	//Load default surface
	SDL_Surface* loadedSurface = LoadBMP( Dir );
	if(!loadedSurface)
		return NULL;
	else
	{
		if(ColorK)
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! \n", Dir);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}

SDL_Texture* loadFromRenderedText(Rend_Struct *Vars, char *textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	
	SDL_Texture* mTexture = NULL;
	//Render text surface
	//SDL_Surface* textSurface = TTF_RenderText_Solid( Vars->gFont, textureText, textColor );
	SDL_Surface* textSurface = TTF_RenderText_Blended( Vars->gFont, textureText, textColor );

	if( textSurface == NULL )
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );

	else
	{
		//Create texture from surface pixels
       mTexture = SDL_CreateTextureFromSurface( Vars->gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			
			//Get image dimensions
			Vars->TextW = textSurface->w;
			Vars->TextH = textSurface->h;
			
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture;
}

int SetWindowIcon(char *Dir, SDL_Window* Window){
	int success = 1;
	SDL_Surface *Icon = LoadBMP(Dir);
	if(Icon){
		SDL_SetWindowIcon(Window, Icon);
		SDL_FreeSurface(Icon);
	}
	else
		success = 0;

	return success;
}

bool PrintText(Rend_Struct *Vars, char *TextToShow, int X, int Y, SDL_Color textColor){
	bool success = false;
	SDL_Rect PlaceTXT;
	PlaceTXT.x = X;
	PlaceTXT.y = Y;
	
	//destroy the old one
	if(Vars->TextTexture)
		SDL_DestroyTexture(Vars->TextTexture);

	Vars->TextTexture = loadFromRenderedText(Vars, TextToShow, textColor );
	
	if(Vars->TextTexture){
		PlaceTXT.h = Vars->TextH;
		PlaceTXT.w = Vars->TextW;
		SDL_RenderCopy( Vars->gRenderer, Vars->TextTexture, NULL, &PlaceTXT );
		
		
		success = true;
	}

	return success;
}

bool PrintImage(Rend_Struct *Vars,int imageID,int X,int Y){
	bool success = false;
	SDL_Rect PlaceIMG;
	PlaceIMG.x = X;
	PlaceIMG.y = Y;
	if(Vars->imgArray[imageID].Img_Texture){
		PlaceIMG.h = Vars->imgArray[imageID].IMG_H /2;
		PlaceIMG.w = Vars->imgArray[imageID].IMG_W /2;

		SDL_RenderCopy( Vars->gRenderer, Vars->imgArray[imageID].Img_Texture, NULL, &PlaceIMG);
		success = true;
	}
	return success;
}

bool DrawMatrixTable(Rend_Struct *Vars){
	int X = Vars->RoboData->M->nX;
	int Y = Vars->RoboData->M->nY;

	SDL_SetRenderDrawColor( Vars->gRenderer, 0, 0, 0, 255);
	int StartX = 20;
	int StartY = 0;

	SDL_Rect Matrix;
	Matrix.x = StartX;
	Matrix.y = StartY;
	Matrix.h = Matrix.w = Vars->imgArray[0].IMG_H/2 ;
	for (int i = 0; i < X; i++)
	{
		
		SDL_RenderDrawRect(Vars->gRenderer, &Matrix);
		
		for (int j = 0; j < Y; j++)
		{
			SDL_RenderDrawRect(Vars->gRenderer, &Matrix);
			Matrix.y += Matrix.h;
		}
		Matrix.y = StartY;
		Matrix.x += Matrix.w;
	}

	SDL_SetRenderDrawColor(Vars->gRenderer, STARTINGCOLOR, 255);

	Matriz *M = Vars->RoboData->M;
	SDL_Color textColor = { 50, 55, 55 };
	int cont = 0;
	for (int i = 0; i < M->nY; i++)//por cada linha
	{
		for (int j = 0; j < M->nX; j++){//por cada coluna
			if(M->Dados[cont] == 'X')
				PrintImage(Vars,OBST,StartX+(j*Matrix.w),StartY+(i*Matrix.h));
			else if(M->Dados[cont] == 'R'){

			}
			else if(M->Dados[cont] == '0')
				PrintImage(Vars,DIRTY,StartX+(j*Matrix.w),StartY+(i*Matrix.h));
			else
				PrintImage(Vars,EMPTY,StartX+(j*Matrix.w),StartY+(i*Matrix.h));

			cont++;
		}
	}
	for (int i = 0; i < Vars->RoboData->Imperio->QtdRobo; i++)
	{
		if (Vars->RoboData->Imperio->R[i].activo)
			PrintImage(Vars,ROBO_ON,StartX+(Vars->RoboData->Imperio->R[i].xAct *Matrix.w),StartY+(Vars->RoboData->Imperio->R[i].yAct *Matrix.h));
		else
			PrintImage(Vars,ROBO_OFF,StartX+(Vars->RoboData->Imperio->R[i].xAct *Matrix.w),StartY+(Vars->RoboData->Imperio->R[i].yAct *Matrix.h));
		PrintText(Vars,Vars->RoboData->Imperio->R[i].id,StartX+(Vars->RoboData->Imperio->R[i].xAct *Matrix.w)+17,StartY+(Vars->RoboData->Imperio->R[i].yAct *Matrix.h),textColor);
	}

	return true;
}

void DrawBatery(Rend_Struct *Vars, SDL_Rect* Matrix, int Batery, int Ratio){
	SDL_Rect BatPosition;
	BatPosition.x = Matrix->x+16+48+5;
	BatPosition.y = Matrix->y+50;
	BatPosition.h = 16+2; //16 altura do interior
	BatPosition.w = 50; //48 comp. interior
	SDL_SetRenderDrawColor( Vars->gRenderer, 0, 0, 0, 255);
	
	SDL_RenderDrawRect(Vars->gRenderer, &BatPosition);//Big square

	BatPosition.x = BatPosition.x+1;
	BatPosition.y = BatPosition.y+1;
	BatPosition.h = BatPosition.h-2;
	BatPosition.w = (BatPosition.w-2)/Ratio;

	SDL_SetRenderDrawColor( Vars->gRenderer, 0, 240, 0, 255);
//	
/*
	BatPosition.h = 14;
	BatPosition.w = (BatPosition.w-3)/(1000/Ratio + 1);
	BatPosition.y += 2;
*/	
	int Divi = BATInicial/Ratio;
	if(Batery>0){
		for (int i = 0; i < (Batery/Divi)+1; i++)
		{
		/*	if(i == Ratio)
				BatPosition.x = BatPosition.x-2;
			*///BatPosition.x += 2;
			SDL_RenderDrawRect(Vars->gRenderer, &BatPosition);
			SDL_RenderFillRect(Vars->gRenderer, &BatPosition);
			BatPosition.x += BatPosition.w;
			
		}
	}
	
}

bool DrawBotStats(Rend_Struct *Vars){
	SDL_Color textColor = { 128, 0, 128 };
	SDL_Rect Matrix;
	Matrix.x = 750;
	Matrix.y = 0;
	Matrix.h = 98;
	Matrix.w = 520;
	char buffer[250];
	
	for (int i = 0; i < Vars->RoboData->Imperio->QtdRobo; i++)
	{
		SDL_SetRenderDrawColor( Vars->gRenderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(Vars->gRenderer, &Matrix);
		if(Vars->RoboData->Imperio->R[i].activo)
			PrintImage(Vars,ROBO_ON,Matrix.x+16,Matrix.y+24);
		else
			PrintImage(Vars,ROBO_OFF,Matrix.x+16,Matrix.y+24);
		strcpy(buffer,"ID: ");
		strcat(buffer,Vars->RoboData->Imperio->R[i].id);
		PrintText(Vars,buffer,Matrix.x+16+48+5,Matrix.y+10,textColor);
		DrawBatery(Vars,&Matrix, Vars->RoboData->Imperio->R[i].bateria,9);
		Matrix.y += 98+4;
	}
	
	SDL_SetRenderDrawColor(Vars->gRenderer, STARTINGCOLOR, 255);

	return true;
}


int sw_INGame_Action(Rend_Struct *Vars, SDL_Event *EventList){
	int ret = 0;
	SDL_Color textColor = { 0, 0, 0 };
		
	switch (EventList->key.keysym.sym)
	{
		case SDLK_ESCAPE:{
			printf("KEY_PRESS_ESCAPE [%d]\n",EventList->key.keysym.sym);
			//PrintImage(Vars,OBST,50,50);
			ret = SDLK_ESCAPE;
			break;
		}
		case SDLK_1:{
			printf("KEY_PRESS_1 [%d]\n",EventList->key.keysym.sym);
			PrintImage(Vars,OBST,50,50);
			break;
		}
		case SDLK_UP:{
			
			printf("KEY_PRESS_UP [%d]\n",EventList->key.keysym.sym);
			SDL_RenderClear( Vars->gRenderer );
			if(PrintText(Vars,"KEY_PRESS_UP",2,10,textColor))
				ret = 1;
			break;
		}
		case SDLK_DOWN:{
			
			printf("KEY_PRESS_DOWN [%d]\n",EventList->key.keysym.sym);
			SDL_RenderClear( Vars->gRenderer );
			if(PrintText(Vars,"KEY_PRESS_DOWN",2,10,textColor))
				ret = 1;	
			break;
		}
		case SDLK_LEFT:{
			
			printf("KEY_PRESS_LEFT [%d]\n",EventList->key.keysym.sym);
			SDL_RenderClear( Vars->gRenderer );
			if(PrintText(Vars,"KEY_PRESS_LEFT",2,10,textColor))
				ret = 1;
			break;
		}
		case SDLK_RIGHT:{
			
			printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			SDL_RenderClear( Vars->gRenderer );
			if(PrintText(Vars,"KEY_PRESS_RIGHT",2,10,textColor))
				ret = 1;
			break;
		}

		default:{
			printf("KEY_PRESS_SURFACE_DEFAULT [%d]\n",EventList->key.keysym.sym);
			break;
		}
	}
	return ret;
}

	int x = 30;
	int y = 20;

int sw_MENU_Action(MenuOPT *VarMenuOpt, SDL_Event *EventList){
	int ret = 0;
	SDL_Color textColor = { 0, 0, 0 };
		
	switch (EventList->key.keysym.sym)
	{
		case SDLK_ESCAPE:{
			printf("KEY_PRESS_ESCAPE [%d]\n",EventList->key.keysym.sym);
			//PrintImage(Vars,OBST,50,50);
			break;
		}
		case SDLK_RETURN:{
			
			//printf("KEY_PRESS_Return [%d]\n",EventList->key.keysym.sym);
			VarMenuOpt->EnterPressed=true;
			ret = 1;
			break;
		}
		case SDLK_UP:{
			
			//printf("KEY_PRESS_UP [%d]\n",EventList->key.keysym.sym);
			if(VarMenuOpt->OptionSelected>0)
				VarMenuOpt->OptionSelected--;
			ret = 1;
			break;
		}
		case SDLK_DOWN:{
			
			//printf("KEY_PRESS_DOWN [%d]\n",EventList->key.keysym.sym);
			if(VarMenuOpt->OptionSelected < TotalOPT-1)
				VarMenuOpt->OptionSelected++;
			
			ret = 1;	
			break;
		}
		case SDLK_LEFT:{
			
			//printf("KEY_PRESS_LEFT [%d]\n",EventList->key.keysym.sym);
			
			ret = 1;
			break;
		}
		case SDLK_RIGHT:{
			
			//printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			
			ret = 1;
			break;
		}
		case SDLK_a:{
			
			//printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			x--;
			ret = 1;
			break;
		}
		case SDLK_s:{
			
			//printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			y++;
			ret = 1;
			break;
		}
		case SDLK_d:{
			
			//printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			x++;
			ret = 1;
			break;
		}
		case SDLK_w:{
			
			//printf("KEY_PRESS_RIGHT [%d]\n",EventList->key.keysym.sym);
			y--;
			ret = 1;
			break;
		}

		default:{
			//printf("KEY_PRESS_SURFACE_DEFAULT [%d]\n",EventList->key.keysym.sym);
			
			break;
		}
	}
	return ret;
}

char* GetTXTInput(rend_Structure* Vars){
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //Set text color as black
    SDL_Color textColor = { 0, 0, 0, 0xFF };

    //The current input text.
    char* inputText = "Some Text";
	PrintText(Vars, inputText, 100, 50, textColor); 

    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( !quit )
    {
        //The rerender text flag
        bool renderText = false;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {

			if( e.type == SDL_KEYDOWN )
				{
					//Handle backspace
					if( e.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0 )
					{
						//lop off character
						inputText[ strlen(inputText) ] = '/0';
						renderText = true;
					}
					//Handle copy
					else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
					{
						SDL_SetClipboardText( inputText );
					}
					//Handle paste
					else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
					{
						inputText = SDL_GetClipboardText();
						renderText = true;
					}
				}

            //Special text input event
            else if( e.type == SDL_TEXTINPUT )
            {
                //Not copy or pasting
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                    //Append character
                    //inputText += e.text.text;
                    renderText = true;
                }
            }
        }
	}

	    //Disable text input
    SDL_StopTextInput();
	return inputText;
}

void MenuRender(Rend_Struct *Vars, bool *Leave, int *GameState){
		
	SDL_Rect RectMenuOpt;
	SDL_Event EventList;

	PrintText(Vars, "Assassins' Roomba",x,y,PurpleIsh);
	TTF_SetFontOutline(Vars->gFont, 1);
	PrintText(Vars, "Assassins' Roomba",32,22,GreenIsh);
	TTF_SetFontOutline(Vars->gFont, 0);
			
	RectMenuOpt.x = 30; RectMenuOpt.y = 100; RectMenuOpt.h = 40; RectMenuOpt.w = 200;
			
	for (int i = 0; i < TotalOPT; i++)//renders the menu options
	{
		SDL_SetRenderDrawColor( Vars->gRenderer, 20,255,255,255);
		SDL_RenderDrawRect(Vars->gRenderer,&RectMenuOpt);
				
		if (Vars->VarMenuOpt.OptionSelected == i)//highlight option
		{
			SDL_SetRenderDrawColor( Vars->gRenderer, 0,0,128,255);
		}
		SDL_RenderFillRect(Vars->gRenderer, &RectMenuOpt);
		PrintText(Vars,Vars->VarMenuOpt.OPTArray[i].String,RectMenuOpt.x+20,RectMenuOpt.y,PurpleIsh);
		RectMenuOpt.y += 50;
	}

	//Handle events on queue
	while( SDL_PollEvent( &EventList ) != 0 ){
		//User requests quit
		if( EventList.type == SDL_QUIT )
			*Leave = true;

		else if (EventList.type == SDL_KEYDOWN){
			sw_MENU_Action(&Vars->VarMenuOpt, &EventList);
			if(Vars->VarMenuOpt.EnterPressed){
				if(Vars->VarMenuOpt.OptionSelected == PlayOPT){
					if( !(Vars->RoboData = initRobo()) )
						return;
					*GameState = PlayMD;
				}

					
				if(Vars->VarMenuOpt.OptionSelected == OptionOPT)
					*GameState = MenuMD;//undone
				if(Vars->VarMenuOpt.OptionSelected == ExitOPT)
					*Leave = true;
				Vars->VarMenuOpt.EnterPressed = false;
			}

		}
	}
}

void PlayRender(Rend_Struct *Vars, bool *Leave, int *GameState, int *TempoPrintEcra){
	SDL_Event EventList;
		//Handle events on queue
		while( SDL_PollEvent( &EventList ) != 0 ){
			//User requests quit
			if( EventList.type == SDL_QUIT )
				*Leave = true;
			
			else if (EventList.type == SDL_KEYDOWN){
				if(sw_INGame_Action(Vars, &EventList) ==SDLK_ESCAPE)
					*GameState = MenuMD; //soon PauseMD;
					
			}
		}

		if(clock() - *TempoPrintEcra > 500){
			Simulacao(Vars->RoboData->Imperio, Vars->RoboData->M);
			*TempoPrintEcra=clock();
		}
		DrawMatrixTable(Vars);
		DrawBotStats(Vars);
}

void MainLoopRender(Rend_Struct *Vars){
	
	bool Leave = false;
	int TempoPrintEcra = 0;
	int GameState = MenuMD; //MainMenu
	
	Vars->VarMenuOpt.EnterPressed = false;
	Vars->VarMenuOpt.OptionSelected = 0;
	strcpy(Vars->VarMenuOpt.OPTArray[PlayOPT].String, "Play");
	strcpy(Vars->VarMenuOpt.OPTArray[OptionOPT].String, "Options");
	strcpy(Vars->VarMenuOpt.OPTArray[ExitOPT].String, "Bye Bye");

	//Event handler
    SDL_Event EventList;


	while(!Leave){
		SDL_SetRenderDrawColor( Vars->gRenderer, STARTINGCOLOR,255);
		SDL_RenderClear( Vars->gRenderer );
		switch (GameState)
		{
		case MenuMD:{
			MenuRender(Vars, &Leave, &GameState);
			break;
					}

		case PlayMD:{
			PlayRender(Vars, &Leave, &GameState,&TempoPrintEcra);
			break;
					}
		}


		//Update the surface
//		SDL_RenderCopy( Vars->gRenderer, Vars->imgArray[currScreen].Key_Texture, NULL, NULL );

		
		SDL_RenderPresent( Vars->gRenderer );
		//printf(".");
		//Wait two seconds
		SDL_Delay(1);
	}

}

bool initWindowRender(Rend_Struct *Vars, int W ,int H){
	bool success = true;
	if( SDL_Init(SDL_INIT_VIDEO) < 0){ //se der erro a inicializar
		printf("SDL_INIT_VIDEO ERROR : %s\n", SDL_GetError());
		success = false;
	}
	else{
		
		//Criar uma janela e colocar no ponteiro Vars->window
		Vars->window = SDL_CreateWindow(WINDOWTITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		
		if(!Vars->window){//Erro
			printf("SDL_CreateWindow ERROR : %s\n", SDL_GetError());
			success = false;
		}
		else{   //  
			SetWindowIcon("media/icon.bmp", Vars->window);
			SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
			//| SDL_RENDERER_PRESENTVSYNC
			Vars->gRenderer = SDL_CreateRenderer( Vars->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( !Vars->gRenderer )
			{
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( Vars->gRenderer, STARTINGCOLOR, 255);

			}
		}
	}
	return success;
}

bool loadMediaRENDER(Rend_Struct *Vars){
	bool ret = true;
	
	Vars->gFont = TTF_OpenFont("media/Roboto-Regular.ttf",35);
	if(	Vars->gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		ret = false;
	}

	//Load default surface
	for (int i = 0; i < IMG_TOTAL; i++)
	{
		Vars->imgArray[ i ].Img_Texture = loadTexture( Vars->imgArray[ i ].Path , Vars->gRenderer, true );
		SDL_QueryTexture(Vars->imgArray[ i ].Img_Texture, NULL, NULL, &Vars->imgArray[ i ].IMG_W, &Vars->imgArray[ i ].IMG_H); //Get width and height of texture

		if( !Vars->imgArray[ i ].Img_Texture ){
			printf( "Failed to load [%s] image!\n", Vars->imgArray[ i ].Path);
			ret = false;
		}
	}
    return ret;
}

void PathToArray(Rend_Struct *Vars){

	strcpy( Vars->imgArray[ROBO_OFF].Path, "media/robo_off.bmp");
	strcpy( Vars->imgArray[ROBO_ON].Path ,"media/robo_on.bmp");
	strcpy( Vars->imgArray[OBST].Path ,"media/obst.bmp");
	strcpy( Vars->imgArray[EMPTY].Path ,"media/empty.bmp");
	strcpy( Vars->imgArray[DIRTY].Path ,"media/Newdirty.bmp");
}

void initNull(Rend_Struct *Vars){
	Vars->gFont = nullptr;
	Vars->gRenderer = nullptr;
	Vars->mainTexture = nullptr;
	
	Vars->TextH = 0;
	Vars->TextTexture = nullptr;
	Vars->TextW = 0;
	Vars->window = nullptr;
	Vars->windowSurface = nullptr;

	for (int i = 0; i < IMG_TOTAL; i++){
		Vars->imgArray[i].Img_Texture = nullptr;
		Vars->imgArray[i].Img_Surf = nullptr;
		Vars->imgArray[ i ].IMG_H = 0;
		Vars->imgArray[ i ].IMG_W = 0;
		Vars->imgArray[i].Path[0] = '/0';
	}
}

bool initRender(Rend_Struct *Vars, int W ,int H){
	bool success = true;
	
	initNull(Vars);

	if( !initWindowRender(Vars, W, H) ){ //se der erro a inicializar
		success = false;
	}
	else{
		if( TTF_Init() == -1 ){
			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
			success = false;
		}
		else{
			PathToArray(Vars);
			//load the images
			if( !loadMediaRENDER(Vars) )
				success = false;
		}
	}
	return success;
}

void Destroy(Rend_Struct *Vars){

	for (int i = 0; i < IMG_TOTAL; i++){
		
		if(Vars->imgArray[i].Img_Texture)
			SDL_DestroyTexture( Vars->imgArray[i].Img_Texture);
		
		if(Vars->imgArray[i].Img_Surf)
			SDL_FreeSurface(Vars->imgArray[i].Img_Surf);

	}
	
	//Destroy window
	SDL_DestroyWindow( Vars->window );
	//Destroy renderer
	SDL_DestroyRenderer( Vars->gRenderer );
	SDL_DestroyTexture( Vars->mainTexture );

	TTF_CloseFont( Vars->gFont );
	TTF_Quit();
	//Quit SDL subsystems
	SDL_Quit();

	free(Vars->RoboData->Imperio->R);
	free(Vars->RoboData->Imperio);
	free(Vars->RoboData->M->Dados);
	free(Vars->RoboData->M);
	free(Vars->RoboData);
	free(Vars);
}