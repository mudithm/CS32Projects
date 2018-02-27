#include "Actor.h"
#include "StudentWorld.h"

#include <iostream>
#include <cassert>
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor implementations


Actor::Actor(int imageID, int xPos, int yPos, int dir, double size, int depth ): GraphObject(imageID, xPos, yPos, dir, size, depth), m_type(imageID)
{}

int Actor::getType()
{
	return m_type;
}

void Actor::kill()
{}

int Actor::travdir()
{}

void Actor::setDir(int dir)
{}

double Actor::getHP()
{}

Actor::~Actor()
{
	//cerr << "deleted " << getType() << endl;
}


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

Spaceship::Spaceship(int imageID, int xPos, int yPos, int dir, double size, double HP, double speed, StudentWorld* world, int depth) : Actor(imageID, xPos, yPos, dir, size, depth), m_HP(HP), m_speed(speed), m_world(world)
{}

Spaceship::~Spaceship()
{}

double Spaceship::getHP() const
{
	return m_HP;
}

double Spaceship::getSpeed() const
{
	return m_speed;
}

void Spaceship::damage(int type)
{
	int amt;
	switch (type)
	{
		case IID_SMALLGON:
			amt = 5;
			break;
		case IID_SNAGGLEGON:
			amt = 15;
			break;
		case IID_SMOREGON:
			amt = 5;			
			break;
		case IID_NACHENBLASTER:
			amt = 999;
			break;
		case IID_CABBAGE:
			amt = 2;
			break;
		case IID_TORPEDO:
			amt = 8;
			break;
		case IID_TURNIP:
			amt = 2;
			break;
		case IID_REPAIR_GOODIE:
			amt = -10;
		default:
			amt = 0;
	}
	m_HP -= amt;
	if (m_HP > 50)
		m_HP = 50;
}

bool Spaceship::isAlive() const
{
	int x = getX(), y = getY();
	if (m_HP <= 0 || y < 0 || y > VIEW_HEIGHT || x < 0 || x > VIEW_WIDTH)
	{
		if (getY() > VIEW_HEIGHT)
			 cerr << "this is a thing" << endl;
		return false;
	}
	return true;
}

StudentWorld* Spaceship::getWorld() const
{
	return m_world;
}

void Spaceship::setSpeed(double speed)
{
	m_speed = speed;
}


void Spaceship::checkCollisions(int direction)
{
	
	if (direction == 0)
	{
		NachenBlaster* player = getWorld()->getPlayer();
		if (euclidean_dist(player->getX(), player->getY(), getX(), getY()) <= .75 * (player->getRadius() + getRadius()) )
		{
			damage(player->getType());
			player->damage(getType());
			kill();
		}

	}



	for (vector<Actor*>::const_iterator iterator = (getWorld()->getActors())->begin(); iterator != (getWorld()->getActors())->end();)
	{
		switch ((*iterator)->getType())
		{
			case IID_CABBAGE:
			case IID_TURNIP:
			case IID_TORPEDO:
				if ((*iterator)->travdir() == direction){
					if((*iterator)->isAlive() && euclidean_dist(getX(), getY(), (*iterator)->getX(), (*iterator)->getY()) <= .75 * (getRadius() + (*iterator)->getRadius()) )
					{
						damage((*iterator)->getType());
						if (! isAlive())
						{
							kill();
							(*iterator)->kill();
							return;
						}
						else
						{
							(*iterator)->kill();
							getWorld()->playSound(SOUND_BLAST);
							iterator++;
						}
					}else
						iterator++;
					break;
				}
			case IID_LIFE_GOODIE:
				if (direction == 180 && euclidean_dist(getX(), getY(), (*iterator)->getX(), (*iterator)->getY()) <= .75 * (getRadius() + (*iterator)->getRadius()))
				{
					getWorld()->increaseScore(100);
					(*iterator)->kill();
					getWorld()->playSound(SOUND_GOODIE);
					getWorld()->incLives();
					return;
				}else
					iterator++;
				break;
			case IID_REPAIR_GOODIE:
				if (direction == 180 && euclidean_dist(getX(), getY(), (*iterator)->getX(), (*iterator)->getY()) <= .75 * (getRadius() + (*iterator)->getRadius()))
				{
					getWorld()->increaseScore(100);
					(*iterator)->kill();
					getWorld()->playSound(SOUND_GOODIE);
					getWorld()->getPlayer()->damage(IID_REPAIR_GOODIE);
					return;
				}else
					iterator++;
				break;
			case IID_TORPEDO_GOODIE:
				if (direction == 180 && euclidean_dist(getX(), getY(), (*iterator)->getX(), (*iterator)->getY()) <= .75 * (getRadius() + (*iterator)->getRadius()))
				{
					getWorld()->increaseScore(100);
					(*iterator)->kill();
					getWorld()->playSound(SOUND_GOODIE);
					getWorld()->getPlayer()->incTorpedoes(5);
					return;
				}else
					iterator++;
				break;
			default:
				iterator++;
		}

	}

}


// NachenBlaster Implementation

