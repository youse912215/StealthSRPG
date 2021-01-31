#pragma once

#include "charactor.h"
#include <vector>

using namespace std;

class Enemy : public Charactor {
public:
	int attack;
	int range;
	bool activity; //行動状態（trueなら行動済み）
	bool isAlive;
	int act_time;
	static int act_order;

	Enemy(int x, int y, int graph, int moving_quantity, int attack, int range,
	      int act_time, bool activity, bool isAlive);
	~Enemy();

	virtual void Update(vector<vector<int>>& map) = 0;
	virtual void get_survival_activity(const bool& p_s_activity, const bool& sw1_s_activity, const bool& sw2_s_activity,
	                                   const bool& sw3_s_activity) = 0;
	virtual void get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                                    const int& sw2_x, const int& sw2_y, const int& sw3_x, const int& sw3_y) = 0;
	virtual void Attack(int* p_hp, int* sw1_hp, int* sw2_hp, int* sw3_hp, const int& a_order) = 0;
	virtual void Move() = 0;
	virtual void get_enemy_cost_0(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                              const int& ey3) = 0;
	virtual void get_enemy_cost_1(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                              const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	                              const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
	                              const int& ey8) = 0;
	virtual void get_enemy_cost_2(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
	                              const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
	                              const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
	                              const int& ey8, const int& ex9, const int& ey9, const int& ex10, const int& ey10,
	                              const int& ex11, const int& ey11) = 0;
	virtual void forward_act_order(const int& a_order) = 0;
	virtual void reset() = 0;

protected:
	int slash;
	int impact;
	int dead;

	enum IWO_POINT {
		ENEMY_PRINCESS,
		ENEMY_WARRIOR1,
		ENEMY_WARRIOR2,
		ENEMY_WARRIOR3
	};

	int add_cost(const int& map_info);
	int set_to_one(int x);
	void reset_act_order();
};
