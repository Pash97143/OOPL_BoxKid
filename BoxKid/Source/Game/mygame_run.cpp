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
    for (int i = 0; i < boxes_amount; i++)
    {
        if (boxes[i].Top() == goals[i].Top() && boxes[i].Left() == goals[i].Left())
        {
            boxes[i].SelectShowBitmap(1);
        }
    }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    background.LoadBitmapByString({"resources/background_level.bmp"}, RGB(0, 0, 0));
    background.SetTopLeft(0, 0);
    player.LoadBitmapByString({"resources/player_left.bmp", "resources/player_up.bmp", "resources/player_right.bmp", "resources/player_down.bmp"}, RGB(0, 0, 0));
    player.SelectShowBitmap(3);
    player.SetTopLeft(160, 460);

    for (int i = 0; i < 20; i++)
    {
        CMovingBitmap wall;
        wall.LoadBitmap("resources/wall.bmp", RGB(0, 0, 0));
        walls.push_back(wall);
    }
    for (int i = 0; i < 8; i++)
    {
        CMovingBitmap floor;
        floor.LoadBitmap("resources/floor.bmp", RGB(0, 0, 0));
        floors.push_back(floor);
    }
    for (int i = 0; i < 1; i++)
    {
        CMovingBitmap goal;
        goal.LoadBitmap("resources/goal.bmp", RGB(0, 0, 0));
        goals.push_back(goal);
    }

    for (int i = 0; i < 1; i++)
    {
        CMovingBitmap box;
        box.LoadBitmapByString({"resources/box.bmp", "resources/box_goal.bmp"}, RGB(0, 0, 0));
        boxes.push_back(box);
    }

    //------
    boxes[0].SetTopLeft(215, 350);
    //------
    Sleep(500);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_LEFT)
    {
        for (int i = 0; i < walls_amount; i++)
        {
            if (player.Top() == walls[i].Top() && player.Left() == walls[i].Left() + 55)
                return;
        }
        for (int i = 0; i < boxes_amount; i++)
        {
            if (player.Top() == boxes[i].Top() && player.Left() == boxes[i].Left() + 55)
            {
                for (int j = 0; j < walls_amount; j++)
                {
                    if (boxes[i].Top() == walls[j].Top() && boxes[i].Left() == walls[j].Left() + 55)
                        return;
                }
                for (int j = 0; j < boxes_amount; j++)
                {
                    if (boxes[i].Top() == boxes[j].Top() && boxes[i].Left() == boxes[j].Left() + 55)
                        return;
                }
                boxes[i].SetTopLeft(boxes[i].Left() - 55, boxes[i].Top());
            }
        }
        Sleep(150);
        player.SetTopLeft(player.Left() - 55, player.Top());
        player.SelectShowBitmap(0);
    }
    else if (nChar == VK_UP)
    {
        for (int i = 0; i < walls_amount; i++)
        {
            if (player.Top() == walls[i].Top() + 55 && player.Left() == walls[i].Left())
                return;
        }
        for (int i = 0; i < boxes_amount; i++)
        {
            if (player.Top() == boxes[i].Top() + 55 && player.Left() == boxes[i].Left())
            {
                for (int j = 0; j < walls_amount; j++)
                {
                    if (boxes[i].Top() == walls[j].Top() + 55 && boxes[i].Left() == walls[j].Left())
                        return;
                }
                for (int j = 0; j < boxes_amount; j++)
                {
                    if (boxes[i].Top() == boxes[j].Top() + 55 && boxes[i].Left() == boxes[j].Left())
                        return;
                }
                boxes[i].SetTopLeft(boxes[i].Left(), boxes[i].Top() - 55);
            }
        }
        Sleep(150);
        player.SetTopLeft(player.Left(), player.Top() - 55);
        player.SelectShowBitmap(1);
    }
    else if (nChar == VK_RIGHT)
    {
        for (int i = 0; i < walls_amount; i++)
        {
            if (player.Top() == walls[i].Top() && player.Left() + 55 == walls[i].Left())
                return;
        }
        for (int i = 0; i < boxes_amount; i++)
        {
            if (player.Top() == boxes[i].Top() && player.Left() + 55 == boxes[i].Left())
            {
                for (int j = 0; j < walls_amount; j++)
                {
                    if (boxes[i].Top() == walls[j].Top() && boxes[i].Left() == walls[j].Left() - 55)
                        return;
                }
                for (int j = 0; j < boxes_amount; j++)
                {
                    if (boxes[i].Top() == boxes[j].Top() && boxes[i].Left() == boxes[j].Left() - 55)
                        return;
                }
                boxes[i].SetTopLeft(boxes[i].Left() + 55, boxes[i].Top());
            }
        }
        Sleep(150);
        player.SetTopLeft(player.Left() + 55, player.Top());
        player.SelectShowBitmap(2);
    }
    else if (nChar == VK_DOWN)
    {
        for (int i = 0; i < walls_amount; i++)
        {
            if (player.Top() + 55 == walls[i].Top() && player.Left() == walls[i].Left())
                return;
        }
        for (int i = 0; i < boxes_amount; i++)
        {
            if (player.Top() + 55 == boxes[i].Top() && player.Left() == boxes[i].Left())
            {
                for (int j = 0; j < walls_amount; j++)
                {
                    if (boxes[i].Top() == walls[j].Top() - 55 && boxes[i].Left() == walls[j].Left())
                        return;
                }
                for (int j = 0; j < boxes_amount; j++)
                {
                    if (boxes[i].Top() == boxes[j].Top() - 55 && boxes[i].Left() == boxes[j].Left())
                        return;
                }
                boxes[i].SetTopLeft(boxes[i].Left(), boxes[i].Top() + 55);
            }
        }
        Sleep(150);
        player.SetTopLeft(player.Left(), player.Top() + 55);
        player.SelectShowBitmap(3);
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
        // Sleep(300);
        background.ShowBitmap();
        if (level == 1)
        {
            walls_amount = 20;
            boxes_amount = 1;

            for (int i = 0; i < 7; i++)
            {
                walls[i].SetTopLeft(50 + i * 55, 295);
            }
            walls[7].SetTopLeft(50, 350);
            walls[8].SetTopLeft(50, 405);
            walls[9].SetTopLeft(50, 460);
            walls[10].SetTopLeft(50, 515);
            walls[11].SetTopLeft(105, 515);
            walls[12].SetTopLeft(160, 515);
            walls[13].SetTopLeft(215, 515);
            walls[14].SetTopLeft(215, 460);
            walls[15].SetTopLeft(215, 405);
            walls[16].SetTopLeft(270, 405);
            walls[17].SetTopLeft(325, 405);
            walls[18].SetTopLeft(380, 405);
            walls[19].SetTopLeft(380, 350);

            floors[0].SetTopLeft(105, 350);
            floors[1].SetTopLeft(160, 350);
            floors[2].SetTopLeft(215, 350);
            floors[3].SetTopLeft(270, 350);
            floors[4].SetTopLeft(105, 405);
            floors[5].SetTopLeft(160, 405);
            floors[6].SetTopLeft(105, 460);
            floors[7].SetTopLeft(160, 460);

            goals[0].SetTopLeft(325, 350);

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
