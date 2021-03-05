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

	GameUI gameUI(input, draw_); //�Q�[��UI�N���X

	PlayerState state;
	DataSave save(state); //�Z�[�u�f�[�^�N���X
	SceneTitle title(save); //�^�C�g���N���X

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		input.update(); //���͏���

		/* �^�C�g���V�[������ */
		if (SceneTitle::gameScene == TITLE_SCENE) title.update();

			/* �Q�[���V�[������ */
		else if (SceneTitle::gameScene == GAME_SCENE) {
			draw_.update(title.roadingMap()); //�}�b�v�X�V����

			collision.update(); //�R���W�����X�V����

			//if (!gameUI.changeFlag) //�ړ������i�A�N�V�����ύX���͈ړ��s�j
			input.movement(collision, draw_);

			player.update(); //�v���C���[�X�V����

			enemy.update(); //�G�X�V����

			save.update();

			//gameUI.update(); //UI�X�V����
		}
			/* ���j���[�V�[������ */
		else if (SceneTitle::gameScene == MENU_ITEM_SCENE) {
		}
			/* �G���h�V�[������ */
		else if (SceneTitle::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //�t�@�C���������ݏ����i��x�̂݁j
			break; //�I�������i���[�v���甲����j
		}

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
