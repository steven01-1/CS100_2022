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

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void set_bullet(int x, int y, double size, double effect);

  int get_lives() const;
  void set_lives(int);
  int get_meteors() const;
  void set_meteors(int);
private:
  std::list<GameObject*> worldobj;
  Dawnbreaker* me;
  int lives;
  int meteors;
};

#endif // !GAMEWORLD_H__
