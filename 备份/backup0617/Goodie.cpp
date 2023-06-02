#include "Goodie.h"
#include "GameWorld.h"

Goodie::Goodie(int imageID, int x, int y, int direction, int layer,
	double size, GameWorld *world) : GameObject(imageID, x, y, direction,
		layer, size, world) {}

bool Goodie::is_enermy() { return false; }
bool Goodie::is_bullet() { return false; }
bool Goodie::can_bump() { return true; }
void Goodie::cause_damage(int)
{
	std::cout << "You can not invoke this in Goodie class!" <<
		std::endl;
}
bool Goodie::is_meteor() { return false; }

void Goodie::Update()
{
	if (!getstate())
		return;
	if (GetY() < 0)
	{
		setdeath();
		return;
	}
	DoDiffrently(); // Bump
}

/*
HP Goodie
*/

HP_Goodie::HP_Goodie(int x, int y, GameWorld *world) :
	Goodie(IMGID_HP_RESTORE_GOODIE, x, y, 0, 2, 0.5, world) {}

void HP_Goodie::DoDiffrently()
{
	if (findworld->Goodie_bump(this))
	{
		findworld->add_HP();
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
	MoveTo(GetX(), GetY() - 2);

	if (findworld->Goodie_bump(this))
	{
		findworld->add_HP();
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
}

/*
Powerup Goodie
*/

Powerup::Powerup(int x, int y, GameWorld *world) :
	Goodie(IMGID_POWERUP_GOODIE, x, y, 0, 2, 0.5, world) {}

void Powerup::DoDiffrently()
{
	if (findworld->Goodie_bump(this))
	{
		findworld->set_powerup(findworld->get_powerup() + 1);
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
	MoveTo(GetX(), GetY() - 2);

	if (findworld->Goodie_bump(this))
	{
		findworld->set_powerup(findworld->get_powerup() + 1);
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
}

/*
Meteor Goodie
*/

Meteor_Goodie::Meteor_Goodie(int x, int y, GameWorld *world) :
	Goodie(IMGID_METEOR_GOODIE, x, y, 0, 2, 0.5, world) {}

void Meteor_Goodie::DoDiffrently()
{
	if (findworld->Goodie_bump(this))
	{
		findworld->set_meteors(findworld->get_meteors() + 1);
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
	MoveTo(GetX(), GetY() - 2);

	if (findworld->Goodie_bump(this))
	{
		findworld->set_meteors(findworld->get_meteors() + 1);
		findworld->IncreaseScore(20);
		setdeath();
		return;
	}
}