// 333project.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "333project.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")



//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  g_pGame = new GameEngine(hInstance, TEXT("333project"),
    TEXT("333project"), IDI_ICON2, IDI_ICON1, 800, 700);
  if (g_pGame == NULL)
    return FALSE;

  // Set the frame rate
  g_pGame->SetFrameRate(30);

  // Store the instance handle
  g_hInstance = hInstance;

  return TRUE;
}

void GameStart(HWND hWindow)
{
  // Read the hi scores
  ReadHiScores();

  // Seed the random number generator
  srand(GetTickCount());

  // Create the offscreen device context and bitmap
  g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
    g_pGame->GetWidth(), g_pGame->GetHeight());
  SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

  // Create and load the bitmaps
  HDC hDC = GetDC(hWindow);
  //g_pSplashBitmap = new Bitmap(hDC, IDB_SPLASH, g_hInstance);
  //g_pDesertBitmap = new Bitmap(hDC, IDB_DESERT, g_hInstance);
  g_pPlayerBitmap[0] = new Bitmap(hDC, IDB_BITMAP1, g_hInstance);
  g_pPlayerBitmap[1] = new Bitmap(hDC, IDB_BITMAP2, g_hInstance);
  g_pPlayerBitmap[2] = new Bitmap(hDC, IDB_BITMAP3, g_hInstance);
  
  g_pPlayerHeadBitmap[0] = new Bitmap(hDC, IDB_BITMAP4, g_hInstance);
  g_pPlayerHeadBitmap[1] = new Bitmap(hDC, IDB_BITMAP5, g_hInstance);
  g_pPlayerHeadBitmap[2] = new Bitmap(hDC, IDB_BITMAP6, g_hInstance);

  g_pSCBitmap[0] = new Bitmap(hDC,IDB_BITMAP9,g_hInstance);
  g_pSCBitmap[1] = new Bitmap(hDC,IDB_BITMAP8,g_hInstance);
  g_pSCBitmap[2] = new Bitmap(hDC,IDB_BITMAP7,g_hInstance);

  g_pPlayer1BulletBitmap[0] = new Bitmap(hDC, IDB_BITMAP10, g_hInstance);
  g_pPlayer1BulletBitmap[1] = new Bitmap(hDC, IDB_BITMAP11, g_hInstance);
  g_pPlayer1BulletBitmap[2] = new Bitmap(hDC, IDB_BITMAP12, g_hInstance);
  g_pPlayer1BulletBitmap[3] = new Bitmap(hDC, IDB_BITMAP13, g_hInstance);
  g_pPlayer2BulletBitmap[0] = new Bitmap(hDC, IDB_BITMAP14, g_hInstance);
  g_pPlayer2BulletBitmap[1] = new Bitmap(hDC, IDB_BITMAP15, g_hInstance);
  g_pPlayer2BulletBitmap[2] = new Bitmap(hDC, IDB_BITMAP16, g_hInstance);
  g_pPlayer2BulletBitmap[3] = new Bitmap(hDC, IDB_BITMAP17, g_hInstance);
  g_pPlayer2BulletBitmap[4] = new Bitmap(hDC, IDB_BITMAP60, g_hInstance);
  g_pPlayer3BulletBitmap[0] = new Bitmap(hDC, IDB_BITMAP18, g_hInstance);
  g_pPlayer3BulletBitmap[1] = new Bitmap(hDC, IDB_BITMAP19, g_hInstance);
  g_pPlayer3BulletBitmap[2] = new Bitmap(hDC, IDB_BITMAP20, g_hInstance);
  g_pPlayer3BulletBitmap[3] = new Bitmap(hDC, IDB_BITMAP21, g_hInstance);

  //g_pEnemyBulletBitmap = new Bitmap(hDC, IDB_BITMAP7, g_hInstance);
  
  g_pCaonimaBitmap[0] = new Bitmap(hDC, IDB_BITMAP22, g_hInstance);
  g_pCaonimaBitmap[1] = new Bitmap(hDC, IDB_BITMAP23, g_hInstance);
  g_pCaonimaBitmap[2] = new Bitmap(hDC, IDB_BITMAP24, g_hInstance);
  g_pCaonimaBitmap[3] = new Bitmap(hDC, IDB_BITMAP25, g_hInstance);
  g_pDragonBitmap[0] = new Bitmap(hDC, IDB_BITMAP26, g_hInstance);
  g_pDragonBitmap[1] = new Bitmap(hDC, IDB_BITMAP27, g_hInstance);
  g_pDragonBitmap[2] = new Bitmap(hDC, IDB_BITMAP28, g_hInstance);
  g_pStoneBitmap[0] = new Bitmap(hDC, IDB_BITMAP29, g_hInstance);
  g_pStoneBitmap[1] = new Bitmap(hDC, IDB_BITMAP30, g_hInstance);
  g_pStoneBitmap[2] = new Bitmap(hDC, IDB_BITMAP31, g_hInstance);
  g_pStoneBitmap[3] = new Bitmap(hDC, IDB_BITMAP32, g_hInstance);
 

  g_pqq1Bitmap = new Bitmap(hDC, IDB_BITMAP33, g_hInstance);
  g_pqq2Bitmap = new Bitmap(hDC, IDB_BITMAP34, g_hInstance);
  g_pQQBitmap = new Bitmap(hDC, IDB_BITMAP35, g_hInstance);
  g_pBoom1Bitmap = new Bitmap(hDC, IDB_BITMAP36, g_hInstance);
  g_pBoom2Bitmap = new Bitmap(hDC, IDB_BITMAP37, g_hInstance);
  g_pBoom3Bitmap = new Bitmap(hDC, IDB_BITMAP38, g_hInstance);
  
  g_pGameOverBitmap = new Bitmap(hDC, IDB_BITMAP39, g_hInstance);
  
  g_pLoadingBitmap = new Bitmap(hDC,IDB_BITMAP40,g_hInstance);
  g_pWallPaperBitmap = new Bitmap(hDC,IDB_BITMAP41,g_hInstance);
  g_pLogoBitmap = new Bitmap(hDC, IDB_BITMAP61, g_hInstance);
  g_pTitleBitmap = new Bitmap(hDC,IDB_BITMAP62, g_hInstance);
  g_pChooseCharacterBitmap[0] = new Bitmap(hDC, IDB_BITMAP64, g_hInstance);
  g_pChooseCharacterBitmap[1] = new Bitmap(hDC, IDB_BITMAP65, g_hInstance);
  g_pChooseCharacterBitmap[2] = new Bitmap(hDC, IDB_BITMAP66, g_hInstance);

  g_pBackground1Bitmap=new Bitmap(hDC,IDB_BITMAP42,g_hInstance);
  g_pBackground2Bitmap=new Bitmap(hDC,IDB_BITMAP43,g_hInstance);
  g_pBackground3Bitmap=new Bitmap(hDC,IDB_BITMAP44,g_hInstance);

  g_pBoomPointBitmap=new Bitmap(hDC,IDB_BITMAP45,g_hInstance);
  g_pPointBitmap=new Bitmap(hDC,IDB_BITMAP46,g_hInstance);
  
  g_pPlayer1SCBitmap = new Bitmap(hDC,IDB_BITMAP47,g_hInstance);
  g_pPlayer2SCBitmap[0]=new Bitmap(hDC,IDB_BITMAP48,g_hInstance);
  g_pPlayer2SCBitmap[1]=new Bitmap(hDC,IDB_BITMAP49,g_hInstance);
  g_pPlayer2SCBitmap[2]=new Bitmap(hDC,IDB_BITMAP50,g_hInstance);
  g_pPlayer2SCBitmap[3]=new Bitmap(hDC,IDB_BITMAP51,g_hInstance);
  g_pPlayer2SCBitmap[4]=new Bitmap(hDC,IDB_BITMAP52,g_hInstance);
  g_pPlayer2SCBitmap[5]=new Bitmap(hDC,IDB_BITMAP53,g_hInstance);
  g_pPlayer3SCBitmap=new Bitmap(hDC,IDB_BITMAP54,g_hInstance);

  g_pEnemyBulletBitmap[0]= new Bitmap(hDC,IDB_BITMAP55,g_hInstance);
  g_pEnemyBulletBitmap[1]= new Bitmap(hDC,IDB_BITMAP56,g_hInstance);
  g_pEnemyBulletBitmap[2]= new Bitmap(hDC,IDB_BITMAP57,g_hInstance);
  g_pEnemyBulletBitmap[3]= new Bitmap(hDC,IDB_BITMAP58,g_hInstance);
  g_pEnemyBulletBitmap[4]= new Bitmap(hDC,IDB_BITMAP59,g_hInstance);

  g_pBossHpBitmap1 = new Bitmap(hDC, IDB_BITMAP67, g_hInstance);
  g_pBossHpBitmap2 = new Bitmap(hDC, IDB_BITMAP68, g_hInstance);

  g_pWallBitmap = new Bitmap(hDC,IDB_BITMAP69,g_hInstance);
  g_pGameEndingBitmap = new Bitmap(hDC, IDB_BITMAP70, g_hInstance);
  g_pGameLogoBitmap = new Bitmap(hDC,IDB_BITMAP71, g_hInstance);


  g_bSmall=false;
  // Create the starry background
  g_pBackground1 = new Background(g_pBackground1Bitmap);
  g_pBackground1->SetNumFrames(9);
  g_pBackground1->SetFrameDelay(2);
  g_pBackground2 = new Background(g_pBackground2Bitmap);
  g_pBackground2->SetNumFrames(19);
  g_pBackground2->SetFrameDelay(1);
  g_pBackground3 = new Background(g_pBackground3Bitmap);
  g_pBackground3->SetNumFrames(18);
  g_pBackground3->SetFrameDelay(2);
  g_iPlayerNum=0;
  g_iSpellCard=2;
  g_tInputDelay=0;
  g_bStage1 = false;
  g_bStage2 = false;
  g_bStage3 = false;
  g_bLogo = false;
  g_dPowerLimit = 3.9;
  g_iLogoFrame = 0;
  g_tAddEnemyDelay=0;
  // Start the game for demo mode
  g_iGameStart=0;
  g_bDemo = TRUE;
  NewGame();
}

