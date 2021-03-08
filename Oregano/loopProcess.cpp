#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"
#include "sceneTitle.h"

void loopProcess() {

	Input input; //���̓N���X

	MapDraw draw_; //�}�b�v�N���X
	MapCollision collision(draw_); //�R���W�����N���X
	Player player(input, draw_); //�v���C���[�N���X
	EnemyConclusion enemy(player); //�G�܂Ƃ߃N���X

	GameUI gameUI(input, player, draw_); //�Q�[��UI�N���X

	PlayerState state;
	DataSave save(state, gameUI); //�Z�[�u�f�[�^�N���X
	SceneTitle title(save); //�^�C�g���N���X

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		input.update(); //���͏���

		/* �^�C�g���V�[������ */
		if (SceneTitle::gameScene == TITLE_SCENE) {
			if (input.X) SceneTitle::gameScene = ROAD_SCENE;
		}

		/* ���[�h�V�[������ */
		if (SceneTitle::gameScene == ROAD_SCENE) {
			title.update();
		}

			/* �Q�[���V�[������ */
		else if (SceneTitle::gameScene == GAME_SCENE) {
			draw_.update(title.roadingMap()); //�}�b�v�X�V����

			collision.update(); //�R���W�����X�V����

			input.movement(collision, draw_); //�ړ�����

			player.update(); //�v���C���[�X�V����

			//enemy.update(); //�G�X�V����

			gameUI.update(); //UI�X�V����
		}
			/* ���j���[�V�[������ */
		else if (SceneTitle::gameScene == MENU_SCENE) {
		}

			/* �Q�[���I�[�o�[�V�[������ */
		else if (SceneTitle::gameScene == GAME_OVER_SCENE) {
		}

			/* �G���h�V�[������ */
		else if (SceneTitle::gameScene == END_SCENE) {
			save.writeSaveData(); //�t�@�C���������ݏ����i��x�̂݁j
			break; //�I�������i���[�v���甲����j
		}

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
