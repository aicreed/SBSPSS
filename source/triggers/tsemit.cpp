/*=========================================================================

	tsemit.cpp

	Author:		CRB
	Created:	
	Project:	Spongebob
	Purpose:	

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef	__TRIGGERS_TSEMIT_H__
#include "triggers\tsemit.h"
#endif

#ifndef __GAME_GAME_H__
#include	"game\game.h"
#endif

#include "fx\fxsteam.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	CSteamEmitterTrigger::init()
{
	CTrigger::init();

	m_soundId = (int) NOT_PLAYING;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	CSteamEmitterTrigger::think(int _frames)
{
	if ( m_soundId == NOT_PLAYING )
	{
		m_soundId = (int) CSoundMediator::playSfx( CSoundMediator::SFX_HAZARD__STEAM, true );
	}

	CTrigger::think( _frames );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	CSteamEmitterTrigger::shutdown()
{
	if ( m_soundId != NOT_PLAYING )
	{
		CSoundMediator::stopAndUnlockSfx( (xmPlayingId) m_soundId );
	}

	CTrigger::shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	CSteamEmitterTrigger::setPositionAndSize(int _x,int _y,int _w,int _h)
{
	CTrigger::setPositionAndSize( _x, _y, _w, _h );

	m_effect = CFX::Create( CFX::FX_TYPE_STEAM, Pos );
	CFXSteam *steam = (CFXSteam *) m_effect;
	steam->SetSize( ( _w >> 4 ) * ONE );
	DVECTOR velocity;
	velocity.vx = 0;
	velocity.vy = -_h >> 4;
	steam->SetVel( velocity );
}
