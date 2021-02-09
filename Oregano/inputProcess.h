#pragma once

class Input {
public:
	static char keys[256]; //最新のキーボード情報用
	static char oldkeys[256]; //1ループ(フレーム)前のキーボード情報
	static void input_info();
	void moving_process(const int& collisionLeftUp, const int& collisionRightUp,
	                    const int& collisionLeftDown, const int& collisionRightDown,
	                    const int& collisionCenterLeft, const int& collisionCenterRight,
	                    const int& collisionCenterUp, const int& collisionCenterDown);
};
