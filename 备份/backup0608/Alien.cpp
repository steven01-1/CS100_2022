#include "Alien.h"
#include "GameWorld.h"

Alien::Alien(int imageID, int x, int y, int direction, int layer,
	double size, GameWorld *world, int energy, int HP, int effect, int strategy,
	int strategy_time, int speed) : GameObject(imageID, x, y, direction, layer, size, world),
	energy(energy), HP(HP), effect(effect), strategy(strategy),
	strategy_time(strategy_time), speed(speed) {}


int Alien::get_energy()  const { return energy; }
int Alien::get_HP()  const { return HP; }
void Alien::set_energy(int e) { energy = e; }
void Alien::set_HP(int hp) { HP = hp; }
int Alien::get_effect()const { return effect; }
int Alien::get_strategy() const { return strategy; }
int Alien::get_strategy_time() const { return strategy_time; }
void Alien::set_strategy(int s) { strategy = s; }
void Alien::set_strategy_time(int t) { strategy_time = t;}

bool Alien::is_enermy() { return true; }
bool Alien::is_bullet() { return false; }
bool Alien::can_bump() { return true; }
void Alien::cause_damage(int d) { HP -= d;}


void Alien::Update()
{
	if (!getstate())
		return;
	if (GetY() < 0 || GetY() >= WINDOW_HEIGHT)
	{
		setdeath();
		return;
	}
	// bomp
	if (findworld->Alien_bump(this)) // dawnbreaker, meteors, blue bullet
	{
		if (HP <= 0)
		{
			setdeath();
			show_death();
			return;
		}
	}
	DoDiffrently();
	// change strategy
	if (strategy_time <= 0)
	{
		strategy = randInt(1, 3);
		strategy_time = randInt(10, 50);
	}
	else if (GetX() < 0)
	{
		strategy = 3;
		strategy_time = randInt(10, 50);
	}
	else if (GetX() >= WINDOW_WIDTH)
	{
		strategy = 2;
		strategy_time = randInt(10, 50);
	}
	// move
	--strategy_time;
	int n_y = GetY() - speed;
	int n_x = 0;
	if (strategy == 2)
		n_x = GetX() - speed;
	else if (strategy == 3)
		n_x = GetX() + speed;
	else if (strategy == 1)
		n_x = GetX();
	MoveTo(n_x, n_y);
	// bomp
	if (findworld->Alien_bump(this)) // dawnbreaker, meteors, blue bullet
	{
		if (HP <= 0)
		{
			setdeath();
			show_death();
			return;
		}
	}
}

/*
Alphatron
*/

Alpha::Alpha(int x, int y, GameWorld *world, int HP, int effect, int speed) : 
	Alien(IMGID_ALPHATRON
	, x, y, 180, 0, 1.0, world, 25, HP, effect, 0, 0, speed) {}

void Alpha::show_death()
{
	findworld->set_explosion(GetX(), GetY());
	findworld->IncreaseScore(50);
	findworld->add_des_num();
}

void Alpha::DoDiffrently()
{
	if (findworld->get_myX() - GetX() <= 10 && findworld->get_myX() - GetX() >= -10)
		if (get_energy() == 25)
			if (randInt(1, 4) == 1)
			{
				set_energy(0);
				findworld->set_Red_Bullet(GetX(), GetY(), get_effect());
			}
	if (get_energy() < 25)
		set_energy(get_energy() + 1);
}

/*
Sigmatron
*/
Sigma::Sigma(int x, int y, GameWorld *world, int HP, int speed) : 
	Alien(IMGID_SIGMATRON, x, y, 180, 0, 1.0, world, 0, HP, 0, 0, 0, speed) {}

void Sigma::show_death()
{

}

void Sigma::DoDiffrently()
{

}

