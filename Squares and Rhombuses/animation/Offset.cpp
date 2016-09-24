#include "Offset.h"

//we need the offset to be greater than 1 (in abs value)
void Offset::AccumOffset()
{
	if(abs(x) < 1)
		x += initX;
	if(abs(y) < 1)
		y += initY;

}

//is offset bigger than -1 and smaller than 1
bool Offset::isOffsetTooSmall()const
{
	
	if(((abs(x) < 1 || x == 0)) && (abs(y) < 1 || y == 0))
		return true;
	else 
		return false;

}

ostream & operator<<(ostream & out, const  Offset & offset)
{
	out<<offset.initX<<' ';
	out<<offset.initY<<' ';
	out<<offset.x<<' ';
	out<<offset.y<<' ';
	

	return out;

}

istream & operator>>(istream & in,  Offset & offset)
{
	in>>offset.initX;
	in>>offset.initY;
	in>>offset.x;
	in>>offset.y;

	return in;

}

