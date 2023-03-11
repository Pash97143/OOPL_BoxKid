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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    level = 1;
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    background.LoadBitmapByString({"resources/background_level.bmp"}, RGB(255, 255, 255));
    background.SetTopLeft(0, 0);
    player.LoadBitmapByString({"resources/player_down.bmp"}, RGB(255, 255, 255));
    player.SetTopLeft(160, 515);
    for (int i = 0; i < 20; i++)
    {
        CMovingBitmap wall;
        wall.LoadBitmap("resources/wall.bmp", RGB(255, 255, 255));
        walls.push_back(wall);
    }
    for (int i = 0; i < 8; i++)
    {
        CMovingBitmap floor;
        floor.LoadBitmap("resources/floor.bmp", RGB(255, 255, 255));
        floors.push_back(floor);
    }
    for (int i = 0; i < 1; i++)
    {
        CMovingBitmap goal;
        goal.LoadBitmap("resources/goal.bmp", RGB(255, 255, 255));
        goals.push_back(goal);
    }

    for (int i = 0; i < 1; i++)
    {
        CMovingBitmap box;
        box.LoadBitmapByString({"resources/box.bmp", "resources/box_goal.bmp"}, RGB(255, 255, 255));
        boxes.push_back(box);
    }
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == 0x25)
    {
        player.SetTopLeft(player.Left() - 55, player.Top());
    }
    else if (nChar == 0x26)
    {
        player.SetTopLeft(player.Left(), player.Top() - 55);
    }
    else if (nChar == 0x27)
    {
        player.SetTopLeft(player.Left() + 55, player.Top());
    }
    else if (nChar == 0x28)
    {
        player.SetTopLeft(player.Left(), player.Top() + 55);
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    showByLevel();
}

void CGameStateRun::showByLevel()
{
    if (level != 0)
    {
        background.ShowBitmap();
        if (level == 1)
        {
            // player.SetTopLeft(160, 515);

            for (int i = 0; i < 7; i++)
            {
                walls[i].SetTopLeft(50 + i * 55, 350);
            }
            walls[7].SetTopLeft(50, 405);
            walls[8].SetTopLeft(50, 460);
            walls[9].SetTopLeft(50, 515);
            walls[10].SetTopLeft(50, 570);
            walls[11].SetTopLeft(105, 570);
            walls[12].SetTopLeft(160, 570);
            walls[13].SetTopLeft(215, 570);
            walls[14].SetTopLeft(215, 515);
            walls[15].SetTopLeft(215, 460);
            walls[16].SetTopLeft(270, 460);
            walls[17].SetTopLeft(325, 460);
            walls[18].SetTopLeft(380, 460);
            walls[19].SetTopLeft(380, 405);

            floors[0].SetTopLeft(105, 405);
            floors[1].SetTopLeft(160, 405);
            floors[2].SetTopLeft(215, 405);
            floors[3].SetTopLeft(270, 405);
            floors[4].SetTopLeft(105, 460);
            floors[5].SetTopLeft(160, 460);
            floors[6].SetTopLeft(105, 515);
            floors[7].SetTopLeft(160, 515);

            goals[0].SetTopLeft(325, 405);

            boxes[0].SetTopLeft(215, 405);

            for (int i = 0; i < 20; i++)
            {
                walls[i].ShowBitmap();
            }
            for (int i = 0; i < 8; i++)
            {
                floors[i].ShowBitmap();
            }
            for (int i = 0; i < 1; i++)
            {
                goals[i].ShowBitmap();
            }
            for (int i = 0; i < 1; i++)
            {
                boxes[i].ShowBitmap();
            }
            player.ShowBitmap();
        }
    }
}
