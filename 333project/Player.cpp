//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Player.h"
#include "StdAfx.h"
#include<time.h>
//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Player::Player(Bitmap* pBitmap, RECT& rcBounds,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
  baBoundsAction)
{
	m_tStarttime=time(0);
	m_iFrameDelay=-1;
	m_bGoldbody=false;
	
}
Player::~Player()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Player::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();
  return saSpriteAction;
}


void Player::CalcCollisionRect()
 {
  int iXShrink = (m_rcPosition.left - m_rcPosition.right) / 2;
  int iYShrink = (m_rcPosition.top - m_rcPosition.bottom) / 2;
  CopyRect(&m_rcCollision, &m_rcPosition);
  InflateRect(&m_rcCollision, iXShrink, iYShrink);
 }