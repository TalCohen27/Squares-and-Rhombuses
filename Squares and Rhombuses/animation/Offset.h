#ifndef _OFFSET_H
#define _OFFSET_H

#include <math.h>
#include <iostream>
using namespace std;

class Offset{

	float initX;
	float initY;
	
	float x;
	float y;

public:
	
	Offset():initX(0), initY(0), x(0), y(0){}


	bool isOffsetTooSmall()const;
	void AccumOffset();

	//operator ==
	bool operator==(const Offset & p)const{return x == p.x && y == p.y;}
	
	//resetters
	void resetOffset(){resetY(); resetX();}
	void resetY(){y = initY;}
	void resetX(){x = initX;}


	//getters
	float getX()const{return x;}
	float getY()const{return y;}
	float getInitX()const{return initX;}
	float getInitY()const{return initY;}

	//setters
	void setInitX(float _x){initX = _x;}
	void setInitY(float _y){initY = _y;}
	void setOffset(float _x, float _y){initX = _x, initY = _y, x = _x, y = _y;}
	void setX(float _x){x = _x;}
	void setY(float _y){y = _y;}

	friend ostream & operator<<(ostream & , const Offset &);
	friend istream & operator>>(istream & ,  Offset &);

};

#endif