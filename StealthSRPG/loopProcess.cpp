#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "mapDraw.h"
#include "mapUI.h"
#include "mapMist.h"
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
#include "music.h"
#include <cstdlib>

#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

using namespace std;

void loop_process() {

	Input input;

	const int player_graph = LoadGraph("Source/Charactor/Player/princess.png");
	Princess Princess(
		BLOCK_SIZE * 14, BLOCK_SIZE * 8, player_graph,
		BLOCK_SIZE, 4, 4, false, true, input);

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
			/* É`ÉÖÅ[ÉgÉäÉAÉã */
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 12, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 10, BLOCK_SIZE * 13, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 14, BLOCK_SIZE * 14, enemy_graph,
			                 BLOCK_SIZE, 4, 2, 25, false, true),
		};
	Enemy* enemies2[] = {
			/* ÉXÉeÅ[ÉW1 */
			new EnemyWolf_1(BLOCK_SIZE * 11, BLOCK_SIZE * 8, enemy_graph,
			                BLOCK_SIZE, 1, 4, 40, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 18, BLOCK_SIZE * 6, enemy_graph,
			                BLOCK_SIZE, 1, 4, 40, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 9, BLOCK_SIZE * 1, enemy_graph,
			                BLOCK_SIZE, 1, 0, 40, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 9, BLOCK_SIZE * 3, enemy_graph,
			                BLOCK_SIZE, 1, 0, 40, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 3, BLOCK_SIZE * 9, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 5, BLOCK_SIZE * 13, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 18, BLOCK_SIZE * 12, enemy_graph,
			                 BLOCK_SIZE, 4, 2, 25, false, true),
			new EnemyBandits(BLOCK_SIZE * 18, BLOCK_SIZE * 15, enemy_graph,
			                 BLOCK_SIZE, 4, 2, 25, false, true),
		};

	Enemy* enemies3[] = {
			new EnemyWolf_1(BLOCK_SIZE * 3, BLOCK_SIZE * 11, enemy_graph,
			                BLOCK_SIZE, 1, 4, 40, false, true),
			new EnemyWolf_1(BLOCK_SIZE * 13, BLOCK_SIZE * 8, enemy_graph,
			                BLOCK_SIZE, 1, 4, 40, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 3, BLOCK_SIZE * 3, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 2, BLOCK_SIZE * 4, enemy_graph,
			                   BLOCK_SIZE, 2, 3, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 12, BLOCK_SIZE * 5, enemy_graph,
			                   BLOCK_SIZE, 2, 0, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 8, BLOCK_SIZE * 11, enemy_graph,
			                   BLOCK_SIZE, 2, 0, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 10, BLOCK_SIZE * 11, enemy_graph,
			                   BLOCK_SIZE, 2, 0, 30, false, true),
			new EnemyWarrior_1(BLOCK_SIZE * 6, BLOCK_SIZE * 5, enemy_graph,
			                   BLOCK_SIZE, 2, 0, 30, false, true),
			new EnemyBandits(BLOCK_SIZE * 10, BLOCK_SIZE * 14, enemy_graph,
			                 BLOCK_SIZE, 4, 0, 25, false, true),
			new EnemyBandits(BLOCK_SIZE * 8, BLOCK_SIZE * 16, enemy_graph,
			                 BLOCK_SIZE, 4, 0, 25, false, true),
			new EnemyBandits(BLOCK_SIZE * 9, BLOCK_SIZE * 18, enemy_graph,
			                 BLOCK_SIZE, 4, 0, 25, false, true),
		};

	const int mist = LoadGraph("Source/Map/mist.png");

	BGM bgm = {
			LoadSoundMem("Source/Music/attack.mp3"),
			LoadSoundMem("Source/Music/cursor.mp3"),
			LoadSoundMem("Source/Music/day.mp3"),
			LoadSoundMem("Source/Music/gameover.mp3"),
			LoadSoundMem("Source/Music/menu.mp3"),
			LoadSoundMem("Source/Music/move.mp3"),
			LoadSoundMem("Source/Music/night.mp3"),
			LoadSoundMem("Source/Music/pickup.mp3"),
			LoadSoundMem("Source/Music/push.mp3"),
			LoadSoundMem("Source/Music/slash.mp3")
		};

	change_sound_volume();
	get_sound_start(bgm.menu);

	GameTitle title;
	GameHelp help;
	GameResult result;
	MapUI UI;

	// ÉQÅ[ÉÄÉãÅ[Év
	while (true) {
		ClearDrawScreen(); //âÊñ ÉNÉäÉA

		input.input_info(); //ì¸óÕèÓïÒ
		MapDraw* _map = new MapDraw;

		Cursor* cursor = new Cursor;
		switch (SceneTransition::game_scene) {
		case TUTORIAL:

			if (!enemies[0]->isAlive && !enemies[1]->isAlive && !enemies[2]->isAlive) {
				Enemy::act_order = Map::scene % 2 == 0 ? 0 : END;
			}

			_map->drawing_map(); //É}ÉbÉvï`âÊ
			ChangeVolumeSoundMem(200, bgm.day);
			ChangeVolumeSoundMem(130, bgm.night);
			_map->booting_timer(bgm.day, bgm.night);

			Princess.Update(bgm.pickup); //ïPÇÃçXêVèàóù
			Princess.Dead(_map->map_20x20); //ïPÇÃéÄñSèàóù
			Warrior1.Update(bgm.pickup); //âeïêé“1ÇÃçXêVèàóù
			Warrior1.Dead(_map->map_20x20); //âeïêé“1ÇÃéÄñSèàóù
			Warrior2.Update(bgm.pickup); //âeïêé“2ÇÃçXêVèàóù
			Warrior2.Dead(_map->map_20x20); //âeïêé“2ÇÃéÄñSèàóù
			Warrior3.Update(bgm.pickup); //âeïêé“3ÇÃçXêVèàóù
			Warrior3.Dead(_map->map_20x20); //âeïêé“3ÇÃéÄñSèàóù

			result.rank_check(Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);


			if (Map::scene % 2 == 0) {
				input.map_scene_update(bgm.cursor, bgm.push); //ì¸óÕçXêVèàóù

				/* è’ìÀîªíË */
				if (Map::range_flag == 1) {
					input.map_collision_decision(_map->map_20x20);
					input.enemy_collision_decision0(enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
					                                enemies[2]->x, enemies[2]->y);
					/*input.player_collision_decision(Princess.x, Princess.y, Warrior1.x, Warrior1.y, Warrior2.x,
					                                Warrior2.y, Warrior3.x, Warrior3.y);*/
				}
				else input.collision_update();
				/* äeñ°ï˚Ç∆ÇÃèdï°îªíË */
				Princess.duplicate_decision(enemies[0]->x, enemies[0]->y, _e_warrior1);
				Princess.duplicate_decision(enemies[1]->x, enemies[1]->y, _e_warrior2);
				Princess.duplicate_decision(enemies[2]->x, enemies[2]->y, _e_bandits1);
				Warrior1.duplicate_decision(enemies[0]->x, enemies[0]->y, _e_warrior1);
				Warrior1.duplicate_decision(enemies[1]->x, enemies[1]->y, _e_warrior2);
				Warrior1.duplicate_decision(enemies[2]->x, enemies[2]->y, _e_bandits1);
				Warrior2.duplicate_decision(enemies[0]->x, enemies[0]->y, _e_warrior1);
				Warrior2.duplicate_decision(enemies[1]->x, enemies[1]->y, _e_warrior2);
				Warrior2.duplicate_decision(enemies[2]->x, enemies[2]->y, _e_bandits1);
				Warrior3.duplicate_decision(enemies[0]->x, enemies[0]->y, _e_warrior1);
				Warrior3.duplicate_decision(enemies[1]->x, enemies[1]->y, _e_warrior2);
				Warrior3.duplicate_decision(enemies[2]->x, enemies[2]->y, _e_bandits1);
				Princess.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Princess.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Princess.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior1.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior1.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Warrior1.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior2.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior2.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior2.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior3.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior3.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior3.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			}

			if (Enemy::act_order >= ARRAY_LENGTH(enemies)) Enemy::act_order = END;


			for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
				if (!enemies[i]->isAlive) continue;
				_map->drawing_enemy_range(enemies[i]->x, enemies[i]->y);
				enemies[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
				                                  Warrior2.isAlive, Warrior3.isAlive);
				enemies[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
				                                   Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
				enemies[i]->get_enemy_cost_0(enemies[0]->x, enemies[0]->y, enemies[1]->x, enemies[1]->y,
				                             enemies[2]->x, enemies[2]->y);

				enemies[i]->Update(_map->map_20x20); //ìGï∫1ÇÃçXêVèàóù
				enemies[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i, bgm.slash, bgm.attack);
			}

			if (Map::scene % 2 != 0) {
				cursor->move_0(Princess.x, Princess.y, enemies[0]->x, enemies[0]->y,
				               enemies[1]->x, enemies[1]->y, enemies[2]->x, enemies[2]->y);
			}

			break;

		case STAGE1:

			_map->drawing_map(); //É}ÉbÉvï`âÊ
			StopMusicMem(bgm.gameover);
			ChangeVolumeSoundMem(200, bgm.day);
			ChangeVolumeSoundMem(130, bgm.night);
			_map->booting_timer(bgm.day, bgm.night);

			Princess.Update(bgm.pickup); //ïPÇÃçXêVèàóù
			Princess.Dead(_map->map_20x20); //ïPÇÃéÄñSèàóù
			Warrior1.Update(bgm.pickup); //âeïêé“1ÇÃçXêVèàóù
			Warrior1.Dead(_map->map_20x20); //âeïêé“1ÇÃéÄñSèàóù
			Warrior2.Update(bgm.pickup); //âeïêé“2ÇÃçXêVèàóù
			Warrior2.Dead(_map->map_20x20); //âeïêé“2ÇÃéÄñSèàóù
			Warrior3.Update(bgm.pickup); //âeïêé“3ÇÃçXêVèàóù
			Warrior3.Dead(_map->map_20x20); //âeïêé“3ÇÃéÄñSèàóù

			result.rank_check(Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);

			if (Map::scene % 2 == 0) {
				input.map_scene_update(bgm.cursor, bgm.push); //ì¸óÕçXêVèàóù

				/* è’ìÀîªíË */
				if (Map::range_flag == 1) {
					input.map_collision_decision(_map->map_20x20);
					input.enemy_collision_decision1(enemies2[0]->x, enemies2[0]->y, enemies2[1]->x, enemies2[1]->y,
					                                enemies2[2]->x, enemies2[2]->y, enemies2[3]->x, enemies2[3]->y,
					                                enemies2[4]->x, enemies2[4]->y, enemies2[5]->x, enemies2[5]->y,
					                                enemies2[6]->x, enemies2[6]->y, enemies2[7]->x, enemies2[7]->y);
					/*input.player_collision_decision(Princess.x, Princess.y, Warrior1.x, Warrior1.y, Warrior2.x,
					                                Warrior2.y, Warrior3.x, Warrior3.y);*/
				}
				else input.collision_update();
				/* äeñ°ï˚Ç∆ÇÃèdï°îªíË */
				Princess.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
				Princess.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
				Princess.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
				Princess.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
				Princess.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
				Princess.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
				Princess.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
				Princess.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
				Warrior1.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
				Warrior1.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
				Warrior1.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
				Warrior1.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
				Warrior1.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
				Warrior1.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
				Warrior1.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
				Warrior1.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
				Warrior2.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
				Warrior2.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
				Warrior2.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
				Warrior2.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
				Warrior2.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
				Warrior2.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
				Warrior2.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
				Warrior2.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
				Warrior3.duplicate_decision(enemies2[0]->x, enemies2[0]->y, _e_wolf1);
				Warrior3.duplicate_decision(enemies2[1]->x, enemies2[1]->y, _e_wolf2);
				Warrior3.duplicate_decision(enemies2[2]->x, enemies2[2]->y, _e_wolf3);
				Warrior3.duplicate_decision(enemies2[3]->x, enemies2[3]->y, _e_wolf4);
				Warrior3.duplicate_decision(enemies2[4]->x, enemies2[4]->y, _e_warrior1);
				Warrior3.duplicate_decision(enemies2[5]->x, enemies2[5]->y, _e_warrior2);
				Warrior3.duplicate_decision(enemies2[6]->x, enemies2[6]->y, _e_bandits1);
				Warrior3.duplicate_decision(enemies2[7]->x, enemies2[7]->y, _e_bandits2);
				Princess.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Princess.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Princess.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior1.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior1.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Warrior1.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior2.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior2.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior2.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior3.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior3.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior3.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			}

			if (Enemy::act_order >= ARRAY_LENGTH(enemies2)) Enemy::act_order = END;

			for (int i = 0; i < ARRAY_LENGTH(enemies2); ++i) {
				if (enemies2[i]->isAlive) {
					_map->drawing_enemy_range(enemies2[i]->x, enemies2[i]->y);
					enemies2[i]->get_survival_activity(Princess.isAlive, Warrior1.isAlive,
					                                   Warrior2.isAlive, Warrior3.isAlive);
					enemies2[i]->get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
					                                    Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
					enemies2[i]->get_enemy_cost_1(enemies2[0]->x, enemies2[0]->y, enemies2[1]->x, enemies2[1]->y,
					                              enemies2[2]->x, enemies2[2]->y, enemies2[3]->x, enemies2[3]->y,
					                              enemies2[4]->x, enemies2[4]->y, enemies2[5]->x, enemies2[5]->y,
					                              enemies2[6]->x, enemies2[6]->y, enemies2[7]->x, enemies2[7]->y);
					enemies2[i]->Update(_map->map_20x20); //ìGï∫1ÇÃçXêVèàóù
					enemies2[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i, bgm.slash,
					                    bgm.attack);
				}
				else enemies2[i]->forward_act_order(i);
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
			_map->drawing_map(); //É}ÉbÉvï`âÊ
			StopMusicMem(bgm.gameover);
			ChangeVolumeSoundMem(200, bgm.day);
			ChangeVolumeSoundMem(130, bgm.night);
			_map->booting_timer(bgm.day, bgm.night);

			Princess.Update(bgm.pickup); //ïPÇÃçXêVèàóù
			Princess.Dead(_map->map_20x20); //ïPÇÃéÄñSèàóù
			Warrior1.Update(bgm.pickup); //âeïêé“1ÇÃçXêVèàóù
			Warrior1.Dead(_map->map_20x20); //âeïêé“1ÇÃéÄñSèàóù
			Warrior2.Update(bgm.pickup); //âeïêé“2ÇÃçXêVèàóù
			Warrior2.Dead(_map->map_20x20); //âeïêé“2ÇÃéÄñSèàóù
			Warrior3.Update(bgm.pickup); //âeïêé“3ÇÃçXêVèàóù
			Warrior3.Dead(_map->map_20x20); //âeïêé“3ÇÃéÄñSèàóù

			result.rank_check(Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);

			if (Map::scene % 2 == 0) {
				input.map_scene_update(bgm.cursor, bgm.push); //ì¸óÕçXêVèàóù

				/* è’ìÀîªíË */
				if (Map::range_flag == 1) {
					input.map_collision_decision(_map->map_20x20);
					input.enemy_collision_decision2(enemies3[0]->x, enemies3[0]->y, enemies3[1]->x, enemies3[1]->y,
					                                enemies3[2]->x, enemies3[2]->y, enemies3[3]->x, enemies3[3]->y,
					                                enemies3[4]->x, enemies3[4]->y, enemies3[5]->x, enemies3[5]->y,
					                                enemies3[6]->x, enemies3[6]->y, enemies3[7]->x, enemies3[7]->y,
					                                enemies3[8]->x, enemies3[8]->y, enemies3[9]->x, enemies3[9]->y,
					                                enemies3[10]->x, enemies3[10]->y);
					/*input.player_collision_decision(Princess.x, Princess.y, Warrior1.x, Warrior1.y, Warrior2.x,
					                                Warrior2.y, Warrior3.x, Warrior3.y);*/
				}
				else input.collision_update();
				/* äeñ°ï˚Ç∆ÇÃèdï°îªíË */
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
				Princess.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Princess.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Princess.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior1.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior1.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
				Warrior1.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior2.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior2.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior2.duplicate_decision(Warrior3.x, Warrior3.y, _s_warrior3);
				Warrior3.duplicate_decision(Princess.x, Princess.y, _princess);
				Warrior3.duplicate_decision(Warrior1.x, Warrior1.y, _s_warrior1);
				Warrior3.duplicate_decision(Warrior2.x, Warrior2.y, _s_warrior2);
			}

			if (Enemy::act_order >= ARRAY_LENGTH(enemies3)) Enemy::act_order = END;

			for (int i = 0; i < ARRAY_LENGTH(enemies3); ++i) {
				if (enemies3[i]->isAlive) {
					_map->drawing_enemy_range(enemies3[i]->x, enemies3[i]->y);
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
					enemies3[i]->Update(_map->map_20x20); //ìGï∫1ÇÃçXêVèàóù
					enemies3[i]->Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp, i, bgm.slash,
					                    bgm.attack);
				}
				else enemies3[i]->forward_act_order(i);
			}


			if (Map::random_mist == 0) {
				draw_mist(mist, 10, 7);
				draw_mist(mist, 12, 8);
				draw_mist(mist, 9, 9);
				draw_mist(mist, 16, 15);
				draw_mist(mist, 14, 17);
				draw_mist(mist, 18, 17);
				draw_mist(mist, 12, 20);
				draw_mist(mist, 15, 19);
				draw_mist(mist, 17, 20);
				draw_mist(mist, 20, 8);
				draw_mist(mist, 21, 10);
				draw_mist(mist, 23, 11);
			}
			else if (Map::random_mist == 1) {
				draw_mist(mist, 10, 7);
				draw_mist(mist, 12, 8);
				draw_mist(mist, 9, 9);
			}
			else if (Map::random_mist == 2) {
				draw_mist(mist, 16, 15);
				draw_mist(mist, 14, 17);
				draw_mist(mist, 18, 17);
				draw_mist(mist, 12, 20);
				draw_mist(mist, 15, 19);
				draw_mist(mist, 17, 20);
			}
			else if (Map::random_mist == 3) {
				draw_mist(mist, 20, 8);
				draw_mist(mist, 21, 10);
				draw_mist(mist, 23, 11);
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
			StopMusicMem(bgm.gameover);
			ChangeVolumeSoundMem(130, bgm.push);
			input.game_title_update(bgm.push);
			title.update();
			Input::current_map_scene = 0;
			Princess.reset();
			Warrior1.reset();
			Warrior2.reset();
			Warrior3.reset();

			break;

		case GAME_INFORMATION:
			ChangeVolumeSoundMem(130, bgm.push);
			input.game_help_update(bgm.push);
			input.start_game(bgm.menu, bgm.day, bgm.push);
			help.draw();
			break;

		case GAME_RESULT:
			StopSoundMem(bgm.day);
			StopSoundMem(bgm.night);
			if (result.rank != 0) {
				ChangeVolumeSoundMem(200, bgm.menu);
				get_sound_music(bgm.menu);
			}
			else {
				ChangeVolumeSoundMem(150, bgm.gameover);
				get_sound_music(bgm.gameover);
			}

			Map::turn_count = 0;
			Map::scene = NOON_PLAY;
			MapUI::UI_flag = true;

			Princess.set_next_map_node(Input::current_map_scene);
			Warrior1.set_next_map_node(Input::current_map_scene);
			Warrior2.set_next_map_node(Input::current_map_scene);
			Warrior3.set_next_map_node(Input::current_map_scene);

			ChangeVolumeSoundMem(130, bgm.push);
			input.game_result_update(result.rank, bgm.push, bgm.gameover, bgm.menu);

			for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
				enemies[i]->reset();
			}

			result.update();

			break;

		case GAME_HELP:
			ChangeVolumeSoundMem(130, bgm.push);
			input.game_help_update(bgm.push);
			input.return_game(bgm.push);
			help.draw();

			break;
		}

		if (SceneTransition::game_scene <= STAGE2) {

			cursor->update();


			UI.drawing_main_status(Princess.moving_flag, Warrior1.moving_flag, Warrior2.moving_flag,
			                       Warrior3.moving_flag);
			UI.drawing_life_status(Princess.hp, Warrior1.hp, Warrior2.hp, Warrior3.hp,
			                       Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
			UI.update();
			if (Input::confirmation_flag) UI.yes_or_no(input.yes_or_no);


		}

		help.map_scene_draw();

		delete cursor;

		SceneTransition* scene = new SceneTransition;
		if (!Princess.moving_flag) scene->transition_to_result(_map->map_20x20, Princess.x, Princess.y);
		delete scene;
		delete _map;

		/*DrawFormatString(400, 0, GetColor(255, 255, 255),
		                 "cur_map%d", Input::current_map_scene, false);
		DrawFormatString(400, 15, GetColor(255, 255, 255),
		                 "count%d, UI%d, act%d", Map::turn_count, MapUI::UI_flag, Enemy::act_order, false);
		DrawFormatString(400, 30, GetColor(255, 255, 255),
		                 "rank%d, mist%d", result.rank, Map::random_mist, false);
		DrawFormatString(400, 45, GetColor(255, 255, 255),
		                 "x:%d, y:%d", Map::current_x / BLOCK_SIZE, Map::current_y / BLOCK_SIZE, false);*/

		window_in_roop(); //ÉãÅ[Évì‡ÉEÉBÉìÉhÉEê›íË
		if (ProcessMessage() == -1) break; //WindowsÉVÉXÉeÉÄÇ©ÇÁÇ≠ÇÈèÓïÒÇèàóù
	}

	for (int i = 0; i < ARRAY_LENGTH(enemies); ++i) {
		delete enemies[i];
	}
	for (int i = 0; i < ARRAY_LENGTH(enemies2); ++i) {
		delete enemies2[i];
	}
	for (int i = 0; i < ARRAY_LENGTH(enemies3); ++i) {
		delete enemies3[i];
	}
}
