#include "enemyBandits.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include <algorithm>

EnemyBandits::EnemyBandits(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity,
                           bool isAlive) :
	Enemy(x, y, graph, moving_quantity, attack, range, activity, isAlive),
	node_x(3),
	node_y(3),
	parent_husteric(4, vector<unsigned int>(4, 0)),
	minimum_husteric1(4, 0),
	husteric(4, 0),
	relative_distance(2, 0),
	relative_position_cost(4, 0),
	obstacle_cost(4),
	cost(4, 0),
	score(4, 0) {
	moving_distance = 0;
	husteric_x = 0;
	husteric_y = 0;
	minimum_husteric2 = 0;
	minimum_score = 0;
	attack_activity = false;
}

void EnemyBandits::Update(vector<vector<int>>& map) {
	Draw();
	get_each_node();
	get_minimum_husteric();
	get_node_husteric();
	get_obstacle_cost(map);
	get_relative_position_cost();
	get_node_cost();
	get_node_score();
	Move();
	Dead(map);
}

void EnemyBandits::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
	DrawGraph(x - current_x + block_size * 9, y - init_position - current_y + block_size * 9, graph, true);
	DrawFormatString(200, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "山賊(%d, %d)", x / block_size, y / block_size, false);
}

void EnemyBandits::get_each_node() {
	node_x[LEFT_X] = (this->x - block_size) / block_size;
	node_x[CENTER_X] = (this->x) / block_size;
	node_x[RIGHT_X] = (this->x + block_size) / block_size;

	node_y[UP_Y] = (this->y - block_size) / block_size;
	node_y[CENTER_Y] = (this->y) / block_size;
	node_y[DOWN_Y] = (this->y + block_size) / block_size;
}

void EnemyBandits::get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
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

void EnemyBandits::get_minimum_husteric() {
	for (unsigned int i = 0; i < parent_husteric.at(0).size(); ++i) {
		minimum_husteric1[i] = *min_element(parent_husteric[i].begin(), parent_husteric[i].end());
	}
	minimum_husteric2 = *min_element(minimum_husteric1.begin(), minimum_husteric1.end());
}

void EnemyBandits::get_node_husteric() {

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

void EnemyBandits::get_obstacle_cost(vector<vector<int>>& map) {
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

void EnemyBandits::get_relative_position_cost() {
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

void EnemyBandits::get_node_cost() {
	cost[LEFT] = abs(node_x[CENTER_X] - node_x[LEFT_X] + obstacle_cost[LEFT] + relative_position_cost[LEFT]);
	cost[RIGHT] = abs(node_x[CENTER_X] - node_x[RIGHT_X] + obstacle_cost[RIGHT] + relative_position_cost[RIGHT]);
	cost[UP] = abs(node_y[CENTER_Y] - node_y[UP_Y] + obstacle_cost[UP] + relative_position_cost[UP]);
	cost[DOWN] = abs(node_y[CENTER_Y] - node_y[DOWN_Y] + obstacle_cost[DOWN] + relative_position_cost[DOWN]);
}

void EnemyBandits::get_node_score() {
	score[LEFT] = cost[LEFT] + husteric[LEFT];
	score[RIGHT] = cost[RIGHT] + husteric[RIGHT];
	score[UP] = cost[UP] + husteric[UP];
	score[DOWN] = cost[DOWN] + husteric[DOWN];
	minimum_score = *min_element(score.begin(), score.end());
}

void EnemyBandits::Move() {
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
		attack_activity = false;
		moving_distance = 0;
	}
}

void EnemyBandits::moving_decision() {
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

void EnemyBandits::Attack(int* p_hp, int* sw1_hp, int* sw2_hp, int* sw3_hp) {
	if (p_hp == nullptr || sw1_hp == nullptr || sw2_hp == nullptr || sw3_hp == nullptr) { return; }

	if (minimum_score == 1 && this->activity && !attack_activity) {
		if (parent_husteric[ENEMY_PRINCESS][LEFT] == 0
			|| parent_husteric[ENEMY_PRINCESS][RIGHT] == 0
			|| parent_husteric[ENEMY_PRINCESS][UP] == 0
			|| parent_husteric[ENEMY_PRINCESS][DOWN] == 0) {
			*p_hp -= this->attack;
			attack_activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR1][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR1][DOWN] == 0) {
			*sw1_hp -= this->attack;
			attack_activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR2][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR2][DOWN] == 0) {
			*sw2_hp -= this->attack;
			attack_activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR3][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR3][DOWN] == 0) {
			*sw3_hp -= this->attack;
			attack_activity = true;
		}
	}
}

void EnemyBandits::Dead(vector<vector<int>>& map) {
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		this->isAlive = false; //生存状態をfalse
		this->x = -1;
		this->y = -1;
	}
}
