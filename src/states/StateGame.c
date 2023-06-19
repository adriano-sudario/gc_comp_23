#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Music.h"
#include "Print.h"

DECLARE_MUSIC(template);

IMPORT_MAP(map);
IMPORT_MAP(hud);

IMPORT_TILES(font);

UINT8 collision_tiles[] = { 1, 0 };

INT8 playMusic = 1;

void enableSounds() {
	NR52_REG = 0x80;
	NR51_REG = 0xFF;
	NR50_REG = 0x77;
}

void START() {
	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, collision_tiles, 0);
	INIT_HUD(hud);
	INIT_CONSOLE(font, 1);
	INIT_FONT(font, PRINT_BKG);
	// PRINT_POS(0, 0);
	// Printf("TESTE");
	enableSounds();

	if (playMusic)
		PlayMusic(template, 1);
}

void UPDATE() {
}
