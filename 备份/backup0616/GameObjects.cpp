#include "GameObjects.h"
#include "GameWorld.h"


////////////
//GameObject
//////////////
GameObject::GameObject(int imageID, int x, int y, int direction, int layer,
                       double size, GameWorld* world)
    : ObjectBase(imageID, x, y, direction, layer, size), state(true),
      findworld(world){}


bool GameObject::getstate() const { return state; }
void GameObject::setdeath() { state = false; }
bool GameObject::is_meteor() { return false; }

/////////////////
//Dawnbreaker
//////////////
Dawnbreaker::Dawnbreaker(GameWorld* g)
    : GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0, g), energy(10), HP(100) {}
///////// 2147483647
// delete me
////////////


bool Dawnbreaker::is_enermy() { return false; }
bool Dawnbreaker::is_bullet() { return false; }
bool Dawnbreaker::can_bump() { return true; }

int Dawnbreaker::get_energy() { return energy; }

int Dawnbreaker::get_HP() { return HP; }

void Dawnbreaker::set_energy(int n_energy) { energy = n_energy; }

void Dawnbreaker::set_HP(int n_HP) { HP = n_HP; }

bool Dawnbreaker::is_meteor() { return false; }

void Dawnbreaker::cause_damage(int d)
{
  std::cout << "You need not invoke this in Dawnbreaker class"
    << std::endl;
}


void Dawnbreaker::Update()
{
  if (HP <= 0)
    setdeath();
  if (!getstate()) // death
    return;
  // move
  if (GetY() + 4 <= WINDOW_HEIGHT - 1 && findworld->GetKey(KeyCode::UP))
    MoveTo(GetX(), GetY() + 4);
  if ((GetY() - 4) >= 50 && findworld->GetKey(KeyCode::DOWN))
    MoveTo(GetX(), GetY() - 4);
  if (GetX() - 4 >= 0 && findworld->GetKey(KeyCode::LEFT))
    MoveTo(GetX() - 4, GetY());
  if (GetX() + 4 <= WINDOW_WIDTH - 1 && findworld->GetKey(KeyCode::RIGHT))
    MoveTo(GetX() + 4, GetY());
  // launch
  if (get_energy() >= 10 && findworld->GetKey(KeyCode::FIRE1))
  {
    findworld->set_bullet(GetX(), GetY(), 
      0.5 + 0.1 * findworld->get_powerup(), 5 + 3 * findworld->get_powerup());
    energy -= 10;
  }

  if (findworld->GetKeyDown(KeyCode::FIRE2) && findworld->get_meteors())
  {
    findworld->set_meteors(findworld->get_meteors() - 1);
    findworld->set_meteor(GetX(), GetY());
  }

  // recover energy
  if (get_energy() < 10)
    set_energy(get_energy() + 1);
}

/////////////////
//Projectile
/////////////////

Projectile::Projectile(int imageID, int x, int y, int direction, int layer,
                       double size, GameWorld* world, double effect)
    : GameObject(imageID, x, y, direction, layer, size, world), effect(effect)
{}

int Projectile::get_effect() const { return effect; }

void Projectile::Update()
{
  if (!getstate())
    return;
  if (GetY() >= WINDOW_HEIGHT || GetY() < 0)
  {
    setdeath();
    return;
  }
  DoDiffrently();
}


///////////
//Alien
////////////
Alien::Alien(int imageID, int x, int y, int direction, int layer,
	double size, GameWorld *world, int energy, int HP, int effect, int strategy,
	int strategy_time, int speed) : GameObject(imageID, x, y, direction, layer, size, world),
	energy(energy), HP(HP), effect(effect), strategy(strategy),
	strategy_time(strategy_time), speed(speed)
{
}


int Alien::get_energy()  const { return energy; }
int Alien::get_HP()  const { return HP; }
void Alien::set_energy(int e) { energy = e; }
void Alien::set_HP(int hp) { HP = hp; }
int Alien::get_effect()const { return effect; }
int Alien::get_strategy() const { return strategy; }
int Alien::get_strategy_time() const { return strategy_time; }
void Alien::set_strategy(int s) { strategy = s; }
void Alien::set_strategy_time(int t) { strategy_time = t; }
void Alien::set_speed(int s) { speed = s; }

bool Alien::is_enermy() { return true; }
bool Alien::is_bullet() { return false; }
bool Alien::can_bump() { return true; }
bool Alien::is_meteor() { return false; }
void Alien::cause_damage(int d) { HP -= d; }


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
		, x, y, 180, 0, 1.0, world, 25, HP, effect, 0, 0, speed)
{
}

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
	Alien(IMGID_SIGMATRON, x, y, 180, 0, 1.0, world, 0, HP, 0, 0, 0, speed)
{
}

void Sigma::show_death()
{
	findworld->set_explosion(GetX(), GetY());
	findworld->IncreaseScore(100);
	findworld->add_des_num();
	if (randInt(1, 5) == 1) // drop a goodie 
	{
		findworld->set_HP_Goodie(GetX(), GetY());
	}
}

void Sigma::DoDiffrently()
{
	if (GetX() - findworld->get_myX() <= 10 &&
		GetX() - findworld->get_myX() >= -10)
	{
		set_strategy(1);
		set_strategy_time(WINDOW_HEIGHT);
		set_speed(10);
	}
}
/*
Omegatron
*/
Omega::Omega(int x, int y, GameWorld *world, int HP, int effect, int speed) :
	Alien(IMGID_OMEGATRON, x, y, 180, 0, 1.0, world, 50, HP, effect,
		0, 0, speed)
{
}

