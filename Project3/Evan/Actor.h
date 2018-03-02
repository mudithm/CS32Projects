#ifndef ACTOR_H_
#define ACTOR_H_
#include "StudentWorld.h"
#include "GraphObject.h"
#include <cmath>
using namespace std;
const int HIT_BY_SHIP = 0;
const int HIT_BY_PROJECTILE = 1;
double euclidian_dist(double thisX, double thisY, double otherX, double otherY);
class StudentWorld;
class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection = 0, double size = 1.0, int depth = 0);
	StudentWorld* getWorld() const;
	virtual ~Actor();
	virtual bool isDamageableToPlayer() const;
	virtual int damageToPlayer() const;
	void setWorld(StudentWorld* newWorld);
	virtual void sufferDamage(double amt, int cause);
	bool getStatus() const;
	void setStatus(bool i);
	int getHitPoints() const;
	void setHitPoints(int points);
	virtual bool isProj() const;
	virtual bool isAlien() const;
	virtual void doSomething() = 0;
	// This actor suffers an amount of damage caused by being hit by either
	// a ship or a projectile (see constants above).
	//virtual void sufferDamage(double amt, int cause) = 0;
private:
	int hitPoints;
	bool m_alive;
	StudentWorld* m_world;
};
class Star : public Actor
{
public:
	Star(StudentWorld* newWorld, double xPos, double yPos);
	virtual void doSomething();
private:
};
class NachenBlaster : public Actor
{
public:
	NachenBlaster(StudentWorld* newWorld);
	virtual void doSomething();

	int getCabbagePoints() const;
	int getTorpedoes() const;
	void addTorpedoes(int p);
	void addHitPoints(int points);

	// This actor suffers an amount of damage caused by being hit by either
	// a ship or a projectile (see constants above).
private:
	int cabbageEnergyPoints;
	int flatTorpedoes;
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Explosion : public Actor
{
public:
	Explosion(StudentWorld* newWorld, double x, double y);
	virtual void doSomething();
private:
	int ticks;
};
class Projectile : public Actor
{
public:
	Projectile(StudentWorld* w, double startX, double startY, int imageID, int imageDir)
		: Actor(w, imageID, startX, startY, imageDir, .5, 1)
	{
	}
	virtual bool isProj() const
	{
		return true;
	}



private:
};
class Cabbage : public Projectile
{
public:
	Cabbage(StudentWorld* newWorld, double x, double y);
	virtual void doSomething();
	virtual int damageToPlayer() const
	{
		return 2;
	}
private:

};
class Turnip : public Projectile
{
public:
	Turnip(StudentWorld* newWorld, double x, double y);
	virtual void doSomething();
	virtual bool isDamageableToPlayer() const
	{
		return true;
	}
	virtual int damageToPlayer() const
	{
		return 2;
	}
private:

};
class PlayerLaunchedTorpedo : public Projectile
{
public:
	PlayerLaunchedTorpedo(StudentWorld* w, double startX, double startY) : Projectile(w, startX, startY, IID_TORPEDO, 0)
	{

	}
	virtual int damageToPlayer() const;
	virtual void doSomething();
};

class AlienLaunchedTorpedo : public Projectile
{
public:
	AlienLaunchedTorpedo(StudentWorld* w, double startX, double startY) : Projectile(w, startX, startY, IID_TORPEDO, 180)
	{

	}
	virtual int damageToPlayer() const;
	virtual bool isDamageableToPlayer() const;
	virtual void doSomething();
};
class Alien : public Actor
{
public:
	//direction 0
	//size 1.5
	// depth 1
	Alien(StudentWorld* newWorld, double startX, double startY, int imageID, double hitPoints, double length, double speed)
		: Actor(newWorld, imageID, startX, startY, 0, 1.5, 1)
	{
		newWorld->addAlien();
		setHitPoints(hitPoints);
		m_length = length;
		m_speed = speed;
	}
	~Alien()
	{
		getWorld()->decCurrent();
	}
	double getLength() const
	{
		return m_length;
	}
	virtual bool isAlien() const
	{
		return true;
	}
	void setLength(int length)
	{
		m_length = length;
	}
	double getSpeed() const
	{
		return m_speed;
	}
	void setSpeed(double speed)
	{
		m_speed = speed;
	}
private:
	double m_length;
	double m_speed;
};

class Smallgon : public Alien
{
public:
	Smallgon(StudentWorld* w, double startX, double startY)
		: Alien(w, startX, startY, IID_SMALLGON, (5 * (1 + (w->getLevel() - 1) * .1)), 0, 2)
	{
	}
	virtual void doSomething();
	virtual int damageToPlayer() const
	{
		return 5;
	}
private:
	int travelDirection;
};

class Smoregon : public Alien
{
public:
	Smoregon(StudentWorld* w, double startX, double startY)
		: Alien(w, startX, startY, IID_SMOREGON, 5 * (1 + (w->getLevel() - 1) * .1), 0, 2)
	{
	}
	virtual void doSomething();
	virtual int damageToPlayer() const
	{
		return 5;
	}

private:
	int travelDirection;
};

class Snagglegon : public Alien
{
public:
	Snagglegon(StudentWorld* w, double startX, double startY)
		: Alien(w, startX, startY, IID_SNAGGLEGON, (10 * (1 + (w->getLevel() - 1) * .1)), 0, 1.75)
	{
		travelDirection = -2;
	}
	virtual void doSomething();
	virtual int damageToPlayer() const
	{
		return 15;
	}
private:
	int travelDirection;
};
class Goodie : public Actor
{
public:
	//direction 0
	// size .5
	// depth 1
	Goodie(StudentWorld* w, double startX, double startY, int imageID)
		: Actor(w, imageID, startX, startY, 0, .5, 1)
	{
	}
};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(StudentWorld* w, double startX, double startY) : Goodie(w, startX, startY, IID_LIFE_GOODIE)
	{

	}
	virtual void doSomething();
};

class RepairGoodie : public Goodie
{
public:
	RepairGoodie(StudentWorld* w, double startX, double startY)
		: Goodie(w, startX, startY, IID_REPAIR_GOODIE)
	{

	}
	virtual void doSomething();
};

class TorpedoGoodie : public Goodie
{
public:
	TorpedoGoodie(StudentWorld* w, double startX, double startY)
		: Goodie(w, startX, startY, IID_TORPEDO_GOODIE)
	{

	}
	virtual void doSomething();
};
#endif // ACTOR_H_