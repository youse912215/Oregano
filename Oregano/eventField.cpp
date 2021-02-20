#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event, Player& player)
	: input(input), event(event), player(player), coinFlag(250),
	  coinQuantity{5, 10, 50, 100}, coin(COIN_INFORMATION_QUANTITY) {
	eventFlag = false;
}

EventField::~EventField() {
}

/// <summary>
/// X�{�^�����������Ƃ��A�t�B�[���h��̎w��̏ꏊ�ŃA�C�e�������\�ɂ���
/// </summary>
void EventField::getFieldItem() {
	if (input.X) {
		for (unsigned int i = 0; i < coin.size() / INFORMATION_SIZE; ++i) {
			if (!( //�C�x���g�����ꏊ�̕����������Ă���Ƃ�
				input.moveDirection == directionReverse(coin[(i * INFORMATION_SIZE) + DIRECTION_])
				//�R�C���t���O��false�̂Ƃ�
				&& !coinFlag[coin[(i * INFORMATION_SIZE) + EVENT_NO_]]
				//�C�x���g�����ꏊ�̎��ӂɂ���Ƃ�
				&& event.getEventCoordinate(
					coin[(i * INFORMATION_SIZE) + MAP_X_],
					coin[(i * INFORMATION_SIZE) + MAP_Y_],
					coin[(i * INFORMATION_SIZE) + CURRENT_X_]
					+ directionSignX(coin[(i * INFORMATION_SIZE) + DIRECTION_]),
					coin[(i * INFORMATION_SIZE) + CURRENT_Y_]
					+ directionSignY(coin[(i * INFORMATION_SIZE) + DIRECTION_]))))
				continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
			{
				player.status[coinTypeDecision(coin[(i * INFORMATION_SIZE) + ITEM_TYPE_])]
					+= coinQuantityDecision(coin[(i * INFORMATION_SIZE) + ITEM_TYPE_]); //�R�C���̓���i��ޕʂɒǉ��j
				coinFlag[coin[(i * INFORMATION_SIZE) + EVENT_NO_]] = true; //���肵���ꏊ�̃R�C���C�x���g���ςݏ��(true)�ɂ���
			}
		}
		eventFlag = true; //�{�^���������Ă���Ƃ��̓C�x���g�t���O��true
	}
	else eventFlag = false; //�{�^���������Ă��Ȃ��Ƃ��̓C�x���g�t���O��false
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
	if (coinType >= 0 && coinType <= 3) return GREEN_COIN;
	if (coinType >= 4 && coinType <= 7) return YELLOW_COIN;
	if (coinType >= 8 && coinType <= 11) return PURPLE_COIN;
	if (coinType >= 12 && coinType <= 15) return WHITE_COIN;
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
	getFieldItem();
	DrawFormatString(300, 0, GetColor(130, 130, 255), "�C�x���g:%d, ����:%d, T%d",
	                 this->eventFlag, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
}
