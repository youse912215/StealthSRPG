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
		block_size, 50, 4, false, true, input);

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

	EnemyWarrior_1 E_Warrior1(block_size * 6, block_size * 7,
	                          LoadGraph("Source/Charactor/enemy_1.png"),
	                          block_size, 50, 3, true);

	EnemyBandits Bandits(block_size * 8, block_size * 9,
	                     LoadGraph("Source/Charactor/enemy_2.png"),
	                     block_size, 75, 2, true);

	// �Q�[�����[�v
	while (true) {
		ClearDrawScreen(); //��ʃN���A

		//if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //�I������

		MapDraw* _map = new MapDraw;
		_map->drawing_map(E_Warrior1.x, E_Warrior1.y, Bandits.x, Bandits.y);
		_map->drawing_format();

		input.input_info();
		input.update(_map->map_20x20, E_Warrior1.x, E_Warrior1.y, Bandits.x, Bandits.y);

		Princess.Update(Warrior1.x, Warrior1.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //�P�̏���
		Warrior1.Update(Princess.x, Princess.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //�e����1�̏���
		Warrior2.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //�e����2�̏���
		Warrior3.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior2.x, Warrior2.y, E_Warrior1.x, E_Warrior1.y,
		                Bandits.x, Bandits.y); //�e����3�̏���
		E_Warrior1.Update();

		E_Warrior1.Update(); //�G��1�̏���
		Bandits.Update(); //�R���̏���

		Cursor* cursor = new Cursor;
		cursor->update();

		if (_map->map_20x20[(Princess.y / block_size)][(Princess.x / block_size)] == GOAL
			&& Princess.moving_flag == -1)
			break;

		DrawFormatString(0, 30, GetColor(0, 0, 0), "����C�i%d, %d�j",
		                 Cursor::current_x / block_size, Cursor::current_y / block_size, false);
		DrawFormatString(150, 30, GetColor(0, 0, 0), "����Q�i%d, %d�j",
		                 cursor->qx / block_size, cursor->qy / block_size, false);
		DrawFormatString(350, 30, GetColor(0, 0, 0), "�͈͒��S���W�i%d, %d�j",
		                 Cursor::range_x / block_size, Cursor::range_y / block_size, false);
		DrawFormatString(550, 30, GetColor(255, 0, 0), "�͈̓t���O:%d",
		                 Cursor::range_flag, false);
		DrawFormatString(600, 45, GetColor(255, 0, 0), "CoF:L%d,R%d,U%d,D%d",
		                 input.collision_flag[LEFT], input.collision_flag[RIGHT],
		                 input.collision_flag[UP], input.collision_flag[DOWN], false);

		DrawFormatString(WIN_WIDTH - block_size * 3, 0, GetColor(0, 0, 0),
		                 "�ړ��}�X x:%d", abs(Cursor::range_x - Cursor::current_x) / block_size, false);
		DrawFormatString(WIN_WIDTH - block_size * 3, 15, GetColor(0, 0, 0),
		                 "�ړ��}�X y:%d", abs(Cursor::range_y - Cursor::current_y) / block_size, false);
		DrawFormatString(WIN_WIDTH - block_size * 3, 30, GetColor(0, 0, 0),
		                 "�ړ��͈�:%d", Cursor::moving_range, false);

		delete _map;
		delete cursor;

		window_in_roop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}