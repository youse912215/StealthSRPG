#include "enemyWarrior_1.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include <algorithm>

bool EnemyWarrior_1::husteric_flag = false;

EnemyWarrior_1::EnemyWarrior_1(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity,
                               bool isAlive) :
	Enemy(x, y, graph, moving_quantity, attack, range, activity, isAlive),
	node_x(7),
	node_y(7),
	parent_husteric(4, vector<unsigned int>(4, 0)),
	minimum_husteric1(4, 0),
	husteric(4, 0),
	relative_distance(2, 0),
	relative_position_cost(4, 0),
	obstacle_cost(4),
	cost(4, 0),
	score(4, 0) {
	moving_flag = -1;
	moving_distance = 0;
	priority = 1;
	husteric_x = 0;
	husteric_y = 0;
	minimum_husteric2 = 0;
	minimum_score = 0;
}

void EnemyWarrior_1::Update(vector<vector<int>>& map) {
	Draw();
	Move();
	Attack();
	Dead(map);
	get_each_node();
	get_minimum_husteric();
	get_node_husteric();
	get_obstacle_cost(map);
	get_relative_position_cost();
	get_node_cost();
	get_node_score();

}

void EnemyWarrior_1::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(0, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "敵兵1(%d, %d)", x / block_size, y / block_size, false);
	DrawFormatString(0, WIN_HEIGHT - block_size, GetColor(0, 0, 0),
	                 "ew1_md:%d", moving_distance, false);
	DrawFormatString(0, WIN_HEIGHT - block_size + 15, GetColor(0, 0, 0),
	                 "e1F:%d", this->activity, false);
	DrawFormatString(710, 355, GetColor(255, 0, 255),
	                 "NoX:%d, %d, %d", node_x[LEFT_X], node_x[CENTER_X], node_x[RIGHT_X], false);
	DrawFormatString(710, 370, GetColor(255, 0, 255),
	                 "NoY:%d, %d, %d", node_y[UP_Y], node_y[CENTER_Y], node_y[DOWN_Y], false);
	DrawFormatString(710, 385, GetColor(200, 255, 125),
	                 "rpDis:%d, %d", relative_distance[X], relative_distance[Y], false);
	DrawFormatString(710, 400, GetColor(200, 255, 125), "rpCo:L%d, R%d, U%d, D%d",
	                 relative_position_cost[LEFT], relative_position_cost[RIGHT],
	                 relative_position_cost[UP], relative_position_cost[DOWN], false);
	DrawFormatString(710, 415, GetColor(200, 255, 125), "pHus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_PRINCESS][LEFT], parent_husteric[ENEMY_PRINCESS][RIGHT],
	                 parent_husteric[ENEMY_PRINCESS][UP], parent_husteric[ENEMY_PRINCESS][DOWN], false);
	DrawFormatString(710, 430, GetColor(200, 255, 125), "w1Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR1][LEFT], parent_husteric[ENEMY_WARRIOR1][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR1][UP], parent_husteric[ENEMY_WARRIOR1][DOWN], false);
	DrawFormatString(710, 445, GetColor(200, 255, 125), "w2Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR2][LEFT], parent_husteric[ENEMY_WARRIOR2][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR2][UP], parent_husteric[ENEMY_WARRIOR2][DOWN], false);
	DrawFormatString(710, 460, GetColor(200, 255, 125), "w3Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR3][LEFT], parent_husteric[ENEMY_WARRIOR3][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR3][UP], parent_husteric[ENEMY_WARRIOR3][DOWN], false);
	DrawFormatString(710, 475, GetColor(200, 255, 125), "mHus:p%d, w%d, w%d, w%d",
	                 minimum_husteric1[ENEMY_PRINCESS], minimum_husteric1[ENEMY_WARRIOR1],
	                 minimum_husteric1[ENEMY_WARRIOR2], minimum_husteric1[ENEMY_WARRIOR3], false);
	DrawFormatString(710, 490, GetColor(200, 255, 125), "cost:L%d, R%d, U%d, D%d",
	                 obstacle_cost[LEFT], obstacle_cost[RIGHT], obstacle_cost[UP], obstacle_cost[DOWN], false);
	DrawFormatString(710, 505, GetColor(200, 255, 125), "obs_cost:L%d, R%d, U%d, D%d",
	                 cost[LEFT], cost[RIGHT], cost[UP], cost[DOWN], false);
	DrawFormatString(710, 520, GetColor(200, 255, 125), "score:L%d, R%d, U%d, D%d, %d",
	                 score[LEFT], score[RIGHT], score[UP], score[DOWN], minimum_score, false);

}

void EnemyWarrior_1::get_each_node() {
	node_x[LEFT_X] = (this->x - block_size) / block_size;
	node_x[CENTER_X] = (this->x) / block_size;
	node_x[RIGHT_X] = (this->x + block_size) / block_size;
	node_x[LEFT_2X] = (this->x - block_size * 2) / block_size;
	node_x[RIGHT_2X] = (this->x + block_size * 2) / block_size;
	node_x[LEFT_3X] = (this->x - block_size * 3) / block_size;
	node_x[RIGHT_3X] = (this->x + block_size * 3) / block_size;

	node_y[UP_Y] = (this->y - block_size) / block_size;
	node_y[CENTER_Y] = (this->y) / block_size;
	node_y[DOWN_Y] = (this->y + block_size) / block_size;
	node_y[UP_2Y] = (this->y - block_size * 2) / block_size;
	node_y[DOWN_2Y] = (this->y + block_size * 2) / block_size;
	node_y[UP_3Y] = (this->y - block_size * 3) / block_size;
	node_y[DOWN_3Y] = (this->y + block_size * 3) / block_size;
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
		+ abs(node_y[UP_Y] - p_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][DOWN] = abs(node_x[CENTER_X] - p_x / block_size)
		+ abs(node_y[DOWN_Y] - p_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者1 */
	parent_husteric[ENEMY_WARRIOR1][LEFT] = abs(node_x[LEFT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][RIGHT] = abs(node_x[RIGHT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][UP] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[UP_Y] - sw1_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][DOWN] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[DOWN_Y] - sw1_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者2 */
	parent_husteric[ENEMY_WARRIOR2][LEFT] = abs(node_x[LEFT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][RIGHT] = abs(node_x[RIGHT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][UP] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[UP_Y] - sw2_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][DOWN] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[DOWN_Y] - sw2_y / block_size); //エネミー下ノードと姫の2点間距離

	/* 影武者3 */
	parent_husteric[ENEMY_WARRIOR3][LEFT] = abs(node_x[LEFT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][RIGHT] = abs(node_x[RIGHT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][UP] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[UP_Y] - sw3_y / block_size); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][DOWN] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[DOWN_Y] - sw3_y / block_size); //エネミー下ノードと姫の2点間距離

	/* プレイヤーとの相対位置コスト計算 */
	relative_distance[X] = (node_x[CENTER_X] - (p_x / block_size)) + (node_x[CENTER_X] - (sw1_x / block_size))
		+ (node_x[CENTER_X] - (sw2_x / block_size)) + (node_x[CENTER_X] - (sw3_x / block_size));
	relative_distance[Y] = (node_y[CENTER_Y] - (p_y / block_size)) + (node_y[CENTER_Y] - (sw1_y / block_size))
		+ (node_y[CENTER_Y] - (sw2_y / block_size)) + (node_y[CENTER_Y] - (sw3_y / block_size));
}

void EnemyWarrior_1::get_minimum_husteric() {
	for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i) {
		minimum_husteric1[i] = *min_element(parent_husteric[i].begin(), parent_husteric[i].end());
	}
	minimum_husteric2 = *min_element(minimum_husteric1.begin(), minimum_husteric1.end());
}

void EnemyWarrior_1::get_node_husteric() {

	if (minimum_husteric2 != minimum_husteric1[ENEMY_PRINCESS]) {
		if (minimum_husteric2 == minimum_husteric1[ENEMY_WARRIOR3]) {
			for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i)
				husteric[i] = parent_husteric[ENEMY_WARRIOR3][i];
		}
		if (minimum_husteric2 == minimum_husteric1[ENEMY_WARRIOR2]) {
			for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i)
				husteric[i] = parent_husteric[ENEMY_WARRIOR2][i];
		}
		if (minimum_husteric2 == minimum_husteric1[ENEMY_WARRIOR1]) {
			for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i)
				husteric[i] = parent_husteric[ENEMY_WARRIOR1][i];
		}
	}
	else {
		for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i)
			husteric[i] = parent_husteric[ENEMY_PRINCESS][i];
	}
}

