
class Animal {
	protected:
		char *name;			//Name of animal
		int currentSize;	//Current size of animal 
		int maxSize;		//Max size of animal 
		int hungerCount;	//Days it has not eat
		int eatenFood;		//Food whitch has been consumed 
		int eatCount;		//Food Units
		int coordinateX;
		int coordinateY;
		int isAlive;
		int isHungry;	 //0-Not hungry 1-is hungry
		int inHeat;		//
		int speed;
		int hibernates;	//0-Not 1 hibernates
		int inHibernation;	//0-Not 1-Yes

    public:
		Animal();
		virtual ~Animal();
		void setX(int n);
		void setY(int n);
		int getX();
		int getY();
		void SetIsHungry(int n);
		int GetIsHungry();		
		int GetHungerCount();
		void SetHungerCount(int n);
		char *GetName();
		int GetHibernates();
		void SetInHibernation(int n);
		int GetInHibernation();
		int GetEatenFood(int n);
		void SetEatenFood(int n);
		int GetEatenFood();
		void SetIsAlive(const int &n);
		int GetIsAlive();
		virtual char GetToken() { return NULL; }
		virtual int GetDaysFull() { return 0; }
		virtual void SetDaysFull(int n){}
		virtual int GetAttack() { return 0; }
		virtual void SetAttack(const int &n) {}
		virtual int GetDefence() { return 0; }
		virtual void SetDefence(const int &n) {}
		void SetCurrentSize(const int &n);
		int GetCurrentSize();
		int GetMaxSize();
		virtual int GetSpeed() { return 0; }
		virtual void SetSpeed(const int &n){}
		virtual int GetNeededFood() { return 0; }
		virtual void SetNeededFood(const int &n) {}
		int GetEatCount();


};

class Herbivores: public Animal {

	protected:
		char token = 'H';
		int canClimb; // 0-No 1-Yes
		int neededFood;
		int daysFull; //num of days he is full

	public:
		Herbivores();
		~Herbivores();
		int GetDaysFull();
		void SetDaysFull(int n);
		char GetToken();
		int GetNeededFood();
		void SetNeededFood(const int &n);
};

class Deer : public Herbivores {

	public:
		Deer(const char *n, int x, int y,int status);	//0-> new born   1->Old
		~Deer();
		void growth();
		void comingOfAge();
};

class Rabbit : public Herbivores {

public:
	Rabbit(const char *n,int x,int y, int status);
	~Rabbit();

	//void Move(Terrain *terrain);

};

class Groundhog : public Herbivores {

public:
	Groundhog(const char *n, int x, int y, int status);
	~Groundhog();

};

class Salmon : public Herbivores {

public:
	Salmon(const char *n, int x, int y);
	~Salmon();

};

class Carnivores : public Animal {

protected:
	char token = 'C';
	int attack;
	int defence;
	int neededFood;

public:
	Carnivores();
	~Carnivores();
	char GetToken();
	int GetNeededFood();
	void SetNeededFood(const int &n);

};

class Fox : public Carnivores {

public:
	Fox(const char *n, int x, int y, int status);
	~Fox();
	int GetAttack();
	void SetAttack(const int &n);
	int GetDefence();
	void SetDefence(const int &n);

};

class Bear : public Carnivores {

public:
	Bear(const char *n, int x, int y, int status);
	~Bear();
	int GetAttack();
	void SetAttack(const int &n);
	int GetDefence();
	void SetDefence(const int &n);

};

class Wolf : public Carnivores {

public:
	Wolf(const char *n, int x, int y, int status);
	~Wolf();
	int GetAttack();
	void SetAttack(const int &n);
	int GetDefence();
	void SetDefence(const int &n);
	int GetSpeed();
	void SetSpeed(const int &n);

};





/*--------------------------------------------------------------------------*/
struct Node{
	public:
		int value;
		Animal* animal;
		Node *next;
		Node(Animal *an,int val);
		~Node();

};

class List{
	private:
		Node *first;
		int numOfElements;
	public:
		List();
		~List();
		void push(Animal* animal,int val);
		int size();
		Node * getFirst();
		void SetFirst(Node *f);
		void dec();
		int GetN();

};
