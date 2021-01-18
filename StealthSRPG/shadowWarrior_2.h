#pragma once
#include "player.h"
#include "inputProcess.h"

class ShadowWarrior_2 : public Player {
private:
	Input& input;
	int moving_flag;
public:
	ShadowWarrior_2(int x, int y, int graph, int moving_distance, int hp, int range, bool activity, bool isAlive,
	                Input& input);

	void Update(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	            const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
	            const int& eb1_x, const int& eb1_y);
	void Draw();


	/*double GetPLCenterX() {
		return quantity_x + width / 2.0;
	}

	double GetPLCenterY() {
		return quantity_y + height / 2.0;
	}

	double GetPLRadius() {
		return radius;
	}*/

private:
	void Pickup();
	void pickup_switching() override;
	void duplicate_decision(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
	                        const int& sw3_x, const int& sw3_y, const int& ew1_x, const int& ew1_y,
	                        const int& eb1_x, const int& eb1_y);
	void Move();
	void Dead();
};
