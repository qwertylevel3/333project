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
class Player : public Sprite
{
protected:
	time_t m_tStarttime;
	bool m_bGoldbody;
public:
  // Constructor(s)/Destructor
          Player(Bitmap* pBitmap, RECT& rcBounds,
            BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~Player();

  virtual void  CalcCollisionRect();
  // General Methods
  void SetGoldbody(bool Goldbody) { m_bGoldbody=Goldbody;};
  virtual SPRITEACTION  Update();
};