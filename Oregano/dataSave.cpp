#include "dataSave.h"
#include "mapDraw.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(Player& player)
	: player(player), currentStatus(16), currentCoin(1078) {
	statusData = "resource\\Data\\statusData.bin";
	coinData = "resource\\Data\\coinData.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// �t�@�C���T�C�Y���擾
/// </summary>
/// <param name="fName">�t�@�C���̖��O</param>
int DataSave::getFileSize(string fileName) {
	ifstream fileRoad(fileName, ifstream::ate);
	size_t fileSize = static_cast<size_t>(fileRoad.tellg());
	return fileSize;
}

/// <summary>
/// �o�C�i���t�@�C���̏�������
/// </summary>
void DataSave::writeBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	lastTimeData.clear(); //�O��܂ł̃f�[�^�̃N���A

	for (auto& i : currentData)
		lastTimeData.push_back(i); //�X�e�[�^�X�����ԂɊi�[

	int sizeOut = lastTimeData.size(); //�x�N�^�[�z��̃T�C�Y�����i�[

	/* �o�C�i���t�@�C���������� */
	ofstream fileWrite(fileName, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&lastTimeData[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //����
}

/// <summary>
/// �o�C�i���t�@�C���̓ǂݍ���
/// </summary>
void DataSave::roadBinaryFile(vector<int>& currentData, vector<int>& lastTimeData, string fileName) {
	/* �o�C�i���t�@�C���ǂݍ��� */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName));
	if (!fileRead.read(&binChar[0], getFileSize(fileName))) return;
	fileRead.close(); //����

	/* 16�i����10�i���ɕϊ����A�o�͔z��Ɋi�[ */
	for (unsigned int i = 0; i < currentData.size(); ++i)
		lastTimeData.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
}

/// <summary>
/// ���݂܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getCurrentStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		currentStatus[i] = player.status[i];
	currentStatus[CURRENT_MAP_X] = MapDraw::mapX; //���݂̃}�b�vx���W����
	currentStatus[CURRENT_MAP_Y] = MapDraw::mapY; //���݂̃}�b�vy���W����
}

/// <summary>
/// �O��܂ł̃v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getLastTimeStatus() {
	for (unsigned int i = 0; i <= PRIORITY; ++i)
		player.status[i] = lastTimeStatus[i];
	MapDraw::mapX = lastTimeStatus[CURRENT_MAP_X]; //�O��܂ł̃}�b�vx���W����
	MapDraw::mapY = lastTimeStatus[CURRENT_MAP_Y]; //�O��܂ł̃}�b�vy���W����
}

void DataSave::getCurrentCoin() {

}

void DataSave::getLastTimeCoin() {
	//for (unsigned int i = 0; i < currentCoin.size(); ++i)
	//	currentCoin[i] = lastTimeCoin[i]; //�O��܂ł̃R�C���󋵂��擾
}

/// <summary>
/// �Z�[�u�f�[�^�̏�������
/// </summary>
void DataSave::writeSaveData() {
	getCurrentStatus(); //���݂܂ł̃X�e�[�^�X���擾
	writeBinaryFile(currentStatus, lastTimeStatus, statusData); //�o�C�i���t�@�C���̏�������

	writeBinaryFile(currentCoin, lastTimeCoin, coinData);
}

/// <summary>
/// �Z�[�u�f�[�^�̓ǂݍ���
/// </summary>
void DataSave::roadSaveData() {
	roadBinaryFile(currentStatus, lastTimeStatus, statusData); //�o�C�i���t�@�C���̓ǂݍ���
	getLastTimeStatus(); //�O��܂ł̃X�e�[�^�X���擾

	roadBinaryFile(currentCoin, lastTimeCoin, coinData);
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	DrawFormatString(0, 500, GetColor(0, 0, 0), "RANK:%d, COIN:%d",
	                 player.status[TREASURE_RANK], player.status[COIN], false);

	DrawFormatString(0, 515, GetColor(0, 0, 0), "mx:%d, my:%d, cx:%d, cy:%d, dir:%d, type:%d, rank:%d, TofF:%d",
	                 lastTimeCoin[0], lastTimeCoin[1], lastTimeCoin[2], lastTimeCoin[3],
	                 lastTimeCoin[4], lastTimeCoin[5], lastTimeCoin[6], lastTimeCoin[7], false);
}
