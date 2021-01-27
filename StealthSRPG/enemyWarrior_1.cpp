#include "enemyWarrior_1.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include <algorithm>

EnemyWarrior_1::EnemyWarrior_1(int x, int y, int graph, int moving_quantity, int attack, int range, int act_time,
                               bool activity, bool isAlive) :
	Enemy(x, y, graph, moving_quantity, attack, range, act_time, activity, isAlive),
	node_x(5),
	node_y(5),
	parent_husteric(4, vector<unsigned int>(4, 0)),
	minimum_husteric1(4, 0),
	husteric(4, 0),
	survival_value(4, 0),
	relative_distance(2, 0),
	relative_position_cost(4, 0),
	obstacle_cost(4),
	cost(4, 0),
	score(4, 0),
	duplication_activity(4),
	enemy_cost(4) {
	moving_distance = 0;
	husteric_x = 0;
	husteric_y = 0;
	minimum_husteric2 = 0;
	minimum_score = 0;
	attack_activity = false;
	attack_motion = 0;
}

void EnemyWarrior_1::Update(vector<vector<int>>& map) {
	get_latency();
	wait_motion();
	activate_reset();
	score_decision();
	moving_end();
	reset_act_order();
	get_slash_motion(this->attack_activity, &attack_motion);
	Draw();
	drawing_effect2();
	get_each_node();
	get_minimum_husteric();
	get_node_husteric();
	get_obstacle_cost(map);
	get_relative_position_cost();
	get_node_cost();
	get_node_score();
	Dead(map);
}

void EnemyWarrior_1::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
	DrawRectGraph(this->x - current_x + block_size * 9,
	              this->y - init_position - current_y + block_size * 9,
	              src_x * block_size, 0,
	              block_size, block_size,
	              this->graph, true, false);

	/*DrawFormatString(0, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "敵兵1(%d, %d)", x / block_size, y / block_size, false);
	DrawFormatString(0, WIN_HEIGHT - block_size, GetColor(0, 0, 0),
	                 "md:%d, Ac:%d", moving_distance, this->activity, false);
	DrawFormatString(0, WIN_HEIGHT - block_size + 15, GetColor(0, 0, 0),
	                 "aF%d, :aT%d", attack_activity, attack_motion, false);
	DrawFormatString(480, 340, GetColor(255, 0, 255),
	                 "NoX:%d, %d, %d", node_x[LEFT_X], node_x[CENTER_X], node_x[RIGHT_X], false);
	DrawFormatString(480, 355, GetColor(255, 0, 255),
	                 "NoY:%d, %d, %d", node_y[UP_Y], node_y[CENTER_Y], node_y[DOWN_Y], false);
	DrawFormatString(480, 370, GetColor(200, 255, 125),
	                 "rpDis:%d, %d", relative_distance[X], relative_distance[Y], false);
	DrawFormatString(480, 385, GetColor(200, 255, 125),
	                 "s_v:%d, %d, %d, %d", survival_value[ENEMY_PRINCESS], survival_value[ENEMY_WARRIOR1],
	                 survival_value[ENEMY_WARRIOR2], survival_value[ENEMY_WARRIOR3], false);
	DrawFormatString(480, 400, GetColor(200, 255, 125), "rpCo:L%d, R%d, U%d, D%d",
	                 relative_position_cost[LEFT], relative_position_cost[RIGHT],
	                 relative_position_cost[UP], relative_position_cost[DOWN], false);
	DrawFormatString(480, 415, GetColor(200, 255, 125), "pHus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_PRINCESS][LEFT], parent_husteric[ENEMY_PRINCESS][RIGHT],
	                 parent_husteric[ENEMY_PRINCESS][UP], parent_husteric[ENEMY_PRINCESS][DOWN], false);
	DrawFormatString(480, 430, GetColor(200, 255, 125), "w1Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR1][LEFT], parent_husteric[ENEMY_WARRIOR1][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR1][UP], parent_husteric[ENEMY_WARRIOR1][DOWN], false);
	DrawFormatString(480, 445, GetColor(200, 255, 125), "w2Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR2][LEFT], parent_husteric[ENEMY_WARRIOR2][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR2][UP], parent_husteric[ENEMY_WARRIOR2][DOWN], false);
	DrawFormatString(480, 460, GetColor(200, 255, 125), "w3Hus:L%d, R%d, U%d, D%d",
	                 parent_husteric[ENEMY_WARRIOR3][LEFT], parent_husteric[ENEMY_WARRIOR3][RIGHT],
	                 parent_husteric[ENEMY_WARRIOR3][UP], parent_husteric[ENEMY_WARRIOR3][DOWN], false);
	DrawFormatString(480, 475, GetColor(200, 255, 125), "mHus:p%d, w%d, w%d, w%d",
	                 minimum_husteric1[ENEMY_PRINCESS], minimum_husteric1[ENEMY_WARRIOR1],
	                 minimum_husteric1[ENEMY_WARRIOR2], minimum_husteric1[ENEMY_WARRIOR3], false);
	DrawFormatString(480, 490, GetColor(200, 255, 125), "obs_cost:L%d, R%d, U%d, D%d",
	                 obstacle_cost[LEFT], obstacle_cost[RIGHT], obstacle_cost[UP], obstacle_cost[DOWN], false);
	DrawFormatString(480, 505, GetColor(200, 255, 125), "cost:L%d, R%d, U%d, D%d",
	                 cost[LEFT], cost[RIGHT], cost[UP], cost[DOWN], false);
	DrawFormatString(480, 520, GetColor(255, 0, 50), "score:L%d, R%d, U%d, D%d, %d",
	                 score[LEFT], score[RIGHT], score[UP], score[DOWN], minimum_score, false);*/
}

