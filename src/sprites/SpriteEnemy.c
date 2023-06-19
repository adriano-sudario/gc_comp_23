#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"

typedef struct {
	INT8 vy;
} CUSTOM_DATA;

void START() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	data->vy = 1;
}

void UPDATE() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	if (TranslateSprite(THIS, 0, data->vy << delta_time)) {
		data->vy = -data->vy;
		PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);
	}
}

void DESTROY() {
}