#include "music.h"
#include "DxLib.h"

Bgm bgm = {
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

void get_sound_se(const int& name) {
	PlaySoundMem(name, DX_PLAYTYPE_BACK, TRUE);
}

void get_sound_music(const int& name) {
	PlaySoundMem(name, DX_PLAYTYPE_LOOP, FALSE);
}

void get_sound_start(const int& name) {
	PlaySoundMem(name, DX_PLAYTYPE_LOOP, TRUE);
}

void change_sound_volume() {
	ChangeVolumeSoundMem(130, bgm.menu);
	ChangeVolumeSoundMem(100, bgm.gameover);
	ChangeVolumeSoundMem(70, bgm.attack);
	ChangeVolumeSoundMem(70, bgm.cursor);
	ChangeVolumeSoundMem(70, bgm.move);
	ChangeVolumeSoundMem(70, bgm.pickup);
	ChangeVolumeSoundMem(70, bgm.push);
	ChangeVolumeSoundMem(70, bgm.slash);
}
