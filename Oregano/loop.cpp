#include "DxLib.h"
#include "window_preference.h"
#include "input.h"
#include "player.h"
#include "map_draw.h"
#include "coordinate_confirmation.h"

void loop_process() {
	// �Q�[�����[�v
	while (true) {
		// ��ʃN���A
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //�I������
		Input* input = new Input;
		input->moving_process();
		delete input;
		Map_draw* map_draw = new Map_draw;
		map_draw->drawing_map();
		delete map_draw;
		Player* player = new Player;
		player->draw();
		delete player;
		Coodinate* debug = new Coodinate;
		debug->debug();
		delete debug;

		window_in_roop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