NachenBlaster::NachenBlaster(StudentWorld* world) : Spaceship(IID_NACHENBLASTER, 0, 128, 0, 1.0, 50.0, 0.0, world, 0), m_cabbage(30), m_numTorpedoes(0)
{}

void NachenBlaster::incTorpedoes(int num)
{
	m_numTorpedoes += num;
}

void NachenBlaster::doSomething()
{

	// Movement

	int ch;
	
	if (getWorld()->getKey(ch))
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
				else if (getX() >= VIEW_WIDTH - 6)
					moveTo(VIEW_WIDTH-1, getY());
				break;
			case KEY_PRESS_SPACE:
				//fire cabbage if possible
				if (getX() < VIEW_WIDTH - 12)
				{		
					if (m_cabbage >= 5)
					{
						m_cabbage -= 5;
						getWorld()->addActor(new Cabbage(getX() + 12, getY()));
						getWorld()->playSound(SOUND_PLAYER_SHOOT);					
					}

				}
				break;
			case KEY_PRESS_UP:
				if (getY() < VIEW_HEIGHT - 7)
					moveTo(getX(), getY() + 6);
				else 
					moveTo(getX(), VIEW_HEIGHT - 1);
				break;
			case KEY_PRESS_DOWN:
				if (getY() > 6)
					moveTo(getX(), getY() - 6);
				else
					moveTo(getX(), 0);

				break;
			case KEY_PRESS_ESCAPE:
				//
				break;
			case KEY_PRESS_TAB:
				// fire torpedo if possible
				if (m_numTorpedoes > 0)
				{
					m_numTorpedoes--;
					getWorld()->addActor(new Torpedo(getX() + 12, getY(), 0));
					getWorld()->playSound(SOUND_TORPEDO);

				}	
				break;
			default:
				break;
		}
	}
	if (m_cabbage < 30)
		m_cabbage++;


	// Projectile Intersections
	checkCollisions(180);
}

int NachenBlaster::getCabbage() const
{
	return m_cabbage;
}



// Alien implementations

Alien::Alien(int imageID, int xPos, int yPos, double HP, double speed, StudentWorld* world, int points) : Spaceship (imageID, xPos, yPos, 0, 1.5, HP, speed, world, 1) , m_points(points), m_deltaX(0), m_deltaY(0), m_flightPlanLength(0)
{}



void Alien::kill()
{
	getWorld()->increaseScore(m_points);
	getWorld()->playSound(SOUND_DEATH);
	getWorld()->addActor(new Explosion(getX(), getY()));
	getWorld()->incKills();

	int random = randInt(1, 6);
	// decide drops 
	switch(getType())
	{
		case IID_SMOREGON:
			if (random == 1)
			{
				getWorld()->addActor(new RepairGoodie(getX(), getY()));
			}

			else if (random == 2)
			{
				getWorld()->addActor(new TorpedoGoodie(getX(), getY()));
			}
			break;
		case IID_SNAGGLEGON:
			if (random == 1)
			{
				getWorld()->addActor(new ExtraLifeGoodie(getX(), getY()));
			}
			break;
		default:
			;
	}
}

bool Alien::fire(int chk)
{
	if (getWorld()->getPlayer()->getX() < getX() && (abs(getWorld()->getPlayer()->getY() - getY()) <= 4))
	{
		if (chk == 1)
		{
			switch(getType())
			{
				case IID_SMALLGON:
				case IID_SMOREGON:
					getWorld()->addActor(new Turnip(getX() - 14, getY()));
					getWorld()->playSound(SOUND_ALIEN_SHOOT);
					break;
				case IID_SNAGGLEGON:
					getWorld()->addActor(new Torpedo(getX() - 14, getY(), 180));
					getWorld()->playSound(SOUND_TORPEDO);
					break;
				default:
					;	
			} 

			
			return true;
		}
	} 
	return false;
}

void Alien::setDeltaX(int x)
{
	m_deltaX = x;
}

void Alien::setDeltaY(int y)
{
	m_deltaY = y;
}

void Alien::setFlightLen(int len)
{
	m_flightPlanLength = len;
}

int Alien::getDeltaX()
{
	return m_deltaX;
}

int Alien::getDeltaY()
{
	return m_deltaY;
}

int Alien::getLen()
{
	return m_flightPlanLength;
}

void Alien::checkFlightPlan()
{
	if (getLen() <= 0 || (getY() + getSpeed()) >= VIEW_HEIGHT - 1 || (getY() - getSpeed()) <= 0 )
	{
		if ((getY() + getSpeed()) >= VIEW_HEIGHT - 1)
		{
			setDeltaX(-1);
			setDeltaY(-1);
		} 
		
		else if ((getY() - getSpeed()) <= 0)
		{
			setDeltaX(-1);
			setDeltaY(1);
		} 

		else if (getLen() <= 0)
		{
			int choice = randInt(1, 3);
			switch (choice)
			{
				case 1:
					setDeltaY(0);
					setDeltaX(-1);
					break;
				case 2:
					setDeltaY(1);
					setDeltaX(-1);
					break;
				case 3:
					setDeltaY(-1);
					setDeltaX(-1);
					break;
			}
		}

		setFlightLen(randInt(1, 32));

	}

}

