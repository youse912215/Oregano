#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "player.h"
#include "playerState.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "dataSave.h"
#include "dataSource.h"
#include "gameUI.h"

#include "sceneTitle.h"
#include "sceneLoad.h"
#include "sceneGame.h"
#include "sceneSave.h"
#include "sceneMenu.h"
#include "sceneGameOver.h"
#include "sceneEnd.h"

void loopProcess() {

	Input input; //���̓N���X

	DataSource source; //�f�[�^�\�[�X�N���X

	MapDraw draw_; //�}�b�v�N���X
	MapCollision collision(draw_); //�R���W�����N���X
	Player player(input, draw_, source); //�v���C���[�N���X
	EnemyConclusion enemy(player, source); //�G�܂Ƃ߃N���X

	GameUI gameUI(input, player, draw_, source); //�Q�[��UI�N���X

	PlayerState state; //�v���C���[��ԃN���X
	DataSave data(state, gameUI); //�Z�[�u�f�[�^�N���X

	SceneTitle title(input); //�^�C�g���V�[���N���X
	SceneLoad load(data); //���[�h�V�[���N���X
	SceneGame game(input, draw_, collision, load, player, enemy, gameUI); //�Q�[���V�[���N���X
	SceneSave save(data, input, gameUI); //�Z�[�u�V�[���N���X
	SceneMenu menu(input); //���j���[�V�[���N���X
	SceneGameOver gameOver(data, input); //�Q�[���I�[�o�[�N���X
	SceneEnd end(input); //�G���h�V�[���N���X

	source.playBgm(); //����BGM

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		input.update(); //���͏���

		title.update(); //�^�C�g���V�[���X�V����

		load.update(); //���[�h�V�[���X�V����

		game.update(); //�Q�[���V�[���X�V����

		save.update(); //�Z�[�u�V�[���X�V����

		menu.update(); //���j���[�V�[���X�V����

		gameOver.update(); //�Q�[���I�[�o�[�V�[���X�V����

		end.update(); //�G���h�V�[���X�V����

		//�I���t���O��true�̂Ƃ�
		if (gameOver.endFlag || end.endFlag) break; //�I������

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
