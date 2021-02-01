#pragma once
#include "player.h"
#include "inputProcess.h"
#include <vector>

using namespace std;

class ShadowWarrior_2 : public Player {
private:
	Input& input;

public:
	bool moving_flag;

	ShadowWarrior_2(int x, int y, int graph, int moving_quantity, int hp, int range, bool activity, bool isAlive,
	                Input& input);

	void Update(const int& se);
	void Draw();
	void Dead(vector<vector<int>>& map);
	void set_next_map_node(const int& c_scene);
	void duplicate_decision(const int& other_x, const int& other_y, const int& name);
	void reset();

private:
	int old_x;
	int old_y;
	vector<bool> duplication_flag; //他のキャラクターとの重複フラグ

	void Pickup(const int& se);
	void pickup_switching() override;
	void Move();
	void get_survival_activity();
	void get_old_node();
	void act_cancel();
};