void Alien::move()
{
	moveTo(getX() + (getSpeed() * getDeltaX()), getY() + (getSpeed() * getDeltaY()));
	setFlightLen(getLen() - 1);
}

Alien::~Alien()
{
	getWorld()->decShips();
}


// Smallgon Implementation

Smallgon::Smallgon(int xPos, int yPos, StudentWorld* world) : Alien(IID_SMALLGON, xPos, yPos, (5.0 * (1.0 + ((world->getLevel() -1)*.1))), 2.0, world, 250)
{}

void Smallgon::doSomething()
{
	if (! isAlive())
		return;
	checkCollisions(0);
	checkFlightPlan();
	int total = (20/(getWorld()->getLevel())) + 5;
	int check = randInt(1, total);
	if (fire(check))
		return;
	move();

}

// Smoregon Implementation

Smoregon::Smoregon(int xPos, int yPos, StudentWorld* world) : Alien(IID_SMOREGON, xPos, yPos, (5.0 * (1.0 + ((world->getLevel() -1)*.1))), 2.0, world, 250)
{}


void Smoregon::doSomething()
{
	if (! isAlive())
		return;
	checkCollisions(0);
	checkFlightPlan();
	int total = (20/(getWorld()->getLevel())) + 5;
	int check = randInt(1, total);
	if (fire(check))
		return;
	if (getWorld()->getPlayer()->getX() < getX() && (abs(getWorld()->getPlayer()->getY() - getY()) <= 4))
	{
		if (check == 2)
		{
			setDeltaX(-1);
			setDeltaY(0);
			setFlightLen(VIEW_WIDTH);
			setSpeed(5.0);
		}
	
	}
	move();
}


// Snagglegon Implementation

Snagglegon::Snagglegon(int xPos, int yPos, StudentWorld* world) : Alien(IID_SNAGGLEGON, xPos, yPos, (10.0 * (1.0 + ((world->getLevel() -1)*.1))), 1.75, world, 1000)
{}


void Snagglegon::doSomething()
{
	if (! isAlive())
		return;
	checkCollisions(0);
	checkFlightPlan();
	int total = (15/(getWorld()->getLevel())) + 10;
	int check = randInt(1, total);
	if (fire(check))
		return;

	move();

}



/////////////////////////////////////
// Projectile type implementations //
/////////////////////////////////////

// Projectile implementation
Projectile::Projectile(int imageID, int xPos, int yPos, int dir) : Actor(imageID, xPos, yPos, dir, .5,  1), m_alive(true), m_travdir(dir)
{}

bool Projectile::isAlive() const
{
	int x = getX(), y = getY();
	if ( ! m_alive || y < 0 || y >= VIEW_HEIGHT - 1 || x < 0 || x >= VIEW_WIDTH)
		return false;
	return true;
}

void Projectile::kill()
{
	m_alive = false;
}

int Projectile::travdir()
{
	return m_travdir;
}

void Projectile::setDir(int dir)
{
	m_travdir = dir;
}


// Cabbage Implementation
Cabbage::Cabbage(int xPos, int yPos) : Projectile(IID_CABBAGE, xPos, yPos, 0)
{}

void Cabbage::doSomething()
{
	if (! isAlive())
		return;

	else
	{
		moveTo(getX() + 8, getY());
		if (getDirection() <= 339)
			setDirection(getDirection() + 20);
		else 
			setDirection(0);
	}
	
}

// Turnip Implementation
Turnip::Turnip(int xPos, int yPos) : Projectile(IID_TURNIP, xPos, yPos, 0)
{
	setDir(180);
}

void Turnip::doSomething()
{
	if (! isAlive())
		return;
	if (travdir() == 180)
		moveTo(getX() - 6, getY());
	else
		moveTo(getX() + 6, getY());
	if (getDirection() <= 339)
		setDirection(getDirection() + 20);
	else 
		setDirection(0);

}

// Flatulence Torpedo Implementation
Torpedo::Torpedo(int xPos, int yPos, int dir) : Projectile(IID_TORPEDO, xPos, yPos, dir)
{}

void Torpedo::doSomething()
{
	if (! isAlive())
		return;

	if (getDirection() == 180)
		moveTo(getX() - 8, getY());
	else 
		moveTo(getX() + 8, getY());
}



////////////////////////////////////////
// Goodie Type Classes Implementation //
////////////////////////////////////////

// Goodie implementation
Goodie::Goodie(int imageID, int xPos, int yPos, int dir) : Projectile(imageID, xPos, yPos, 0)
{}

void Goodie::doSomething()
{
	if (! isAlive())
		return;
	moveTo(getX() - 0.75, getY() - 0.75);
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



////////////////////////////////////
// Auxiliary Function Definitions //
////////////////////////////////////

double euclidean_dist(int x1, int y1, int x2, int y2)
{
	return (sqrt(static_cast<double>((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}
