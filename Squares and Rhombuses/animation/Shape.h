/*

This is the abstract hierarchical father to Square and to Diamond.
It holds all the generic algorithms concerning movement, like updating the shape's current position.

There are also a number of pure virtual methods e.g. insertIntoScreen which prints the shape 
into the screen matrix and/or to the console screen.

*/

#ifndef __SHAPE_H__
#define __SHAPE_H__


class Square;
class Diamond;


#include "point.h"
#include "Offset.h"
#include "Screen.h"

#define TYPELEN  2
enum {binFile, txtFile};

class Shape
{

protected:

	//data members
	Point pos;
	int len;
	char ch;
	Offset offset;

public:

	//c'tor
	Shape(Point _pos, int _len, char _ch):pos(_pos), len(_len), ch(_ch){} 
	Shape(ifstream & in, bool fileType);
	

	//pure methods
	virtual void insertIntoScreen(Screen & , unsigned int)const =0;
	virtual unsigned int isWall()const = 0;
	virtual bool isPointInside(Point)const = 0;
	
	virtual bool areDisjoint(const Square * )const =0;
	virtual bool areDisjoint(const Diamond * )const =0;
	virtual bool areDisjoint(const Shape * )const =0;
	
	virtual bool isContained(const Square *)const =0;
	virtual bool isContained(const Diamond *)const =0;
	virtual bool isContained(const Shape *)const =0;

	virtual int getSize() =0;


	//virtual d'tor
	virtual ~Shape(){};

	//generic algorithms
	void draw(Screen &)const; 
	void move(Screen &);
	void animate(Screen &);
	void updatePos();
	void changeDirection();
	bool isBigger(Shape *shp);
	bool areEqual(Shape *shp);
	unsigned int findCollisionAxis( Shape *shp);
	unsigned int isCollision( Shape *shp);
	bool isFaster(const Shape & shp, unsigned int axis)const;
	void save(ofstream & out, bool fileType);
	//void load(ifstream &, bool);
	void saveType(ofstream &, bool);
	

	//setters
	void setPos(int x, int y){pos.setPoint(x, y);}
	void setPos(Point p){pos = p;}
	void setLen(int length){len = length;}
	void setChar(char _ch){ch = _ch;}
	void setOffset(float _x, float _y){offset.setOffset(_x, _y);}

	//getters
	Point getPos()const{return pos;}
	char getChar()const{return ch;}
	int getLength()const{return len;}
	Offset getOffset()const{return offset;}


};

#endif