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
	void Switching(); ///’©–éØ‚è‘Ö‚¦
	void Rain(); ///‰J
	void Ice(); ///•X
	void Tide(); ///’ª
	void Fog(); ///–¶
	void RainBow(); ///“ø
};
