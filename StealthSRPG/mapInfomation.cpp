#include "mapInfomation.h"
#include "constant.h"

/// <summary>
/// マップの情報をもとにマップチップ画像の列と行を返す
/// </summary>
/// <param name="column">列</param>
/// <param name="row">行</param>
/// <param name="map_info">マップの情報</param>
void Infomation::get_map_info(int* column, int* row, const int& map_info) {
	if (column == nullptr || row == nullptr) { return; } //nullチェック

	Switching();

	switch (map_info) {
	case SEA:
		*column = 0;
		*row = 1;
		break;
	case ROAD:
		*column = 0;
		*row = 2;
		break;
	case GOAL:
		*column = 0;
		*row = 0;
		break;
	case TIDE:
		//満潮マスを干潮マスにするまたは干潮マスを満潮マスにする
		*column = phenomenonFlag[tide] ? 0 : 1;
		*row = 3;
		break;
	case RAINBOW:
		*column = 0;
		*row = 4;
		break;
	case BRIDGE:
		*column = 0;
		*row = 5;
		break;
	case ICE:
		//道マスを氷マスにするまたは氷のマスを道マスにする
		*column = phenomenonFlag[ice] ? 0 : 1;
		*row = 6;
		break;
	case CENTER:
		*column = 1;
		*row = 9;
		break;
	case RANGE:
		*column = range_flag == 1 ? 0 : 2;
		*row = 9;
		break;
	default:
		break;
	}
}
