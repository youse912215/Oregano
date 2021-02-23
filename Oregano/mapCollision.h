#pragma once
#include "mapDraw.h"
#include <vector>

using namespace std;

class MapCollision {
private:
	MapDraw& map; //�}�b�v�`��N���X����

	/* 4�����̏Փ˃t���O */
	bool leftUpCollisionFlag();
	bool rightUpCollisionFlag();
	bool leftDownCollisionFlag();
	bool rightDownCollisionFlag();

	/* �e�������Ƃ̏Փ˔��� */
	void collisionDetectionLeftUp();
	void collisionDetectionRightUp();
	void collisionDetectionLeftDown();
	void collisionDetectionRightDown();
	void collisionDetectionCenterLeft1();
	void collisionDetectionCenterLeft2();
	void collisionDetectionCenterRight1();
	void collisionDetectionCenterRight2();
	void collisionDetectionCenterUp1();
	void collisionDetectionCenterUp2();
	void collisionDetectionCenterDown1();
	void collisionDetectionCenterDown2();

	bool collisionDetection(const int& dirXY, const int& dirX, const int& dirY);

	vector<bool> collisionFlag; //�Փ˃t���O
	vector<bool> boundaryCriteria; //�e�����̋��E����

public:
	MapCollision(MapDraw& map);
	~MapCollision();

	void update(); //�X�V����

	bool leftCollisionFlag();
	bool rightCollisionFlag();
	bool upCollisionFlag();
	bool downCollisionFlag();
};
