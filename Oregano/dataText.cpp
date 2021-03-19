#include "dataText.h"
#include "DxLib.h"
#include "playerState.h"

DataText::DataText() :
	coinPos(20, 30), accumulationPos(WIN_WIDTH - 250, WIN_HEIGHT - 60), fontSize(32),
	color{
		//花萌葱
		GetColor(0x00, 0x8d, 0x56),
		//深支子
		GetColor(0xef, 0xbb, 0x2c),
		//燕子花
		GetColor(0x4b, 0x5e, 0xaa),
		//中紅花
		GetColor(0xee, 0x86, 0x9a),
		//茶色（その他文字用）
		GetColor(0x50, 0x34, 0x50)
	} {
}

/// <summary>
/// フォントのロード
/// </summary>
void DataText::loadFont() {
	LPCSTR fontPath = "resource\\Font\\SHOWG.TTF"; //フォントファイルのパス指定

	/* フォントデータのロード */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "", MB_OK); //エラーメッセージ
	}

	ChangeFont("Showcard Gothic", DX_CHARSET_DEFAULT); //読み込んだフォントに変更
	SetFontSize(fontSize); //フォントサイズの変更

	drawText(); //テキストの描画

	/* フォントデータのアンロード */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //エラーメッセージ
	}
}

/// <summary>
/// テキストの描画
/// </summary>
void DataText::drawText() {
	//現在の所持コイン数を表示
	for (int i = 0; i <= BLOODING; ++i) {
		DrawFormatString(coinPos.x + BLOCK_SIZE * i, coinPos.y, color[4], "%d",
		                 PlayerState::coin[i], false);
		/* 属性耐久値を表示 */
		if (PlayerState::condition[i]) continue; //条件以外のとき、処理をスキップする
		DrawFormatString(accumulationPos.x + BLOCK_SIZE * i, accumulationPos.y, color[i],
		                 "%d", PlayerState::attributeAccumulation[i], false);
	}
}
