#pragma once
#include "enemy.h"
#include <vector>

using namespace std;

class EnemyWarrior_1 : public Enemy {
public:
	EnemyWarrior_1(int x, int y, int graph, int moving_quantity, int attack, int range, int act_time, bool activity,
	               bool isAlive);
	void Update(vector<vector<int>>& map) override;
	void get_survival_activity(const bool& p_s_activity, const bool& sw1_s_activity, const bool& sw2_s_activity,
	                           const bool& sw3_s_activity) override;
	void get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                            const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y) override;
	void Attack(int* p_hp, int* sw1_hp, int* sw2_hp, int* sw3_hp, const int& a_order) override;
	void Move() override;
	void get_enemy_cost(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                    const int& ey3, const int& ex4, const int& ey4) override;
	void forward_act_order(const int& a_order) override;

private:
	vector<int> node_x; //x�����̃m�[�h
	vector<int> node_y; //y�����̃m�[�h
	unsigned int husteric_x; //x�����̃q���[�X�e���b�N
	unsigned int husteric_y; //y�����̃q���[�X�e���b�N
	vector<vector<unsigned int>> parent_husteric; //�e�q���[�X�e���b�N
	vector<unsigned int> minimum_husteric1; //�e�����̍ŏ��̃q���[�X�e���b�N
	unsigned int minimum_husteric2; //�ŏ��̃q���[�X�e���b�N
	vector<unsigned int> husteric; //�q���[�X�e���b�N
	vector<int> survival_value; //�����l
	vector<int> relative_distance; //���΋���
	vector<int> relative_position_cost; //���Έʒu�R�X�g
	vector<int> obstacle_cost; //��Q���R�X�g
	vector<unsigned int> cost; //���v�R�X�g
	vector<unsigned int> score; //�g�[�^���X�R�A
	unsigned int minimum_score; //�ŏ��R�X�g
	int moving_distance; //�ړ�����
	bool attack_activity; //�U����ԁitrue:�U���ς݁Afalse:�U���\�j
	vector<bool> duplication_activity; //�d����ԁitrue:�d���Afalse:����ȊO�j
	int attack_motion;
	vector<int> enemy_cost;

	void Draw();
	void drawing_effect1(const int& nx, const int& ny, const int& direction);
	void drawing_effect2();
	void get_each_node();
	void get_minimum_husteric();
	void get_node_husteric();
	void get_obstacle_cost(vector<vector<int>>& map);
	void get_relative_position_cost();
	void get_node_cost();
	void get_node_score();
	void moving_decision();
	void Dead(vector<vector<int>>& map);
	void score_decision();
	void moving_end();
	void activate_reset();
	void duplicate_process(const int& dir_num);
	void get_attack_direction(const int& player_num);
	void get_slash_motion(const int& a_activity, int* motion);
};
