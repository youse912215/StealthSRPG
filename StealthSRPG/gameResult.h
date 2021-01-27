#pragma once

class GameResult {
private:
	int rank; //0=Cランク, 1=Bランク, 2=Aランク, 3=Sランク

	enum RANK {
		C,
		B,
		A,
		S
	};

	void draw();

public:
	GameResult();
	~GameResult();
	void rank_check(const bool& p_ac, const bool& sw1_ac, const bool& sw2_ac, const bool& sw3_ac);
	void update();
};
