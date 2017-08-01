//-----------------------------------------------------------------
// Sprite Object
// C++ Source - Sprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Sprite.h"
#include"Player.h"
#include "StdAfx.h"
#include<math.h>

extern BOOL g_bDemo;
extern Bitmap* g_pPlayerBitmap[3];
extern time_t g_tStageDelay;
extern int g_iPlayerNum;
extern Player* g_pPlayer[3];
extern Bitmap* g_pCaonimaBitmap[4];
extern Bitmap* g_pDragonBitmap[3];
extern Bitmap* g_pStoneBitmap[4];
extern Bitmap* g_pqq1Bitmap;
extern Bitmap* g_pqq2Bitmap;
extern Bitmap* g_pQQBitmap;
extern Bitmap* g_pEnemyBulletBitmap[5];
extern Bitmap* g_pBossHpBitmap1;
extern Bitmap* g_pBossHpBitmap2;
extern Bitmap* g_pPointBitmap;
extern GameEngine* g_pGame;
extern bool g_bStage1;
extern bool g_bStage2;
extern bool g_bStage3;
extern Sprite* g_sBoss1;
extern Sprite* g_sBoss2;
extern Sprite* g_sBoss3;
extern int     g_iDifficulty;
//-----------------------------------------------------------------
// Sprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Sprite::Sprite(Bitmap* pBitmap)
{
	// Initialize the member variables
	m_pBitmap = pBitmap;
	m_iNumFrames = 1;
	m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
	SetRect(&m_rcPosition, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
	CalcCollisionRect();
	m_ptVelocity.x = m_ptVelocity.y = 0;
	m_iZOrder = 0;
	SetRect(&m_rcBounds, 0, 0, 640, 480);
	m_baBoundsAction = BA_STOP;
	m_satAttribute = SAT_ENEMY;
	m_bHidden = FALSE;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
	m_tStarttime = time(0);
	m_tLifetime = time(0);
	m_iHp = 1;
	m_dDamage = 0;
	m_iScore = 0;
}

Sprite::Sprite(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
	// Calculate a random position
	int iXPos = rand() % (rcBounds.right - rcBounds.left);
	int iYPos = rand() % (rcBounds.bottom - rcBounds.top);

	// Initialize the member variables
	m_pBitmap = pBitmap;
	m_iNumFrames = 1;
	m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
	SetRect(&m_rcPosition, iXPos, iYPos, iXPos + pBitmap->GetWidth(),
		iYPos + pBitmap->GetHeight());
	CalcCollisionRect();
	m_ptVelocity.x = m_ptVelocity.y = 0;
	m_iZOrder = 0;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_satAttribute = SAT_ENEMY;
	m_bHidden = FALSE;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
	m_tStarttime = time(0);
	m_tLifetime = time(0);
	m_iHp = 5;
	m_dDamage = 0;
	m_iScore = 5;
}

Sprite::Sprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder,
	RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
	// Initialize the member variables
	m_pBitmap = pBitmap;
	m_iNumFrames = 1;
	m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
	SetRect(&m_rcPosition, ptPosition.x, ptPosition.y,
		ptPosition.x + pBitmap->GetWidth(), ptPosition.y + pBitmap->GetHeight());
	CalcCollisionRect();
	m_ptVelocity = ptVelocity;
	m_iZOrder = iZOrder;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_satAttribute = SAT_ENEMY;
	m_bHidden = FALSE;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
	m_tStarttime = time(0);
	m_tLifetime = time(0);
	m_iHp = 1;
	m_dDamage = 0;
	m_iScore = 0;
}

Sprite::~Sprite()
{
}

//-----------------------------------------------------------------
// Sprite General Methods
//-----------------------------------------------------------------

