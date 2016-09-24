	
#include "Shape.h"


//a file-based c'tor
Shape::Shape(ifstream & in, bool fileType)
{
	
	if(fileType == txtFile)
	{
		in>>pos;
		in>>len;
		in>>ch;
		in>>offset;

	}
	else
		in.read((char *)this, sizeof(Shape));

}



void Shape::move(Screen & scr)
{

	updatePos();
	insertIntoScreen(scr, newScreen);

}
	

void Shape::animate(Screen & scr)
{


	
	if(!(offset.isOffsetTooSmall()))
		move(scr);
	else
		insertIntoScreen(scr, newScreen);	
	
	offset.AccumOffset();

}
	

void Shape::updatePos()
{
	
	if(abs(offset.getX()) >= 1 && abs(offset.getY()) >= 1)
	{
		pos.setPoint(pos.getX() + int(offset.getX()), pos.getY() + int(offset.getY()));
		
		changeDirection();	
		offset.resetOffset();
		
	}
	else if(abs(offset.getX()) >= 1 &&  abs(offset.getY()) < 1)
	{
		pos.setPoint(pos.getX() + int(offset.getX()), pos.getY());

		changeDirection();
		offset.resetX();
	}
	else if(abs(offset.getX()) < 1 &&  abs(offset.getY()) >= 1)
	{
		pos.setPoint(pos.getX(), pos.getY() + int(offset.getY()));
		
		changeDirection();
		offset.resetY();
		
	}

}


void Shape::changeDirection()
{
	switch(isWall())
	{
	case upEdge: 
		offset.setInitY(offset.getInitY() * -1);
		break;
	case downEdge: 
		offset.setInitY(offset.getInitY() * -1);
		break;
	case leftEdge: 
		offset.setInitX(offset.getInitX() * -1);
		break;
	case rightEdge: 
		offset.setInitX(offset.getInitX() * -1);
		break;
	default:
			break;
	}		


}


void Shape::draw(Screen & scr)const
{

	insertIntoScreen(scr, oldScreen);


}

bool Shape::isBigger(Shape *shp)
{

	return getSize() > shp->getSize();


}

bool Shape::areEqual(Shape *shp)
{

	return getSize() == shp->getSize();

}

unsigned int Shape::findCollisionAxis( Shape *shp)
{
	
	if(offset.getInitX() == 0 && shp->offset.getInitX() == 0)
		return x_axis;
	else if(pos.getY() < shp->pos.getY()  || pos.getY() > shp->pos.getY() + shp->len)
		return x_axis;
	else
		return y_axis;


}

unsigned int Shape::isCollision(Shape *shp)
{
	//savers
	Point posShp1 = pos; 
	Point posShp2 = shp->pos;
	
	Offset offsetShp1 = offset;
	Offset offsetShp2 = shp->offset;
	
	unsigned int res = false;
	
	if(areDisjoint(shp))
	{
		updatePos();
		shp->updatePos();
		
		if(!areDisjoint(shp))
			res  =	findCollisionAxis(shp);
	}
	else if(isContained(shp) || shp->isContained(this))
	{
		updatePos();
		shp->updatePos();
		
		if( (!(isContained(shp)) || !(shp->isContained(shp))))
			res =  findCollisionAxis(shp);
	}
	else
	{
		updatePos();
		shp->updatePos();
		
		if((areDisjoint(shp) || isContained(shp) || shp->isContained(this)))
			res = findCollisionAxis(shp);

		
	}
	
	//restore
	pos = posShp1;
	shp->pos = posShp2;

	offset = offsetShp1;
	shp->offset = offsetShp2;
	
	return res;
}


bool Shape::isFaster(const Shape & shp, unsigned int axis)const
{
	if(axis == y_axis)
	{
		if(abs(offset.getInitX()) > abs(shp.offset.getInitX()))
			return true;
		else
			return false;
	}
	else
	{
		if(abs(offset.getInitY()) > abs(shp.offset.getInitY()))
			return true;
		else
			return false;
	}
	
}


void Shape::save(ofstream & out, bool fileType)
{
	saveType(out, fileType);			//first save the type

	//save shape properties

	
	if(fileType == txtFile)							//txt file
	{
		out<<pos<<' ';
		out<<len<<' ';
		out<<ch<<' ';
		out<<offset<<' ';
		out<<endl;
	}
	else											//.bin file
		out.write((const char *)this, sizeof(Shape));
}

void Shape::saveType(ofstream & out, bool fileType)
{
	char type[TYPELEN + 1];
	strncpy_s(type, typeid(*this).name() + 6, TYPELEN);
	
	if(fileType == txtFile)
		out<<type<<' ';
	else
		out.write((const char *)&type, TYPELEN);
}

