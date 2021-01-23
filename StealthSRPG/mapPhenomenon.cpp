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
		memset(phenomenonFlag + 2, false, 2); //ice, tideをfalseに変更
		break;
	case NIGHT_PLAY:
	case NIGHT_ENEMY:
		memset(phenomenonFlag + 2, true, 2); //ice, tideをtrueに変更
		break;
	default:
		break;
	}
}

//void Phenomenon::Rain() {
//	//移動範囲制限
//	if (phenomenonFlag[rain1] == true) {
//
//	}
//}
//
//void Phenomenon::Ice() {
//	if (phenomenonFlag[ice] == false) {
//
//	}
//	else {
//
//	}
//}
//
//void Phenomenon::Tide() {
//
//	if (phenomenonFlag[tide] == true) {
//
//	}
//	else {
//
//	}
//}
//
//void Phenomenon::Fog() {
//}
//
//void Phenomenon::RainBow() {
//}
