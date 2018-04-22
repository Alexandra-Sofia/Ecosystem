// File: main.cpp

#include <iostream>
#include <string>
#include <ctime>                //for function time
#include "ecosystem.h"

using namespace std;

int main (void)
{
	srand( time( NULL ) );
	cout << "Insert days of simulation: ";
	
	//cin >>
	
	Ecosystem eco(20);
	eco.MapGenerator();
	eco.RunEcosystem();
	//eco.PrintSystem();
	
	
	
//	cout << "\n\nEverything ok\n\n";


	return 0;
}

