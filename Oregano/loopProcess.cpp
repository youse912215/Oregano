#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "dataSave.h"
#include "gameUI.h"

#include "sceneRoad.h"
#include "sceneSave.h"
#include "sceneMenu.h"
#include "sceneGameOver.h"
#include "sceneEnd.h"

void loopProcess() {

	Input input; //���̓N���X

	MapDraw draw_; //�}�b�v�N���X
	MapCollision collision(draw_); //�R���W�����N���X
	Player player(input, draw_); //�v���C���[�N���X
	EnemyConclusion enemy(player); //�G�܂Ƃ߃N���X

	GameUI gameUI(input, player, draw_); //�Q�[��UI�N���X

	PlayerState state; //�v���C���[��ԃN���X
	DataSave data(state, gameUI); //�Z�[�u�f�[�^�N���X

	SceneRoad road(data); //���[�h�V�[���N���X
	SceneSave save(data, input); //�Z�[�u�V�[���N���X
	SceneMenu menu(input); //���j���[�V�[���N���X
	SceneGameOver gameOver(data, input); //�Q�[���I�[�o�[�N���X
	SceneEnd end(input); //�G���h�V�[���N���X

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		input.update(); //���͏���

		/* �^�C�g���V�[������ */
		if (SceneRoad::gameScene == TITLE_SCENE) {
			if (input.A) SceneRoad::gameScene = ROAD_SCENE;
		}
		/* ���[�h�V�[������ */
		road.update(); //�X�V����

		/* �Q�[���V�[������ */
		if (SceneRoad::gameScene == GAME_SCENE) {
			draw_.update(road.roadingMap()); //�}�b�v�X�V����

			collision.update(); //�R���W�����X�V����

			input.menuProcess(); //���j���[����
			input.movement(collision, draw_); //�ړ�����

			player.update(); //�v���C���[�X�V����

			//enemy.update(); //�G�X�V����

			gameUI.update(); //UI�X�V����
		}

		/* �Z�[�u�V�[������ */
		save.update(); //�X�V����

		/* ���j���[�V�[������ */
		menu.update(); //�X�V����

		/* �Q�[���I�[�o�[�V�[������ */
		gameOver.update(); //�X�V����

		/* �G���h�V�[������ */
		end.update(); //�X�V����

		if (gameOver.endFlag || end.endFlag) break; //�I������

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
