#include "enemyWarrior_1.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include <algorithm>

EnemyWarrior_1::EnemyWarrior_1(int x, int y, int graph, int moving_distance, int attack, int range, bool isAlive) :
	Enemy(x, y, graph, moving_distance, attack, range, isAlive),
	node_x({(this->x - block_size) / block_size, (this->x) / block_size, (this->x + block_size) / block_size}),
	node_y({(this->y - block_size) / block_size, (this->y) / block_size, (this->y + block_size) / block_size}),
	open_list(2, vector<int>(8, 0)),
	closed_list(area_height, vector<int>(area_width, 0)),
	parent_husteric(4, vector<unsigned int>(4, 0)),
	minimum_husteric(4, 0),
	cost(4, 0),
	score(4, 0) {
	moving_flag = -1;
	priority = 1;
	moving_quantity = 0.0;
	open_width = open_list.at(0).size();
	open_height = open_list.size();
	husteric_x = 0;
	husteric_y = 0;
}

void EnemyWarrior_1::Update() {
	Draw();
	Move();
	Attack();
	Dead();
	//get_open_list();
	//get_closed_list();
	get_minimum_husteric();
	get_node_cost();
	get_node_score();
}

void EnemyWarrior_1::Draw() {
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(0, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "敵兵1(%d, %d)", x / block_size, y / block_size, false);
	DrawFormatString(0, WIN_HEIGHT - block_size, GetColor(0, 0, 0),
	                 "ew1_mq:%.1lf", moving_quantity, false);
	DrawFormatString(0, WIN_HEIGHT - block_size + 15, GetColor(0, 0, 0),
	                 "ew1_r:%d", this->range, false);
	DrawFormatString(760, 385, GetColor(255, 0, 255),
	                 "NoX:%d, %d, %d", node_x[LEFT_X], node_x[CENTER_X], node_x[RIGHT_X], false);
	DrawFormatString(760, 400, GetColor(255, 0, 255),
	                 "NoY:%d, %d, %d", node_y[TOP_Y], node_y[CENTER_Y], node_y[BOTTOM_Y], false);
	DrawFormatString(720, 415, GetColor(200, 255, 125), "pHus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_PRINCESS][LEFT], parent_husteric[ENEMY_PRINCESS][RIGHT],
	                 parent_husteric[ENEMY_PRINCESS][UP], parent_husteric[ENEMY_PRINCESS][DOWN], false);
	DrawFormatString(720, 430, GetColor(200, 255, 125), "w1Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR1][LEFT], parent_husteric[ENEMY_WARRIOR1][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR1][UP], parent_husteric[ENEMY_WARRIOR1][DOWN], false);
	DrawFormatString(720, 445, GetColor(200, 255, 125), "w2Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR2][LEFT], parent_husteric[ENEMY_WARRIOR2][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR2][UP], parent_husteric[ENEMY_WARRIOR2][DOWN], false);
	DrawFormatString(720, 460, GetColor(200, 255, 125), "w3Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR3][LEFT], parent_husteric[ENEMY_WARRIOR3][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR3][UP], parent_husteric[ENEMY_WARRIOR3][DOWN], false);
	DrawFormatString(720, 475, GetColor(200, 255, 125), "mHus:p%d, w%d, w%d, w%d",
	                 minimum_husteric[ENEMY_PRINCESS], minimum_husteric[ENEMY_WARRIOR1],
	                 minimum_husteric[ENEMY_WARRIOR2], minimum_husteric[ENEMY_WARRIOR3], false);
	DrawFormatString(720, 500, GetColor(200, 255, 125), "cost:L%d, R%d, U%d, D%d",
	                 cost[LEFT], cost[RIGHT], cost[UP], cost[DOWN], false);
	DrawFormatString(720, 515, GetColor(200, 255, 125), "score:L%d, R%d, U%d, D%d",
	                 score[LEFT], score[RIGHT], score[UP], score[DOWN], false);
}

void EnemyWarrior_1::get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
                                            const int& sw2_x,
                                            const int& sw2_y, const int& sw3_x, const int& sw3_y) {
	/* 姫 */
	parent_husteric[ENEMY_PRINCESS][LEFT] = abs(node_x[LEFT_X] - p_x / block_size)
		+ abs(node_y[CENTER_Y] - p_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][RIGHT] = abs(node_x[RIGHT_X] - p_x / block_size)
		+ abs(node_y[CENTER_Y] - p_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][UP] = abs(node_x[CENTER_X] - p_x / block_size)
		+ abs(node_y[TOP_Y] - p_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][DOWN] = abs(node_x[CENTER_X] - p_x / block_size)
		+ abs(node_y[BOTTOM_Y] - p_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者1 */
	parent_husteric[ENEMY_WARRIOR1][LEFT] = abs(node_x[LEFT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][RIGHT] = abs(node_x[RIGHT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][UP] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[TOP_Y] - sw1_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][DOWN] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[BOTTOM_Y] - sw1_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者2 */
	parent_husteric[ENEMY_WARRIOR2][LEFT] = abs(node_x[LEFT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][RIGHT] = abs(node_x[RIGHT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][UP] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[TOP_Y] - sw2_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][DOWN] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[BOTTOM_Y] - sw2_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者3 */
	parent_husteric[ENEMY_WARRIOR3][LEFT] = abs(node_x[LEFT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][RIGHT] = abs(node_x[RIGHT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][UP] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[TOP_Y] - sw3_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][DOWN] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[BOTTOM_Y] - sw3_y / block_size); //エネミー下ノードと姫の2点間距離
}

void EnemyWarrior_1::get_minimum_husteric() {
	for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i) {
		minimum_husteric[i] = *min_element(parent_husteric[i].begin(), parent_husteric[i].end());
	}

	//if (minimum_husteric == )
}

void EnemyWarrior_1::get_node_cost() {
	cost[LEFT] = abs(node_x[CENTER_X] - node_x[LEFT_X]);
	cost[RIGHT] = abs(node_x[CENTER_X] - node_x[RIGHT_X]);
	cost[UP] = abs(node_y[CENTER_Y] - node_y[TOP_Y]);
	cost[DOWN] = abs(node_y[CENTER_Y] - node_y[BOTTOM_Y]);
}

void EnemyWarrior_1::get_node_score() {
	/*score[LEFT] = cost[LEFT] + minimum_husteric;
	score[RIGHT] = cost[RIGHT] + minimum_husteric;
	score[UP] = cost[UP] + minimum_husteric;
	score[DOWN] = cost[DOWN] + minimum_husteric;*/
}

void EnemyWarrior_1::Move() {
	if (Map::turn_timer == 0) moving_quantity = 0.0;


	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
}

void EnemyWarrior_1::Attack() {
}

void EnemyWarrior_1::Dead() {
}

//void EnemyWarrior_1::get_open_list() {
//
//	for (int i = 0; i < 3; ++i) {
//		/* xのノード代入 */
//		open_list[X][i * 3] = node_x[LEFT_X];
//		open_list[X][i * 3 + 1] = node_x[RIGHT_X];
//		if (i != 2) open_list[X][i * 3 + 2] = node_x[CENTER_X];
//		/* yのノード代入 */
//		open_list[Y][i * 3] = node_y[TOP_Y];
//		open_list[Y][i * 3 + 1] = node_y[BOTTOM_Y];
//		if (i != 2) open_list[Y][i * 3 + 2] = node_y[CENTER_Y];
//	}
//}
//
//void EnemyWarrior_1::get_closed_list() {
//	closed_list[X][0] = node_x[CENTER_X];
//	closed_list[Y][0] = node_y[CENTER_Y];
//}
