
#include <conio.h>
#include "mainmenu.h"


void MainMenu::start()
{
	//render main menu
	showMenu();

	//enter animator loop - ends with ESC
	handleChoice(); 
}

//renders and animates all shapes currently in the container
void MainMenu::drawAndAnimateAll()
{
	clrscr();

	for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
		(*curr)->draw(scr);
	
	
	while(!_kbhit() || _getch()!=27){
	
		for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
			(*curr)->animate(scr);
		
		scr.diff();
		scr.initNewScreen();
		Sleep(cycle);
	}
}
	
	
//render the relevant menu options
void MainMenu::showMenu()
{
	cout<<"1. Add Shape"<<endl;
	cout<<"2. Draw Shapes"<<endl;
	cout<<"3. Select a Shape"<<endl;
	cout<<"4. Save to .txt file"<<endl;
	cout<<"5. Load from .txt file"<<endl;
	cout<<"6. Save to .bin file"<<endl;
	cout<<"7. Load from .bin file"<<endl;
	cout<<"8. Quit"<<endl;

}

//add a shape to the container
void MainMenu::addShape()
{
	
	clrscr();

	unsigned int choice;
	
	cout<<"Which shape would you like to add?"<<endl;
	cout<<"1. Square"<<endl;
	cout<<"2. Diamond"<<endl;
	
	do 
	{
		cin>>choice;

		if(choice < Sqr || choice > Dmnd)
			cout<<"must choose between option 1 and 2!"<<endl;

	}while(choice < Sqr || choice > Dmnd);
	
	
	int x, y, Length;
	char figure;
	
	getInput(x, y, Length, figure, choice);
	
	
	switch(choice)
	{
	case Sqr: shapes.push_back(new Square(Point(x, y, figure), Length, figure));
		break;
	case Dmnd: shapes.push_back(new Diamond(Point(x, y, figure), Length, figure));
		break;
	}
	
	drawShapes();

}

void MainMenu::drawShapes()
{
	clrscr();

	for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
			(*curr)->draw(scr);

	
	
	handleSuspension();
	
}


void MainMenu::drawShapes(const Point & p)
{
	

	for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
		(*curr)->draw(scr);
			

	handleSuspension(p);
	
}

//find and select a shape
void MainMenu::selectShape()
{
	clrscr();
	char saver;
	int x, y;
	getInput(x, y);

	try
	{
		firstShape = find(Point(x, y));

	}
	catch(list<Shape *>::iterator shpItr)
	{
		if(shapes.end() == shpItr)
		{
			cout<<"No such shape has been found!";
			drawShapes(Point(x, y));
			return;
		}
	}
	catch(string msg)
	{
		cout<<msg;
		drawShapes(Point(x, y));
		return;
	}
	
	
	//temporarily change the square char to @ and its position to front of screen
	saver = (*firstShape)->getChar();
	
	(*firstShape)->setChar('@');
	
	swap(*firstShape, shapes.back()); 
	
	drawShapes(Point(x, y));
	
	clrscr();
	
	//render shape sub-menu
	showSubMenu();
	
	//set the shape back to original char and position
	swap(*firstShape, shapes.back());

	(*firstShape)->setChar(saver);
	
	
	//enter shape sub-menu
	handleChoice(*(firstShape)); 
			
	
}

//suspend until ESC
void MainMenu::handleSuspension()
{

	while(!_kbhit() || _getch()!=27){}
	
	clrscr();
	showMenu();
		
}
//suspend until ESC while making the given point flicker
void MainMenu::handleSuspension(const Point & point)
{
	
	while(!_kbhit() || _getch()!=27)
		point.blink();
		
		
	clrscr();
	showMenu();
		


}

//render sub-menu for shape
void MainMenu::showSubMenu()
{
	cout<<"1. Cancel choice (return)"<<endl;
	cout<<"2. Delete selected shape"<<endl;
	cout<<"3. Move selected shape to front of screen"<<endl;
	cout<<"4. Merge with another shape"<<endl;
	cout<<"5. Add animation"<<endl;
	cout<<"6. Add double animation"<<endl;

}

