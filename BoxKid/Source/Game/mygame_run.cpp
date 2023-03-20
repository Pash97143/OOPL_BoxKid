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
    if (level >= 1)
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
        int bc = boxes.size(), c = 0;
        for (unsigned i = 0; i < boxes.size(); i++)
        {
            if (boxes[i].GetFrameIndexOfBitmap() == 1)
            {
                c++;
            }
        }
        //
        // 跳關畫面
        //
        if (c == bc)
        {
            if (level == highestLevel)
            {
                highestLevel++;
            }
        }
    }

    void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
    {
        background.LoadBitmapByString({"resources/bg_main.bmp", "resources/bg_level_sheet.bmp", "resources/bg_level.bmp"}, RGB(163, 73, 164));
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
        Sleep(1000);
    }

    void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if (level >= 1)
        { /*
             if (nChar == VK_LEFT)
             {
                 for (auto wall : walls)
                 {
                     if (player.GetTop() == wall.GetTop() && player.GetLeft() == wall.GetLeft() + 60)
                         return;
                 }
                 for (auto box1 : boxes)
                 {
                     if (player.GetTop() == box1.GetTop() && player.GetLeft() == box1.GetLeft() + 60)
                     {
                         for (auto wall : walls)
                         {
                             if (box1.GetTop() == wall.GetTop() && box1.GetLeft() == wall.GetLeft() + 60)
                                 return;
                         }
                         for (auto box2 : boxes)
                         {
                             if (box1.GetTop() == box2.GetTop() && box1.GetLeft() == box2.GetLeft() + 60)
                                 return;
                         }
                         box1.SetTopLeft(box1.GetLeft() - 60, box1.GetTop());
                     }
                 }
                 Sleep(150);
                 player.SetTopLeft(player.GetLeft() - 60, player.GetTop());
                 player.SetFrameIndexOfBitmap(0);
             }
             else if (nChar == VK_UP)
             {
                 for (auto wall : walls)
                 {
                     if (player.GetTop() == wall.GetTop() + 60 && player.GetLeft() == wall.GetLeft())
                         return;
                 }
                 for (auto box1 : boxes)
                 {
                     if (player.GetTop() == box1.GetTop() + 60 && player.GetLeft() == box1.GetLeft())
                     {
                         for (auto wall : walls)
                         {
                             if (box1.GetTop() == wall.GetTop() + 60 && box1.GetLeft() == wall.GetLeft())
                                 return;
                         }
                         for (auto box2 : boxes)
                         {
                             if (box1.GetTop() == box2.GetTop() + 60 && box1.GetLeft() == box2.GetLeft())
                                 return;
                         }
                         box1.SetTopLeft(box1.GetLeft(), box1.GetTop() - 60);
                     }
                 }
                 Sleep(150);
                 player.SetTopLeft(player.GetLeft(), player.GetTop() - 60);
                 player.SetFrameIndexOfBitmap(1);
             }
             else if (nChar == VK_RIGHT)
             {
                 for (auto wall : walls)
                 {
                     if (player.GetTop() == wall.GetTop() && player.GetLeft() + 60 == wall.GetLeft())
                         return;
                 }
                 for (auto box1 : boxes)
                 {
                     if (player.GetTop() == box1.GetTop() && player.GetLeft() + 60 == box1.GetLeft())
                     {
                         for (auto wall : walls)
                         {
                             if (box1.GetTop() == wall.GetTop() && box1.GetLeft() + 60 == wall.GetLeft())
                                 return;
                         }
                         for (auto box2 : boxes)
                         {
                             if (box1.GetTop() == box2.GetTop() && box2.GetLeft() == box1.GetLeft() + 60)
                                 return;
                         }
                         // background.SetFrameIndexOfBitmap(0);
                         // box1.SetFrameIndexOfBitmap(1);
                         // box1.SetTopLeft(box1.GetLeft() + 60, box1.GetTop());
                         box1.SetTopLeft(box1.GetLeft() + 60, box1.GetTop());
                     }
                 }
                 Sleep(150);
                 player.SetTopLeft(player.GetLeft() + 60, player.GetTop());
                 player.SetFrameIndexOfBitmap(2);
             }
             else if (nChar == VK_DOWN)
             {
                 for (auto wall : walls)
                 {
                     if (player.GetTop() + 60 == wall.GetTop() && player.GetLeft() == wall.GetLeft())
                         return;
                 }
                 for (auto box1 : boxes)
                 {
                     if (player.GetTop() + 60 == box1.GetTop() && player.GetLeft() == box1.GetLeft())
                     {
                         for (auto wall : walls)
                         {
                             if (box1.GetTop() + 60 == wall.GetTop() && box1.GetLeft() == wall.GetLeft())
                                 return;
                         }
                         for (auto box2 : boxes)
                         {
                             if (box2.GetTop() + 60 == box1.GetTop() && box1.GetLeft() == box2.GetLeft())
                                 return;
                         }
                         box1.SetTopLeft(box1.GetLeft(), box1.GetTop() + 60);
                     }
                 }
                 Sleep(150);
                 player.SetTopLeft(player.GetLeft(), player.GetTop() + 60);
                 player.SetFrameIndexOfBitmap(3);
             }
     */
            int walls_amount = walls.size();
            int boxes_amount = boxes.size();

            if (nChar == VK_LEFT)
            {
                for (int i = 0; i < walls_amount; i++)
                {
                    if (player.GetTop() == walls[i].GetTop() && player.GetLeft() == walls[i].GetLeft() + 60)
                        return;
                }
                for (int i = 0; i < boxes_amount; i++)
                {
                    if (player.GetTop() == boxes[i].GetTop() && player.GetLeft() == boxes[i].GetLeft() + 60)
                    {
                        for (int j = 0; j < walls_amount; j++)
                        {
                            if (boxes[i].GetTop() == walls[j].GetTop() && boxes[i].GetLeft() == walls[j].GetLeft() + 60)
                                return;
                        }
                        for (int j = 0; j < boxes_amount; j++)
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
                for (int i = 0; i < walls_amount; i++)
                {
                    if (player.GetTop() == walls[i].GetTop() + 60 && player.GetLeft() == walls[i].GetLeft())
                        return;
                }
                for (int i = 0; i < boxes_amount; i++)
                {
                    if (player.GetTop() == boxes[i].GetTop() + 60 && player.GetLeft() == boxes[i].GetLeft())
                    {
                        for (int j = 0; j < walls_amount; j++)
                        {
                            if (boxes[i].GetTop() == walls[j].GetTop() + 60 && boxes[i].GetLeft() == walls[j].GetLeft())
                                return;
                        }
                        for (int j = 0; j < boxes_amount; j++)
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
                for (int i = 0; i < walls_amount; i++)
                {
                    if (player.GetTop() == walls[i].GetTop() && player.GetLeft() + 60 == walls[i].GetLeft())
                        return;
                }
                for (int i = 0; i < boxes_amount; i++)
                {
                    if (player.GetTop() == boxes[i].GetTop() && player.GetLeft() + 60 == boxes[i].GetLeft())
                    {
                        for (int j = 0; j < walls_amount; j++)
                        {
                            if (boxes[i].GetTop() == walls[j].GetTop() && boxes[i].GetLeft() == walls[j].GetLeft() - 60)
                                return;
                        }
                        for (int j = 0; j < boxes_amount; j++)
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
                for (int i = 0; i < walls_amount; i++)
                {
                    if (player.GetTop() + 60 == walls[i].GetTop() && player.GetLeft() == walls[i].GetLeft())
                        return;
                }
                for (int i = 0; i < boxes_amount; i++)
                {
                    if (player.GetTop() + 60 == boxes[i].GetTop() && player.GetLeft() == boxes[i].GetLeft())
                    {
                        for (int j = 0; j < walls_amount; j++)
                        {
                            if (boxes[i].GetTop() == walls[j].GetTop() - 60 && boxes[i].GetLeft() == walls[j].GetLeft())
                                return;
                        }
                        for (int j = 0; j < boxes_amount; j++)
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
        if (level == -1)
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
                    }
                }
            }
            // Sleep(450);
            if (point.x >= 30 && point.x < 30 + 72 && point.y >= 810 && point.y < 810 + 72)
            {
                level = -1;
            }
        }
        else if (level > 0)
        {
            if (point.x >= 231 && point.x < 231 + 78 && point.y >= 830 && point.y < 830 + 78)
            {
                level = 0;
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

        if (level == 0)
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

            //(41,830)

            //(136,830)

            foot_to_level.LoadBitmapByString({"resources/foot_to_level0.bmp"}, RGB(163, 73, 164));
            foot_to_level.SetTopLeft(231, 830);

            foot_undo.LoadBitmapByString({"resources/foot_undo.bmp"}, RGB(163, 73, 164));
            foot_undo.SetTopLeft(336, 835);

            foot_restart.LoadBitmapByString({"resources/foot_restart.bmp"}, RGB(163, 73, 164));
            foot_restart.SetTopLeft(431, 835);

            walls.clear();
            floors.clear();
            goals.clear();
            boxes.clear();

            if (level == 1)
            {
                player.LoadBitmapByString({"resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp"}, RGB(163, 73, 164));
                player.SetFrameIndexOfBitmap(3);
                player.SetTopLeft(180, 480);

                for (int i = 0; i < 20; i++)
                {
                    CMovingBitmap wall;
                    wall.LoadBitmap("resources/gobj_wall.bmp", RGB(163, 73, 164));
                    walls.push_back(wall);
                }
                for (int i = 0; i < 8; i++)
                {
                    CMovingBitmap floor;
                    floor.LoadBitmap("resources/gobj_floor.bmp", RGB(163, 73, 164));
                    floors.push_back(floor);
                }
                for (int i = 0; i < 1; i++)
                {
                    CMovingBitmap goal;
                    goal.LoadBitmap("resources/gobj_goal.bmp", RGB(163, 73, 164));
                    goals.push_back(goal);
                }

                for (int i = 0; i < 1; i++)
                {
                    CMovingBitmap box;
                    box.LoadBitmapByString({"resources/gobj_box0.bmp", "resources/gobj_box1.bmp"}, RGB(163, 73, 164));
                    boxes.push_back(box);
                }

                //------
                Sleep(500);
                //-------

                boxes[0].SetTopLeft(240, 360);

                for (int i = 0; i < 7; i++)
                {
                    walls[i].SetTopLeft(60 + i * 60, 300);
                }
                walls[7].SetTopLeft(60, 360);
                walls[8].SetTopLeft(60, 420);
                walls[9].SetTopLeft(60, 480);
                walls[10].SetTopLeft(60, 540);
                walls[11].SetTopLeft(120, 540);
                walls[12].SetTopLeft(180, 540);
                walls[13].SetTopLeft(240, 540);
                walls[14].SetTopLeft(240, 480);
                walls[15].SetTopLeft(240, 420);
                walls[16].SetTopLeft(300, 420);
                walls[17].SetTopLeft(360, 420);
                walls[18].SetTopLeft(420, 420);
                walls[19].SetTopLeft(420, 360);

                floors[0].SetTopLeft(120, 360);
                floors[1].SetTopLeft(180, 360);
                floors[2].SetTopLeft(240, 360);
                floors[3].SetTopLeft(300, 360);
                floors[4].SetTopLeft(120, 420);
                floors[5].SetTopLeft(180, 420);
                floors[6].SetTopLeft(120, 480);
                floors[7].SetTopLeft(180, 480);

                goals[0].SetTopLeft(360, 360);
            }
            else if (level == 2)
            {
                player.LoadBitmapByString({"resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp", "resources/player9.bmp"}, RGB(163, 73, 164));
                player.SetFrameIndexOfBitmap(3);
                player.SetTopLeft(240, 360);

                for (int i = 0; i < 22; i++)
                {
                    CMovingBitmap wall;
                    wall.LoadBitmap("resources/gobj_wall.bmp", RGB(163, 73, 164));
                    walls.push_back(wall);
                }
                for (int i = 0; i < 20; i++)
                {
                    CMovingBitmap floor;
                    floor.LoadBitmap("resources/gobj_floor.bmp", RGB(163, 73, 164));
                    floors.push_back(floor);
                }
                for (int i = 0; i < 1; i++)
                {
                    CMovingBitmap goal;
                    goal.LoadBitmap("resources/gobj_goal.bmp", RGB(163, 73, 164));
                    goals.push_back(goal);
                }

                for (int i = 0; i < 1; i++)
                {
                    CMovingBitmap box;
                    box.LoadBitmapByString({"resources/gobj_box0.bmp", "resources/gobj_box1.bmp"}, RGB(163, 73, 164));
                    boxes.push_back(box);
                }

                //------
                Sleep(500);
                //-------

                for (int i = 0; i < 7; i++)
                {
                    walls[i].SetTopLeft(60 + i * 60, 300);
                }
                walls[7].SetTopLeft(60, 360);
                walls[8].SetTopLeft(420, 360);
                walls[9].SetTopLeft(60, 420);
                walls[10].SetTopLeft(420, 420);
                walls[11].SetTopLeft(60, 480);
                walls[12].SetTopLeft(420, 480);
                walls[13].SetTopLeft(60, 540);
                walls[14].SetTopLeft(420, 540);

                for (int i = 0; i < 7; i++)
                {
                    walls[i + 15].SetTopLeft(60 + i * 60, 600);
                }

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        floors[i * 5 + j].SetTopLeft(120 + j * 60, 360 + i * 60);
                    }
                }

                boxes[0].SetTopLeft(300, 480);
                goals[0].SetTopLeft(360, 480);
            }
        }
    }
