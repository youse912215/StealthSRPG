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
	vector<int> open_list;
	vector<int> closed_list;

	void Move();
	void Attack();
	void Dead();
	void get_open_list();
	void get_closed_list();
};
