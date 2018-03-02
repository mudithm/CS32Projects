#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp


StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	numAlienDestroyed = 0;
}
void StudentWorld::addActor(Actor* a)
{
	actorList.push_back(a);
}
void StudentWorld::setPoints(int p)
{
	points = p;
}
int StudentWorld::getPoints() const
{
	return points;
}
void StudentWorld::addLife()
{
	lives++;
}
// If there's at least one alien that's collided with a, return
// a pointer to one of them; otherwise, return a null pointer.
Actor* StudentWorld::getOneCollidingAlien(const Actor* a) const
{
	double thisX = a->getX();
	double thisY = a->getY();
	double thisR = a->getRadius();
	double alienX;
	double alienY;
	double alienR;
	vector<Actor*>::const_iterator it = actorList.begin();
	while (it != actorList.end())
	{
		if ((*it)->getStatus() && (*it)->isAlien())
		{
			alienX = (*it)->getX();
			alienY = (*it)->getY();
			alienR = (*it)->getRadius();
			if (euclidian_dist(thisX, thisY, alienX, alienY) < (.75 * (thisR + alienR)))
			{
				return (*it);
			}

		}

		it++;
	}
	return NULL;
}
void StudentWorld::addAlien()
{
	current++;
}
void StudentWorld::killAlien()
{
	//current--;
	remainingAlienShips--;
	numAlienDestroyed++;
}
Actor* StudentWorld::getOneCollidingProjectile(const Actor* a) const
{
	double thisX = a->getX();
	double thisY = a->getY();
	double thisR = a->getRadius();
	double projX;
	double projY;
	double projR;
	vector<Actor*>::const_iterator it = actorList.begin();
	while (it != actorList.end())
	{
		if ((*it)->getStatus() && (*it)->isProj() && (*it)->isDamageableToPlayer())
		{
			projX = (*it)->getX();
			projY = (*it)->getY();
			projR = (*it)->getRadius();
			if (euclidian_dist(thisX, thisY, projX, projY) < (.75 * (thisR + projR)))
			{
				return (*it);
			}

		}

		it++;
	}
	return NULL;
}
Actor* StudentWorld::getPlayerProjectile(const Actor* a) const
{

	double thisX = a->getX();
	double thisY = a->getY();
	double thisR = a->getRadius();
	double projX;
	double projY;
	double projR;
	vector<Actor*>::const_iterator it = actorList.begin();
	while (it != actorList.end())
	{
		if ((*it)->getStatus() && (*it)->isProj() && !(*it)->isDamageableToPlayer())
		{
			projX = (*it)->getX();
			projY = (*it)->getY();
			projR = (*it)->getRadius();
			if (euclidian_dist(thisX, thisY, projX, projY) < (.75 * (thisR + projR)))
			{
				return (*it);
			}

		}

		it++;
	}
	return NULL;
}
NachenBlaster* StudentWorld::getPlayer() const
{
	return playerObject;
}
StudentWorld::~StudentWorld()
{
	this->cleanUp();
}
int StudentWorld::init()
{
	int randX;
	int randY;
	points = 0;
	current = 0;
	numAlienDestroyed = 0;
	remainingAlienShips = 6 + (4 * getLevel());
	lives = getLives();
	levelNum = getLevel();
	int numStars = 30;
	Actor* object;
	playerObject = new NachenBlaster(this);
	actorList.push_back(playerObject);
	for (int counter = 0; counter < numStars;)
	{
		randX = randInt(0, VIEW_WIDTH - 1);
		randY = randInt(0, VIEW_HEIGHT - 1);
		object = new Star(this, randX, randY);
		actorList.push_back(object);
		counter++;
	}
	//set the text
	string s = "Lives: " + std::to_string(lives) + "  Health: 100%  Score: " + std::to_string(points) + "  Level: " + std::to_string(levelNum) + "  Cabbages: 100%  Torpedoes: " + std::to_string(playerObject->getTorpedoes());
	setGameStatText(s);
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	playerObject->doSomething();
	if (numAlienDestroyed == (6 + 4 * levelNum) || remainingAlienShips == 0)
	{
		levelNum++;
		return GWSTATUS_FINISHED_LEVEL;
	}
	int randX;
	int randY;
	int randNum;
	Actor* object;

	randNum = randInt(1, 15);
	if (randNum == 1)
	{
		randX = VIEW_WIDTH - 1;
		randY = randInt(0, VIEW_HEIGHT - 1);
		object = new Star(this, randX, randY);
		actorList.push_back(object);
	}
	double min;
	double maxShips = 4 + (.5 * getLevel());
	if (maxShips < remainingAlienShips)
	{
		min = maxShips;
	}
	else
	{
		min = remainingAlienShips;
	}
	double s1;
	double s2;
	double s3;
	double s;
	if (current < min)
	{
		//current++;
		s1 = 60;
		s2 = 20 + (getLevel() * 5);
		s3 = 5 + (getLevel() * 10);
		s = s1 + s2 + s3;
		int rand = randInt(0, s);
		if (rand <= s1)
		{
			Actor* thisOne = new Smallgon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actorList.push_back(thisOne);

		}
		else if (rand <= (s1 + s2))
		{
			Actor* one = new Smoregon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actorList.push_back(one);
		}
		else
		{
			Actor* next = new Snagglegon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1));
			actorList.push_back(next);
		}
	}
	vector<Actor*>::iterator it = actorList.begin();
	while (it != actorList.end())
	{

		if ((*it)->getStatus())
		{
			(*it)->doSomething();
			if (!playerObject->getStatus())
			{
				return GWSTATUS_PLAYER_DIED;
			}
			if (numAlienDestroyed == (6 + 4 * levelNum))
			{
				levelNum++;
				return GWSTATUS_FINISHED_LEVEL;
			}
		}

		it++;
	}
	it = actorList.begin();
	while (it != actorList.end())
	{
		if (!(*it)->getStatus())
		{
			Actor* act = *it;
			it = actorList.erase(it);
			delete act;
		}
		else
		{
			it++;
		}
	}

	int healthPercent = 100 * playerObject->getHitPoints() / 50;
	int cabbagePercent = 100 * int(playerObject->getCabbagePoints() / 30);
	string sss = "Lives: " + std::to_string(lives) + "  Health: " + std::to_string(healthPercent) + "%  Score: " + std::to_string(points) + "  Level: " + std::to_string(levelNum) + "  Cabbages: " + std::to_string(cabbagePercent) + "%  Torpedoes: " + std::to_string(playerObject->getTorpedoes());
	setGameStatText(sss);

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	vector<Actor*>::iterator iter = actorList.begin();
	for (; iter != actorList.end();)
	{
		Actor* act = *iter;
		iter = actorList.erase(iter);
		delete act;
	}
}