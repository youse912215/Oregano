#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "enemy.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "mapAutogeneration.h"
#include "eventField.h"
#include "eventBase.h"
#include "dataSave.h"
#include "gameUI.h"
#include "dataText.h"

#include "sceneTitle.h"

void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(input, source); //�v���C���[�N���X

	//Enemy enemy(source.enemy1, player);
	vector<Enemy*> enemies;

	for (unsigned int i = 0; i < 10; ++i)
		enemies.push_back(new Enemy(source.enemy1, player));

	EventBase event; //�C�x���g�N���X
	EventField field(input, event, player); //�t�B�[���h�N���X
	DataText text(input); //�e�L�X�g�N���X
	DataSave save(player, field, text); //�Z�[�u�f�[�^�N���X
	GameUI gameUI(input); //�Q�[��UI�N���X
	SceneTitle title(save);

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw mapDraw_(source.mapChipGraph()); //�}�b�v�N���X
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

			gameUI.update(); //UI�X�V����

			//enemy.update();
			for (unsigned int i = 0; i != enemies.size(); ++i) {
				enemies[i]->update();
			}

			for (unsigned int i = enemies.size() - 1; i != 0; --i) {
				if (enemies[i]->alive) continue;
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				enemies.push_back(new Enemy(source.enemy1, player));
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
	for (unsigned int i = 0; i != enemies.size(); ++i) {
		delete enemies[i];
	}

}
