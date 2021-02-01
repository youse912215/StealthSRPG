#pragma once

class GameHelp {
private:
	int manual;
	int map_information;
	int enemy_information;
	int enemy_information_2;
	int return_game;
	int help;

public:
	static int help_num;

	GameHelp();
	~GameHelp();
	void draw();
	void map_scene_draw();
};
