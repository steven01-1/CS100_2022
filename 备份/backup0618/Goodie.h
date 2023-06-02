#ifndef GOODIE_H__
#define GOODIE_H__

#include "GameObjects.h"

class Goodie : public GameObject
{
public:
	Goodie(int imageID, int x, int y, int direction, int layer,
		double size, GameWorld *world);

  virtual void Update() override;

  virtual bool is_enermy() override;
  virtual bool is_bullet()override;
  virtual bool can_bump()override;
  virtual void cause_damage(int)override; // cause damege of Aliens, tell the object it is attcked
  virtual bool is_meteor()override;
  
private:
  virtual void DoDiffrently() = 0;
};

/*
HP Goodie
*/

class HP_Goodie : public Goodie
{
public:
  HP_Goodie(int x, int y, GameWorld *world);

private:
  virtual void DoDiffrently() override;
};

/*
Powerup Goodie
*/

class Powerup : public Goodie
{
public:
  Powerup(int x, int y, GameWorld *world);

private:
  virtual void DoDiffrently() override;
};

/*
Meteor Goodie
*/

class Meteor_Goodie : public Goodie
{
public:
  Meteor_Goodie(int x, int y, GameWorld *world);

private:
  virtual void DoDiffrently() override;

};

#endif // !GOODIE_H__
