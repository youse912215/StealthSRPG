#pragma once
#include "charactor.h"

class Enemy : public Charactor {
public:
	int attack;
	int range;
	bool isAlive;

	Enemy(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive);
protected:
	enum IWO_POINT {
		ENEMY_PRINCESS,
		ENEMY_WARRIOR1,
		ENEMY_WARRIOR2,
		ENEMY_WARRIOR3
	};
};
