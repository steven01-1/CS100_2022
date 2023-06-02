#ifndef STAR_EXPLOSION_H__
#define STAR_EXPLOSION_H__

#include "GameObjects.h"

/**********
Star
**********/
class Star : public GameObject
{
public:
  Star(int x, int y, double size, GameWorld* g);
  virtual void Update() override;
  virtual bool is_enermy() override;
  virtual bool is_bullet()override;
  virtual bool can_bump()override;
	virtual void cause_damage(int)  override;
	virtual bool is_meteor() override;
};

/**********
Explosion
**********/
class Explosion : public GameObject
{
public:
	Explosion(int x, int y, GameWorld *world);
	void Update() override;
	virtual bool is_enermy() override;
	virtual bool can_bump() override;
	virtual bool is_bullet() override;
	virtual void cause_damage(int)  override;
	virtual bool is_meteor() override;
private:
	int tick;
};


#endif // !STAR_EXPLOSION_H__