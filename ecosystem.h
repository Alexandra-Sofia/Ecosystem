// File: ecosystem.h

#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include "animals.h" 

class Ecosystem
{
	tiles** terrain;
	int terrainSize;
	int lakeSize;
	int hillsNumber;
	int dayOfYear;
	int days;
	int PlantGrowthPeriod;
 	int AnimalGrowthPeriod;
 	int PlantBreedingRepPeriod;
	int HerbivoresBreedingRepPeriod;
	int CarnivoresBreedingRepPeriod;
	std::string season;
	std::deque <Animal*> A;

public:

	Ecosystem(int terrainSize_);
	~Ecosystem();

	void MapGenerator();
	void GenerateRiver();
	void GenerateLake();
	void GenerateHills();
	void GenerateMeadow();
	void PlacePlants(int,int,int,int,int);
	void PlaceAnimals(int,int,int,int,int,int,int);	
	void FindFreeTile();			
	void PlantBreeding();
	void AnimalBreeding();
	void PrintTerrain();
	void PrintSystem();
	void RunEcosystem();
	void PrintPlantStatistics();
	void PrintAnimalStatistics();
	void PrintAnimalCharacteristics();
	void AnimalMovement();
	void AnimalEating();
	void ApplySeason(std::string);
	void CheckHunger();
	int DecidePlants();
	void DailyReset();
	void CheckDeadEntities();
	void countElements(int&,int&,int&);
	bool checkbounds(int,int);
};

#endif		// ECOSYSTEM_H

