#include "GameWorld.h"
#include "GameObjects.h"

GameWorld::GameWorld() : me(nullptr), worldobj({}), lives(3),  meteors(0), des_num(0) {}

GameWorld::~GameWorld() = default;

int GameWorld::get_lives() const { return lives; }
void GameWorld::reduce_lives() { --lives; }
int GameWorld::get_meteors() const { return meteors; }
void GameWorld::set_meteors(int n_m) { meteors = n_m; }
int GameWorld::get_des_num() const { return des_num; }
void GameWorld::add_des_num() { ++des_num; }

void GameWorld::set_bullet(int x, int y, double size, double effect)
{
  worldobj.emplace_back(
  new Blue_Bullet(IMGID_BLUE_BULLET, x, y + 50, 0, 1, size, nullptr, effect));
}

// tell two objects bomp or not.
bool GameWorld::check_bomp(GameObject *o1, GameObject *o2)
{
  if ((o1->GetX() - o2->GetX()) * (o1->GetX() - o2->GetX()) +
    (o1->GetY() - o2->GetY()) * (o1->GetY() - o2->GetY()) <
    (30.0 * (o1->GetSize() + o2->GetSize())) * (30.0 * (o1->GetSize() + o2->GetSize()))
    )
    return true;
  else
    return false;
}

/********************
这4个基本函数不许主动调用
*************************/
void GameWorld::Init()
{
  me = new Dawnbreaker(this);
  meteors = 0, des_num = 0;
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

// needn`t to set level!
  std::string mes("HP: " + std::to_string(me->get_HP()) + 
    "/100   Meteors: " + std::to_string(get_meteors()) + 
    "   Lives: " + std::to_string(get_lives()) + 
    "   Level: " + std::to_string(GetLevel()) +
    "   Enemies: X/" + std::to_string(3 * GetLevel()) + 
    "   Score: " + std::to_string(GetScore()));
  SetStatusBarMessage(mes);

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  for (auto &i : worldobj)
    delete i;
  worldobj.clear();
  delete me;
}

bool GameWorld::IsGameOver() const 
{
  if (get_lives())
    return false; 
  else
    return true;
}
