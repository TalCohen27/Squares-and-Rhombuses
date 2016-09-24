/*
 This is the principal program class - meaning it controls the majority of the program's features, including the 
 animator loop and menu. It also contains an array of Shape pointers (container) and handles all actions that are
 described in the assignment instructions - e.g. add shape, select shape, delete shape etc...
 It also holds an object of type Screen that contains two screen records for easy comparison and animation (see more in Screen.h)

*/



#ifndef __MAINMENU_H__
#define __MAINMENU_H__


#include <list>
#include <string>
#include <typeinfo>



#include "Square.h"
#include "Diamond.h"


//enums for menu options
enum {add = 1, draw, selection, saveTxt, loadTxt, saveBin, loadBin, quit};
enum {cancel = 1, deleteSqr, moveToTop, merge, addAnima, addDblAnima};
enum {Sqr = 1, Dmnd};
enum {noShp, firstShp, secondShp};
enum {yes = 1, no};


//various enums
const int cycle = 100;
const int m_num_of_options = 8;
const int subOptions = 6;


class MainMenu
{
	//data members
	list<Shape *>::iterator firstShape;		 //iterator to first selected square
	list<Shape *>::iterator secondShape;       //iterator to second selected square

	//container - list
	list<Shape *> shapes; 

	//screen grids
	Screen scr;

	bool unsavedChanges;

	//privare methods
	void drawAndAnimateAll();
	void showMenu();
	void addShape();
	void drawShapes();
	void drawShapes(const Point & );
	void selectShape();
	void handleSuspension();
	void handleSuspension(const Point & );
	void showSubMenu();
	unsigned int choose();
	unsigned int choose(Shape *);
	void handleChoice();
	void handleChoice(Shape *);
	void moveShapeToTop();
	void mergeTwoShapes(Shape *);
	
	list<Shape *>::iterator find(Point &);

	void replaceAndDeleteFirstShape();	
	void addAnimation(Shape *);
	void addDblAnimation(Shape *);
	bool selectASecondShape();

	void getInput(int & x, int & y, int & length, char & figure, unsigned int );  //this is for a new shape
    void getInput (float & offsetX, float & offsetY);				//add animation
	void getInput(int & x, int & y);							//coords for searching  a shape in the container
	

	unsigned int handleCollision(list<Shape *>::iterator, list<Shape *>::iterator, unsigned int);
	void deleteShape(list<Shape *>::iterator);
	
	void swap(Shape * &, Shape * &);

	Shape * constructByType(ifstream & in, bool fileType);
	char * typeFromFile(ifstream &, bool, char *);

	//save/load
	void saveShapes(bool fileType);
	void loadShapes(bool fileType);

public:
	
	//empty c'tor
	MainMenu():unsavedChanges(false){}

	//d'tor
	~MainMenu();

	//member method
	void start();

};

#endif