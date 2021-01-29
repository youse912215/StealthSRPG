#pragma once
#include <vector>

using namespace std;

class SceneTransition {
private:

public:
	static int game_scene;

	void transition_to_result(vector<vector<int>>& map, const int& px, const int& py);
	void transition_to_gameover(const bool& isAlive);
};
