#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
//#include "Actor.h"
#include <vector>
#include <string>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class NachenBlaster;
class StudentWorld : public GameWorld
{
public:
	StudentWorld(string assetDir);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	virtual ~StudentWorld();

	NachenBlaster* getPlayer() const;
	void addActor(Actor* a);
	void setPoints(int p);
	int getPoints() const;
	void addLife();
	Actor* getOneCollidingAlien(const Actor* a) const;
	void addAlien();
	void killAlien();
	void decCurrent()
	{
		current--;
	}
	Actor* getOneCollidingProjectile(const Actor* a) const;
	Actor* getPlayerProjectile(const Actor* a) const;
private:
	std::vector<Actor*> actorList;
	NachenBlaster* playerObject;
	int numAlienDestroyed;//how many killed
	int remainingAlienShips;//how many left to kill
	int lives;
	int levelNum;
	int points;
	int current;//on screen
};

#endif // STUDENTWORLD_H_