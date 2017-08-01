//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Enemy.h"
#include "StdAfx.h"
#include<time.h>
//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Bitmap* g_pqq1Bitmap;
extern Bitmap* g_pqq2Bitmap;
extern Bitmap* g_pQQBitmap;
extern Bitmap* g_pqqBulletBitmap;

extern int     g_iDifficulty;

//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Enemy::Enemy(int score,int hp,int damage,Bitmap* pBitmap, RECT& rcBounds,
  BOUNDSACTION baBoundsAction) :score(score),hp(hp),damage(damage), Sprite(pBitmap, rcBounds,
  baBoundsAction)
{
	starttime=time(0);
}

Enemy::~Enemy()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Enemy::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  // See if the alien should fire a missile
  if ((rand() % (g_iDifficulty / 2)) == 0)
   if(saSpriteAction!=SA_KILL)	
   {
		saSpriteAction |= SA_ADDSPRITE;
   }
  return saSpriteAction;
}

Sprite* Enemy::AddSprite()
{
  //// Create a new missile sprite
  //RECT    rcBounds = { 25, 25, 525, 675 };
  //RECT    rcPos = GetPosition();
  //Sprite* pSprite = NULL;
  //if (GetBitmap() == g_pqq1Bitmap)
  //{
  //  // Blobbo missile
  //  pSprite = new Sprite(g_pqqBulletBitmap, rcBounds, BA_DIE);
  //  pSprite->SetVelocity(0, 10);
  //}
  //else if (GetBitmap() == g_pqq2Bitmap)
  //{
  //  // Jelly missile
  //  pSprite = new Sprite(g_pqqBulletBitmap, rcBounds, BA_DIE);
  //  pSprite->SetVelocity(0, 15);
  //}
  //else if(GetBitmap()==g_pQQBitmap)
  //{
  //  // Timmy missile
  //  pSprite = new Sprite(g_pqq1Bitmap, rcBounds, BA_DIE);
  //  pSprite->SetVelocity(0, 10);
  //}

  //// Set the missile sprite's position and return it
  //pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
  return NULL;
}
 void Enemy::AddSprite(int choose)
{

}
 void  Enemy::CalcCollisionRect()
 {
 }