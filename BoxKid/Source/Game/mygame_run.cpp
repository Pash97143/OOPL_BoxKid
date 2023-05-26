#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;
using namespace game_framework;
CAudio *audio = CAudio::Instance(); // 背景音樂

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
            bool goal_flag = 0;
            for (auto goal : goals)
            {
                if (boxes[i].GetTop() == goal.GetTop() && boxes[i].GetLeft() == goal.GetLeft())
                {
                    boxes[i].SetFrameIndexOfBitmap(1);
                    goal_flag = 1;
                }
            }
            if (goal_flag == 0)
            {
                boxes[i].SetFrameIndexOfBitmap(0);
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
            Sleep(500);
            TRACE("level %d clear\n", level);
            change_level();
        }
    }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    
    audio->Load(1, "resources/music.wav");
    audio->Load(2, "resources/sound.wav");
    audio->Play(1, true);
    
    //載入所有背景
       
    background.LoadBitmapByString({"resources/bg_main.bmp", "resources/bg_level_sheet.bmp", "resources/bg_level_sheet.bmp", "resources/bg_level_sheet.bmp", "resources/bg_level.bmp", "resources/bg_next_level.bmp"}, RGB(163, 73, 164));
    background.SetTopLeft(0, 0);

    //載入主畫面PLAY按鈕
    menu_play_text.LoadBitmapByString({"resources/menu_play_text0.bmp"}, RGB(163, 73, 164));
    menu_play_text.SetTopLeft(186, 450);

    //載入主畫面背景音樂按鈕
    menu_music.LoadBitmapByString({"resources/menu_music0.bmp", "resources/menu_music1.bmp"}, RGB(163, 73, 164));
    menu_music.SetTopLeft(190, 575);

    //載入主畫面按鍵音樂按鈕
    menu_sound.LoadBitmapByString({"resources/menu_sound0.bmp", "resources/menu_sound1.bmp"}, RGB(163, 73, 164));
    menu_sound.SetTopLeft(275, 575);

    //選關畫面設置
    for (int i = 0; i < 70; i++)
    {
        CMovingBitmap level;
        level.LoadBitmapByString({"resources/level0.bmp", "resources/level1.bmp", "resources/level2.bmp"}, RGB(163, 73, 164));
        levels[i] = level;
    }

    //選關畫面SELECT LEVEL 字樣
    level_select_text.LoadBitmap("resources/level_select_text.bmp", RGB(163, 73, 164));
    level_select_text.SetTopLeft(100, 85);
    
    //選關畫面回主畫面按鈕
    level_to_menu.LoadBitmapByString({"resources/level_to_menu0.bmp"}, RGB(163, 73, 164));
    level_to_menu.SetTopLeft(30, 810);

    //載入關卡頁面切換按鈕
    for (int i = 0; i < 3; i++)
    {
        CMovingBitmap page;
        page.LoadBitmapByString({"resources/levels_page0.bmp", "resources/levels_page1.bmp"}, RGB(255, 255, 255));
        turnPage.push_back(page);
        turnPage[i].SetTopLeft(220 + 40 * i, 810);
    }

    //載入關卡底下功能按鈕
    foot_control.LoadBitmapByString({"resources/foot_control0.bmp", "resources/foot_control1.bmp", "resources/foot_control2.bmp"}, RGB(163, 73, 164));
    foot_control.SetTopLeft(41, 835);

    //載入關卡底下音樂按鈕
    foot_music.LoadBitmapByString({"resources/foot_music0.bmp", "resources/foot_music1.bmp"}, RGB(163, 73, 164));
    foot_music.SetTopLeft(136, 835);

    //載入關卡底下回到選關畫面按鈕
    foot_to_level.LoadBitmapByString({"resources/foot_to_level0.bmp"}, RGB(163, 73, 164));
    foot_to_level.SetTopLeft(231, 830);

    //載入關卡底下回上一步按鈕
    foot_undo.LoadBitmapByString({"resources/foot_undo.bmp"}, RGB(163, 73, 164));
    foot_undo.SetTopLeft(336, 835);

    //載入關卡底下重新開始按鈕
    foot_restart.LoadBitmapByString({"resources/foot_restart.bmp"}, RGB(163, 73, 164));
    foot_restart.SetTopLeft(431, 835);

    //載入過關後跳回選關畫面按鈕
    middle_to_level.LoadBitmapByString({"resources/middle_to_level.bmp"}, RGB(163, 73, 164));
    middle_to_level.SetTopLeft(90, 485);

    //載入過關後跳下一關按鈕
    middle_next.LoadBitmapByString({"resources/middle_next.bmp"}, RGB(163, 73, 164));
    middle_next.SetTopLeft(218, 465);

    //載入過關後跳重新遊玩按鈕
    middle_restart.LoadBitmapByString({"resources/middle_restart.bmp"}, RGB(163, 73, 164));
    middle_restart.SetTopLeft(381, 485);

    //載入主人物
    player.LoadBitmapByString({"resources/player0.bmp", "resources/player1.bmp", "resources/player2.bmp", "resources/player3.bmp", "resources/player4.bmp", "resources/player5.bmp", "resources/player6.bmp", "resources/player7.bmp", "resources/player8.bmp", "resources/player9.bmp", "resources/player10.bmp", "resources/player11.bmp"}, RGB(163, 73, 164));
    Sleep(500);
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
                    addToUndo();
                    boxes[i].SetTopLeft(boxes[i].GetLeft() - 60, boxes[i].GetTop());
                    player.SetTopLeft(player.GetLeft() - 60, player.GetTop());
                    player.SetFrameIndexOfBitmap(0);
                    Sleep(150);
                    return;
                }
            }
            addToUndo();
            player.SetTopLeft(player.GetLeft() - 60, player.GetTop());
            player.SetFrameIndexOfBitmap(0);
            Sleep(150);
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
                    addToUndo();
                    boxes[i].SetTopLeft(boxes[i].GetLeft(), boxes[i].GetTop() - 60);
                    player.SetTopLeft(player.GetLeft(), player.GetTop() - 60);
                    player.SetFrameIndexOfBitmap(3);
                    Sleep(150);
                    return;
                }
            }

            addToUndo();
            player.SetTopLeft(player.GetLeft(), player.GetTop() - 60);
            player.SetFrameIndexOfBitmap(3);
            Sleep(150);
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
                    addToUndo();
                    boxes[i].SetTopLeft(boxes[i].GetLeft() + 60, boxes[i].GetTop());
                    player.SetTopLeft(player.GetLeft() + 60, player.GetTop());
                    player.SetFrameIndexOfBitmap(6);
                    Sleep(150);
                    return;
                }
            }

            addToUndo();
            player.SetTopLeft(player.GetLeft() + 60, player.GetTop());
            player.SetFrameIndexOfBitmap(6);
            Sleep(150);
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
                    addToUndo();
                    boxes[i].SetTopLeft(boxes[i].GetLeft(), boxes[i].GetTop() + 60);
                    player.SetTopLeft(player.GetLeft(), player.GetTop() + 60);
                    player.SetFrameIndexOfBitmap(9);
                    Sleep(150);
                    return;
                }
            }

            addToUndo();

            player.SetTopLeft(player.GetLeft(), player.GetTop() + 60);
            player.SetFrameIndexOfBitmap(9);
            Sleep(150);
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
            sound_it();
            level = 0;
            change_level_flag = false;
            setByLevel();
            return;
        }
        else if (point.x >= 218 && point.x <= 218 + 103 && point.y >= 465 && point.y <= 465 + 103)
        {
            sound_it();
            level += 1;
            change_level_flag = false;
            setByLevel();
            return;
        }
        else if (point.x >= 381 && point.x <= 381 + 68 && point.y >= 485 && point.y <= 485 + 68)
        {
            sound_it();
            change_level_flag = false;
            setByLevel();
            return;
        }
    }
    else if (level == -1)
    {
        if (point.x >= 190 && point.x <= 186 + 168 && point.y >= 450 && point.y <= 450 + 73)
        {
            sound_it();
            level = 0;
        }
        else if (point.x >= 190 && point.x <= 190 + 68 && point.y >= 575 && point.y <= 575 + 72)
        {
            sound_it();
            if (music_flag == true)
            {
                audio->Stop(1);
                music_flag = false;
                menu_music.SetFrameIndexOfBitmap(1);
                foot_music.SetFrameIndexOfBitmap(1);
            }
            else
            {
                audio->Play(1, true);
                music_flag = true;
                menu_music.SetFrameIndexOfBitmap(0);
                foot_music.SetFrameIndexOfBitmap(0);
            }
        }
        else if (point.x >= 275 && point.x <= 275 + 68 && point.y >= 575 && point.y <= 575 + 72)
        {
            sound_it();
            if (sound_flag == true)
            {
                sound_flag = false;
                menu_sound.SetFrameIndexOfBitmap(1);
            }
            else
            {
                sound_flag = true;
                menu_sound.SetFrameIndexOfBitmap(0);
            }
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
                    sound_it();
                    level = page * 30 + i * 5 + j + 1;
                    setByLevel();
                    TRACE("\nhere my level is %d\n", level);
                }
            }
        }
        // Sleep(450);
        if (point.x >= 30 && point.x < 30 + 72 && point.y >= 810 && point.y < 810 + 72)
        {
            sound_it();
            level = -1;
            setByLevel();
        }

        if (point.x >= 220 && point.x < 220 + 27 && point.y >= 810 && point.y < 810 + 30)
        {
            setPage(0);
            TRACE("\nhere my highestlevel is %d\n", highestLevel);
        }
        if (point.x >= 260 && point.x < 260 + 27 && point.y >= 810 && point.y < 810 + 30)
        {
            setPage(1);
            TRACE("\nhere my highestlevel is %d\n", highestLevel);
        }
        if (point.x >= 300 && point.x < 300 + 27 && point.y >= 810 && point.y < 810 + 30)
        {
            setPage(2);
            TRACE("\nhere my highestlevel is %d\n", highestLevel);
        }
    }
    else if (level > 0)
    {
        if (point.x >= 41 && point.x < 41 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            sound_it();
            foot_control.SetFrameIndexOfBitmap((foot_control.GetFrameIndexOfBitmap() + 1) % 3);
        }
        else if (point.x >= 136 && point.x < 136 + 68 && point.y >= 835 && point.y < 835 + 68) // 136 835
        {
            sound_it();
            if (music_flag == true)
            {
                audio->Stop(1);
                music_flag = false;
                menu_music.SetFrameIndexOfBitmap(1);
                foot_music.SetFrameIndexOfBitmap(1);
            }
            else
            {
                audio->Play(1, true);
                music_flag = true;
                menu_music.SetFrameIndexOfBitmap(0);
                foot_music.SetFrameIndexOfBitmap(0);
            }
        }
        else if (point.x >= 231 && point.x < 231 + 78 && point.y >= 830 && point.y < 830 + 78)
        {
            sound_it();
            level = 0;
            setByLevel();
        }
        else if (point.x >= 336 && point.x < 336 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            sound_it();
            undo();
        }
        else if (point.x >= 431 && point.x < 431 + 68 && point.y >= 835 && point.y < 835 + 68)
        {
            sound_it();
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
        level_select_text.ShowBitmap();
        level_to_menu.ShowBitmap();
        
        if(page == 0 || page == 1){
        
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    levels[page * 30 + i * 5 + j].SetTopLeft(30 + 100 * j, 210 + 100 * i);
                }
            }

            for(int i = 30 * page; i <  30 * page + 30; i++)
            {
                levels[i].ShowBitmap();
                draw_levels_text();
            }
        }
        else if(page == 2){

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    levels[page * 30 + i * 5 + j].SetTopLeft(30 + 100 * j, 210 + 100 * i);
                }
            }

            for(int i = 30 * page; i <  30 * page + 10; i++)
            {
                levels[i].ShowBitmap();
                draw_levels_text();
            }
        }

        for (int i = 0; i < 3; i++){

            if(i == page)
            {
                turnPage[i].SetFrameIndexOfBitmap(1);
            }
            else
            {
                turnPage[i].SetFrameIndexOfBitmap(0);
            }
            turnPage[i].ShowBitmap();
        }
    }
    else if (level == -1)
    {
        background.ShowBitmap();
        menu_play_text.ShowBitmap();
        menu_music.ShowBitmap();
        menu_sound.ShowBitmap();
    }
    else if (level >= 1)
    {
        background.ShowBitmap();

        foot_control.ShowBitmap();
        foot_music.ShowBitmap();
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

        draw_level(level);
    }
}

