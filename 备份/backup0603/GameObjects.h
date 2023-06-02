#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__


#include "ObjectBase.h"

// ObjectBase(int imageID, int x, int y, int direction, int layer, double size);
//int GetX() const;
//int GetY() const;
//int GetDirection() const;
//int GetLayer() const;
//double GetSize() const;
//
//void MoveTo(int x, int y);
//void SetDirection(int direction);
//void SetSize(double size);

class GameWorld;
class GameObject : public ObjectBase
{
public:
  GameObject(int imageID, int x, int y, int direction, int layer, double size);
  GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world);
  virtual ~GameObject() = default;
  virtual void Update() = 0;
  inline bool getstate() { return state; } // true 存活, false 死亡
  inline void setdeath() { state = false; }
  GameWorld* findworld; // 保存world信息

private:
  bool state;
};

class Alien : public GameObject
{
};

class Projectile : public GameObject
{
public:
  //Projectile(int imageID, int x, int y, int direction, int layer, double size);
  Projectile(int imageID, int x, int y, int direction, int layer, double size,
             GameWorld* world, double effect);
  virtual void Update() = 0;
  inline double get_effect();
  inline void set_effect(double n_ef);

private:
  double effect;
};

class Blue_Bullet : public Projectile
{
public:
  Blue_Bullet(int imageID, int x, int y, int direction, int layer, double size,
               GameWorld* world, double effect);
  virtual void Update() override;
};

class Dawnbreaker : public GameObject
{
public:
  // GameObject(int imageID, int x, int y, int direction, int layer, double
  // size) : ObjectBase(imageID, x, y, direction, layer, size) {}
  Dawnbreaker();  
  inline int get_energy();
  inline int get_HP();
  inline void set_energy(int);
  inline void set_HP(int);
  virtual void Update() override;
private : 
  int energy;
  int HP;
};

class Star : public GameObject
{
public:
  Star(int imageID, int x, int y, int direction, int layer, double size);

  virtual void Update() override;
};




#endif // GAMEOBJECTS_H__