void GameEnd()
{
  // Close the MIDI player for the background music
  g_pGame->CloseMIDIPlayer();

  // Cleanup the offscreen device context and bitmap
  DeleteObject(g_hOffscreenBitmap);
  DeleteDC(g_hOffscreenDC);  

  // Cleanup the bitmaps
  //delete g_pSplashBitmap;
  //delete g_pDesertBitmap;
  for(int i=0;i<3;++i)
  {
	  delete g_pPlayerBitmap[i];
	  delete g_pPlayerHeadBitmap[i];
	  delete g_pSCBitmap[i];
	  delete g_pDragonBitmap[i];
  }
  for(int i=0;i<4;++i)
  {
	  delete g_pPlayer1BulletBitmap[i];
	  delete g_pPlayer3BulletBitmap[i];
	  delete g_pCaonimaBitmap[i];
	  delete g_pStoneBitmap[i];
  }
  for(int i=0;i<5;++i)
  {
	  delete g_pEnemyBulletBitmap[i];
	  delete g_pPlayer2BulletBitmap[i];
  }
  delete g_pPlayer1SCBitmap;
  delete g_pPlayer3SCBitmap;
  for(int i=0;i<6;++i)
  {
	  delete g_pPlayer2SCBitmap[i];
  }
delete g_pqq1Bitmap;
delete g_pqq2Bitmap;
delete g_pQQBitmap;
delete g_pBoom1Bitmap;
delete g_pBoom2Bitmap;
delete g_pBoom3Bitmap;


delete g_pWallPaperBitmap;
delete g_pLoadingBitmap;
delete g_pStartBitmap;
delete g_pTitleBitmap;
delete g_pLogoBitmap;

delete g_pGameOverBitmap;
delete g_pBackground1;
delete g_pBackground2;
delete g_pBackground3;

delete g_pPointBitmap;
delete g_pBoomPointBitmap;

 for(int i=0;i<3;++i)
 {
	 delete g_pChooseCharacterBitmap[i];
 }


  // Cleanup the sprites
  g_pGame->CleanupSprites();

  // Cleanup the game engine
  delete g_pGame;

  // Save the hi scores
  WriteHiScores();
}

