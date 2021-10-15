#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "EcoSystem.h"


using namespace std;

Ecosystem::Ecosystem(int terrainsize,int currentDate, int lakeSize, int sumOfHills, int *&plantArray)
{
	dayOfYear = currentDate;
	terrain = new Terrain(terrainsize,lakeSize,sumOfHills,plantArray);
	growthPeriod = new int[2];
	breedingRepPeriod = new int[3];
	cout << "Constructing an Ecosystem" << endl;
}

Ecosystem::~Ecosystem()
{
	delete terrain;
	delete []growthPeriod;
	delete []breedingRepPeriod;
	cout << "Deleting an Ecosystem" << endl;
}

List * Ecosystem::Placeanimals(int *& animalarray)
{
	return terrain->PlaceAnimals(animalarray);
}


void Ecosystem::RunEcosystem(List *list,int daysOfSimulation)
{

	PrintPlantStatistics();
	PrintSystem(list);
	for (dayOfYear; dayOfYear <= daysOfSimulation; dayOfYear++) {
		for (int hour = 1; hour <= 24; hour++) {
			terrain->AnimalMovement(list);		
			terrain->AnimalEating(list);
			
		}

		
		grow(list);
		CheckHunger(list);
		DeadEntities(list);
		DailyReset(list,dayOfYear);
		if (dayOfYear%90 == 0) {		//Change season
			ApplySeason(list);
			PrintPlantStatistics();
			PrintSystem(list);
		}
		
	}
	PrintPlantStatistics();
	PrintSystem(list);
}

void Ecosystem::ApplySeason(List *list)
{
	Node *cur = list->getFirst();
	season++;
	if (season == 4) {
		season = 0;
	}
	switch (season)
	{
	case(0):		//Winter
		growthPeriod[0] = 10;
		growthPeriod[1] = 30;
		breedingRepPeriod[0] = -1;
		breedingRepPeriod[1] = 18;
		breedingRepPeriod[2] = 10;
		cur = list->getFirst();
		if (cur != NULL) {
			while (cur->next != NULL) {	//Hibernation
				if (cur->animal->GetHibernates() == 1) {
					cout << "good night " << cur->animal->GetName() << endl;
					cur->animal->SetInHibernation(1);
				}
				cur = cur->next;
			}
		}
		
		break;
	case(1):		//Spring
		growthPeriod[0] = 5;
		growthPeriod[1] = 20;
		breedingRepPeriod[0] = 10;
		breedingRepPeriod[1] = 12;
		breedingRepPeriod[2] = 11;
		cur = list->getFirst();
		if (cur != NULL) {
			while (cur->next != NULL) {		//Good morning!
				if (cur->animal->GetInHibernation() == 1 && cur->animal->GetHibernates() == 1) {
					cout << "good morning " << cur->animal->GetName() << endl;
					cur->animal->SetInHibernation(0);
				}
				cur = cur->next;
			}
		}
		break;
	case(2):		//Summer
		growthPeriod[0] = 10;
		growthPeriod[1] = 30;
		breedingRepPeriod[0] = 10;
		breedingRepPeriod[1] = 8;
		breedingRepPeriod[2] = 9;
		break;
	case(3):		//Autumn
		growthPeriod[0] = -1;
		growthPeriod[1] = 15;
		breedingRepPeriod[0] = 20;
		breedingRepPeriod[1] = 5;
		breedingRepPeriod[2] = 9;
		
		break;

	}
}

