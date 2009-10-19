enum display_mode
{
        DM_OFF,
        DM_GRAPHIC,
        DM_VRAM,
        DM_RAM
};

enum bg_mode {
        BG_TEXT,
        BG_AFFINE,
        BG_AFFINE_EXT,
        BG_3D,
        BG_TEXT_3D,
        BG_LARGE,
        BG_INVALID
};

enum screen {
        DISP_A,
        DISP_B
};

enum bgnum {
        BG_0,
        BG_1,
        BG_2,
        BG_3
};

enum tile_mode
{
        BG_PIXEL, // pixel (direct mode)
        BG_CHAR8  // tile based ()
};

enum object_mode {
	OM_NORMAL = 0,
	OM_TRANS  = 1,
	OM_WINDOW = 2,
	OM_BITMAP = 3
};

struct mode_setting
{
        int w;
        int h;
		int pixels; // w*h
};

typedef mode_setting mode_row[6];
typedef mode_row mode_grid[4];
#ifndef _MODES_H_
#define _MODES_H_

typedef mode_grid mode_grids[2];

struct bgmode_setting
{
        bg_mode mode;
};
typedef bgmode_setting bg_row[4];
typedef bg_row bg_grid[8];
typedef bg_grid bg_grids[2];

typedef mode_setting oam_grid[4];
typedef oam_grid oam_grids[4];


extern tile_mode tilemode_grid[6];
extern bg_grids bgmodes;
extern mode_grids modes;
extern oam_grids oam_modes;

#endif
