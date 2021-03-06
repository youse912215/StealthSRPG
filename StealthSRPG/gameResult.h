#pragma once

class GameResult {
private:

	int char_next; //次のシーン文字
	int background; //背景

	enum RANK {
		D,
		C,
		B,
		A,
		S
	};

	void draw();

public:
	int rank; //0=Cランク, 1=Bランク, 2=Aランク, 3=Sランク
	static int result_num;

	GameResult();
	~GameResult();
	void rank_check(const bool& p_ac, const bool& sw1_ac, const bool& sw2_ac, const bool& sw3_ac);
	void update();
};
