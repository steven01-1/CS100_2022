#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameWorld;
class GameObject : public ObjectBase
{
public:
  GameObject(int imageID, int x, int y, int direction,
    int layer, double size, GameWorld *world);
  //GameObject(int imageID, int x, int y, int direction,
  //  int layer, double size, GameWorld *world, int HP_A);
  //GameObject(int imageID, int x, int y, int direction,
  //  int layer, double size, int effect_b, GameWorld *world); // for blue bullets

  virtual ~GameObject() = default;

  virtual void Update() = 0;
  bool getstate() const;
  void setdeath();
  int get_HP_A() const; // HP of Aliens
  void set_HP_A(int);
  int get_effect_b() const; // the effect of blue bullets
  void set_effect_b(int);
  
  GameWorld *findworld;

  virtual bool is_enermy() = 0;
  virtual bool is_bullet() = 0;
  virtual bool can_bump() = 0;
  virtual void cause_damage(int) = 0; // cause damege of Aliens, tell the object it is attcked
  virtual bool is_meteor() = 0;


private:
  bool state;
  int HP_A;
  int effect_b;

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
    GameWorld *world, int effect);
  virtual void Update();
  virtual bool is_enermy() = 0;
  virtual bool is_bullet() = 0;
  virtual bool can_bump() = 0;
  virtual void cause_damage(int) = 0;
  virtual bool is_meteor() = 0;
  int get_effect() const;
private:
  int effect; // effect of red bullets
  virtual void DoDiffrently() = 0; // bump, move
};










#endif // GAMEOBJECTS_H__