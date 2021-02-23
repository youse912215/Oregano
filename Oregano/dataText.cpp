#include "dataText.h"
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>

DataText::DataText() {
	textFile = "resource\\Data\\game.txt";
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

/// <summary>
/// 更新処理
/// </summary>
void DataText::update() {
	//setlocale(LC_ALL, "");

	DrawFormatString(400, 300, GetColor(255, 0, 255),
	                 convertStringFromWString(charFromUtf8()).substr(0, 25).c_str(), false);
}
