


#include "Screen.h"


//the c'tor fills the two grids with spaces
Screen::Screen()
{
	
	for(int i = 0; i <= max_y; i++)
		for(int j = 0; j <= max_x; j++)
		{
			newScreen[i][j] = ' ';
			oldScreen[i][j] = ' ';

		}
}


//we only print out the differences
//and make sure to update the oldScreen
void Screen::diff()
{
	
	for(int i = 0; i <= max_y; i++)
	{
		for(int j = 0; j <= max_x; j++)
		{
			if(newScreen[i][j] != oldScreen[i][j])
			{
				gotoxy(j, i);
				cout<<newScreen[i][j];
				oldScreen[i][j] = newScreen[i][j];
			}
			
		}
	}

}

//setters
void Screen::setNewTile(int i, int j, char ch)
{

	newScreen[i][j] = ch;


}

void Screen::setOldTile(int i, int j, char ch)
{

	oldScreen[i][j] = ch;


}

//init the new copy
void Screen::initNewScreen()
{
	for(int i = 0; i <= max_y; i++)
		for(int j = 0; j <= max_x; j++)
			newScreen[i][j] = ' ';

}

