// File: plant.h

#ifndef PLANT_H
#define PLANT_H

#include <iostream>

class Plant;

class tiles
{
	std::string T;
	Plant* P;

public:

	tiles();
	~tiles();

	void chtiles(std::string T_);
	std::string retT();
	Plant* getP();
	void printTile();
	void printTile2();
	void printP();
	void put_plant(std::string token, int x, int y);
	void deleteP();
};

class Plant
{
	std::string name;
	std::string token;
	int x;
	int y;
	int breedingProb;
	int illnessProb;
	int life;
	int lifeFactor;

public:

	Plant(std::string,std::string,int,int,int,int,int,int);
	virtual ~Plant();

	virtual int LoseLife (int amount) = 0;		// Got eaten
	virtual void Grow() = 0;
	virtual bool Breed(tiles&,int,int) = 0;
	virtual bool CheckSurvival(tiles&) = 0;

	std::string getName();
	std::string getToken();
	int getX();
	int getY();
	int getBreedingProb();
	int getIllnessProb();
	int getLife();
	int getLifeFactor();
	void changeLife(int life_);

	virtual void printAll() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Seedless : public Plant
{

public:

	Seedless(std::string,std::string,int,int,int,int,int,int);
	virtual ~Seedless();

	int LoseLife (int amount);				// LoseLife is alike for all seedless plants
	void Grow();							// Grow is alike for all seedless plants
	virtual bool Breed(tiles&,int,int) = 0;
	virtual bool CheckSurvival(tiles&) = 0;

	virtual void printAll() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Seeded : public Plant
{
	int size;
	int foliage;
	int seeds;

public:

	Seeded(std::string,std::string,int,int,int,int,int,int,int,int,int);
	virtual ~Seeded();

	int LoseLife (int amount);				// LoseLife is alike for all seeded plants
	void Grow();							// Grow is alike for all seeded plants
	virtual bool Breed(tiles&,int,int) = 0;
	virtual bool CheckSurvival(tiles&) = 0;

	int getSize();
	int getSeeds();
	int getFoliage();

	void changeSize(int);
	void changeSeeds(int);
	void changeFoliage(int);

	virtual void printAll() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Grass : public Seedless
{
	
public:
	Grass(int, int);
	Grass(Grass&);
	~Grass();

	bool Breed(tiles&,int,int);
	bool CheckSurvival(tiles&);
	std::string survivePlace();

	void printAll();
};


class Algae : public Seedless
{
public:
	Algae(int, int);
	~Algae();

	bool Breed(tiles&,int,int);
	bool CheckSurvival(tiles&);
	std::string survivePlace();

	void printAll();
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Oak : public Seeded
{
public:
	Oak(int,int);
	~Oak();

	bool Breed(tiles&,int,int);
	bool CheckSurvival(tiles&);
	std::string survivePlace();

	void printAll();
};

class Pine : public Seeded
{
public:
	Pine(int, int);
	~Pine();

	bool Breed(tiles&,int,int);
	bool CheckSurvival(tiles&);
	std::string survivePlace();

	void printAll();
};

class Maple : public Seeded
{
public:
	Maple(int, int);
	~Maple();

	bool Breed(tiles&,int,int);
	bool CheckSurvival(tiles&);

	void printAll();
};

///////////////////////////////////////////////////////////////////////////////////////////////

bool check_if_Integer(float);

#endif		// PLANT_H