void CGameStateRun::change_level()
{
    change_level_flag = true;
    if (level == highestLevel)
    {
        highestLevel++;
    }
    background.SetFrameIndexOfBitmap(5);
}

void CGameStateRun::setPage(int n)
{
    background.SetFrameIndexOfBitmap(n + 1);
    page = n;
}
``
void CGameStateRun::setByLevel()
{
    prelevel = level;
    if (level < 1)
    {
        if (level == -1)
        {
            background.SetFrameIndexOfBitmap(0);

        }
        else if (level == 0)
        {
            TRACE("\nhere my highestlevel is %d\n", highestLevel);
            for (int i = 0; i < highestLevel; i++)
            {
                levels[i].SetFrameIndexOfBitmap(1);
            }
            background.SetFrameIndexOfBitmap(1);
        }
    }
    else if (level >= 1)
    {
        background.SetFrameIndexOfBitmap(4);

        walls.clear();
        floors.clear();
        goals.clear();
        boxes.clear();
        //
        // stack clear here
        player_pos.clear();
        for (auto box : boxes_pos)
        {
            box.clear();
        }
        boxes_pos.clear();
        //
        TRACE("b: %d, f: %d, g: %d, w: %d\n", boxes.size(), floors.size(), goals.size(), walls.size());
        TRACE("bp: %d\n", boxes_pos.size());

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

            std::vector<std::pair<int, int>> vec;
            boxes_pos.push_back(vec);
        }


        //------
        Sleep(500);
        //-------

        // boxes[0].SetTopLeft180, 360);
        int walls_count = 0;
        int floors_count = 0;
        int boxes_count = 0;
        int goals_count = 0;
        TRACE("%d\n", level);
        vector<vector<char>> walls_like = {};

        string line;
        string filename;
        filename = "./Source/level/level" + to_string(level) + ".txt";
        ifstream inputFile(filename);

        while (getline(inputFile, line))
        {
            vector<char> temp = {};
            for (unsigned int i = 0; i < (line.length()); i++)
            {
                if ((line[i] != ',') && (line[i] != ' '))
                {
                    temp.push_back(line[i]);
                }
            }
            walls_like.push_back(temp);
        }
        inputFile.close();
        TRACE("%d\n", walls_like.size());
        TRACE("%d\n", walls_like[0].size());

        for (unsigned int i = 0; i < walls_like[0].size(); i++)
        {
            for (unsigned int j = 0; j < walls_like.size(); j++)
            {
                if (walls_like[j][i] == '1')
                {
                    walls[walls_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    walls_count++;
                    // TRACE("%d\n", walls_count);
                }
                else if (walls_like[j][i] == '2')
                {
                    floors[floors_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    floors_count++;
                    // TRACE("%d\n", floors_count);
                }
                else if (walls_like[j][i] == '3')
                {
                    floors[floors_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    floors_count++;
                    boxes[boxes_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    boxes_count++;
                }
                else if (walls_like[j][i] == '4')
                {
                    goals[goals_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    goals_count++;
                }
                else if (walls_like[j][i] == '5')
                {
                    boxes[boxes_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    boxes_count++;
                    goals[goals_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    goals_count++;
                }
                else if (walls_like[j][i] == '6')
                {
                    player.SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    floors[floors_count].SetTopLeft(0 + 60 * i, 180 + 60 * j);
                    floors_count++;
                }
            }
        }

        TRACE("b: %d, f: %d, g: %d, w: %d\n", boxes.size(), floors.size(), goals.size(), walls.size());
        TRACE("bp: %d\n", boxes_pos.size());
    }
}

void CGameStateRun::addToUndo()
{
    TRACE("now is ok    \n");
    if (player_pos.size() < 20)
    {
        TRACE("undo <= 20 !!\n");
        player_pos.push_back(std::make_pair(player.GetLeft(), player.GetTop()));
        for (int i = 0; i < boxes_amount[level - 1]; i++)
        {
            boxes_pos[i].push_back(std::make_pair(boxes[i].GetLeft(), boxes[i].GetTop()));
        }
        TRACE("player: %d!, box: %d\n", player_pos.size(), boxes_pos[0].size());
    }
    else
    {
        TRACE("undo > 20 !!\n");
        player_pos.erase(player_pos.begin());
        player_pos.push_back(std::make_pair(player.GetLeft(), player.GetTop()));
        for (int i = 0; i < boxes_amount[level - 1]; i++)
        {
            boxes_pos[i].erase(boxes_pos[i].begin());
            boxes_pos[i].push_back(std::make_pair(boxes[i].GetLeft(), boxes[i].GetTop()));
        }
        TRACE("player: %d!, box: %d\n", player_pos.size(), boxes_pos[0].size());
    }
}

void CGameStateRun::undo()
{
    if (player_pos.empty())
    {
        TRACE("cannot undo!!!\n");
        return;
    }

    TRACE("undo!!!\n");
    player.SetTopLeft(player_pos.back().first, player_pos.back().second);
    player_pos.pop_back();
    for (int i = 0; i < boxes_amount[level - 1]; i++)
    {
        boxes[i].SetTopLeft(boxes_pos[i].back().first, boxes_pos[i].back().second);
        boxes_pos[i].pop_back();
    }
    TRACE("player: %d!, box: %d\n", player_pos.size(), boxes_pos[0].size());
}

void CGameStateRun::draw_levels_text()
{
    CDC *pDC = CDDraw::GetBackCDC();
    // CFont *fp;

    /* Print title */

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (30 * page + i * 5 + j + 1 <= highestLevel)
            {
                string s;
                s = std::to_string(30 * page + i * 5 + j + 1);
                CTextDraw::ChangeFontLog(pDC, 34, "Forte", RGB(255, 255, 255));
                if (30 * page + i * 5 + j + 1 < 10)
                {
                    CTextDraw::Print(pDC, 54 + 100 * j, 217 + 100 * i, s);
                }
                else
                {
                    CTextDraw::Print(pDC, 46 + 100 * j, 217 + 100 * i, s);
                }
            }
        }
    }
    CDDraw::ReleaseBackCDC();
}

void CGameStateRun::draw_level(int n)
{
    CDC *pDC = CDDraw::GetBackCDC();
    // CFont *fp;

    /* Print title */

    string s = "LEVEL ";
    s += std::to_string(n);
    CTextDraw::ChangeFontLog(pDC, 38, "Forte", RGB(255, 255, 255));
    if (n < 10)
    {
        CTextDraw::Print(pDC, 190, 70, s);
    }
    else
    {
        CTextDraw::Print(pDC, 180, 70, s);
    }

    CDDraw::ReleaseBackCDC();
}

void CGameStateRun::sound_it()
{
    if (sound_flag == true)
    {
        audio->Play(2, 0);
    }
}