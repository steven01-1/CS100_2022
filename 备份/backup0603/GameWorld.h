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

  void set_bullet();
  //std::string confirm_movingkey();

private:
  std::list<GameObject*> worldobj;
  Dawnbreaker* me;
};

#endif // !GAMEWORLD_H__
