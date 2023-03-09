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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{ //
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize..."); // 一開始的loading進度為0%
	//
	Sleep(200);
	background.LoadBitmap("resources/background_main.bmp", RGB(0, 0, 0));
	background.SetTopLeft(0, 0);

	playIcon.LoadBitmap("resources/play.bmp", RGB(0, 0, 0));
	playIcon.SetTopLeft(152, 500);
	Sleep(200);
	//
	Sleep(1000); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
			GotoGameState(GAME_STATE_RUN); // 切換至GAME_STATE_RUN
		}
	}
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	playIcon.ShowBitmap();
}
