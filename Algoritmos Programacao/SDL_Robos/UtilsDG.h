#ifndef UTILDG_H_INC
#define UTILDG_H_INC

/*
*Give a number interval and returns a random number from that interval
*Parameter: int MIN, int MAX
*Return: INT
*/
int Randomizer(int min, int max);

/*
*	Give a text to show, and returns the number the user entered. Only returns numbers, no text
*	Parameter: char* to show on screen
*	Return: INT option
*/
int MenuOpt(char *Question);

/*
*	Don't do anything for X mlseconds
*	Parameter: int wiht how many mlseconds to wait
*/
void wait(int mlseconds);

/*
* Read Text from console
*/
char* ReadText(char *Question);

/*
*KeyPressed:
*Retorna true se uma tecla for pressionada
*/
bool KeyPressed();

#endif // !UTILDG_H_INC
