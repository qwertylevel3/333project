#pragma once

#include "resource.h"
//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         g_hInstance;
GameEngine*       g_pGame;
HDC               g_hOffscreenDC;
HBITMAP           g_hOffscreenBitmap;

//Bitmap*           g_pSplashBitmap;
//Bitmap*           g_pDesertBitmap;
Sprite*			  g_sBoss1;
Sprite*			  g_sBoss2;
Sprite*			  g_sBoss3;

Bitmap*           g_pPlayerBitmap[3];

Bitmap*           g_pPlayerHeadBitmap[3];
Bitmap*           g_pPlayer1SCBitmap;
Bitmap*			  g_pPlayer2SCBitmap[6];
Bitmap*			  g_pPlayer3SCBitmap;
Bitmap*			  g_pSCBitmap[3];
Player*           g_pPlayer[3];
Bitmap*           g_pPlayer1BulletBitmap[4];
Bitmap*           g_pPlayer2BulletBitmap[5];
Bitmap*           g_pPlayer3BulletBitmap[4];

Bitmap*           g_pEnemyBulletBitmap[5];
Bitmap*			  g_pCaonimaBitmap[4];
Bitmap*           g_pDragonBitmap[3];
Bitmap*           g_pStoneBitmap[4];

Bitmap*           g_pqq1Bitmap;
Bitmap*           g_pqq2Bitmap;
Bitmap*           g_pQQBitmap;
Bitmap*			  g_pBoom1Bitmap;
Bitmap*			  g_pBoom2Bitmap;
Bitmap*			  g_pBoom3Bitmap;


Bitmap*           g_pWallPaperBitmap;
Bitmap*			  g_pLoadingBitmap;
Bitmap*			  g_pStartBitmap;
Bitmap*           g_pGameOverBitmap;
Bitmap*			  g_pLogoBitmap;
Bitmap*			  g_pTitleBitmap;
Bitmap*			  g_pGameEndingBitmap;

Bitmap*           g_pBackground1Bitmap;
Bitmap*           g_pBackground2Bitmap;
Bitmap*			  g_pBackground3Bitmap;
Bitmap*			  g_pPointBitmap;
Bitmap*			  g_pBoomPointBitmap;
Bitmap*			  g_pChooseCharacterBitmap[3];


Bitmap*			  g_pGameLogoBitmap;
Bitmap*			  g_pBossHpBitmap1;
Bitmap*			  g_pBossHpBitmap2;
Bitmap*			  g_pWallBitmap;
int               g_iBackground;
Background*		  g_pBackground1;
Background*		  g_pBackground2;
Background*		  g_pBackground3;


int				  g_iLogoFrame;
int               g_iFireInputDelay;
int				  g_iFireTrigger;
int               g_iSpellCard;
int               g_iNumLives, g_iScore, g_iDifficulty;
BOOL              g_bGameOver;

BOOL              g_bDemo;
int               g_iHiScores;
BOOL              g_bSmall;

int				  g_iPlayerNum;
int				  g_iSCNum;
int				  g_iNumLivesDelay;
double			  g_dPower;
double			  g_dPowerLimit;
bool			  g_bGoldbody;

time_t			  g_tStageDelay;
clock_t            g_tGameOverDelay;
time_t			  g_tStartTime;
time_t			  g_tTime;
time_t			  g_tAddEnemyDelay;
time_t			  g_tGoldTime;
clock_t			  g_tInputDelay;


int			      g_iGameStart;
bool			  g_bGoodEnd;
bool			  g_bStage1;
bool			  g_bStage2;
bool			  g_bStage3;
bool			  g_bLogo;
//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void AddAlien();
void MovePlayer(int x,int y);
void UpdateHiScores();
BOOL ReadHiScores();
BOOL WriteHiScores();
void SC1();
void SC2();
void SC3();
void stage1();
void stage2();
void stage3();
void fire1();
void fire2();
void fire3();
void slowfire1();
void slowfire2();
void slowfire3();
void EventAddDragon(int type);
void EventAddCaonima(int type);
void EventAddStone(int type);
void EventAddqq(int type);
void EventAddBoss(int type);