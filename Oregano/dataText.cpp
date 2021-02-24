#include "dataText.h"
#include "DxLib.h"
#include "constant.h"
#include "eventBase.h"
#include <iostream>
#include <fstream>
#include <codecvt>

DataText::DataText(Input& input) : input(input), textBox(120) {
	defaultColor = GetColor(185, 185, 210);
	textFile = "resource\\Data\\itemData.txt";
}

DataText::~DataText() {
}

/// <summary>
/// wstring文字からstring文字に変換し返す
/// </summary>
/// <param name="wStr">wstring文字</param>
string DataText::convertStringFromWString(wstring wStr) {
	//新しい文字列を受け取るバッファサイズの取得
	int bufferSize = WideCharToMultiByte(CP_OEMCP, 0, wStr.c_str()
	                                     , -1, static_cast<char*>(nullptr),
	                                     0, nullptr, nullptr);

	CHAR* lpMultiByteStr = new CHAR[bufferSize]; //// 新しい文字列を受け取るバッファのアドレスの取得

	WideCharToMultiByte(CP_OEMCP, 0, wStr.c_str(),
	                    -1, lpMultiByteStr, bufferSize,
	                    nullptr, nullptr); //wstringからShiftJISに変換


	string outStr(lpMultiByteStr, lpMultiByteStr + bufferSize - 1); //stringの生成

	delete[] lpMultiByteStr; //バッファの破棄

	return outStr;
}

/// <summary>
/// 読み込んだutf8のテキストファイルをwstring文字として返す
/// </summary>
wstring DataText::charFromUtf8() {
	wifstream ifs(textFile); //ファイルを開く

	ifs.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); //ロケールの設定

	//wstringの生成
	wstring str((istreambuf_iterator<wchar_t>(ifs)), istreambuf_iterator<wchar_t>());

	ifs.close(); //ファイルを閉じる

	return str;
}

void DataText::showItemText() {
	//setlocale(LC_ALL, "");

	LPCSTR fontPath = "resource\\Font\\SoukouMincho.ttf"; //フォントファイルのパス指定

	/* フォントデータのロード */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "",MB_OK); //エラーメッセージ
	}

	SetFontSize(itemFontSize); //フォントサイズの変更

	ChangeFont("装甲明朝", DX_CHARSET_DEFAULT); //読み込んだフォントに変更

	////アイテム一覧と説明を表示
	drawString(0);
	drawString(1);
	drawString(2);


	SetFontSize(15); //フォントサイズをデフォルトに戻す

	/* フォントデータのアンロード */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //エラーメッセージ
	}
}

void DataText::drawString(const int& line) {
	DrawFormatString(textPosition(line), 50 + (line / 3) * itemFontSize + lineFeed(line), defaultColor,
	                 convertStringFromWString(charFromUtf8()).substr(textLine(line), textBox[line]).c_str(),
	                 false);
}

/// <summary>
/// テキストの開始位置を返す
/// </summary>
/// <param name="line">テキストの行</param>
int DataText::textLine(const int& line) {
	int textLen = 0; //文字数格納場所

	if (line != 0) {
		for (int n = line - 1; n >= 0; --n) {
			textLen += textBox[n]; //行数分の配列中の文字数を加算
		}
		return textLen; //加算後、文字数の和を返す
	}
	return 0; //最初なので、初期開始位置の0を返す
}

int DataText::textPosition(const int& line) {
	if (line % 3 == 1) return 500;
	if (line % 3 == 2) return 800;
	return 200;
}

int DataText::lineFeed(const int& line) {
	//if (line >= 3 && line % 3 != 2) return itemFontSize * 2;
	//if (line >= 3 && line % 3 == 2) return itemFontSize * 4;
	return 0;
}

void DataText::returnGameScene() {
	if (input.Y) {
		EventBase::gameScene = GAME_SCENE;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void DataText::update() {
	showItemText();
	returnGameScene();

	DrawFormatString(0, 0, defaultColor, "%d", textBox[7], false);
}