void Ecosystem::DailyReset(List *list,int currentDay)
{
	Node *cur = list->getFirst();
	if (cur != NULL) {
		while (cur->next != NULL) {
			if (cur->animal->GetToken() == 'C') {
				if (cur->animal->GetEatenFood() == 0) {
					cur->animal->SetHungerCount(cur->animal->GetHungerCount() + 1); //days he hasnt eaten++
				}
				else {
					cur->animal->SetHungerCount(0);
				}
				cur->animal->SetIsHungry(1);
				cur->animal->SetEatenFood(0);
			}
			else {
				if (cur->animal->GetEatenFood() >= cur->animal->GetNeededFood()) {
					if (cur->animal->GetDaysFull() < 7) { //still full
						cur->animal->SetIsHungry(0);
						cur->animal->SetDaysFull(cur->animal->GetDaysFull() + 1);
					}
					else {
						cur->animal->SetDaysFull(0);
						cur->animal->SetEatenFood(0);
						cur->animal->SetIsHungry(1);
						cur->animal->SetHungerCount(0);
					}

				}
				else {
					if (cur->animal->GetEatenFood() == 0) {
						cur->animal->SetHungerCount(cur->animal->GetHungerCount() + 1);
						cur->animal->SetIsHungry(1);
					}
					else {
						cur->animal->SetEatenFood(0);
						cur->animal->SetIsHungry(1);
						cur->animal->SetHungerCount(0);
					}
				}

			}

			cur = cur->next;
		}
	}

}

void Ecosystem::CheckHunger(List * list)
{
	Node *cur = list->getFirst();
	if (cur != NULL) {
		while (cur->next != NULL) {
			if (cur->animal->GetHungerCount() == 10) {
				cur->animal->SetIsAlive(0);
			}
			cur = cur->next;
		}
	}
}

void Ecosystem::RemoveEntitie(List *list,int key)
{
	Node *cur = list->getFirst();
	Node *temp = cur;
	Node *prev = list->getFirst();
	if (temp != NULL )
	{
		//if (temp->animal->GetIsAlive() == key && temp->animal->GetInHibernation() == 0) {
			list->SetFirst(temp->next);   // Changed head 
			delete temp;               // free old head 
			list->dec();
			return;
		//}
	}
	while (temp != NULL )
	{
		//if (temp->animal->GetIsAlive() != key) {
			prev = temp;
			temp = temp->next;
		//}
	}
	if (temp == NULL) return;
	prev->next = temp->next;
	delete temp;  
	list->dec();
}

void Ecosystem::DeadEntities(List * list)
{
	for (int i = 0; i <= list->GetN(); i++) {
		RemoveEntitie(list, 0);
	}

}

