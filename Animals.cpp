#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Animals.h"

using namespace std;

Deer::Deer(const char *n, int x, int y, int status)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);

	if (status == 0) {
		currentSize = 2;
		isAlive = 1;
		maxSize = 5;
		hungerCount = 0;
		eatenFood = 0;
		hibernates = 0;
		inHibernation = -1;
		speed = 4;
		neededFood = 4;
		canClimb = 1;
		eatCount = 2;
		isHungry = 0;
		inHeat = 0;
	}
	else {
		currentSize = 2;
		isAlive = 1;
		maxSize = 5;
		hungerCount = 0;
		eatenFood = 0;
		hibernates = 0;
		inHibernation = -1;
		speed = 8;
		neededFood = 8;
		canClimb = 0;
		eatCount = 2;
		isHungry = 0;
		inHeat = 0;

	}

	cout << "A deer has just been created" << endl;
}

Deer::~Deer()
{
	cout << "A deer has just waisted" << endl;
}

void Deer::growth()
{
	//if(size < max)
}

void Deer::comingOfAge()
{
	if (currentSize == maxSize) {
		speed = 8;
		neededFood = 8;
		canClimb = 0;
	}
}

Herbivores::Herbivores()
{
	cout << "It's herbivore" << endl;
}

Herbivores::~Herbivores()
{
	cout << "A herbivore just died" << endl;
}

int Herbivores::GetDaysFull()
{
	return daysFull;
}

void Herbivores::SetDaysFull(int n)
{
	daysFull = n;
}

char Herbivores::GetToken()
{
	return token;
}

int Herbivores::GetNeededFood()
{
	return neededFood;
}

void Herbivores::SetNeededFood(const int & n)
{
	neededFood = n;
}

Animal::Animal()
{
	/*char *name;
	currentSize = -1;
	maxSize = -1;
	hungerCount = -1;
	eatenFood = -1;
	eatCount = -1;
	isHungry = -1;
	inHeat = -1;
	speed = -1;
	hibernates = -1;
	inHibernation = -1;	
	*/cout << "An animal has been created" << endl;
}

Animal::~Animal()
{
	delete[] name;
	cout << "An animal just died" << endl;
}

void Animal::setX(int n)
{
	coordinateX = n;
}

void Animal::setY(int n)
{
	coordinateY = n;
}

int Animal::getX()
{
	return coordinateX;
}

int Animal::getY()
{
	return coordinateY;
}

void Animal::SetIsHungry(int n)
{
	isHungry = n;
}

int Animal::GetIsHungry()
{
	return isHungry;
}

void Animal::SetHungerCount(int n)
{
	hungerCount = n;
}

char * Animal::GetName()
{
	return name;
}

int Animal::GetHibernates()
{
	return hibernates;
}

void Animal::SetInHibernation(int n)
{
	inHibernation = n;
}

int Animal::GetInHibernation()
{
	return inHibernation;
}

int Animal::GetEatenFood(int n)
{
	return eatenFood;
}

void Animal::SetEatenFood(int n)
{
	eatenFood = n;
}

int Animal::GetHungerCount()
{
	return hungerCount;
}

int Animal::GetEatenFood()
{
	return eatenFood;
}

void Animal::SetIsAlive(const int & n)
{
	isAlive = n;
}

int Animal::GetIsAlive()
{
	return isAlive;
}

void Animal::SetCurrentSize(const int & n)
{
	currentSize = n;
}

int Animal::GetCurrentSize()
{
	return currentSize;
}

int Animal::GetMaxSize()
{
	return maxSize;
}

int Animal::GetEatCount()
{
	return eatCount;
}

Rabbit::Rabbit(const char *n, int x, int y, int status)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	if (status == 0) {
		currentSize = 1;
		maxSize = 2;
		hungerCount = 0;
		eatenFood = 0;
		eatCount = 1;
		isAlive = 1;
		speed = 2;
		neededFood = 2;
		isHungry = 0;
		hibernates = 0;
		inHibernation = -1;
		canClimb = 0;
		inHeat = 0;
	}
	else {
		currentSize = 2;
		maxSize = 2;
		hungerCount = 0;
		eatenFood = 0;
		eatCount = 1;
		isAlive = 1;
		speed = 6;
		neededFood = 4;
		isHungry = 0;
		hibernates = 0;
		inHibernation = -1;
		canClimb = 0;
		inHeat = 0;
	}

	cout << "A Rabbit has been created" << endl;

}

Rabbit::~Rabbit()
{
	cout << "A Rabbit just died" << endl;
}


Groundhog::Groundhog(const char *n, int x, int y,int status)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	if (status == 0) {
		currentSize = 2;
		maxSize = 3;
		hungerCount = 0;
		eatenFood = 0;
		eatCount = 1;
		isAlive = 1;
		speed = 3;
		neededFood = 3;
		isHungry = 0;
		hibernates = 1;
		inHibernation = 0;
		canClimb = 1;
		inHeat = 0;
	}
	else {
		currentSize = 3;
		maxSize = 3;
		hungerCount = 0;
		eatenFood = 0;
		eatCount = 1;
		isAlive = 1;
		speed = 5;
		neededFood = 5;
		isHungry = 0;
		hibernates = 1;
		inHibernation = 0;
		canClimb = 1;
		inHeat = 0;
	}
	cout << "A Groundhog has been created" << endl;

}

