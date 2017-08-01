//-----------------------------------------------------------------
// Background Object
// C++ Header - Background.h
//-----------------------------------------------------------------

#pragma once
#include "StdAfx.h"
//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Bitmap.h"

//-----------------------------------------------------------------
// Background Class
//-----------------------------------------------------------------
class Background
{
protected:
  // Member Variables
  int       m_iWidth, m_iHeight;
  COLORREF  m_crColor;
  Bitmap*   m_pBitmap;
  int		m_iCurFrame;
  int		m_iNumFrames;
  int		m_iFrameDelay;
  int		m_iFrameTrigger;

public:
  // Constructor(s)/Destructor
          Background(int iWidth, int iHeight, COLORREF crColor);
          Background(Bitmap* pBitmap);
  virtual ~Background();

  // General Methods

  virtual void  Update();
  virtual void  Draw(HDC hDC);

  // Accessor Methods
  void    SetNumFrames(int iNumFrames) { m_iNumFrames = iNumFrames;};
  int	  GetFrames() { return m_iCurFrame; };
  void    SetFrameDelay(int iFrameDelay) { m_iFrameDelay = iFrameDelay; };
  int GetWidth()  { return m_iWidth; };
  int GetHeight() { return m_iHeight; };
};