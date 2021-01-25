#pragma once
#include "player.h"
#include "inputProcess.h"
#include <vector>

using namespace std;

class Princess : public Player {
private:
	Input& input;

public:
	int moving_flag;
	Princess(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity, bool isAlive,
	         Input& input);
	void Update(const int& sw1_x, const int& sw1_y, const int& sw2_x, const int& sw2_y,
	            const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
	            const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y);
	void Draw();
	void Dead(vector<vector<int>>& map);

private:
	int old_x;
	int old_y;

	void Pickup();
	void pickup_switching() override;
	void duplicate_decision(const int& sw1_x, const int& sw1_y, const int& sw2_x, const int& sw2_y,
	                        const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
	                        const int& ew2_x, const int& ew2_y, const int& eb1_x, const int& eb1_y);
	void Move();
	void get_survival_activity();
	void get_old_node();
	void act_cancel();
};
