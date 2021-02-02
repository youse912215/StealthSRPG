#include "enemyBandits.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "inputProcess.h"
#include "sceneTransition.h"
#include "mapAll.h"
#include "music.h"
#include <algorithm>

EnemyBandits::EnemyBandits(int x, int y, int graph, int moving_quantity, int attack, int range, int act_time,
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
	init_x = 0;
	init_y = 0;
}

void EnemyBandits::Update(vector<vector<int>>& map) {
	get_latency();
	wait_motion();
	activate_reset();
	score_decision();
	moving_end();
	reset_act_order();
	get_slash_motion(this->attack_activity, &attack_motion);
	Draw();
	drawing_effect2();
	if (Map::turn_count == 0) get_init_node();
	get_each_node();
	get_minimum_husteric();
	get_node_husteric();
	get_obstacle_cost(map);
	get_relative_position_cost();
	get_node_cost();
	get_node_score();
	Dead(map);
	reset();
}

void EnemyBandits::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //移動範囲をプレイヤー移動範囲に置換する
	}
	DrawRectGraph(this->x - current_x + BLOCK_SIZE * 9,
	              this->y - INIT_POSITION - current_y + BLOCK_SIZE * 9,
	              src_x * BLOCK_SIZE, BLOCK_SIZE,
	              BLOCK_SIZE, BLOCK_SIZE,
	              this->graph, true, false);

	/*DrawFormatString(200, WIN_HEIGHT - BLOCK_SIZE - 15, GetColor(0, 0, 0),
	                 "山賊(%d, %d)", x / BLOCK_SIZE, y / BLOCK_SIZE, false);
	DrawFormatString(200, WIN_HEIGHT - BLOCK_SIZE, GetColor(0, 0, 0),
	                 "md:%d, Ac:%d", MOVING_DISTANCE, this->activity, false);
	DrawFormatString(200, WIN_HEIGHT - BLOCK_SIZE + 15, GetColor(0, 0, 0),
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
	                 parent_heuristic[ENEMY_PRINCESS][LEFT], parent_heuristic[ENEMY_PRINCESS][RIGHT],
	                 parent_heuristic[ENEMY_PRINCESS][UP], parent_heuristic[ENEMY_PRINCESS][DOWN], false);
	DrawFormatString(480, 430, GetColor(200, 255, 125), "w1Hus:L%d, R%d, U%d, D%d",
	                 parent_heuristic[ENEMY_WARRIOR1][LEFT], parent_heuristic[ENEMY_WARRIOR1][RIGHT],
	                 parent_heuristic[ENEMY_WARRIOR1][UP], parent_heuristic[ENEMY_WARRIOR1][DOWN], false);
	DrawFormatString(480, 445, GetColor(200, 255, 125), "w2Hus:L%d, R%d, U%d, D%d",
	                 parent_heuristic[ENEMY_WARRIOR2][LEFT], parent_heuristic[ENEMY_WARRIOR2][RIGHT],
	                 parent_heuristic[ENEMY_WARRIOR2][UP], parent_heuristic[ENEMY_WARRIOR2][DOWN], false);
	DrawFormatString(480, 460, GetColor(200, 255, 125), "w3Hus:L%d, R%d, U%d, D%d",
	                 parent_heuristic[ENEMY_WARRIOR3][LEFT], parent_heuristic[ENEMY_WARRIOR3][RIGHT],
	                 parent_heuristic[ENEMY_WARRIOR3][UP], parent_heuristic[ENEMY_WARRIOR3][DOWN], false);
	DrawFormatString(480, 475, GetColor(200, 255, 125), "mHus:p%d, w%d, w%d, w%d",
	                 minimum_heuristic1[ENEMY_PRINCESS], minimum_heuristic1[ENEMY_WARRIOR1],
	                 minimum_heuristic1[ENEMY_WARRIOR2], minimum_heuristic1[ENEMY_WARRIOR3], false);
	DrawFormatString(480, 490, GetColor(200, 255, 125), "obs_cost:L%d, R%d, U%d, D%d",
	                 obstacle_cost[LEFT], obstacle_cost[RIGHT], obstacle_cost[UP], obstacle_cost[DOWN], false);
	DrawFormatString(480, 505, GetColor(200, 255, 125), "cost:L%d, R%d, U%d, D%d",
	                 cost[LEFT], cost[RIGHT], cost[UP], cost[DOWN], false);
	DrawFormatString(480, 520, GetColor(255, 0, 50), "score:L%d, R%d, U%d, D%d, %d",
	                 score[LEFT], score[RIGHT], score[UP], score[DOWN], minimum_score, false);*/
}

