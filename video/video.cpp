#include "video.h"

////////////////////////////////////////////////////////////////////////////////
// mode tables

tile_mode tilemode_grid[6] =
{
        BG_CHAR8, BG_CHAR8, BG_CHAR8,
        BG_PIXEL, BG_PIXEL, BG_PIXEL
};

bg_grids bgmodes = {
        // DISP_A bg modes (page 95)
        {
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_TEXT},       {BG_TEXT}       },
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_TEXT},       {BG_AFFINE}     },
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_AFFINE},     {BG_AFFINE}     },
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_TEXT},       {BG_AFFINE_EXT} },
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_AFFINE},     {BG_AFFINE_EXT} },
                { {BG_TEXT_3D}, {BG_TEXT},    {BG_AFFINE_EXT}, {BG_AFFINE_EXT} },
                { {BG_3D},      {BG_INVALID}, {BG_LARGE},      {BG_INVALID}    },
                { {BG_INVALID}, {BG_INVALID}, {BG_INVALID},    {BG_INVALID}    }
        },
        // DISP_B bg modes (page 96)
        {
                { {BG_TEXT},    {BG_TEXT},    {BG_TEXT},       {BG_TEXT}       },
                { {BG_TEXT},    {BG_TEXT},    {BG_TEXT},       {BG_AFFINE}     },
                { {BG_TEXT},    {BG_TEXT},    {BG_AFFINE},     {BG_AFFINE}     },
                { {BG_TEXT},    {BG_TEXT},    {BG_TEXT},       {BG_AFFINE_EXT} },
                { {BG_TEXT},    {BG_TEXT},    {BG_AFFINE},     {BG_AFFINE_EXT} },
                { {BG_TEXT},    {BG_TEXT},    {BG_AFFINE_EXT}, {BG_AFFINE_EXT} },
                { {BG_INVALID}, {BG_INVALID}, {BG_INVALID},    {BG_INVALID}    },
                { {BG_INVALID}, {BG_INVALID}, {BG_INVALID},    {BG_INVALID}    }
        }
};

#define M(x,y) x,y,x*y

mode_grids modes = {
        // DISP_A modes
        {
                { {M(256,256)}, {M(128,128)},   {M(128, 128)},   
				  {M(128,128)}, {M(128,128)},   {M(512,1024)} },
                { {M(512,256)}, {M(256,256)},   {M(256,256)},   
				  {M(256,256)}, {M(256,256)},   {M(1024,512)} },
                { {M(256,512)}, {M(512,512)},   {M(512,512)},   
				  {M(512,512)}, {M(512,512)},   {M(0,0)}      },
                { {M(512,512)}, {M(1024,1024)}, {M(1024,1024)}, 
				  {M(512,512)}, {M(512,512)},   {M(0,0)}      }
        },
        // DISP_B modes
        {
                { {M(256,256)}, {M(128,128)},   {M(128,128)},   
				  {M(128,128)}, {M(128,128)},   {M(0,0)} },
                { {M(512,256)}, {M(256,256)},   {M(256,256)},   
				  {M(256,256)}, {M(256,256)},   {M(0,0)} },
                { {M(256,512)}, {M(512,512)},   {M(512,512)},   
				  {M(512,256)}, {M(0,0)},       {M(0,0)} },
                { {M(512,512)}, {M(1024,1024)}, {M(1024,1024)}, 
				  {M(0,0)},     {M(0,0)},       {M(0,0)} }
        }
};

oam_grids oam_modes = {
	{{M( 8, 8)}, {M(16,16)}, {M(32,32)}, {M(64,64)}},
	{{M(16, 8)}, {M(32, 8)}, {M(32,16)}, {M(64,32)}},
	{{M( 8,16)}, {M( 8,32)}, {M(16,32)}, {M(32,64)}},
	{{M( 0, 0)}, {M( 0, 0)}, {M( 0, 0)}, {M( 0, 0)}}
};

#undef M


////////////////////////////////////////////////////////////////////////////////
// Abstract BG

void CAbstractBG::calcBases()
	{
		screen_base = (control << 3)  & 0x0F800; // 0x0800 * screen base
		char_base   = (control << 12) & 0x3C000; // 0x4000 * character base
		
		if (disp == DISP_A)
		{
			screen_base |= (dcontrol >> 11) & 0x70000;
			char_base   |= (dcontrol >> 8)  & 0x70000;
			vram_bank    = (dcontrol >> 18) & 0x3;
			disp_mode    = (display_mode)((dcontrol >> 16) & 0x3);
		} else
		{
			screen_base |= (dcontrol >> 11) & 0x70000;
			char_base   |= (dcontrol >> 8)  & 0x70000;
			vram_bank = 0;
			disp_mode = (display_mode)((dcontrol >> 16) & 0x1);
		}
	}