void EnemyWarrior_1::drawing_effect1(const int& nx, const int& ny, const int& direction) {
	if (minimum_score == score[direction]) {
		DrawRectGraph(node_x[nx] * block_size - current_x + block_size * 9,
		              node_y[ny] * block_size - init_position - current_y + block_size * 9,
		              block_size * attack_motion, 0,
		              block_size, block_size,
		              slash, true, false);
	}
}

void EnemyWarrior_1::drawing_effect2() {
	if (attack_activity) {
		get_attack_direction(ENEMY_PRINCESS);
		get_attack_direction(ENEMY_WARRIOR1);
		get_attack_direction(ENEMY_WARRIOR2);
		get_attack_direction(ENEMY_WARRIOR3);
	}
}

void EnemyWarrior_1::get_each_node() {
	node_x[LEFT_X] = (this->x - block_size) / block_size;
	node_x[CENTER_X] = (this->x) / block_size;
	node_x[RIGHT_X] = (this->x + block_size) / block_size;
	node_x[LEFT_2X] = (this->x - block_size * 2) / block_size;
	node_x[RIGHT_2X] = (this->x + block_size * 2) / block_size;

	node_y[UP_Y] = (this->y - block_size) / block_size;
	node_y[CENTER_Y] = (this->y) / block_size;
	node_y[DOWN_Y] = (this->y + block_size) / block_size;
	node_y[UP_2Y] = (this->y - block_size * 2) / block_size;
	node_y[DOWN_2Y] = (this->y + block_size * 2) / block_size;
}

