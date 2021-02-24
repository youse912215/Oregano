#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(source.playerGraph()); //�v���C���[�N���X
	EventBase event; //�C�x���g�N���X
	EventField field(input, event, player); //�t�B�[���h�N���X
	DataSave save(player, field); //�Z�[�u�f�[�^�N���X
	GameUI gameUI(input);
	DataText text(save);

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw map(source.mapChipGraph()); //�}�b�v�N���X
		MapCollision collision(map); //�R���W�����N���X

		input.update(); //���͍X�V����

		if (EventBase::gameScene == TITLE_SCENE)
			CALL_ONCE(save.roadSaveData()); //�t�@�C���ǂݍ��ݏ����i��x�̂݁j

		if (EventBase::gameScene == GAME_SCENE) {
			map.update(); //�}�b�v�X�V����
			collision.update(); //�R���W�����X�V����


			if (!gameUI.changeFlag) //�ړ������i�A�N�V�����ύX���͈ړ��s�j
				input.moveProcess(collision.leftCollisionFlag(), collision.rightCollisionFlag(),
				                  collision.upCollisionFlag(), collision.downCollisionFlag());

			event.update();

			field.update(); //�t�B�[���h�X�V����

			save.update(); //�f�[�^�X�V����

			player.update(); //�v���C���[�X�V����

			gameUI.update();

			text.update();
		}

		if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //�t�@�C���������ݏ����i��x�̂݁j
			break; //�I������
		}

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
