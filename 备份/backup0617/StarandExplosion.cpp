#include "StarandExplosion.h"

Star::Star(int x, int y, double size, GameWorld* t)
  : GameObject(IMGID_STAR, x, y, 0, 4, size, t)
{}

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
{}

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