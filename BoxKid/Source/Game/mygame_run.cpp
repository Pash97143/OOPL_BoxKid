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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
    background.LoadBitmapByString({"resources/background_level.bmp"}, RGB(0, 0, 0));
    background.SetTopLeft(0, 0);
}

void CGameStateRun::OnMove() // ���ʹC������
{
}

void CGameStateRun::OnInit() // �C������Ȥιϧγ]�w
{
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
    showByLevel();
}

void CGameStateRun::showByLevel()
{
    if (level == 1)
    {
        background.ShowBitmap();
        for (int i = 0; i < 20; i++)
        {
            CMovingBitmap wall;
            wall.LoadBitmap("resources/wall.bmp", RGB(0, 0, 0));
            walls.push_back(wall);
        }

        for (int i = 0; i < 7; i++)
        {
            walls[i].SetTopLeft(50 + i * 55, 350);
        }
        walls[7].SetTopLeft(50, 407);
        walls[8].SetTopLeft(50, 464);
        walls[9].SetTopLeft(50, 521);
        walls[10].SetTopLeft(50, 578);
        walls[11].SetTopLeft(105, 578);
        walls[12].SetTopLeft(160, 578);
        walls[13].SetTopLeft(215, 578);
        walls[14].SetTopLeft(215, 521);
        walls[15].SetTopLeft(215, 464);
        walls[16].SetTopLeft(270, 464);
        walls[17].SetTopLeft(325, 464);
        walls[18].SetTopLeft(380, 464);
        walls[19].SetTopLeft(380, 407);
        Sleep(200);
        for (int i = 0; i < 20; i++)
        {
            walls[i].ShowBitmap();
        }
    }
}
