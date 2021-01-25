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
#include "enemyWarrior_1.h"
#include "enemyWarrior_2.h"
#include "enemyBandits.h"
#include <cstdlib>

using namespace std;

void loop_process() {

	Input input;

	Princess Princess(
		block_size * 8, block_size * 13,
		LoadGraph("Source/Charactor/Player/princess.png"),
		block_size, 3, 4, false, true, input);

	ShadowWarrior_1 Warrior1(
		block_size * 8, block_size * 14,
		LoadGraph("Source/Charactor/Player/princess.png"),
		block_size, 3, 3, false, true, input);

	ShadowWarrior_2 Warrior2(
		block_size * 9, block_size * 13,
		LoadGraph("Source/Charactor/Player/princess.png"),
		block_size, 3, 3, false, true, input);

	ShadowWarrior_3 Warrior3(
		block_size * 7, block_size * 13,
		LoadGraph("Source/Charactor/Player/princess.png"),
		block_size, 3, 3, false, true, input);

	EnemyWarrior_1 E_Warrior1(block_size * 5, block_size * 8,
	                          LoadGraph("Source/Charactor/Enemy/enemies.png"),
	                          block_size, 1, 3, 50, false, true);

	EnemyWarrior_2 E_Warrior2(block_size * 7, block_size * 6,
	                          LoadGraph("Source/Charactor/Enemy/enemies.png"),
	                          block_size, 1, 3, 80, false, true);

	EnemyBandits Bandits(block_size * 14, block_size * 14,
	                     LoadGraph("Source/Charactor/Enemy/enemies.png"),
	                     block_size, 2, 2, 150, false, true);

	// �Q�[�����[�v
	while (true) {
		ClearDrawScreen(); //��ʃN���A

		//if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //�I������

		MapDraw* _map = new MapDraw;
		_map->drawing_map(E_Warrior1.x, E_Warrior1.y, Bandits.x, Bandits.y); //�}�b�v�`��
		_map->drawing_format(); //�t�H�[�}�b�g

		input.input_info(); //���͏��
		input.update(_map->map_20x20, E_Warrior1.x, E_Warrior1.y,
		             Bandits.x, Bandits.y); //���͍X�V����

		Princess.Update(Warrior1.x, Warrior1.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                E_Warrior2.x, E_Warrior2.y, Bandits.x, Bandits.y); //�P�̍X�V����
		Princess.Dead(_map->map_20x20); //�P�̎��S����
		Warrior1.Update(Princess.x, Princess.y, Warrior2.x, Warrior2.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                E_Warrior2.x, E_Warrior2.y, Bandits.x, Bandits.y); //�e����1�̍X�V����
		Warrior1.Dead(_map->map_20x20); //�P�̎��S����
		Warrior2.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior3.x, Warrior3.y, E_Warrior1.x, E_Warrior1.y,
		                E_Warrior2.x, E_Warrior2.y, Bandits.x, Bandits.y); //�e����2�̍X�V����
		Warrior2.Dead(_map->map_20x20); //�P�̎��S����
		Warrior3.Update(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
		                Warrior2.x, Warrior2.y, E_Warrior1.x, E_Warrior1.y,
		                E_Warrior2.x, E_Warrior2.y, Bandits.x, Bandits.y); //�e����3�̍X�V����
		Warrior3.Dead(_map->map_20x20); //�P�̎��S����

		if (E_Warrior1.isAlive) {
			E_Warrior1.get_survival_activity(Princess.isAlive, Warrior1.isAlive,
			                                 Warrior2.isAlive, Warrior3.isAlive);
			E_Warrior1.get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                                  Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
			E_Warrior1.get_enemy_cost(E_Warrior2.x, E_Warrior2.y, Bandits.x, Bandits.y);
			E_Warrior1.Update(_map->map_20x20); //�G��1�̍X�V����	
			E_Warrior1.Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp);
		}

		if (E_Warrior2.isAlive) {
			E_Warrior2.get_survival_activity(Princess.isAlive, Warrior1.isAlive,
			                                 Warrior2.isAlive, Warrior3.isAlive);
			E_Warrior2.get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                                  Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
			E_Warrior2.get_enemy_cost(E_Warrior1.x, E_Warrior1.y, Bandits.x, Bandits.y);
			E_Warrior2.Update(_map->map_20x20); //�G��1�̍X�V����
			E_Warrior2.Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp);
		}

		if (Bandits.isAlive) {
			Bandits.get_survival_activity(Princess.isAlive, Warrior1.isAlive,
			                              Warrior2.isAlive, Warrior3.isAlive);
			Bandits.get_two_point_distance(Princess.x, Princess.y, Warrior1.x, Warrior1.y,
			                               Warrior2.x, Warrior2.y, Warrior3.x, Warrior3.y);
			Bandits.get_enemy_cost(E_Warrior1.x, E_Warrior1.y, E_Warrior2.x, E_Warrior2.y);
			Bandits.Update(_map->map_20x20); //�R���̍X�V����
			Bandits.Attack(&Princess.hp, &Warrior1.hp, &Warrior2.hp, &Warrior3.hp);
		}

		Cursor* cursor = new Cursor;
		cursor->update();

		if (_map->map_20x20[(Princess.y / block_size)][(Princess.x / block_size)] == GOAL
			&& Princess.moving_flag == -1)
			break;

		DrawFormatString(0, 15, GetColor(255, 255, 255), " Z:�v���C���[�I��", false);
		DrawFormatString(0, 30, GetColor(255, 255, 255), " SPACE:���t�F�C�X��", false);
		DrawFormatString(0, 45, GetColor(255, 255, 255), " ARROW:1�}�X�ړ�", false);
		/*DrawFormatString(0, 60, GetColor(255, 255, 255), "Hp:%d, %d, %d, %d",
		                 Princess.hp, Warrior1.hp, Warrior2.hp, Warrior3.hp, false);
		DrawFormatString(300, 15, GetColor(0, 200, 0), "%d", Princess.latency, false);*/


		/*DrawFormatString(0, 30, GetColor(0, 0, 0), "����C�i%d, %d�j",
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
		                 "�ړ��͈�:%d", Cursor::moving_range, false);*/

		MapUI* UI = new MapUI;
		UI->yes_or_no(input.yes_or_no);
		UI->drawing_life_status(Princess.hp, Warrior1.hp, Warrior2.hp, Warrior3.hp,
		                        Princess.isAlive, Warrior1.isAlive, Warrior2.isAlive, Warrior3.isAlive);
		UI->update();
		delete UI;

		delete _map;
		delete cursor;

		window_in_roop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
