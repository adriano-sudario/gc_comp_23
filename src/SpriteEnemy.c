#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"

extern const UINT8 SOUNDS_ON;

typedef struct {
	INT8 speed;
} CUSTOM_DATA;

const UINT8 enemyAnim[] = { 4, 0, 1, 2, 1 };

void START() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	data->speed = 1;
	SetSpriteAnim(THIS, enemyAnim, 15);
}

void UPDATE() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	INT8 willFall = 0;
	INT8 turnAround = 0;
	INT8 horizontalForce = data->speed << delta_time;

	if (TranslateSprite(THIS, horizontalForce, 0)) {
		turnAround = 1;

		if (SOUNDS_ON)
			PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);
	} else if (!TranslateSprite(THIS, 0, 1)) {
		TranslateSprite(THIS, -horizontalForce, -1);
		turnAround = 1;
	}

	if (turnAround) {
		data->speed = -data->speed;
		THIS->mirror = data->speed < 0 ? V_MIRROR : NO_MIRROR;
	}
}

void DESTROY() {
}