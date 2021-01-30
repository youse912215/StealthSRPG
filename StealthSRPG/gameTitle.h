#pragma once

class GameTitle {
private:
	int title;
	int button;
	static int button_timer;

	void draw();
	void get_timer();

public:
	GameTitle();
	~GameTitle();
	void update();
};
