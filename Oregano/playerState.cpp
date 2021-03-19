#include "playerState.h"
#include "moveProcess.h"
#include "sceneLoad.h"

MoveProcess move_;

vector<bool> PlayerState::condition = {false, false, false, false}; //��Ԉُ�
vector<int> PlayerState::coin = {10, 10, 10, 10}; //�R�C��
vector<int> PlayerState::attributeAccumulation = {0, 0, 0, 0}; //�����ϋv�l
int PlayerState::battleStyle = 0; //�퓬�X�^�C��

PlayerState::PlayerState() :
	/* �����l */
	poisonTime(0), roughTime(0), crampsTime(0),

	/* �Œ�l */
	damageTimeMax(100), crampsTimeMax(60), cooldownMax(120),
	attributeMax(10), poisonDamage(1), roughDamage(2), recoveryCoin(10),

	/* �_���[�W�t���O */
	poisonDamageFlag(false), roughDamageFlag(false) {
}

/// <summary>
/// ��Ԉُ���擾
/// </summary>
void PlayerState::getCondition() {
	for (unsigned int i = 0; i != condition.size(); ++i) {
		if (attributeAccumulation[i] < attributeMax) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		condition[i] = true; //��Ԉُ��true
	}
}

/// <summary>
/// ����ł̏�Ԃ��擾
/// </summary>
/// <param name="draw_">�}�b�v�̕`��N���X</param>
void PlayerState::getFloorState(MapDraw& draw_) {
	//�ŏ��̏�ɂ���Ƃ����A�퓬�X�^�C�����ԖG�K(�Ζғ�)�ȊO�̂Ƃ�
	if (move_.mapCondition(draw_, POISON) && battleStyle != DEADLY_POISON) {
		condition[DEADLY_POISON] = true; //�ғŏ�Ԃ�t�^
	}
		//�ʉ����̏�ɂ���Ƃ����A�퓬�X�^�C�������q��(�΍���)�ȊO�̂Ƃ�
	else if (move_.mapCondition(draw_, ROUGH) && battleStyle != CONFUSION) {
		//0����100�܂Ŏ��Ԃ𓮂���
		roughTime = roughTime <= damageTimeMax ? ++roughTime : 0; //�ʉ����Ԃ��J�E���g
	}
	else roughTime = 0; //�ʉ����Ԃ����Z�b�g
}

/// <summary>
/// �ғŏ�Ԃ��J�E���g
/// </summary>
void PlayerState::countStateTime() {
	if (condition[DEADLY_POISON])
		poisonTime++; //�ғŏ�ԂȂ玞�Ԃ��J�E���g
	else if (poisonTime >= damageTimeMax || !condition[DEADLY_POISON])
		poisonTime = 0; //�ő厞�Ԃ܂��͖ғŏ�Ԃ��������ꂽ��A���Ԃ����Z�b�g
}

/// <summary>
/// �p���_���[�W��t�^
/// </summary>
/// <param name="time">����</param>
/// <param name="value">�_���[�W��</param>
void PlayerState::continuousDamage(const int& time, const int& value, DataSource& source) {
	//time��timeMax�̂Ƃ�
	if (time % damageTimeMax == 0 && time != 0) {
		coin[battleStyle] -= value; //value���R�C�������炷
		source.playSe(source.seDamage); //�_���[�WSE

		if (time == poisonTime) poisonDamageFlag = true; //�ғŃ_���[�W�t���O��true
		else roughDamageFlag = true; //�ʉ��_���[�W�t���O��true
	}
}

/// <summary>
/// ��Ԉُ�X�V����
/// </summary>
/// <param name="draw_"></param>
void PlayerState::conditionUpdate(MapDraw& draw_, DataSource& source) {
	getCondition(); //��Ԉُ���擾
	getFloorState(draw_); //�ғŏ�Ԃ��擾
	countStateTime(); //�ғŎ��Ԃ��J�E���g
	continuousDamage(poisonTime, poisonDamage, source); //�ғŃ_���[�W��t�^
	continuousDamage(roughTime, roughDamage, source); //�ʉ��_���[�W��t�^
	resetCoin(); //�R�C����0�Ƀ��Z�b�g
	countCrampsTime(); //�z�����Ԃ��J�E���g
}

/// <summary>
/// �R�C����0�Ƀ��Z�b�g
/// </summary>
void PlayerState::resetCoin() {
	//���݂̐퓬�X�^�C���̃R�C����0�ɂȂ�����A0�ɂ���
	if (coin[battleStyle] < 0)
		coin[battleStyle] = 0; //0�ɂ���
}

/// <summary>
/// �z�����Ԃ��J�E���g
/// </summary>
void PlayerState::countCrampsTime() {
	//�z����Ԃ̂Ƃ�
	if (condition[CRAMPS]) {
		crampsTime = crampsTime++; //�z�����Ԃ��J�E���g
	}

	if (crampsTime >= crampsTimeMax) {
		condition[CRAMPS] = false; //��ԉ���
		attributeAccumulation[CRAMPS] = 0; //�ϋv�l���Z�b�g
		crampsTime = 0; //���Ԃ����Z�b�g
	}
}

