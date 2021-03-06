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
		*row = 0;
		break;
	case LAND:
		*column = 0;
		*row = 1;
		break;
	case GOAL:
		*column = 1;
		*row = 1;
		break;
	case TIDE:
		//満潮マスを干潮マスにするまたは干潮マスを満潮マスにする
		*column = phenomenonFlag[tide] ? 0 : 2;
		*row = phenomenonFlag[tide] ? 0 : 1;
		break;
	case RAINBOW_WIDTH:
		*column = 5;
		*row = 1;
		break;
	case RAINBOW_HEIGHT:
		*column = 6;
		*row = 1;
		break;
	case BRIDGE_WIDTH:
		*column = 3;
		*row = 1;
		break;
	case BRIDGE_HEIGHT:
		*column = 4;
		*row = 1;
		break;
	case ICE_LAND:
		//陸マスを氷マスにするまたは氷のマスを陸マスにする
		*column = phenomenonFlag[ice] ? 11 : 12;
		*row = 1;
		break;
	case ICE_SEA:
		//海マスを氷マスにするまたは氷のマスを海マスにする
		*column = phenomenonFlag[ice] ? 13 : 0;
		*row = phenomenonFlag[ice] ? 1 : 0;
		break;
	case LAND_TOP:
		*column = 0;
		*row = 2;
		break;
	case LAND_BOT:
		*column = 0;
		*row = 3;
		break;
	case LAND_LEFT:
		*column = 0;
		*row = 4;
		break;
	case LAND_RIGHT:
		*column = 0;
		*row = 5;
		break;
	case LAND_RIGHT_BOT:
		*column = 0;
		*row = 6;
		break;
	case LAND_LEFT_BOT:
		*column = 0;
		*row = 7;
		break;
	case LAND_LEFT_TOP:
		*column = 0;
		*row = 8;
		break;
	case LAND_RIGHT_TOP:
		*column = 0;
		*row = 9;
		break;
	case LAND_RIGHT_BOT2:
		*column = 8;
		*row = 2;
		break;
	case LAND_LEFT_BOT2:
		*column = 9;
		*row = 2;
		break;
	case LAND_RIGHT_TOP2:
		*column = 10;
		*row = 2;
		break;
	case LAND_LEFT_TOP2:
		*column = 11;
		*row = 2;
		break;
	case LAND_OBLIQUE1:
		*column = 12;
		*row = 2;
		break;
	case LAND_OBLIQUE2:
		*column = 13;
		*row = 2;
		break;
	case CENTER:
		*column = 9;
		*row = 1;
		break;
	case RANGE:
		*column = range_flag == 1 ? 8 : 10;
		*row = 1;
		break;
	default:
		break;
	}
}
