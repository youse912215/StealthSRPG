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
#include "enemyBandits.h"
#include "enemyWolf1.h"
#include "sceneTransition.h"
#include "gameTitle.h"
#include "gameResult.h"
#include "gameHelp.h"
#include <cstdlib>

#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

using namespace std;

void loop_process() {

	Input input;

	const int player_graph = LoadGraph("Source/Charactor/Player/princess.png");
	Princess Princess(
		BLOCK_SIZE * 8, BLOCK_SIZE * 8, player_graph,
		BLOCK_SIZE, 6, 4, false, true, input);

	ShadowWarrior_1 Warrior1(
		BLOCK_SIZE * 8, BLOCK_SIZE * 9, player_graph,
		BLOCK_SIZE, 6, 3, false, true, input);

	ShadowWarrior_2 Warrior2(
		BLOCK_SIZE * 9, BLOCK_SIZE * 8, player_graph,
		BLOCK_SIZE, 6, 3, false, true, input);

	ShadowWarrior_3 Warrior3(
		BLOCK_SIZE * 7, BLOCK_SIZE * 8, player_graph,
		BLOCK_SIZE, 6, 3, false, true, input);

	const int enemy_graph = LoadGraph("Source/Charactor/Enemy/enemies.png");
	Enemy* enemies[] = {
			/* チュートリアル */
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 12, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 10, BLOCK_SIZE * 13, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 14, BLOCK_SIZE * 14, enemy_graph,
			                 BLOCK_SIZE, 4, 2, 20, false, true),
		};
	Enemy* enemies2[] = {
			/* ステージ1 */
			new EnemyWolf_1(BLOCK_SIZE * 11, BLOCK_SIZE * 8, enemy_graph,
			                BLOCK_SIZE, 1, 4, 20, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 18, BLOCK_SIZE * 6, enemy_graph,
			                BLOCK_SIZE, 1, 4, 20, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 9, BLOCK_SIZE * 1, enemy_graph,
			                BLOCK_SIZE, 1, 0, 20, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 9, BLOCK_SIZE * 3, enemy_graph,
			                BLOCK_SIZE, 1, 0, 20, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 3, BLOCK_SIZE * 9, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 13, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 18, BLOCK_SIZE * 12, enemy_graph,
			                 BLOCK_SIZE, 3, 2, 20, false, true),
			new EnemyBandits(BLOCK_SIZE * 18, BLOCK_SIZE * 15, enemy_graph,
			                 BLOCK_SIZE, 3, 2, 20, false, true),
		};

	Enemy* enemies3[] = {
			new EnemyWolf_1(BLOCK_SIZE * 11, BLOCK_SIZE * 3, enemy_graph,
			                BLOCK_SIZE, 1, 4, 20, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 11, BLOCK_SIZE * 4, enemy_graph,
			                BLOCK_SIZE, 1, 4, 20, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 7, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 8, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 6, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 5, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 6, BLOCK_SIZE * 6, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 6, BLOCK_SIZE * 5, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 10, BLOCK_SIZE * 11, enemy_graph,
			                 BLOCK_SIZE, 3, 2, 20, false, true),
			new EnemyBandits(BLOCK_SIZE * 10, BLOCK_SIZE * 12, enemy_graph,
			                 BLOCK_SIZE, 3, 2, 20, false, true),
			new EnemyBandits(BLOCK_SIZE * 9, BLOCK_SIZE * 13, enemy_graph,
			                 BLOCK_SIZE, 3, 2, 20, false, true),
		};

	// ゲームループ
	while (true) {
		ClearDrawScreen(); //画面クリア

		input.input_info(); //入力情報

		MapDraw* _map = new MapDraw;
		Cursor* cursor = new Cursor;
		GameTitle* title = new GameTitle;
		GameHelp* help = new GameHelp;
		MapUI* UI = new MapUI;

		switch (SceneTransition::game_scene) {
		case TUTORIAL:

			if (!enemies[0]->isAlive && !enemies[1]->isAlive && !enemies[2]->isAlive) {
				Enemy::act_order = Map::scene % 2 == 0 ? 0 : END;
			}
			_map->drawing_map(); //マップ描画

			input.map_scene_update(_map->map_20x20); //入力更新処理


			for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) _map->drawing_enemy_range(enemies[i]->x, enemies[i]->y);

			Princess.Update(); //姫の更新処理
			/* 各敵との重複判定 */
			Princess.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
			Princess.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			Princess.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
			Princess.Dead(_map->map_20x20); //姫の死亡処理
			Warrior1.Update(); //影武者1の更新処理
			/* 各敵との重複判定 */
			Warrior1.duplicate_decision(Princess.x, Princess.y, _princess);
			Warrior1.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			Warrior1.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
			Warrior1.Dead(_map->map_20x20); //影武者1の死亡処理
			Warrior2.Update(); //影武者2の更新処理
			/* 各敵との重複判定 */
			Warrior2.duplicate_decision(Princess.x, Princess.y, _princess);
			Warrior2.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
			Warrior2.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
			Warrior2.Dead(_map->map_20x20); //影武者2の死亡処理
			Warrior3.Update(); //影武者3の更新処理
			/* 各敵との重複判定 */
			Warrior3.duplicate_decision(Princess.x, Princess.y, _princess);
			Warrior3.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
			Warrior3.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			Warrior3.Dead(_map->map_20x20); //影武者3の死亡処理

			if (Enemy::act_order >= ARRAY_LENGTH(enemies)) Enemy::act_order = END;

			for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
				if (enemies[i]->isAlive) {
					enemies[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
					                                  Warrior2.isAlive, Warrior3.isAlive);
					enemies[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
					                                   Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
					enemies[i]->get_enemy_cost_0(enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
					                             enemies[2]->x, enemies[2]->y);
					enemies[i]->Update(_map->map_20x20); //敵兵1の更新処理
				}
				enemies[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i);
			}

			if (Map::scene % 2 != 0) {
				cursor->move_0(Princess.x, Princess.y, enemies[0]->x, enemies[0]->y,
				               enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y);
			}
			break;

		case STAGE1:

			_map->drawing_map(); //マップ描画

			input.map_scene_update(_map->map_20x20); //入力更新処理


			for (int i = 0; i < ARRAY_LENGTH(enemies2); ++i)
				_map->drawing_enemy_range(enemies2[i]->x, enemies2[i]->y);

			Princess.Update(); //姫の更新処理
			/* 各敵との重複判定 */
			Princess.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
			Princess.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
			Princess.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
			Princess.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
			Princess.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
			Princess.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
			Princess.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
			Princess.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
			Princess.Dead(_map->map_20x20); //姫の死亡処理
			Warrior1.Update(); //影武者1の更新処理
			/* 各敵との重複判定 */
			Warrior1.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
			Warrior1.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
			Warrior1.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
			Warrior1.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
			Warrior1.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
			Warrior1.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
			Warrior1.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
			Warrior1.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
			Warrior1.Dead(_map->map_20x20); //影武者1の死亡処理
			Warrior2.Update(); //影武者2の更新処理
			/* 各敵との重複判定 */
			Warrior2.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
			Warrior2.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
			Warrior2.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
			Warrior2.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
			Warrior2.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
			Warrior2.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
			Warrior2.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
			Warrior2.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
			Warrior2.Dead(_map->map_20x20); //影武者2の死亡処理
			Warrior3.Update(); //影武者3の更新処理
			/* 各敵との重複判定 */
			Warrior3.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
			Warrior3.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
			Warrior3.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
			Warrior3.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
			Warrior3.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
			Warrior3.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
			Warrior3.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
			Warrior3.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
			Warrior3.Dead(_map->map_20x20); //影武者3の死亡処理

			if (Enemy::act_order >= ARRAY_LENGTH(enemies2)) Enemy::act_order = END;

			for (int i = 0; i < ARRAY_LENGTH(enemies2); ++i) {
				if (enemies2[i]->isAlive) {
					enemies2[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
					                                   Warrior2.isAlive, Warrior3.isAlive);
					enemies2[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
					                                    Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
					enemies2[i]->get_enemy_cost_1(enemies2[0]->x, enemies2[0]->y, enemies2[1]->x, enemies2[1]->y,
					                              enemies2[2]->x, enemies2[2]->y, enemies2[3]->x, enemies2[3]->y,
					                              enemies2[4]->x, enemies2[4]->y, enemies2[5]->x, enemies2[5]->y,
					                              enemies2[6]->x, enemies2[6]->y, enemies2[7]->x, enemies2[7]->y);
					enemies2[i]->Update(_map->map_20x20); //敵兵1の更新処理
				}
				enemies2[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i);
			}

			if (Map::scene % 2 != 0) {
				cursor->move_1(Princess.x, Princess.y, enemies2[0]->x, enemies2[0]->y,
				               enemies2[1]->x, enemies2[1]->y, enemies2[2]->x, enemies2[2]->y,
				               enemies2[3]->x, enemies2[3]->y, enemies2[4]->x, enemies2[4]->y,
				               enemies2[5]->x, enemies2[5]->y, enemies2[6]->x, enemies2[6]->y,
				               enemies2[7]->x, enemies2[7]->y);
			}
			break;

		case STAGE2:
			_map->drawing_map(); //マップ描画

			input.map_scene_update(_map->map_20x20); //入力更新処理


			for (int i = 0; i < ARRAY_LENGTH(enemies3); ++i)
				_map->drawing_enemy_range(enemies3[i]->x, enemies3[i]->y);

			Princess.Update(); //姫の更新処理
			/* 各敵との重複判定 */
			Princess.duplicate_decision(enemies3[0]->x, enemies3[0]->y, _e_wolf1);
			Princess.duplicate_decision(enemies3[1]->x, enemies3[1]->y, _e_wolf2);
			Princess.duplicate_decision(enemies3[2]->x, enemies3[2]->y, _e_wolf3);
			Princess.duplicate_decision(enemies3[3]->x, enemies3[3]->y, _e_wolf4);
			Princess.duplicate_decision(enemies3[4]->x, enemies3[4]->y, _e_warrior1);
			Princess.duplicate_decision(enemies3[5]->x, enemies3[5]->y, _e_warrior2);
			Princess.duplicate_decision(enemies3[6]->x, enemies3[6]->y, _e_warrior3);
			Princess.duplicate_decision(enemies3[7]->x, enemies3[7]->y, _e_warrior4);
			Princess.duplicate_decision(enemies3[8]->x, enemies3[8]->y, _e_warrior5);
			Princess.duplicate_decision(enemies3[9]->x, enemies3[9]->y, _e_warrior6);
			Princess.duplicate_decision(enemies3[10]->x, enemies3[10]->y, _e_bandits1);
			Princess.Dead(_map->map_20x20); //姫の死亡処理
			Warrior1.Update(); //影武者1の更新処理
			/* 各敵との重複判定 */
			Warrior1.duplicate_decision(enemies3[0]->x, enemies3[0]->y, _e_wolf1);
			Warrior1.duplicate_decision(enemies3[1]->x, enemies3[1]->y, _e_wolf2);
			Warrior1.duplicate_decision(enemies3[2]->x, enemies3[2]->y, _e_wolf3);
			Warrior1.duplicate_decision(enemies3[3]->x, enemies3[3]->y, _e_wolf4);
			Warrior1.duplicate_decision(enemies3[4]->x, enemies3[4]->y, _e_warrior1);
			Warrior1.duplicate_decision(enemies3[5]->x, enemies3[5]->y, _e_warrior2);
			Warrior1.duplicate_decision(enemies3[6]->x, enemies3[6]->y, _e_warrior3);
			Warrior1.duplicate_decision(enemies3[7]->x, enemies3[7]->y, _e_warrior4);
			Warrior1.duplicate_decision(enemies3[8]->x, enemies3[8]->y, _e_warrior5);
			Warrior1.duplicate_decision(enemies3[9]->x, enemies3[9]->y, _e_warrior6);
			Warrior1.duplicate_decision(enemies3[10]->x, enemies3[10]->y, _e_bandits1);
			Warrior1.Dead(_map->map_20x20); //影武者1の死亡処理
			Warrior2.Update(); //影武者2の更新処理
			/* 各敵との重複判定 */
			Warrior2.duplicate_decision(enemies3[0]->x, enemies3[0]->y, _e_wolf1);
			Warrior2.duplicate_decision(enemies3[1]->x, enemies3[1]->y, _e_wolf2);
			Warrior2.duplicate_decision(enemies3[2]->x, enemies3[2]->y, _e_wolf3);
			Warrior2.duplicate_decision(enemies3[3]->x, enemies3[3]->y, _e_wolf4);
			Warrior2.duplicate_decision(enemies3[4]->x, enemies3[4]->y, _e_warrior1);
			Warrior2.duplicate_decision(enemies3[5]->x, enemies3[5]->y, _e_warrior2);
			Warrior2.duplicate_decision(enemies3[6]->x, enemies3[6]->y, _e_warrior3);
			Warrior2.duplicate_decision(enemies3[7]->x, enemies3[7]->y, _e_warrior4);
			Warrior2.duplicate_decision(enemies3[8]->x, enemies3[8]->y, _e_warrior5);
			Warrior2.duplicate_decision(enemies3[9]->x, enemies3[9]->y, _e_warrior6);
			Warrior2.duplicate_decision(enemies3[10]->x, enemies3[10]->y, _e_bandits1);
			Warrior2.Dead(_map->map_20x20); //影武者2の死亡処理
			Warrior3.Update(); //影武者3の更新処理
			/* 各敵との重複判定 */
			Warrior3.duplicate_decision(enemies3[0]->x, enemies3[0]->y, _e_wolf1);
			Warrior3.duplicate_decision(enemies3[1]->x, enemies3[1]->y, _e_wolf2);
			Warrior3.duplicate_decision(enemies3[2]->x, enemies3[2]->y, _e_wolf3);
			Warrior3.duplicate_decision(enemies3[3]->x, enemies3[3]->y, _e_wolf4);
			Warrior3.duplicate_decision(enemies3[4]->x, enemies3[4]->y, _e_warrior1);
			Warrior3.duplicate_decision(enemies3[5]->x, enemies3[5]->y, _e_warrior2);
			Warrior3.duplicate_decision(enemies3[6]->x, enemies3[6]->y, _e_warrior3);
			Warrior3.duplicate_decision(enemies3[7]->x, enemies3[7]->y, _e_warrior4);
			Warrior3.duplicate_decision(enemies3[8]->x, enemies3[8]->y, _e_warrior5);
			Warrior3.duplicate_decision(enemies3[9]->x, enemies3[9]->y, _e_warrior6);
			Warrior3.duplicate_decision(enemies3[10]->x, enemies3[10]->y, _e_bandits1);
			Warrior3.Dead(_map->map_20x20); //影武者3の死亡処理

			if (Enemy::act_order >= ARRAY_LENGTH(enemies3)) Enemy::act_order = END;

			for (int i = 0; i < ARRAY_LENGTH(enemies3); ++i) {
				if (enemies3[i]->isAlive) {
					enemies3[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
					                                   Warrior2.isAlive, Warrior3.isAlive);
					enemies3[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
					                                    Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
					enemies3[i]->get_enemy_cost_2(enemies3[0]->x, enemies3[0]->y, enemies3[1]->x, enemies3[1]->y,
					                              enemies3[2]->x, enemies3[2]->y, enemies3[3]->x, enemies3[3]->y,
					                              enemies3[4]->x, enemies3[4]->y, enemies3[5]->x, enemies3[5]->y,
					                              enemies3[6]->x, enemies3[6]->y, enemies3[7]->x, enemies3[7]->y,
					                              enemies3[8]->x, enemies3[8]->y, enemies3[9]->x, enemies3[9]->y,
					                              enemies3[10]->x, enemies3[10]->y);
					enemies3[i]->Update(_map->map_20x20); //敵兵1の更新処理
				}
				enemies3[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i);
			}

			if (Map::scene % 2 != 0) {
				cursor->move_2(Princess.x, Princess.y, enemies3[0]->x, enemies3[0]->y, enemies3[1]->x, enemies3[1]->y,
				               enemies3[2]->x, enemies3[2]->y, enemies3[3]->x, enemies3[3]->y,
				               enemies3[4]->x, enemies3[4]->y, enemies3[5]->x, enemies3[5]->y,
				               enemies3[6]->x, enemies3[6]->y, enemies3[7]->x, enemies3[7]->y,
				               enemies3[8]->x, enemies3[8]->y, enemies3[9]->x, enemies3[9]->y,
				               enemies3[10]->x, enemies3[10]->y);
			}
			break;

		case GAME_TITLE:
			input.game_title_update();
			title->update();
			break;

		case GAME_INFORMATION:
			input.game_help_update();
			input.start_game();
			help->draw();
			break;

		case GAME_RESULT:

			Princess.set_next_map_node(input.current_map_scene);
			Warrior1.set_next_map_node(input.current_map_scene);
			Warrior2.set_next_map_node(input.current_map_scene);
			Warrior3.set_next_map_node(input.current_map_scene);

			input.game_result_update();

			break;

		case GAME_HELP:
			input.game_help_update();
			input.return_game();
			help->draw();

			break;
		}

		SceneTransition* scene = new SceneTransition;
		if (Princess.moving_flag == -1) scene->transition_to_result(_map->map_20x20, Princess.x, Princess.y);
		delete scene;

		GameResult* result = new GameResult;
		result->rank_check(Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
		result->update();
		delete result;

		if (SceneTransition::game_scene <= STAGE2) {
			cursor->update();


			UI->yes_or_no(input.yes_or_no);
			UI->drawing_main_status(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                        Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
			UI->drawing_life_status(Princess.hp, Warrior1.hp, Warrior2.hp, Warrior3.hp,
			                        Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
			UI->update();
		}
		delete UI;
		delete title;
		delete help;
		delete cursor;
		delete _map;

		/*DrawFormatString(700, 0, GetColor(255, 0, 255),
		                 "Scene:%d", SceneTransition::game_scene, false);*/

		window_in_roop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}

	for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
		delete enemies[i];
	}
}
