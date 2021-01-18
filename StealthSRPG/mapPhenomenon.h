#pragma once
#include "mapAll.h"

class Phenomenon : public Map {
public:
	bool phenomenonFlag[7];

	enum phonomenonNum {
		rain1,
		rain2,
		ice,
		tide,
		fog1,
		fog2,
		rainbow
	};

	Phenomenon();
	~Phenomenon();
	void Switching(); ///����؂�ւ�
	void Rain(); ///�J
	void Ice(); ///�X
	void Tide(); ///��
	void Fog(); ///��
	void RainBow(); ///��
};
