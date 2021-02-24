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

#include "sceneTitle.h"

void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(source.playerGraph()); //�v���C���[�N���X
	EventBase event; //�C�x���g�N���X
	EventField field(input, event, player); //�t�B�[���h�N���X
	DataText text(input);
	DataSave save(player, field, text); //�Z�[�u�f�[�^�N���X
	GameUI gameUI(input);

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw mapDraw_(source.mapChipGraph()); //�}�b�v�N���X
		MapCollision collision(mapDraw_); //�R���W�����N���X

		input.update(); //���͍X�V����

		if (EventBase::gameScene == TITLE_SCENE) {
			titleProcess(save); //�^�C�g���V�[������
			save.update();
			DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", text.textBox[7], false);
		}

		else if (EventBase::gameScene == GAME_SCENE) {
			collision.update(); //�R���W�����X�V����

			if (!gameUI.changeFlag) //�ړ������i�A�N�V�����ύX���͈ړ��s�j
				input.moveProcess(collision);

			field.update(); //�t�B�[���h�X�V����

			gameUI.update(); //UI�X�V����
		}
		else if (EventBase::gameScene == MENU_ITEM_SCENE) {
			text.update(); //�e�L�X�g�X�V����
		}
		else if (EventBase::gameScene == END_SCENE) {
			CALL_ONCE(save.writeSaveData()); //�t�@�C���������ݏ����i��x�̂݁j
			break; //�I������
		}

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
