#pragma once
#include "enemy.h"
#include <vector>

using namespace std;

class EnemyWarrior_1 : public Enemy {
public:
	int moving_flag;
	int priority;
	double moving_quantity;


	EnemyWarrior_1(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive);
	void Update();
	void Draw();

private:
	void Move();
	void Attack();
	void Dead();
};
