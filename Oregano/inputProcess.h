#pragma once

class Input {
public:
	static char keys[256]; //�ŐV�̃L�[�{�[�h���p
	static char oldkeys[256]; //1���[�v(�t���[��)�O�̃L�[�{�[�h���
	static void input_info();
	void moving_process(const int& collisionLeftUp, const int& collisionRightUp,
	                    const int& collisionLeftDown, const int& collisionRightDown,
	                    const int& collisionCenterLeft, const int& collisionCenterRight,
	                    const int& collisionCenterUp, const int& collisionCenterDown);
};
