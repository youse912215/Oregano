#pragma once

class Input {
public:
	static char keys[256]; //�ŐV�̃L�[�{�[�h���p
	static char oldkeys[256]; //1���[�v(�t���[��)�O�̃L�[�{�[�h���
	static void input_info();
	void moving_process(const bool& collisionLeftUp, const bool& collisionRightUp,
	                    const bool& collisionLeftDown, const bool& collisionRightDown,
	                    const bool& collisionCenterLeft, const bool& collisionCenterRight,
	                    const bool& collisionCenterUp, const bool& collisionCenterDown);
};