void GameActivate(HWND hWindow)
{
  if (!g_bDemo)
    // Resume the background music
    g_pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
  if (!g_bDemo)
    // Pause the background music
    g_pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{
	if(g_bLogo == true)
	{
		if (g_bDemo)
		{
		  if(g_iGameStart==0 && g_bGameOver == false)
		  {
			  g_pTitleBitmap->Draw(hDC,0,0,false);
		  }
		  else if(g_iGameStart == 1)
		  {
			  if(g_iPlayerNum==0)
			  {
				  g_pChooseCharacterBitmap[0]->Draw(hDC,0,0,false);
			  }
			  else if(g_iPlayerNum == 1)
			  {
				  g_pChooseCharacterBitmap[1]->Draw(hDC,0,0,false);
			  }
			  else if(g_iPlayerNum == 2)
			  {
				  g_pChooseCharacterBitmap[2]->Draw(hDC,0,0,false);
			  }
		  
		  }
	  }
	  else
	  {

		if(g_iBackground == 1)
		{
			g_pBackground1->Draw(hDC);
		}
		else if(g_iBackground == 2)
		{
			g_pBackground2->Draw(hDC);
		}
		else if(g_iBackground == 3)
		{
			g_pBackground3->Draw(hDC);
		}
 

		  // Draw the sprites
		g_pGame->DrawSprites(hDC);
		g_pWallPaperBitmap->Draw(hDC,0,0,true);
		// Draw the score
		TCHAR szText[64];
		RECT  rect = { 600, 0, 700, 100 };
		wsprintf(szText, L"%d", g_iScore);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		TCHAR szText1[64];
		RECT rect1 = { 600, 200, 700, 250 };
		swprintf(szText1, L"%4.2f", g_dPower);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText1, -1, &rect1, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
	
		/*RECT rect1 = { 650, 25, 700, 175 };
		wsprintf(szText,L"%d",g_iHiScores);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect1, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);*/

		// Draw the number of remaining lives
		for (int i = 0; i < g_iNumLives; i++)
		  g_pPlayerHeadBitmap[g_iPlayerNum]->Draw(hDC, 650 + (g_pPlayerHeadBitmap[g_iPlayerNum]->GetWidth() * i)+3,
			100, TRUE);
		for(int i=0;i<g_iSpellCard;i++)
			g_pSCBitmap[g_iPlayerNum]->Draw(hDC, 650 + (g_pSCBitmap[g_iSCNum]->GetWidth() * i)+3,  150, TRUE);

	  }
		// Draw the game over message, if necessary
		if (g_bGameOver == true && g_bGoodEnd == false)
		  g_pGameOverBitmap->Draw(hDC, 0, 0, false);
		else if(g_bGameOver == true && g_bGoodEnd == true)
		{
			if((time(0)-g_tStartTime)*20<3332)
			 g_pGameEndingBitmap->DrawPart(hDC, 0, 0,
					0, (time(0)-g_tStartTime)*20, 800, 700, TRUE);
			else
			{
				g_pGameEndingBitmap->DrawPart(hDC, 0, 0,
					0, 3332, 800, 700, TRUE);
			}
		}
	}
	else
	{
		if(++g_iFireInputDelay>2)
		{
			if(++g_iLogoFrame<31)
				g_pGameLogoBitmap->DrawPart(hDC, 0, 0,
					g_iLogoFrame*800, 0, 800, 700, TRUE);
			else
			{
					g_bLogo = true;
					g_pGame->CloseMIDIPlayer();
					g_pGame->PlayMIDISong(TEXT("Music.wav"),true);
			}
			g_iFireInputDelay=0;
		}
		
			
	}
  
  
}

void GameCycle()
{
 if(g_bLogo == true)
 {
	 if(g_iScore>g_iNumLivesDelay)
	 {
		 g_iNumLives++;
		 g_iNumLivesDelay=g_iNumLivesDelay+4000;
	 }
  g_tTime=time(0);
  if(g_tTime-g_tStageDelay==9)
  {
	  if(g_bStage1 == false)
	  {
		  g_bStage1=true;
		  g_tStageDelay=0;
		  g_tStartTime = time(0);
	  }
	  else if(g_bStage2 == false)
	  {
		  g_bStage2=true;
		  g_tStageDelay=0;
		  g_tStartTime = time(0);
	  }
	  else if(g_bStage3 == false)
	  {
		  g_bStage3=true;
		  g_tStageDelay=0;
		  g_tStartTime = time(0);
		  g_bGoodEnd = true;
		  g_bGameOver = true;
		  g_pGame->CloseMIDIPlayer();
	      g_pGame->PlayMIDISong(TEXT("ending.wav"),true);
	  }
  }
  
  if (!g_bGameOver)
  {
    if (!g_bDemo)
	{
			if(g_tTime-g_tGoldTime >2 && g_tGoldTime != 0)
			{
				g_pPlayer[g_iPlayerNum]->SetFrames(0);
				g_bGoldbody=false;
				g_tGoldTime=0;
			}
			if(!g_bStage1)
			{
				stage1();
			}
			else if(!g_bStage2)
			{
				stage2();
			}
			else if(!g_bStage3)
			{
				stage3();
			}
		}

		// Update the background
		if(g_iBackground == 1)
		{
			g_pBackground1->Update();
		}
		else if(g_iBackground == 2)
		{
			g_pBackground2->Update();
		}
		else if(g_iBackground == 3)
		{
			g_pBackground3->Update();
		}
    
	
		// Update the sprites
		g_pGame->UpdateSprites();

		// Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		// Paint the game to the offscreen device context
		GamePaint(g_hOffscreenDC);


		// Blit the offscreen bitmap to the game screen
		BitBlt(hDC, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight(),
		  g_hOffscreenDC, 0, 0, SRCCOPY);

		// Cleanup
		ReleaseDC(hWindow, hDC);
	  }
	  else if(g_bGameOver == true && g_bGoodEnd == true)
	  {
			  // Obtain a device context for repainting the game
		HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		// Paint the game to the offscreen device context
		GamePaint(g_hOffscreenDC);


		// Blit the offscreen bitmap to the game screen
		BitBlt(hDC, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight(),
		  g_hOffscreenDC, 0, 0, SRCCOPY);

		// Cleanup
		ReleaseDC(hWindow, hDC);
	  }
	 // else 
		//if (--g_iGameOverDelay == 0)
	 //   {
	 //     // Stop the music and switch to demo mode
	 //     g_pGame->PauseMIDISong();
	 //     g_bDemo = TRUE;
	 //     NewGame();
	 //   }
  }
  else
  {
	    HWND  hWindow = g_pGame->GetWindow();
		HDC   hDC = GetDC(hWindow);

		// Paint the game to the offscreen device context
		GamePaint(g_hOffscreenDC);


		// Blit the offscreen bitmap to the game screen
		BitBlt(hDC, 0, 0, g_pGame->GetWidth(), g_pGame->GetHeight(),
		  g_hOffscreenDC, 0, 0, SRCCOPY);

		// Cleanup
		ReleaseDC(hWindow, hDC);
  }
}

void HandleKeys()
{
  int x,y;
  if (!g_bGameOver && !g_bDemo)
  {
	  if(GetAsyncKeyState(VK_SHIFT)<0 && g_bGoldbody == false )
	  {
		  g_bSmall=true;
		  g_pPlayer[g_iPlayerNum]->SetFrames(1);
	  }
	  else if(g_bGoldbody == false )
	  {
		  g_bSmall=false;
		  g_pPlayer[g_iPlayerNum]->SetFrames(0);
	  }


	  if(g_iPlayerNum==0)
	  {
		  if(g_bSmall)
		  {
				if (GetAsyncKeyState(VK_LEFT) <0)
					x=-6;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=6;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-6;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=6;
				else
					y=0;
				MovePlayer(x, y);
		  }
		  else
		  {
		  		if (GetAsyncKeyState(VK_LEFT) <0)
					x=-13;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=13;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-13;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=13;
				else
					y=0;
				MovePlayer(x, y);
		  }
	  }
	  else if(g_iPlayerNum==1)
	  {

		  if(g_bSmall)
		  {
				if (GetAsyncKeyState(VK_LEFT) <0)
					x=-8;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=8;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-8;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=8;
				else
					y=0;
				MovePlayer(x, y);
		  }
		  else
		  {
		  		if (GetAsyncKeyState(VK_LEFT) <0)
					x=-16;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=16;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-16;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=16;
				else
					y=0;
				MovePlayer(x, y);
		  }
	  }
	  else if(g_iPlayerNum == 2)
	  {
		  if(g_bSmall)
		  {
				if (GetAsyncKeyState(VK_LEFT) <0)
					x=-7;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=7;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-7;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=7;
				else
					y=0;
				MovePlayer(x, y);
		  }
		  else
		  {
		  		if (GetAsyncKeyState(VK_LEFT) <0)
					x=-14;
				else if (GetAsyncKeyState(VK_RIGHT) <0)
					x=14;
				else
					x=0;
				if (GetAsyncKeyState(VK_UP) <0)
					y=-14;
				else if (GetAsyncKeyState(VK_DOWN) <0)
					y=14;
				else
					y=0;
				MovePlayer(x, y);
		  }
	  }
	  
	  //sc
	  if((GetAsyncKeyState(0x58)<0)&&(g_iSpellCard>0)&& g_bGoldbody == false)
	  {
		  PlaySound((LPCWSTR)IDR_WAVE6, g_hInstance, SND_ASYNC |
			SND_RESOURCE);
		  if(g_iPlayerNum == 0)
		  {
			  SC1();
		  }
		  else if(g_iPlayerNum == 1)
		  {
			  SC2();
		  }
		  else if(g_iPlayerNum == 2)
		  {
			  SC3();
		  }
		  g_iSpellCard--;
	  }
    // Fire
    if ((++g_iFireInputDelay > g_iFireTrigger) && GetAsyncKeyState(0x5a) < 0 && GetAsyncKeyState(VK_SHIFT)<0 )
    {
		if(g_iPlayerNum == 0)
		{
			slowfire1();
		}
		else if(g_iPlayerNum == 1)
		{
			slowfire2();
		}
		else if(g_iPlayerNum == 2)
		{
			slowfire3();
		}
		if(g_bGoldbody == false)
			PlaySound((LPCWSTR)IDR_WAVE5, g_hInstance, SND_ASYNC |
			SND_RESOURCE);

     // // Reset the input delay
      g_iFireInputDelay = 0;
	
    }
	else if((++g_iFireInputDelay > g_iFireTrigger) && GetAsyncKeyState(0x5a) < 0)
	{
		if(g_bGoldbody == false)
			PlaySound((LPCWSTR)IDR_WAVE5, g_hInstance, SND_ASYNC |
			SND_RESOURCE);
		if(g_iPlayerNum == 0)
		{
			fire1();
		}
		else if(g_iPlayerNum == 1)
		{
			fire2();
		}
		else if(g_iPlayerNum == 2)
		{
			fire3();
		}
		g_iFireInputDelay = 0;
	}


  }
  if(g_bDemo==true && g_bGameOver==false)
  {
	  if(g_iGameStart == 1)
	  {
		  if(GetAsyncKeyState(VK_UP)<0  && clock()-g_tInputDelay >600)
		  {
			  PlaySound((LPCWSTR)IDR_WAVE2, g_hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);
			  if(--g_iPlayerNum<0)
			  {
				  g_iPlayerNum=2;
			  }
			  g_iSpellCard=2+g_iPlayerNum;
			  if(g_iPlayerNum == 2)
			  {
				  g_dPowerLimit=7.9;
			  }
			  else
			  {
				  g_dPowerLimit=3.9;
			  }
			  g_tInputDelay=clock();
		  }
		  else if(GetAsyncKeyState(VK_DOWN)<0 && clock()-g_tInputDelay >600)
		  {
			  PlaySound((LPCWSTR)IDR_WAVE2, g_hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);
			  if(++g_iPlayerNum>2)
			  {
				  g_iPlayerNum=0;
			  }
			  g_iSpellCard=2+g_iPlayerNum;
			  if(g_iPlayerNum == 2)
			  {
				  g_dPowerLimit=7.9;
			  }
			  else
			  {
				  g_dPowerLimit=3.9;
			  }
			  g_tInputDelay=clock();
		  }
	  }
  }
  // Start a new game based upon an Enter (Return) key press
  if ((GetAsyncKeyState(VK_RETURN) < 0 || GetAsyncKeyState(0x5a)<0) && clock()-g_tInputDelay >600)
    if (g_bDemo==true && g_bGameOver==false)
    {
		PlaySound((LPCWSTR)IDR_WAVE2, g_hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);
		if(g_iGameStart == 0)
		{
			g_iGameStart = 1;
		}
		else if(g_iGameStart == 1)
		{
			g_bDemo = FALSE;
			g_pGame->PauseMIDISong();
			NewGame();
		}
		g_tInputDelay=clock();
      // Switch out of demo mode to start a new game
    }
    else if (g_bGameOver && clock()-g_tGameOverDelay>1000)
    {
		g_iGameStart=0;
      // Start a new game
		g_bDemo = true;
		g_bGameOver=false;
        NewGame();
    }
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
  
  SPRITEATTRIBUTE satHitter = pSpriteHitter->GetSpriteAttribute();
  SPRITEATTRIBUTE satHittee = pSpriteHittee->GetSpriteAttribute();
  Bitmap* pHitter = pSpriteHitter->GetBitmap();
  Bitmap* pHittee = pSpriteHittee->GetBitmap();
  //something->wall
  {
	  if((satHitter == SAT_ENEMYBULLET || satHitter == SAT_ENEMY)&& satHittee == SAT_WALL)
	  {
		  pSpriteHitter->Kill();
	  }
  }
  //sc -> enemybullet
  if ( (satHitter == SAT_SC) && 
	   (satHittee == SAT_ENEMYBULLET ))
  {
	  pSpriteHittee->Kill();
  }

  //enemy||enemybullet -> player
  if((satHitter == SAT_ENEMY || satHitter == SAT_ENEMYBULLET) && satHittee == SAT_PLAYER && g_bGoldbody == false && g_bGoodEnd == false)
  {
	g_pPlayer[g_iPlayerNum]->SetPosition(200, 625);
	g_tGoldTime=time(0);
	g_bGoldbody = true;
	g_pPlayer[g_iPlayerNum]->SetFrames(2);
	PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
        SND_RESOURCE);
	g_iSpellCard=2+g_iPlayerNum;
	if(--g_dPower<0)
	{
		g_dPower=0;
	}
	for(int i=0;i<10;++i)
	{
		RECT rcBounds = { 25, 25, 525, 675 };
		RECT rcPos;
		rcPos = pSpriteHittee->GetPosition();
		Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
		pSprite->SetSpriteAttribute(SAT_POINT);
		pSprite->SetNumFrames(1);
		pSprite->SetPosition(100+i*15, 300-i*10);
		pSprite->SetScore(10);
		pSprite->SetVelocity(0,4);
		g_pGame->AddSprite(pSprite);
	}
	for(int i=0;i<10;++i)
	{
		RECT rcBounds = { 25, 25, 525, 675 };
		RECT rcPos;
		rcPos = pSpriteHittee->GetPosition();
		Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
		pSprite->SetSpriteAttribute(SAT_POINT);
		pSprite->SetNumFrames(1);
		pSprite->SetPosition(250+i*15, 200+i*10);
		pSprite->SetScore(10);
		pSprite->SetVelocity(0,4);
		g_pGame->AddSprite(pSprite);
	}
    // See if the game is over
    if (--g_iNumLives == 0)
    {
      // Play the game over sound
     // PlaySound((LPCSTR)IDW_GAMEOVER, g_hInstance, SND_ASYNC |
       // SND_RESOURCE);
	  g_pGame->CloseMIDIPlayer();

	  g_iGameStart=0;

      g_bGameOver = true;
	  g_bDemo=true;
	  g_tGameOverDelay = clock();
      // Update the hi scores
      UpdateHiScores();
    }
  }
  	 
  //playerbullet->enemy
  if (satHitter == SAT_PLAYERBULLET && satHittee == SAT_ENEMY )
  {
    // Play the small explosion sound
    // PlaySound((LPCSTR)IDW_LGEXPLODE, g_hInstance, SND_ASYNC |
    // SND_RESOURCE);
	 
	  if((pHitter == g_pPlayer3BulletBitmap[0] ||
		  pHitter == g_pPlayer3BulletBitmap[1] ||
		  pHitter == g_pPlayer3BulletBitmap[2] ||
		  pHitter == g_pPlayer3BulletBitmap[3]) &&
		  (pHittee ==g_pqq1Bitmap ||
		   pHittee ==g_pqq2Bitmap) )
	  {
		  
	  }
	  else
	  {
		  pSpriteHitter->Kill();
	  }
    
    //pSpriteHittee->Kill();
	if(pHitter == g_pPlayer1BulletBitmap[0] || 
		pHitter == g_pPlayer1BulletBitmap[1] ||
		pHitter == g_pPlayer1BulletBitmap[2] ||
		pHitter == g_pPlayer1BulletBitmap[3])
	{
		pSpriteHittee->SufferDamage(1);
	}
	else if(pHitter == g_pPlayer2BulletBitmap[4])
	{
		pSpriteHittee->SufferDamage(g_dPower+1+9);
	}
	else if(pHitter == g_pPlayer3BulletBitmap[0] || 
		pHitter == g_pPlayer3BulletBitmap[1] ||
		pHitter == g_pPlayer3BulletBitmap[2] ||
		pHitter == g_pPlayer3BulletBitmap[3])
	{
		pSpriteHittee->SufferDamage((g_dPower+1)*2);
	}
	else
	{
		pSpriteHittee->SufferDamage(g_dPower+1);
	}
	
	if(pSpriteHittee->DamageEnough())
	{
		
		if(pSpriteHittee->GetDying()==false)
		{
			if(pHittee!=g_pqq1Bitmap || pHittee != g_pqq2Bitmap)
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pBoom1Bitmap, rcBounds,true);
				pSprite->SetSpriteAttribute(SAT_BOOM);
				pSprite->SetNumFrames(5, TRUE);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				g_pGame->AddSprite(pSprite);
			}
			if(pHittee == g_pqq1Bitmap || pHittee == g_pqq2Bitmap)
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
				pSprite->SetSpriteAttribute(SAT_POINT);
				pSprite->SetNumFrames(1);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				pSprite->SetScore(10);
				pSprite->SetVelocity(0,3);
				g_pGame->AddSprite(pSprite);
			}
			else if(pHittee == g_pCaonimaBitmap[0] ||
					pHittee == g_pCaonimaBitmap[1] ||
					pHittee == g_pDragonBitmap[0] ||
					pHittee == g_pStoneBitmap[0] ||
					pHittee == g_pStoneBitmap[1] ||
					pHittee == g_pStoneBitmap[2])
			{
				for(int i=0;i<20;++i)
				{
					RECT rcBounds = { 25, 25, 525, 675 };
					RECT rcPos;
					rcPos = pSpriteHittee->GetPosition();
					Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
					pSprite->SetSpriteAttribute(SAT_POINT);
					pSprite->SetNumFrames(1);
					pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2+rand()%40-80, rcPos.top+pSpriteHittee->GetHeight()/2+rand()%40-80);
					pSprite->SetScore(10);
					pSprite->SetVelocity(0,4);
					g_pGame->AddSprite(pSprite);
				}
			}
			else if(pHittee == g_pCaonimaBitmap[2] ||
					pHittee == g_pDragonBitmap[1] ||
					pHittee == g_pStoneBitmap[3])
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pBoomPointBitmap, rcBounds,BA_DIE);
				pSprite->SetSpriteAttribute(SAT_POINT);
				pSprite->SetNumFrames(1);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				pSprite->SetScore(20);
				pSprite->SetVelocity(0,5);
				g_pGame->AddSprite(pSprite);
			}

			// Update the score
			g_iScore+=pSpriteHittee->GetScore();
		}
		pSpriteHittee->Kill();
	}
 
  }
  //SC->ENEMY
  if(satHitter == SAT_SC && satHittee == SAT_ENEMY)
  {
	
		if(pSpriteHittee->GetDying()==false)
		{
			if(pHittee!=g_pqq1Bitmap || pHittee != g_pqq2Bitmap)
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pBoom1Bitmap, rcBounds,true);
				pSprite->SetSpriteAttribute(SAT_BOOM);
				pSprite->SetNumFrames(5, TRUE);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				g_pGame->AddSprite(pSprite);
			}
			if(pHittee == g_pqq1Bitmap || pHittee == g_pqq2Bitmap)
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
				pSprite->SetSpriteAttribute(SAT_POINT);
				pSprite->SetNumFrames(1);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				pSprite->SetScore(10);
				pSprite->SetVelocity(0,3);
				g_pGame->AddSprite(pSprite);
			}
			else if(pHittee == g_pCaonimaBitmap[0] ||
					pHittee == g_pCaonimaBitmap[1] ||
					pHittee == g_pDragonBitmap[0] ||
					pHittee == g_pStoneBitmap[0] ||
					pHittee == g_pStoneBitmap[1] ||
					pHittee == g_pStoneBitmap[2])
			{
				for(int i=0;i<20;++i)
				{
					RECT rcBounds = { 25, 25, 525, 675 };
					RECT rcPos;
					rcPos = pSpriteHittee->GetPosition();
					Sprite* pSprite = new Sprite(g_pPointBitmap, rcBounds,BA_DIE);
					pSprite->SetSpriteAttribute(SAT_POINT);
					pSprite->SetNumFrames(1);
					pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2+rand()%40-80, rcPos.top+pSpriteHittee->GetHeight()/2+rand()%40-80);
					pSprite->SetScore(10);
					pSprite->SetVelocity(0,4);
					g_pGame->AddSprite(pSprite);
				}
			}
			else if(pHittee == g_pCaonimaBitmap[2] ||
					pHittee == g_pDragonBitmap[1] ||
					pHittee == g_pStoneBitmap[3])
			{
				RECT rcBounds = { 25, 25, 525, 675 };
				RECT rcPos;
				rcPos = pSpriteHittee->GetPosition();
				Sprite* pSprite = new Sprite(g_pBoomPointBitmap, rcBounds,BA_DIE);
				pSprite->SetSpriteAttribute(SAT_POINT);
				pSprite->SetNumFrames(1);
				pSprite->SetPosition(rcPos.left+pSpriteHittee->GetWidth()/2, rcPos.top+pSpriteHittee->GetHeight()/2);
				pSprite->SetScore(20);
				pSprite->SetVelocity(0,5);
				g_pGame->AddSprite(pSprite);
			}

			// Update the score
			g_iScore+=pSpriteHittee->GetScore();
		}
		pSpriteHittee->Kill();
  }
  //player->point
  if(satHitter == SAT_PLAYER && satHittee == SAT_POINT)
  {
	  pSpriteHittee->Kill();
	  g_iScore+=pSpriteHittee->GetScore();
	  if(pHittee == g_pPointBitmap && g_dPower<g_dPowerLimit)
	  {
		  g_dPower+=0.05;
		  if(g_dPower>g_dPowerLimit)
		  {
			  g_dPower=g_dPowerLimit;
		  }
	  }
	  else if(pHittee == g_pBoomPointBitmap)
	  {
		  g_iSpellCard+=1;
	  }
  }
  //SC->BOSS
  if(satHitter == SAT_SC && satHittee == SAT_BOSS)
  {
	pSpriteHittee->SufferDamage(g_dPower * 5+50);
	pSpriteHitter->Kill();
	if(pSpriteHittee->DamageEnough())
	{
		pSpriteHittee->Kill();
		g_tStageDelay=time(0);

		RECT rcBounds = { 25, 25, 525, 675 };
		RECT rcPos;
		rcPos = pSpriteHitter->GetPosition();
		Sprite* pSprite = new Sprite(g_pBoom3Bitmap, rcBounds,true);
		pSprite->SetNumFrames(16, TRUE);
		pSprite->SetSpriteAttribute(SAT_BOOM);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		g_pGame->AddSprite(pSprite);

		// Update the score
		g_iScore+=pSpriteHittee->GetScore();

		if(g_tStageDelay != 0)
		{
			g_pGame->CloseMIDIPlayer();
			g_pGame->PlayMIDISong(TEXT("CarryOut.wav"),true);
		}
		if(pHittee == g_pQQBitmap)
		{
			g_bGoodEnd = true;
		}
	}
  }
  //playerbullet->boss
  if(satHitter == SAT_PLAYERBULLET && satHittee == SAT_BOSS )
  {
	  pSpriteHitter->Kill();
	if(pHitter == g_pPlayer1BulletBitmap[0] || 
		pHitter == g_pPlayer1BulletBitmap[1] ||
		pHitter == g_pPlayer1BulletBitmap[2] ||
		pHitter == g_pPlayer1BulletBitmap[3])
	{
		pSpriteHittee->SufferDamage(1);
	}
	else if(pHitter == g_pPlayer2BulletBitmap[4])
	{
		pSpriteHittee->SufferDamage(g_dPower+1+9);
	}
	else if(pHitter == g_pPlayer3BulletBitmap[0] || 
		pHitter == g_pPlayer3BulletBitmap[1] ||
		pHitter == g_pPlayer3BulletBitmap[2] ||
		pHitter == g_pPlayer3BulletBitmap[3])
	{
		pSpriteHittee->SufferDamage(g_dPower*2);
	}
	else
	{
		pSpriteHittee->SufferDamage(g_dPower+2);
	}
	if(pSpriteHittee->DamageEnough())
	{
		g_tStageDelay=time(0);
		pSpriteHittee->Kill();

		RECT rcBounds = { 25, 25, 525, 675 };
		RECT rcPos;
		rcPos = pSpriteHitter->GetPosition();
		Sprite* pSprite = new Sprite(g_pBoom3Bitmap, rcBounds,true);
		pSprite->SetNumFrames(16, TRUE);
		pSprite->SetSpriteAttribute(SAT_BOOM);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		g_pGame->AddSprite(pSprite);

		// Update the score
		g_iScore+=pSpriteHittee->GetScore();

		if(g_tStageDelay != 0)
		{
			g_pGame->CloseMIDIPlayer();
			g_pGame->PlayMIDISong(TEXT("CarryOut.wav"),true);
		}
		if(pHittee == g_pQQBitmap)
		{
			g_bGoodEnd = true;
		}
	}
  }
  return false;
}



