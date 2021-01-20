#pragma once
#include "charactor.h"

class Enemy : public Charactor {
public:
	int attack;
	int range;
	bool activity; //�s����ԁitrue�Ȃ�s���ς݁j
	bool isAlive;

	Enemy(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive);
protected:
	enum IWO_POINT {
		ENEMY_PRINCESS,
		ENEMY_WARRIOR1,
		ENEMY_WARRIOR2,
		ENEMY_WARRIOR3
	};

	int add_cost(const int& map_info);
};