void EnemyWarrior_1::get_survival_activity(const bool& p_s_activity, const bool& sw1_s_activity,
                                           const bool& sw2_s_activity,
                                           const bool& sw3_s_activity) {
	survival_value[ENEMY_PRINCESS] = p_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR1] = sw1_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR2] = sw2_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR3] = sw3_s_activity ? 1 : 0;
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
	relative_distance[X] = set_to_one(node_x[CENTER_X] - (p_x / block_size)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_x[CENTER_X] - (sw1_x / block_size)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_x[CENTER_X] - (sw2_x / block_size)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_x[CENTER_X] - (sw3_x / block_size)) * survival_value[ENEMY_WARRIOR3];
	relative_distance[Y] = set_to_one(node_y[CENTER_Y] - (p_y / block_size)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_y[CENTER_Y] - (sw1_y / block_size)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_y[CENTER_Y] - (sw2_y / block_size)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_y[CENTER_Y] - (sw3_y / block_size)) * survival_value[ENEMY_WARRIOR3];
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
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == ICE_LAND && Map::scene <= 1)) {
		obstacle_cost[LEFT] = 10;
	}
	else obstacle_cost[LEFT] = 0;

	/* 右側のコスト */
	if (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == ICE_LAND && Map::scene <= 1)) {
		obstacle_cost[RIGHT] = 10;
	}
	else obstacle_cost[RIGHT] = 0;

	/* 上側のコスト */
	if (map[node_y[UP_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == ICE_LAND && Map::scene <= 1)) {
		obstacle_cost[UP] = 10;
	}
	else obstacle_cost[UP] = 0;

	/* 下側のコスト */
	if (map[node_y[DOWN_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == ICE_LAND && Map::scene <= 1)) {
		obstacle_cost[DOWN] = 10;
	}
	else obstacle_cost[DOWN] = 0;
}

void EnemyWarrior_1::get_relative_position_cost() {
	/* x方向の相対位置コスト */
	if (relative_distance[X] < 0) {
		relative_position_cost[LEFT] = 1;
		relative_position_cost[RIGHT] = 0;
	}
	else if (relative_distance[X] > 0) {
		relative_position_cost[LEFT] = 0;
		relative_position_cost[RIGHT] = 1;
	}
	else if (relative_distance[X] == 0) {
		relative_position_cost[LEFT] = 0;
		relative_position_cost[RIGHT] = 0;
	}

	/* y方向の相対位置コスト */
	if (relative_distance[Y] < 0) {
		relative_position_cost[UP] = 1;
		relative_position_cost[DOWN] = 0;
	}
	else if (relative_distance[Y] > 0) {
		relative_position_cost[UP] = 0;
		relative_position_cost[DOWN] = 1;
	}
	else if (relative_distance[Y] == 0) {
		relative_position_cost[UP] = 0;
		relative_position_cost[DOWN] = 0;
	}
}

void EnemyWarrior_1::get_node_cost() {
	cost[LEFT] = abs(
		node_x[CENTER_X] - node_x[LEFT_X] + obstacle_cost[LEFT] + relative_position_cost[LEFT] + enemy_cost[LEFT]);
	cost[RIGHT] = abs(
		node_x[CENTER_X] - node_x[RIGHT_X] + obstacle_cost[RIGHT] + relative_position_cost[RIGHT] + enemy_cost[RIGHT]);
	cost[UP] = abs(
		node_y[CENTER_Y] - node_y[UP_Y] + obstacle_cost[UP] + relative_position_cost[UP] + enemy_cost[UP]);
	cost[DOWN] = abs(
		node_y[CENTER_Y] - node_y[DOWN_Y] + obstacle_cost[DOWN] + relative_position_cost[DOWN] + enemy_cost[DOWN]);
}

void EnemyWarrior_1::get_node_score() {
	score[LEFT] = cost[LEFT] + husteric[LEFT];
	score[RIGHT] = cost[RIGHT] + husteric[RIGHT];
	score[UP] = cost[UP] + husteric[UP];
	score[DOWN] = cost[DOWN] + husteric[DOWN];
	minimum_score = *min_element(score.begin(), score.end());
}

void EnemyWarrior_1::Move() {
	if (Map::turn_timer % MOVING_INTERVAL == 0
		&& Map::turn_timer > 0
		&& !this->activity) {
		moving_decision();
	}
}

void EnemyWarrior_1::moving_decision() {
	if (minimum_score == score[DOWN] && !this->activity && Map::scene % 2 != 0) {
		this->y += moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[RIGHT] && !this->activity && Map::scene % 2 != 0) {
		this->x += moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[LEFT] && !this->activity && Map::scene % 2 != 0) {
		this->x -= moving_quantity;
		moving_distance++;
	}
	else if (minimum_score == score[UP] && !this->activity && Map::scene % 2 != 0) {
		this->y -= moving_quantity;
		moving_distance++;
	}
}

void EnemyWarrior_1::Attack(int* p_hp, int* sw1_hp, int* sw2_hp, int* sw3_hp, const int& a_order) {
	if (p_hp == nullptr || sw1_hp == nullptr || sw2_hp == nullptr || sw3_hp == nullptr) { return; }

	if (act_order == a_order) Move();

	if (activity && !attack_activity && Map::scene % 2 != 0
		&& act_order == a_order && Map::turn_timer > this->act_time) {
		if (parent_husteric[ENEMY_PRINCESS][LEFT] == 0
			|| parent_husteric[ENEMY_PRINCESS][RIGHT] == 0
			|| parent_husteric[ENEMY_PRINCESS][UP] == 0
			|| parent_husteric[ENEMY_PRINCESS][DOWN] == 0) {
			*p_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR1][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR1][DOWN] == 0) {
			*sw1_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR2][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR2][DOWN] == 0) {
			*sw2_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
		}
		else if (parent_husteric[ENEMY_WARRIOR3][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR3][DOWN] == 0) {
			*sw3_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
		}
	}

	if (Map::turn_timer >= 60) forward_act_order(a_order);
}

