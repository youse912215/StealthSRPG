#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "Princess.h"
#include "mapDraw.h"
#include "cursor.h"
#include "shadowWarrior_1.h"
#include "shadowWarrior_2.h"
#include "shadowWarrior_3.h"
#include "enemyWarrior_1.h"
#include "enemyBandits.h"
#include <cstdlib>

using namespace std;

void loop_process() {

	Input input;

	Princess Princess(
		block_size * 9, block_size * 11,
		LoadGraph("Source/Charactor/princess.png"),
		block_size, 75, 4, false, true, input);

	ShadowWarrior_1 Warrior1(
		block_size * 7, block_size * 14,
		LoadGraph("Source/Charactor/shadow_warrior.png"),
		block_size, 100, 3, false, true, input);

	ShadowWarrior_2 Warrior2(
		block_size * 8, block_size * 13,
		LoadGraph("Source/Charactor/shadow_warrior.png"),
		block_size, 100, 3, false, true, input);

	ShadowWarrior_3 Warrior3(
		block_size * 6, block_size * 12,
		LoadGraph("Source/Charactor/shadow_warrior.png"),
		block_size, 100, 3, false, true, input);

	EnemyWarrior_1 E_Warrior1(block_size * 14, block_size * 14,
	                          LoadGraph("Source/Charactor/enemy_1.png"),
	                          block_size, 50, 3, false, true);

	EnemyBandits Bandits(block_size * 6, block_size * 7,
	                     LoadGraph("Source/Charactor/enemy_2.png"),
	                     block_size, 80, 2, false, true);

	// ゲームループ
	while (true) {
		ClearDrawScreen(); //画面クリア

		//if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //終了処理

		MapDraw* _map = new MapDraw;
		_map->drawing_map(E_Warrior1.x, E_Warrior1.y, Bandits.x, Bandits.y); //マップ描画
		_map->drawing_format(); //フォーマット

		input.input_info(); //入力情報
		input.update(_map->map_20x20, E_Warrior1.x, E_Warrior1.y,
		             Bandits.x, Bandits.y); //入力更新処理

		Princess.Update(Warrior1.x, Warrior1.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //姫の更新処理
		Princess.Dead(_map->map_20x20); //姫の死亡処理
		Warrior1.Update(Princess.x, Princess.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //影武者1の更新処理
		Warrior1.Dead(_map->map_20x20); //姫の死亡処理
		Warrior2.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //影武者2の更新処理
		Warrior2.Dead(_map->map_20x20); //姫の死亡処理
		Warrior3.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior2.x, Warrior2.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //影武者3の更新処理
		Warrior3.Dead(_map->map_20x20); //姫の死亡処理


		E_Warrior1.Update(_map->map_20x20); //敵兵1の更新処理
		E_Warrior1.get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                                  Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
		E_Warrior1.Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp);

		Bandits.Update(_map->map_20x20); //山賊の更新処理
		Bandits.get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                               Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
		Bandits.Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp);

		Cursor* cursor = new Cursor;
		cursor->update();

		if (_map->map_20x20[(Princess.y / block_size)][(Princess.x / block_size)] == GOAL
			&& Princess.moving_flag == -1)
			break;

		DrawFormatString(0, 30, GetColor(0, 0, 0), "現在C（%d, %d）",
		                 Cursor::current_x / block_size, Cursor::current_y / block_size, false);
		DrawFormatString(150, 30, GetColor(0, 0, 0), "現在Q（%d, %d）",
		                 cursor->qx / block_size, cursor->qy / block_size, false);
		DrawFormatString(350, 30, GetColor(0, 0, 0), "範囲中心座標（%d, %d）",
		                 Cursor::range_x / block_size, Cursor::range_y / block_size, false);
		DrawFormatString(550, 30, GetColor(255, 0, 0), "範囲フラグ:%d",
		                 Cursor::range_flag, false);
		DrawFormatString(600, 45, GetColor(255, 0, 0), "CoF:L%d,R%d,U%d,D%d",
		                 input.collision_flag[LEFT], input.collision_flag[RIGHT],
		                 input.collision_flag[UP], input.collision_flag[DOWN], false);

		DrawFormatString(WIN_WIDTH - block_size * 3, 0, GetColor(0, 0, 0),
		                 "移動マス x:%d", abs(Cursor::range_x - Cursor::current_x) / block_size, false);
		DrawFormatString(WIN_WIDTH - block_size * 3, 15, GetColor(0, 0, 0),
		                 "移動マス y:%d", abs(Cursor::range_y - Cursor::current_y) / block_size, false);
		DrawFormatString(WIN_WIDTH - block_size * 3, 30, GetColor(0, 0, 0),
		                 "移動範囲:%d", Cursor::moving_range, false);

		delete _map;
		delete cursor;

		window_in_roop(); //ループ内ウィンドウ設定
		if (ProcessMessage() == -1) break; //Windowsシステムからくる情報を処理
	}
}
