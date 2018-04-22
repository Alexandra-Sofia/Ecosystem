// File: animals.h

#ifndef ANIMALS_H
#define ANIMALS_H

#include "plants.h"
#include <deque>

class Animal
{
	std::string name;
	std::string token;
	int x;
	int y;
	int size;
	int hungerCount;
	int eatenFood;
	int eatCount;
	int speed;
	bool isAlive;
	bool isHungry;
	bool inHeat;
	bool hibernates;
	bool inHibernation;

public:

	// name, token, x, y, size, hungerCount, eatenFood, eatCount, speed, isAlive, isHungry, inHeat, hibernates, inHibernation
	Animal(std::string,std::string,int,int,int,int,int,int,int,bool,bool,bool,bool,bool);
	~Animal();

	virtual void Move(tiles **, int)=0;
	virtual void Eat(tiles **, std::deque<Animal*>)=0;
	virtual void Raise()=0;

	virtual void printAll();

	std::string getName();
	std::string getToken();
	int getX();
	int getY();
	int getSize();
	int getHungerCount();
	int getEatenFood();
	int getEatCount();
	int getSpeed();
	bool getIsAlive();
	bool getIsHungry();
	bool getInHeat();
	bool getHibernates();
	bool getInHibernation();

	void changeX(int);
	void changeY(int);
	void changeSize(int);
	void changeHungerCount(int);
	void changeEatenFood(int);
	void changeEatCount(int);
	void changeSpeed(int);
	void changeIsAlive();
	void changeIsHungry(bool);
	void changeInHeat(bool);
	void changeHibernates(bool);
	void changeInHibernation(bool);
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Herbivores : public Animal
{
	bool canClimb;
	int neededFood;

public:

	// The two last are canClimb, neededfood. All rest are members of class Animal
	Herbivores(std::string,std::string,int,int,int,int,int,int,int,bool,bool,bool,bool,bool,bool,int);
	~Herbivores();

	virtual void Move(tiles **,int)=0;
	virtual void Eat(tiles **,std::deque<Animal*>)=0;
	virtual void Raise()=0;

	bool getCanClimb();
	int getNeededFood();

	virtual void printAll();

	void changeNeededFood(int);
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Carnivores : public Animal
{
	int attack;
	int defence;

public:

	// The two last are attack, defence. All rest are members of class Animal
	Carnivores(std::string,std::string,int,int,int,int,int,int,int,bool,bool,bool,bool,bool,int,int);
	~Carnivores();

	virtual void Move(tiles **,int)=0;
	virtual void Eat(tiles **,std::deque<Animal*>)=0;
	virtual void Raise()=0;

	virtual void printAll();

	int getAttack();
	int getDefence();
	virtual void changeAttack(int);
	virtual void changeDefence(int);
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Deer : public Herbivores
{
public:
	// x and y
	Deer(int,int);
	// The boolean variable is used to distinguish the constructor for young Deer from the adult's Deer constructor
	Deer(bool justBorn,int,int);
	~Deer();

	void Move(tiles **,int);
	void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

class Rabbit : public Herbivores
{
public:
	Rabbit(int,int);
	Rabbit(bool,int,int);
	~Rabbit();

	void Move(tiles **,int);
	void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

class Groundhog : public Herbivores
{
public:
	Groundhog(int,int);
	Groundhog(bool,int,int);
	~Groundhog();

	void Move(tiles **,int);
	virtual void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

class Salmon : public Herbivores
{
public:
	Salmon(int,int);
	Salmon(bool,int,int);
	~Salmon();

	void Move(tiles **,int);
	virtual void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Fox : public Carnivores
{
public:
	Fox(int,int);
	Fox(bool,int,int);
	~Fox();

	void Move(tiles **,int);
	virtual void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

class Bear : public Carnivores
{
public:
	Bear(int,int);
	Bear(bool,int,int);
	~Bear();

	void Move(tiles **,int);
	virtual void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

class Wolf : public Carnivores
{
public:
	Wolf(int,int);
	Wolf(bool,int,int);
	~Wolf();

	void Move(tiles **,int);
	virtual void Eat(tiles **,std::deque<Animal*>);
	void Raise();
};

///////////////////////////////////////////////////////////////////////////////////////////////

#endif
