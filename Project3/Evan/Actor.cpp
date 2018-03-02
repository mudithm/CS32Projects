#include "Actor.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
double euclidian_dist(double thisX, double thisY, double otherX, double otherY)
{
	double xDiff = thisX - otherX;
	double yDiff = thisY - otherY;
	double dist = pow(xDiff, 2) + pow(yDiff, 2);
	dist = sqrt(dist);
	return dist;

Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double size, int depth)
	: GraphObject(imageID, startX, startY, startDirection, size, depth)
{
	m_alive = true;
	m_world = world;
}
StudentWorld* Actor::getWorld() const
{
	return m_world;
}
void Actor::setWorld(StudentWorld* newWorld)
{
	m_world = newWorld;
}
bool Actor::getStatus() const
{
	return m_alive;
}
void Actor::setStatus(bool i)
{
	m_alive = i;
}



Star::Star(StudentWorld* newWorld, double xPos, double yPos) :
	Actor(newWorld, IID_STAR, xPos, yPos, 0, (double(randInt(5, 50)) / 100), 3)
{
}
void Star::doSomething()
{
	double newX = getX() - 1;
	double newY = getY();
	moveTo(newX, newY);
	if (newX < 0)
	{

		setStatus(false);
	}

}
Actor::~Actor()
{
}
bool Actor::isDamageableToPlayer() const
{
	return false;
}
int Actor::damageToPlayer() const
{
	return 0;
}
int Actor::getHitPoints() const
{
	return hitPoints;
}
void Actor::setHitPoints(int points)
{
	hitPoints = points;
	if (hitPoints >= 50)
	{
		hitPoints = 50;
	}
}
bool Actor::isProj() const
{
	return false;
}
bool Actor::isAlien() const
{
	return false;
}
NachenBlaster::NachenBlaster(StudentWorld* newWorld)
	: Actor(newWorld, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0)
{
	setHitPoints(50);
	cabbageEnergyPoints = 30;
	flatTorpedoes = 0;
}
void Actor::sufferDamage(double amt, int cause)
{
	if (cause == 0)
	{
		hitPoints = hitPoints - amt;
		if (hitPoints <= 0)
		{
			setStatus(false);
		}
	}
	else if (cause == 1)
	{
		hitPoints = hitPoints - amt;
		if (hitPoints <= 0)
		{
			setStatus(false);
		}
	}
}
int NachenBlaster::getCabbagePoints() const
{
	return cabbageEnergyPoints;
}
int NachenBlaster::getTorpedoes() const
{
	return flatTorpedoes;
}
void NachenBlaster::addTorpedoes(int p)
{
	flatTorpedoes = flatTorpedoes + p;
}
void NachenBlaster::addHitPoints(int points)
{
	int hit = getHitPoints();
	hit = hit + points;

	if (hit > 50)
	{
		setHitPoints(50);
	}
	else
	{
		setHitPoints(hit);
	}
}
void NachenBlaster::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	else
	{
		int ch;
		if (getWorld()->getKey(ch))
		{

			double newX;
			double newY;
			switch (ch)
			{
				Actor* proj;
				Actor* alien;
			case KEY_PRESS_SPACE:
				if (cabbageEnergyPoints >= 5)
				{
					Actor* cab = new Cabbage(getWorld(), getX() + 12, getY());
					getWorld()->addActor(cab);
					getWorld()->playSound(SOUND_PLAYER_SHOOT);
					cabbageEnergyPoints = cabbageEnergyPoints - 5;

				}
				break;
			case KEY_PRESS_TAB:
				if (flatTorpedoes > 0)
				{
					Actor* torp = new PlayerLaunchedTorpedo(getWorld(), getX() + 12, getY());
					getWorld()->addActor(torp);
					getWorld()->playSound(SOUND_TORPEDO);
					flatTorpedoes = flatTorpedoes - 1;
				}
				break;
			case KEY_PRESS_UP:
				newX = getX();
				newY = 6 + getY();
				if (newY >= 0 && newY < VIEW_HEIGHT)
				{
					moveTo(newX, newY);
				}
				else
					break;


				proj = getWorld()->getOneCollidingProjectile(this);
				if (proj != NULL)
				{
					sufferDamage(proj->damageToPlayer(), HIT_BY_PROJECTILE);
					getWorld()->playSound(SOUND_BLAST);

				}
				alien = getWorld()->getOneCollidingAlien(this);
				if (alien != NULL)
				{
					sufferDamage(alien->damageToPlayer(), HIT_BY_SHIP);
					getWorld()->playSound(SOUND_DEATH);
					Explosion* expl = new Explosion(getWorld(), getX(), getY());
					getWorld()->addActor(expl);
					alien->setStatus(false);
					getWorld()->killAlien();

				}
				break;
			case KEY_PRESS_DOWN:
				newX = getX();
				newY = getY() - 6;
				if (newY >= 0 && newY < VIEW_HEIGHT)
				{
					moveTo(newX, newY);
				}
				else
					break;

				proj = getWorld()->getOneCollidingProjectile(this);
				if (proj != NULL)
				{
					sufferDamage(proj->damageToPlayer(), HIT_BY_PROJECTILE);
					getWorld()->playSound(SOUND_BLAST);

				}
				alien = getWorld()->getOneCollidingAlien(this);
				if (alien != NULL)
				{
					sufferDamage(alien->damageToPlayer(), HIT_BY_SHIP);
					getWorld()->playSound(SOUND_DEATH);
					Explosion* expl = new Explosion(getWorld(), getX(), getY());
					getWorld()->addActor(expl);
					alien->setStatus(false);
					getWorld()->killAlien();

				}
				break;
			case KEY_PRESS_LEFT:
				newX = getX() - 6;
				newY = getY();
				if (newX >= 0 && newX < VIEW_WIDTH)
				{
					moveTo(newX, newY);
				}
				else
					break;

				proj = getWorld()->getOneCollidingProjectile(this);
				if (proj != NULL)
				{
					sufferDamage(proj->damageToPlayer(), HIT_BY_PROJECTILE);
					getWorld()->playSound(SOUND_BLAST);

				}
				alien = getWorld()->getOneCollidingAlien(this);
				if (alien != NULL)
				{
					sufferDamage(alien->damageToPlayer(), HIT_BY_SHIP);
					getWorld()->playSound(SOUND_DEATH);
					Explosion* expl = new Explosion(getWorld(), getX(), getY());
					getWorld()->addActor(expl);
					alien->setStatus(false);
					getWorld()->killAlien();

				}
				break;
			case KEY_PRESS_RIGHT:
				newX = getX() + 6;
				newY = getY();
				if (newX >= 0 && newX < VIEW_WIDTH)
				{
					moveTo(newX, newY);
				}
				else
					break;

				proj = getWorld()->getOneCollidingProjectile(this);
				if (proj != NULL)
				{
					sufferDamage(proj->damageToPlayer(), HIT_BY_PROJECTILE);
					getWorld()->playSound(SOUND_BLAST);

				}
				alien = getWorld()->getOneCollidingAlien(this);
				if (alien != NULL)
				{
					sufferDamage(alien->damageToPlayer(), HIT_BY_SHIP);
					getWorld()->playSound(SOUND_DEATH);
					Explosion* expl = new Explosion(getWorld(), getX(), getY());
					getWorld()->addActor(expl);
					alien->setStatus(false);
					getWorld()->killAlien();

				}
				break;
			default:
				break;
			}
		}
		cabbageEnergyPoints++;
		if (cabbageEnergyPoints >= 30)
		{
			cabbageEnergyPoints = 30;
		}
	}
}
Explosion::Explosion(StudentWorld* newWorld, double x, double y) : Actor(newWorld, IID_EXPLOSION, x, y, 0, 1, 0)
{
	ticks = 0;
}
void Explosion::doSomething()
{
	if (ticks == 4)
	{
		setStatus(false);
		return;
	}
	double size = getSize();
	size = size * 1.5;
	setSize(size);
	ticks++;
}
Cabbage::Cabbage(StudentWorld* newWorld, double x, double y) : Projectile(newWorld, x, y, IID_CABBAGE, 0)
{

}
void Cabbage::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	else
	{
		double xCord = getX();
		double yCord = getY();
		if (xCord >= VIEW_WIDTH)
		{
			setStatus(false);
			return;
		}
	}
	Actor* a = getWorld()->getOneCollidingAlien(this);
	if (a != NULL)
	{
		a->sufferDamage(2, HIT_BY_PROJECTILE);

		if (a->getHitPoints() <= 0)
		{
			getWorld()->playSound(SOUND_DEATH);
			Explosion* thisO = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(thisO);
			if (a->damageToPlayer() == 5)
			{
				getWorld()->setPoints(getWorld()->getPoints() + 250);
			}
			else
			{
				getWorld()->setPoints(getWorld()->getPoints() + 1000);
			}
			a->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;

	}
	moveTo(getX() + 8, getY());
	int dir = getDirection();
	dir = dir + 20;
	if (dir > 359)
	{
		dir = dir - 360;
	}
	setDirection(dir);
	a = getWorld()->getOneCollidingAlien(this);
	if (a != NULL)
	{
		a->sufferDamage(2, HIT_BY_PROJECTILE);

		if (a->getHitPoints() <= 0)
		{
			getWorld()->playSound(SOUND_DEATH);
			Explosion* thisO = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(thisO);
			if (a->damageToPlayer() == 5)
			{
				getWorld()->setPoints(getWorld()->getPoints() + 250);
			}
			else
			{
				getWorld()->setPoints(getWorld()->getPoints() + 1000);
			}
			a->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;

	}

}
Turnip::Turnip(StudentWorld* newWorld, double x, double y) : Projectile(newWorld, x, y, IID_TURNIP, 0)
{
}
void Turnip::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	else
	{
		double xCord = getX();
		double yCord = getY();
		if (xCord < 0)
		{
			setStatus(false);
			return;
		}
	}
	double xCord = getX();
	double yCord = getY();
	double rad = getRadius();
	double xPlayer = getWorld()->getPlayer()->getX();
	double yPlayer = getWorld()->getPlayer()->getY();
	double radPlayer = getWorld()->getPlayer()->getRadius();
	if (euclidian_dist(xCord, yCord, xPlayer, yPlayer) < .75 * (rad + radPlayer))
	{
		getWorld()->getPlayer()->sufferDamage(2, 1);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->playSound(SOUND_BLAST);
			getWorld()->decLives();
			getWorld()->getPlayer()->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;
	}

	xCord = xCord - 6;
	int dir = getDirection();
	dir = dir + 20;
	if (dir > 359)
	{
		dir = dir - 360;
	}
	moveTo(xCord, getY());
	setDirection(dir);
	rad = getRadius();
	radPlayer = getWorld()->getPlayer()->getRadius();
	if (euclidian_dist(xCord, yCord, xPlayer, yPlayer) < .75 * (rad + radPlayer))
	{
		getWorld()->getPlayer()->sufferDamage(2, 1);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->playSound(SOUND_BLAST);
			getWorld()->decLives();
			getWorld()->getPlayer()->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;
	}
}
void Smallgon::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() < 0)
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(5, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
			//return;

		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 250;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);

	}
	Actor* playerProj;
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 250);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}
	if (getLength() == 0 || getY() >= 255 || getY() <= 0)
	{
		if (getY() >= VIEW_HEIGHT - 1)
		{
			travelDirection = -2;
		}
		else if (getY() <= 0)
		{
			travelDirection = 1;
		}
		else if (getLength() == 0)
		{
			int rand = randInt(1, 3);
			switch (rand)
			{
			case 1:
				travelDirection = 3;
				break;
			case 2:
				travelDirection = 1;
				break;
			case 3:
				travelDirection = -2;
				break;
			}

		}
		setLength(randInt(1, 32));

	}
	double yDifference = thisY - nachY;
	if (nachX < thisX && abs(yDifference) <= 4)
	{
		double numerator = ((20 / getWorld()->getLevel()) + 5);
		int rand = randInt(1, numerator);
		if (rand == 1)
		{
			Projectile* turn;
			turn = new Turnip(getWorld(), getX() - 14, getY());
			getWorld()->addActor(turn);
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
	}
	if (travelDirection == 1)
	{
		thisX = thisX - getSpeed();
		thisY = thisY + getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	else if (travelDirection == -2)
	{
		thisX = thisX - getSpeed();
		thisY = thisY - getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	else if (travelDirection == 3)
	{
		thisX = thisX - getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(5, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
			//return;
		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 250;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);

	}
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 250);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}

}
int AlienLaunchedTorpedo::damageToPlayer() const
{
	return 8;
}
bool AlienLaunchedTorpedo::isDamageableToPlayer() const
{
	return true;
}
void AlienLaunchedTorpedo::doSomething()
{

	if (!getStatus())
	{
		return;
	}
	else
	{
		double xCord = getX();
		double yCord = getY();
		if (xCord < 0 || xCord >= VIEW_WIDTH)
		{
			setStatus(false);
			return;
		}
	}
	double xCord = getX();
	double yCord = getY();
	double rad = getRadius();
	double xPlayer = getWorld()->getPlayer()->getX();
	double yPlayer = getWorld()->getPlayer()->getY();
	double radPlayer = getWorld()->getPlayer()->getRadius();
	if (euclidian_dist(xCord, yCord, xPlayer, yPlayer) < .75 * (rad + radPlayer))
	{
		getWorld()->getPlayer()->sufferDamage(8, 1);
		getWorld()->playSound(SOUND_BLAST);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
		}
		setStatus(false);
		return;
	}
	xCord = xCord - 8;
	moveTo(xCord, getY());
	rad = getRadius();
	radPlayer = getWorld()->getPlayer()->getRadius();
	if (euclidian_dist(xCord, yCord, xPlayer, yPlayer) < .75 * (rad + radPlayer))
	{
		getWorld()->getPlayer()->sufferDamage(8, 1);
		getWorld()->playSound(SOUND_BLAST);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
		}
		setStatus(false);
		return;
	}
}
int PlayerLaunchedTorpedo::damageToPlayer() const
{
	return 8;
}
void PlayerLaunchedTorpedo::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	else
	{
		double xCord = getX();
		double yCord = getY();
		if (xCord >= VIEW_WIDTH || xCord < 0)
		{
			setStatus(false);
			return;
		}
	}
	Actor* a = getWorld()->getOneCollidingAlien(this);
	if (a != NULL)
	{
		a->sufferDamage(8, HIT_BY_PROJECTILE);
		if (a->getHitPoints() <= 0)
		{
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Explosion* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			if (a->damageToPlayer() == 5)
			{
				getWorld()->setPoints(getWorld()->getPoints() + 250);
			}
			else
			{
				getWorld()->setPoints(getWorld()->getPoints() + 1000);
			}
			a->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;
	}
	moveTo(getX() + 8, getY());

	a = getWorld()->getOneCollidingAlien(this);
	if (a != NULL)
	{
		a->sufferDamage(8, HIT_BY_PROJECTILE);
		if (a->getHitPoints() <= 0)
		{
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Explosion* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			if (a->damageToPlayer() == 5)
			{
				getWorld()->setPoints(getWorld()->getPoints() + 250);
			}
			else
			{
				getWorld()->setPoints(getWorld()->getPoints() + 1000);
			}
			a->setStatus(false);
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
		setStatus(false);
		return;
	}
}
void Smoregon::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() < 0)
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(5, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
			//return;
		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 250;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);
		int rand = randInt(1, 3);
		if (rand == 1)
		{
			int randNum = randInt(1, 2);
			if (randNum == 1)
			{
				Actor* newRepair = new RepairGoodie(getWorld(), thisX, thisY);
				getWorld()->addActor(newRepair);

			}
			else if (randNum == 2)
			{
				Actor* newTorpedo = new TorpedoGoodie(getWorld(), thisX, thisY);
				getWorld()->addActor(newTorpedo);
			}
		}

	}
	Actor* playerProj;
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 250);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			int num = randInt(1, 3);
			if (num == 1)
			{
				int num2 = randInt(1, 2);
				if (num2 == 1)
				{
					Actor* goodie = new RepairGoodie(getWorld(), getX(), getY());
					getWorld()->addActor(goodie);
				}
				else if (num2 == 2)
				{
					Actor* goodie = new TorpedoGoodie(getWorld(), getX(), getY());
					getWorld()->addActor(goodie);
				}
			}
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}
	if (getLength() == 0 || getY() >= 255 || getY() <= 0)
	{
		if (getY() >= VIEW_HEIGHT - 1)
		{
			travelDirection = -2;
		}
		else if (getY() <= 0)
		{
			travelDirection = 1;
		}
		else if (getLength() == 0)
		{
			int rand = randInt(1, 3);
			switch (rand)
			{
			case 1:
				travelDirection = 3;
				break;
			case 2:
				travelDirection = 1;
				break;
			case 3:
				travelDirection = -2;
				break;
			}

		}
		setLength(randInt(1, 32));

	}
	double yDifference = thisY - nachY;
	if (nachX < thisX && abs(yDifference) <= 4)
	{
		double numerator = ((20 / getWorld()->getLevel()) + 5);
		int rand = randInt(1, numerator);
		if (rand == 1)
		{
			Projectile* hey = new Turnip(getWorld(), getX() - 14, getY());
			getWorld()->addActor(hey);
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
		numerator = ((20 / getWorld()->getLevel()) + 5);
		rand = randInt(1, numerator);
		if (rand == 1)
		{
			travelDirection = 3;
			setLength(VIEW_WIDTH);
			setSpeed(5);
		}
	}
	if (travelDirection == 1)
	{
		thisX = thisX - getSpeed();
		thisY = thisY + getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	else if (travelDirection == -2)
	{
		thisX = thisX - getSpeed();
		thisY = thisY - getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	else if (travelDirection == 3)
	{
		thisX = thisX - getSpeed();
		moveTo(thisX, thisY);
		setLength(getLength() - 1);
	}
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(5, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->getPlayer()->setStatus(false);
			getWorld()->decLives();
			//return;
		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 250;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);
		int rand = randInt(1, 3);
		if (rand == 1)
		{
			int randNum = randInt(1, 2);
			if (randNum == 1)
			{
				Actor* newRepair = new RepairGoodie(getWorld(), thisX, thisY);
				getWorld()->addActor(newRepair);

			}
			else if (randNum == 2)
			{
				Actor* newTorpedo = new TorpedoGoodie(getWorld(), thisX, thisY);
				getWorld()->addActor(newTorpedo);
			}
		}
	}
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 250);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			int num = randInt(1, 3);
			if (num == 1)
			{
				int num2 = randInt(1, 2);
				if (num2 == 1)
				{
					Actor* goodie = new RepairGoodie(getWorld(), getX(), getY());
					getWorld()->addActor(goodie);
				}
				else if (num2 == 2)
				{
					Actor* goodie = new TorpedoGoodie(getWorld(), getX(), getY());
					getWorld()->addActor(goodie);
				}
			}
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}

}

