#include "Diamond.h"
#include "square.h"


//insert diamond into new/old screen and/or print
//this function fills the screen matrices according to which, and 
//prints only if which == newScreen
void Diamond::insertIntoScreen(Screen & scr, unsigned int which)const
{
	
	int x = pos.getX();
	int y = pos.getY();

	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
	{
		for(int j = 0; j < 2*i + 1; j++)
		{
			Point p1(x - i + j, y + len - i);
			Point p2(x - i + j, y - len + i);
			switch(which)
			{
			case oldScreen: if(p1.isPointInScreenBounds())
							{
								scr.setOldTile(y + len - i, x - i + j, ch);
								gotoxy(x - i + j, y + len - i); 
								cout<<ch;
							}

							if(p2.isPointInScreenBounds()) 
							{
								scr.setOldTile(y - len + i, x - i + j, ch); 
								gotoxy(x - i + j, y - len + i); 
								cout<<ch;
							}
							break;
			case newScreen: if(p1.isPointInScreenBounds()) 
							{
								scr.setNewTile(y + len - i, x - i + j, ch);
							} 

							if(p2.isPointInScreenBounds()) 
							{
								scr.setNewTile(y - len + i, x - i + j, ch);
							}
							break;
			default:
				break;
			}
			
		}
	}
}

//did the diamond hit a wall
unsigned int Diamond::isWall()const
{
	
	if(pos.getX() + len >= max_x && offset.getX() >= 0 ) 
		return rightEdge;

	else if( pos.getX() - len <= min_x && offset.getX() <= 0)
		return leftEdge;

	else if(pos.getY() + len >= max_y && offset.getY() >= 0)
		return downEdge;

	else if(pos.getY() - len <= min_y && offset.getY() <= 0)
		return upEdge;
	
	return false;

}

//is a given point p inside the diamond?
bool Diamond::isPointInside(Point p)const
{
	Point p1;
	Point p2;

    int x = pos.getX();
	int y = pos.getY();
	
	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
		for(int j = 0; j < 2*i + 1; j++)
		{

			p1.setPoint(x - i + j, y + len - i);
			p2.setPoint(x - i + j, y - len + i);

			if(p == p1 || p == p2)
				return true;
		}
		
		return false;

	
}

//are the diamond and another square disjoint?
bool Diamond::areDisjoint(const Square * sqr)const
{
	Point p1;
	Point p2;

    int x = pos.getX();
	int y = pos.getY();

	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
		for(int j = 0; j < 2*i + 1; j++)
		{

			p1.setPoint(x - i + j, y + len - i);
			p2.setPoint(x - i + j, y - len + i);

			if(((isPointInside(p1) && sqr->isPointInside(p1)) || (isPointInside(p2) && sqr->isPointInside(p2))))
				return false;
		}
		
		return true;

}

//are the diamond and another diamond  disjoint?
bool Diamond::areDisjoint(const Diamond * dmnd)const
{

	Point p1;
	Point p2;
	int x = pos.getX();
	int y = pos.getY();
	
	
	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
		for(int j = 0; j < 2*i + 1; j++)
		{

			p1.setPoint(x - i + j, y + len - i);
			p2.setPoint(x - i + j, y - len + i);

			if(((isPointInside(p1) && dmnd->isPointInside(p1)) || (isPointInside(p2) &&  dmnd->isPointInside(p2))))
				return false;
		}
		
		return true;
}

//general case
bool Diamond::areDisjoint(const Shape * shp)const
{

	return  shp->areDisjoint(this);

}


//diamond size (actually the number of chars)
int Diamond::getSize()
{

	return 2*len*(1 + len) + 1;				//num of chars

}



//is the diamond contained within a square
 bool Diamond::isContained(const Square * sqr)const
 {
	Point p1;
	Point p2;
	int x = pos.getX();
	int y = pos.getY();
	
	
	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
		for(int j = 0; j < 2*i + 1; j++)
		{

			p1.setPoint(x - i + j, y + len - i);
			p2.setPoint(x - i + j, y - len + i);
			
			if(!((sqr->isPointInside(p1) || !(sqr->isPointInside(p2)))))
				return false;
		}
		
		return true;

 }

 //is the diamond contained within another diamond
bool Diamond::isContained(const Diamond * dmnd)const 
{
	Point p1;
	Point p2;
	int x = pos.getX();
	int y = pos.getY();
	
	
	for(int i = 0; i < (len*2+1)/2 + 1 ; i++)
		for(int j = 0; j < 2*i + 1; j++)
		{

			p1.setPoint(x - i + j, y + len - i);
			p2.setPoint(x - i + j, y - len + i);
			
			if(!((dmnd->isPointInside(p1) || !(dmnd->isPointInside(p2)))))
				return false;
		}
		
		return true;

}

//in the general case
bool Diamond::isContained(const Shape * shp)const 
{
	return shp->isContained(this);


}

//validate that the point is not out of screen console bounds
//bool Diamond::isPointInScreenBounds(const Point & p)const
//{
//
//	if(p.getX() < max_x + 1 && p.getX() >= min_x  
//				&&  p.getY() < max_y + 1 && p.getY() >= min_y) 
//				return true;
//	else 
//		return false;
//
//}