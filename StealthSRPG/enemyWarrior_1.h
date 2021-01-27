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
	vector<int> node_x; //x方向のノード
	vector<int> node_y; //y方向のノード
	unsigned int husteric_x; //x方向のヒューステリック
	unsigned int husteric_y; //y方向のヒューステリック
	vector<vector<unsigned int>> parent_husteric; //親ヒューステリック
	vector<unsigned int> minimum_husteric1; //各方向の最小のヒューステリック
	unsigned int minimum_husteric2; //最小のヒューステリック
	vector<unsigned int> husteric; //ヒューステリック
	vector<int> survival_value; //生存値
	vector<int> relative_distance; //相対距離
	vector<int> relative_position_cost; //相対位置コスト
	vector<int> obstacle_cost; //障害物コスト
	vector<unsigned int> cost; //合計コスト
	vector<unsigned int> score; //トータルスコア
	unsigned int minimum_score; //最小コスト
	int moving_distance; //移動距離
	bool attack_activity; //攻撃状態（true:攻撃済み、false:攻撃可能）
	vector<bool> duplication_activity; //重複状態（true:重複、false:それ以外）
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
