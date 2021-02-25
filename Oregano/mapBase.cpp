#include "mapBase.h"
#include "constant.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//������
MapBase::MapBase() :
	mapBase(AREA_HEIGHT, vector<int>(AREA_WIDTH)) {
	initialCsv = "resource/csv/map_x08y08.csv"; //�����n�_�̃}�b�v(����)
}

MapBase::~MapBase() {
}

/// <summary>
/// ���݂̍��W���m�F���A����ɉ�����csv�t�@�C����T��
/// </summary>
/// <param name="cx">���݂̑S�̃}�b�v��x���W</param>
/// <param name="cy">���݂̑S�̃}�b�v��y���W</param>
/// <param name="csv">csv�t�@�C����</param>
/// <returns>������ύX����csv�t�@�C������Ԃ�</returns>
string MapBase::mapConfirmation(const int& cx, const int& cy, string& csv) {
	//if (csv == nullptr) { return; } //null�`�F�b�N
	csv.replace(18, 2, csvNum[cx]); //�t�@�C������x���W��ύX
	csv.replace(21, 2, csvNum[cy]); //�t�@�C������y���W��ύX
	return csv; //csv�t�@�C������Ԃ�
}

/// <summary>
/// �}�b�v�f�[�^�̃t�@�C���ǂݍ���
/// </summary>
void MapBase::fileImport(const int& nx, const int& ny, vector<vector<int>>& map) {

	ifstream file(mapConfirmation(nx, ny, initialCsv));
	string line;
	int j = 0;
	while (getline(file, line)) {
		int i = 0;
		// �J���}����؂蕶���Ƃ��Đ؂蕪���Aint�ɕϊ�����data[][]�Ɋi�[����
		for (string::size_type spos, epos = 0;
		     (spos = line.find_first_not_of(comma, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(comma, spos)) - spos);
			map[j][i++] = stoi(token);
		}
		++j; //���Z
	}
}
