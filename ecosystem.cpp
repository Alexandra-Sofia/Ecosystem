// File: ecosystem.cpp

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "ecosystem.h"

using namespace std;

Ecosystem::Ecosystem(int terrainSize_) : terrainSize(terrainSize_)
{
	int i;
	ApplySeason("winter");
	terrain=new tiles*[terrainSize];
	for(i=0; i<terrainSize; i++)
	{
		terrain[i]=new tiles[terrainSize];
	}

	i = rand()%((terrainSize/5)+1);
	while (i<2) i = rand()%((terrainSize/5)+1);
	lakeSize = i;

	hillsNumber = terrainSize/3;
	days=20;
}

Ecosystem::~Ecosystem()
{
	int i;
	for(i=0;i<terrainSize;i++){
		delete [] terrain[i];
	}
	delete [] terrain;

}

void Ecosystem::MapGenerator()
{ 
	GenerateRiver();
	GenerateLake();
	GenerateHills();
	GenerateMeadow();
	PlacePlants(3,3,3,3,3);
	PlaceAnimals(4,10,10,10,6,6,2);
}

void Ecosystem::GenerateRiver()
{
	int t,x,y;
	t=rand()%(terrainSize-5);
	terrain[5][t].chtiles("#");				//to prvto bhma tou potamiou
	x=6;
	y=t;
	while (x<terrainSize)
	{   //oso to potami den exei ftasei sthn apenadi plevra
		terrain[x][y].chtiles("#");						//to potami proxwra ena vhma
		if(rand()%101<=30){
			t=rand();
			if (t%2==0 && y+1<terrainSize){				//to potami stribei de3ia mia thesi
				terrain[x][y+1].chtiles("#");
				y++;									//h nea thesi tou potamiou einai 1 stili de3ia
				if(rand()%2==1 && y+1<terrainSize){		//to potami parklinei de3ia 2 thesis
					terrain[x][y+1].chtiles("#");
					y++;								//h nea thesi tou potamiou einai dyo grammes pio katw
				}
			}
			if(t%2==1 && y-1>0)
			{											//to potami tha stripsei aristera
				terrain[x][y-1].chtiles("#");
				y--;									//h nea thesi tou potamiou einai 1 grammi pio katw
				if(rand()%2==1 && y-1>0){
					terrain[x][y-1].chtiles("#");
					y--;								//h nea thesi tou potamiou einai dyo grammes pio katw
				}
			}
		}
		x++;
	}
}


void Ecosystem::GenerateLake()
{
	int x,y,i,j;
	x=rand()%(terrainSize-lakeSize);
	y=rand()%(terrainSize-lakeSize);
	for(i=x;i<=lakeSize+x;i++){
		for(j=y;j<=lakeSize+y;j++){
			terrain[i][j].chtiles("#");
		}
	}
}

void Ecosystem::GenerateHills()
{
	int i,t,x,y;

	for(i=0; i<hillsNumber; i++)
	{
		t=rand();
		x=rand()%(terrainSize-1);
		y=rand()%(terrainSize-1);
  		if(terrain[x][y].retT()==" " && terrain[x][y+1].retT()==" ")
		{	
			terrain[x][y].chtiles("^");
			terrain[x][y+1].chtiles("^");
			if(t%3==0 && (y+2)<terrainSize && terrain[x][y+2].retT()==" ")
				terrain[x][y+2].chtiles("^");
			else
			{
				t=rand();
				if(t%3==1 && (y+3)<terrainSize && terrain[x][y+2].retT()==" " && terrain[x][y+3].retT()==" ")
				{
					terrain[x][y+2].chtiles("^");
					terrain[x][y+3].chtiles("^");
				}
			}			
		}
		else
			i--;
	}
}


void Ecosystem::GenerateMeadow()
{
	int x=0,y=0;
	
	for (x=0; x<terrainSize; x++)
		for (y=0; y<terrainSize; y++)
			if ( terrain[x][y].retT()==" " )
				terrain[x][y].chtiles("\"");
}

