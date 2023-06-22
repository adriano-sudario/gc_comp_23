#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Sound.h"

typedef struct {
	INT8 speed;
} CUSTOM_DATA;

void START() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	data->speed = 1;
}

void UPDATE() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	if (TranslateSprite(THIS, 0, data->speed << delta_time)) {
		data->speed = -data->speed;
		// PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);
	}
}

void DESTROY() {
}