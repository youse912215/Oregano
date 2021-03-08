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
	LPCSTR fontPath = "resource\\Font\\SHOWG.TTF"; //フォントファイルのパス指定

	/* フォントデータのロード */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "", MB_OK); //エラーメッセージ
	}

	ChangeFont("Showcard Gothic", DX_CHARSET_DEFAULT); //読み込んだフォントに変更
	SetFontSize(fontSize); //フォントサイズの変更

	/* フォントデータのアンロード */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //エラーメッセージ
	}
}

void DataText::drawText() {
	//現在の所持コイン数を表示
	for (int i = 0; i <= BLOODING; ++i) {
		DrawFormatString(coinPos.x + BLOCK_SIZE * i, coinPos.y, color[4], "%d",
		                 PlayerState::coin[i], false);
		/* 属性耐久値を表示 */
		if (!PlayerState::condition[i])
			DrawFormatString(accumulationPos.x + BLOCK_SIZE * i, accumulationPos.y, color[i],
			                 "%d", PlayerState::attributeAccumulation[i], false);
	}
}