void EnemyWarrior_1::get_obstacle_cost(vector<vector<int>>& map) {
	/* 左側のコスト */
	if (map[node_y[CENTER_Y]][node_x[LEFT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == TIDE && Map::scene % 2 != 0)) {
		obstacle_cost[LEFT] = add_cost(SEA);
	}
	else obstacle_cost[LEFT] = 0;

	/* 右側のコスト */
	if (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == TIDE && Map::scene % 2 != 0)) {
		obstacle_cost[RIGHT] = add_cost(SEA);
	}
	else obstacle_cost[RIGHT] = 0;

	/* 上側のコスト */
	if (map[node_y[UP_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == TIDE && Map::scene % 2 != 0)) {
		obstacle_cost[UP] = add_cost(SEA);
	}
	else obstacle_cost[UP] = 0;

	/* 下側のコスト */
	if (map[node_y[DOWN_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == TIDE && Map::scene % 2 != 0)) {
		obstacle_cost[DOWN] = add_cost(SEA);
	}
	else obstacle_cost[DOWN] = 0;
}

void EnemyWarrior_1::get_relative_position_cost() {
	/* x方向の相対位置コスト */
	if (relative_distance[X] < 0) relative_position_cost[LEFT] = 5;
	else if (relative_distance[X] > 0) relative_position_cost[RIGHT] = 5;
	else {
		relative_position_cost[LEFT] = 0;
		relative_position_cost[RIGHT] = 0;
	}

	/* y方向の相対位置コスト */
	if (relative_distance[Y] < 0) relative_position_cost[UP] = 5;
	else if (relative_distance[Y] > 0) relative_position_cost[DOWN] = 5;
	else {
		relative_position_cost[UP] = 0;
		relative_position_cost[DOWN] = 0;
	}
}

void EnemyWarrior_1::get_node_cost() {
	cost[LEFT] = abs(node_x[CENTER_X] - node_x[LEFT_X] + obstacle_cost[LEFT] + relative_position_cost[LEFT]);
	cost[RIGHT] = abs(node_x[CENTER_X] - node_x[RIGHT_X] + obstacle_cost[RIGHT] + relative_position_cost[RIGHT]);
	cost[UP] = abs(node_y[CENTER_Y] - node_y[UP_Y] + obstacle_cost[UP] + relative_position_cost[UP]);
	cost[DOWN] = abs(node_y[CENTER_Y] - node_y[DOWN_Y] + obstacle_cost[DOWN] + relative_position_cost[DOWN]);
}

void EnemyWarrior_1::get_node_score() {
	score[LEFT] = cost[LEFT] + husteric[LEFT];
	score[RIGHT] = cost[RIGHT] + husteric[RIGHT];
	score[UP] = cost[UP] + husteric[UP];
	score[DOWN] = cost[DOWN] + husteric[DOWN];
	minimum_score = *min_element(score.begin(), score.end());
}

void EnemyWarrior_1::Move() {
	if (this->range == moving_distance) {
		this->activity = true;
	}

	if (Map::turn_timer % MOVEING_INTERVAL == 0
		&& Map::turn_timer > 0
		&& !this->activity) {
		moving_decision();
	}

	if (Map::scene % 2 == 0) {
		this->activity = false;
		moving_distance = 0;
	}
}

void EnemyWarrior_1::moving_decision() {
	if (minimum_score == 1) {
		this->activity = true;
		moving_distance = this->range;
	}

	if (minimum_score == score[DOWN] && !this->activity) {
		this->y += moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[RIGHT] && !this->activity) {
		this->x += moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[LEFT] && !this->activity) {
		this->x -= moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[UP] && !this->activity) {
		this->y -= moving_quantity;
		moving_distance++;
	}
}

void EnemyWarrior_1::Attack() {
	if (minimum_score == 1) {
	}
}

void EnemyWarrior_1::Dead(vector<vector<int>>& map) {
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		this->isAlive = false; //生存状態をfalse
		this->x = -1;
		this->y = -1;
	}
}
