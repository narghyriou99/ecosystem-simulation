#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Plants.h"


using namespace std;



Plant::Plant()
{
	cout << "A plant was just created" << endl;
}

Plant::~Plant()
{
	delete[] name;
	cout << "A plant has just died" << endl;
}

char Plant::GetToken()
{
	return token;
}



Seeded::Seeded()
{
	cout << "The plant have seed" << endl;
}

Seeded::~Seeded()
{
	cout << "Destroying a plant with seed" << endl;
}

int Seeded::LoseLife(int amount, int &eaten)
{
	if (seed > 0) {
		if (seed - amount > 0) { // if there is enough
			seed -= amount;
			eaten = amount;
			return 1;
		}
		else {					//eat all the seeds and the rest from the life
			seed -= amount;
			if (life + seed > 0) {
				life += seed;
				foliage += seed;
				seed = 0;
				eaten = amount;
				return 1;
			}
			else {
				eaten = life;
				life = 0;
				return 0;
			}
		}
	}
	else {						//only from life
		if (life - amount > 0) {
			foliage -= amount;
			life -= amount;
			eaten = amount;
			return 1;
		}
		else {
			eaten = life;
			life = 0;
			return 0;

		}
		
		
	}
}

int Seeded::CheckIfSick()
{
	float choice = float((rand() % 100 + 1) / 100.0);
	if (choice <= illnessProb) { // is sick
		if (foliage - lifeFactor >= 0) {
			foliage -= lifeFactor;
		}
		else {
			foliage = 0;
		}
		if ((seed - lifeFactor * 2 )>= 0) {
			seed -= foliage * 2;
		}
		else {
			seed = 0;
		}
		if (foliage <= lifeFactor) {
			if (size != 1) {
				size--;
			}
			else {
				size = 0;
				return 0;		//dead
			}
		}
		return 1;

	}
	else {  //is healthy and has grown
		foliage += lifeFactor;
		seed += foliage * 2;

		if (foliage >= lifeFactor) {
			size++;
		}
		return 1;
	}
}

int Seeded::checkifBreeded()
{
	double choice = (rand() % 100 + 1) / 100;
	if (choice <= breedingProb) {
		return 1;
	}
	else {
		return 0;
	}
}

int Seeded::GetSize()
{
	return size;
}

Seedless::Seedless()
{
	cout << "The plant do not have seed" << endl;
}

Seedless::~Seedless()
{
	cout << "Destroying a plant with no seed" << endl;
}

int Seedless::LoseLife(int amount, int &eaten)
{
	if (life - amount > 0) {
		life -= amount;
		return 1;
	}
	else {
		life = 0;
		return 0;
	}
}

int Seedless::CheckIfSick() 
{
	int temp;
	int result;
	float choice = float((rand() % 100 + 1) / 100.0);
	if (choice <=illnessProb) {
		result = LoseLife(lifeFactor, temp); // 1 - Alive  0 - Dead
		return result;
	}
	else {								//Isnt sick
		life += lifeFactor;
		return 2;
	}
}

int Seedless::CheckIfBreeded()
{
	double choice = (rand() % 100 + 1) / 100;
	if (choice <= breedingProb) {
		return 1;
	}
	else {
		return 0;
	}

}

int Seedless::GetLife()
{
	return life;
}

int Seedless::GetLifeFactor()
{
	return lifeFactor;
}

void Seedless::SetLife(const int & n)
{
	life = n;
}

void Seedless::SetLifeFactor(const int & n)
{
	lifeFactor = n;
}



Oak::Oak(const char *n,int x,int y) 
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	/*----------------------*/
	token = 'O';
	size = 5;
	foliage = 30;
	seed = 15;
	breedingProb = 0.2;
	illnessProb = 0.2;
	lifeFactor = 15;
	life = seed + foliage;
	
}

Oak::~Oak()
{
	
	cout << "Destroying an Oak" << endl;
}

Pine::Pine(const char *n, int x, int y)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	/*----------------------*/
	token = 'P';
	size = 5;
	foliage = 40;
	seed = 20;
	breedingProb = 0.15;
	illnessProb = 0.15;
	lifeFactor = 20;
	life = seed + foliage;
}

Pine::~Pine()
{
	cout << "Destroying a Pine" << endl;
}

Maple::Maple(const char *n, int x, int y)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	/*----------------------*/
	token = 'M';
	size = 2;
	foliage = 20;
	seed = 10;
	breedingProb = 0.05;
	illnessProb = 0.05;
	lifeFactor = 10;
	life = seed + foliage;
}

Maple::~Maple()
{
	cout << "Destroying a Maple" << endl;
}

Grass::Grass(const char *n, int x, int y)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	/*----------------------*/
	 token = 'G';
	 life = 5;
	 breedingProb = 0.15;
	 illnessProb = 0.15;
	 lifeFactor = 4;
}

Grass::~Grass()
{
	cout << "Destroying Grass"<<endl;
}

Algae::Algae(const char *n, int x, int y)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	/*----------------------*/
	 token = 'A';
	 life = 5;
	 breedingProb = 0.25;
	 illnessProb = 0.25;
     lifeFactor = 2;
}

Algae::~Algae()
{
	cout << "Destroying Algae" << endl;
}