void EnemyBandits::drawing_effect1(const int& nx, const int& ny, const int& direction) {
	if (husteric[direction] == 0) {
		DrawRectGraph(node_x[nx] * BLOCK_SIZE - current_x + BLOCK_SIZE * 9,
		              node_y[ny] * BLOCK_SIZE - INIT_POSITION - current_y + BLOCK_SIZE * 9,
		              BLOCK_SIZE * attack_motion, 0,
		              BLOCK_SIZE, BLOCK_SIZE,
		              slash, true, false);
	}
}

void EnemyBandits::drawing_effect2() {
	if (attack_activity) {
		get_attack_direction(ENEMY_PRINCESS);
		get_attack_direction(ENEMY_WARRIOR1);
		get_attack_direction(ENEMY_WARRIOR2);
		get_attack_direction(ENEMY_WARRIOR3);
	}
}

void EnemyBandits::get_each_node() {
	node_x[LEFT_X] = (this->x - BLOCK_SIZE) / BLOCK_SIZE;
	node_x[CENTER_X] = (this->x) / BLOCK_SIZE;
	node_x[RIGHT_X] = (this->x + BLOCK_SIZE) / BLOCK_SIZE;
	node_x[LEFT_2X] = (this->x - BLOCK_SIZE * 2) / BLOCK_SIZE;
	node_x[RIGHT_2X] = (this->x + BLOCK_SIZE * 2) / BLOCK_SIZE;

	node_y[UP_Y] = (this->y - BLOCK_SIZE) / BLOCK_SIZE;
	node_y[CENTER_Y] = (this->y) / BLOCK_SIZE;
	node_y[DOWN_Y] = (this->y + BLOCK_SIZE) / BLOCK_SIZE;
	node_y[UP_2Y] = (this->y - BLOCK_SIZE * 2) / BLOCK_SIZE;
	node_y[DOWN_2Y] = (this->y + BLOCK_SIZE * 2) / BLOCK_SIZE;
}

void EnemyBandits::get_survival_activity(const bool& p_s_activity, const bool& sw1_s_activity,
                                         const bool& sw2_s_activity,
                                         const bool& sw3_s_activity) {
	survival_value[ENEMY_PRINCESS] = p_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR1] = sw1_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR2] = sw2_s_activity ? 1 : 0;
	survival_value[ENEMY_WARRIOR3] = sw3_s_activity ? 1 : 0;
}

