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
	void get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                            const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y);
	void get_minimum_husteric();
	void get_node_cost();
	void get_node_score();

private:
	vector<int> node_x;
	vector<int> node_y;
	vector<vector<int>> open_list;
	vector<vector<int>> closed_list;
	int open_width;
	int open_height;
	unsigned int husteric_x;
	unsigned int husteric_y;
	vector<vector<unsigned int>> parent_husteric;
	vector<unsigned int> minimum_husteric;
	vector<unsigned int> cost;
	vector<unsigned int> score;


	void Move();
	void Attack();
	void Dead();
	/*void get_open_list();
	void get_closed_list();*/
};