void Ecosystem::grow(List * list)
{
	
	Node *cur = list->getFirst();
	if (cur != NULL) {
		if (growthPeriod[1] % dayOfYear == 0) {
			while (cur->next != NULL) {
				if (strcmp(cur->animal->GetName(), "bear") == 0) {
					if (cur->animal->GetAttack() < 10) {			//Attack
						cur->animal->SetAttack(cur->animal->GetAttack() + 2);
					}
					if (cur->animal->GetDefence() < 10) {			//Defence
						cur->animal->SetDefence(cur->animal->GetDefence() + 2);
					}
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 2);
					}
					if (cur->animal->GetNeededFood() < 10) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 2);
					}
				}
				if (strcmp(cur->animal->GetName(), "wolf") == 0) {
					if (cur->animal->GetAttack() < 8) {			//Attack
						cur->animal->SetAttack(cur->animal->GetAttack() + 2);
					}
					if (cur->animal->GetDefence() < 6) {			//Defence
						cur->animal->SetDefence(cur->animal->GetDefence() + 2);
					}
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 1);
					}
					if (cur->animal->GetSpeed() < 8) {			//Speed
						cur->animal->SetSpeed(cur->animal->GetSpeed() + 2);
					}
					if (cur->animal->GetNeededFood() < 8) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 2);
					}
				}
				if (strcmp(cur->animal->GetName(), "fox") == 0) {
					if (cur->animal->GetAttack() < 5) {			//Attack
						cur->animal->SetAttack(cur->animal->GetAttack() + 1);
					}
					if (cur->animal->GetDefence() < 5) {			//Defence
						cur->animal->SetDefence(cur->animal->GetDefence() + 1);
					}
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 1);
					}
					if (cur->animal->GetSpeed() < 6) {			//Speed
						cur->animal->SetSpeed(cur->animal->GetSpeed() + 1);
					}
					if (cur->animal->GetNeededFood() < 6) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 1);
					}
				}
				if (strcmp(cur->animal->GetName(), "groundhog") == 0) {
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 1);
					}
					if (cur->animal->GetSpeed() < 5) {			//Speed
						cur->animal->SetSpeed(cur->animal->GetSpeed() + 1);
					}
					if (cur->animal->GetNeededFood() < 5) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 1);
					}
				}
				if (strcmp(cur->animal->GetName(), "rabbit") == 0) {
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 1);
					}
					if (cur->animal->GetSpeed() < 6) {			//Speed
						cur->animal->SetSpeed(cur->animal->GetSpeed() + 2);
					}
					if (cur->animal->GetNeededFood() < 4) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 2);
					}
				}
				if (strcmp(cur->animal->GetName(), "deer") == 0) {
					if (cur->animal->GetCurrentSize() < cur->animal->GetMaxSize()) {	//Size
						cur->animal->SetCurrentSize(cur->animal->GetCurrentSize() + 1);
					}
					if (cur->animal->GetSpeed() < 8) {			//Speed
						cur->animal->SetSpeed(cur->animal->GetSpeed() + 2);
					}
					if (cur->animal->GetNeededFood() < 8) {							//Needed food
						cur->animal->SetNeededFood(cur->animal->GetNeededFood() + 2);
					}
				}
				cur = cur->next;
			}

		}
	}
	
	if (growthPeriod[0] % dayOfYear == 0) {
		for (int i = 0; i < terrain->GetTerrainSize(); i++) {
			for (int j = 0; j < terrain->GetTerrainSize(); j++) {
				if (GetTerrainPlant(i, j) != NULL) {
					Plant * temp = GetTerrainPlant(i, j);
					if (temp->GetToken() == 'G') {
						int result = temp->CheckIfSick();
						if (result == 0) {
							delete temp;
							terrain->setNullPlant(i, j);
						}
					}
					else if (temp->GetToken() == 'A') {
						int result = temp->CheckIfSick();
						if (result == 0) {
							delete temp;
							terrain->setNullPlant(i, j);
						}
					}
					else if (temp->GetToken() == 'O') {
						int result = temp->CheckIfSick();
						if (result == 0) {
							delete temp;
							terrain->setNullPlant(i, j);
						}
					}
					else if (temp->GetToken() == 'P') {
						int result = temp->CheckIfSick();
						if (result == 0) {
							delete temp;
							terrain->setNullPlant(i, j); 
						}
					}
					else if (temp->GetToken() == 'M') {
						int result = temp->CheckIfSick();
						if (result == 0) {
							delete temp;
							terrain->setNullPlant(i, j);
						}
					}
				}
			}
		}
	}
	
}

Plant * Ecosystem::GetTerrainPlant(int i, int j)
{
	return terrain->GetPlant(i,j);
}

void Ecosystem::PrintPlantStatistics()
{
	int ar[5]; // 0-grass 1-algae 2-oak 3-pine 4-maple
	for (int k = 0; k < 5; k++) {
		ar[k] = 0;
	}
	for (int i = 0; i < terrain->GetTerrainSize(); i++) {
		for (int j = 0; j < terrain->GetTerrainSize(); j++) {
			if (GetTerrainPlant(i, j) != NULL) {
				Plant * temp = GetTerrainPlant(i, j);
				if (temp->GetToken() == 'G') {
					ar[0]++;
				}
				else if (temp->GetToken() == 'A') {
					ar[1]++;
				}
				else if (temp->GetToken() == 'O') {
					ar[2]++;
				}
				else if (temp->GetToken() == 'P') {
					ar[3]++;
				}
				else if (temp->GetToken() == 'M') {
					ar[4]++;
				}
			}
		}
	}
	cout << "---------------" << endl;
	cout << "Grass :" << ar[0] << " Algrae :" << ar[1] << " Oak :" << ar[2] << " Pine :" << ar[3] << " Maple :" << ar[4] << endl;
	cout << "---------------" << endl;
}

