#include "coordinate_confirmation.h"
#include "DxLib.h"
#include <string>

using namespace std;

void Coodinate::debug() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d, %d", current_map_x, current_map_y, false);
}