/// <summary>
/// ��Ԉُ�ɂ��ǉ��_���[�W
/// </summary>
int PlayerState::addConditionDamage() {
	//�o����ԈȊO�̂Ƃ�
	if (!condition[BLOODING])
		return 1; //�ǉ��_���[�W�Ȃ�
	return 3; //�_���[�W3�{�Ƃ��ĕԂ�
}

/// <summary>
/// �����ꂩ�̏�Ԉُ��Ԃ�
/// </summary>
bool PlayerState::anyCondition() {
	if (condition[DEADLY_POISON] || condition[CRAMPS]
		|| condition[CONFUSION] || condition[BLOODING]) {
		return true;
	}
	return false;
}

/// <summary>
/// �_���[�W�t���O�����Z�b�g
/// </summary>
void PlayerState::resetDamageFlag() {
	poisonDamageFlag = false; //�ғŃ_���[�W�t���O��false
	roughDamageFlag = false; //�ʉ��_���[�W�t���O��false
}

/// <summary>
/// �퓬�X�^�C����؂�ւ���
/// </summary>
void PlayerState::changeBattleStyle(const int& dir) {
	//L�{�^�����͂��A�퓬�X�^�C�����ԖG�K(�Ζғ�)�ł͂Ȃ��Ƃ�
	if (dir == LEFT && battleStyle != DEADLY_POISON) {
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ��A�O�̃X�^�C���ɐ؂�ւ�
		if (coin[battleStyle - 1] != 0)
			battleStyle--;
			//�[�x�q(���z��)�̃R�C����0�ł͂Ȃ��Ƃ�
		else if (battleStyle == BLOODING && coin[CRAMPS] != 0)
			battleStyle = CRAMPS;
			//�ԖG�K(�Ζғ�)�̃R�C����0�ł͂Ȃ��Ƃ�
		else if ((battleStyle == CONFUSION || battleStyle == BLOODING) && coin[DEADLY_POISON] != 0)
			battleStyle = DEADLY_POISON;
	}

		//R�{�^�����͂��A�퓬�X�^�C�������g��(�Ώo��)�ł͂Ȃ��Ƃ�
	else if (dir == RIGHT && battleStyle != BLOODING) {
		//���̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ��A���̃X�^�C���ɐ؂�ւ�
		if (coin[battleStyle + 1] != 0)
			battleStyle++;
			//���q��(�΍���)�̃R�C����0�ł͂Ȃ��Ƃ�
		else if (battleStyle == DEADLY_POISON && coin[CONFUSION] != 0)
			battleStyle = CONFUSION;
			//���g��(�Ώo��)�̃R�C����0�ł͂Ȃ��Ƃ�
		else if ((battleStyle == DEADLY_POISON || battleStyle == CRAMPS) && coin[BLOODING] != 0)
			battleStyle = BLOODING;
	}
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
			SceneLoad::gameScene = GAME_OVER_SCENE; //�S�ẴR�C����0�ɂȂ�A�Q�[���I�[�o�[�V�[����
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
			attributeAccumulation[attribute] = attributeMax; //attributeMax�ȏ�͑����~�ϒl���ő�l�ɂ���
	}
}

/// <summary>
/// �����ϐ��l�����Z�b�g�Ə�Ԉُ������
/// </summary>
/// <param name="actionFlag">�A�N�V�����t���O</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
void PlayerState::valueReset(vector<bool>& actionFlag, vector<bool>& cooldownFlag) {
	//���݂̐퓬�X�^�C���̏�Ԉُ킪true���A�����t���O��true�̂Ƃ�
	if (actionFlag[RECOVERY]) {
		if (condition[battleStyle] && coin[battleStyle] >= recoveryCoin) {
			attributeAccumulation[battleStyle] = 0; //�����ϐ��l�����Z�b�g
			condition[battleStyle] = false; //��Ԉُ������
			cooldownFlag[RECOVERY] = true; //�N�[���_�E���t���O��true
			coin[battleStyle] -= recoveryCoin; //�R�C���x����
		}
		actionFlag[RECOVERY] = false; //�����t���O��false
	}
}

/// <summary>
/// ��Ԃ̃N�[���_�E������
/// </summary>
/// <param name="cooldown">�N�[���_�E��</param>
/// <param name="cooldownFlag">�N�[���_�E���t���O</param>
void PlayerState::countCooldown(vector<int>& cooldown, vector<bool>& cooldownFlag) {
	if (cooldownFlag[RECOVERY]) cooldown[RECOVERY]++; //�N�[���_�E���J�n

	//�N�[���_�E����cooldownMax�b
	if (cooldown[RECOVERY] >= cooldownMax) {
		cooldown[RECOVERY] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[RECOVERY] = false; //�N�[���_�E���t���O��false
	}
}
