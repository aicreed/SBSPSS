/*=========================================================================

	hdbarrel.cpp

	Author:		CRB
	Created: 
	Project:	Spongebob
	Purpose: 

	Copyright (c) 2001 Climax Development Ltd

===========================================================================*/

#ifndef __HAZARD_HDBARREL_H__
#include "hazard\hdbarrel.h"
#endif

#ifndef __LAYER_COLLISION_H__
#include "level\layercollision.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CNpcDualPlatformBarrelHazard::init()
{
	CNpcHazard::init();

	m_npcPath.setPathType( CNpcPath::SINGLE_USE_PATH );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CNpcDualPlatformBarrelHazard::processMovement( int _frames )
{
	s32 maxHeight = 20;
	s32 distX, distY;
	s32 fallSpeed = 3;
	s8 yMovement = fallSpeed * _frames;
	s32 groundHeight;

	s32 moveX = 0;
	s32 moveY = 0;

	// ignore y component of waypoint, since we are stuck to the ground

	bool pathComplete;

	if ( m_npcPath.thinkFlat( Pos, &pathComplete, &distX, &distY, &m_heading ) )
	{
		if ( pathComplete )
		{
			// reset

			Pos = m_base;
			m_npcPath.resetPath();

			return;
		}
		else
		{
			// check for vertical movement

			groundHeight = m_layerCollision->getHeightFromGround( Pos.vx, Pos.vy, yMovement + 16 );

			if ( groundHeight <= yMovement )
			{
				// groundHeight <= yMovement indicates either just above ground or on or below ground

				moveY = groundHeight;
			}
			else
			{
				// fall

				moveY = yMovement;
			}
		}
	}
	else
	{
		// check for collision

		distX = distX / abs( distX );

		if ( m_layerCollision->getHeightFromGround( Pos.vx + ( distX * 3 * _frames ), Pos.vy ) < -maxHeight )
		{
			// there is an obstacle in the way, increment the path point (hopefully this will resolve the problem)

			m_npcPath.incPath();
		}
		else
		{
			// check for vertical movement

			groundHeight = m_layerCollision->getHeightFromGround( Pos.vx, Pos.vy, yMovement + 16 );

			if ( groundHeight <= yMovement )
			{
				// groundHeight <= yMovement indicates either just above ground or on or below ground

				moveX = distX * 3 * _frames;
				moveY = groundHeight;
			}
			else
			{
				// fall

				moveY = yMovement;
			}
		}
	}

	Pos.vx += moveX;
	Pos.vy += moveY;

	s32 minY, maxY;

	m_npcPath.getPathYExtents( &minY, &maxY );

	if ( Pos.vy > maxY )
	{
		Pos = m_base;
		m_npcPath.resetPath();
	}
}