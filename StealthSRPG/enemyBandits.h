#pragma once
#include "enemy.h"
#include <vector>

using namespace std;

class EnemyBandits : public Enemy {
public:
	int moving_flag;
	int priority;
	EnemyBandits(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive);
	void Update();
	void Dead(vector<vector<int>>& map);

private:
	void Draw();
	void Move();
	void Attack();

};
