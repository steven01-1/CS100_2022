#include "GameWorld.h"
#include "GameObjects.h"

GameWorld::GameWorld() : me(nullptr), worldobj({}) {}

GameWorld::~GameWorld() = default;

void GameWorld::set_bullet(int x, int y, double size, double effect)
{
  worldobj.emplace_back(
  new Blue_Bullet(IMGID_BLUE_BULLET, x, y + 50, 0, 1, size, nullptr, effect));
}

void GameWorld::Init()
{
  me = new Dawnbreaker(this);
  for (int i = 0; i < 30; ++i)
  {
    worldobj.emplace_back(new Star(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1),
                                   randInt(0, WINDOW_HEIGHT - 1), 0, 4,
                                   randInt(10, 40) / 100.0));
  }
}

LevelStatus GameWorld::Update()
{
  if (randInt(1, 30) == 10)
    worldobj.emplace_back(new Star(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1),
                                   WINDOW_HEIGHT - 1, 0, 4,
                                   randInt(10, 40) / 100.0));
  me->Update();
  for (auto& ele : worldobj)
    ele->Update();

  for (auto i = worldobj.begin(); i != worldobj.end();)
    if (!(*i)->getstate())
    {
      delete *i;
      worldobj.erase(i++);
    }
    else
      ++i;
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  for (auto i = worldobj.begin(); i != worldobj.end(); ++i)
    delete *i;
  worldobj.clear();
  delete me;
}

bool GameWorld::IsGameOver() const { return false; }
