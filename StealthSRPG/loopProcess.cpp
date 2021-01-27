#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "mapDraw.h"
#include "mapUI.h"
#include "cursor.h"
#include "charactor.h"
#include "Princess.h"
#include "shadowWarrior_1.h"
#include "shadowWarrior_2.h"
#include "shadowWarrior_3.h"
#include "enemy.h"
#include "enemyWarrior_1.h"
#include "enemyWarrior_2.h"
#include "enemyBandits.h"
#include "enemyWolf1.h"
#include "sceneTransition.h"
#include "gameResult.h"
#include "gameHelp.h"
#include <cstdlib>
#include <vector>

#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

using namespace std;

void loop_process() {

	Input input;

	const int player_graph = LoadGraph("Source/Charactor/Player/princess.png");
	Princess Princess(
		block_size * 8, block_size * 8, player_graph,
		block_size, 4, 4, false, true, input);

	ShadowWarrior_1 Warrior1(
		block_size * 8, block_size * 9, player_graph,
		block_size, 6, 3, false, true, input);

	ShadowWarrior_2 Warrior2(
		block_size * 9, block_size * 8, player_graph,
		block_size, 6, 3, false, true, input);

	ShadowWarrior_3 Warrior3(
		block_size * 7, block_size * 8, player_graph,
		block_size, 6, 3, false, true, input);

	const int enemy_graph = LoadGraph("Source/Charactor/Enemy/enemies.png");
	Enemy* enemies[] = {
			new EnemyWarrior_1(block_size * 5, block_size * 12, enemy_graph,
			                   block_size, 3, 3, 30, false, true),
			new EnemyWarrior_1(block_size * 10, block_size * 13, enemy_graph,
			                   block_size, 3, 3, 30, false, true),
			new EnemyBandits(block_size * 14, block_size * 14, enemy_graph,
			                 block_size, 4, 2, 20, false, true),
			new EnemyWolf_1(block_size * 6, block_size * 6, enemy_graph,
			                block_size, 2, 4, 20, false, true),
		};

	// ゲームループ
	while (true) {
		ClearDrawScreen(); //画面クリア

		input.input_info(); //入力情報

		MapDraw* _map = new MapDraw;

		if (SceneTransition::game_scene <= STAGE2) {

			_map->drawing_map(enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
			                  enemies[2]->x, enemies[2]->y, enemies[3]->x, enemies[3]->y); //マップ描画

			input.map_scene_update(_map->map_20x20, enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
			                       enemies[2]->x, enemies[2]->y); //入力更新処理

			Princess.Update(Warrior1.x, Warrior1.y, Warrior2.x, Warrior2.y,
			                Warrior3.x, Warrior3.y, enemies[0]->x, enemies[0]->y,
			                enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y); //姫の更新処理
			Princess.Dead(_map->map_20x20); //姫の死亡処理
			Warrior1.Update(Princess.x, Princess.y, Warrior2.x, Warrior2.y,
			                Warrior3.x, Warrior3.y, enemies[0]->x, enemies[0]->y,
			                enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y); //影武者1の更新処理
			Warrior1.Dead(_map->map_20x20); //姫の死亡処理
			Warrior2.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                Warrior3.x, Warrior3.y, enemies[0]->x, enemies[0]->y,
			                enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y); //影武者2の更新処理
			Warrior2.Dead(_map->map_20x20); //姫の死亡処理
			Warrior3.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                Warrior2.x, Warrior2.y, enemies[0]->x, enemies[0]->y,
			                enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y); //影武者3の更新処理
			Warrior3.Dead(_map->map_20x20); //姫の死亡処理

			for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
				enemies[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
				                                  Warrior2.isAlive, Warrior3.isAlive);
				enemies[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
				                                   Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
				enemies[i]->get_enemy_cost(enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
				                           enemies[2]->x, enemies[2]->y, enemies[3]->x, enemies[3]->y);
				enemies[i]->Update(_map->map_20x20); //敵兵1の更新処理
				enemies[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i);
			}

			Cursor* cursor = new Cursor;
			cursor->update();
			if (Map::scene % 2 != 0) {
				cursor->move(Princess.x, Princess.y, enemies[0]->x, enemies[0]->y,
				             enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y, enemies[3]->x, enemies[3]->y);
			}
			delete cursor;

			MapUI* UI = new MapUI;
			UI->yes_or_no(input.yes_or_no);
			UI->drawing_life_status(Princess.hp, Warrior1.hp, Warrior2.hp, Warrior3.hp,
			                        Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
			UI->update();
			delete UI;
		}
		else if (SceneTransition::game_scene == GAME_RESULT) {
			Princess.set_next_map_node(input.current_map_scene);
			Warrior1.set_next_map_node(input.current_map_scene);
			Warrior2.set_next_map_node(input.current_map_scene);
			Warrior3.set_next_map_node(input.current_map_scene);
			input.game_result_update();
		}
		else if (SceneTransition::game_scene == GAME_HELP) {
			input.game_help_update();
		}

		SceneTransition* scene = new SceneTransition;
		if (_map->map_20x20[(Princess.y / block_size)][(Princess.x / block_size)] == GOAL
			&& Princess.moving_flag == -1)
			scene->transition_to_result();
		delete scene;

		GameResult* result = new GameResult;
		result->rank_check(Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
		result->update();
		delete result;

		delete _map;

		DrawFormatString(700, 0, GetColor(255, 0, 255),
		                 "Scene:%d, help:%d", SceneTransition::game_scene, GameHelp::help_num, false);

		window_in_roop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}

	for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
		delete enemies[i];
	}
}
