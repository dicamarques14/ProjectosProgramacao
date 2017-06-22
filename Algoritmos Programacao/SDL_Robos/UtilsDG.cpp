#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "UtilsDG.h"
#define CHAR_LIMIT 255
/*
*	Give a number interval and returns a random number from that interval
*	Parameter: int MIN, int	MAX
*	Return: INTrandom number
*/
int Randomizer(int min, int max){
	srand(clock()+ rand());
	return min + rand()% (max - min + 1);
}

/*
*	Give a text to show, and returns the number the user entered. Only returns numbers, no text
*	Parameter: char* to show on screen
*	Return: INT option
*/
int MenuOpt(char *Question){
	char c[20];
	int opcao = 0;

	printf("%s",Question);
	do{
		scanf("%s",c);
	}while (!isdigit(c[0]));
	opcao = atoi(c);
	return opcao;
}

/*
*	Don't do anything for X mlseconds
*	Parameter: int wiht how many mlseconds to wait
*/
void wait(int mlseconds){
	clock_t endwait;
	endwait = clock() + mlseconds;
	while (clock() < endwait) {} 
}

/*
* Read Text from console
*/
char* ReadText(char *Question){
	char buffer[CHAR_LIMIT];
	int i = 0;
	printf("%s",Question);
	
	do {
		fflush(stdin);			//Limpar o buffer
		while (i < CHAR_LIMIT)
		{
			buffer[i] = getchar();	//le o char introduzido no ecra
			if (buffer[0] == '\n')break; // nao queremos strings vazias, nem que passem para a proxima linha
			if (buffer[i] == '\n'){// assim que chegar a um \n colocar um fim de string
				buffer[i] = '\0';
				break;
			}
			i++;
		}
	} while (buffer[0] == '\n' && i < CHAR_LIMIT);  // nao queremos strings vazias, nem que passem para a proxima linha
/*
	//printf("\nLIDO[%s],",buffer);
	strcat(buffer,".csv");
	//printf("CAT[%s]\n",buffer);
	strcpy(nome,"..\\");
	strcat(nome,buffer);
	//printf("nome[%s]\n",nome);
	*/
}

/*
*KeyPressed:
*Retorna true se uma tecla for pressionada
*/
bool KeyPressed()
{
	// foi necessario incluir #include <conio.h>
	return kbhit();
}

