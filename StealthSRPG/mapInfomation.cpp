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
		//�����}�X�������}�X�ɂ���܂��͊����}�X�𖞒��}�X�ɂ���
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
		//���}�X��X�}�X�ɂ���܂��͕X�̃}�X�𓹃}�X�ɂ���
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
