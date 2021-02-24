#include "dataText.h"
#include "DxLib.h"
#include "constant.h"
#include <iostream>
#include <fstream>
#include <codecvt>

DataText::DataText(DataSave& save) : save(save),

                                     num{
	                                     7, 15, 1, 5, 15, 1, 3, 30, 1,
	                                     3, 17, 1, 3, 15, 1, 5, 15, 1,
	                                     9, 24, 1, 9, 24, 1, 15, 25, 1,
	                                     5, 27, 1, 7, 25, 1, 7, 15, 1,
	                                     13, 9, 1, 7, 9, 1, 15, 9, 1,
	                                     7, 9, 1, 5, 9, 1, 5, 35, 1,
	                                     9, 35, 1, 9, 23, 1, 7, 13, 1,
	                                     5, 27, 1, 13, 9, 1, 7, 15, 29,
	                                     7, 16, 35, 7, 15, 22, 7, 15, 37,
	                                     7, 23, 1, 9, 9, 1, 9, 9, 1,
	                                     13, 9, 1, 7, 30, 1, 5, 29, 1,
	                                     9, 21, 1, 7, 37, 37, 11, 46, 43,
	                                     15, 9, 1, 19, 15, 55, 9, 9, 1,
	                                     15, 15, 35
                                     } {
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

	int add = 0;

	////アイテム一覧と説明を表示
	for (unsigned int i = 0; i < save.ItemTextBox.size(); ++i) {
		if (i >= 90) add = 800;

		DrawFormatString(200 + add, i * itemFontSize - add, defaultColor,
		                 convertStringFromWString(charFromUtf8()).substr(textLine(i), save.ItemTextBox[i]).c_str(),
		                 false);
	}


	SetFontSize(15); //フォントサイズをデフォルトに戻す

	/* フォントデータのアンロード */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //エラーメッセージ
	}
}

/// <summary>
/// テキストの開始位置を返す
/// </summary>
/// <param name="line">テキストの行</param>
int DataText::textLine(const int& line) {
	int textLen = 0; //文字数格納場所

	if (line != 0) {
		for (int n = line - 1; n >= 0; --n) {
			textLen += save.ItemTextBox[n]; //行数分の配列中の文字数を加算
		}
		return textLen; //加算後、文字数の和を返す
	}
	return 0; //最初なので、初期開始位置の0を返す
}

/// <summary>
/// 更新処理
/// </summary>
void DataText::update() {
	showItemText();
}
