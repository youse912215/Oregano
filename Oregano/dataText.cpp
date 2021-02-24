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
/// wstring��������string�����ɕϊ����Ԃ�
/// </summary>
/// <param name="wStr">wstring����</param>
string DataText::convertStringFromWString(wstring wStr) {
	//�V������������󂯎��o�b�t�@�T�C�Y�̎擾
	int bufferSize = WideCharToMultiByte(CP_OEMCP, 0, wStr.c_str()
	                                     , -1, static_cast<char*>(nullptr),
	                                     0, nullptr, nullptr);

	CHAR* lpMultiByteStr = new CHAR[bufferSize]; //// �V������������󂯎��o�b�t�@�̃A�h���X�̎擾

	WideCharToMultiByte(CP_OEMCP, 0, wStr.c_str(),
	                    -1, lpMultiByteStr, bufferSize,
	                    nullptr, nullptr); //wstring����ShiftJIS�ɕϊ�


	string outStr(lpMultiByteStr, lpMultiByteStr + bufferSize - 1); //string�̐���

	delete[] lpMultiByteStr; //�o�b�t�@�̔j��

	return outStr;
}

/// <summary>
/// �ǂݍ���utf8�̃e�L�X�g�t�@�C����wstring�����Ƃ��ĕԂ�
/// </summary>
wstring DataText::charFromUtf8() {
	wifstream ifs(textFile); //�t�@�C�����J��

	ifs.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); //���P�[���̐ݒ�

	//wstring�̐���
	wstring str((istreambuf_iterator<wchar_t>(ifs)), istreambuf_iterator<wchar_t>());

	ifs.close(); //�t�@�C�������

	return str;
}

void DataText::showItemText() {
	//setlocale(LC_ALL, "");

	LPCSTR fontPath = "resource\\Font\\SoukouMincho.ttf"; //�t�H���g�t�@�C���̃p�X�w��

	/* �t�H���g�f�[�^�̃��[�h */
	if (AddFontResourceEx(fontPath, FR_PRIVATE, nullptr) > 0) {
	}
	else {
		MessageBox(nullptr, "add error", "",MB_OK); //�G���[���b�Z�[�W
	}

	SetFontSize(itemFontSize); //�t�H���g�T�C�Y�̕ύX

	ChangeFont("���b����", DX_CHARSET_DEFAULT); //�ǂݍ��񂾃t�H���g�ɕύX

	////�A�C�e���ꗗ�Ɛ�����\��
	drawString(0);
	drawString(1);
	drawString(2);


	SetFontSize(15); //�t�H���g�T�C�Y���f�t�H���g�ɖ߂�

	/* �t�H���g�f�[�^�̃A�����[�h */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //�G���[���b�Z�[�W
	}
}

void DataText::drawString(const int& line) {
	DrawFormatString(textPosition(line), 50 + (line / 3) * itemFontSize + lineFeed(line), defaultColor,
	                 convertStringFromWString(charFromUtf8()).substr(textLine(line), textBox[line]).c_str(),
	                 false);
}

/// <summary>
/// �e�L�X�g�̊J�n�ʒu��Ԃ�
/// </summary>
/// <param name="line">�e�L�X�g�̍s</param>
int DataText::textLine(const int& line) {
	int textLen = 0; //�������i�[�ꏊ

	if (line != 0) {
		for (int n = line - 1; n >= 0; --n) {
			textLen += textBox[n]; //�s�����̔z�񒆂̕����������Z
		}
		return textLen; //���Z��A�������̘a��Ԃ�
	}
	return 0; //�ŏ��Ȃ̂ŁA�����J�n�ʒu��0��Ԃ�
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
/// �X�V����
/// </summary>
void DataText::update() {
	showItemText();
	returnGameScene();

	DrawFormatString(0, 0, defaultColor, "%d", textBox[7], false);
}