// Grass, Algae, Oak, Pine, Maple
void Ecosystem::PlacePlants(int g, int a, int o, int p, int m)
{
	int i, j;
	int water, hills, valley;
	int grass, algae, oak, pine, maple;
	countElements(water, hills, valley);
	grass = algae = oak = pine = maple = 0;
	//cout << water << " "<< hills << " "<< valley << " "<< endl;
	
	// if input isn't realistic, change it
	if (water<a)
	{
		a=rand()%water;
	}
	if (hills<m+p)
	{
		p=rand()%hills;
	}
	if (valley<g+m+o)
	{
		g=rand()%valley;
		o=rand()%(valley-g);
		m=rand()%(valley-g-o);	
	}
	
	//cout << "grass: "<< g << ", algae: "<< a << ", oak: "<< o << ", pine: "<< p << ", maple: "<< m <<  endl;
	
	// While we haven't put all plants in random place keep going
	while (grass!=g || algae!=a || oak!=o || pine!=p || maple!=m)
		for (i=0; i<terrainSize; i++)
			for (j=0; j<terrainSize; j++)
			{
				// For each tile there is a terrainSize% possibility of plant
				if (rand()%terrainSize!=0)
					continue;

				if (terrain[i][j].retT().compare("#")==0)
				{
					// Algae
					if (algae!=a) {
						terrain[i][j].put_plant("A", i, j);
						algae++;
					}
				}
				else if (terrain[i][j].retT().compare("^")==0)
				{
					// Maple
					// Pine
					// Don't place maples before pines
					if (maple!=m && pine==p)
						if (rand()%2==0) {
							terrain[i][j].put_plant("M", i, j);
							maple++;
							continue;
						}

					if (pine!=p) {
						terrain[i][j].put_plant("P", i, j);
						pine++;
					}
				}
				else if (terrain[i][j].retT().compare("\"")==0)
				{
					// Grass
					// Maple
					// Oak
					if (rand()%3==0 && grass!=g) {
						terrain[i][j].put_plant("G", i, j);
						grass++;
						continue;
					}				
					if (rand()%2==0 && maple!=m) {
						terrain[i][j].put_plant("M", i, j);
						maple++;
						continue;
					}
					if (oak!=o) {
						terrain[i][j].put_plant("O", i, j);
						oak++;
					}					
				}		
			}
}

