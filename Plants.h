

class Plant {
private:
	
protected:
	 char *name;
	int coordinateX;
	int coordinateY;
	char token;
public:
	Plant();
	virtual ~Plant();
	char GetToken();
	virtual int GetLife() { return 0; }
	virtual int GetLifeFactor() { return 0; }
	virtual void SetLife(const int &n) {}
	virtual void SetLifeFactor(const int &n) {}
	virtual int CheckIfSick() { return 0; }
	virtual int LoseLife(int amount, int &eaten) { return 0; }
	virtual int GetSize() { return 0; }
	
};

class Seeded :public Plant {	//Have seed
protected:
	int size;
	int foliage;
	int seed;
	double breedingProb;
	double illnessProb;
	int lifeFactor;
	int life;		//TO BE FILLED
	public:
		Seeded();
		~Seeded();
		int LoseLife(int amount, int &eaten); // 1 - Alive  0 - Dead
		int CheckIfSick();
		int checkifBreeded();
		int GetSize();

};

class Oak :public Seeded {
private:

public :
	Oak(const char *n, int x, int y);
	~Oak();
};

class Pine :public Seeded {
private:
public:
	Pine(const char *n, int x, int y);
	~Pine();
};

class Maple :public Seeded {
private:
	
public:
	Maple(const char *n, int x, int y);
	~Maple();

};

class Seedless :public Plant {	//Not have seed
protected:
	int life;
	double breedingProb;
	double illnessProb;
	int lifeFactor;
public:
		Seedless();
		~Seedless();	
		int LoseLife(int amount, int &eaten);
		int CheckIfSick();	//2 - Isnt Sick  1 - Sick but alive  0 - Dead
		int CheckIfBreeded(); // 1 - Success  0 - Failure
		int GetLife();
		int GetLifeFactor();
		void SetLife(const int &n);
		void SetLifeFactor(const int &n);
};

class Grass :public Seedless {
public:
	Grass(const char *n, int x, int y);
	~Grass();
};

class Algae :public Seedless {
public:
	Algae(const char *n, int x, int y);
	~Algae();
};