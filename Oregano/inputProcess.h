#pragma once

class Input {
private:
	static char keys[256];
	static char oldkeys[256];

public:
	Input();
	void input_info();
	void moving_process(const bool& collisionLeft, const bool& collisionRight,
	                    const bool& collisionUp, const bool& collisionDown);
};
