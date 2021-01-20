#pragma once
#include "enemy.h"
#include <vector>

using namespace std;

class EnemyWarrior_1 : public Enemy {
public:
	int moving_flag;
	int priority;
	static bool husteric_flag;

	EnemyWarrior_1(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity, bool isAlive);
	void Update(vector<vector<int>>& map);
	void get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                            const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y);
	void Attack(int* p_hp, const int& sw1_hp, const int& sw2_hp, const int& sw3_hp);

private:
	vector<int> node_x; //x方向のノード
	vector<int> node_y; //y方向のノード
	unsigned int husteric_x; //x方向のヒューステリック
	unsigned int husteric_y; //y方向のヒューステリック
	vector<vector<unsigned int>> parent_husteric; //親ヒューステリック
	vector<unsigned int> minimum_husteric1; //各方向の最小のヒューステリック
	unsigned int minimum_husteric2; //最小のヒューステリック
	vector<unsigned int> husteric; //ヒューステリック
	vector<int> relative_distance; //相対距離
	vector<int> relative_position_cost; //相対位置コスト
	vector<int> obstacle_cost; //障害物コスト
	vector<unsigned int> cost; //合計コスト
	vector<unsigned int> score; //トータルスコア
	unsigned int minimum_score; //最小コスト
	int moving_distance;
	bool attack_flag;

	void Draw();
	void get_each_node();
	void get_minimum_husteric();
	void get_node_husteric();
	void get_obstacle_cost(vector<vector<int>>& map);
	void get_relative_position_cost();
	void get_node_cost();
	void get_node_score();
	void Move();
	void moving_decision();
	void Dead(vector<vector<int>>& map);
};
