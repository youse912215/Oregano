#include "playerState.h"

#include "eventBase.h"

PlayerState::PlayerState() :
	stateAbnormal(4), attributeAccumulation{0, 0, 0, 0} {
	battleStyle = 0;
}

/// <summary>
/// �퓬�X�^�C����؂�ւ���
/// </summary>
void PlayerState::changeBattleStyle(std::vector<int>& coin, const int& dir) {
	//L�{�^�����͂��A�퓬�X�^�C�����ԖG�K�ł͂Ȃ��Ƃ�
	if (dir == LEFT && battleStyle != 0)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle - 1] != 0 ? --battleStyle : battleStyle; //�O�̃X�^�C���ɐ؂�ւ�

		//R�{�^�����͂��A�퓬�X�^�C�������g�Ԃł͂Ȃ��Ƃ�
	else if (dir == RIGHT && battleStyle != 3)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle + 1] != 0 ? ++battleStyle : battleStyle; //���̃X�^�C���ɐ؂�ւ�

}

/// <summary>
/// �퓬�X�^�C���̐�����Ԃ��X�V
/// </summary>
void PlayerState::switchStyleAutomatically(std::vector<int>& coin) {
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
		if (attributeAccumulation[attribute] < 100)
			attributeAccumulation[attribute] += attributeValue; //�����~�ϒl�����Z
		else if (attributeAccumulation[attribute] >= 100)
			attributeAccumulation[attribute] = 100; //100�ȏ�͑����~�ϒl���ő�l�ɂ���
	}
}

/// <summary>
/// ��Ԉُ���擾
/// </summary>
void PlayerState::getStateAbnormal() {
	for (unsigned int i = 0; i != stateAbnormal.size(); ++i) {
		if (attributeAccumulation[i] < 100) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		stateAbnormal[i] = true; //��Ԉُ��true
	}
}
