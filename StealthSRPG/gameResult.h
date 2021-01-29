#pragma once

class GameResult {
private:
	int rank; //0=C�����N, 1=B�����N, 2=A�����N, 3=S�����N
	int char_next; //���̃V�[������
	int background; //�w�i

	enum RANK {
		D,
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
