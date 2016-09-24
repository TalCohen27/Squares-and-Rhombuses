
#include "square.h"
#include "Diamond.h"


//check if a point is on a square's circumference
bool Square::isPointOnCircum(Point p)const
{
	if(isPointInside(p) == false)
		return false;
	else
	{
		if((p.getX() == pos.getX()) || (p.getY() == pos.getY()) ||( p.getX() == pos.getX() + len-1)  
			|| (p.getY() == pos.getY() + len-1))
			return true;
		else
			return false;
	}
	
}


//check if a given point is inside a square (including circmference)
bool Square::isPointInside(Point p)const
{
	
	if(p.getX() <= pos.getX() + len-1 && p.getX() >= pos.getX() && p.getY() <= pos.getY() + len-1 
		&& p.getY() >=  pos.getY())
		return true;
	else
		return false;
}


//check if two squares are disjoint
bool Square::areDisjoint(const Square * sqr)const
{
	Point p;
	for(int i = 0; i < sqr->len; i++)
		{
			
			for(int j = 0; j < sqr->len; j++)
			{
				p.setPoint(sqr->pos.getX() + j,  sqr->pos.getY() + i);
				if(isPointInside(p) == true && sqr->isPointInside(p) == true)
					return false;
				
			}
	}
	
	return true;


}

//check if square hit the screen's edge
unsigned int Square::isWall()const
{
	if(pos.getX() + len > max_x && offset.getX() > 0 ) 
		return rightEdge;

	else if(pos.getX() -1 < min_x && offset.getX() < 0)
		return leftEdge;

	else if(pos.getY() + len > max_y && offset.getY() > 0)
		return downEdge;

	else if(pos.getY() -1 < min_y && offset.getY() < 0)
		return upEdge;
	
	return false;
	
}

//insert square into new/old screen and/or print
//this function fills the screen matrices according to which, and 
//prints only if which == newScreen
void Square::insertIntoScreen(Screen & scr, unsigned int which)const
{
	
	int x = pos.getX();
	int y =  pos.getY();

	for(int i = 0; i < len; i++)
	{
		

		for(int j = 0; j < len; j++)
		{
			Point p(x + j, y + i);

			if(p.isPointInScreenBounds()) //limiting the visible console
			{
				if(isPointOnCircum(p) == true)		//we only enter the circumference

					switch(which)
				{
					case oldScreen: scr.setOldTile(y + i, x + j, ch); gotoxy(x + j, y + i); cout<<ch;
						break;
					case newScreen: scr.setNewTile(y + i, x + j, ch);
						break;
					default:
						break;
				}
				else       
					switch(which)
				{
					case oldScreen: scr.setOldTile(y + i, x + j, ' '); gotoxy(x + j, y + i); cout<<' ';
						break;
					case newScreen: scr.setNewTile(y + i, x + j, ' ');
						break;
					default:
						break;
				}												//otherwise it's whitespace
															
			}
				
		}
	}
}

//are a square and diamond disjoint
bool Square::areDisjoint(const Diamond * dmnd)const
{
	return dmnd->areDisjoint(this);
	
}

//general case
bool Square::areDisjoint(const Shape * shp)const
{
	return shp->areDisjoint(this);

}

//number of chars
int Square::getSize()
{

	return 4*len -4 ; //num of chars

}

//is a square contained within another square
bool Square::isContained(const Square * sqr)const
{

	Point p;
	for(int i = 0; i < len; i++)
	{
		
		for(int j = 0; j < len; j++)
		{
			p.setPoint(pos.getX() + j,  pos.getY() + i);
			if(!(sqr->isPointInside(p)))
				return false;
		
		}
	
	}
	
	return true;
}

//is a square contained within another diamond
bool Square::isContained(const Diamond * dmnd)const
{
	Point p;
	for(int i = 0; i < len; i++)
	{
		
		for(int j = 0; j < len; j++)
		{
			p.setPoint(pos.getX() + j,  pos.getY() + i);
			if(!(dmnd->isPointInside(p)))
				return false;
		
		}
	
	}
	
	return true;
}

//general case
bool Square::isContained(const Shape * shp)const
{
	return shp->isContained(this);

}