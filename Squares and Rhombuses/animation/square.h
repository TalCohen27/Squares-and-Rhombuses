#ifndef __SQUARE_H__
#define __SQUARE_H__


#include "Shape.h"


class Square : public Shape{

	//data members


public:
	
	//c'tor
	Square(Point _upperLeft,  int _sideLength, char _ch):Shape(_upperLeft, _sideLength, _ch){}
	Square(ifstream & in, bool fileType):Shape(in, fileType){}
	
	//member methods - inherited - virtual - overrided
	virtual bool isPointInside( Point )const;
	virtual void insertIntoScreen(Screen &, unsigned int)const;
	
	virtual bool areDisjoint(const Square *)const;
	virtual bool areDisjoint(const Diamond * )const;
	virtual bool areDisjoint(const Shape *)const;
	
	virtual bool isContained(const Square *)const;
	virtual bool isContained(const Diamond *)const;
	virtual bool isContained(const Shape *)const;
	
	virtual unsigned int isWall()const;
	virtual int getSize();
	
	
	//additional
	bool isPointOnCircum( Point )const;
	

};

#endif