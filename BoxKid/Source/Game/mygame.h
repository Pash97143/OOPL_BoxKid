#include <vector>
/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 */

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID
	{				// 定義各種音效的編號
		AUDIO_DING, // 0
		AUDIO_LAKE, // 1
		AUDIO_NTUT	// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame *g);
		void OnInit();								   // 遊戲的初值及圖形設定
		void OnBeginState();						   // 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT);				   // 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
	protected:
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo; // csie的logo
		// CMovingBitmap background; // 背景圖
		void draw_text(); // 顯示文字
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState(); // 設定每次重玩所需的變數
		void OnInit();		 // 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);   // 處理滑鼠的動作
		void OnRButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);   // 處理滑鼠的動作

	protected:
		void OnMove();	   // 移動遊戲元素
		void OnShow();	   // 顯示這個狀態的遊戲畫面
		void setByLevel(); // 顯示不同關卡的畫面

	private:
		int level = -1;	   // 遊戲關卡
		int prelevel = -2; // 上一關的關卡
		int highestLevel = 1;
		CMovingBitmap background; // 背景圖

		// menu
		CMovingBitmap menu_play_text; // 開始鈕
		CMovingBitmap menu_voice;	  // 音效開關
		CMovingBitmap menu_music;	  // 背景音樂開關

		// level sheet
		CMovingBitmap level_select_text; // 選擇關卡的圖片
		CMovingBitmap level_to_menu;
		CMovingBitmap levels[70];

		// in the level
		vector<CMovingBitmap> walls;
		vector<CMovingBitmap> floors;
		vector<CMovingBitmap> goals;
		vector<CMovingBitmap> boxes;

		CMovingBitmap player;

		CMovingBitmap foot_control;

		CMovingBitmap foot_to_level;
		CMovingBitmap foot_undo;
		CMovingBitmap foot_restart;

		vector<int> walls_amount = {20, 22, 24, 30, 25};
		vector<int> floors_amount = {8, 19, 21, 23, 21};
		vector<int> boxes_amount = {1, 1, 2, 2, 2};
		vector<int> goals_amount = {1, 1, 2, 2, 2};


/*
0:empty
1:wall
2:floor
3:box
4:goal
5:box on goals
6:player
*/
		vector<vector<vector<int>>> walls_like = {{{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 1, 2, 2, 3, 2, 4, 1, 0}, {0, 1, 2, 2, 1, 1, 1, 1, 0}, {0, 1, 2, 6, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}},
												  {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 1, 2, 2, 6, 2, 2, 1, 0}, {0, 1, 2, 2, 2, 2, 2, 1, 0}, {0, 1, 2, 2, 2, 3, 4, 1, 0}, {0, 1, 2, 2, 2, 2, 2, 1, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 0}}};
	}; 

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		void OnBeginState(); // 設定每次重玩所需的變數
		void OnInit();

	protected:
		void OnMove(); // 移動遊戲元素
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		int counter; // 倒數之計數器
	};
}