#pragma once
#include "charactor.h"

class Enemy : public Charactor {
public:
	int attack;
	int range;
	bool activity; //行動状態（trueなら行動済み）
	bool isAlive;
	int act_time;

	Enemy(int x, int y, int graph, int moving_quantity, int attack, int range,
	      int act_time, bool activity, bool isAlive);
	~Enemy();

protected:
	int slash;
	int impact;
	int dead;

	enum IWO_POINT {
		ENEMY_PRINCESS,
		ENEMY_WARRIOR1,
		ENEMY_WARRIOR2,
		ENEMY_WARRIOR3
	};

	int add_cost(const int& map_info);
	int set_to_one(int x);
};