void Omega::DoDiffrently()
{
	if (get_energy() == 50)
	{
		findworld->set_Red_Bullet(GetX(), GetY(), get_effect(), 162);
		findworld->set_Red_Bullet(GetX(), GetY(), get_effect(), 198);
		set_energy(0);
	}
	if (get_energy() < 50)
		set_energy(get_energy() + 1);
}

void Omega::show_death()
{
	findworld->set_explosion(GetX(), GetY());
	findworld->IncreaseScore(200);
	findworld->add_des_num();
	if (randInt(1, 5) <= 2)
	{
		if (randInt(1, 5) == 1) // meteor
		{
			findworld->set_Meteor_Goodie(GetX(), GetY());
		}
		else // power up
		{
			findworld->set_Powerup_Goodie(GetX(), GetY());
		}
	}
}

//////////////
// Goodie
/////////////
Goodie::Goodie(int imageID, int x, int y, int direction, int layer,
	double size, GameWorld *world) : GameObject(imageID, x, y, direction,
		layer, size, world)
{
}

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
	DoDiffrently(); // Bomp
}

/*
HP Goodie
*/

HP_Goodie::HP_Goodie(int x, int y, GameWorld *world) :
	Goodie(IMGID_HP_RESTORE_GOODIE, x, y, 0, 2, 0.5, world)
{
}

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
	Goodie(IMGID_POWERUP_GOODIE, x, y, 0, 2, 0.5, world)
{
}

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
	Goodie(IMGID_METEOR_GOODIE, x, y, 0, 2, 0.5, world)
{
}

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

//////////////
// Projectile
//////////////
/*
Blue_Bullet
*/
Blue_Bullet::Blue_Bullet(int x, int y, double size, GameWorld *world, double effect)
	: Projectile(IMGID_BLUE_BULLET, x, y, 0, 1, size, world, effect)
{
}

void Blue_Bullet::DoDiffrently()
{
	if (findworld->Blue_Bullet_bump(this))
	{
		setdeath();
		return;
	}
	MoveTo(GetX(), GetY() + 6);
	if (findworld->Blue_Bullet_bump(this))
	{
		setdeath();
		return;
	}
}

bool Blue_Bullet::is_enermy() { return false; }
bool Blue_Bullet::is_bullet() { return true; }
bool Blue_Bullet::can_bump() { return true; }
bool Blue_Bullet::is_meteor() { return false; }
void Blue_Bullet::cause_damage(int)
{
	std::cout << "You can not invoke this in Blue_bullet class"
		<< std::endl;
}
/*
Red_Bullet
*/
Red_Bullet::Red_Bullet(int x, int y, int direction,
	GameWorld *world, double effect) :
	Projectile(IMGID_RED_BULLET, x, y, direction, 1, 0.5, world, effect)
{
}

bool Red_Bullet::is_meteor() { return false; }
void Red_Bullet::cause_damage(int)
{
	std::cout << "You can not invoke this in Red_bullet class"
		<< std::endl;
}
void Red_Bullet::DoDiffrently()
{
	if (findworld->Red_Bullet_bump(this))
	{
		setdeath();
		return;
	}
	// move
	switch (GetDirection())
	{
	case 180:
		MoveTo(GetX(), GetY() - 6);
		break;
	case 162:
		MoveTo(GetX() + 2, GetY() - 6);
		break;
	case 198:
		MoveTo(GetX() - 2, GetY() - 6);
		break;
	}
	if (findworld->Red_Bullet_bump(this))
	{
		setdeath();
		return;
	}
}

bool Red_Bullet::is_enermy() { return true; }
bool Red_Bullet::is_bullet() { return true; }
bool Red_Bullet::can_bump() { return true; }

/*
Meteor
*/

Meteor::Meteor(int x, int y, GameWorld *world) :
	Projectile(IMGID_METEOR, x, y, 0, 1, 2.0, world, 10000000)
{
}

bool Meteor::is_enermy() { return false; }
bool Meteor::is_bullet() { return true; }
bool Meteor::can_bump() { return true; }
void Meteor::cause_damage(int)
{
	std::cout << "You can not invoke this in Meteor class"
		<< std::endl;
}
bool Meteor::is_meteor() { return true; }

void Meteor::DoDiffrently()
{
	findworld->Meteor_bump(GetX(), GetY());

	MoveTo(GetX(), GetY() + 2);
	SetDirection(GetDirection() + 2);

	findworld->Meteor_bump(GetX(), GetY());
}

//////////////
// Star and Explosion
/////////////
Star::Star(int x, int y, double size, GameWorld *t)
	: GameObject(IMGID_STAR, x, y, 0, 4, size, t)
{
}

void Star::Update()
{
	if (GetY() < 0)
	{
		setdeath();
		return;
	}
	else
		MoveTo(GetX(), GetY() - 1);
}

bool Star::is_enermy() { return false; }
bool Star::is_bullet() { return false; }
bool Star::can_bump() { return false; }
bool Star::is_meteor() { return false; }
void Star::cause_damage(int)
{
	std::cout << "You can not invoke this in Star class"
		<< std::endl;
}

/**********
Explosion
**********/
Explosion::Explosion(int x, int y, GameWorld *world) :
	GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5, world), tick(0)
{
}

bool Explosion::is_enermy() { return false; }
bool Explosion::can_bump() { return false; }
bool Explosion::is_bullet() { return false; }
bool Explosion::is_meteor() { return false; }
void Explosion::cause_damage(int)
{
	std::cout << "You can not invoke this in Explosion class"
		<< std::endl;
}

void Explosion::Update()
{
	SetSize(GetSize() - 0.2);
	if (++tick == 20)
	{
		setdeath();
		return;
	}
	return;
}