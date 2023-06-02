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

