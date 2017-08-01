#pragma once
#include "StdAfx.h"
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"

//-----------------------------------------------------------------
// AlienSprite Class
//-----------------------------------------------------------------
class Enemy : public Sprite
{
protected:
	int hp;
	int damage;
	time_t starttime;
	int score;
public:
  // Constructor(s)/Destructor
          Enemy(int score,int hp,int damage,Bitmap* pBitmap, RECT& rcBounds,
            BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~Enemy();
  int GetScore(){ return score;};
  int SufferDamage(int power) { damage=damage+power;return damage;};
  bool DamageEnough() {return damage>hp;};
  virtual void  CalcCollisionRect();
  // General Methods
  virtual SPRITEACTION  Update();
  virtual Sprite*       AddSprite();
  virtual void AddSprite(int choose);
};