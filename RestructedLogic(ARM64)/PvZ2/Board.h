#pragma once

#define GRID_TILE_WIDTH 64.0f
#define GRID_TILE_HEIGHT 76.0f
#define GRID_TILE_TOP 160.0f
#define GRID_TILE_LEFT 200.0f

#define BOARD_START_POS 232.0f
#define BOARD_END_POS 776.0f

#ifdef __arm__
#define INITIAL_BOARD_OFFSET 148
#define LAWNRECT_BOARD_OFFSET 676
#elif __aarch64__
#define INITIAL_BOARD_OFFSET 216
#define LAWNRECT_BOARD_OFFSET 864
#endif

class Board
{
public:
	char pad_0000[INITIAL_BOARD_OFFSET]; //0x0000
	int m_columnCount; //0x0094
	int m_rowCount; //0x0098
	char pad_009C[LAWNRECT_BOARD_OFFSET]; //0x009C
	Rect m_lawnRect; //0x0340
};

uint_t getLawnApp();
uint_t getSexyApp();