void EnemyBandits::get_two_point_distance(const int& p_x, const int& p_y, const int& sw1_x, const int& sw1_y,
                                          const int& sw2_x,
                                          const int& sw2_y, const int& sw3_x, const int& sw3_y) {
	/* 姫 */
	parent_husteric[ENEMY_PRINCESS][LEFT] = abs(node_x[LEFT_X] - p_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - p_y / BLOCK_SIZE); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][RIGHT] = abs(node_x[RIGHT_X] - p_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - p_y / BLOCK_SIZE); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][UP] = abs(node_x[CENTER_X] - p_x / BLOCK_SIZE)
		+ abs(node_y[UP_Y] - p_y / BLOCK_SIZE); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_PRINCESS][DOWN] = abs(node_x[CENTER_X] - p_x / BLOCK_SIZE)
		+ abs(node_y[DOWN_Y] - p_y / BLOCK_SIZE); //エネミー下ノードと姫の2点間距離

	/* 影武者1 */
	parent_husteric[ENEMY_WARRIOR1][LEFT] = abs(node_x[LEFT_X] - sw1_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw1_y / BLOCK_SIZE); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][RIGHT] = abs(node_x[RIGHT_X] - sw1_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw1_y / BLOCK_SIZE); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][UP] = abs(node_x[CENTER_X] - sw1_x / BLOCK_SIZE)
		+ abs(node_y[UP_Y] - sw1_y / BLOCK_SIZE); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR1][DOWN] = abs(node_x[CENTER_X] - sw1_x / BLOCK_SIZE)
		+ abs(node_y[DOWN_Y] - sw1_y / BLOCK_SIZE); //エネミー下ノードと姫の2点間距離

	/* 影武者2 */
	parent_husteric[ENEMY_WARRIOR2][LEFT] = abs(node_x[LEFT_X] - sw2_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw2_y / BLOCK_SIZE); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][RIGHT] = abs(node_x[RIGHT_X] - sw2_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw2_y / BLOCK_SIZE); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][UP] = abs(node_x[CENTER_X] - sw2_x / BLOCK_SIZE)
		+ abs(node_y[UP_Y] - sw2_y / BLOCK_SIZE); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR2][DOWN] = abs(node_x[CENTER_X] - sw2_x / BLOCK_SIZE)
		+ abs(node_y[DOWN_Y] - sw2_y / BLOCK_SIZE); //エネミー下ノードと姫の2点間距離

	/* 影武者3 */
	parent_husteric[ENEMY_WARRIOR3][LEFT] = abs(node_x[LEFT_X] - sw3_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw3_y / BLOCK_SIZE); //エネミー左ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][RIGHT] = abs(node_x[RIGHT_X] - sw3_x / BLOCK_SIZE)
		+ abs(node_y[CENTER_Y] - sw3_y / BLOCK_SIZE); //エネミー右ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][UP] = abs(node_x[CENTER_X] - sw3_x / BLOCK_SIZE)
		+ abs(node_y[UP_Y] - sw3_y / BLOCK_SIZE); //エネミー上ノードと姫の2点間距離
	parent_husteric[ENEMY_WARRIOR3][DOWN] = abs(node_x[CENTER_X] - sw3_x / BLOCK_SIZE)
		+ abs(node_y[DOWN_Y] - sw3_y / BLOCK_SIZE); //エネミー下ノードと姫の2点間距離

	/* プレイヤーとの相対位置コスト計算 */
	relative_distance[X] = set_to_one(node_x[CENTER_X] - (p_x / BLOCK_SIZE)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_x[CENTER_X] - (sw1_x / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_x[CENTER_X] - (sw2_x / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_x[CENTER_X] - (sw3_x / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR3];
	relative_distance[Y] = set_to_one(node_y[CENTER_Y] - (p_y / BLOCK_SIZE)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_y[CENTER_Y] - (sw1_y / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_y[CENTER_Y] - (sw2_y / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_y[CENTER_Y] - (sw3_y / BLOCK_SIZE)) * survival_value[ENEMY_WARRIOR3];
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
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == ICE_LAND && Map::scene <= 1)
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == ICE_SEA && Map::scene <= 1)) {
		obstacle_cost[LEFT] = 10;
	}
	else obstacle_cost[LEFT] = 0;

	/* 右側のコスト */
	if (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == ICE_LAND && Map::scene <= 1)
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == ICE_SEA && Map::scene <= 1)) {
		obstacle_cost[RIGHT] = 10;
	}
	else obstacle_cost[RIGHT] = 0;

	/* 上側のコスト */
	if (map[node_y[UP_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == ICE_LAND && Map::scene <= 1)
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == ICE_SEA && Map::scene <= 1)) {
		obstacle_cost[UP] = 10;
	}
	else obstacle_cost[UP] = 0;

	/* 下側のコスト */
	if (map[node_y[DOWN_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == ICE_LAND && Map::scene <= 1)
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == ICE_SEA && Map::scene <= 1)) {
		obstacle_cost[DOWN] = 10;
	}
	else obstacle_cost[DOWN] = 0;
}

