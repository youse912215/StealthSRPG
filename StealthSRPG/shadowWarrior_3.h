#pragma once
#include "player.h"
#include "inputProcess.h"

class ShadowWarrior_3 : public Player {
private:
	Input& input;
	int moving_flag;
public:
	ShadowWarrior_3(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity, bool isAlive,
	                Input& input);

	void Update(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	            const int& sw2_x, const int& sw2_y, const int& ew1_x, const int& ew1_y,
	            const int& eb1_x, const int& eb1_y);
	void Draw();
	void Dead(vector<vector<int>>& map);

private:
	void Pickup();
	void pickup_switching() override;
	void duplicate_decision(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                        const int& sw2_x, const int& sw2_y, const int& ew1_x, const int& ew1_y,
	                        const int& eb1_x, const int& eb1_y);
	void Move();
	void get_survival_activity();
};