void SpriteDying(Sprite* pSpriteDying)
{
  
 
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
  // Clear the sprites
  g_pGame->CleanupSprites();

  // Initialize the game variables
  g_iFireInputDelay = 0;
  
  g_bSmall=false;
  
  g_bGameOver = FALSE;
  g_iBackground=1;
  
  g_dPower=0.0;
  g_tStartTime = time(0);
  g_tGoldTime = 0;
  g_bGoldbody=false;
  g_iGameStart=0;
  g_bGoodEnd=false;
  g_tGameOverDelay = 0;
  g_tStageDelay = 0;
  g_iSpellCard=2;
  g_tInputDelay=0;
  g_bStage1 = false;
  g_bStage2 = false;
  g_bStage3 = false;
  if(g_iPlayerNum == 2)
  {
	  g_dPowerLimit = 7.9;
  }
  else
  {
	  g_dPowerLimit = 3.9;
  }
  
  g_tAddEnemyDelay=0;

  RECT rcBounds = { 0, 0, 550, 700 };
  g_pPlayer[g_iPlayerNum] = new Player(g_pPlayerBitmap[g_iPlayerNum], rcBounds, BA_STOP);
  g_pPlayer[g_iPlayerNum]->SetPosition(200, 625);
  g_pPlayer[g_iPlayerNum]->SetNumFrames(3,false);
  g_pPlayer[g_iPlayerNum]->SetFrames(0);
  g_pPlayer[g_iPlayerNum]->SetSpriteAttribute(SAT_PLAYER);
  g_pGame->AddSprite(g_pPlayer[g_iPlayerNum]);
  if(g_bLogo == true && g_bDemo)
  {
	  g_pGame->CloseMIDIPlayer();
	  g_pGame->PlayMIDISong(TEXT("Music.wav"),true);
  }
  if (g_bDemo)
  {
	 
	  //PlaySound((LPCWSTR)IDR_WAVE1, g_hInstance, SND_ASYNC |
        //SND_RESOURCE | SND_NOSTOP);
	  g_iNumLives = 3;
	  g_iScore = 0;
	  g_iNumLivesDelay=2000;
  }
  else
  {
	g_tStartTime = time(0);
	g_iFireTrigger =4+g_iPlayerNum*4;

	if(g_bStage1==false)
	{
		if(g_iPlayerNum==2)
			g_iNumLives+=99;
		g_pGame->CloseMIDIPlayer();
		g_pGame->PlayMIDISong(TEXT("Music1.wav"),true);

		
	}
	else if(g_bStage2 == false)
	{
		g_iBackground=2;
		g_pGame->CloseMIDIPlayer();
		g_pGame->PlayMIDISong(TEXT("Music2.wav"),true);


		g_pPlayer[g_iPlayerNum]->SetPosition(275, 625);
	
	}
	else if(g_bStage3 == false)
	{
		g_iBackground=3;
		g_pGame->CloseMIDIPlayer();
		g_pGame->PlayMIDISong(TEXT("Music3.wav"),true);

		g_pPlayer[g_iPlayerNum]->SetPosition(275, 625);
		
	}
	 
  }
}


