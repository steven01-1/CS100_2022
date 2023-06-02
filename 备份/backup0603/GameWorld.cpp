#include "GameWorld.h"
#include "GameObjects.h"


GameWorld::GameWorld()
{ Init(); }

GameWorld::~GameWorld() { CleanUp(); }

void GameWorld::set_bullet() 
{
  worldobj.emplace_back(new Blue_Bullet(IMGID_BLUE_BULLET, me->GetX(),
   me->GetY() + 50, 0, 1, 0.5, this, 5));
}

void GameWorld::Init() 
{ me = new Dawnbreaker(); 
  for (int i = 0; i < 30; ++i)
  {
    worldobj.emplace_back(new Star(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1),
                                   randInt(0, WINDOW_HEIGHT - 1), 0, 4,
                                   randInt(10, 40) / 100.0));
  }
}

//Star::Star(int imageID, int x, int y, int direction, int layer, double size)
//    : GameObject(IMGID_STAR, x, y, 0, 4, size)
//{
//}

LevelStatus GameWorld::Update()
{
  if (randInt(1,30) == 10)
    worldobj.emplace_back(new Star(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1),
                                 WINDOW_HEIGHT - 1, 0, 4,
                                 randInt(10, 40) / 100.0));
  me->Update();
  for (auto& ele : worldobj)
    ele->Update();
  for (auto i = worldobj.begin(); i != worldobj.end(); ++i)
    if (!(*i)->getstate())
      worldobj.erase(i);

  return LevelStatus::ONGOING;

}

void GameWorld::CleanUp()
{
  for (auto& i : worldobj)
    delete i;
  delete me;
}


bool GameWorld::IsGameOver() const {
  return false;
}
