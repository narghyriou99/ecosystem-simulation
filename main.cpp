#include <iostream>
#include <cstdlib>
#include <ctime>
#include "EcoSystem.h"

using namespace std;

int main(int argc, char *argv[]) {
	srand((unsigned int)time(NULL));
	int size, dateOfYear,lakeSize,sumOfHills,daysOfSimulation;
	int *plantsArray, *animalsArray;
	plantsArray = new int[5];	//Array with sum of plants given by user
	animalsArray = new int[7];	//Array with sum of animals given by user 
	dateOfYear = 1;
	


	/*--------------------------------------------*/
	cout << "Give days of simulation: " << endl;
	cin >> daysOfSimulation;
	cout << "Give size of terrain: " << endl;
	cin >> size;
	cout << "Give size of Lake: " << endl;
	cin >> lakeSize;
	cout << "Give amount of hills: " << endl;
	cin >> sumOfHills;
	
	/*--------------------------------------------*/
	
	cout << "Give amount Grass: " << endl;
	cin >> plantsArray[0];
	cout << "Give amount Algae: " << endl;
	cin >> plantsArray[1];
	cout << "Give amount Oak: " << endl;
	cin >> plantsArray[2];
	cout << "Give amount Pine: " << endl;
	cin >> plantsArray[3];
	cout << "Give amount Mapple: " << endl;
	cin >> plantsArray[4];

	/*--------------------------------------------*/
	cout << "Give amount of Deer: " << endl;
	cin >> animalsArray[0];
	cout << "Give amount of Rabbit: " << endl;
	cin >> animalsArray[1];
	cout << "Give amount of Groundhog: " << endl;
	cin >> animalsArray[2];
	cout << "Give amount of Salmon: " << endl;
	cin >> animalsArray[3];
	cout << "Give amount of Fox: " << endl;
	cin >> animalsArray[4];
	cout << "Give amount of Wolf: " << endl;
	cin >> animalsArray[5];
	cout << "Give amount of Bear: " << endl;
	cin >> animalsArray[6];
	/*--------------------------------------------*/


	
	

	
	List *animalList=NULL;
	Ecosystem *ecosystem = new Ecosystem(size,dateOfYear,lakeSize,sumOfHills,plantsArray);		//Create an ecosystem
	animalList=ecosystem->Placeanimals(animalsArray);			//Return list of animals
	ecosystem->RunEcosystem(animalList, daysOfSimulation);



	delete[]animalsArray;
	delete[]plantsArray;
	delete ecosystem;
	delete animalList;
	return 0;
}