#include "dataSave.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "DxLib.h"

DataSave::DataSave(EventBase& event, Player& player) : position(event), player(player), statusData(14) {
	fileName = "resource\\Data\\saveData1.bin";
}

DataSave::~DataSave() {
}

/// <summary>
/// �o�C�i���t�@�C���̏�������
/// </summary>
void DataSave::writeBinaryFile() {
	getCurrentStatus(); //�X�e�[�^�X���擾

	vecOut.clear(); //�o�͔z��̃N���A

	for (auto& i : statusData)
		vecOut.push_back(i); //�X�e�[�^�X�����ԂɊi�[

	int sizeOut = vecOut.size(); //�x�N�^�[�z��̃T�C�Y�����i�[

	/* �o�C�i���t�@�C���������� */
	ofstream fileWrite(fileName, ios::binary);
	if (!fileWrite) return;

	fileWrite.write(reinterpret_cast<char*>(&vecOut[0]),
	                static_cast<std::streamsize>(sizeof(int)) * sizeOut);
	fileWrite.close(); //����
}

/// <summary>
/// �o�C�i���t�@�C���ǂݍ���
/// </summary>
void DataSave::roadBinaryFile() {
	/* �o�C�i���t�@�C���ǂݍ��� */
	ifstream fileRead(fileName, ios::binary);
	if (!fileRead) return;

	vector<char> binChar(getFileSize(fileName));
	if (!fileRead.read(&binChar[0], getFileSize(fileName))) return;
	fileRead.close(); //����

	/* 16�i����10�i���ɕϊ����A�o�͔z��Ɋi�[ */
	for (unsigned int i = 0; i < statusData.size(); ++i)
		vecOut.push_back((binChar[i * 4] & 0xff)
			+ static_cast<int>((binChar[i * 4 + 1] & 0xff) * pow(16, 2)));
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
/// �v���C���[�̃X�e�[�^�X���擾
/// </summary>
void DataSave::getCurrentStatus() {
	statusData[LIFE] = player.status[LIFE]; //������
	statusData[ATTACK] = player.status[ATTACK]; //�U����
	statusData[DEFENSE] = player.status[DEFENSE]; //�����
	statusData[DEADLY_POISON_RESISTANCE] = player.status[DEADLY_POISON_RESISTANCE]; //�ғőϐ�
	statusData[DEADLY_POISON_VALUE] = player.status[DEADLY_POISON_VALUE]; //�ғő����l
	statusData[PARALYSIS_RESISTANCE] = player.status[PARALYSIS_RESISTANCE]; //��ბϐ�
	statusData[PARALYSIS_VALUE] = player.status[PARALYSIS_VALUE]; //��ბ����l
	statusData[HYPNOSIS_RESISTANCE] = player.status[HYPNOSIS_RESISTANCE]; //�Ö��ϐ�
	statusData[HYPNOSIS_VALUE] = player.status[HYPNOSIS_VALUE]; //�Ö������l
	statusData[PRIORITY] = player.status[PRIORITY]; //�D��x
	statusData[CURRENT_MAP_X] = position.currentMapPosition(MAP_X); //���݂̃}�b�vx���W
	statusData[CURRENT_MAP_Y] = position.currentMapPosition(MAP_Y); //���݂̃}�b�vy���W
	statusData[CENTRAL_POSITION_X] = position.centralPlayerPosition(MAP_X); //�v���C���[�̒���x���W
	statusData[CENTRAL_POSITION_Y] = position.centralPlayerPosition(MAP_Y); //�v���C���[�̒���y���W
}

/// <summary>
/// �X�V����
/// </summary>
void DataSave::update() {
	roadBinaryFile(); //�o�C�i���t�@�C���ǂݍ���

	DrawFormatString(0, 500, GetColor(0, 0, 0), "%d, %d, %d, %d",
	                 vecOut[CURRENT_MAP_X], vecOut[CURRENT_MAP_Y],
	                 vecOut[CENTRAL_POSITION_X], vecOut[CENTRAL_POSITION_Y],
	                 false);
}
