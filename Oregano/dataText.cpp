#include "dataText.h"
#include "DxLib.h"
#include "playerState.h"

DataText::DataText() :
	coinPos(20, 30), accumulationPos(WIN_WIDTH - 250, WIN_HEIGHT - 60), fontSize(32),
	color{
		//�ԖG�K
		GetColor(0x00, 0x8d, 0x56),
		//�[�x�q
		GetColor(0xef, 0xbb, 0x2c),
		//���q��
		GetColor(0x4b, 0x5e, 0xaa),
		//���g��
		GetColor(0xee, 0x86, 0x9a),
		//���F�i���̑������p�j
		GetColor(0x50, 0x34, 0x50)
	} {
}

/// <summary>
/// �t�H���g�̃��[�h
/// </summary>
void DataText::loadFont() {
	LPCSTR fontPath = "resource\\Font\\SHOWG.TTF"; //�t�H���g�t�@�C���̃p�X�w��

	/* �t�H���g�f�[�^�̃��[�h */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "", MB_OK); //�G���[���b�Z�[�W
	}

	ChangeFont("Showcard Gothic", DX_CHARSET_DEFAULT); //�ǂݍ��񂾃t�H���g�ɕύX
	SetFontSize(fontSize); //�t�H���g�T�C�Y�̕ύX

	drawText(); //�e�L�X�g�̕`��

	/* �t�H���g�f�[�^�̃A�����[�h */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //�G���[���b�Z�[�W
	}
}

/// <summary>
/// �e�L�X�g�̕`��
/// </summary>
void DataText::drawText() {
	//���݂̏����R�C������\��
	for (int i = 0; i <= BLOODING; ++i) {
		DrawFormatString(coinPos.x + BLOCK_SIZE * i, coinPos.y, color[4], "%d",
		                 PlayerState::coin[i], false);
		/* �����ϋv�l��\�� */
		if (PlayerState::condition[i]) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		DrawFormatString(accumulationPos.x + BLOCK_SIZE * i, accumulationPos.y, color[i],
		                 "%d", PlayerState::attributeAccumulation[i], false);
	}
}