void Ecosystem::PlantBreeding()
{
	int i, j;

	//cout << "Start of Plant Breeding\n";

	if (PlantBreedingRepPeriod) {
		if (dayOfYear%PlantBreedingRepPeriod!=0)
			return;
	}
	else return;	
/*
	for (i=0; i<terrainSize; i++)
		for (j=0; j<terrainSize; j++)
		{
			int t;
			int x=i,y=j;
			if (terrain[i][j].getP()==NULL)
				continue;
			
			// pairs: (i, j-1), (i, j+1), (i-1, j), (i+1, j)
			while ( x==i && y==j ){
				
				t=rand()%4;
				cout << "got stuck\n";
				cout<<"  "<<x<<"   "<<y<<endl;
				if (t==0){
					
					if (checkbounds(i, j-1)==true)
					{
						
						if (terrain[i][j].getP()->CheckSurvival(terrain[i][j-1])==true
							&& terrain[i][j-1].getP()==NULL) 
						{
							terrain[i][j].getP()->Breed(terrain[i][j-1],i,j-1);							
							y--;
							cout<<" got in 0"<<endl;
							//continue;
							
						}
					}
				}
				else if (t==1){
					
					if (checkbounds(i, j+1)==true)
					{
						
						if (terrain[i][j].getP()->CheckSurvival(terrain[i][j+1])==true
							&& terrain[i][j+1].getP()==NULL) 
						{
							terrain[i][j].getP()->Breed(terrain[i][j+1],i,j+1);
							y++;
							//continue;
							cout<<" got in 1"<<endl;
							cout<<"  "<<x<<"   "<<y<<endl;
						}
					}
				}
				else if (t==2){
					if (checkbounds(i-1, j)==true)
					{
						
						if (terrain[i][j].getP()->CheckSurvival(terrain[i-1][j])==true
							&& terrain[i-1][j].getP()==NULL) 
						{
							cout<<" got in 2"<<endl;
							terrain[i][j].getP()->Breed(terrain[i-1][j],i-1,j);
							x--;
							//continue;
							cout<<"  "<<x<<"   "<<y<<endl;
						}
					}
				}
				else{
					
					if (checkbounds(i+1, j)==true)
					{
						
						if (terrain[i][j].getP()->CheckSurvival(terrain[i+1][j])==true
						&& terrain[i+1][j].getP()==NULL) 
						{
							cout<<" got in 3"<<endl;
							terrain[i][j].getP()->Breed(terrain[i+1][j],i+1,j);
							x++;
							//continue;
							cout<<"  "<<x<<"   "<<y<<endl;
						}
					}
				}
		}
	}*/
	for (i=0; i<terrainSize; i++)
		for (j=0; j<terrainSize; j++)
		{
			if (terrain[i][j].getP()==NULL)
				continue;
			
			// pairs: (i, j-1), (i, j+1), (i-1, j), (i+1, j)
			if (checkbounds(i, j-1)==true)
			{
				if (terrain[i][j].getP()->CheckSurvival(terrain[i][j-1])==true
					&& terrain[i][j-1].getP()==NULL) 
				{
					terrain[i][j].getP()->Breed(terrain[i][j-1],i,j-1);
					continue;
				}
			}

			if (checkbounds(i, j+1)==true)
			{
				if (terrain[i][j].getP()->CheckSurvival(terrain[i][j+1])==true
					&& terrain[i][j+1].getP()==NULL) 
				{
					terrain[i][j].getP()->Breed(terrain[i][j+1],i,j+1);
					continue;
				}
			}
			
			if (checkbounds(i-1, j)==true)
			{
				if (terrain[i][j].getP()->CheckSurvival(terrain[i-1][j])==true
					&& terrain[i-1][j].getP()==NULL) 
				{
					terrain[i][j].getP()->Breed(terrain[i-1][j],i-1,j);
					continue;
				}
			}
			
			if (checkbounds(i+1, j)==true)
			{
				if (terrain[i][j].getP()->CheckSurvival(terrain[i+1][j])==true
					&& terrain[i+1][j].getP()==NULL) 
				{
					terrain[i][j].getP()->Breed(terrain[i+1][j],i+1,j);
					continue;
				}
			}
		}
		
		//cout << "End of Plant Breeding\n";
}

void Ecosystem::FindFreeTile()
{

}

int Ecosystem::DecidePlants()
{
	int i, j;
	int water=0;
	int meadow=0;
	int hills=0;

	for (i=0; i<terrainSize; i++)
		for (j=0; j<terrainSize; j++)
		{
			if (terrain[i][j].retT() == "#") water++;
			else if (terrain[i][j].retT() == "\"") meadow++;
			else if (terrain[i][j].retT() == "^") hills++;
		}
		return water;
}

void Ecosystem::PrintTerrain()
{
	int i, j;

	for (i=0; i<terrainSize; i++)
	{
		cout << endl;
		for (j=0; j<terrainSize; j++)
			terrain[i][j].printTile2();
	}
}

void Ecosystem::PrintSystem()
{
	int i, j;

	for (i=0; i<terrainSize; i++)
	{
		cout << endl;
		for (j=0; j<terrainSize; j++)
			terrain[i][j].printTile();		
	}
	
	cout << "\n\n";
	
	PrintPlantStatistics();
	PrintAnimalStatistics();
}

void Ecosystem::PrintPlantStatistics()
{
	int i, j;
	string token;
	int grass, algae, oak, pine, maple;
	grass = algae = oak = pine = maple = 0;
	
	for (i=0; i<terrainSize; i++)
		for (j=0; j<terrainSize; j++) 
		{
			if (terrain[i][j].getP()==NULL)
				continue;

			token.assign(terrain[i][j].getP()->getToken());

			if (token.compare("G")==0)
			{
				grass++;
			}
			else if (token.compare("A")==0)
			{
				algae++;
			}
			else if (token.compare("O")==0)
			{
				oak++;
			}
			else if (token.compare("P")==0)
			{
				pine++;
			}
			else if (token.compare("M")==0)
			{
				maple++;
			}
		}
	
	cout << "Grass: " << grass << ", Algae: " << algae << ", Oak: " << oak << ", Pine: " << pine << ", Maple: " << maple << "\n\n";
}

