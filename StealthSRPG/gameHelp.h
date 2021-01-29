#pragma once

class GameHelp {
private:
	int manual;
	int enemy_infomation;
	int map_infomation;

public:
	static int help_num;

	GameHelp();
	~GameHelp();
	void draw();
};
