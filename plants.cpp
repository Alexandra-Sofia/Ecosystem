// File: plant.cpp

#include <iostream>
#include <string>
#include <ctime>                //for function time
#include <cstdlib>              //for functions rand, srand
#include "plants.h"

using namespace std;

tiles::tiles() { T=" "; P=NULL;}
tiles::~tiles() { delete P; }
void tiles::chtiles(string T_) { T=T_; }
string tiles::retT() { return T; }
Plant* tiles::getP() { return P; }
void tiles::deleteP() { if (P!=NULL) delete P; P=NULL; }
//void tiles::printTile2() { cout << " " << T; }
void tiles::printTile2() {
	
	if (T=="\"")
		cout <<"\033[0;" << 32 << "m \"\033[0m";
		//cout <<"\033[1;" << 32 << "m\"\033[0m";
	else if (T=="#")
		cout <<"\033[0;" << 34 << "m #\033[0m";
	else if (T=="^")
		//cout <<"\033[0;" << 33 << "m^\033[0m";
		//cout <<"\033[1;" << 31 << "m^\033[0m";
		cout <<"\033[0;" << 31 << "m ^\033[0m";
	else 
		cout << " " << T;		
}

void tiles::printP() { if (P!=NULL) P->printAll(); }
void tiles::printTile()
{
	if (P==NULL)
		printTile2();
	else
	{
		cout << " " << P->getToken();
	}
}
void tiles::put_plant(string token, int x, int y)
{
	if (token.compare("G")==0)
	{
		Grass *g;		
		g = new Grass(x,y);
		P = g;
	}
	else if (token.compare("A")==0)
	{
		Algae *a;
		a = new Algae(x,y);
		P = a;
	}
	else if (token.compare("O")==0)
	{
		Oak *o;
		o = new Oak(x,y);
		P = o;
	}
	else if (token.compare("P")==0)
	{
		Pine *p;
		p = new Pine(x,y);
		P = p;
	}
	else if (token.compare("M")==0)
	{
		Maple *m;
		m = new Maple(x,y);
		P = m;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

Plant::Plant(string name_,string token_,int x_,int y_,int breeding,int illness,int life_,int lifeFactor_) 
	: name(name_), token(token_), x(x_), y(y_), breedingProb(breeding), 
	illnessProb(illness), life(life_), lifeFactor(lifeFactor_)
{}

Plant::~Plant(){ }

string Plant::getName() { return name; }
string Plant::getToken() { return token; }
int Plant::getX() { return x; }
int Plant::getY() { return y; }
int Plant::getBreedingProb() { return breedingProb; }
int Plant::getIllnessProb() { return illnessProb; }
int Plant::getLife() {	return life;  }
int Plant::getLifeFactor() { return lifeFactor; }
void Plant::changeLife(int life_) 
{ 
	if (life_ > 0)
		life = life_; 
	else
		life = 0;		// we cannot allow negative life
}

void Plant::printAll()
{
	cout << "Name: " << name << endl;
	cout << "Token: " << token << endl;
	cout << "Life: " << life << endl;
	cout << "Coordinates: " << x << ", " << y << endl;
	cout << "Breeding Probability: " << breedingProb << endl;
	cout << "Illness Probability: " << illnessProb << endl;
	cout << "Life Factor: " << lifeFactor << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Seedless::Seedless(string name_,string token_,int x_,int y_,int breeding,int illness,int life_,int lifeFactor_)	
	: Plant(name_, token_, x_, y_, breeding, illness, life_, lifeFactor_)
{}

Seedless::~Seedless(){}

int Seedless::LoseLife (int amount)
{
	int l;						// shows life
	l = getLife();
	changeLife(l-amount);
	if (getLife())
		return amount;
	else
		return l;
}

void Seedless::Grow()
{
	int l;						// shows life
	int check;

	l = getLife();
	if (l==0) return;

	check = ((rand() % 100) + 1);

	if ( check > getIllnessProb() )
		changeLife(l+getLifeFactor());		// In case of healthyness
	else
		changeLife(l-getLifeFactor());		// In case of illness

	// cout << "\nCheck: " << check << endl << endl;
}

void Seedless::printAll() { Plant::printAll(); }

///////////////////////////////////////////////////////////////////////////////////////////////

Seeded::Seeded(string name_,string token_,int x_,int y_,int breeding,int illness,int life_,int lifeFactor_,int size_,int foliage_, int seeds_)
	: Plant(name_, token_, x_, y_, breeding, illness, life_, lifeFactor_), size(size_), foliage(foliage_), seeds(seeds_)
{}

Seeded::~Seeded() {}

int Seeded::LoseLife (int amount)
{
	int s = getSeeds();
	int f = getFoliage();
	int a = amount;

	if (s)
	{
		if (s>amount)
		{
			changeSeeds(s-amount);
			return a;
		}
		else
		{
			amount -= s;
			changeSeeds(0);
		}
	}

	if(f)
	{
		if (f>amount)
		{
			changeFoliage(f-amount);
			changeLife(f-amount);
			return a;
		}
		else
		{
			changeFoliage(0);
			changeLife(0);
		}
	}
	return s+f;
}

void Seeded::Grow()
{
	int check;
	int lifefactor_ = getLifeFactor();
	int l = getLife();
	int s = getSeeds();
	int f = getFoliage();
	int size_ = getSize();
	float fl;

	if (l==0) return;

	check = ((rand() % 100) + 1);

	//cout << "\nCheck: " << check << endl << endl;

	if ( check > getIllnessProb() )		// In case of healthyness
	{
		changeLife(l+lifefactor_);
		changeFoliage(f+lifefactor_);
		changeSeeds(s+(2*lifefactor_));
		fl = (float) f / (float) lifefactor_;
		
		if ( (fl>=1) && (check_if_Integer(fl) == true) )
		{
			size_++;
			changeSize(size_);
		}
	}
	else
	{
		changeLife(l-lifefactor_);		// In case of illness
		changeFoliage(f-lifefactor_);
		changeSeeds(s-(2*lifefactor_));

		fl = (float) f / (float) lifefactor_;
		
		if ( (fl>=1) && (check_if_Integer(fl) == true) )
		{
			size_--;
			changeSize(size_);
		}
	}

	// cout << "\nCheck: " << check << endl << endl;
}

int Seeded::getSize() { return size; }
int Seeded::getSeeds() { return seeds; }
int Seeded::getFoliage() { return foliage; }

void Seeded::changeSize(int size_) 
{
	if (size_ > 0)
		size = size_;
	else
		size = 0;
}

void Seeded::changeSeeds(int seeds_)
{
	if (seeds > 0)
		seeds = seeds_;
	else
		seeds = 0;
}

void Seeded::changeFoliage(int foliage_)
{
	if (foliage > 0)
		foliage = foliage_;
	else
		foliage = 0;
}

void Seeded::printAll()
{
	Plant::printAll();
	cout << "Size: " << size << endl;
	cout << "Foliage: " << foliage << endl;
	cout << "Seeds: " << seeds << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Grass::Grass(int x_,int y_) : Seedless("Grass","G", x_, y_, 15, 15, 5, 4) {}
Grass::Grass(Grass& g) : Seedless("Grass","G", g.getX(), g.getY(), 15, 15, 5, 4) {}
Grass::~Grass() {}

bool Grass::Breed(tiles& tile, int x, int y)
{
	int check = ((rand() % 100) + 1);

	//cout << "Check: " << check << endl;
	//cout << "Been in the correct place :D\n\n";

	if ( CheckSurvival(tile) == true )
	{
		if (check > getBreedingProb()) {
			tile.put_plant("G", x, y);
			return true;
		}
		else
			return false;	
	}
}

bool Grass::CheckSurvival(tiles& tile)
{
	if (tile.retT() == survivePlace())
		return true; 
	else return false;
}

string Grass::survivePlace() { return "\""; }

void Grass::printAll()
{
	Seedless::printAll();
	cout << "Places where survives: " << survivePlace() << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////

Algae::Algae(int x_, int y_) : Seedless("Algae", "A", x_, y_, 25, 25, 5, 2) {}
Algae::~Algae() {}

bool Algae::Breed(tiles& tile, int x, int y)
{
	int check = ((rand() % 100) + 1);

	//cout << "Check: " << check << endl;

	if ( CheckSurvival(tile) == true )
	{
		if (check > getBreedingProb()){
			tile.put_plant("A", x, y);
			return true;
		}
		else
			return false;	
	}
}

bool Algae::CheckSurvival(tiles& tile)
{
	if (tile.retT() == survivePlace())
		return true; 
	else return false;
}

string Algae::survivePlace() { return "#"; }

void Algae::printAll()
{
	Seedless::printAll();
	cout << "Places where survives: " << survivePlace() << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

Oak::Oak(int x_, int y_) : Seeded("Oak", "O", x_, y_, 20, 20, 30, 15, 5, 30, 15) {}
Oak::~Oak() {}

bool Oak::Breed(tiles& tile, int x, int y)
{
	int check = ((rand() % 100) + 1);

	//cout << "Check: " << check << endl;

	if ( CheckSurvival(tile) == true )
	{
		if (check > getBreedingProb()){
			tile.put_plant("O", x, y);
			return true;
		}
		else
			return false;	
	}
}

bool Oak::CheckSurvival(tiles& tile)
{
	if (tile.retT() == survivePlace())
		return true; 
	else return false;
}

string Oak::survivePlace() { return "\""; }

void Oak::printAll()
{
	Seeded::printAll();
	cout << "Places where survives: " << survivePlace() << endl << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////

Pine::Pine(int x_, int y_) : Seeded("Pine", "P", x_, y_, 15, 15, 40, 20, 5, 40, 20) {}
Pine::~Pine() {}

bool Pine::Breed(tiles& tile, int x, int y)
{
	int check = ((rand() % 100) + 1);

	//cout << "Check: " << check << endl;

	if ( CheckSurvival(tile) == true )
	{
		if (check > getBreedingProb()){
			tile.put_plant("P", x, y);
			return true;
		}
		else
			return false;	
	}
}

bool Pine::CheckSurvival(tiles& tile)
{
	if (tile.retT() == survivePlace())
		return true; 
	else return false;
}

string Pine::survivePlace() { return "^"; }

void Pine::printAll()
{
	Seeded::printAll();
	cout << "Places where survives: " << survivePlace() << endl << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////

Maple::Maple(int x_, int y_) : Seeded("Maple", "M", x_, y_, 5, 5, 20, 10, 2, 20, 10) {}
Maple::~Maple() {}

bool Maple::Breed(tiles& tile, int x, int y)
{
	int check = ((rand() % 100) + 1);

	//cout << "Check: " << check << endl;

	if ( CheckSurvival(tile) == true )
	{
		if (check > getBreedingProb()){
			tile.put_plant("M", x, y);
			return true;
		}
		else
			return false;	
	}
}

bool Maple::CheckSurvival(tiles& tile)
{
	if (tile.retT() == "\"" || tile.retT() == "^")
		return true; 
	else return false;
}

void Maple::printAll()
{
	Seeded::printAll();
	cout << "Places where survives: \" and ^" << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool check_if_Integer(float f)
{
	int i = (int) f;
	cout << i << endl;
	cout << f << endl;

	if ( ((float) i - f) == 0)
		return true;
	else return false;
}
