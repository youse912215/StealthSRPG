#include "init_princess.h"
#include "inputProcess.h"
#include "Princess.h"

void init_princess() {
	Input input;
	Princess Princess(
		block_size * 10, block_size * 14,
		LoadGraph("Source/Charactor/princess.png"),
		block_size, 50, 100, true, input);
}
