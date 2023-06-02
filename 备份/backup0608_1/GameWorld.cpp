#include "GameWorld.h"
#include "GameObjects.h"

#include "StarandExplosion.h"
#include "Projectile.h"
#include "Alien.h"

#define my_MAX(x, y) (x) < (y) ? (y) : (x)
#define my_MIN(x, y) (y) < (x) ? (y) : (x)

GameWorld::GameWorld() : me(nullptr), worldobj({}), lives(3),  
meteors(0), des_num(0),  powerup(0), onScreen(0) {}

GameWorld::~GameWorld() = default;

int GameWorld::get_lives() const { return lives; }
void GameWorld::reduce_lives() { --lives; }
int GameWorld::get_meteors() const { return meteors; }
void GameWorld::set_meteors(int n_m) { meteors = n_m; }
int GameWorld::get_des_num() const { return des_num; }
void GameWorld::add_des_num() { ++des_num; }
int GameWorld::get_powerup() const { return powerup; }
void GameWorld::set_powerup(int p) { powerup = p; }
int GameWorld::get_myX() const { return me->GetX(); }
int GameWorld::get_myY() const { return me->GetY(); }

void GameWorld::set_explosion(int x, int y)
{
  worldobj.emplace_back(new Explosion(x, y, this));
}

bool GameWorld::Red_Bullet_bump(Red_Bullet * obj)
{
  if (check_bump(me, obj))
  {
    me->set_HP(me->get_HP() - obj->get_effect());
    return true;
  }
  else
    return false;
}

bool GameWorld::Blue_Bullet_bump(Blue_Bullet *b_bu)
{
  for (auto i : worldobj)
    if (i->can_bump())
      if (i->is_enermy())
        if (!i->is_bullet())
          if (check_bump(i, b_bu))
          {
            i->cause_damage(b_bu->get_effect());
            return true;
          }
  return false;
}

bool GameWorld::Alien_bump(Alien * obj)
{
  for (auto i : worldobj)
    if (!i->is_enermy())
      if (i->is_bullet())
        if (check_bump(i, obj))
        {
          if (!i->is_meteor()) // blue bullet
          {
            obj->set_HP(obj->get_HP() - (5 + 3 * powerup));
            i->setdeath();
          }
          else // meteor
            obj->set_HP(0);
          return true;
        }
  if (check_bump(me, obj)) // dawnbreaker
  {
    obj->set_HP(0);
    me->set_HP(me->get_HP() - 20);
    return true;
  }
  return false;
}

// set Blue Bullet
void GameWorld::set_bullet(int x, int y, double size, double effect)
{
  worldobj.emplace_back(
    new Blue_Bullet(x, y + 50, size, this, effect));
}

void GameWorld::set_Red_Bullet(int mx, int my, int effect, 
  int direction)
{
  worldobj.emplace_back(new Red_Bullet(mx, my - 50, direction, this, effect));
}

// tell two objects bump or not.
bool GameWorld::check_bump(GameObject *o1, GameObject *o2)
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
  meteors = 0, des_num = 0, powerup = 0, onScreen = 0;
  for (int i = 0; i < 30; ++i)
  {
    worldobj.emplace_back(new Star(randInt(0, WINDOW_WIDTH - 1),
                                   randInt(0, WINDOW_HEIGHT - 1),
                                   randInt(10, 40) / 100.0, this));
  }
  ////////////////
  //delete me
  ///////////////
  worldobj.emplace_back(new Alpha(100, WINDOW_HEIGHT - 1, this, 40, 1, 1));
}

LevelStatus GameWorld::Update()
{
  if (randInt(1, 30) == 10)
    worldobj.emplace_back(new Star(randInt(0, WINDOW_WIDTH - 1),
                                   WINDOW_HEIGHT - 1,
                                   randInt(10, 40) / 100.0, this));
  int level = GetLevel();
  int required = level * 3;
  int destroyed = des_num;
  int toDestroy = required - destroyed;
  int maxOnScreen = (5 + level) / 2;
  int allowed = my_MIN(toDestroy, maxOnScreen);
  if (onScreen < allowed)
  {
    ++onScreen;
    int P1 = 6;
    int P2 = 2 * my_MAX(level - 1, 0);
    int P3 = 3 * my_MAX(level - 2, 0);
    int sum = P1 + P2 + P3;
    int rate = randInt(1, sum);
    if (rate <= P1)
      worldobj.emplace_back(new Alpha(randInt(0, WINDOW_WIDTH - 1),
        WINDOW_HEIGHT - 1, this, 20 + 2 * level, 4 + level, 2 + level / 5));
    else if (rate > P1 && rate <= P1 + P2)
      worldobj.emplace_back(new Sigma(randInt(0, WINDOW_WIDTH - 1),
        WINDOW_HEIGHT - 1, this, 25 + 5 * level, 2 + level / 5));
    else if (rate > P2 && rate <= sum)
      worldobj.emplace_back(new Omega(randInt(0, WINDOW_WIDTH - 1),
        WINDOW_HEIGHT - 1, this, 20 + level, 2 + 2 * level, 3 + level / 4));
  }

  me->Update();
  for (auto& ele : worldobj)
    ele->Update();

  if (!me->getstate())
  {
    reduce_lives();
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }

  if (des_num >= 3 * GetLevel())
    return LevelStatus::LEVEL_CLEARED;

  for (auto i = worldobj.begin(); i != worldobj.end();)
  {
    if (!(*i)->getstate())
    {
      if ((*i)->can_bump() && (*i)->is_enermy() && !((*i)->is_bullet()))
        --onScreen;
      delete *i;
      worldobj.erase(i++);
    }
    else
      ++i;
  }

// needn`t to set level!
  std::string mes("HP: " + std::to_string(me->get_HP()) + 
    "/100   Meteors: " + std::to_string(get_meteors()) + 
    "   Lives: " + std::to_string(get_lives()) + 
    "   Level: " + std::to_string(GetLevel()) +
    "   Enemies: " + std::to_string(des_num) + "/" + std::to_string(3 * GetLevel()) + 
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
