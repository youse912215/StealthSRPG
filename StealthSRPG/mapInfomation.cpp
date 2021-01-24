#include "mapInfomation.h"
#include "constant.h"

/// <summary>
/// �}�b�v�̏������ƂɃ}�b�v�`�b�v�摜�̗�ƍs��Ԃ�
/// </summary>
/// <param name="column">��</param>
/// <param name="row">�s</param>
/// <param name="map_info">�}�b�v�̏��</param>
void Infomation::get_map_info(int* column, int* row, const int& map_info) {
	if (column == nullptr || row == nullptr) { return; } //null�`�F�b�N

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
		//�����}�X�������}�X�ɂ���܂��͊����}�X�𖞒��}�X�ɂ���
		*column = phenomenonFlag[tide] ? 0 : 12;
		*row = phenomenonFlag[tide] ? 0 : 1;
		break;
	case RAINBOW:
		*column = 5;
		*row = 1;
		break;
	case BRIDGE:
		*column = 4;
		*row = 1;
		break;
	case ICE:
		//���}�X��X�}�X�ɂ���܂��͕X�̃}�X�𓹃}�X�ɂ���
		*column = phenomenonFlag[ice] ? 0 : 1;
		*row = 6;
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