void Ecosystem::PrintAnimalStatistics()
{
	int deer, rabbit, groundhog, salmon, fox, wolf, bear;
	deer = rabbit = groundhog = salmon = fox = wolf = bear = 0;
	
	deque<Animal*>::iterator it;
	for ( it=A.begin() ; it != A.end(); it++ ){
		if ((*it)->getName()=="Deer" ){
			deer++;
		}
		else if ((*it)->getName()=="Rabbit" ){
			rabbit++;
		}
		else if ((*it)->getName()=="Groundhog" ){
			groundhog++;
		}
		else if ((*it)->getName()=="Salmon" ){
			salmon++;
		}
		else if ( (*it)->getName()=="Fox" ){
			fox++;
		}
		else if ((*it)->getName()=="Wolf" ){
			wolf++;
		}
		else if ((*it)->getName()=="Bear" ){
			bear++;	
    	}
	}
	cout << "Number of Deers: " << deer << endl;
	cout << "Number of Rabbits: " << rabbit << endl;
	cout << "Number of Grounhogs: " << groundhog << endl;
	cout << "Number of Salmons: " << salmon << endl;
	cout << "Number of Foxes: " << fox << endl;
	cout << "Number of Wolves: " << wolf << endl;
	cout << "Number of Bears: " << bear << endl << endl;
}

void Ecosystem::PrintAnimalCharacteristics(){
	deque<Animal*>::iterator it;
	for ( it=A.begin() ; it != A.end(); it++ ){
		(*it)->printAll();
	}
}

void Ecosystem::countElements(int& water,int& hills,int& valley)
{
	int i, j;
	water = hills = valley = 0;
	for (i=0; i<terrainSize; i++)
		for (j=0; j<terrainSize; j++)
		{
			if (terrain[i][j].retT().compare("\"")==0)
				valley++;
			else if (terrain[i][j].retT().compare("#")==0)
				water++;
			else if (terrain[i][j].retT().compare("^")==0)
				hills++;
		}
}

bool Ecosystem::checkbounds(int i, int j) {	  		  /* returns false if we get out of board */
	return (0 <= i && i < terrainSize && 0 <= j && j < terrainSize);
}

void Ecosystem::PlaceAnimals(int nD,int nR,int nG,int nS,int nF,int nW,int nB){
	
	//cout<<"Placing Animals"<<endl;
	int x,y,j=0;
	while(j<nD){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT() =="\"" ){
			Deer* D;
			D=new Deer(x,y);
			A.push_front(D);
			j++;
		}
	}
	j=0;
	while(j<nR){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT()=="\"" ){
			Rabbit* R;
			R=new Rabbit(x,y);
			A.push_front(R);
			j++;
		}
	}
	j=0;
	while(j<nG){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT() == "\"" ){
			Groundhog* G;
			G=new Groundhog(x,y);
			A.push_front(G);
			j++;
		}
	}
	j=0;
	while(j<nS){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT()== "#" ){
			Salmon* S;
			S=new Salmon(x,y);
			A.push_front(S);
			j++;
		}
	}
	j=0;
	while(j<nF){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT() =="\"" ){
			Fox* F;
			F=new Fox(x,y);
			A.push_front(F);
			j++;
		}
	
	}
	j=0;
    while(j<nW){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT()!="#" ){
			Wolf* W;
			W=new Wolf(x,y);
			A.push_front(W);
			j++;
		}
	}
	j=0;
    while(j<nB){
		x=rand()%terrainSize;
		y=rand()%terrainSize;
		if( terrain[x][y].retT() =="^" ){
			Bear* B;
			B=new Bear(x,y);
			A.push_front(B);
			j++;
		}
	}
	//cout<<"Placing Animals Done"<<endl;
}


void Ecosystem::AnimalMovement(){
	deque<Animal*>::iterator it;
	for ( it= A.begin()  ; it !=  A.end() ; it++ ){
		(*it)->Move(terrain,terrainSize);
	}
}

void Ecosystem::AnimalEating(){
	//cout<<"Animal Eating"<<endl;
	deque<Animal*>::iterator it;
	for ( it = A.begin() ; it != A.end(); it++ ){
		(*it) -> Eat( terrain , A );
	}
	//cout<<"end of animal eating"<<endl;
}


