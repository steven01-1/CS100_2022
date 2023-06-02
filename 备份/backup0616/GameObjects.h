#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameWorld;
class GameObject : public ObjectBase
{
public:
  GameObject(int imageID, int x, int y, int direction,
    int layer, double size, GameWorld *world);
  virtual ~GameObject() = default;

  virtual void Update() = 0;
  bool getstate() const;
  void setdeath();

  GameWorld *findworld;

  virtual bool is_enermy() = 0;
  virtual bool is_bullet() = 0;
  virtual bool can_bump() = 0;
  virtual void cause_damage(int) = 0; // cause damege of Aliens, tell the object it is attcked
  virtual bool is_meteor() = 0;

private:
  bool state;

};

class Dawnbreaker : public GameObject
{
public:
  Dawnbreaker(GameWorld *g);
  int get_energy();
  int get_HP();
  void set_energy(int);
  void set_HP(int);
  virtual void Update() override;

  virtual bool is_enermy() override;
  virtual bool is_bullet() override;
  virtual bool can_bump() override;
  virtual void cause_damage(int) override;
  virtual bool is_meteor() override;
private:
  int energy;
  int HP;
};



/*
  Projectile base
*/
class Projectile : public GameObject
{
public:
  Projectile(int imageID, int x, int y, int direction, int layer, double size,
    GameWorld *world, double effect);
  virtual void Update();
  virtual bool is_enermy() = 0;
  virtual bool is_bullet() = 0;
  virtual bool can_bump() = 0;
  virtual void cause_damage(int) = 0;
  virtual bool is_meteor() = 0;
  int get_effect() const;
private:
  int effect;
  virtual void DoDiffrently() = 0; // bump, move
};


/////////////////
// Alien
//////////////////
class Alien : public GameObject
{
public:
	Alien(int imageID, int x, int y, int direction, int layer,
		double size, GameWorld *world, int energy, int HP, int effect, int strategy,
		int strategy_time, int speed);

	virtual void Update() override;

	virtual bool is_enermy() override;
	virtual bool is_bullet() override;
	virtual bool can_bump() override;
	virtual void cause_damage(int) override;
	virtual bool is_meteor() override;
	virtual void show_death() = 0;

	int get_energy() const;
	int get_HP() const;
	void set_energy(int);
	void set_HP(int);
	int get_effect()const;
	int get_strategy() const;
	int get_strategy_time() const;
	void set_strategy(int);
	void set_strategy_time(int);
	void set_speed(int);
private:
	int energy;
	int HP;
	int effect;
	int strategy; // 1: down, 2: Ldown, 3: Rdown
	int strategy_time;
	int speed;

	virtual void DoDiffrently() = 0;
};

/*
Alphatron
*/
class Alpha : public Alien
{
public:
	Alpha(int x, int y, GameWorld *world, int HP, int effect,
		int speed);

	virtual void show_death() override; // show, ++score, drop
private:
	void DoDiffrently() override;
};

/*
Sigmatron
*/
class Sigma : public Alien
{
public:
	Sigma(int x, int y, GameWorld *world, int HP, int speed);
	virtual void show_death() override;

private:
	virtual void DoDiffrently() override;
};

/*
Omegatron
*/
class Omega : public Alien
{
public:
	Omega(int x, int y, GameWorld *world, int HP, int effect, int speed);

	virtual void show_death() override;
private:
	virtual void DoDiffrently() override;
};


//////////////////
// Goodie/////
///////////////
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

/////////////////
// Projectile
////////////////
class Blue_Bullet : public Projectile
{
public:
  Blue_Bullet(int x, int y, double size, GameWorld *world, double effect);

  virtual bool is_enermy() override;
  virtual bool is_bullet() override;
  virtual bool can_bump() override;
  virtual void cause_damage(int) override;
  virtual bool is_meteor() override;
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
  virtual bool is_meteor() override;
private:
  void DoDiffrently() override;

};

/*
Meteor
*/

class Meteor : public Projectile
{
public:
  Meteor(int x, int y, GameWorld *world);

  virtual bool is_enermy() override;
  virtual bool is_bullet() override;
  virtual bool can_bump() override;
  virtual void cause_damage(int) override;
  virtual bool is_meteor() override;

private:
  virtual void DoDiffrently() override;
};

/////////////////
// Star and Explosion
///////////////
/**********
Star
**********/
class Star : public GameObject
{
public:
  Star(int x, int y, double size, GameWorld *g);
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

#endif // GAMEOBJECTS_H__