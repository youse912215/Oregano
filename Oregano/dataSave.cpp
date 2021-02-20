#include "dataSave.h"
#include "mapDraw.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(EventBase& event, Player& player) : position(event), player(player), statusData(15) {
	saveDataFile = "resource\\Data\\saveData1.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// �t�@�C���T�C�Y���擾
/// </summary>
/// <param name="fName">�t�@�C���̖��O</param>
int DataSave::getFileSize(string fName) {
	ifstream fileRoad(fName, ifstream::ate);
	size_t fileSize = static_cast<size_t>(fileRoad.tellg());
	return fileSize;
}

/// <summary>
/// �o�C�i���t�@�C���̏�������
/// </summary>
void DataSave::writeBinaryFile() {
	lastTimeData.clear(); //�o�͔z��̃N���A

	for (auto& i : statusData)
		lastTimeData.push_back(i); //�X�e�[�^�X�����ԂɊi�[

	int sizeOut = lastTimeData.size(); //�x�N�^�[�z��̃T�C�Y�����i�[

	/* �o�C�i���t�@�C���������� */
	ofstream fileWrite(saveDataFile, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&lastTimeData[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //����
}

/// <summary>
/// �o�C�i���t�@�C���̓ǂݍ���
/// </summary>
void DataSave::roadBinaryFile() {
	/* �o�C�i���t�@�C���ǂݍ��� */
	ifstream fileRead(saveDataFile, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(saveDataFile));
	if (!fileRead.read(&binChar[0], getFileSize(saveDataFile))) return;
	fileRead.close(); //����

	/* 16�i����10�i���ɕϊ����A�o�͔z��Ɋi�[ */
	for (unsigned int i = 0; i < statusData.size(); ++i)
		lastTimeData.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
}

/// <summary>
/// ���݂܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getCurrentStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		statusData[i] = player.status[i];
	statusData[CURRENT_MAP_X] = MapDraw::mapX; //���݂̃}�b�vx���W����
	statusData[CURRENT_MAP_Y] = MapDraw::mapY; //���݂̃}�b�vy���W����
}

/// <summary>
/// �O��܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		player.status[i] = lastTimeData[i];
	MapDraw::mapX = lastTimeData[CURRENT_MAP_X]; //�O��܂ł̃}�b�vx���W����
	MapDraw::mapY = lastTimeData[CURRENT_MAP_Y]; //�O��܂ł̃}�b�vy���W����
}

/// <summary>
/// �Z�[�u�f�[�^�̏�������
/// </summary>
void DataSave::writeSaveData() {
	getCurrentStatus(); //���݂܂ł̃X�e�[�^�X���擾
	writeBinaryFile(); //�o�C�i���t�@�C���̏�������
}

/// <summary>
/// �Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::roadSaveData() {
	roadBinaryFile(); //�o�C�i���t�@�C���̓ǂݍ���
	getLastTimeStatus(); //�O��܂ł̃X�e�[�^�X���擾
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(0, 0, 0), "%d, %d",
	                 lastTimeData[CURRENT_MAP_X], lastTimeData[CURRENT_MAP_Y], false);
}
