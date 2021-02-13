#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "coordinate_confirmation.h"

void loop_process() {
	// �Q�[�����[�v

	int playerGraph = LoadGraph("resource/charactor/player.png");
	int mapGraph = LoadGraph("resource/map/mapchip.png"); //�}�b�v�`�b�v�摜�t�@�C���̓ǂݍ���
	Player player(WIN_WIDTH / 2 - BLOCK_SIZE / 2, WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2, playerGraph);


	while (true) {
		// ��ʃN���A
		ClearDrawScreen();

		MapDraw map(mapGraph);
		MapCollision collision(map);

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break; //�I������

		map.update();

		Input* input = new Input;
		input->input_info();
		input->moving_process(collision.leftCollisionFlag(), collision.rightCollisionFlag(),
		                      collision.upCollisionFlag(), collision.downCollisionFlag());
		delete input;

		player.draw();

		DrawFormatString(0, 75, GetColor(255, 0, 0),
		                 "LU y:%d, x:%d", player.y, player.x, false);
		DrawFormatString(150, 75, GetColor(255, 0, 0),
		                 "RU y:%d, x:%d", player.y, player.x + BLOCK_SIZE, false);
		DrawFormatString(0, 90, GetColor(255, 0, 0),
		                 "LD y:%d, x:%d", player.y + BLOCK_SIZE, player.x, false);
		DrawFormatString(150, 90, GetColor(255, 0, 0),
		                 "RD y:%d, x:%d", player.y + BLOCK_SIZE, player.x + BLOCK_SIZE, false);

		window_in_roop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
