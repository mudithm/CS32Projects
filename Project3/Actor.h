#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// Actor base class
class Actor : public GraphObject
{
public:
	Actor(int imageID, int xPos, int yPos, int dir, double size, int depth = 0);
	virtual ~Actor();
	virtual void doSomething() = 0;
	virtual bool isAlive() const = 0;
	virtual void kill();
	virtual double getHP();
	virtual int travdir();
	virtual void setDir(int dir);
	int getType() const;

private:
	int m_type;

};

// Star class definition
class Star : public Actor
{
public:
	Star(int xPos, int yPos, double size);
	virtual void doSomething() override;
	virtual bool isAlive() const;
};

// Explosion class definition
class Explosion : public Actor
{
public:
	Explosion(int xPos, int yPos);
	virtual void doSomething() override;
	virtual bool isAlive() const;
private:
	int m_count;
};

////////////////////////////
// Spaceship type classes //
////////////////////////////


// Spaceship class definition
class Spaceship : public Actor
{
public:
	Spaceship(int imageID, int xPos, int yPos, int dir, double size, double HP, double speed, StudentWorld* world, int depth = 0);
	virtual ~Spaceship();
	double getHP() const;
	double getSpeed() const;
	void setSpeed(double speed);
	void damage(int amt);
	void checkCollisions(int direction);
	StudentWorld* getWorld() const;
	virtual bool isAlive() const;
private:
	double m_HP;
	double m_speed;
	StudentWorld* m_world;
	int m_travdir;


};


// NachenBlaster class definition
class NachenBlaster : public Spaceship
{
public:
	NachenBlaster(StudentWorld* world);
	virtual void doSomething() override;
	void incTorpedoes(int num);
	int getTorpedoes();
	int getCabbage() const;
private:
	int m_cabbage;
	int m_numTorpedoes;

};

class Alien : public Spaceship
{
public:
	Alien(int imageID, int xPos, int yPos, double HP, double speed, StudentWorld* world, int points);
	//void move();
	~Alien();
	virtual void kill();
	void setDeltaX(int x);
	void setDeltaY(int y);
	void setFlightLen(int len);
	int getDeltaX();
	int getDeltaY();
	int getLen();
	void move();
	bool fire(int chk);
	virtual void checkFlightPlan();
private:
	int m_points;
	int m_flightPlanLength;
	double m_deltaX;
	double m_deltaY;
};

//Smallgon class definition
class Smallgon : public Alien
{
public:
	Smallgon(int xPos, int yPos, StudentWorld* world);
	virtual void doSomething() override;
};

//Smoregon class definition
class Smoregon : public Alien
{
public:
	Smoregon(int xPos, int yPos, StudentWorld* world);
	virtual void doSomething() override;
};

//Snagglegon class definition
class Snagglegon : public Alien
{
public:
	Snagglegon(int xPos, int yPos, StudentWorld* world);
	virtual void checkFlightPlan();
	virtual void doSomething() override;

};

/////////////////////////////
// Projectile Type Classes //
/////////////////////////////

// Projectile class definitions
class Projectile : public Actor
{
public:
	Projectile(int imageID, int xPos, int yPos, int dir);
	virtual bool isAlive() const;
	virtual void kill();
	virtual int travdir();
	void setDir(int dir);
private:
	bool m_alive;
	int m_travdir;

};

// Cabbage class definition

class Cabbage : public Projectile
{
public:
	Cabbage(int xPos, int yPos);
	virtual void doSomething() override;
};


class Turnip : public Projectile
{
public:
	Turnip(int xPos, int yPos);
	virtual void doSomething() override;
};


class Torpedo : public Projectile
{
public:
	Torpedo(int xPos, int yPos, int dir);
	virtual void doSomething() override;
};


////////////////////////
// Goodie-Type clases //
////////////////////////

// Goodie class definition
class Goodie : public Projectile
{
public:
	Goodie(int imageID, int xPos, int yPos, int dir);
	virtual ~Goodie() = 0;
	virtual void doSomething();
};


// Extra Life Goodie class definition
class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(int xPos, int yPos);
};

// Repair Goodie class definition
class RepairGoodie : public Goodie
{
public:
	RepairGoodie(int xPos, int yPos);
};

// Torpedo Goodie class definition
class TorpedoGoodie : public Goodie
{
public:
	TorpedoGoodie(int xPos, int yPos);
};

/////////////////////////
// Auxiliary Functions //
/////////////////////////

double euclidean_dist(int x1, int y1, int x2, int y2);


#endif // ACTOR_H_
