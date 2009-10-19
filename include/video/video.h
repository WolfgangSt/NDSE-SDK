#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "modes.h"
namespace NDSE {
#include "../NDSE_simple.h"
};

class CAbstractBG
{
public:
	typedef double matrix[16];
	unsigned long screen_base;
	unsigned long char_base;
	unsigned long color_mode;
	unsigned long vram_bank;
	display_mode disp_mode;
	tile_mode tilemode;
	bool direct_mode; // (non paletted)
	bool valid;
	matrix mat;       // holding linear transform
	double affine[2]; // cant directly encode to mat due to scaling
	long offset[2];
	unsigned long control;
	unsigned long dcontrol;
	bg_mode bgmode;
	bgnum bg;
	screen disp;
	mode_setting mode;
	unsigned long enabled;
	unsigned long ignore_flush;

	void calcBases();
};

#endif
