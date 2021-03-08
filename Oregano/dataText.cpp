#include "dataText.h"
#include "DxLib.h"
#include "playerState.h"

DataText::DataText() :
	coinPos(20, 30), accumulationPos(WIN_WIDTH - 250, WIN_HEIGHT - 60), fontSize(32),
	color{
		GetColor(0x00, 0x8d, 0x56), GetColor(0xef, 0xbb, 0x2c),
		GetColor(0x4b, 0x5e, 0xaa), GetColor(0xee, 0x86, 0x9a),
		GetColor(0x50, 0x34, 0x50)
	} {
}

void DataText::roadFont() {
	LPCSTR fontPath = "resource\\Font\\SHOWG.TTF"; //�t�H���g�t�@�C���̃p�X�w��

	/* �t�H���g�f�[�^�̃��[�h */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "", MB_OK); //�G���[���b�Z�[�W
	}

	ChangeFont("Showcard Gothic", DX_CHARSET_DEFAULT); //�ǂݍ��񂾃t�H���g�ɕύX
	SetFontSize(fontSize); //�t�H���g�T�C�Y�̕ύX

	/* �t�H���g�f�[�^�̃A�����[�h */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //�G���[���b�Z�[�W
	}
}

void DataText::drawText() {
	//���݂̏����R�C������\��
	for (int i = 0; i <= BLOODING; ++i) {
		DrawFormatString(coinPos.x + BLOCK_SIZE * i, coinPos.y, color[4], "%d",
		                 PlayerState::coin[i], false);
		/* �����ϋv�l��\�� */
		if (!PlayerState::condition[i])
			DrawFormatString(accumulationPos.x + BLOCK_SIZE * i, accumulationPos.y, color[i],
			                 "%d", PlayerState::attributeAccumulation[i], false);
	}
}
