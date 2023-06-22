#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"

typedef struct {
	INT8 speed;
	INT8 direction;
} PROJECTILE_DATA;

const UINT8 projectileAnim[] = { 2, 0, 1 };

void CreatePlayerProjectile(UINT16 x, UINT16 y, INT8 direction) BANKED {
	Sprite* spr = SpriteManagerAdd(SpriteProjectile, x, y + 4);
	PROJECTILE_DATA* data = (PROJECTILE_DATA*)spr->custom_data;

	data->direction = direction;
	// PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

void START() {
	SetSpriteAnim(THIS, projectileAnim, 15);
	PROJECTILE_DATA* data = (PROJECTILE_DATA*)THIS->custom_data;
	data->speed = 2;
	data->direction = 1;
}

void UPDATE() {
	PROJECTILE_DATA* data = (PROJECTILE_DATA*)THIS->custom_data;

    if (TranslateSprite(THIS, (data->speed) * data->direction << delta_time, 0))
		SpriteManagerRemoveSprite(THIS);
}

void DESTROY() {
}