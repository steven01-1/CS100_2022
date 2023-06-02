#ifndef ALIEN_H__
#define ALIEN_H__

#include "GameObjects.h"

class Alien : public GameObject
{
public:
	Alien(int imageID, int x, int y, int direction, int layer,
		double size, GameWorld *world, int energy, int HP, int effect, int strategy, 
		int strategy_time, int speed);

	virtual void Update() override;

	virtual bool is_enermy() override;
	virtual bool is_bullet() override;
	virtual bool can_bump() override;
	virtual void cause_damage(int) override;
	virtual bool is_meteor() override;
	virtual void show_death() = 0;

	int get_energy() const;
	//int get_HP() const;
	void set_energy(int);
	//void set_HP(int);
	int get_effect()const;
	int get_strategy() const;
	int get_strategy_time() const;
	void set_strategy(int);
	void set_strategy_time(int);
	void set_speed(int);

private:
	int energy;
	int effect;
	int strategy; // 1: down, 2: Ldown, 3: Rdown
	int strategy_time;
	int speed;
	
	virtual void DoDiffrently() = 0;
};

/*
Alphatron
*/
class Alpha : public Alien
{
public:
	Alpha(int x, int y, GameWorld *world, int HP, int effect,
		int speed);

	virtual void show_death() override; // show, ++score, drop
private:
	void DoDiffrently() override;
};

/*
Sigmatron
*/
class Sigma : public Alien
{
public:
	Sigma(int x, int y, GameWorld *world, int HP, int speed);
	virtual void show_death() override;

private:
	virtual void DoDiffrently() override;
};

/*
Omegatron
*/
class Omega : public Alien
{
public:
	Omega(int x, int y, GameWorld *world, int HP, int effect, int speed);

	virtual void show_death() override;
private:
	virtual void DoDiffrently() override;
};

#endif // !ALIEN_H__