void Ecosystem::RunEcosystem(){
	int hour;
	dayOfYear=1;
	PrintSystem();
	PrintAnimalCharacteristics();
	while ( dayOfYear<= days ){
		cout<<"Day Is:  "<<endl;
		cout<<dayOfYear<<endl;
		if ( dayOfYear%90==0 ){
			PrintSystem();
			PrintAnimalCharacteristics();
			ApplySeason(season);
			cout<<"Season is:  "<< season <<endl;
			PrintSystem();
			PrintAnimalCharacteristics();
		}
		DailyReset();
		for (hour=1;hour<24;hour++){
			AnimalMovement();
			AnimalEating();
		}
		CheckHunger();
		CheckDeadEntities();
		AnimalBreeding();
		PlantBreeding();
		dayOfYear++;
		PrintSystem();
		PrintAnimalCharacteristics();
	}
}
			
void Ecosystem::ApplySeason(string season_){

	if (season_=="winter"){
		season="spring";
		PlantGrowthPeriod=5;
 		AnimalGrowthPeriod=20;
		PlantBreedingRepPeriod=10;
		HerbivoresBreedingRepPeriod=12;
		CarnivoresBreedingRepPeriod=11;
		std::deque<Animal*>::iterator it;
		for ( it= A.begin()  ; it !=  A.end() ; it++ ){
			if ( (*it) -> getHibernates()== 1 ) (*it) -> changeInHibernation(0);
		}
	}
	else if (season_=="spring"){
		season="summer";
		PlantGrowthPeriod=10;
 		AnimalGrowthPeriod=30;
		PlantBreedingRepPeriod=10;
		HerbivoresBreedingRepPeriod=8;
		CarnivoresBreedingRepPeriod=9;
	}
	else if (season_=="summer"){
		season="automn";
		PlantGrowthPeriod=0;
 		AnimalGrowthPeriod=15;
		PlantBreedingRepPeriod=20;
		HerbivoresBreedingRepPeriod=5;
		CarnivoresBreedingRepPeriod=9;
	}
	else{
		season="winter";
		PlantGrowthPeriod=10;
 		AnimalGrowthPeriod=30;
		PlantBreedingRepPeriod=0;
		HerbivoresBreedingRepPeriod=18;
		CarnivoresBreedingRepPeriod=10;
		std::deque<Animal*>::iterator it;
		for ( it= A.begin()  ; it !=  A.end() ; it++ ){
			if ( (*it) -> getHibernates()== 1 ) (*it) -> changeInHibernation(1);
		}
	}
}

void Ecosystem::DailyReset(){
	
	int i, j;

	deque<Animal*>::iterator it;
	for (it=A.begin() ; it != A.end(); it++  ){
		(*it)->changeIsHungry(1);
		(*it)->changeEatenFood(0);
		if (dayOfYear%AnimalGrowthPeriod==0) (*it)->Raise();
	}

//	for (i=0; i<terrainSize; i++)
//		for (j=0; j<terrainSize; j++)
//		{
//			(terrain[i][j].getP())->Grow();
//		}	
}

void Ecosystem::AnimalBreeding(){
	//cout<<"Animal Breeding"<<endl;
	deque<Animal*>::iterator it;
	deque<Animal*> an2;
	if ( dayOfYear%HerbivoresBreedingRepPeriod==0   ){
		for ( it=A.begin() ; it != A.end(); it++ ){
			if ( (*it)->getName()=="Deer" && (*it)->getSpeed()==8   ){
				Deer* D;
				D=new Deer(1,(*it)->getX(),(*it)->getY());
				an2.push_front(D);
			}
			if ( (*it)->getName()=="Rabbit" && (*it)->getSpeed()==6 ){
				Rabbit* R;
				R=new Rabbit(1,(*it)->getX(),(*it)->getY());
				an2.push_front(R);
			}
			if ( (*it)->getName()=="Groundhog"  && (*it)->getSpeed()==5 ){
				Groundhog* G;
				G=new Groundhog(1,(*it)->getX(),(*it)->getY());
				an2.push_front(G);
			}
			if ( (*it)->getName()=="Salmon" && (*it)->getSpeed()==5 ){
				Salmon* S;
				S=new Salmon( (*it)->getX(),(*it)->getY());
					an2.push_front(S);
			}
		}
	}
	if ( dayOfYear%CarnivoresBreedingRepPeriod==0   ){
		for ( it=A.begin() ; it != A.end(); it++ ){
			if ( (*it)->getName()=="Fox"  && (*it)->getSpeed()==6 ){
				Fox* F;
				F=new Fox(1,(*it)->getX(),(*it)->getY());
				an2.push_front(F);
			}
			if ( (*it)->getName()=="Wolf" && (*it)->getSpeed()==8  ){
				Wolf* W;
				W=new Wolf(1,(*it)->getX(),(*it)->getY());
				an2.push_front(W);
			}
			if ( (*it)->getName()=="Bear" && (*it)->getSize()==10 ){
				Bear* B;
				B=new Bear(1,(*it)->getX(),(*it)->getY());
				an2.push_front(B);
			}
		}
	}
	for ( it=an2.begin() ; it != an2.end(); it++ ){
		A.push_front(*it);
	}
	an2.clear();
	//cout<<"end of Animal Breeding"<<endl;
}

