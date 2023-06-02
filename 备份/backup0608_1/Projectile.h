#ifndef Projectile_H__
#define Projectile_H__

#include "GameObjects.h"

class Blue_Bullet : public Projectile
{
public:
  Blue_Bullet(int x, int y, double size, GameWorld *world, double effect);

  virtual bool is_enermy() override;
  virtual bool is_bullet() override;
  virtual bool can_bump() override;
	virtual void cause_damage(int) override ;
private:
  void DoDiffrently() override;
};

/*
Red_Bullet
*/
class Red_Bullet : public Projectile
{
public:
	Red_Bullet(int x, int y, int direction, GameWorld *world, double effect);

	virtual bool is_enermy() override;
	virtual bool is_bullet() override;
	virtual bool can_bump() override;
	virtual void cause_damage(int) override;
private:
	void DoDiffrently() override;

};

#endif // !Projectile_H__
