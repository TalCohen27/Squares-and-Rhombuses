#ifndef __DIAMOND_H__
#define __DIAMOND_H__



#include "Shape.h"


class Diamond : public Shape{

	

public:

	//c'tor
	Diamond(Point _pos, int _len, char _ch):Shape(_pos, _len, _ch){ch = '@';}
	Diamond(ifstream & in, bool fileType):Shape(in, fileType){}

	//member methods - inherited - virtual - overrided
	virtual unsigned int isWall()const;
	virtual void insertIntoScreen(Screen & , unsigned int)const;
	virtual bool isPointInside(Point)const;
	
	virtual bool areDisjoint(const Square * )const;
	virtual bool areDisjoint(const Diamond * )const;
	virtual bool areDisjoint(const Shape * )const;
	
	virtual bool isContained(const Square *)const;
	virtual bool isContained(const Diamond *)const;
	virtual bool isContained(const Shape *)const;
	
	virtual int getSize();

	
	//additional
	bool isPointInScreenBounds(const Point & )const;

};

#endif