//-----------------------------------------------------------------
// Background Object
// C++ Source - Background.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Background.h"
#include "StdAfx.h"
//-----------------------------------------------------------------
// Background Constructor(s)/Destructor
//-----------------------------------------------------------------
Background::Background(int iWidth, int iHeight, COLORREF crColor)
{
  // Initialize the member variables
  m_iWidth = iWidth;
  m_iHeight = iHeight;
  m_crColor = crColor;
  m_pBitmap = NULL;
  m_iCurFrame=m_iNumFrames=m_iFrameDelay=m_iFrameTrigger=0;
}

Background::Background(Bitmap* pBitmap)
{
  // Initialize the member variables
  m_crColor = 0;
  m_pBitmap = pBitmap;
  m_iWidth = pBitmap->GetWidth();
  m_iHeight = pBitmap->GetHeight();
  m_iCurFrame=m_iFrameDelay=m_iFrameTrigger=0;
  m_iNumFrames=1;
}

Background::~Background()
{
}

//-----------------------------------------------------------------
// Background General Methods
//-----------------------------------------------------------------
void Background::Update()
{
  
  if ((m_iFrameDelay >= 0) && (--m_iFrameTrigger <= 0))
  {
    // Reset the frame trigger;
    m_iFrameTrigger = m_iFrameDelay;

    // Increment the frame
    if (++m_iCurFrame >= m_iNumFrames)
    {
        m_iCurFrame = 0;
    }
  }
}



void Background::Draw(HDC hDC)
{
  // Draw the background

   m_pBitmap->DrawPart(hDC,25, 25,
        m_iCurFrame * 500, 0, 500, 650, TRUE);

}