void Ecosystem::PrintSystem(List *list)
{
	Node *cur = list->getFirst();
	int plantCounter = 0, animalCounter = 0, herbCounter = 0,carnCounter=0;
	cout << "Current day of Simulation: " << dayOfYear << endl;		//Cur day of year
	for (int i = 0; i < terrain->GetTerrainSize(); i++) {			
		for (int j = 0; j < terrain->GetTerrainSize(); j++) {
			if (terrain->GetPlant(i,j) != NULL) {
				plantCounter++;
			}
		}
	}
	if (cur != NULL) {
		while (cur->next != NULL) {
			if (cur->animal->GetToken() == 'H') {
				herbCounter++;
			}
			else if (cur->animal->GetToken() == 'C') {
				carnCounter++;
			}
			animalCounter++;
			cur = cur->next;
		}
	}

	for (int i = 0; i < terrain->GetTerrainSize(); i++) {			//Print terrain 
		for (int j = 0; j < terrain->GetTerrainSize(); j++) {
			if (terrain->GetPlant(i, j) != NULL) {
				cout << terrain->GetPlant(i, j)->GetToken() << " ";
			}
			else {
				cout << terrain->getTypeOfEnvironment(i, j) << " ";
			}
		}
		cout << endl;
	}
	cout << "Sum of Plants: " << plantCounter << endl;
	cout << "Sum of Herbivores: " << herbCounter << endl;
	cout << "Sum of Carnivores: " << carnCounter << endl;
	cout << "Sum of Animals: " << animalCounter << endl;

}
	



Terrain::Terrain(int size,int lakeSize, int sumOfHills, int *&PlantArray)
{
	terrainSize = size;
	tile = new Tile**[terrainSize];
	for (int i = 0; i < terrainSize; i++) {
		tile[i] = new Tile*[terrainSize];
		for (int j = 0; j < terrainSize; j++) {
			tile[i][j] = new Tile();
		}
	}
	MapGenerator(lakeSize,sumOfHills);
	PlacePlants(PlantArray);
	printTerrain();
	cout << "Creating Terrain" << endl;
}

Terrain::~Terrain()
{
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j < terrainSize; j++) {
			delete tile[i][j]->getPlantPtr();
			delete tile[i][j];
		}
		delete[]tile[i];
	}
	delete[]tile;

	cout << "Deleting Terrain" << endl;
}




void Terrain::MapGenerator(int lakeSize, int sumOfHills)
{
	
	GenerateRiver();
	GenerateLake(lakeSize);
	GenerateHills(sumOfHills);
	GenerateMeadow();
}

void Terrain::GenerateRiver()
{
	int startOfRiver = rand() % (terrainSize - 10) + 6;
	int N = terrainSize;
	int choice;
	int row = 0;
	int direction;
	tile[startOfRiver][row]->setTypeOfEnvironment('#');
	while(row<N-1 && startOfRiver<N-1 && startOfRiver>0) {
		choice = rand() % 100 + 1;
		if (choice >= 1 && choice <= 30) {
			direction = rand() % 4 + 1;
			switch (direction)
			{
			case 1:		//1 down 
				startOfRiver++;
				row++;
				tile[startOfRiver][row]->setTypeOfEnvironment('#');
				break;
			case 2:		//2 down 
				startOfRiver++;
				row++;
				tile[startOfRiver][row]->setTypeOfEnvironment('#');
				startOfRiver++;
				row++;
				if (row < N  && startOfRiver < N && startOfRiver>=0) {
					tile[startOfRiver][row]->setTypeOfEnvironment('#');
				}
				break;
			case 3:		// 1 up
				startOfRiver--;
				row++;
				tile[startOfRiver][row]->setTypeOfEnvironment('#');
				break;
			case 4:    // 2 up
				startOfRiver--;
				row++;
				tile[startOfRiver][row]->setTypeOfEnvironment('#');
				startOfRiver++;
				row++;
				if (row < N  && startOfRiver < N && startOfRiver >= 0) {
					tile[startOfRiver][row]->setTypeOfEnvironment('#');
				}
				break;	
			}
		}
		else {
			row++;
			tile[startOfRiver][row]->setTypeOfEnvironment('#');
		}

		
	}
}

