#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"

class GameObject;
class Dawnbreaker;
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
  bool check_bomp(GameObject*, GameObject*);
  int get_des_num() const;
  void add_des_num();

private:
  std::list<GameObject*> worldobj;
  Dawnbreaker* me;
  int lives;
  int meteors;
  int des_num;
};

#endif // !GAMEWORLD_H__
