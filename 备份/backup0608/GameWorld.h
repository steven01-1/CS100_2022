#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"

class GameObject;
class Dawnbreaker;
class Red_Bullet;
class Blue_Bullet;
class Alien;
class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

/*
这四个函数不能主动调用, 只能由框架调用. 
*/
  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void set_bullet(int x, int y, double size, double effect);

  int get_lives() const;
  void reduce_lives();
  int get_meteors() const;
  void set_meteors(int);
  bool check_bump(GameObject*, GameObject*); // check if bump
  int get_des_num() const;
  void add_des_num();
  int get_powerup() const;
  void set_powerup(int);
  void set_explosion(int x, int y);
  int get_myX() const;
  int get_myY() const;
  void set_Red_Bullet(int mx, int my, int effect);

  bool Red_Bullet_bump(Red_Bullet *); // check
  bool Blue_Bullet_bump(Blue_Bullet *);
  bool Alien_bump(Alien *);
private:
  std::list<GameObject*> worldobj;
  Dawnbreaker* me;
  int lives;
  int meteors;
  int des_num;
  int powerup;
};

#endif // !GAMEWORLD_H__
