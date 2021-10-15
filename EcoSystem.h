#include "Plants.h"
#include "Animals.h"




class Tile {
	private:
		Plant *plant=NULL;
		int animals;
		char typeOfEnvironment;
		
	public:
		Tile();
		~Tile();
		
		void setTypeOfEnvironment(char type);
		char getTypeOfEnvironment();
		void setPlantPtr(Plant *p);
		Plant *getPlantPtr();

};


class Terrain {
	private:
		int terrainSize;
		Tile ***tile=NULL;
	public:
		Terrain(int size, int lakeSize, int sumOfHills, int *&PlantArray);
		~Terrain();

		void MapGenerator(int lakeSize, int sumOfHills);	//Creates the terrain
		void GenerateRiver();	//Creates the river
		void GenerateLake(int lakeSize);	//Creates the lake
		void GenerateHills(int sumOfHills);    //Creates the hills
		void GenerateMeadow();
		void PlacePlants(int *&plantArray);
		List* PlaceAnimals(int *&animalArray);
		void printTerrain();
		int GetTerrainSize();
		Plant * GetPlant(int i, int j);
		int AnimalMovement(List *list);
		void AnimalEating(List *list);
		char getTypeOfEnvironment(int i,int j);
		void setNullPlant(int i,int j);
};

class Ecosystem {
	private:
		Terrain *terrain;
		int dayOfYear;		//Current day of year
		int *growthPeriod;		//[0]->Plant [1]->Animal		
		int *breedingRepPeriod;		//[0]->Plant [1]->Herbivores [2]->Carnivores		
		int season;			//0->Winter 1->Spring 2->Summer 3->Autumn
	public:
		Ecosystem(int terrainsize, int currentDate,int lakeSize,int sumOfHills,int *&plantArray);
		~Ecosystem();
		List * Placeanimals(int *&animalarray);

		void RunEcosystem(List *list,int daysOfSimulation);
		void ApplySeason(List *list);
		void DailyReset(List *list,int currentDay);
		void CheckHunger(List *list);
		void RemoveEntitie(List *list,int key);
		void DeadEntities(List *list);
		void grow(List *list);
		Plant * GetTerrainPlant(int i, int j);
		void PrintPlantStatistics();
		void PrintSystem(List *list);
};


