#pragma once
#include "mapPhenomenon.h"

class Infomation : public Phenomenon {
public:
	void get_map_info(int* column, int* row, const int& map_info);
};
