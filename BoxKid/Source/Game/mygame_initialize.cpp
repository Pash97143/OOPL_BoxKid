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
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize..."); // 一開始的loading進度為0%

	//
	// 開始載入資料
	//
	// Sleep(500);									  // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	// ShowInitProgress(33, "Start Initialize...");  // 載入了1/3，進度為33%
	// Sleep(500);									  // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	// ShowInitProgress(66, "Start Initialize...");  // 載入了2/3，進度為66%
	// Sleep(500);									  // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	// ShowInitProgress(100, "Start Initialize..."); // 載入了3/3，進度為100%

	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
	// goRun();
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	goRun();
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	goRun();
}

void CGameStateInit::OnShow()
{
	draw_text();
}

void CGameStateInit::goRun()
{
	GotoGameState(GAME_STATE_RUN); // 切換至GAME_STATE_RUN
}

void CGameStateInit::draw_text()
{
	CDC *pDC = CDDraw::GetBackCDC();
	// CFont *fp;

	/* Print title */

	string s = "Press any key to start";
	CTextDraw::ChangeFontLog(pDC, 26, "微軟正黑體", RGB(255, 255, 255));

	CTextDraw::Print(pDC, 100, 400, s);

	CDDraw::ReleaseBackCDC();
}