void Terrain::GenerateLake(int lakeSize)
{
	int i, j;
	int N = terrainSize;
	int x = 0;
	int y = 0;
	x = rand() % terrainSize;
	y = rand() % terrainSize;
	while (x + lakeSize > N || y + lakeSize > N) {
		cout << "error" << endl;
		x = rand() % terrainSize;
		y = rand() % terrainSize;
	}
	
		for (i = x; i < x + lakeSize; i++) {
			for (j = y; j < y + lakeSize; j++) {
					tile[i][j]->setTypeOfEnvironment('#');
			}
		}
}

void Terrain::GenerateHills(int sumOfHills)
{
	int x, y,hillSize;
	for (int sum = 0; sum < sumOfHills; sum++) {
		x = rand() % terrainSize;
		y = rand() % terrainSize;
		hillSize = rand() % 3 + 2;
		while (x + hillSize > terrainSize || y + hillSize> terrainSize) {
			cout << "error" << endl;
			x = rand() % terrainSize;
			y = rand() % terrainSize;
		}
		
		for (int i = x; i < x + hillSize; i++) {
			for (int j = y; j < y + hillSize; j++){
				if (tile[i][j]->getTypeOfEnvironment() != '#') {
					tile[i][j]->setTypeOfEnvironment('^');
				}
				
			}
		}
	}

}

void Terrain::GenerateMeadow()
{
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j <terrainSize; j++) {
			if (tile[i][j]->getTypeOfEnvironment() == '0') {
				tile[i][j]->setTypeOfEnvironment('"');
			}
		}
	}
}

void Terrain::PlacePlants(int *&plantArray)
{
	int choise = 0;
	int choisePosition = 0;
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j < terrainSize; j++) {
			switch(tile[i][j]->getTypeOfEnvironment()){
				case '#':	//Water	
					choise = rand() % 2;
					if (choise == 1) {
						if (plantArray[1] > 0) {
							tile[i][j]->setPlantPtr(new Algae("algae", i, j));
							plantArray[1]--;
						}
					}
					break;
				case '^':	//Hill
					choisePosition = rand() % 2;
					if (choisePosition == 1) {
						choise = rand() % 2;
						if (choise == 0) {	//Mapple
							if (plantArray[4] > 0) {
								tile[i][j]->setPlantPtr(new Maple("mapple", i, j));
								plantArray[4]--;
							}
						}
						else {		//Pine
							if (plantArray[3] > 0) {
								tile[i][j]->setPlantPtr(new Pine("pine", i, j));
								plantArray[3]--;
							}
						}
					}
					break; 
				case '"':	//Meadow
					choisePosition = rand() % 2;
					if (choisePosition == 1) {
						choise = rand() % 100 + 1;
						if (choise <=70) {	//Grass
							if (plantArray[0] > 0) {
								tile[i][j]->setPlantPtr(new Grass("grass", i, j));
								plantArray[0]--;
							}
						}
						else {		//Oak
							if (plantArray[2] > 0) {
								tile[i][j]->setPlantPtr(new Oak("oak", i, j));
								plantArray[2]--;
								
							}
						}
					}
					break;
			}
			
		}
	}
}

