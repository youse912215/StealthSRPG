#pragma once


typedef struct BGM {
	int attack;
	int cursor;
	int day;
	int gameover;
	int menu;
	int move;
	int night;
	int pickup;
	int push;
	int slash;
} Bgm;

void get_sound_se(const int& name);
void get_sound_music(const int& name);
void get_sound_start(const int& name);
void change_sound_volume();
