#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

// ¹CÀ¸¿ïÃö

// void CGameStateRun::setByLevel()
// {
//     prelevel = level;
//     if (level < 1)
//     {
//         if (level == -1)
//         {
//             playIcon.LoadBitmap("resources/play.bmp", RGB(0, 0, 0));
//             playIcon.SetTopLeft(190, 450);
//             playIcon.ShowBitmap();
//         }
//         else if (level == 0)
//         {
//         }
//     }
//     else
//     {
//         walls.clear();
//         floors.clear();
//         goals.clear();
//         boxes.clear();

//         if (level == 1)
//         {
//             background.SelectShowBitmap(1);

//             player.LoadBitmapByString({"resources/player_left.bmp", "resources/player_up.bmp", "resources/player_right.bmp", "resources/player9.bmp"}, RGB(163, 73, 164));
//             player.SelectShowBitmap(3);
//             player.SetTopLeft(180, 480);

//             for (int i = 0; i < 20; i++)
//             {
//                 CMovingBitmap wall;
//                 wall.LoadBitmap("resources/wall.bmp", RGB(0, 0, 0));
//                 walls.push_back(wall);
//             }
//             for (int i = 0; i < 8; i++)
//             {
//                 CMovingBitmap floor;
//                 floor.LoadBitmap("resources/floor.bmp", RGB(0, 0, 0));
//                 floors.push_back(floor);
//             }
//             for (int i = 0; i < 1; i++)
//             {
//                 CMovingBitmap goal;
//                 goal.LoadBitmap("resources/goal.bmp", RGB(0, 0, 0));
//                 goals.push_back(goal);
//             }

//             for (int i = 0; i < 1; i++)
//             {
//                 CMovingBitmap box;
//                 box.LoadBitmapByString({"resources/box0.bmp", "resources/box1.bmp"}, RGB(0, 0, 0));
//                 boxes.push_back(box);
//             }

//             //------
//             Sleep(500);
//             //-------

//             boxes[0].SetTopLeft(240, 360);

//             for (int i = 0; i < 7; i++)
//             {
//                 walls[i].SetTopLeft(60 + i * 60, 300);
//             }
//             walls[7].SetTopLeft(60, 360);
//             walls[8].SetTopLeft(60, 420);
//             walls[9].SetTopLeft(60, 480);
//             walls[10].SetTopLeft(60, 540);
//             walls[11].SetTopLeft(120, 540);
//             walls[12].SetTopLeft(180, 540);
//             walls[13].SetTopLeft(240, 540);
//             walls[14].SetTopLeft(240, 480);
//             walls[15].SetTopLeft(240, 420);
//             walls[16].SetTopLeft(300, 420);
//             walls[17].SetTopLeft(360, 420);
//             walls[18].SetTopLeft(420, 420);
//             walls[19].SetTopLeft(420, 360);

//             floors[0].SetTopLeft(120, 360);
//             floors[1].SetTopLeft(180, 360);
//             floors[2].SetTopLeft(240, 360);
//             floors[3].SetTopLeft(300, 360);
//             floors[4].SetTopLeft(120, 420);
//             floors[5].SetTopLeft(180, 420);
//             floors[6].SetTopLeft(120, 480);
//             floors[7].SetTopLeft(180, 480);

//             goals[0].SetTopLeft(360, 360);
//         }
//         else if (level == 2)
//         {
//         }
//     }
// }
