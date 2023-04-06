#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace std;
using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
    walls.clear();
    floors.clear();
    goals.clear();
    boxes.clear();
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    if (level >= 1 && change_level_flag == 0)
    {
        for (unsigned i = 0; i < boxes.size(); i++)
        {
            for (auto goal : goals)
            {
                if (boxes[i].GetTop() == goal.GetTop() && boxes[i].GetLeft() == goal.GetLeft())
                {
                    boxes[i].SetFrameIndexOfBitmap(1);
                }
            }
        }

        /////////////////
        // 放最下面判斷 //
        /////////////////
        int c = 0;
        for (auto box : boxes)
        {
            for (auto goal : goals)
            {
                if (box.GetTop() == goal.GetTop() && box.GetLeft() == goal.GetLeft())
                {
                    c++;
                }
            }
        }
        //
        // 跳關畫面
        //
        if (c == goals_amount[level - 1])
        {
            TRACE("level %d clear", level);
            change_level();
        }
    }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    background.LoadBitmapByString({"resources/bg_main.bmp", "resources/bg_level_sheet.bmp", "resources/bg_level.bmp", "resources/bg_next_level.bmp"}, RGB(163, 73, 164));
    background.SetTopLeft(0, 0);
    for (int i = 0; i < 70; i++)
    {
        CMovingBitmap level;
        level.LoadBitmapByString({"resources/level0.bmp", "resources/level1.bmp", "resources/level2.bmp"}, RGB(163, 73, 164));
        levels[i] = level;
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            levels[i * 5 + j].SetTopLeft(30 + 100 * j, 210 + 100 * i);
        }
    }

    //
    middle_to_level.LoadBitmapByString({"resources/middle_to_level.bmp"}, RGB(163, 73, 164));
    middle_to_level.SetTopLeft(90, 485);
    middle_next.LoadBitmapByString({"resources/middle_next.bmp"}, RGB(163, 73, 164));
    middle_next.SetTopLeft(218, 465);
    middle_restart.LoadBitmapByString({"resources/middle_restart.bmp"}, RGB(163, 73, 164));
    middle_restart.SetTopLeft(381, 485);

    //
    //(41,835)
    foot_control.LoadBitmapByString({"resources/foot_control0.bmp", "resources/foot_control1.bmp", "resources/foot_control2.bmp"}, RGB(163, 73, 164));
    foot_control.SetTopLeft(41, 835);

    //(136,835)

    foot_to_level.LoadBitmapByString({"resources/foot_to_level0.bmp"}, RGB(163, 73, 164));
    foot_to_level.SetTopLeft(231, 830);

    foot_undo.LoadBitmapByString({"resources/foot_undo.bmp"}, RGB(163, 73, 164));
    foot_undo.SetTopLeft(336, 835);

    foot_restart.LoadBitmapByString({"resources/foot_restart.bmp"}, RGB(163, 73, 164));
    foot_restart.SetTopLeft(431, 835);
    Sleep(1000);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (level >= 1)
    {
        if (nChar == VK_LEFT)
        {
            for (int i = 0; i < walls_amount[level - 1]; i++)
            {
                if (player.GetTop() == walls[i].GetTop() && player.GetLeft() == walls[i].GetLeft() + 60)
                    return;
            }
            for (int i = 0; i < boxes_amount[level - 1]; i++)
            {
                if (player.GetTop() == boxes[i].GetTop() && player.GetLeft() == boxes[i].GetLeft() + 60)
                {
                    for (int j = 0; j < walls_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == walls[j].GetTop() && boxes[i].GetLeft() == walls[j].GetLeft() + 60)
                            return;
                    }
                    for (int j = 0; j < boxes_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == boxes[j].GetTop() && boxes[i].GetLeft() == boxes[j].GetLeft() + 60)
                            return;
                    }

                    boxes[i].SetTopLeft(boxes[i].GetLeft() - 60, boxes[i].GetTop());
                }
            }

            Sleep(150);
            player.SetTopLeft(player.GetLeft() - 60, player.GetTop());
            player.SetFrameIndexOfBitmap(0);
        }
        else if (nChar == VK_UP)
        {
            for (int i = 0; i < walls_amount[level - 1]; i++)
            {
                if (player.GetTop() == walls[i].GetTop() + 60 && player.GetLeft() == walls[i].GetLeft())
                    return;
            }
            for (int i = 0; i < boxes_amount[level - 1]; i++)
            {
                if (player.GetTop() == boxes[i].GetTop() + 60 && player.GetLeft() == boxes[i].GetLeft())
                {
                    for (int j = 0; j < walls_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == walls[j].GetTop() + 60 && boxes[i].GetLeft() == walls[j].GetLeft())
                            return;
                    }
                    for (int j = 0; j < boxes_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == boxes[j].GetTop() + 60 && boxes[i].GetLeft() == boxes[j].GetLeft())
                            return;
                    }

                    boxes[i].SetTopLeft(boxes[i].GetLeft(), boxes[i].GetTop() - 60);
                }
            }

            Sleep(150);
            player.SetTopLeft(player.GetLeft(), player.GetTop() - 60);
            player.SetFrameIndexOfBitmap(1);
        }
        else if (nChar == VK_RIGHT)
        {
            for (int i = 0; i < walls_amount[level - 1]; i++)
            {
                if (player.GetTop() == walls[i].GetTop() && player.GetLeft() + 60 == walls[i].GetLeft())
                    return;
            }
            for (int i = 0; i < boxes_amount[level - 1]; i++)
            {
                if (player.GetTop() == boxes[i].GetTop() && player.GetLeft() + 60 == boxes[i].GetLeft())
                {
                    for (int j = 0; j < walls_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == walls[j].GetTop() && boxes[i].GetLeft() == walls[j].GetLeft() - 60)
                            return;
                    }
                    for (int j = 0; j < boxes_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == boxes[j].GetTop() && boxes[i].GetLeft() == boxes[j].GetLeft() - 60)
                            return;
                    }

                    boxes[i].SetTopLeft(boxes[i].GetLeft() + 60, boxes[i].GetTop());
                    // AS_boxes[i].push(boxes[i].GetLeft(), boxes[i].GetTop());
                }
            }

            Sleep(150);
            player.SetTopLeft(player.GetLeft() + 60, player.GetTop());
            player.SetFrameIndexOfBitmap(2);
        }
        else if (nChar == VK_DOWN)
        {
            for (int i = 0; i < walls_amount[level - 1]; i++)
            {
                if (player.GetTop() + 60 == walls[i].GetTop() && player.GetLeft() == walls[i].GetLeft())
                    return;
            }
            for (int i = 0; i < boxes_amount[level - 1]; i++)
            {
                if (player.GetTop() + 60 == boxes[i].GetTop() && player.GetLeft() == boxes[i].GetLeft())
                {
                    for (int j = 0; j < walls_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == walls[j].GetTop() - 60 && boxes[i].GetLeft() == walls[j].GetLeft())
                            return;
                    }
                    for (int j = 0; j < boxes_amount[level - 1]; j++)
                    {
                        if (boxes[i].GetTop() == boxes[j].GetTop() - 60 && boxes[i].GetLeft() == boxes[j].GetLeft())
                            return;
                    }

                    boxes[i].SetTopLeft(boxes[i].GetLeft(), boxes[i].GetTop() + 60);
                }
            }

            Sleep(150);
            player.SetTopLeft(player.GetLeft(), player.GetTop() + 60);
            player.SetFrameIndexOfBitmap(3);
        }
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    if (change_level_flag)
    {
        if (point.x >= 90 && point.x <= 90 + 68 && point.y >= 485 && point.y <= 485 + 68)
        {
            level = 0;
            change_level_flag = false;
            setByLevel();
            return;
        }
        else if (point.x >= 218 && point.x <= 218 + 103 && point.y >= 465 && point.y <= 465 + 103)
        {
            level += 1;
            change_level_flag = false;
            setByLevel();
            return;
        }
        else if (point.x >= 381 && point.x <= 381 + 68 && point.y >= 485 && point.y <= 485 + 68)
        {
            change_level_flag = false;
            setByLevel();
            return;
        }
    }
    else if (level == -1)
    {
        if (point.x >= 190 && point.x <= 186 + 168 && point.y >= 450 && point.y <= 450 + 73)
        {
            level = 0;
        }
    }
    else if (level == 0)
    {

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if ((i * 5 + j + 1) <= highestLevel && point.x >= 30 + 100 * j && point.x <= 30 + 100 * j + 70 && point.y >= 210 + 100 * i && point.y <= 210 + 100 * i + 70)
                {
                    // levels[i * 5 + j].SetFrameIndexOfBitmap(2);
                    // levels[i * 5 + j].ShowBitmap();
                    level = i * 5 + j + 1;
                    setByLevel();
                }
            }
        }
        // Sleep(450);
        if (point.x >= 30 && point.x < 30 + 72 && point.y >= 810 && point.y < 810 + 72)
        {
            level = -1;
            setByLevel();
        }
    }
    else if (level > 0)
    {
        if (point.x >= 231 && point.x < 231 + 78 && point.y >= 830 && point.y < 830 + 78)
        {
            level = 0;
            setByLevel();
        }
        else if (point.x >= 41 && point.x < 41 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            // int index = (foot_control.GetFrameIndexOfBitmap() + 1) % 3;
            foot_control.SetFrameIndexOfBitmap((foot_control.GetFrameIndexOfBitmap() + 1) % 3);
        }
        else if (point.x >= 336 && point.x < 336 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            ;
        }
        else if (point.x >= 431 && point.x < 431 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            setByLevel();
        }
    }
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
    if (level != prelevel)
    {
        setByLevel();
    }

    Sleep(100);

    if (change_level_flag == 1)
    {
        background.ShowBitmap();
        middle_restart.ShowBitmap();
        middle_next.ShowBitmap();
        middle_to_level.ShowBitmap();
    }
    else if (level == 0)
    {
        background.ShowBitmap();
        for (int i = 0; i < 30; i++)
        {
            levels[i].ShowBitmap();
            level_select_text.ShowBitmap();
            level_to_menu.ShowBitmap();
        }
    }
    else if (level == -1)
    {
        background.ShowBitmap();
        menu_play_text.ShowBitmap();
    }
    else if (level >= 1)
    {
        background.ShowBitmap();

        foot_control.ShowBitmap();

        foot_to_level.ShowBitmap();
        foot_undo.ShowBitmap();
        foot_restart.ShowBitmap();

        for (auto wall : walls)
        {
            wall.ShowBitmap();
        }
        for (auto floor : floors)
        {
            floor.ShowBitmap();
        }
        for (auto goal : goals)
        {
            goal.ShowBitmap();
        }
        for (auto box : boxes)
        {
            box.ShowBitmap();
        }
        player.ShowBitmap();
    }
}
void CGameStateRun::change_level()
{
    change_level_flag = true;
    if (level == highestLevel)
    {
        highestLevel++;
    }
    background.SetFrameIndexOfBitmap(3);
}
void CGameStateRun::setByLevel()
{
    prelevel = level;
    if (level < 1)
    {
        if (level == -1)
        {
            background.SetFrameIndexOfBitmap(0);
            menu_play_text.LoadBitmap("resources/menu_play_text0.bmp", RGB(163, 73, 164));
            menu_play_text.SetTopLeft(186, 450);
        }
        else if (level == 0)
        {
            for (int i = 0; i < highestLevel; i++)
            {
                levels[i].SetFrameIndexOfBitmap(1);
            }

            background.SetFrameIndexOfBitmap(1);

            level_select_text.LoadBitmap("resources/level_select_text.bmp", RGB(163, 73, 164));
            level_select_text.SetTopLeft(100, 85);
            level_to_menu.LoadBitmapByString({"resources/level_to_menu0.bmp"}, RGB(163, 73, 164));
            level_to_menu.SetTopLeft(30, 810);
        }
    }
    else if (level >= 1)
    {
        background.SetFrameIndexOfBitmap(2);

        walls.clear();
        floors.clear();
        goals.clear();
        boxes.clear();
        //
        // stack clear here
        //

        player.LoadBitmapByString({"resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp"}, RGB(163, 73, 164));
        player.SetFrameIndexOfBitmap(3);

        for (int i = 0; i < walls_amount[level - 1]; i++)
        {
            CMovingBitmap wall;
            wall.LoadBitmap("resources/gobj_wall.bmp", RGB(163, 73, 164));
            walls.push_back(wall);
        }
        for (int i = 0; i < floors_amount[level - 1]; i++)
        {
            CMovingBitmap floor;
            floor.LoadBitmap("resources/gobj_floor.bmp", RGB(163, 73, 164));
            floors.push_back(floor);
        }
        for (int i = 0; i < goals_amount[level - 1]; i++)
        {
            CMovingBitmap goal;
            goal.LoadBitmap("resources/gobj_goal.bmp", RGB(163, 73, 164));
            goals.push_back(goal);
        }
        for (int i = 0; i < boxes_amount[level - 1]; i++)
        {
            CMovingBitmap box;
            box.LoadBitmapByString({"resources/gobj_box0.bmp", "resources/gobj_box1.bmp"}, RGB(163, 73, 164));
            boxes.push_back(box);
        }

        player.SetTopLeft(180, 480);

        //------
        Sleep(500);
        //-------

        // boxes[0].SetTopLeft(240, 360);
        int walls_count = 0;
        int floors_count = 0;
        int boxes_count = 0;
        int goals_count = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (walls_like[level - 1][j][i] == 1)
                {
                    walls[walls_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    walls_count++;
                }
                else if (walls_like[level - 1][j][i] == 2)
                {
                    floors[floors_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    floors_count++;
                }
                else if (walls_like[level - 1][j][i] == 3)
                {
                    floors[floors_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    floors_count++;
                    boxes[boxes_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    boxes_count++;
                }
                else if (walls_like[level - 1][j][i] == 4)
                {
                    goals[goals_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    goals_count++;
                }
                else if (walls_like[level - 1][j][i] == 5)
                {
                    boxes[boxes_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    boxes_count++;
                    goals[goals_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    goals_count++;
                }
                else if (walls_like[level - 1][j][i] == 6)
                {
                    player.SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    floors[floors_count].SetTopLeft(0 + 60 * i, 240 + 60 * j);
                    floors_count++;
                }
            }
        }
    }
}
