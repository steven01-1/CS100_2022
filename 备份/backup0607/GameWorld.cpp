#include "GameObjects.h"
#include "GameWorld.h"

GameWorld::GameWorld() : me(nullptr), worldobj({}), lives(3),  meteors(0) {}
/// <summary>
/// ��һ����ʯ�ǲ���ÿһ������
/// </summary>
GameWorld::~GameWorld() = default;

int GameWorld::get_lives() const { return lives; }
void GameWorld::set_lives(int l) { lives = l; }
int GameWorld::get_meteors() const { return meteors; }
void GameWorld::set_meteors(int m) { meteors = m; }

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
  /// <summary>
/// ��һ����ʯ�ǲ���ÿһ������
/// </summary>
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
  for (auto i = worldobj.begin(); i != worldobj.end(); ++i)
    delete *i;
  worldobj.clear();
  delete me;
}

bool GameWorld::IsGameOver() const { return false; }
