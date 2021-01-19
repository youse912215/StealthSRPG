#include "mapPhenomenon.h"
#include "constant.h"

Phenomenon::Phenomenon(): phenomenonFlag{} {
}

Phenomenon::~Phenomenon() {
}

void Phenomenon::Switching() {

	if (turn_timer >= 50000) {
		if (scene == NOON_ENEMY)
			scene = NIGHT_PLAY;
		else if (scene == NIGHT_ENEMY)
			scene = NOON_PLAY;
	}

	switch (scene) {
	case NOON_PLAY:
	case NOON_ENEMY:
		memset(phenomenonFlag + 2, false, 2); //ice, tide��false�ɕύX
		break;
	case NIGHT_PLAY:
	case NIGHT_ENEMY:
		memset(phenomenonFlag + 2, true, 2); //ice, tide��true�ɕύX
		break;
	default:
		break;
	}
}

void Phenomenon::Rain() {
	//�ړ��͈͐���
	if (phenomenonFlag[rain1] == true) {

	}
}

void Phenomenon::Ice() {
	if (phenomenonFlag[ice] == false) {

	}
	else {

	}
}

void Phenomenon::Tide() {

	/*��dfor�����ɁA
	if(map[i][j]==4)
	{
		map[i][j] = 1;
	}*/
	if (phenomenonFlag[tide] == true) {

	}
	else {

	}
}

void Phenomenon::Fog() {
	//�ړ�����
	//�����Ȃ��Ȃ�O���t�B�b�N
}

void Phenomenon::RainBow() {
	//����������}�X�������߂�悤�ɂ���
}
