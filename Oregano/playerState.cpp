#include "playerState.h"
#include "eventBase.h"
#include "moveProcess.h"

MoveProcess move_;

PlayerState::PlayerState() : poisonTime(0), roughTime(0), attributeMax(100), timeMax(100), cooldownMax(120),
                             poisonDamage(50), roughDamage(100),
                             eliminateCoin(300),
                             stateAbnormal{false, false, false, false}, attributeAccumulation{0, 0, 0, 0},
                             coin{100, 100, 100, 100},
                             battleStyle(0) {
}

/// <summary>
/// ��Ԉُ���擾
/// </summary>
void PlayerState::getStateAbnormal() {
	for (unsigned int i = 0; i != stateAbnormal.size(); ++i) {
		if (attributeAccumulation[i] < attributeMax) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		stateAbnormal[i] = true; //��Ԉُ��true
	}
}

/// <summary>
/// ����ł̏�Ԃ��擾
/// </summary>
/// <param name="draw_">�}�b�v�̕`��N���X</param>
void PlayerState::getFloorState(MapDraw& draw_) {
	if (move_.mapCondition(draw_, POISON)) {
		stateAbnormal[DEADLY_POISON] = true; //�ғŏ�Ԃ�t�^
	}
	else if (move_.mapCondition(draw_, ROUGH)) {
		//0����100�܂Ŏ��Ԃ𓮂���
		roughTime = roughTime <= timeMax ? ++roughTime : 0; //�ʉ����Ԃ��J�E���g
	}
	else roughTime = 0; //�ʉ����Ԃ����Z�b�g
}

/// <summary>
/// �ғŏ�Ԃ��J�E���g
/// </summary>
void PlayerState::countStateTime() {
	if (stateAbnormal[DEADLY_POISON])
		poisonTime++; //�ғŏ�ԂȂ玞�Ԃ��J�E���g
	else if (poisonTime >= timeMax || !stateAbnormal[DEADLY_POISON])
		poisonTime = 0; //�ő厞�Ԃ܂��͖ғŏ�Ԃ��������ꂽ��A���Ԃ����Z�b�g
}

/// <summary>
/// �p���_���[�W��t�^
/// </summary>
/// <param name="time">����</param>
/// <param name="value">�_���[�W��</param>
void PlayerState::continuousDamage(const int& time, const int& value) {
	//time��timeMax�̂Ƃ�
	if (time % timeMax == 0 && time != 0)
		coin[battleStyle] -= value; //value���R�C�������炷
}

/// <summary>
/// ��Ԉُ�X�V����
/// </summary>
/// <param name="draw_"></param>
void PlayerState::stateAbnormalUpdate(MapDraw& draw_) {
	getStateAbnormal(); //��Ԉُ���擾
	getFloorState(draw_); //�ғŏ�Ԃ��擾
	countStateTime(); //�ғŎ��Ԃ��J�E���g
	continuousDamage(poisonTime, poisonDamage); //�ғŃ_���[�W��t�^
	continuousDamage(roughTime, roughDamage); //�ʉ��_���[�W��t�^
}

/// <summary>
/// �퓬�X�^�C����؂�ւ���
/// </summary>
void PlayerState::changeBattleStyle(const int& dir) {
	//L�{�^�����͂��A�퓬�X�^�C�����ԖG�K(�ΖғŃX�^�C��)�ł͂Ȃ��Ƃ�
	if (dir == LEFT && battleStyle != DEADLY_POISON)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle - 1] != 0 ? --battleStyle : battleStyle; //�O�̃X�^�C���ɐ؂�ւ�

		//R�{�^�����͂��A�퓬�X�^�C�������g��(�Ώo���X�^�C��)�ł͂Ȃ��Ƃ�
	else if (dir == RIGHT && battleStyle != BLOODING)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle + 1] != 0 ? ++battleStyle : battleStyle; //���̃X�^�C���ɐ؂�ւ�
}

/// <summary>
/// �퓬�X�^�C���̐�����Ԃ��X�V
/// </summary>
void PlayerState::switchStyleAutomatically() {
	if (coin[battleStyle] <= 0) {
		//�S�ẴR�C���̒���0�ȏ�̗v�f��T���A���������ŏ��̗v�f�̃C�e���[�^�[��Ԃ�
		auto itr = find_if(coin.begin(), coin.end(),
		                   [](int x) { return x > 0; });
		//0�ȊO�̗v�f��������΁A���̗v�f��battleStyle�ɑ��
		if (itr != coin.end())
			battleStyle = distance(coin.begin(), itr); //�퓬�X�^�C����؂�ւ���
		else
			EventBase::gameScene = END_SCENE; //�S�ẴR�C����0�ɂȂ�A�Q�[���I�[�o�[�V�[����
	}
}

/// <summary>
/// �����~�ϒl�̌v�Z
/// </summary>
/// <param name="attribute">�G�̑���</param>
/// <param name="attributeValue">�G�̑����l</param>
void PlayerState::calculateValue(const int& attribute, const int& attributeValue) {
	//���݂̐퓬�X�^�C���ƓG�̑������قȂ�Ƃ�
	if (battleStyle != attribute) {
		if (attributeAccumulation[attribute] < attributeMax)
			attributeAccumulation[attribute] += attributeValue; //�����~�ϒl�����Z
		else if (attributeAccumulation[attribute] >= attributeMax)
			attributeAccumulation[attribute] = attributeMax; //100�ȏ�͑����~�ϒl���ő�l�ɂ���
	}
}

/// <summary>
/// �����ϐ��l�����Z�b�g�Ə�Ԉُ������
/// </summary>
/// <param name="elimination">�����t���O</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
/// <param name="coin">�v���C���[�R�C��</param>
void PlayerState::valueReset(bool& elimination, vector<bool>& cooldownFlag) {
	//���݂̐퓬�X�^�C���̏�Ԉُ킪true���A�����t���O��true�̂Ƃ�
	if (elimination) {
		if (stateAbnormal[battleStyle] && coin[battleStyle] >= eliminateCoin) {
			attributeAccumulation[battleStyle] = 0; //�����ϐ��l�����Z�b�g
			stateAbnormal[battleStyle] = false; //��Ԉُ������
			cooldownFlag[ELIMINATION] = true; //�N�[���_�E���t���O��true
			coin[battleStyle] -= eliminateCoin;
		}
		elimination = false; //�����t���O��false
	}
}

/// <summary>
/// ��Ԃ̃N�[���_�E������
/// </summary>
/// <param name="cooldown">�N�[���_�E��</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
void PlayerState::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[ELIMINATION]) cooldown[ELIMINATION]++; //�N�[���_�E���J�n

	//�N�[���_�E����cooldownMax�b
	if (cooldown[ELIMINATION] >= cooldownMax) {
		cooldown[ELIMINATION] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[ELIMINATION] = false; //�N�[���_�E���t���O��false
	}
}
