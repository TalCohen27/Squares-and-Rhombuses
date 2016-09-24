#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
using namespace std;
#include "gotoxy.h"



#include <Windows.h>
#include <fstream>

//enum for screen console limits
enum {min_x=0, max_x=79 ,min_y=0, max_y=24};
enum {y_axis = 1, x_axis = 2};
enum{leftEdge = 1, upEdge, rightEdge, downEdge};
 
class Point{

	char chara;
	int x, y;
	int dirx, diry;

public:
	
	//c'tor
	Point(int _x = 0, int _y = 0, char _chara = '!') {x = _x; y = _y; chara = _chara;}

	bool operator==(const Point & p)const{return x == p.x && y == p.y;}
	friend ostream & operator<<(ostream & , const Point & );
	friend istream & operator>>(istream & , Point & );
	bool isPointInScreenBounds()const;
	
	//blinking char
	void blink(char ch = '@')const;



	//setters
	void setPoint(Point p){setPoint(p.getX(), p.getY());}
	void setPoint(int x1, int y1){x = x1; y = y1;}
	void setChara(char _chara){chara = _chara;}
	
	//getters
	int Point::getX()const{return x;}
	int Point::getY()const{return y;}
	char getChara()const{return chara;}

//void draw()
//{
//	gotoxy(x,y);
//	cout << chara << endl;
//}

//void Point::move(Point & offset)
//{

//	dirx = offset.getX();
//	diry = offset.getY();
//	//changeDirection();
//	x += dirx;
//	y += diry;
//
//	//if(x > max_x)
//	//{
//	//	x = min_x;
//	//}
//	//else if(x < min_x)
//	//{
//	//	x = max_x;
//	//}
//	//if(y > max_y)
//	//{
//	//	y = min_y;
//	//}
//	//else if(y < min_y)
//	//{
//	//	y = max_y;
//	//}
//}


//void Point::changeDirection(const Point & offset)
//{
//	// 10% of cases we will change dir
//	if(rand()%10==0)
//	{
//		int dir = rand()%4;
//		switch(dir)
//		{
//		case 0: // UP
//			dirx = 0;
//			diry = -1;
//			break;
//		case 1: // DOWN
//			dirx = 0;
//			diry = 1;
//			break;
//		case 2: // LEFT
//			dirx = -1;
//			diry = 0;
//			break;
//		case 3: // RIGHT
//			dirx = 1;
//			diry = 0;
//			break;
//		}		
//	}
//}

	//void erase()
	//{
	//	gotoxy(x,y);
	//	cout << ' ' << endl;
	//}

};

#endif