#include "enemyBandits.h"
#include "DxLib.h"
#include "cursor.h"
#include "constant.h"
#include "mapAll.h"
#include <algorithm>

EnemyBandits::EnemyBandits(int x, int y, int graph, int moving_quantity, int attack, int range, bool activity,
                           bool isAlive) :
	Enemy(x, y, graph, moving_quantity, attack, range, activity, isAlive),
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
	duplication_flag(4) {
	moving_distance = 0;
	husteric_x = 0;
	husteric_y = 0;
	minimum_husteric2 = 0;
	minimum_score = 0;
	attack_activity = false;
	attack_motion = 0;
	attack_motion = 0;
}

void EnemyBandits::Update(vector<vector<int>>& map) {
	get_latency();
	wait_motion();
	activate_reset();
	score_decision();
	moving_end();
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

void EnemyBandits::Draw() {
	if (this->x == current_x && this->y == current_y) {
		moving_range = this->range; //Ú®ÍÍðvC[Ú®ÍÍÉu··é
	}
	DrawRectGraph(this->x - current_x + block_size * 9,
	              this->y - init_position - current_y + block_size * 9,
	              src_x * block_size, block_size,
	              block_size, block_size,
	              this->graph, true, false);

	DrawFormatString(200, WIN_HEIGHT - block_size - 15, GetColor(0, 0, 0),
	                 "R¯(%d, %d)", x / block_size, y / block_size, false);
	DrawFormatString(200, WIN_HEIGHT - block_size, GetColor(0, 0, 0),
	                 "md:%d, Ac:%d", moving_distance, this->activity, false);
	DrawFormatString(200, WIN_HEIGHT - block_size + 15, GetColor(0, 0, 0),
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
	                 score[LEFT], score[RIGHT], score[UP], score[DOWN], minimum_score, false);
}

void EnemyBandits::drawing_effect1(const int& nx, const int& ny, const int& direction) {
	if (minimum_score == score[direction]) {
		DrawRectGraph(node_x[nx] * block_size - current_x + block_size * 9,
		              node_y[ny] * block_size - init_position - current_y + block_size * 9,
		              block_size * attack_motion, 0,
		              block_size, block_size,
		              slash, true, false);
	}
}

void EnemyBandits::drawing_effect2() {
	if (attack_activity) {
		drawing_effect1(LEFT_X, CENTER_Y, LEFT);
		drawing_effect1(RIGHT_X, CENTER_Y, RIGHT);
		drawing_effect1(CENTER_X, UP_Y, UP);
		drawing_effect1(CENTER_X, DOWN_Y, DOWN);
	}
}

void EnemyBandits::get_each_node() {
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
	/* P */
	parent_husteric[ENEMY_PRINCESS][LEFT] = abs(node_x[LEFT_X] - p_x / block_size)
		+ abs(node_y[CENTER_Y] - p_y / block_size); //Gl~[¶m[hÆPÌ2_Ô£
	parent_husteric[ENEMY_PRINCESS][RIGHT] = abs(node_x[RIGHT_X] - p_x / block_size)
		+ abs(node_y[CENTER_Y] - p_y / block_size); //Gl~[Em[hÆPÌ2_Ô£
	parent_husteric[ENEMY_PRINCESS][UP] = abs(node_x[CENTER_X] - p_x / block_size)
		+ abs(node_y[UP_Y] - p_y / block_size); //Gl~[ãm[hÆPÌ2_Ô£
	parent_husteric[ENEMY_PRINCESS][DOWN] = abs(node_x[CENTER_X] - p_x / block_size)
		+ abs(node_y[DOWN_Y] - p_y / block_size); //Gl~[ºm[hÆPÌ2_Ô£

	/* eÒ1 */
	parent_husteric[ENEMY_WARRIOR1][LEFT] = abs(node_x[LEFT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //Gl~[¶m[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR1][RIGHT] = abs(node_x[RIGHT_X] - sw1_x / block_size)
		+ abs(node_y[CENTER_Y] - sw1_y / block_size); //Gl~[Em[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR1][UP] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[UP_Y] - sw1_y / block_size); //Gl~[ãm[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR1][DOWN] = abs(node_x[CENTER_X] - sw1_x / block_size)
		+ abs(node_y[DOWN_Y] - sw1_y / block_size); //Gl~[ºm[hÆPÌ2_Ô£

	/* eÒ2 */
	parent_husteric[ENEMY_WARRIOR2][LEFT] = abs(node_x[LEFT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //Gl~[¶m[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR2][RIGHT] = abs(node_x[RIGHT_X] - sw2_x / block_size)
		+ abs(node_y[CENTER_Y] - sw2_y / block_size); //Gl~[Em[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR2][UP] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[UP_Y] - sw2_y / block_size); //Gl~[ãm[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR2][DOWN] = abs(node_x[CENTER_X] - sw2_x / block_size)
		+ abs(node_y[DOWN_Y] - sw2_y / block_size); //Gl~[ºm[hÆPÌ2_Ô£

	/* eÒ3 */
	parent_husteric[ENEMY_WARRIOR3][LEFT] = abs(node_x[LEFT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //Gl~[¶m[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR3][RIGHT] = abs(node_x[RIGHT_X] - sw3_x / block_size)
		+ abs(node_y[CENTER_Y] - sw3_y / block_size); //Gl~[Em[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR3][UP] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[UP_Y] - sw3_y / block_size); //Gl~[ãm[hÆPÌ2_Ô£
	parent_husteric[ENEMY_WARRIOR3][DOWN] = abs(node_x[CENTER_X] - sw3_x / block_size)
		+ abs(node_y[DOWN_Y] - sw3_y / block_size); //Gl~[ºm[hÆPÌ2_Ô£

	/* vC[ÆÌÎÊuRXgvZ */
	relative_distance[X] = set_to_one(node_x[CENTER_X] - (p_x / block_size)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_x[CENTER_X] - (sw1_x / block_size)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_x[CENTER_X] - (sw2_x / block_size)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_x[CENTER_X] - (sw3_x / block_size)) * survival_value[ENEMY_WARRIOR3];
	relative_distance[Y] = set_to_one(node_y[CENTER_Y] - (p_y / block_size)) * survival_value[ENEMY_PRINCESS]
		+ set_to_one(node_y[CENTER_Y] - (sw1_y / block_size)) * survival_value[ENEMY_WARRIOR1]
		+ set_to_one(node_y[CENTER_Y] - (sw2_y / block_size)) * survival_value[ENEMY_WARRIOR2]
		+ set_to_one(node_y[CENTER_Y] - (sw3_y / block_size)) * survival_value[ENEMY_WARRIOR3];
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
	/* ¶¤ÌRXg */
	if (map[node_y[CENTER_Y]][node_x[LEFT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[LEFT_X]] == TIDE && Map::scene >= 2)) {
		obstacle_cost[LEFT] = 10;
	}
	else obstacle_cost[LEFT] = 0;

	/* E¤ÌRXg */
	if (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == SEA
		|| (map[node_y[CENTER_Y]][node_x[RIGHT_X]] == TIDE && Map::scene >= 2)) {
		obstacle_cost[RIGHT] = 10;
	}
	else obstacle_cost[RIGHT] = 0;

	/* ã¤ÌRXg */
	if (map[node_y[UP_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[UP_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)) {
		obstacle_cost[UP] = 10;
	}
	else obstacle_cost[UP] = 0;

	/* º¤ÌRXg */
	if (map[node_y[DOWN_Y]][node_x[CENTER_X]] == SEA
		|| (map[node_y[DOWN_Y]][node_x[CENTER_X]] == TIDE && Map::scene >= 2)) {
		obstacle_cost[DOWN] = 10;
	}
	else obstacle_cost[DOWN] = 0;
}

void EnemyBandits::get_relative_position_cost() {
	/* xûüÌÎÊuRXg */
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

	/* yûüÌÎÊuRXg */
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

void EnemyBandits::Move(const int& ew1_x, const int& ew1_y) {
	if (this->range == moving_distance && !this->activity) {
		if (node_x[CENTER_X] == ew1_x / block_size && node_y[CENTER_Y] == ew1_y / block_size)
			duplicate_process();
	}

	if (Map::turn_timer % MOVEING_INTERVAL == 0
		&& Map::turn_timer > 100
		&& !this->activity) {
		moving_decision();
	}
}

void EnemyBandits::moving_decision() {
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

	if (activity && !attack_activity && Map::scene % 2 != 0) {
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
}

void EnemyBandits::Dead(vector<vector<int>>& map) {
	if (map[this->y / block_size][this->x / block_size] == TIDE
		&& Map::scene == NIGHT_PLAY) {
		this->isAlive = false; //¶¶óÔðfalse
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
		fill(duplication_flag.begin(), duplication_flag.end(), false); //falseÉZbg
		moving_distance = 0;
	}
}

void EnemyBandits::duplicate_process() {
	if (minimum_score == score[DOWN] && !duplication_flag[DOWN]) {
		this->y -= moving_quantity;
		duplication_flag[DOWN] = true;
	}
	else if (minimum_score == score[RIGHT] && !duplication_flag[RIGHT]) {
		this->x -= moving_quantity;
		duplication_flag[RIGHT] = true;
	}
	else if (minimum_score == score[LEFT] && !duplication_flag[LEFT]) {
		this->x += moving_quantity;
		duplication_flag[LEFT] = true;
	}
	else if (minimum_score == score[UP] && !duplication_flag[UP]) {
		this->y += moving_quantity;
		duplication_flag[UP] = true;
	}
}
