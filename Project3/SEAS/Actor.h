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

    private:

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
		Spaceship(int imageID, int xPos, int yPos, int dir, double size, double HP, double speed, int depth=0);
		double getHP() const;
		double getSpeed() const;
		virtual bool isAlive() const;
	private:
		double m_HP;
		double m_speed;
};


// NachenBlaster class definition
class NachenBlaster : public Spaceship
{
	public:
		NachenBlaster(StudentWorld* world);
		virtual void doSomething() override;
		int getCabbage() const;
	private:
		int m_cabbage;
		StudentWorld* m_world;

};

//Smallgon class definition
class Smallgon : public Spaceship
{
	public:
		Smallgon(int xPos, int yPos, int dir);
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
	private:
		bool m_alive;

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
///////////////////////

// Goodie class definition
class Goodie : public Projectile
{
	public:
		Goodie(int imageID, int xPos, int yPos, int dir);
		virtual void doSomething();
	private:
		int m_type;
};


// Extra Life Goodie class definition
class ExtraLifeGoodie : public Goodie
{
	public:
		ExtraLifeGoodie(int xPos, int yPos);
};

// Repair Goodie class definition
class RepairGoodie: public Goodie
{
	public:
		RepairGoodie(int xPos, int yPos);
};

// Torpedo Goodie class definition
class TorpedoGoodie: public Goodie
{
	public:
		TorpedoGoodie(int xPos, int yPos);
};


#endif // ACTOR_H_
