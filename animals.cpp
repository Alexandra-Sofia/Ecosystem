// File: animals.cpp

#include <iostream>
#include <string>
#include <ctime>                //for function time
#include <cstdlib>              //for functions rand, srand
#include "animals.h"

using namespace std;

// name, token, x, y, size, hungerCount, eatenFood, eatCount, speed, isAlive, isHungry, inHeat, hibernates, inHibernation
Animal::Animal(string name_, string token_, int x_, int y_, int size_, int hungerCount_, int eatenFood_, int eatCount_, int speed_,
	           bool isAlive_, bool isHungry_, bool inHeat_, bool hibernates_, bool inHibernation_)

	: name(name_), token(token_), x(x_), y(y_), size(size_), hungerCount(hungerCount_), eatenFood(eatenFood_), eatCount(eatCount_), speed(speed_), 
	  isAlive(isAlive_), isHungry(isHungry_), inHeat(inHeat_), hibernates(hibernates_), inHibernation(inHibernation_)
{}
Animal::~Animal() {}

void Animal::printAll()
{
	cout << "Name: " << name << endl;
	cout << "Token: " << token << endl;
	cout << "Coordinates: " << x << ", " << y << endl;
	cout << "Size: " << size << endl;
	cout << "Hunger Count: " << hungerCount << endl;
	cout << "Eaten Food: " << eatenFood << endl;
	cout << "Eat Count: " << eatCount << endl;
	cout << "Speed: " << speed << endl;
	cout << "Is Alive: ";
	if (isAlive==true)
		cout << "Yes\n";
	else cout << "No\n";
	cout << "Is Hungry: ";
	if (isHungry==true)
		cout << "Yes\n";
	else cout << "No\n";
	cout << "In Heat: ";
	if (inHeat==true)
		cout << "Yes\n";
	else cout << "No\n";
	cout << "Hibernates: ";
	if (hibernates==true)
		cout << "Yes\n";
	else cout << "No\n";
	cout << "In Hibernation: ";
	if (inHibernation==true)
		cout << "Yes\n";
	else cout << "No\n";
}

string Animal::getName() { return name; }
string Animal::getToken() { return token; }
int Animal::getX() { return x; }
int Animal::getY() { return y; }
int Animal::getSize() { return size; }
int Animal::getHungerCount() { return hungerCount; }
int Animal::getEatenFood() { return eatenFood; }
int Animal::getEatCount() { return eatCount; }
int Animal::getSpeed() { return speed; }
bool Animal::getIsAlive() { return isAlive; }
bool Animal::getIsHungry() { return isHungry; }
bool Animal::getInHeat() { return inHeat; }
bool Animal::getHibernates() { return hibernates; }
bool Animal::getInHibernation() { return inHibernation; }

void Animal::changeX(int X) { x=X; }
void Animal::changeY(int Y) { y=Y; }
void Animal::changeSize(int Size) { size+=Size; }
void Animal::changeHungerCount(int HungerCount) { hungerCount=HungerCount; }
void Animal::changeEatenFood(int EatenFood) { eatenFood=EatenFood; }
void Animal::changeEatCount(int EatCount) { eatCount=EatCount; }
void Animal::changeSpeed(int Speed) { speed=Speed; }
void Animal::changeIsAlive() { isAlive=false; }
void Animal::changeIsHungry(bool IsHungry) { isHungry=IsHungry; }
void Animal::changeInHeat(bool InHeat) { inHeat=InHeat; }
void Animal::changeHibernates(bool Hibernates) { hibernates=Hibernates; }
void Animal::changeInHibernation(bool InHibernation) { inHibernation=InHibernation; }

///////////////////////////////////////////////////////////////////////////////////////////////

Herbivores::Herbivores(string name_, string token_, int x_, int y_, int size_, int hungerCount_, int eatenFood_, int eatCount_, int speed_,
	bool isAlive_,bool isHungry_,bool inHeat_,bool hibernates_,bool inHibernation_, bool canClimb_, int neededFood_)
	: Animal(name_, token_, x_, y_, size_, hungerCount_, eatenFood_, eatCount_, speed_, isAlive_, isHungry_, inHeat_, hibernates_, inHibernation_), 
	  canClimb(canClimb_), neededFood(neededFood_)
{}
Herbivores::~Herbivores() {}

void Herbivores::printAll()
{
	Animal::printAll();
	cout << "Can Climb: ";
	if (canClimb==true)
		cout << "Yes\n";
	else cout << "No\n";
	cout << "Needed Food: " << neededFood << endl << endl;
}

