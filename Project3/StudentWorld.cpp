#include "StudentWorld.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir), m_numKilled(0), m_numShips(0)
{}

int StudentWorld::init()
{
    m_numKilled = 0;
    m_numShips = 0;
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

    // iterate through the actors and perform necessary actions
    for (vector<Actor*>::const_iterator iterator = m_actors.begin(); iterator != m_actors.end();iterator++)    
    {
        if (! (m_player)->isAlive())
        {
            decLives();
            m_numShips = 0;
            m_numKilled = 0;
            cleanUp();
            return GWSTATUS_PLAYER_DIED;
        }
        if ((*iterator)->isAlive())
            (*iterator)->doSomething();
    }

    // add stars

    if (randInt(1, 15) == 15)
        addActor(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), randInt(5, 50) / 100.0));

    // add ships
    int T = 6 + (4 * getLevel());
    int D = m_numKilled;
    int R = T - D;
    int M = 4 + (.5 * getLevel());


    if (D == T)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;  
    }
    else if (m_numShips < min(R, M)) 
    {
        int S1 = 60;
        int S2 = 20 + getLevel() * 5;
        int S3 = 5 + getLevel() * 10;

        int S = S1 + S2 + S3;
        S2 = S1 + S2;
        int check = randInt(1, S);
        
        if (check <= S1)
            addActor(new Smallgon(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this));
        else if (check <= S2)
            addActor(new Smoregon(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this));
        else
            addActor(new Snagglegon(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), this));
        

    }


    // Check for collisions or ship




    // Check for dead actors
    for (vector<Actor*>::const_iterator iterator = m_actors.begin(); iterator != m_actors.end();)
    {

        if (! (*iterator)->isAlive())
        {
            Actor* temp = *iterator;
            iterator = m_actors.erase(iterator);
            delete temp;
        }
        else
            iterator++;
    }

        // reset stat text
    setGameStatText("Lives: " + to_string(getLives()) + "  Health: " + to_string(static_cast<int>(m_player->getHP() * 2)) + "\%  Score: " + to_string(getScore()) + "  Level: " + to_string(getLevel()) + "  Cabbages: " + to_string(static_cast<int>((m_player->getCabbage() / 30.0) * 100)) + "%  Torpedoes: " + to_string(0));

    
     
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

}

void StudentWorld::addActor(Actor* act)
{
    m_actors.push_back(act);

}

void StudentWorld::decShips()
{
    m_numShips--;
}

void StudentWorld::incShips()
{
    m_numShips++;
}

void StudentWorld::incKills()
{
    m_numKilled++;
}

NachenBlaster* StudentWorld::getPlayer()
{
    return m_player;
}

vector<Actor*>* StudentWorld::getActors()
{
    return &m_actors;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