void EnemyWarrior_1::get_enemy_cost(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                    const int& ey3, const int& ex4, const int& ey4) {
	if (!this->activity) {
		if ((node_x[LEFT_X] == ex1 / block_size && node_y[CENTER_Y] == ey1 / block_size)
			|| (node_x[LEFT_X] == ex2 / block_size && node_y[CENTER_Y] == ey2 / block_size)
			|| (node_x[LEFT_X] == ex3 / block_size && node_y[CENTER_Y] == ey3 / block_size)
			|| (node_x[LEFT_X] == ex4 / block_size && node_y[CENTER_Y] == ey4 / block_size))
			enemy_cost[LEFT] = ENEMY_COST;
		else enemy_cost[LEFT] = 0;

		if ((node_x[RIGHT_X] == ex1 / block_size && node_y[CENTER_Y] == ey1 / block_size)
			|| (node_x[RIGHT_X] == ex2 / block_size && node_y[CENTER_Y] == ey2 / block_size)
			|| (node_x[RIGHT_X] == ex3 / block_size && node_y[CENTER_Y] == ey3 / block_size)
			|| (node_x[RIGHT_X] == ex4 / block_size && node_y[CENTER_Y] == ey4 / block_size))
			enemy_cost[RIGHT] = ENEMY_COST;
		else enemy_cost[RIGHT] = 0;

		if ((node_x[CENTER_X] == ex1 / block_size && node_y[UP_Y] == ey1 / block_size)
			|| (node_x[CENTER_X] == ex2 / block_size && node_y[UP_Y] == ey2 / block_size)
			|| (node_x[CENTER_X] == ex3 / block_size && node_y[UP_Y] == ey3 / block_size)
			|| (node_x[CENTER_X] == ex4 / block_size && node_y[UP_Y] == ey4 / block_size))
			enemy_cost[UP] = ENEMY_COST;
		else enemy_cost[UP] = 0;

		if ((node_x[CENTER_X] == ex1 / block_size && node_y[DOWN_Y] == ey1 / block_size)
			|| (node_x[CENTER_X] == ex2 / block_size && node_y[DOWN_Y] == ey2 / block_size)
			|| (node_x[CENTER_X] == ex3 / block_size && node_y[DOWN_Y] == ey3 / block_size)
			|| (node_x[CENTER_X] == ex4 / block_size && node_y[DOWN_Y] == ey4 / block_size))
			enemy_cost[DOWN] = ENEMY_COST;
		else enemy_cost[DOWN] = 0;
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

void EnemyWarrior_1::score_decision() {
	if (minimum_score == 1) {
		this->activity = true;
		moving_distance = this->range;
	}
}

void EnemyWarrior_1::moving_end() {
	if (this->range == moving_distance) {
		this->activity = true;
	}
}

void EnemyWarrior_1::activate_reset() {
	if (Map::scene % 2 == 0) {
		this->activity = false;
		attack_activity = false;
		fill(duplication_activity.begin(), duplication_activity.end(), false); //falseにリセット
		moving_distance = 0;
	}
}

void EnemyWarrior_1::duplicate_process(const int& dir_num) {
	enemy_cost[dir_num] = 2;
}

void EnemyWarrior_1::get_attack_direction(const int& player_num) {
	if (minimum_husteric2 == parent_husteric[player_num][LEFT]) {
		drawing_effect1(LEFT_X, CENTER_Y, LEFT);
	}
	else if (minimum_husteric2 == parent_husteric[player_num][RIGHT]) {
		drawing_effect1(RIGHT_X, CENTER_Y, RIGHT);
	}
	else if (minimum_husteric2 == parent_husteric[player_num][UP]) {
		drawing_effect1(CENTER_X, UP_Y, UP);
	}
	else if (minimum_husteric2 == parent_husteric[player_num][DOWN]) {
		drawing_effect1(CENTER_X, DOWN_Y, DOWN);
	}
}

void EnemyWarrior_1::get_slash_motion(const int& a_activity, int* motion) {
	if (motion == nullptr) { return; }
	*motion = a_activity ? ++*motion : -1;
}

void EnemyWarrior_1::forward_act_order(const int& a_order) {
	if (this->activity && act_order == a_order) {
		Map::turn_timer = 0;
		act_order = a_order + 1;
	}
}
