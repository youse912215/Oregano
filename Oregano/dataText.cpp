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

	int add = 0;

	////�A�C�e���ꗗ�Ɛ�����\��
	for (unsigned int i = 0; i < save.ItemTextBox.size(); ++i) {
		if (i >= 90) add = 800;

		DrawFormatString(200 + add, i * itemFontSize - add, defaultColor,
		                 convertStringFromWString(charFromUtf8()).substr(textLine(i), save.ItemTextBox[i]).c_str(),
		                 false);
	}


	SetFontSize(15); //�t�H���g�T�C�Y���f�t�H���g�ɖ߂�

	/* �t�H���g�f�[�^�̃A�����[�h */
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, nullptr)) {
	}
	else {
		MessageBox(nullptr, "remove error", "", MB_OK); //�G���[���b�Z�[�W
	}
}

/// <summary>
/// �e�L�X�g�̊J�n�ʒu��Ԃ�
/// </summary>
/// <param name="line">�e�L�X�g�̍s</param>
int DataText::textLine(const int& line) {
	int textLen = 0; //�������i�[�ꏊ

	if (line != 0) {
		for (int n = line - 1; n >= 0; --n) {
			textLen += save.ItemTextBox[n]; //�s�����̔z�񒆂̕����������Z
		}
		return textLen; //���Z��A�������̘a��Ԃ�
	}
	return 0; //�ŏ��Ȃ̂ŁA�����J�n�ʒu��0��Ԃ�
}

/// <summary>
/// �X�V����
/// </summary>
void DataText::update() {
	showItemText();
}