List* Terrain::PlaceAnimals(int *&animalArray)
 {
	List *animalList=new List();	//List with all the animals 
	int choice = -1;
	int choicePosition = -1;
	int value = 1;
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j < terrainSize; j++) {
			switch (tile[i][j]->getTypeOfEnvironment()) {
			case '#':	//Water
				choicePosition = rand() % 2;
				if (choicePosition == 1) {
					if (animalArray[3] > 0) {
						animalList->push(new Salmon("salmon",i,j),value);
						animalArray[3] -= 1;
						value++;
					}
				}
				break;
			case '^':	//Hill
				choicePosition = rand() % 2;
				if (choicePosition == 1) {
					choice = rand() % 2;
					if (choice == 1) {
						if (animalArray[5] > 0) {
							animalList->push(new Bear("bear",i,j,1), value);
							animalArray[5] -= 1;
							value++;
						}
					}
					else {
						if (animalArray[6] > 0) {
							animalList->push(new Wolf("wolf",i,j,1),value);
							animalArray[6] -= 1;
							value++;
						}
					}
				}
				break;
			case '"':	//Meadow
				choicePosition = rand() % 2;
				if (choicePosition == 1) {
					switch (choice = rand() % 5 + 1) {
					case(1):
						if (animalArray[0] > 0) {
							animalList->push(new Deer("deer",i,j,1),value);
							animalArray[0] -= 1;
							value++;
						}
						break;
					case(2):
						if (animalArray[1] > 0) {
							animalList->push(new Rabbit("rabbit",i,j,1),value);
							animalArray[1] -= 1;
							value++;
						}
						break;
					case(3):
						if (animalArray[2] > 0) {
							animalList->push(new Groundhog("groundhog",i,j,1),value);
							animalArray[2] -= 1;
							value++;
						}
						break;
					case(4):
						if (animalArray[4] > 0) {
							animalList->push(new Fox("fox",i,j,1),value);
							animalArray[4] -= 1;
							value++;
						}
						break;
					case(5):
						if (animalArray[6] > 0) {
							animalList->push(new Wolf("wolf",i,j,1),value);
							animalArray[6] -= 1;
							value++;
						}
						break;
					}
			
				}			
				break;
			}

		}
	}
	return animalList;
}


void Terrain::printTerrain()
{
	for (int i = 0; i < terrainSize; i++) {
		for (int j = 0; j < terrainSize; j++) {
			cout << tile[i][j]->getTypeOfEnvironment() << " ";
		}
		cout << endl;
	}
}

int Terrain::GetTerrainSize()
{
	return terrainSize;
}

Plant * Terrain::GetPlant(int i, int j)
{
	return tile[i][j]->getPlantPtr();
}