//get the user's choice for the main menu
unsigned int MainMenu::choose()
{
	unsigned int l_choice = m_num_of_options;

	clrscr();
	showMenu();
	cin >> l_choice;
	while ( l_choice > m_num_of_options || l_choice < 1)
	{
		
		cerr << "Wrong option ! Please choose an option between 1 and " 
			 << (m_num_of_options - 1) <<" or 8 to quit" <<  endl << endl << endl;
		
		
		cin >> l_choice;
		clrscr();
		showMenu();

	}
	return l_choice;
}

//get the user's choice for the shape sub-menu
unsigned int MainMenu::choose(Shape * sqr)
{
	unsigned int l_choice = subOptions;

	clrscr();
	showSubMenu();
	cin >> l_choice;
	while ( l_choice > subOptions || l_choice < 1)
	{
		cerr << "Wrong option ! Please choose an option between 1 and " 
			 << subOptions << endl << endl << endl;
		
		cin >> l_choice;

		clrscr();
		showSubMenu();
	}
	return l_choice;


}

//wait for the user's main menu choice (in loop until quit is chosen)
void MainMenu::handleChoice()
{
	
	unsigned int choice;
	
	
	do
	{
		choice = choose();

		switch(choice)
		{
		case add: addShape(); unsavedChanges = true;
			break;
		case draw: drawAndAnimateAll(); unsavedChanges = true;
			break;
		case selection: selectShape();
			break;
		case saveTxt: saveShapes(txtFile); unsavedChanges = false;
			break;
		case saveBin: saveShapes(binFile); unsavedChanges = false;
			break;
		case loadBin: loadShapes(binFile);
			break;
		case loadTxt: loadShapes(txtFile);
			break;
		default:
			break;	
		}
	}while(choice != quit);
}

//wait for the user's choice - this time in the shape sub-menu
void MainMenu::handleChoice(Shape * shp)
{
	unsigned int choice;
	
	do
	{
		choice = choose(shp);
		switch(choice)
		{
		case cancel: 
			break;
		case deleteSqr:  deleteShape(firstShape); unsavedChanges = true;
			break;
		case moveToTop: moveShapeToTop(); unsavedChanges = true;
			break;
		case merge: mergeTwoShapes(shp); 
			break;	
		case addAnima: addAnimation(shp);
			break;
		case addDblAnima: addDblAnimation(shp);
			break;
		default:
			break;
		}
	}
	while(choice == addAnima);
	
	drawShapes();

	
}

void MainMenu::moveShapeToTop()
{
	swap(*firstShape, shapes.back());
}

//merge two shapes
void MainMenu::mergeTwoShapes(Shape *shp)
{
	if(selectASecondShape() == true)
	{
		
		if(shp->areDisjoint(*secondShape) == true)
		{
			
			if((*secondShape)->isBigger(shp))  
				replaceAndDeleteFirstShape();
			
			else if(shp->isBigger(*secondShape) || !(shp->isBigger(*secondShape)))   // //if first is bigger or equal in size
					deleteShape(secondShape);
		}

		//if there's a containment relation (one within the other)
		else if(shp->isContained(*secondShape) && !(*secondShape)->isContained(shp)) 
			deleteShape(secondShape);
		
		else if((*secondShape)->isContained(shp)  && !(shp->isContained(*secondShape)))
			replaceAndDeleteFirstShape();

		//if not disjoint or contained - this means they are intersected
		else 
		{
			if(shp->isBigger(*secondShape) == true)
				replaceAndDeleteFirstShape();
			else
				deleteShape(secondShape);
		}

		unsavedChanges = true;
	}
}


list<Shape *>::iterator MainMenu::find(Point & p)
{
	list<Shape *>::iterator selectedShape = shapes.end();

	if(!shapes.empty())
	{
		for(list<Shape *>::iterator curr = --(shapes.end()), begin = shapes.begin(); 
			(curr != begin || curr == begin) && selectedShape == shapes.end() ; curr--)
		{
			
			if((*curr)->isPointInside(p) == true)
				selectedShape = curr;
			
			if(curr == shapes.begin())
					break;
		}
	}
	else 
		throw string("There are currently no shapes available!");
	
	if(selectedShape == shapes.end())
		throw selectedShape;
	
	return selectedShape;
}

//d'tor - we free the list and all the pointers
MainMenu::~MainMenu()
{
	//free each Shape *
	for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
		delete (*curr);

	//free list
	shapes.clear();
}

