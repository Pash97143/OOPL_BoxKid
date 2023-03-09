#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{ //
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize..."); // �@�}�l��loading�i�׬�0%
	//
	Sleep(200);
	background.LoadBitmap("resources/background_main.bmp", RGB(0, 0, 0));
	background.SetTopLeft(0, 0);

	playIcon.LoadBitmap("resources/play.bmp", RGB(0, 0, 0));
	playIcon.SetTopLeft(152, 500);
	Sleep(200);
	//
	Sleep(1000); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON)
	{
		if (point.x >= 152 && point.x <= 152 + 174 && point.y >= 500 && point.y <= 500 + 77)
		{
			GotoGameState(GAME_STATE_RUN); // ������GAME_STATE_RUN
		}
	}
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	playIcon.ShowBitmap();
}
