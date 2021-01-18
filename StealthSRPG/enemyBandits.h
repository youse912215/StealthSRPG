#pragma once
#include "enemy.h"

class EnemyBandits : public Enemy {
public:
	int moving_flag;
	int priority;
	EnemyBandits(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive);
	void Update();
	void Draw();

private:
	void Move();
	void Attack();
	void Dead();
};
