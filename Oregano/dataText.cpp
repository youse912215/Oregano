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

/// <summary>
/// �X�V����
/// </summary>
void DataText::update() {
	//setlocale(LC_ALL, "");

	DrawFormatString(400, 300, GetColor(255, 0, 255),
	                 convertStringFromWString(charFromUtf8()).substr(0, 25).c_str(), false);
}