void MainMenu::replaceAndDeleteFirstShape()
{
	(*secondShape)->setPos((*firstShape)->getPos());
	swap(*firstShape, *secondShape);
	deleteShape(secondShape);
}

void MainMenu::addAnimation(Shape *shp)
{
	float offsetX, offsetY;

	getInput(offsetX, offsetY);

	shp->setOffset(offsetX, offsetY);
	shp->draw(scr);

	while(!_kbhit() || _getch()!=27){


		shp->animate(scr);

		scr.diff();
		scr.initNewScreen();
		Sleep(cycle);
	
	}
	
	unsavedChanges = true;

	clrscr();


}

void MainMenu::addDblAnimation(Shape * shp)
{
	
	unsigned int whichDeleted = noShp;
	
	clrscr();
	if(selectASecondShape() == false){}
	else
	{
		if((*firstShape)->getOffset() == Offset() && (*secondShape)->getOffset() == Offset())
		{
			clrscr();
			(*firstShape)->draw(scr);
			(*secondShape)->draw(scr);
		}
		else
		{
			
			unsavedChanges = true;

			(*firstShape)->draw(scr);
			(*secondShape)->draw(scr);

		

			while(!_kbhit() || _getch()!=27){
				
				//are colliding?
				if((whichDeleted == noShp) && ((*firstShape)->isCollision(*(secondShape)) != false))
					whichDeleted = handleCollision(firstShape, secondShape, (*firstShape)->isCollision(*(secondShape)));
				
				
				if(whichDeleted == noShp)
				{
					(*firstShape)->animate(scr);
					(*secondShape)->animate(scr);
				}
				else if(whichDeleted == secondShp)
					(*firstShape)->animate(scr);
				else
					(*secondShape)->animate(scr);

				scr.diff();
				scr.initNewScreen();

				Sleep(cycle);
			}

		}
	}


	
}



bool MainMenu::selectASecondShape()
{
	int x, y;

	getInput(x, y);

	try
	{
		secondShape = find(Point(x, y));
	}
	catch(list<Shape *>::iterator shpItr)
	{
		if(shpItr == shapes.end())
		{
			cout<<"No such shape has been found!";
			handleSuspension();
			return false;
		}
		
	}
	
	if(secondShape == firstShape)
	{
		cout<<"This is the same shape!";
		handleSuspension();
		secondShape = shapes.end();
		return false;
	}
	return true;
}

//for a new shape
void MainMenu::getInput(int & x, int & y, int & Length, char  & figure, unsigned int choice)
{
	clrscr();
	
	cout<<"Please enter the following:"<<endl;
	cout<<"Shape coordinates:"<<endl;
	cout<<"coordinate x:"<<endl;
	cin>>x;
	cout<<"and coordinate y:"<<endl;
	cin>>y;
	
	do
	{
		cout<<"Shape length:"<<endl;
		cin>>Length;

		if(Length <= 0)
			cout<<"Length must be positive!"<<endl;

	}while(Length <= 0);

	if(choice == Sqr)
	{
		do
		{
			cout<<"And finally, a figure:"<<endl;
			cin>>figure;
			if(figure == '@')
				cout<<"figure must be different from @";
		}while(figure == '@');
	}
}

//for animation
void MainMenu::getInput(float & offsetX, float & offsetY)
{
	clrscr();


	do
	{
		cout<<"Please enter an offset between -1 and 1:"<<endl;
		cout<<"for x:"<<endl;
		cin>>offsetX;
		cout<<"and for y:"<<endl;
		cin>>offsetY;
		if(abs(offsetX) > 1 || abs(offsetY) > 1)
			cout<<"Offset must be between -1 and 1!";

	}while(abs(offsetX) > 1 || abs(offsetY) > 1);  
	
	clrscr();


}

//for searching
void MainMenu::getInput(int & x, int & y)
{
	clrscr();

	cout<<"Please enter coordinates for a shape to find:"<<endl; 
	cout<<"x coordinate: "<<endl;
	cin>>x;
	cout<<"and a y coordinate: "<<endl;
	cin>>y;

	clrscr();

}

