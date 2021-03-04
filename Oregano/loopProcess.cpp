#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "enemyConclusion.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

#include "sceneTitle.h"


void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(input); //�v���C���[�N���X
	EnemyConclusion enemy(player); //�G�܂Ƃ߃N���X
	GameUI gameUI(input); //�Q�[��UI�N���X

	EventBase event; //�C�x���g�N���X
	EventField field(input, event, player); //�t�B�[���h�N���X
	DataText text(input); //�e�L�X�g�N���X
	DataSave save(player, field, text); //�Z�[�u�f�[�^�N���X
	SceneTitle title(save); //�^�C�g���N���X


	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw mapDraw_(source.mapChip); //�}�b�v�N���X
		MapCollision collision(mapDraw_); //�R���W�����N���X

		input.update(); //���͏���

		/* �^�C�g���V�[������ */
		if (EventBase::gameScene == TITLE_SCENE) title.update();

			/* �Q�[���V�[������ */
		else if (EventBase::gameScene == GAME_SCENE) {
			mapDraw_.update(title.roadingMap()); //�}�b�v�X�V����

			collision.update(); //�R���W�����X�V����

			//if (!gameUI.changeFlag) //�ړ������i�A�N�V�����ύX���͈ړ��s�j
			input.movement(collision, mapDraw_);

			field.update(); //�t�B�[���h�X�V����

			gameUI.update(); //UI�X�V����2

			//enemy.update(); //�G�X�V����
		}
			/* ���j���[�V�[������ */
		else if (EventBase::gameScene == MENU_ITEM_SCENE) {
			text.update(); //�e�L�X�g�X�V����
		}
			/* �G���h�V�[������ */
		else if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //�t�@�C���������ݏ����i��x�̂݁j
			break; //�I�������i���[�v���甲����j
		}

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
