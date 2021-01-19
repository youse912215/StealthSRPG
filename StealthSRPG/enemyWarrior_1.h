#pragma once
#include "enemy.h"
#include <vector>

using namespace std;

class EnemyWarrior_1 : public Enemy {
public:
	int moving_flag;
	int priority;
	static bool husteric_flag;
	static int X;
	static int Y;

	EnemyWarrior_1(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive);
	void Update(vector<vector<int>>& map);
	void get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                            const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y);

private:
	vector<int> node_x;
	vector<int> node_y;
	unsigned int husteric_x;
	unsigned int husteric_y;
	vector<vector<unsigned int>> parent_husteric;
	vector<unsigned int> minimum_husteric1;
	unsigned int minimum_husteric2;
	vector<unsigned int> husteric;
	vector<int> obstacle_cost;
	vector<unsigned int> cost;
	vector<unsigned int> score;
	unsigned int minimum_score;
	int moving_distance;

	void Draw();
	void Move();
	void moving_decision();
	void Attack();
	void Dead(vector<vector<int>>& map);
	void get_each_node();
	void get_minimum_husteric();
	void get_node_husteric();
	void get_obstacle_cost(vector<vector<int>>& map);
	void get_node_cost();
	void get_node_score();
};
