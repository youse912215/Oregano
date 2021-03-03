#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "enemy.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

#include "sceneTitle.h"

#include "effectBlood.h"
#include "effectSpurt.h"


void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(input); //�v���C���[�N���X

	Enemy enemy;
	vector<Enemy> enemies(30);

	EventBase event; //�C�x���g�N���X
	EventField field(input, event, player); //�t�B�[���h�N���X
	DataText text(input); //�e�L�X�g�N���X
	DataSave save(player, field, text); //�Z�[�u�f�[�^�N���X
	GameUI gameUI(input); //�Q�[��UI�N���X
	SceneTitle title(save);

	EffectBlood blood;
	vector<EffectBlood> bloods(100);

	EffectSpurt spurt;
	vector<EffectSpurt> spurts(150);

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw mapDraw_(source.mapChip); //�}�b�v�N���X
		MapCollision collision(mapDraw_); //�R���W�����N���X

		input.update(); //���͏���

		/* �^�C�g���V�[������ */
		if (EventBase::gameScene == TITLE_SCENE) title.titleProcess();

			/* �Q�[���V�[������ */
		else if (EventBase::gameScene == GAME_SCENE) {


			mapDraw_.update(title.returnMapAll()); //�}�b�v�X�V����
			collision.update(); //�R���W�����X�V����


			//if (!gameUI.changeFlag) //�ړ������i�A�N�V�����ύX���͈ړ��s�j
			input.moveProcess(collision);

			field.update(); //�t�B�[���h�X�V����

			gameUI.update(); //UI�X�V����2

			/* �G�̕��� */
			for (auto& i : enemies) {
				//�������Ă��Ȃ����A���S���ԂłȂ��Ƃ�
				if (!i.activity && !i.deadFlag) {
					i.initialize(player); //������
				}
				i.update(player); //�X�V����
				//���S���Ԃ̂Ƃ�
				if (i.deadFlag) {
					blood.update(bloods, i.screenPos, i.attribute); //���̃G�t�F�N�g
					if (i.deadTime <= 15) spurt.update(spurts, i.screenPos); //�����o���i�R�C���j�G�t�F�N�g
				}
			}


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