int Terrain::AnimalMovement(List * list)
{
	Node *cur = list->getFirst();
	int flag;
	if (cur != NULL) {
		while (cur->next != NULL) {
			if ((strcmp(cur->animal->GetName(), "bear")) == 0 || (strcmp(cur->animal->GetName(), "wolf")) == 0 || (strcmp(cur->animal->GetName(), "fox")) == 0 || (strcmp(cur->animal->GetName(), "deer")) == 0) {
				int choice; // direction
				flag = 0;
				while (flag == 0) {
					choice = rand() % 4 + 1;
					switch (choice) {
					case(1): //up
						if (cur->animal->getX() >= 1) {
							cur->animal->setX(cur->animal->getX() - 1);
							flag = 1;
						}
						break;
					case(2):	//down
						if (cur->animal->getX() < terrainSize - 1) {
							cur->animal->setX(cur->animal->getX() + 1);
							flag = 1;
						}
						break;
					case(3):	//right
						if (cur->animal->getY() < terrainSize - 1) {
							cur->animal->setY(cur->animal->getY() + 1);
							flag = 1;
						}
						break;
					case(4):
						if (cur->animal->getY() >= 1) {
							cur->animal->setY(cur->animal->getY() - 1);
							flag = 1;
						}
						break;
					}
				}
			}
			else if ((strcmp(cur->animal->GetName(), "rabbit")) == 0) {
				int choice; // direction
				flag = 0;
				while (flag == 0) {
					choice = rand() % 4 + 1;
					switch (choice) {
					case(1): //up
						if (cur->animal->getX() >= 1) {
							if (tile[cur->animal->getX() - 1][cur->animal->getY()]->getTypeOfEnvironment() != '^') {
								cur->animal->setX(cur->animal->getX() - 1);
								flag = 1;
							}
						}
						break;
					case(2):	//down
						if (cur->animal->getX() < terrainSize - 1) {
							if (tile[cur->animal->getX() + 1][cur->animal->getY()]->getTypeOfEnvironment() != '^') {
								cur->animal->setX(cur->animal->getX() + 1);
								flag = 1;
							}
						}
						break;
					case(3):	//right
						if (cur->animal->getY() < terrainSize - 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() + 1]->getTypeOfEnvironment() != '^') {
								cur->animal->setY(cur->animal->getY() + 1);
								flag = 1;
							}
						}
						break;
					case(4):
						if (cur->animal->getY() >= 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() - 1]->getTypeOfEnvironment() != '^') {
								cur->animal->setY(cur->animal->getY() - 1);
								flag = 1;
							}
						}
						break;
					}
				}

			}
			else if ((strcmp(cur->animal->GetName(), "goundhog")) == 0) {
				int choice; // direction
				flag = 0;
				while (flag == 0) {
					choice = rand() % 4 + 1;
					switch (choice) {
					case(1): //up
						if (cur->animal->getX() >= 1) {
							if (tile[cur->animal->getX() - 1][cur->animal->getY()]->getTypeOfEnvironment() != '#') {
								cur->animal->setX(cur->animal->getX() - 1);
								flag = 1;
							}
						}
						break;
					case(2):	//down
						if (cur->animal->getX() < terrainSize - 1) {
							if (tile[cur->animal->getX() + 1][cur->animal->getY()]->getTypeOfEnvironment() != '#') {
								cur->animal->setX(cur->animal->getX() + 1);
								flag = 1;
							}
						}
						break;
					case(3):	//right
						if (cur->animal->getY() < terrainSize - 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() + 1]->getTypeOfEnvironment() != '#') {
								cur->animal->setY(cur->animal->getY() + 1);
								flag = 1;
							}
						}
						break;
					case(4):
						if (cur->animal->getY() >= 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() - 1]->getTypeOfEnvironment() != '#') {
								cur->animal->setY(cur->animal->getY() - 1);
								flag = 1;
							}
						}
						break;
					}
				}

			}
			else if ((strcmp(cur->animal->GetName(), "salmon")) == 0) {
				int choice; // direction
				flag = 1;
				while (flag == 0) {
					choice = rand() % 4 + 1;
					switch (choice) {
					case(1): //up
						if (cur->animal->getX() >= 1) {
							if (tile[cur->animal->getX() - 1][cur->animal->getY()]->getTypeOfEnvironment() == '#') {
								cur->animal->setX(cur->animal->getX() - 1);
								flag = 1;
							}
						}
						break;
					case(2):	//down
						if (cur->animal->getX() < terrainSize - 1) {
							if (tile[cur->animal->getX() + 1][cur->animal->getY()]->getTypeOfEnvironment() == '#') {
								cur->animal->setX(cur->animal->getX() + 1);
								flag = 1;
							}
						}
						break;
					case(3):	//right
						if (cur->animal->getY() < terrainSize - 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() + 1]->getTypeOfEnvironment() == '#') {
								cur->animal->setY(cur->animal->getY() + 1);
								flag = 1;
							}
						}
						break;
					case(4):
						if (cur->animal->getY() >= 1) {
							if (tile[cur->animal->getX()][cur->animal->getY() - 1]->getTypeOfEnvironment() == '#') {
								cur->animal->setY(cur->animal->getY() - 1);
								flag = 1;
							}
						}
						break;
					}
				}
			}


			cur = cur->next;
		}
	}
	return 0;
}

