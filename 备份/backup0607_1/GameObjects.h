#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__


#include "ObjectBase.h"
#include "Alphatron.h"
#include "BlueBullet.h"
#include "Sigmatron.h"



class GameWorld;
class GameObject : public ObjectBase
{
public:
  GameObject(int imageID, int x, int y, int direction, int layer, double size);
  GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld *world);
  virtual ~GameObject() = default;

  virtual void Update() = 0;
  bool getstate() const;
  void setdeath();


  GameWorld *findworld;

  virtual bool is_enermy() = 0;
  virtual bool is_bullet() = 0;
  virtual bool can_bomp() = 0;

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
private:
  int energy;
  int HP;
};

class Alien : public GameObject
{
};

class Projectile : public GameObject
{
public:
  Projectile(int imageID, int x, int y, int direction, int layer, double size,
    GameWorld *world, double effect);
  virtual void Update() = 0;

private:
  int effect;
};

class Blue_Bullet : public Projectile
{
public:
  Blue_Bullet(int imageID, int x, int y, int direction, int layer, double size,
    GameWorld *world, double effect);
  virtual void Update() override;
};



class Star : public GameObject
{
public:
  Star(int imageID, int x, int y, int direction, int layer, double size);
  virtual void Update() override;
};




#endif // GAMEOBJECTS_H__