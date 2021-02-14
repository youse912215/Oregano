#include "DxLib.h"
#include "windowPreference.h"
#include "inputProcess.h"
#include "dataSource.h"
#include "player.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "eventField.h"
#include "eventBase.h"

void loopProcess() {

	Input input; //���̓N���X
	DataSource source; //�f�ރN���X
	Player player(source.playerGraph()); //�v���C���[�N���X
	EventBase event; //�C�x���g�N���X
	EventField field(input, event); //�t�B�[���h�N���X

	while (true) {
		ClearDrawScreen(); //��ʃN���A

		MapDraw map(source.mapChipGraph()); //�}�b�v�N���X
		MapCollision collision(map); //�R���W�����N���X

		map.update(); //�}�b�v�X�V����

		input.update(); //���͍X�V����
		input.moveProcess(collision.leftCollisionFlag(), collision.rightCollisionFlag(),
		                  collision.upCollisionFlag(), collision.downCollisionFlag());

		field.update(); //�t�B�[���h�X�V����

		player.draw(); //�v���C���[�`�揈��

		if (EventBase::gameScene == END_SCENE) break; //�C������

		windowSettingInLoop(); //���[�v���E�B���h�E�ݒ�
		if (ProcessMessage() == -1) break; //Windows�V�X�e�����炭���������
	}
}
