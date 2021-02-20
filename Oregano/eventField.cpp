#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event, Player& player)
	: input(input), event(event), player(player), coinFlag(250),
	  coinQuantity{5, 10, 50, 100}, coin(COIN_INFORMATION_SIZE), item(ITEM_INFORMATION_SIZE) {
	actionFlagX = false;
}

EventField::~EventField() {
}

/// <summary>
/// X�{�^�����������Ƃ��A�t�B�[���h��̎w��̏ꏊ�ŃA�C�e����R�C���Ȃǂ����\�ɂ���
/// </summary>
void EventField::getFieldItem(vector<int>& eventName, vector<bool>& eventFlag) {
	for (unsigned int i = 0; i < eventName.size() / EVENT_INFORMATION_SIZE; ++i) {
		if (!( //�C�x���g�����ꏊ�̕����������Ă���Ƃ�
			input.moveDirection == directionReverse(eventName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_])
			//�C�x���g�t���O��false�̂Ƃ�
			&& !eventFlag[eventName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]]
			//�C�x���g�����ꏊ�̎��ӂɂ���Ƃ�
			&& event.getEventCoordinate(
				eventName[(i * EVENT_INFORMATION_SIZE) + MAP_X_],
				eventName[(i * EVENT_INFORMATION_SIZE) + MAP_Y_],
				eventName[(i * EVENT_INFORMATION_SIZE) + CURRENT_X_]
				+ directionSignX(eventName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]),
				eventName[(i * EVENT_INFORMATION_SIZE) + CURRENT_Y_]
				+ directionSignY(eventName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]))))
			continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		{
			eventFlag[eventName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]] = true; //���肵���ꏊ�̃C�x���g���ςݏ��(true)�ɂ���

			if (eventName != coin) continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
			player.status[coinTypeDecision(eventName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_])]
				+= coinQuantityDecision(eventName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_]); //�R�C���̓���i��ޕʂɒǉ��j
		}
	}
}

/// <summary>
/// �t�B�[���h�A�N�V����
/// </summary>
void EventField::fieldAction() {
	if (input.X) {
		getFieldItem(coin, coinFlag); //�R�C�������

		actionFlagX = true; //�{�^���������Ă���Ƃ��̓A�N�V�����t���O��true
	}
	else actionFlagX = false; //�{�^���������Ă��Ȃ��Ƃ��̓A�N�V�����t���O��false
}

/// <summary>
/// x�����ɂ���āA-1��1��Ԃ�
/// </summary>
/// <param name="direction">�C�x���g�����ꏊ�Ɨאڂ��Ă������</param>
int EventField::directionSignX(const int& direction) {
	if (direction == LEFT) return -1;
	if (direction == RIGHT) return 1;
	return 0;
}

/// <summary>
///	y�����ɂ���āA-1��1��Ԃ�
/// </summary>
/// <param name="direction">�C�x���g�����ꏊ�Ɨאڂ��Ă������</param>
int EventField::directionSignY(const int& direction) {
	if (direction == UP) return -1;
	if (direction == DOWN) return 1;
	return 0;
}

/// <summary>
/// �R�C���̎�ނɂ���āA�K�؂ȗʂ�Ԃ�
/// </summary>
/// <param name="coinTypeDecision">�R�C���̎��</param>
int EventField::coinQuantityDecision(const int& coinType) {
	return coinQuantity[coinType];
}

/// <summary>
/// �R�C���̎�ނɂ���āA�K�؂ȐF�̃R�C������Ԃ�
/// </summary>
/// <param name="coinTypeDecision">�R�C���̎��</param>
int EventField::coinTypeDecision(const int& coinType) {
	if (coinType >= 0 && coinType <= 3) return GREEN_COIN; //�ԖG�K�̃R�C��
	if (coinType >= 4 && coinType <= 7) return YELLOW_COIN; //�������̃R�C��
	if (coinType >= 8 && coinType <= 11) return PURPLE_COIN; //�������̃R�C��
	if (coinType >= 12 && coinType <= 15) return WHITE_COIN; //���S���̃R�C��
	return 0;
}

/// <summary>
/// �����𔽓]������
/// </summary>
/// <param name="direction"></param>
int EventField::directionReverse(const int& direction) {
	if (direction == LEFT) return RIGHT;
	if (direction == RIGHT) return LEFT;
	if (direction == UP) return DOWN;
	if (direction == DOWN) return UP;
	return 0;
}

/// <summary>
/// �X�V����
/// </summary>
void EventField::update() {
	fieldAction();
	DrawFormatString(300, 0, GetColor(130, 130, 255), "�C�x���g:%d, ����:%d, T%d",
	                 this->actionFlagX, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
}