void Terrain::AnimalEating(List * list)
{
	Node *cur = list->getFirst();
	Plant *temp = NULL;
	if (cur != NULL) {
		while (cur->next != NULL) {
			//if (cur->animal->GetIsHungry() == 1) {
			int eaten = 0;
			if (cur->animal->GetToken() == 'H') {
				temp = tile[cur->animal->getX()][cur->animal->getY()]->getPlantPtr();
				if (temp != NULL) {
					if ((strcmp(cur->animal->GetName(), "deer")) == 0) {
						if (temp->GetToken() == 'G') {
							if (temp->GetLife() >= cur->animal->GetEatCount()) {
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + cur->animal->GetEatCount());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
							}
							else {
								cur->animal->SetEatenFood(temp->GetLife() + cur->animal->GetEatenFood());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);

							}
						}
						else  if (temp->GetToken() != 'A') {
							if ((cur->animal->GetCurrentSize() + 4) >= temp->GetSize()) {
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + eaten);
							}
						}
					}
					else if ((strcmp(cur->animal->GetName(), "salmon")) == 0) {
						if (temp->GetToken() == 'A') {
							if (temp->GetLife() >= cur->animal->GetEatCount()) {
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + cur->animal->GetEatCount());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
							}
							else {
								cur->animal->SetEatenFood(temp->GetLife() + cur->animal->GetEatenFood());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);

							}
						}
					}
					else if (strcmp(cur->animal->GetName(), "groundhog") == 0) {
						//if (cur->animal->GetInHibernation() == 0) {		//
						if (temp->GetToken() == 'G') {
							if (temp->GetLife() >= cur->animal->GetEatCount()) {
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + cur->animal->GetEatCount());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
							}
							else {
								cur->animal->SetEatenFood(temp->GetLife() + cur->animal->GetEatenFood());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);

							}
						}
						else  if (temp->GetToken() != 'A') {
							if ((cur->animal->GetCurrentSize() * 3) >= temp->GetSize()) {
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + eaten);
							}
						}
						//}
					}
					else if (strcmp(cur->animal->GetName(), "rabbit") == 0) {
						if (temp->GetToken() == 'G') {
							if (temp->GetLife() >= cur->animal->GetEatCount()) {
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + cur->animal->GetEatCount());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
							}
							else {
								cur->animal->SetEatenFood(temp->GetLife() + cur->animal->GetEatenFood());
								temp->LoseLife(cur->animal->GetEatCount(), eaten);

							}
						}
						else  if (temp->GetToken() != 'A') {
							if ((cur->animal->GetCurrentSize()) >= temp->GetSize()) {
								temp->LoseLife(cur->animal->GetEatCount(), eaten);
								cur->animal->SetEatenFood(cur->animal->GetEatenFood() + eaten);
							}
						}

					}


				}
			}
			//}
			cur = cur->next;
		}
	}
}

char Terrain::getTypeOfEnvironment(int i,int j)
{
	return tile[i][j]->getTypeOfEnvironment();
}

void Terrain::setNullPlant(int i, int j)
{
	tile[i][j]->setPlantPtr(NULL);
}

Tile::Tile():typeOfEnvironment('0')
{
	
	//cout << "Creating a Tile" << endl;
}

Tile::~Tile()
{
	//cout << "Deleting a tile" << endl;
}

void Tile::setTypeOfEnvironment(char type)
{
	typeOfEnvironment = type;
}

char Tile::getTypeOfEnvironment()
{
	return typeOfEnvironment;
}

void Tile::setPlantPtr(Plant * p)
{
	plant = p;
}

Plant * Tile::getPlantPtr()
{
	return plant;
}
