#pragma once

class Input {
public:
	static char keys[256]; //最新のキーボード情報用
	static char oldkeys[256]; //1ループ(フレーム)前のキーボード情報
	static void input_info();
	void moving_process(const bool& collisionLeftUp, const bool& collisionRightUp,
	                    const bool& collisionLeftDown, const bool& collisionRightDown,
	                    const bool& collisionCenterLeft, const bool& collisionCenterRight,
	                    const bool& collisionCenterUp, const bool& collisionCenterDown);
};
