#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
#include <cstdlib>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual ~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	void addActor(Actor* act);
	void decShips();
	void incShips();
	void incKills();
	NachenBlaster* getPlayer();
	list<Actor*>* getActors();

private:
	list<Actor*> m_actors;
	NachenBlaster* m_player;
	int m_numKilled;
	int m_numShips;
};

#endif // STUDENTWORLD_H_
