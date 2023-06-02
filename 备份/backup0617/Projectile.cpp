#include "Projectile.h"
#include"GameWorld.h"

/*
Blue_Bullet
*/
Blue_Bullet::Blue_Bullet(int x, int y, double size, GameWorld *world, double effect)
  : Projectile(IMGID_BLUE_BULLET, x, y, 0, 1, size, world, effect)
{}

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
bool Blue_Bullet::can_bump()  { return true; }
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
{}


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
bool Red_Bullet::is_meteor() { return false; }
void Red_Bullet::cause_damage(int)
{
  std::cout << "You can not invoke this in Red_bullet class"
    << std::endl;
}

/*
Meteor
*/

Meteor::Meteor(int x, int y, GameWorld *world) : 
  Projectile(IMGID_METEOR, x, y, 0, 1, 2.0, world, 10000000) {}

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