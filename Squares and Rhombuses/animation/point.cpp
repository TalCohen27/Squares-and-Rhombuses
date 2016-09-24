#include "point.h"


void Point::blink(char ch)const
{
	
	gotoxy(x, y);
	cout<<ch;
	Sleep(200);
	gotoxy(x, y);
	cout<<' ';
	Sleep(200);

}

ostream & operator<<(ostream & out, const Point & p)
{

	out<<p.x<<' ';
	out<<p.y<<' ';

	return out;
}

istream & operator>>(istream & in, Point & p)
{
	in>>p.x;
	in>>p.y;

	return in;

}

//validate that the point is not out of screen console bounds
bool Point::isPointInScreenBounds()const
{
	if(x < max_x + 1 && x >= min_x  
		&&  y < max_y + 1 && y >= min_y) 
		return true;
	else 
		return false;
}