void EnemyBandits::get_relative_position_cost() {
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

void EnemyBandits::get_node_cost() {
	cost[LEFT] = abs(
		node_x[CENTER_X] - node_x[LEFT_X] + obstacle_cost[LEFT] + relative_position_cost[LEFT] + enemy_cost[LEFT]);
	cost[RIGHT] = abs(
		node_x[CENTER_X] - node_x[RIGHT_X] + obstacle_cost[RIGHT] + relative_position_cost[RIGHT] + enemy_cost[RIGHT]);
	cost[UP] = abs(
		node_y[CENTER_Y] - node_y[UP_Y] + obstacle_cost[UP] + relative_position_cost[UP] + enemy_cost[UP]);
	cost[DOWN] = abs(
		node_y[CENTER_Y] - node_y[DOWN_Y] + obstacle_cost[DOWN] + relative_position_cost[DOWN] + enemy_cost[DOWN]);
}

void EnemyBandits::get_node_score() {
	score[LEFT] = cost[LEFT] + husteric[LEFT];
	score[RIGHT] = cost[RIGHT] + husteric[RIGHT];
	score[UP] = cost[UP] + husteric[UP];
	score[DOWN] = cost[DOWN] + husteric[DOWN];
	minimum_score = *min_element(score.begin(), score.end());
}

void EnemyBandits::Move() {
	if (Map::turn_timer % MOVING_INTERVAL == 0
		&& Map::turn_timer > 0
		&& !this->activity) {
		moving_decision();
	}
}

void EnemyBandits::moving_decision() {
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

void EnemyBandits::Attack(int* p_hp, int* sw1_hp, int* sw2_hp, int* sw3_hp, const int& a_order, const int& se1,
                          const int& se2) {
	if (p_hp == nullptr || sw1_hp == nullptr || sw2_hp == nullptr || sw3_hp == nullptr) { return; }

	if (act_order == a_order && minimum_husteric2 != 0) Move();

	if (activity && !attack_activity && Map::scene % 2 != 0
		&& act_order == a_order && Map::turn_timer > this->act_time) {
		if (parent_husteric[ENEMY_PRINCESS][LEFT] == 0
			|| parent_husteric[ENEMY_PRINCESS][RIGHT] == 0
			|| parent_husteric[ENEMY_PRINCESS][UP] == 0
			|| parent_husteric[ENEMY_PRINCESS][DOWN] == 0) {
			*p_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
			get_sound_se(se1);
		}
		else if (parent_husteric[ENEMY_WARRIOR1][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR1][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR1][DOWN] == 0) {
			*sw1_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
			get_sound_se(se1);
		}
		else if (parent_husteric[ENEMY_WARRIOR2][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR2][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR2][DOWN] == 0) {
			*sw2_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
			get_sound_se(se1);
		}
		else if (parent_husteric[ENEMY_WARRIOR3][LEFT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][RIGHT] == 0
			|| parent_husteric[ENEMY_WARRIOR3][UP] == 0
			|| parent_husteric[ENEMY_WARRIOR3][DOWN] == 0) {
			*sw3_hp -= this->attack;
			attack_activity = true;
			this->activity = true;
			get_sound_se(se1);
		}

	}
	if (Map::turn_timer >= ENEMY_TURN_TIME) forward_act_order(a_order);
	else if (Map::turn_timer >= 10 && this->range == 0) forward_act_order(a_order);
}

void EnemyBandits::get_enemy_cost_0(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                    const int& ey3) {
	if (!this->activity) {
		if ((node_x[LEFT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE))
			enemy_cost[LEFT] = ENEMY_COST;
		else enemy_cost[LEFT] = 0;

		if ((node_x[RIGHT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE))
			enemy_cost[RIGHT] = ENEMY_COST;
		else enemy_cost[RIGHT] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[UP_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[UP_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[UP_Y] == ey3 / BLOCK_SIZE))
			enemy_cost[UP] = ENEMY_COST;
		else enemy_cost[UP] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[DOWN_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[DOWN_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[DOWN_Y] == ey3 / BLOCK_SIZE))
			enemy_cost[DOWN] = ENEMY_COST;
		else enemy_cost[DOWN] = 0;
	}
}

void EnemyBandits::get_enemy_cost_1(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                    const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                                    const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
                                    const int& ey8) {
	if (!this->activity) {
		if ((node_x[LEFT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex4 / BLOCK_SIZE && node_y[CENTER_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex5 / BLOCK_SIZE && node_y[CENTER_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex6 / BLOCK_SIZE && node_y[CENTER_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex7 / BLOCK_SIZE && node_y[CENTER_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex8 / BLOCK_SIZE && node_y[CENTER_Y] == ey8 / BLOCK_SIZE))
			enemy_cost[LEFT] = ENEMY_COST;
		else enemy_cost[LEFT] = 0;

		if ((node_x[RIGHT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex4 / BLOCK_SIZE && node_y[CENTER_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex5 / BLOCK_SIZE && node_y[CENTER_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex6 / BLOCK_SIZE && node_y[CENTER_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex7 / BLOCK_SIZE && node_y[CENTER_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex8 / BLOCK_SIZE && node_y[CENTER_Y] == ey8 / BLOCK_SIZE))
			enemy_cost[RIGHT] = ENEMY_COST;
		else enemy_cost[RIGHT] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[UP_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[UP_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[UP_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex4 / BLOCK_SIZE && node_y[UP_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex5 / BLOCK_SIZE && node_y[UP_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex6 / BLOCK_SIZE && node_y[UP_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex7 / BLOCK_SIZE && node_y[UP_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex8 / BLOCK_SIZE && node_y[UP_Y] == ey8 / BLOCK_SIZE))
			enemy_cost[UP] = ENEMY_COST;
		else enemy_cost[UP] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[DOWN_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[DOWN_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[DOWN_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex4 / BLOCK_SIZE && node_y[DOWN_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex5 / BLOCK_SIZE && node_y[DOWN_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex6 / BLOCK_SIZE && node_y[DOWN_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex7 / BLOCK_SIZE && node_y[DOWN_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex8 / BLOCK_SIZE && node_y[DOWN_Y] == ey8 / BLOCK_SIZE))
			enemy_cost[DOWN] = ENEMY_COST;
		else enemy_cost[DOWN] = 0;
	}
}

void EnemyBandits::get_enemy_cost_2(const int& ex1, const int& ey1, const int& ex2, const int& ey2, const int& ex3,
                                    const int& ey3, const int& ex4, const int& ey4, const int& ex5, const int& ey5,
                                    const int& ex6, const int& ey6, const int& ex7, const int& ey7, const int& ex8,
                                    const int& ey8, const int& ex9, const int& ey9, const int& ex10, const int& ey10,
                                    const int& ex11, const int& ey11) {
	if (!this->activity) {
		if ((node_x[LEFT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex4 / BLOCK_SIZE && node_y[CENTER_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex5 / BLOCK_SIZE && node_y[CENTER_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex6 / BLOCK_SIZE && node_y[CENTER_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex7 / BLOCK_SIZE && node_y[CENTER_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex8 / BLOCK_SIZE && node_y[CENTER_Y] == ey8 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex9 / BLOCK_SIZE && node_y[CENTER_Y] == ey9 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex10 / BLOCK_SIZE && node_y[CENTER_Y] == ey10 / BLOCK_SIZE)
			|| (node_x[LEFT_X] == ex11 / BLOCK_SIZE && node_y[CENTER_Y] == ey11 / BLOCK_SIZE))
			enemy_cost[LEFT] = ENEMY_COST;
		else enemy_cost[LEFT] = 0;

		if ((node_x[RIGHT_X] == ex1 / BLOCK_SIZE && node_y[CENTER_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex2 / BLOCK_SIZE && node_y[CENTER_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex3 / BLOCK_SIZE && node_y[CENTER_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex4 / BLOCK_SIZE && node_y[CENTER_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex5 / BLOCK_SIZE && node_y[CENTER_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex6 / BLOCK_SIZE && node_y[CENTER_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex7 / BLOCK_SIZE && node_y[CENTER_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex8 / BLOCK_SIZE && node_y[CENTER_Y] == ey8 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex9 / BLOCK_SIZE && node_y[CENTER_Y] == ey9 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex10 / BLOCK_SIZE && node_y[CENTER_Y] == ey10 / BLOCK_SIZE)
			|| (node_x[RIGHT_X] == ex11 / BLOCK_SIZE && node_y[CENTER_Y] == ey11 / BLOCK_SIZE))
			enemy_cost[RIGHT] = ENEMY_COST;
		else enemy_cost[RIGHT] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[UP_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[UP_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[UP_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex4 / BLOCK_SIZE && node_y[UP_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex5 / BLOCK_SIZE && node_y[UP_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex6 / BLOCK_SIZE && node_y[UP_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex7 / BLOCK_SIZE && node_y[UP_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex8 / BLOCK_SIZE && node_y[UP_Y] == ey8 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex9 / BLOCK_SIZE && node_y[UP_Y] == ey9 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex10 / BLOCK_SIZE && node_y[UP_Y] == ey10 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex11 / BLOCK_SIZE && node_y[UP_Y] == ey11 / BLOCK_SIZE))
			enemy_cost[UP] = ENEMY_COST;
		else enemy_cost[UP] = 0;

		if ((node_x[CENTER_X] == ex1 / BLOCK_SIZE && node_y[DOWN_Y] == ey1 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex2 / BLOCK_SIZE && node_y[DOWN_Y] == ey2 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex3 / BLOCK_SIZE && node_y[DOWN_Y] == ey3 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex4 / BLOCK_SIZE && node_y[DOWN_Y] == ey4 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex5 / BLOCK_SIZE && node_y[DOWN_Y] == ey5 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex6 / BLOCK_SIZE && node_y[DOWN_Y] == ey6 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex7 / BLOCK_SIZE && node_y[DOWN_Y] == ey7 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex8 / BLOCK_SIZE && node_y[DOWN_Y] == ey8 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex9 / BLOCK_SIZE && node_y[DOWN_Y] == ey9 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex10 / BLOCK_SIZE && node_y[DOWN_Y] == ey10 / BLOCK_SIZE)
			|| (node_x[CENTER_X] == ex11 / BLOCK_SIZE && node_y[DOWN_Y] == ey11 / BLOCK_SIZE))
			enemy_cost[DOWN] = ENEMY_COST;
		else enemy_cost[DOWN] = 0;
	}
}

void EnemyBandits::Dead(vector<vector<int>>& map) {
	if ((map[this->y / BLOCK_SIZE][this->x / BLOCK_SIZE] == TIDE && Map::scene == NIGHT_PLAY)
		|| (map[this->y / BLOCK_SIZE][this->x / BLOCK_SIZE] == ICE_LAND && Map::scene == NOON_PLAY)
		|| (map[this->y / BLOCK_SIZE][this->x / BLOCK_SIZE] == ICE_SEA && Map::scene == NOON_PLAY)) {
		this->isAlive = false; //生存状態をfalse
		this->x = -1;
		this->y = -1;
	}
}

void EnemyBandits::score_decision() {
	if (minimum_score == 1) {
		this->activity = true;
		moving_distance = this->range;
	}
}

void EnemyBandits::moving_end() {
	if (this->range == moving_distance) {
		this->activity = true;
	}
}

void EnemyBandits::activate_reset() {
	if (Map::scene % 2 == 0) {
		this->activity = false;
		attack_activity = false;
		fill(duplication_activity.begin(), duplication_activity.end(), false); //falseにリセット
		moving_distance = 0;
	}
}

void EnemyBandits::duplicate_process(const int& dir_num) {
	enemy_cost[dir_num] = 2;
}

void EnemyBandits::get_attack_direction(const int& player_num) {

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

void EnemyBandits::get_slash_motion(const int& a_activity, int* motion) {
	if (motion == nullptr) { return; }
	*motion = a_activity ? ++*motion : -1;
}

void EnemyBandits::get_init_node() {
	init_x = this->x;
	init_y = this->y;
}

void EnemyBandits::forward_act_order(const int& a_order) {
	if (act_order == a_order) {
		Map::turn_timer = 0;
		act_order = a_order + 1;
	}
}

void EnemyBandits::reset() {
	if (SceneTransition::game_scene == GAME_RESULT) {
		this->x = init_x;
		this->y = init_y;
		this->isAlive = true;
	}
}