void Ecosystem::CheckDeadEntities(){
	//cout<<"check dead entities"<<endl;
	int i,j;
	for (i=0;i<terrainSize;i++){
		for( j=0;j<terrainSize;j++ ){
			Plant *p;
			p = terrain[i][j].getP();
			//cout<<"got P"<<endl;
			if ( p!=NULL ){
				//cout<<"Null"<<endl;
				if ( p->getLife()==0 ){
					//cout<<"dead plant"<<endl;
					 terrain[i][j].deleteP();
					
				}
			}				
		}
	}
	deque<Animal*>::iterator it;
	for ( it=A.begin() ; it != A.end(); it++ ){
		if( (*it)->getIsAlive()==0 ) {
			 A.erase(it);
			 it=A.begin();
		}
	}
	//cout<<"end of check dead entities"<<endl;
}

void Ecosystem::CheckHunger(){
	//cout<<"check hunger"<<endl;
	deque<Animal*>::iterator it;
	for ( it=A.begin() ; it != A.end(); it++ ){
		if ((*it)->getName()=="Deer" ){
			if(  Herbivores* c = dynamic_cast<Herbivores*>(*it)    ){
				if        (    c->getEatenFood()  ==   c->getNeededFood()   ) c->changeHungerCount( 0 );
				else     c->changeHungerCount( c->getHungerCount() +1 );
			}
		}
		if ((*it)->getName()=="Rabbit" ){
			if(  Herbivores* c = dynamic_cast<Herbivores*>(*it)    ){
				if        (    c->getEatenFood()  ==   c->getNeededFood()   ) c->changeHungerCount( 0 );
				else     c->changeHungerCount(c->getHungerCount() +1 );
			}
		}
		if ((*it)->getName()=="Grounhog" ){
			if(  Herbivores* c = dynamic_cast<Herbivores*>(*it)    ){
				if        (    c->getEatenFood()  ==   c->getNeededFood()   ) c->changeHungerCount( 0 );
				else     c->changeHungerCount(c->getHungerCount() +1 );
			};
		}
		if ((*it)->getName()=="Salmon" ){
			if(  Herbivores* c = dynamic_cast<Herbivores*>(*it)    ){
				if   (    c->getEatenFood()  ==   c->getNeededFood()  )  c->changeHungerCount( 0 );
			}
		}
		if ( (*it)->getName()=="Fox" ){
			if        (    (*it)->getEatenFood()!=0  ) 	(*it)->changeHungerCount( 0 );
			else     (*it)->changeHungerCount( (*it)->getHungerCount() +1 );
		}
		if ((*it)->getName()=="Wolf" ){
			if        (  (*it)->getEatenFood()!=0    ) 	(*it)->changeHungerCount( 0 );
			else     (*it)->changeHungerCount( (*it)->getHungerCount() +1 );
		}
		if ((*it)->getName()=="Bear" ){
			if        (  (*it)->getEatenFood()!=0    ) 	(*it)->changeHungerCount( 0 );
			else     (*it)->changeHungerCount( (*it)->getHungerCount() +1 );
		}
		if ( (*it)->getHungerCount()==10 )  (*it)->changeIsAlive();
	}
	//cout<<"end of check hunger"<<endl;
}


