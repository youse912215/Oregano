#pragma once
#include <vector>

using namespace std;

class Input {
private:
	static char keys[256];
	static char oldkeys[256];

	int pad;
	bool padLeft;
	bool padRight;
	bool padUp;
	bool padDown;
	bool pad1;
	bool pad2;
	bool pad3;
	bool pad4;
	bool pad5;
	bool pad6;
	bool pad7;
	bool pad8;
	bool pad9;
	bool pad10;

public:
	static int add;

	vector<bool> buttonFlag;
	bool A;
	bool B;
	bool X;
	bool Y;

	int moveDirection; //¡Œ©‚Ä‚¢‚éˆÚ“®•ûŒü

	Input();
	void inputInformation();
	void moveProcess(const bool& collisionLeft, const bool& collisionRight,
	                 const bool& collisionUp, const bool& collisionDown);
	void eventProcess();
	void endProcess();
	void update();
};
