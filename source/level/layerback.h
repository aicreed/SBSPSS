/************************/
/*** Back Layer Class ***/
/************************/

#ifndef __LAYER_BACK_H__
#define __LAYER_BACK_H__


/*****************************************************************************/
class CLayerBack : public CLayerTile
{
public:
		CLayerBack(sLayerHdr *Hdr,sTile *TileList,sTri *TriList,sQuad *QuadList,sVtx *VtxList);
		~CLayerBack();

		void	init(DVECTOR &MapPos,int Shift,int Width,int Height);
		void	shutdown();
		void	think(DVECTOR &MapPos);
		void	render();

protected:

};



/*****************************************************************************/

#endif