void UpdateHiScores()
{

    if (g_iScore > g_iHiScores)
		g_iHiScores=g_iScore;   
  
}

BOOL ReadHiScores()
{
  // Open the hi score file (HiScores.dat)
  HANDLE hFile = CreateFile(TEXT("HiScores.dat"), GENERIC_READ, 0, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    // The hi score file doesn't exist, so initialize the scores to 0
      g_iHiScores = 0;
    return FALSE;
  }

 

    // Read the score
    char  cData[6];
    DWORD dwBytesRead;
    if (!ReadFile(hFile, &cData, 5, &dwBytesRead, NULL))
    {
      // Something went wrong, so close the file handle
      CloseHandle(hFile);
      return FALSE;
    }

    // Extract each integer score from the score data
    g_iHiScores = atoi(cData);


  // Close the file
  return CloseHandle(hFile);
}

BOOL WriteHiScores()
{
  // Create the hi score file (HiScores.dat) for writing
  HANDLE hFile = CreateFile(TEXT("HiScores.dat"), GENERIC_WRITE, 0, NULL,
    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    // The hi score file couldn't be created, so bail
    return FALSE;

  // Write the scores
  
    // Format each score for writing
	TCHAR szText[64];
    LPWSTR cData=szText;
    wsprintf(cData, L"%05d", g_iHiScores);

    // Write the score
    DWORD dwBytesWritten;
    if (!WriteFile(hFile, &cData, 1, &dwBytesWritten, NULL))
    {
      // Something went wrong, so close the file handle
      CloseHandle(hFile);
      return FALSE;
    
  }

  // Close the file
  return CloseHandle(hFile);
}

void MovePlayer(int iXDistance,int iYDistance)
{
	g_pPlayer[g_iPlayerNum]->SetVelocity(iXDistance, iYDistance);
}
void SC1()
{
	g_tGoldTime=time(0);
	g_bGoldbody=true;
	g_pPlayer[g_iPlayerNum]->SetFrames(2);

	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top-100;

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(0,-10);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(4,-9);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(7,-7);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(9,-4);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(10,0);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(0,-10);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(-4,-9);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(-7,-7);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(-9,-4);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pPlayer1SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
    pSprite->SetNumFrames(8,false);
	pSprite->SetVelocity(-10,0);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

}
void SC2()
{
	g_tGoldTime=time(0);
	g_bGoldbody=true;
	g_pPlayer[g_iPlayerNum]->SetFrames(2);

	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top-100;
	for(int i=0;i<19;++i)
	{
		pSprite = new Sprite(g_pPlayer2SCBitmap[rand()%5+0], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_SC);
		pSprite->SetVelocity(0,-30);
		pSprite->SetPosition(50+rand()%300+10,650+rand()%100+10);
		g_pGame->AddSprite(pSprite);
	}
}
void SC3()
{
	g_tGoldTime=time(0);
	g_bGoldbody=true;
	g_pPlayer[g_iPlayerNum]->SetFrames(2);

	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top-100;

	pSprite = new Sprite(g_pPlayer3SCBitmap, rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_SC);
	pSprite->SetVelocity(0,-10);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);
}

