
/*

In this class we hold two screen records: one is the screen as it is before animation (oldScreen)
and the other after animation (newScreen). We can then compare the two members and print out 
only the difference, which prevents flickering during animation

*/



#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "point.h"

enum {oldScreen, newScreen};


class Screen{

	//data members - two grid matrices
	char oldScreen[max_y + 1][max_x + 1];
	char newScreen[max_y + 1][max_x + 1];

public:
	
	//c'tor
	Screen();

	//diff function
	void diff();

	//init new screen
	void initNewScreen();
	
	//setters
	void setNewTile(int , int , char );
	void setOldTile(int , int , char );
	
	//getters
	char getOldTile(int i, int j)const{return oldScreen[i][j];}
	char getNewTile(int i, int j)const{return newScreen[i][j];}
	
};


#endif