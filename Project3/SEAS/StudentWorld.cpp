#include "StudentWorld.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{}

int StudentWorld::init()
{

    // Initialize the NachenBlaster
    m_player = new NachenBlaster(this);
    addActor(m_player);
    // initialize the stars
    int randX, randY;
    double randSize;
    for (int i = 0; i < 30; i++)
    {
        randX = randInt(0, VIEW_WIDTH - 1);
        randY = randInt(0, VIEW_HEIGHT - 1);
        randSize = randInt(5, 50) / 100.00;
        
        addActor(new Star(randX, randY, randSize));

    }  



    // Initialize the score board

    setGameStatText("Lives: " + to_string(getLives()) + "  Health: " + to_string(static_cast<int>(m_player->getHP() * 2)) + "\%  Score: " + to_string(getScore()) + "  Level: " + to_string(getLevel()) + "  Cabbages: " + to_string((m_player->getCabbage() / 30) * 100) + "%  Torpedoes: " + to_string(0));


    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    // reset stat text
    setGameStatText("Lives: " + to_string(getLives()) + "  Health: " + to_string(static_cast<int>(m_player->getHP() * 2)) + "\%  Score: " + to_string(getScore()) + "  Level: " + to_string(getLevel()) + "  Cabbages: " + to_string(static_cast<int>((m_player->getCabbage() / 30.0) * 100)) + "%  Torpedoes: " + to_string(0));

    // iterate through the actors and perform necessary actions
    for (vector<Actor*>::const_iterator iterator = m_actors.begin(); iterator != m_actors.end();)
    {
        if ( ! (*iterator)->isAlive())
        {
            Actor* temp = *iterator;
            iterator = m_actors.erase(iterator);
            delete temp;

        }
        else
        {
            (*iterator)->doSomething();
            iterator++;   
        }
    }

    // add stars

    if (randInt(1, 15) == 15)
        addActor(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), randInt(5, 50) / 100.0));




    
    if (!m_player->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }   
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (vector<Actor*>::const_iterator iterator = m_actors.begin(); iterator != m_actors.end();)
    {
        Actor* temp = *iterator;
        iterator = m_actors.erase(iterator);
        delete temp;

    }

    delete m_player;
}

void StudentWorld::addActor(Actor* act)
{
    m_actors.push_back(act);
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