void Snagglegon::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() < 0)
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(15, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->decLives();
			getWorld()->getPlayer()->setStatus(false);
			//return;
		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 1000;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);
		int rand = randInt(1, 6);
		if (rand == 1)
		{
			Actor* extraLife = new ExtraLifeGoodie(getWorld(), thisX, thisY);
			getWorld()->addActor(extraLife);
		}

	}
	Actor* playerProj;
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 1000);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			int rand = randInt(1, 6);
			if (rand == 1)
			{
				Goodie* it = new ExtraLifeGoodie(getWorld(), getX(), getY());
				getWorld()->addActor(it);
			}
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}
	if (getY() >= 255 || getY() <= 0)
	{
		if (getY() >= VIEW_HEIGHT - 1)
		{
			travelDirection = -2;
		}
		else if (getY() <= 0)
		{
			travelDirection = 1;
		}


	}
	double yDifference = thisY - nachY;
	if (nachX < thisX && abs(yDifference) <= 4)
	{
		double numerator = ((15 / getWorld()->getLevel()) + 10);
		int rand = randInt(1, numerator);
		if (rand == 1)
		{
			Projectile* hey = new AlienLaunchedTorpedo(getWorld(), getX() - 14, getY());
			getWorld()->addActor(hey);
			getWorld()->playSound(SOUND_TORPEDO);
			return;
		}
	}
	if (travelDirection == 1)
	{
		thisX = thisX - getSpeed();
		thisY = thisY + getSpeed();
		moveTo(thisX, thisY);
	}
	else if (travelDirection == -2)
	{
		thisX = thisX - getSpeed();
		thisY = thisY - getSpeed();
		moveTo(thisX, thisY);
	}

	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->getPlayer()->sufferDamage(15, 0);
		if (getWorld()->getPlayer()->getHitPoints() <= 0)
		{
			getWorld()->decLives();
			getWorld()->getPlayer()->setStatus(false);
			//return;
		}
		setStatus(false);
		getWorld()->killAlien();
		int points = getWorld()->getPoints();
		points = points + 1000;
		getWorld()->setPoints(points);
		getWorld()->playSound(SOUND_DEATH);
		Actor* newExplosion = new Explosion(getWorld(), thisX, thisY);
		getWorld()->addActor(newExplosion);
		int rand = randInt(1, 6);
		if (rand == 1)
		{
			Actor* extraLife = new ExtraLifeGoodie(getWorld(), thisX, thisY);
			getWorld()->addActor(extraLife);
		}

	}
	playerProj = getWorld()->getPlayerProjectile(this);
	if (playerProj != NULL)
	{
		sufferDamage(playerProj->damageToPlayer(), HIT_BY_PROJECTILE);
		if (getHitPoints() <= 0)
		{
			getWorld()->setPoints(getWorld()->getPoints() + 1000);
			setStatus(false);
			getWorld()->killAlien();
			getWorld()->playSound(SOUND_DEATH);
			Actor* expl = new Explosion(getWorld(), getX(), getY());
			getWorld()->addActor(expl);
			int rand = randInt(1, 6);
			if (rand == 1)
			{
				Goodie* it = new ExtraLifeGoodie(getWorld(), getX(), getY());
				getWorld()->addActor(it);
			}
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
		}
	}

}
void ExtraLifeGoodie::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() >= 0 && getX() < VIEW_WIDTH && getY() >= 0 && getY() < VIEW_HEIGHT)
	{
	}
	else
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->addLife();
		return;
	}
	thisX = thisX - .75;
	thisY = thisY - .75;
	moveTo(thisX, thisY);
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->addLife();
		return;
	}
}
void RepairGoodie::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() >= 0 && getX() < VIEW_WIDTH && getY() >= 0 && getY() < VIEW_HEIGHT)
	{
	}
	else
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->getPlayer()->setHitPoints(getWorld()->getPlayer()->getHitPoints() + 10);
		return;
	}
	thisX = thisX - .75;
	thisY = thisY - .75;
	moveTo(thisX, thisY);
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->getPlayer()->setHitPoints(getWorld()->getPlayer()->getHitPoints() + 10);
		return;
	}
}
void TorpedoGoodie::doSomething()
{
	if (!getStatus())
	{
		return;
	}
	if (getX() >= 0 && getX() < VIEW_WIDTH && getY() >= 0 && getY() < VIEW_HEIGHT)
	{
	}
	else
	{
		setStatus(false);
		return;
	}
	double thisX = getX();
	double thisY = getY();
	double thisRadius = getRadius();
	double nachX = getWorld()->getPlayer()->getX();
	double nachY = getWorld()->getPlayer()->getY();
	double nachRad = getWorld()->getPlayer()->getRadius();
	////////////////////////////////////////////////
	//double cabbageX = getWorld()->
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->getPlayer()->addTorpedoes(5);
		return;
	}
	thisX = thisX - .75;
	thisY = thisY - .75;
	moveTo(thisX, thisY);
	if (euclidian_dist(thisX, thisY, nachX, nachY) < .75 * (thisRadius + nachRad))
	{
		getWorld()->setPoints(getWorld()->getPoints() + 100);
		setStatus(false);
		getWorld()->playSound(SOUND_GOODIE);
		getWorld()->getPlayer()->addTorpedoes(5);
		return;
	}
}
