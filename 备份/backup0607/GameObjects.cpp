#include "GameObjects.h"
#include "GameWorld.h"



GameObject::GameObject(int imageID, int x, int y, int direction, int layer,
                       double size)
    : ObjectBase(imageID, x, y, direction, layer, size), state(true),
      findworld(nullptr)
{
}

GameObject::GameObject(int imageID, int x, int y, int direction, int layer,
                       double size, GameWorld* world)
    : ObjectBase(imageID, x, y, direction, layer, size), state(true),
      findworld(world)
{
}

bool GameObject::getstate() { return state; }
void GameObject::setdeath() { state = false; }

Dawnbreaker::Dawnbreaker(GameWorld* g)
    : GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0, g), energy(10), HP(100)
{
}

int Dawnbreaker::get_energy() { return energy; }

int Dawnbreaker::get_HP() { return HP; }

void Dawnbreaker::set_energy(int n_energy) { energy = n_energy; }

void Dawnbreaker::set_HP(int n_HP) { HP = n_HP; }

void Dawnbreaker::Update()
{
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
    // void set_bullet(int x, int y, double size, double effect);
    findworld->set_bullet(GetX(), GetY(), 0.5, 5);
    energy -= 10;
  }
  // recover energy
  if (get_energy() < 10)
    set_energy(get_energy() + 1);
}

Star::Star(int imageID, int x, int y, int direction, int layer, double size)
    : GameObject(IMGID_STAR, x, y, 0, 4, size)
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

Projectile::Projectile(int imageID, int x, int y, int direction, int layer,
                       double size, GameWorld* world, double effect)
    : GameObject(imageID, x, y, direction, layer, size, world), effect(effect)
{
}

double Projectile::get_effect() { return effect; }

void Projectile::set_effect(double n_ef) { effect = n_ef; }

Blue_Bullet::Blue_Bullet(int imageID, int x, int y, int direction, int layer,
                         double size, GameWorld* world, double effect)
    : Projectile(IMGID_BLUE_BULLET, x, y, 0, 1, size, world, effect)
{
}

void Blue_Bullet::Update()
{
  if (!getstate())
    return;
  if (GetY() >= WINDOW_HEIGHT)
  {
    setdeath();
    return;
  }
  MoveTo(GetX(), GetY() + 6);
}