Groundhog::~Groundhog()
{
	cout << "A GroundHog just died" << endl;
}

Salmon::Salmon(const char *n, int x, int y)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);

	currentSize = 1;
	maxSize = 1;
	hungerCount = 0;
	eatenFood = 0;
	eatCount = 1;
	isAlive = 1;
	speed = 5;
	neededFood = 1;
	isHungry = 0;
	hibernates = 0;
	inHibernation = -1;
	canClimb = 0;
	inHeat = 0;

	cout << "A Salmon has been created" << endl;
}

Salmon::~Salmon()
{
	cout << "A Salmon just died" << endl;
}

Carnivores::Carnivores()
{
	cout << "It's Carnivore" << endl;
}

Carnivores::~Carnivores()
{
	cout << "A Carnivore just died" << endl;

}

char Carnivores::GetToken()
{
	return token;
}

int Carnivores::GetNeededFood()
{
	return neededFood;
}

void Carnivores::SetNeededFood(const int & n)
{
	neededFood = n;
}

Fox::Fox(const char *n, int x, int y,int status)
{	
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);

	if (status == 0) {
		currentSize = 1;
		maxSize = 4;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 1;
		hibernates = 0;
		inHibernation = -1;
		attack = 1;
		defence = 1;
		neededFood = 2;
	}
	else {
		currentSize = 4;
		maxSize = 4;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 6;
		hibernates = 0;
		inHibernation = -1;
		attack = 5;
		defence = 5;
		neededFood = 6;
	}

	cout << "A Fox has been created" << endl;

}

Fox::~Fox()
{
	cout << "A Fox just died" << endl;
}

int Fox::GetAttack()
{
	return attack;
}

void Fox::SetAttack(const int & n)
{
	attack = n;
}

int Fox::GetDefence()
{
	return defence;
}

void Fox::SetDefence(const int & n)
{
	defence = n;
}

Wolf::Wolf(const char *n, int x, int y, int status)
{
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);

	if (status == 0) {	
		currentSize = 1;
		maxSize = 7;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 1;
		hibernates = 0;
		inHibernation = -1;
		attack = 2;
		defence = 2;
		neededFood = 2;
	}
	else {
		currentSize = 7;
		maxSize = 7;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 8;
		hibernates = 0;
		inHibernation = -1;
		attack = 8;
		defence = 6;
		neededFood = 8;
	}

	cout << "A Wolf has been created" << endl;
}

Wolf::~Wolf()
{
	cout << "A Wolf just died" << endl;
}

int Wolf::GetAttack()
{
	return attack;
}

void Wolf::SetAttack(const int & n)
{
	attack = n;
}

int Wolf::GetDefence()
{
	return defence;
}

void Wolf::SetDefence(const int & n)
{
	defence = n;
}

int Wolf::GetSpeed()
{
	return speed;
}

void Wolf::SetSpeed(const int & n)
{
	speed = n;
}

Bear::Bear(const char *n, int x, int y, int status)
{		
	coordinateX = x;
	coordinateY = y;
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	if (status == 0) {
		currentSize = 3;
		maxSize = 10;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 4;
		hibernates = 1;
		inHibernation = 0;
		attack = 6;
		defence = 6;
		neededFood = 5;
	}
	else {
		currentSize = 10;
		maxSize = 10;
		hungerCount = 0;
		eatenFood = 0;
		//eatCount;		//Food Units
		isAlive = 1;
		isHungry = 1;
		inHeat = 0;
		speed = 4;
		hibernates = 1;
		inHibernation = 0;
		attack = 10;
		defence = 10;
		neededFood = 10;
	}
	cout << "A Bear has been created" << endl;
}

Bear::~Bear()
{
	cout << "A Bear just died" << endl;

}

int Bear::GetAttack()
{
	return attack;
}

void Bear::SetAttack(const int & n)
{
	attack = n;
}

int Bear::GetDefence()
{
	return defence;
}

void Bear::SetDefence(const int & n)
{
	defence = n;
}

/*-------------------------------------------------------*/

List::List() :numOfElements(0)
{
	first = NULL;
}

List::~List()
{
	Node *cur = first;
	Node *Next;
	while (cur != NULL) {
		Next = cur->next;
		delete cur;
		cur = Next;

	}
	first = NULL;
}

void List::push(Animal * animal, int val)
{
	if (size() == 0) {		//For First Node
		first = new Node(animal, val);
	}
	else {			//For Others Node
		Node *cur = first;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new Node(animal, val);
	}
	numOfElements++;
}

int List::size()
{
	return numOfElements;
}

Node * List::getFirst()
{
	return first;
}

void List::SetFirst(Node * f)
{
	first = f;
}

void List::dec()
{
	numOfElements--;
}

int List::GetN()
{
	return numOfElements;
}

Node::Node(Animal * an, int val)
{
	value = val;
	animal = an;
	next = NULL;

}

Node::~Node()
{
	delete animal;
	next = NULL;
	value = 0;
}