bool Herbivores::getCanClimb() { return canClimb; }
int Herbivores::getNeededFood() { return neededFood; }

void Herbivores::changeNeededFood(int NeededFood) { neededFood=NeededFood; }

///////////////////////////////////////////////////////////////////////////////////////////////

Carnivores::Carnivores(string name_, string token_, int x_, int y_, int size_, int hungerCount_, int eatenFood_, int eatCount_, int speed_,
	bool isAlive_,bool isHungry_,bool inHeat_,bool hibernates_,bool inHibernation_, int attack_, int defence_)
	: Animal(name_, token_, x_, y_, size_, hungerCount_, eatenFood_, eatCount_, speed_, isAlive_, isHungry_, inHeat_, hibernates_, inHibernation_), 
	  attack(attack_), defence(defence_)
{}
Carnivores::~Carnivores() {}

void Carnivores::printAll()
{
	Animal::printAll();
	cout << "Attack: " << attack << endl;
	cout << "Defence: " << defence << endl << endl;
}

int Carnivores::getAttack() { return attack; }
int Carnivores::getDefence() { return defence; }
void Carnivores::changeAttack(int attack_) { attack=attack_;  }
void Carnivores::changeDefence(int defence_) { defence=defence_;  }

///////////////////////////////////////////////////////////////////////////////////////////////

// name, token, x, y, size, hungerCount, eatenFood, eatCount, speed, isAlive, isHungry, inHeat, hibernates, inHibernation
// canClimb, neededfood

Deer::Deer(int x_, int y_) : Herbivores("Deer", "H", x_, y_,5,0,0,0,8,1,1,0,0,0,0, 8){
	//cout<< "Deer just created" <<endl;
}

Deer::Deer(bool justBorn, int x_, int y_) : Herbivores("Deer", "H",x_,y_,2,0,0,0,4,1,1,0,0,0,0,4){
	//cout<< "baby Deer just created" <<endl;
}

Deer::~Deer() {}