void stage1()
{
	g_tTime=time(0);
	if(g_tTime-g_tStartTime==3 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		g_tAddEnemyDelay=g_tTime;
		
	}
	else if(g_tTime-g_tStartTime==4  && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddCaonima(0);
		EventAddqq(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 10 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;

	}
	else if(g_tTime- g_tStartTime == 12 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddCaonima(1);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 16 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 20 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(6);
		EventAddqq(2);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 25 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		EventAddCaonima(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 30 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 36 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(6);
		EventAddqq(5);
		EventAddCaonima(2);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 44 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddCaonima(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 52 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(3);
		EventAddqq(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 56 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 60 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(6);
		EventAddCaonima(1);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 66 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddCaonima(2);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 70 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		EventAddqq(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 75 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddCaonima(2);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 80 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 82 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 84 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(4);
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("warning.wav"),true);
		g_tAddEnemyDelay=g_tTime;
	}
	if(g_tTime-g_tStartTime == 87 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("BossMusic1.wav"),true);
		EventAddBoss(1);
		g_tAddEnemyDelay=g_tTime;
	}

}
void stage2()
{
	g_tTime=time(0);
	if(g_tTime-g_tStartTime==1 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_iBackground=2;
		g_pGame->CloseMIDIPlayer();
		g_pGame->PlayMIDISong(TEXT("Music2.wav"),true);
		
		g_tAddEnemyDelay=g_tTime;


		g_pGame->CleanupSprites();

		RECT rcBounds = { 0, 0, 550, 700 };
		g_pPlayer[g_iPlayerNum] = new Player(g_pPlayerBitmap[g_iPlayerNum], rcBounds, BA_STOP);
		g_pPlayer[g_iPlayerNum]->SetPosition(200, 625);
		g_pPlayer[g_iPlayerNum]->SetNumFrames(3,false);
		g_pPlayer[g_iPlayerNum]->SetFrames(0);
		g_pPlayer[g_iPlayerNum]->SetSpriteAttribute(SAT_PLAYER);
		g_pGame->AddSprite(g_pPlayer[g_iPlayerNum]);
	}
	else if(g_tTime-g_tStartTime==5 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(5);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==8 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(2);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==10 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(0);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==15 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==20 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(1);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==25 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==29 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==32 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(0);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==36 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==40 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(1);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==44 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==49 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==53 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(1);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==56 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==60 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==60 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddDragon(0);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==63 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==66 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddStone(2);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==70 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(3);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==74 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==77 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==79 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(0);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==82 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==87 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==89 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==91 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==95 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(5);
		EventAddqq(1);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==100 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(1);
		EventAddqq(5);
		EventAddqq(6);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==105 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(6);
		EventAddqq(0);
		EventAddqq(1);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==110 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(5);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 112 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(4);
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("warning.wav"),true);
		g_tAddEnemyDelay=g_tTime;
	}
	if(g_tTime-g_tStartTime == 115 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("BossMusic2.wav"),true);
		EventAddBoss(2);
		g_tAddEnemyDelay=g_tTime;
	}
}
void stage3()
{
	g_tTime=time(0);
	if(g_tTime-g_tStartTime==1 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_iBackground=3;
		g_pGame->CloseMIDIPlayer();
		g_pGame->PlayMIDISong(TEXT("Music3.wav"),true);
	
		g_tAddEnemyDelay=g_tTime;


		g_pGame->CleanupSprites();

		RECT rcBounds = { 0, 0, 550, 700 };
		g_pPlayer[g_iPlayerNum] = new Player(g_pPlayerBitmap[g_iPlayerNum], rcBounds, BA_STOP);
		g_pPlayer[g_iPlayerNum]->SetPosition(200, 625);
		g_pPlayer[g_iPlayerNum]->SetNumFrames(3,false);
		g_pPlayer[g_iPlayerNum]->SetFrames(0);
		g_pPlayer[g_iPlayerNum]->SetSpriteAttribute(SAT_PLAYER);
		g_pGame->AddSprite(g_pPlayer[g_iPlayerNum]);
	}
	else if(g_tTime-g_tStartTime==5 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==8 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(0);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==11 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddStone(0);
		EventAddqq(1);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==16 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(2);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==18 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(0);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==20 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddDragon(0);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==25 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(3);
		EventAddqq(5);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==27 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==31 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(0);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==35 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddStone(3);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==41 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddStone(0);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==45 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(4);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==48 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddStone(2);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==54 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(3);
		EventAddqq(2);
		EventAddqq(4);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==57 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(3);
		EventAddqq(4);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==60 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(3);
		EventAddqq(4);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==64 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(1);
		EventAddqq(3);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==70 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddStone(3);
		EventAddqq(4);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==75 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(4);
		EventAddqq(1);
		EventAddqq(3);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==79 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddStone(3);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime==80 && g_tTime-g_tAddEnemyDelay>1)
	{
		EventAddqq(2);
		EventAddqq(3);
		EventAddqq(4);
		EventAddqq(5);
		g_tAddEnemyDelay=g_tTime;
	}
	else if(g_tTime-g_tStartTime == 82 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("warning.wav"),true);
		g_tAddEnemyDelay=g_tTime;
	}
	if(g_tTime-g_tStartTime == 85 && g_tTime-g_tAddEnemyDelay>1)
	{
		g_pGame->CloseMIDIPlayer();
	    g_pGame->PlayMIDISong(TEXT("BossMusic3.wav"),true);
		EventAddBoss(3);
		g_tAddEnemyDelay=g_tTime;
	}
}
void fire1()
{

     //PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
     //   SND_RESOURCE | SND_NOSTOP);
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top;

	pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
    pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-20);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	for(int i=1;i<int(floor(g_dPower));++i)
	{
		pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(-3*i,-20);
		pSprite->SetPosition(position);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(3*i,-20);
		pSprite->SetPosition(position);
		g_pGame->AddSprite(pSprite);

	}
}
void fire2()
{
	//PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
    //   SND_RESOURCE | SND_NOSTOP);
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top;
	POINT tempposition1=position;
	POINT tempposition2=position;

	pSprite = new Sprite(g_pPlayer2BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
    pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-20);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	for(int i=1;i<int(floor(g_dPower));++i)
	{
		tempposition1.x= tempposition1.x-20;
	    tempposition1.y= tempposition1.y-5;
		pSprite = new Sprite(g_pPlayer2BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-20);
		pSprite->SetPosition(tempposition1);
		g_pGame->AddSprite(pSprite);

		tempposition2.x= tempposition2.x+20;
	    tempposition2.y= tempposition2.y-5;
		pSprite = new Sprite(g_pPlayer2BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-20);
		pSprite->SetPosition(tempposition2);
		g_pGame->AddSprite(pSprite);

	}


}
void fire3()
{
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top-20;
	POINT tempposition1=position;
	POINT tempposition2=position;

	pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
    pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-10);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	for(int i=1;i<int(floor(g_dPower));++i)
	{
		tempposition1.x= tempposition1.x-20;
	    tempposition1.y= tempposition1.y+10;
		pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-10);
		pSprite->SetPosition(tempposition1);
		g_pGame->AddSprite(pSprite);

		tempposition2.x= tempposition2.x+20;
	    tempposition2.y= tempposition2.y+10;
		pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-10);
		pSprite->SetPosition(tempposition2);
		g_pGame->AddSprite(pSprite);

	}
}
void slowfire1()
{
	     //PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
     //   SND_RESOURCE | SND_NOSTOP);
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top;
	POINT tempposition1=position;
	POINT tempposition2=position;

	pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
    pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-20);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	for(int i=1;i<int(floor(g_dPower));++i)
	{
		
		tempposition1.x= tempposition1.x-10;
	    tempposition1.y= tempposition1.y-10;
		pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-20);
		pSprite->SetPosition(tempposition1);
		g_pGame->AddSprite(pSprite);

		tempposition2.x= tempposition2.x+10;
		tempposition2.y= tempposition2.y-10;
		pSprite = new Sprite(g_pPlayer1BulletBitmap[int(floor(g_dPower))], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-20);
		pSprite->SetPosition(tempposition2);
		g_pGame->AddSprite(pSprite);

	}
}
void slowfire2()
{
	     //PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
     //   SND_RESOURCE | SND_NOSTOP);
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top;

	pSprite = new Sprite(g_pPlayer2BulletBitmap[4], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
    pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-15);
    pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

}
void slowfire3()
{
	 //PlaySound((LPCWSTR)IDR_WAVE4, g_hInstance, SND_ASYNC |
     //   SND_RESOURCE | SND_NOSTOP);
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position;
	position.x= g_pPlayer[g_iPlayerNum]->GetPosition().left+42;
	position.y= g_pPlayer[g_iPlayerNum]->GetPosition().top-20;
	POINT tempposition1=position;
	POINT tempposition2=position;

	pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
	pSprite->SetNumFrames(1);
	pSprite->SetVelocity(0,-10);
	pSprite->SetPosition(position);
	g_pGame->AddSprite(pSprite);

	for(int i=1;i<int(floor(g_dPower));++i)
	{
		tempposition1.x= tempposition1.x-10;
		tempposition1.y= tempposition1.y+10;
		pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-10);
		pSprite->SetPosition(tempposition1);
		g_pGame->AddSprite(pSprite);

		tempposition2.x= tempposition2.x+10;
		tempposition2.y= tempposition2.y+10;
		pSprite = new Sprite(g_pPlayer3BulletBitmap[int(floor(g_dPower)/2)], rcBounds1, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_PLAYERBULLET);
		pSprite->SetNumFrames(1);
		pSprite->SetVelocity(0,-10);
		pSprite->SetPosition(tempposition2);
		g_pGame->AddSprite(pSprite);

	}
}
void EventAddDragon(int type)
{
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position1={ 100, 50};
	POINT position2={ 390, 50};

	pSprite = new Sprite(g_pDragonBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(4,false);
	pSprite->SetHp(20);
	pSprite->SetScore(50);
	pSprite->SetVelocity(0,3);
    pSprite->SetPosition(position1);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pDragonBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(4,false);
	pSprite->SetHp(20);
	pSprite->SetScore(50);
	pSprite->SetVelocity(0,3);
    pSprite->SetPosition(position2);
	g_pGame->AddSprite(pSprite);
}
void EventAddCaonima(int type)
{
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position1={ 100, 50};
	POINT position2={ 390, 50};

	pSprite = new Sprite(g_pCaonimaBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(1);
	pSprite->SetHp(10);
	pSprite->SetScore(20);
	pSprite->SetVelocity(0,3);
    pSprite->SetPosition(position1);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pCaonimaBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(1);
	pSprite->SetHp(10);
	pSprite->SetScore(20);
	pSprite->SetVelocity(0,3);
    pSprite->SetPosition(position2);
	g_pGame->AddSprite(pSprite);
}
void EventAddStone(int type)
{
	Sprite*  pSprite;
	RECT rcBounds1 = { 25, 25, 525, 675 };
	POINT position1={ 100, 150};
	POINT position2={ 390, 150};

	pSprite = new Sprite(g_pStoneBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(1);
	pSprite->SetHp(50);
	pSprite->SetScore(80);
	pSprite->SetVelocity(0,0);
    pSprite->SetPosition(position1);
	g_pGame->AddSprite(pSprite);

	pSprite = new Sprite(g_pStoneBitmap[type], rcBounds1, BA_DIE);
	pSprite->SetSpriteAttribute(SAT_ENEMY);
    pSprite->SetNumFrames(1);
	pSprite->SetHp(50);
	pSprite->SetScore(80);
	pSprite->SetVelocity(0,0);
    pSprite->SetPosition(position2);
	g_pGame->AddSprite(pSprite);
}
void EventAddqq(int type)
{
	Sprite*  pSprite;
	RECT rcBounds1 = { 0, 25, 550, 675 };
	POINT position1={ 0, 150};
	POINT position2={ 550, 150};
	if(type == 0)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq2Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetNumFrames(1);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(3,2);
			pSprite->SetPosition(position1.x+i*25,position1.y);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq2Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-3,2);
			pSprite->SetPosition(position2.x-i*25,position2.y);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 1)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq2Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(2,0);
			pSprite->SetPosition(position1.x+i*40,position1.y);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq2Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-2,0);
			pSprite->SetPosition(position2.x-i*40,position2.y);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 2)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(3,5+i*4);
			pSprite->SetPosition(position1.x+i*50+50,position1.y-100);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-3,5+i*4);
			pSprite->SetPosition(position2.x-i*50-50,position2.y-100);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 3)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(i*2,5+i*4);
			pSprite->SetPosition(position1.x+i*50,position1.y);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-i*2,5+i*4);
			pSprite->SetPosition(position2.x-i*50,position2.y);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 4)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(3,6);
			pSprite->SetPosition(position1.x+i*50,position1.y+25+50);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-3,6);
			pSprite->SetPosition(position2.x-i*50,position2.y+25+50);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 5)
	{
		for(int i=0;i<7;++i)
		{
			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(2,2);
			pSprite->SetPosition(position1.x+i*50,position1.y+25+50);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-2,2);
			pSprite->SetPosition(position2.x-i*50,position2.y+25+50);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if(type == 6)
	{
		for(int i=0;i<5;++i)
		{
			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(3,0);
			pSprite->SetPosition(position1.x+i*50,position1.y+25+60);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq1Bitmap, rcBounds1, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetHp(1);
			pSprite->SetScore(10);
			pSprite->SetVelocity(-3,0);
			pSprite->SetPosition(position2.x-i*50,position2.y+25+60);
			g_pGame->AddSprite(pSprite);
		}
	}
}
void EventAddBoss(int type)
{
	if(type == 1)
	{
		Sprite*  pSprite2;
		Sprite*  pSprite3;
		RECT rcBounds1 = { 25, 25, 525, 675 };
		POINT position1={ 250, 75};
		POINT position2={ 50,50};
		
		g_sBoss1 = new Sprite(g_pCaonimaBitmap[3], rcBounds1, BA_DIE);
		g_sBoss1->SetSpriteAttribute(SAT_BOSS);
		g_sBoss1->SetNumFrames(1);
		g_sBoss1->SetHp(1500);
		g_sBoss1->SetScore(2000);
		g_sBoss1->SetVelocity(0,0);
		g_sBoss1->SetPosition(position1);
		g_pGame->AddSprite(g_sBoss1);

		pSprite2 = new Sprite(g_pBossHpBitmap2, rcBounds1, BA_DIE);
		pSprite2->SetSpriteAttribute(SAT_OTHER);
		pSprite2->SetNumFrames(1);
		pSprite2->SetVelocity(0,0);
		pSprite2->SetPosition(position2);
		g_pGame->AddSprite(pSprite2);

		pSprite3 = new Sprite(g_pBossHpBitmap1, rcBounds1, BA_DIE);
		pSprite3->SetSpriteAttribute(SAT_OTHER);
		pSprite3->SetNumFrames(1);
		pSprite3->SetVelocity(0,0);
		pSprite3->SetPosition(position2.x+55,position2.y+3);
		g_pGame->AddSprite(pSprite3);

	}
	else if(type == 2)
	{
		Sprite*  pSprite2;
		Sprite*  pSprite3;
		RECT rcBounds1 = { 25, 25, 525, 675 };
		POINT position1={ 200, 75};
		POINT position2={ 50,50};
		
		g_sBoss2 = new Sprite(g_pDragonBitmap[2], rcBounds1, BA_BOUNCE);
		g_sBoss2->SetSpriteAttribute(SAT_BOSS);
		g_sBoss2->SetNumFrames(4);
		g_sBoss2->SetFrameDelay(4);
		g_sBoss2->SetHp(2500);
		g_sBoss2->SetScore(2000);
		g_sBoss2->SetVelocity(0,0);
		g_sBoss2->SetPosition(position1);
		g_pGame->AddSprite(g_sBoss2);

		pSprite2 = new Sprite(g_pBossHpBitmap2, rcBounds1, BA_DIE);
		pSprite2->SetSpriteAttribute(SAT_OTHER);
		pSprite2->SetNumFrames(1);
		pSprite2->SetVelocity(0,0);
		pSprite2->SetPosition(position2);
		g_pGame->AddSprite(pSprite2);

		pSprite3 = new Sprite(g_pBossHpBitmap1, rcBounds1, BA_DIE);
		pSprite3->SetSpriteAttribute(SAT_OTHER);
		pSprite3->SetNumFrames(1);
		pSprite3->SetVelocity(0,0);
		pSprite3->SetPosition(position2.x+55,position2.y+3);
		g_pGame->AddSprite(pSprite3);
	}
	else if(type == 3)
	{
	
		Sprite*  pSprite2;
		Sprite*  pSprite3;
		Sprite*  pSprite4;
		RECT rcBounds1 = { 25, 25, 525, 675 };
		POINT position1={ 100, 25};
		POINT position2={ 50,50};
		
		g_sBoss3 = new Sprite(g_pQQBitmap, rcBounds1, BA_DIE);
		g_sBoss3->SetSpriteAttribute(SAT_BOSS);
		g_sBoss3->SetNumFrames(1);
		g_sBoss3->SetHp(4000);
		g_sBoss3->SetScore(2000);
		g_sBoss3->SetVelocity(0,0);
		g_sBoss3->SetPosition(position1);
		g_pGame->AddSprite(g_sBoss3);

		pSprite2 = new Sprite(g_pBossHpBitmap2, rcBounds1, BA_DIE);
		pSprite2->SetSpriteAttribute(SAT_OTHER);
		pSprite2->SetNumFrames(1);
		pSprite2->SetVelocity(0,0);
		pSprite2->SetPosition(position2);
		g_pGame->AddSprite(pSprite2);

		pSprite3 = new Sprite(g_pBossHpBitmap1, rcBounds1, BA_DIE);
		pSprite3->SetSpriteAttribute(SAT_OTHER);
		pSprite3->SetNumFrames(1);
		pSprite3->SetVelocity(0,0);
		pSprite3->SetPosition(position2.x+55,position2.y+3);
		g_pGame->AddSprite(pSprite3);

		pSprite4 = new Sprite(g_pWallBitmap, rcBounds1, BA_STOP);
		pSprite4->SetSpriteAttribute(SAT_WALL);
		pSprite4->SetNumFrames(1);
		pSprite4->SetVelocity(0,0);
		pSprite4->SetPosition(25,670);
		g_pGame->AddSprite(pSprite4);
	}
}