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
	vector<int> node_x; //x�����̃m�[�h
	vector<int> node_y; //y�����̃m�[�h
	unsigned int husteric_x; //x�����̃q���[�X�e���b�N
	unsigned int husteric_y; //y�����̃q���[�X�e���b�N
	vector<vector<unsigned int>> parent_husteric; //�e�q���[�X�e���b�N
	vector<unsigned int> minimum_husteric1; //�e�����̍ŏ��̃q���[�X�e���b�N
	unsigned int minimum_husteric2; //�ŏ��̃q���[�X�e���b�N
	vector<unsigned int> husteric; //�q���[�X�e���b�N
	vector<int> relative_distance; //���΋���
	vector<int> relative_position_cost; //���Έʒu�R�X�g
	vector<int> obstacle_cost; //��Q���R�X�g
	vector<unsigned int> cost; //���v�R�X�g
	vector<unsigned int> score; //�g�[�^���X�R�A
	unsigned int minimum_score; //�ŏ��R�X�g
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