unsigned int MainMenu::handleCollision(list<Shape *>::iterator s1, list<Shape *>::iterator s2, unsigned int axis)
{


	if(typeid(**s1).name() == typeid(**s2).name() && typeid(**s1).name() == typeid(Square).name())
	{
		
		if((*s2)->isBigger(*s1) && (*s1)->isFaster(**s2, axis))
		{
		
			deleteShape(s2);
			return secondShp;
		}
		else
		{
			
			deleteShape(s1);
			return firstShp;
		}
	}
	else if(typeid(**s1).name() == typeid(**s2).name() && typeid(**s1).name() == typeid(Diamond).name())
	{

		if((*s1)->isFaster(**s2, axis) && (*s1)->getLength() >= (*s2)->getLength())
		{
			deleteShape(s2);
			return secondShp;
		}
		else
		{
			deleteShape(s1);
			return firstShp;
		}
	}
	else
	{
		if((*s1)->isFaster(**s2, axis))
		{
			deleteShape(s2);
			return secondShp;
		}

		else
		{
		
			deleteShape(s1);
			return firstShp;
		}
	}
}

void MainMenu::deleteShape(list<Shape *>::iterator shp)
{
	delete *shp;		//free the pointer
	shapes.erase(shp);	//free the list node
}

void MainMenu::swap(Shape * & a, Shape * & b)
{

	Shape * tmp = a;

	a = b;

	b = tmp;

}

void MainMenu::saveShapes(bool fileType)
{
	ofstream out;
	int numShapes = shapes.size();
	string fileName;

	cout<<"Please enter a name for the file: "<<endl;

	cin>>fileName;
	
	//preparing the file accordin to fileType (.bin or .txt)
	
	if(fileType == txtFile)					//txt file
	{
		fileName.append(".txt", ios::trunc);
		out.open(fileName);
		out<<numShapes<<' ';
	}
	else	//.bin file
	{
		fileName.append(".bin");
		out.open(fileName, ios::binary|ios::trunc);
		out.write((char *)&numShapes, sizeof(int));
	}
	
	//saving all the shapes in the container
	for(list<Shape *>::const_iterator curr = shapes.begin(), end = shapes.end(); curr != end; ++curr)
			(*curr)->save(out, fileType);

	//closing the file
	out.close();
}

void MainMenu::loadShapes(bool fileType)
{
	//if there are any unsaved changes, we ask before loading another file
	if(unsavedChanges)
	{
		cout<<"Are you sure you wish to lose any unsaved information?"<<endl;
		cout<<"1. Yes"<<endl;
		cout<<"2. No"<<endl;

		unsigned int choice;
		
		do
		{
			cin>>choice;

			if(choice == no)
				return;
			else if(choice < yes || choice > no)
				cout<<"Please choose Yes or No"<<endl;
		
		}while(choice < yes || choice > no);
	}
	
	//if no unsaved and/or the user wants to load anyway
	//we continue with the loading process:

	unsavedChanges = false;

	string fileName;
	int numShapes;
	ifstream in;

	//clearing the container
	shapes.clear();

	cout<<"Please enter the name of the saved file you wish to load:" <<endl;
	
	cin>>fileName;
	
	//preparing the file accordin to fileType (.bin or .txt)
	if(fileType == txtFile)
	{
		fileName.append(".txt", ios::_Nocreate);
		in.open(fileName);
		in>>numShapes;
	}
	else
	{
		fileName.append(".bin");
		in.open(fileName, ios::binary|ios::_Nocreate);
		in.read((char *)&numShapes, sizeof(int));
	}
	
	//filling the container with all the saved shapes
	for(int i = 0; i < numShapes; i++)
		shapes.push_back(constructByType(in, fileType));
	
	//closing the file
	in.close();
}

//get the shape's type
char * MainMenu::typeFromFile(ifstream & in, bool fileType, char * buff)
{
	
	if(fileType == txtFile)
		in>>buff;
	else
		in.read((char *)buff, TYPELEN);
	
	
	buff[TYPELEN] = '\0';
	
	return buff;

}

//build the shape according to the type (square or diamond)
Shape * MainMenu::constructByType(ifstream & in, bool fileType)
{

	char type[TYPELEN + 1];

	typeFromFile(in, fileType, type);

	if(strncmp(type, "Square", TYPELEN) == 0)
		return new Square(in, fileType);
	else
		return new Diamond(in, fileType);

}