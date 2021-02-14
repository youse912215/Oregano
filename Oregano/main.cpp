#include "DxLib.h"
#include "windowPreference.h"
#include "loopProcess.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	windowSettingOutLoop(); //���[�v�O�E�B���h�E�ݒ�
	if (DxLib_Init() == -1) { return -1; } //DXlib�̏�����
	SetDrawScreen(DX_SCREEN_BACK); //(�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��

	loopProcess(); //���[�v���ɂ����鏈��

	DxLib_End(); //Dx���C�u�����I������
	return 0; //����I��
}
