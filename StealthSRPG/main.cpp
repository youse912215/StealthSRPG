#include "DxLib.h"
#include "windowPreference.h"
#include "loopProcess.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	window_out_loop(); //���[�v�O�E�B���h�E�ݒ�
	if (DxLib_Init() == -1) { return -1; } //DXlib�̏�����
	SetDrawScreen(DX_SCREEN_BACK); //(�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��

	loop_process(); //���[�v������

	DxLib_End(); //Dx���C�u�����I������
	return 0; //����I��
}
