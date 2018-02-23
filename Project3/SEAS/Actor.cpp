#include "Actor.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor implementations


Actor::Actor(int imageID, int xPos, int yPos, int dir, double size, int depth ): GraphObject(imageID, xPos, yPos, dir, size, depth)
{}


Actor::~Actor()
{}


// Star implementations

Star::Star(int xPos, int yPos, double size) : Actor(IID_STAR, xPos, yPos, 0, size, 3)
{}

void Star::doSomething()
{
	moveTo(getX()-1, getY());
}

bool Star::isAlive() const
{
	int x = getX(), y = getY();
	if (y < 0 || y >= VIEW_HEIGHT || x < 0 || x >= VIEW_WIDTH)
		return false;
	return true;
}

// Explosion Implementations

Explosion::Explosion(int xPos, int yPos) : Actor(IID_EXPLOSION, xPos, yPos, 0, 1, 0), m_count(1)
{}

bool Explosion::isAlive() const
{
	if (m_count > 4)
		return false;
	return true;
}

void Explosion::doSomething()
{
	setSize(getSize() * 1.5);
	m_count++;
}

////////////////////////////////////
// Spaceship-type implementations //
////////////////////////////////////

Spaceship::Spaceship(int imageID, int xPos, int yPos, int dir, double size, double HP, double speed, int depth) : Actor(imageID, xPos, yPos, dir, size, depth), m_HP(HP), m_speed(speed)
{}

double Spaceship::getHP() const
{
	return m_HP;
}

double Spaceship::getSpeed() const
{
	return m_speed;
}

bool Spaceship::isAlive() const
{
	int x = getX(), y = getY();
	if (m_HP <= 0 || y < 0 || y >= VIEW_HEIGHT || x < 0 || x >= VIEW_WIDTH)
		return false;
	return true;
}

// NachenBlaster Implementation

NachenBlaster::NachenBlaster(StudentWorld* world) : Spaceship(IID_NACHENBLASTER, 0, 128, 0, 1.0, 50.0, 0.0,  0), m_cabbage(30), m_world(world)
{}

void NachenBlaster::doSomething()
{
	int ch;
	if (! isAlive())
		return;
	else if (m_world->getKey(ch))
	{
		switch (ch)
		{
			case KEY_PRESS_LEFT:
				//Move ship left
				if (getX() > 5)
					moveTo(getX() - 6, getY());
				break;
			case KEY_PRESS_RIGHT:
				//move ship right
				if (getX() < VIEW_WIDTH - 6)
					moveTo(getX() + 6, getY());
				else 
					moveTo(VIEW_WIDTH-1, getY());
				break;
			case KEY_PRESS_SPACE:
				//fire cabbage if possible
				if (m_cabbage >= 5)
				{
					m_cabbage -= 5;
				}
				break;
			case KEY_PRESS_UP:
				if (getY() < VIEW_HEIGHT - 6)
					moveTo(getX(), getY() + 6);
				else
					moveTo(getX(), VIEW_HEIGHT - 1);
				break;
			case KEY_PRESS_DOWN:
				if (getY() > 5)
					moveTo(getX(), getY() - 6);
				else
					moveTo(getX(), 0);

				break;
			case KEY_PRESS_ESCAPE:
				//
				break;
			case KEY_PRESS_TAB:
				// fire torpedo if possible
				break;
			default:
				break;
						
		}
	}
	if (m_cabbage < 30)
		m_cabbage++;
}

int NachenBlaster::getCabbage() const
{
	return m_cabbage;
}

// Smallgon Implementation

Smallgon::Smallgon(int xPos, int yPos, int dir) : Spaceship(IID_SMALLGON, xPos, yPos, 0, 1.5, dir, 2.0, 1)
{}

void Smallgon::doSomething()
{
	
}


/////////////////////////////////////
// Projectile type implementations //
/////////////////////////////////////

// Projectile implementation
Projectile::Projectile(int imageID, int xPos, int yPos, int dir) : Actor(imageID, xPos, yPos, dir, .5,  1), m_alive(true)
{}

bool Projectile::isAlive() const
{
	int x = getX(), y = getY();
	if ( ! m_alive || y < 0 || y >= VIEW_HEIGHT || x < 0 || x >= VIEW_WIDTH)
		return false;
	return true;
}

// Cabbage Implementation
Cabbage::Cabbage(int xPos, int yPos) : Projectile(IID_CABBAGE, xPos, yPos, 0)
{}

void Cabbage::doSomething()
{

}

// Turnip Implementation
Turnip::Turnip(int xPos, int yPos) : Projectile(IID_TURNIP, xPos, yPos, 0)
{}

void Turnip::doSomething()
{

}

// Flatulence Torpedo Implementation
Torpedo::Torpedo(int xPos, int yPos, int dir) : Projectile(IID_TORPEDO, xPos, yPos, dir)
{}

void Torpedo::doSomething()
{

}



////////////////////////////////////////
// Goodie Type Classes Implementation //
////////////////////////////////////////

// Goodie implementation
Goodie::Goodie(int imageID, int xPos, int yPos, int dir) : Projectile(imageID, xPos, yPos, 0), m_type(imageID)
{}


void Goodie::doSomething()
{
	switch (m_type){
		case 0:
			break;
		default:
			break;
	}
}

// Extra Life Goodie Implementation

ExtraLifeGoodie::ExtraLifeGoodie(int xPos, int yPos) : Goodie(IID_LIFE_GOODIE, xPos, yPos, 0)
{}



// Repair Goodie Implementation

RepairGoodie::RepairGoodie(int xPos, int yPos) : Goodie(IID_REPAIR_GOODIE, xPos, yPos, 0)
{}


// Torpedo Goodie Implementation

TorpedoGoodie::TorpedoGoodie(int xPos, int yPos) : Goodie(IID_REPAIR_GOODIE, xPos, yPos, 0)
{}