void Deer::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),y_=getY();
	//cout<<"deer moving from:  "<< x_<<","<<y_<<"to:   ";
	while( getX()==x_ && getY()==y_ ){
		t=rand()%4;
		if(t==0){
			if (getX()-1>0 )	x_--;
		}
	    else if(t==1){
			if (getX()+1<terrainSize) x_++;
		}
		else if(t==2){
			if (getY()-1>0) y_--;
		}
		else if(t==3){
			if(getY()+1<terrainSize) y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}
void Deer::Eat(tiles **terrain, deque<Animal*> an)
{	
	//cout<<"deer eating"<<endl;
	
	if( getHungerCount()==0 ){
		int n=getNeededFood();
		int t=getEatenFood();
		if ( t  < n ){
			int x_=getX(),y_=getY();
			Plant* p=terrain[x_][y_].getP();
			if( p !=NULL){
				//cout<<"there is a plant in danger"<<endl;
					if  ( p->getName()  == "Grass" || p->getName() == "Algae"  ){
				    	changeEatCount( p->LoseLife(2) );
				    	//cout<<"deer ate   "<<  p->getName() <<endl;
					}
					else {
						Seeded* s;
						s = (Seeded*) p;
						if (  s->getSize()  < getSize() +4 ){
							changeEatCount( p->LoseLife(2) );
							//cout<<"deer ate   "<<  p->getName() <<endl;
						}
					}
				changeEatenFood( getEatenFood() + getEatCount() );
				//cout<<"eaten food:   "<< getEatenFood()<<endl;
			}
		}
	}
	//cout<<"end of deer eating"<<endl;
}

void Deer::Raise(){
	if (getSize() <5) changeSize(1);
	if (getSpeed() <7) changeSpeed(2);
	if ( getNeededFood() <7) changeNeededFood(2);
}


Rabbit::Rabbit(int x_,int y_):Herbivores("Rabbit","H",x_,y_,2,0,0,0,6,1,1,0,0,0,0,4){
	//cout<< "Rabbit just created"<<endl;
	}

Rabbit::Rabbit(bool justBorn,int x_,int y_):Herbivores("Rabbit","H",x_,y_,1,0,0,0,2,1,1,0,0,0,0,2){
	//cout<< "baby Rabbit just created"<<endl;
}

void Rabbit::Move(tiles **terrain,int terrainSize){
	int t,x1=getX(),x_=getX(),y1=getY(),y_=getY();
	//cout<<"rabbit moving from:  "<< x_<<","<<y_<<"to:   ";
	while( x1==x_ && y1==y_ ){
		t=rand()%4;
		if(t==0){
			if (x1-1>0 )
				if ( ( terrain[x1-1][y1]) .retT() != "^")	x_--;
		}
	    else if(t==1){
			if (x1+1<terrainSize )
				if ( terrain[x1+1][y1].retT()!= "^") x_++;
		}
		else if(t==2){
			if (y1-1>0 )
			if ( terrain[x1][y1-1].retT() != "^") y_--;
		}
		else if(t==3){
			if( y1+1<terrainSize )
				if ( terrain[x1][y1+1].retT()!= "^") y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Rabbit::Eat(tiles **terrain,deque<Animal*> an) {
	//cout<<"rabbit eating"<<endl;
	if( getHungerCount()==0 ){
		int t=getEatenFood();
		int n=getNeededFood();
		if ( t < n ){
			int x_=getX();
			int y_=getY();
			Plant* p=terrain[x_][y_].getP();
			if( p != NULL && ( terrain[ getX() ][ getY() ] ).retT() !="#"){
				if ( p->getName() =="Grass"  ){
				   changeEatCount( p->LoseLife(1)  );
				  // cout<<"rabbit ate   "<<  p->getName() <<endl;
				}
				else{
						Seeded* s;
						s = (Seeded*) p;
					if ( s ->getSize() <= getSize() ){
						changeEatCount( p->LoseLife(1)  );
						//cout<<"rabbit ate   "<<  p->getName() <<endl;
					}
				}
				changeEatenFood( getEatenFood() + getEatCount() );
			}
		}
	}
	//cout<<"end or rabbit eating"<<endl;
}

void Rabbit::Raise(){
	if (getSize() < 2) changeSize(1);
	if (getSpeed() < 6) changeSpeed(2);
	if (getNeededFood() < 4) changeNeededFood(1);
}

Rabbit::~Rabbit() {}

///////////////////////////////////////////////////////////////////////////////////////////////

Groundhog::Groundhog(int x_,int y_):Herbivores("Groundhog","H",x_,y_,3,0,0,0,5,1,1,0,0,0,1,5){
	//cout<< "Groundhog just created" <<endl;
}

Groundhog::Groundhog(bool justBorn,int x_,int y_):Herbivores("Rabbit","H",x_,y_,2,0,0,0,3,1,1,0,0,0,1,3){
	//cout<< "baby Groundhog just created" <<endl;
}

void Groundhog::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),x1=getX(),y_=getY(),y1=getY();
	//cout<<"groundhog moving from:  "<< x_<<","<<y_<<"to:   ";
	while( x1==x_ && y1==y_ ){
		t=rand()%4;
		if(t==0){
			if (x1-1>0 )
				if ( terrain[x1-1][y1].retT()!= "#")	x_--;
		}
	    else if(t==1){
			if (x1+1<terrainSize )
				if ( terrain[x1+1][y1].retT()!= "#") x_++;
		}
		else if(t==2){
			if (y1-1>0 )
				if( terrain[x1][y1-1].retT()!= "#") y_--;
		}
		else if(t==3){
			if(y1+1<terrainSize )
				if ( terrain[x1][y1+1].retT()!= "#") y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Groundhog::Eat(tiles **terrain,deque<Animal*> an) {
	//cout<<"groundhog eating"<<endl;
	if( getHungerCount()==0 ){
		int t=getEatenFood();
		int n=getNeededFood();
		if ( t  < n ){
		    int x_=getX();
			int y_=getY();
			Plant* p=terrain[x_][y_].getP();
			if( p!=NULL && ( terrain[x_][y_] ).retT() !="#"){
				if (p-> getName()=="Grass" ){
				   	changeEatCount( p-> LoseLife(1) );
				   //cout<<"groundhog ate   "<<  p->getName() <<endl;
				}
				else {
					Seeded* s;
					s = (Seeded*) p;
					if ( ( s )-> getSize() <= getSize() && ( s)-> getSize() <= 3*getSize() ){
						changeEatCount( p->LoseLife(1) );
						//cout<<"groundhog ate   "<<  p->getName() <<endl;
					}
				}
				changeEatenFood( getEatenFood() + getEatCount() );
			}
		}
	}
	//cout<<"end of groundhog eating"<<endl;
}

void Groundhog::Raise(){
	if (getSize() < 3) changeSize(1);
	if ( getSpeed()<5) changeSpeed(1);
	if ( getNeededFood() < 5) changeNeededFood(1);
}

Groundhog::~Groundhog() {}

///////////////////////////////////////////////////////////////////////////////////////////////

Salmon::Salmon(int x_,int y_):Herbivores("Salmon","H",x_,y_,1,0,0,0,5,1,1,0,0,0,0,1){
	//cout<< "Salmon just created"<<endl;
}

void Salmon::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),x1=getX(),y_=getY(),y1=getY();
	//cout<<"salmon moving from:  "<< x_<<","<<y_<<"to:   ";
	while( x1==x_ && y1==y_ ){
		t=rand()%4;
		if(t==0){
			if (x1-1>0 )
				if ( terrain[x1-1][y1].retT()== "#")	x_--;
		}
	    else if(t==1){
			if (x1+1<terrainSize )
				if( terrain[x1+1][y1].retT()== "#") x_++;
		}
		else if(t==2){
			if (y1-1>0 )
				if ( terrain[x1][y1-1].retT()== "#") y_--;
		}
		else if(t==3){
			if(y1+1<terrainSize)
				if ( terrain[x1][y1+1].retT()== "#") y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Salmon::Eat(tiles **terrain,deque<Animal*> an) {
	//cout<<"salmon eating"<<endl;
	if( getHungerCount() ==0 ){
		if ( getEatenFood() < getNeededFood() ){
			int x_=getX();
			int y_=getY();
			Plant* p=terrain[x_][y_].getP();
			if( p !=NULL ){
				changeEatCount( p->LoseLife(1) );
				//cout<<"salmon ate   "<<  p->getName() <<endl;
			}
			changeEatenFood( getEatenFood() + getEatCount() );
		}
	}
	//cout<<"end of salmon eating"<<endl;
}



void Salmon::Raise(){}

Salmon::~Salmon() {}


Fox::Fox(int x_, int y_) : Carnivores("Fox","C",x_,y_,4,0,0,0,6,1,1,0,0,0,5,5){
	//cout<< "Fox just created" <<endl;
}

Fox::Fox(bool justBorn, int x_, int y_) : Carnivores("Fox","C",x_,y_,1,0,0,0,1,1,0,0,0,0,1,1){
	//cout<< "baby Fox just created" <<endl;
}

void Fox::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),y_=getY();
	//cout<<"fox moving from:  "<< x_<<","<<y_<<"to:   ";
	while( getX()==x_ && getY()==y_ ){
		t=rand()%4;
		if(t==0){
			if (getX()-1>0 )	x_--;
		}
	    else if(t==1){
			if (getX()+1<terrainSize) x_++;
		}
		else if(t==2){
			if (getY()-1>0) y_--;
		}
		else if(t==3){
			if(getY()+1<terrainSize) y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Fox::Eat(tiles **terrain,deque<Animal*> an){
	deque<Animal*>::iterator it;
	for ( it=an.begin() ; it != an.end(); it++ ){
		if ( getIsHungry() ){
			if ( (*it)->getX()==getX()  &&  (*it)->getY()==getY() ){
				if ( (*it)->getIsAlive() ){
					if ( (*it)->getToken() == "H" && (*it)->getName()!="Salmon" ){
						if ( (*it)->getSize() <= getSize() && (*it)->getSpeed() < getSpeed() ){
							(*it)->changeIsAlive();
							changeEatCount(0);
							changeIsHungry(0);
							changeHungerCount(0);
							//cout<<"eating a herbivore   "<<(*it)->getName()<<endl;
						}
					}
					else if ((*it)->getToken()=="C"   && getHungerCount()>8    ){
							if(  Carnivores* c = dynamic_cast<Carnivores*>(*it)    ){
								if( *it!=this ){
	   								if ( ( c->getSize()<= getSize() ) || ( c->getSize()== getSize() && c->getDefence() < getAttack() )   ){
										c->changeIsAlive();
										changeEatCount(0);
										changeIsHungry(0);
										//cout<<"eating a carnivore   "<<(*it)->getName()<<endl;
									}
								}
							}
					}
				}
			}
		}
		else break;
	}
}

void Fox::Raise(){
	if ( getSize()<4  ) changeSize(1);
	if ( getAttack()<5 ) changeAttack(1);
	if ( getDefence()<5 ) changeDefence(1);
	if ( getSpeed()<6 ) changeSpeed(1);
}

Wolf::Wolf(int x_, int y_) : Carnivores("Wolf","C",x_,y_,7,0,0,0,8,1,1,0,0,0,8,6){
		//cout<< "wolf just created"<<endl;
}

Wolf::Wolf(bool justBorn, int x_, int y_) : Carnivores("Wolf","C",x_,y_,1,0,0,0,2,1,1,0,0,0,2,2){
	//cout<< "baby wolf just created"<<endl;
}


void Wolf::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),y_=getY();
		//cout<<"wolf moving from:  "<< x_<<","<<y_<<"to:   ";
	while( getX()==x_ && getY()==y_ ){
		t=rand()%4;
		if(t==0){
			if (getX()-1>0 )	x_--;
		}
	    else if(t==1){
			if (getX()+1<terrainSize) x_++;
		}
		else if(t==2){
			if (getY()-1>0) y_--;
		}
		else if(t==3){
			if(getY()+1<terrainSize) y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Wolf::Eat(tiles **terrain,deque<Animal*> an){
	deque<Animal*>::iterator it;
	for ( it=an.begin() ; it != an.end(); it++ ){
		if ( getIsHungry() ){
			if ( (*it)->getX()==getX()  &&  (*it)->getY()==getY() ){
				if ( (*it)->getIsAlive() ){
					if ( (*it)->getToken() == "H" && (*it)->getName()!="Salmon" ){
						if ( (*it)->getSize() <= getSize() && (*it)->getSpeed() < getSpeed() ){
							(*it)->changeIsAlive();
							changeEatCount(0);
							changeIsHungry(0);
							changeHungerCount(0);
						//	cout<<"eating a herbivore   "<<(*it)->getName()<<endl;
						}
					}
					else if ((*it)->getToken()=="C" && getHungerCount()>8 ){
							if(  Carnivores* c = dynamic_cast<Carnivores*>(*it)    ){
								if( *it!=this ){
	   								if ( ( c->getSize()<= getSize() ) || ( c->getSize()== getSize() && c->getDefence() < getAttack() )   ){
										c->changeIsAlive();
										changeEatCount(0);
										changeIsHungry(0);
									//	cout<<"eating a carnivore   "<<(*it)->getName()<<endl;
									}
								}
							}
					}
				}
			}
		}
		else break;
	}
}


void Wolf::Raise(){
	if ( getSize()<7  ) changeSize(1);
	if ( getAttack()<7 ) changeAttack(2);
	if ( getDefence()<5 ) changeDefence(2);
	if ( getSpeed()<7 ) changeSpeed(2);
}

Bear::Bear(int x_, int y_) : Carnivores("Bear","C",x_,y_,10,0,0,0,4,1,1,0,0,0,10,10){
	//cout<< "Bear just created" <<endl;
}

Bear::Bear(bool justBorn, int x_, int y_) : Carnivores("Bear","C",x_,y_,3,0,0,0,4,1,0,0,0,0,6,6){
	//cout<< "baby Bear just created" <<endl;
}


void Bear::Move(tiles **terrain,int terrainSize){
	int t,x_=getX(),y_=getY();
	//cout<<"bear moving from:  "<< x_<<","<<y_<<"to:   ";
	while( getX()==x_ && getY()==y_ ){
		t=rand()%4;
		if(t==0){
			if (getX()-1>0 )	x_--;
		}
	    else if(t==1){
			if (getX()+1<terrainSize) x_++;
		}
		else if(t==2){
			if (getY()-1>0) y_--;
		}
		else if(t==3){
			if(getY()+1<terrainSize) y_++;
		}
	}
	changeX(x_);
	changeY(y_);
	//cout<<x_<<","<<y_<<endl;
}

void Bear::Eat(tiles **terrain,deque<Animal*> an){
	deque<Animal*>::iterator it;
	for ( it=an.begin() ; it != an.end(); it++ ){
		if ( getIsHungry() ){
			if ( (*it)->getX()==getX()  &&  (*it)->getY()==getY() ){
				if ( (*it)->getIsAlive() ){
					if ( (*it)->getToken() == "H"  ){
						(*it)->changeIsAlive();
						changeEatCount(0);
						changeIsHungry(0);
					}
					else if ((*it)->getToken()=="C"  &&   (*it)->getName()=="Bear" && getHungerCount()>8 ){
						if( getHungerCount()>7 ){
							if(  Carnivores* c = dynamic_cast<Carnivores*>(*it)    ){
		   						if ( ( c->getSize()<= getSize() ) || ( c->getSize()== getSize() && c->getDefence() < getAttack()  )   ){
									c->changeIsAlive();
									changeEatCount(0);
								}
							}
						}
					}
				}
			}
		}
		else break;
	}
}

void Bear::Raise(){
	if ( getSize()<9  ) changeSize(2);
	else if ( getSize()==9 ) changeSize(1);
	if ( getAttack()<9 ) changeAttack(2);
	else if ( getAttack()==9 ) changeAttack(1);
	if ( getDefence()<9 ) changeDefence(2);
	else if ( getDefence()==9 ) changeDefence(1);
	if ( getSpeed()<3 && getSpeed()+1<4 ) changeSpeed(2);
	else  changeSpeed(1); 
}