RECT&   Sprite::GetPosition()
{
	return m_rcPosition;
};
SPRITEACTION Sprite::Update()
{
	SPRITEACTION saSpriteAction = SA_NONE;
	// See if the sprite needs to be killed
	if (m_bDying)
		return  SA_KILL;
	if (DamageEnough())
	{
		m_bDying = true;
		return SA_KILL;
	}
	if (g_tStageDelay != 0 && (m_pBitmap == g_pBossHpBitmap1 || m_pBitmap == g_pBossHpBitmap2))
	{
		m_bDying = true;
	}
	if (m_pBitmap == g_pStoneBitmap[0] ||
		m_pBitmap == g_pStoneBitmap[1] ||
		m_pBitmap == g_pStoneBitmap[2] ||
		m_pBitmap == g_pStoneBitmap[3])
	{
		if (time(0) - m_tLifetime > 5)
		{
			m_bDying = true;
		}
	}
	time_t Nowtime = time(0);
	// Update the frame
	UpdateFrame();

	// Update the position
	POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
	ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
	ptNewPosition.y = m_rcPosition.top + m_ptVelocity.y;
	ptSpriteSize.x = m_rcPosition.right - m_rcPosition.left;
	ptSpriteSize.y = m_rcPosition.bottom - m_rcPosition.top;
	ptBoundsSize.x = m_rcBounds.right - m_rcBounds.left;
	ptBoundsSize.y = m_rcBounds.bottom - m_rcBounds.top;

	// Check the bounds
	// Wrap?
	if (m_baBoundsAction == BA_WRAP)
	{
		if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left)
			ptNewPosition.x = m_rcBounds.right;
		else if (ptNewPosition.x > m_rcBounds.right)
			ptNewPosition.x = m_rcBounds.left - ptSpriteSize.x;
		if ((ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top)
			ptNewPosition.y = m_rcBounds.bottom;
		else if (ptNewPosition.y > m_rcBounds.bottom)
			ptNewPosition.y = m_rcBounds.top - ptSpriteSize.y;
	}
	// Bounce?
	else if (m_baBoundsAction == BA_BOUNCE)
	{
		BOOL bBounce = FALSE;
		POINT ptNewVelocity = m_ptVelocity;
		if (ptNewPosition.x < m_rcBounds.left)
		{
			bBounce = TRUE;
			ptNewPosition.x = m_rcBounds.left;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		else if ((ptNewPosition.x + ptSpriteSize.x) > m_rcBounds.right)
		{
			bBounce = TRUE;
			ptNewPosition.x = m_rcBounds.right - ptSpriteSize.x;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		if (ptNewPosition.y < m_rcBounds.top)
		{
			bBounce = TRUE;
			ptNewPosition.y = m_rcBounds.top;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		else if ((ptNewPosition.y + ptSpriteSize.y) > m_rcBounds.bottom)
		{
			bBounce = TRUE;
			ptNewPosition.y = m_rcBounds.bottom - ptSpriteSize.y;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		if (bBounce)
			SetVelocity(ptNewVelocity);
	}
	// Die?
	else if (m_baBoundsAction == BA_DIE)
	{
		if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left ||
			ptNewPosition.x > m_rcBounds.right ||
			(ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top ||
			ptNewPosition.y > m_rcBounds.bottom)
			return SA_KILL;
	}
	// Stop (default)
	else
	{
		if (ptNewPosition.x  < m_rcBounds.left ||
			ptNewPosition.x >(m_rcBounds.right - ptSpriteSize.x))
		{
			ptNewPosition.x = max(m_rcBounds.left, min(ptNewPosition.x,
				m_rcBounds.right - ptSpriteSize.x));
			SetVelocity(0, 0);
		}
		if (ptNewPosition.y  < m_rcBounds.top ||
			ptNewPosition.y >(m_rcBounds.bottom - ptSpriteSize.y))
		{
			ptNewPosition.y = max(m_rcBounds.top, min(ptNewPosition.y,
				m_rcBounds.bottom - ptSpriteSize.y));
			SetVelocity(0, 0);
		}
	}
	SetPosition(ptNewPosition);

	if (saSpriteAction != SA_KILL)
	{
		if (Nowtime - m_tStarttime > 1)
		{
			m_tStarttime = Nowtime;
			return SA_ADDSPRITE;
		}
	}
	return SA_NONE;
}

void Sprite::AddSprite()
{
	// Create a new missile sprite
	RECT    rcBounds = { 25, 25, 525, 675 };
	RECT    rcPos1 = GetPosition();
	POINT	position1;
	position1.x = GetPosition().left + GetWidth() / 2;
	position1.y = GetPosition().bottom;
	POINT position2;
	if (g_bDemo == false)
	{
		position2.x = g_pPlayer[g_iPlayerNum]->GetPosition().left + 42;
		position2.y = g_pPlayer[g_iPlayerNum]->GetPosition().top;
	}
	POINT position3;
	position3.x = 75;
	position3.y = 100;
	POINT position4;
	position4.x = 500;
	position4.y = 100;
	Sprite* pSprite = NULL;
	if (GetBitmap() == g_pqq1Bitmap)
	{
	}
	else if (GetBitmap() == g_pqq2Bitmap)
	{
		int x = (position2.x) - (position1.x);
		int y = (position2.y) - (position1.y);
		int z = pow(x*x + y*y, 0.5);
		int posx = 10 * x / z;
		int posy = 10 * y / z;
		//自机狙
		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetPosition(position1.x, position1.y);
		pSprite->SetVelocity(posx, posy);

		g_pGame->AddSprite(pSprite);
	}
	else if (GetBitmap() == g_pCaonimaBitmap[0])
	{
		//高速自机狙
		int x = (position2.x) - (position1.x);
		int y = (position2.y) - (position1.y);
		int z = pow(x*x + y*y, 0.5);
		int posx = 8 * x / z;
		int posy = 8 * y / z;

		pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetPosition(position1.x, position1.y);
		pSprite->SetVelocity(posx * 2, posy * 2);

		g_pGame->AddSprite(pSprite);
	}
	else if (GetBitmap() == g_pCaonimaBitmap[1])
	{
		//随机弹
		for (int i = 0; i < 20; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pCaonimaBitmap[2])
	{
		//弧形弹幕
		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(0, 10);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(4, 9);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(7, 7);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(9, 4);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(10, 0);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(-4, 9);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(-7, 7);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(-9, 4);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);

		pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
		pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
		pSprite->SetVelocity(-10, 0);
		pSprite->SetPosition(position1);
		g_pGame->AddSprite(pSprite);
	}
	else if (GetBitmap() == g_pDragonBitmap[0])
	{
		//方形弹幕
		for (int i = 0; i < 8; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(i, 8 - i);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
		for (int i = 1; i < 8; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(-i, 8 - i);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pDragonBitmap[1])
	{
		//弧形弹幕
		for (int i = 0; i < 30; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[2], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(10 * cos(double((360 / 30)*i)) + rand() % 3 - 1, 10 * sin(double((360 / 30)*i)) + rand() % 3 - 1);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pStoneBitmap[0])
	{
		//方形弹幕
		for (int i = 0; i < 8; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(i, 8 - i);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
		for (int i = 1; i < 8; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(-i, 8 - i);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pStoneBitmap[1])
	{
		//弧形弹幕
		for (int i = 0; i < 30; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[3], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(10 * cos(double((360 / 30)*i)) + rand() % 3 - 1, 10 * sin(double((360 / 30)*i)) + rand() % 3 - 1);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pStoneBitmap[2])
	{
		int x = (position2.x) - (position1.x);
		int y = (position2.y) - (position1.y);
		int z = pow(x*x + y*y, 0.5);
		int posx = 10 * x / z;
		int posy = 10 * y / z;
		//自机狙
		for (int i = 0; i < 3; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[3], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetPosition(position1.x, position1.y + i * 100);
			pSprite->SetVelocity(posx, posy);

			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pStoneBitmap[3])
	{
		//随机弹
		for (int i = 0; i < 10; ++i)
		{
			pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
			pSprite->SetPosition(position1);
			g_pGame->AddSprite(pSprite);
		}
	}
	else if (GetBitmap() == g_pCaonimaBitmap[3])   //BOSS1
	{
		if ((g_sBoss1->GetDamage() / g_sBoss1->GetHp()) < 0.25)
		{
			for (int i = 0; i < 20; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
			int x = (position2.x) - (position1.x);
			int y = (position2.y) - (position1.y);
			int z = pow(x*x + y*y, 0.5);
			int posx = 10 * x / z;
			int posy = 10 * y / z;
			//自机狙
			pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
			pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
			pSprite->SetPosition(position1.x, position1.y);
			pSprite->SetVelocity(posx, posy);

			g_pGame->AddSprite(pSprite);
		}
		else if ((g_sBoss1->GetDamage() / g_sBoss1->GetHp()) < 0.5)
		{
			for (int i = 0; i < 30; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[3], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
		else if ((g_sBoss1->GetDamage() / g_sBoss1->GetHp()) < 0.75)
		{
			for (int i = 0; i < 35; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(10 * cos(double((360 / 36)*i)) + rand() % 3 - 1, 10 * sin(double((360 / 36)*i)) + rand() % 3 - 1);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
			for (int i = 0; i < 20; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[2], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 10 - 5, rand() % 10 - 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
		else
		{
			for (int i = 0; i < 50; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
	}
	else if (GetBitmap() == g_pDragonBitmap[2])  //BOSS2
	{
		if ((g_sBoss2->GetDamage() / g_sBoss2->GetHp()) < 0.25)
		{
			for (int i = 0; i < 40; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
		else if ((g_sBoss2->GetDamage() / g_sBoss2->GetHp()) < 0.5)
		{
			for (int i = 1; i < 30; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(10 * cos(double(i*(360 / 15))), 10 * sin(double(i*(360 / 15))));
				pSprite->SetPosition(position3.x + 100, position3.y + 50);
				g_pGame->AddSprite(pSprite);
			}
			for (int i = 1; i < 30; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(-10 * cos(double(i*(60 / 15))), 10 * sin(double(i*(60 / 15))));
				pSprite->SetPosition(position4.x - 100, position4.y + 50);
				g_pGame->AddSprite(pSprite);
			}
			int x = (position2.x) - (position1.x);
			int y = (position2.y) - (position1.y);
			int z = pow(x*x + y*y, 0.5);
			int posx = 10 * x / z;
			int posy = 10 * y / z;
			//自机狙
			for (int i = 0; i < 5; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetPosition(position1.x + rand() % 20 - 10, position1.y + rand() % 20 - 10);
				pSprite->SetVelocity(posx + rand() % 20 - 10, posy + rand() % 20 - 10);

				g_pGame->AddSprite(pSprite);
			}
			for (int i = 0; i < 3; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetPosition(position3);
				pSprite->SetVelocity(posx + rand() % 20 - 10, posy + rand() % 20 - 10);

				g_pGame->AddSprite(pSprite);
			}
			for (int i = 0; i < 3; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetPosition(position4);
				pSprite->SetVelocity(posx + rand() % 20 - 10, posy + rand() % 20 - 10);

				g_pGame->AddSprite(pSprite);
			}
		}
		else if ((g_sBoss2->GetDamage() / g_sBoss2->GetHp()) < 0.75)
		{
			for (int i = 0; i < 30; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(10 * cos(double((360 / 30)*i)) + rand() % 3 - 1, 10 * sin(double((360 / 30)*i)) + rand() % 3 - 1);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
			int x = (position2.x) - (position1.x);
			int y = (position2.y) - (position1.y);
			int z = pow(x*x + y*y, 0.5);
			int posx = 10 * x / z;
			int posy = 10 * y / z;
			//跟随。。。
			SetVelocity(posx, posy);
		}
		else
		{
			for (int i = 0; i < 60; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[1], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(10 * cos(double((360 / 36)*i)) + rand() % 3 - 1, 10 * sin(double((360 / 36)*i)) + rand() % 3 - 1);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
			int x = (position2.x) - (position1.x);
			int y = (position2.y) - (position1.y);
			int z = pow(x*x + y*y, 0.5);
			int posx = 10 * x / z;
			int posy = 10 * y / z;
			//跟随。。。
			SetVelocity(posx, posy);
		}
	}
	else if (GetBitmap() == g_pQQBitmap)//BOSS3
	{
		if ((g_sBoss3->GetDamage() / g_sBoss3->GetHp()) < 0.25)
		{
			for (int i = 0; i < 50; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[0], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
		else if ((g_sBoss3->GetDamage() / g_sBoss3->GetHp()) < 0.5)
		{
			for (int i = 0; i < 15; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[3], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetVelocity(rand() % 30 - 15, rand() % 5 + 5);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
			int x = (position2.x) - (position1.x);
			int y = (position2.y) - (position1.y);
			int z = pow(x*x + y*y, 0.5);
			int posx = 10 * x / z;
			int posy = 10 * y / z;
			for (int i = 0; i < 3; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetPosition(position3);
				pSprite->SetVelocity(posx + rand() % 20 - 10, posy + rand() % 20 - 10);

				g_pGame->AddSprite(pSprite);
			}
			for (int i = 0; i < 3; ++i)
			{
				pSprite = new Sprite(g_pEnemyBulletBitmap[4], rcBounds, BA_DIE);
				pSprite->SetSpriteAttribute(SAT_ENEMYBULLET);
				pSprite->SetPosition(position4);
				pSprite->SetVelocity(posx + rand() % 20 - 10, posy + rand() % 20 - 10);

				g_pGame->AddSprite(pSprite);
			}
		}
		else if ((g_sBoss3->GetDamage() / g_sBoss3->GetHp()) < 0.75)
		{
			for (int i = 0; i < 20; ++i)
			{
				pSprite = new Sprite(g_pqq1Bitmap, rcBounds, BA_BOUNCE);
				pSprite->SetSpriteAttribute(SAT_ENEMY);
				pSprite->SetVelocity(rand() % 30 - 15, 5 - rand() % 2);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
		else
		{
			pSprite = new Sprite(g_pqq2Bitmap, rcBounds, BA_BOUNCE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetVelocity(rand() % 30 - 15, 5 - rand() % 2);
			pSprite->SetPosition(position3);
			g_pGame->AddSprite(pSprite);

			pSprite = new Sprite(g_pqq2Bitmap, rcBounds, BA_BOUNCE);
			pSprite->SetSpriteAttribute(SAT_ENEMY);
			pSprite->SetVelocity(rand() % 30 - 15, 5 - rand() % 2);
			pSprite->SetPosition(position4);
			g_pGame->AddSprite(pSprite);

			for (int i = 0; i < 20; ++i)
			{
				pSprite = new Sprite(g_pqq2Bitmap, rcBounds, BA_BOUNCE);
				pSprite->SetSpriteAttribute(SAT_ENEMY);
				pSprite->SetVelocity(rand() % 30 - 15, 5 - rand() % 2);
				pSprite->SetPosition(position1);
				g_pGame->AddSprite(pSprite);
			}
		}
	}
	// Set the missile sprite's position and return it
}

void Sprite::Draw(HDC hDC)
{
	// Draw the sprite if it isn't hidden
	if (m_pBitmap != NULL && !m_bHidden)
	{
		// Draw the appropriate frame, if necessary
		if (m_iNumFrames == 1 && m_pBitmap != g_pBossHpBitmap1)
			m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, TRUE);
		else if (m_pBitmap != g_pBossHpBitmap1)
			m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
				m_iCurFrame * GetWidth(), 0, GetWidth(), GetHeight(), TRUE);
		else if (g_bStage1 == false)
			m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
				0, 0, GetWidth()*((g_sBoss1->GetHp() - g_sBoss1->GetDamage()) / g_sBoss1->GetHp()), GetHeight(), TRUE);
		else if (g_bStage2 == false)
			m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
				0, 0, GetWidth()*((g_sBoss2->GetHp() - g_sBoss2->GetDamage()) / g_sBoss2->GetHp()), GetHeight(), TRUE);
		else if (g_bStage3 == false)
			m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
				0, 0, GetWidth()*((g_sBoss3->GetHp() - g_sBoss3->GetDamage()) / g_sBoss3->GetHp()), GetHeight(), TRUE);
	}
}