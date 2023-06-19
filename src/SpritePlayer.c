#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Scroll.h"
#include "Print.h"
#include "Constants.h"

const UINT8 animIdle[] = { 4, 0, 1, 2, 1 };
const UINT8 animWalk[] = { 4, 3, 4, 5, 6 };
const UINT8 animJump[] = { 1, 7 };
const UINT8 speed = 1;
const UINT8 jumpForce = 45;
UINT8 life = 3;
UINT8 isJumpButtonHeld = 1;
INT8 verticalForce = 0;
UINT8 isOnFloor = 0;

void UpdateLifeHud() {
	for (UINT8 i = 0; i < 3; ++i)
		UPDATE_HUD_TILE(16 + i, 0, i < life ? 1 : 2);
}

void TakeDamage(UINT8 amount) {
	life -= amount;
	UpdateLifeHud();

	if (life <= 0) {
		SetState(StateGame);
		PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
	}
}

void ManageInputs() {
	// if (KEY_PRESSED(J_UP)) {
	// 	TranslateSprite(THIS, 0, -speed << delta_time);
	// 	SetSpriteAnim(THIS, anim_walk, 15);
	// }

	// if (KEY_PRESSED(J_DOWN)) {
	// 	TranslateSprite(THIS, 0, speed << delta_time);
	// 	SetSpriteAnim(THIS, anim_walk, 15);
	// }

	if (isOnFloor && KEY_PRESSED(J_A) && isJumpButtonHeld) {
		verticalForce = -(jumpForce + GRAVITY);
		isJumpButtonHeld = 0;
		isOnFloor = 0;
	} else if (KEY_RELEASED(J_A) && !isJumpButtonHeld) {
		if (verticalForce < 0)
			verticalForce = 0;
		
		isJumpButtonHeld = 1;
	}

	if (KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -speed << delta_time, 0);
		SetSpriteAnim(THIS, animWalk, 15);
		THIS->mirror = V_MIRROR;
	}

	if (KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, speed << delta_time, 0);
		SetSpriteAnim(THIS, animWalk, 15);
		THIS->mirror = NO_MIRROR;
	}

	if (keys == 0)
		SetSpriteAnim(THIS, animIdle, 15);
}

void ApplyGravity() {
	verticalForce += GRAVITY;

	if (TranslateSprite(THIS, 0, (verticalForce / 10) << delta_time)) {
		verticalForce = 0;
		isOnFloor = 1;
	}
	
	if (!isOnFloor) {
		SetSpriteAnim(THIS, animJump, 15);
	}
}

void START() {
}

void UPDATE() {
	ManageInputs();
	ApplyGravity();
	
	UINT8 i;
	Sprite* spr;

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteEnemy && CheckCollision(THIS, spr)) {
			SpriteManagerRemove(i);
			TakeDamage(1);
		}
	}

	// DPRINT(0, 0, "x:%d y:%d  ", THIS->x, THIS->y);
	// PRINT_POS(0, 0);
	// Printf("x:%d y:%d v:%d  ", THIS->x, THIS->y, verticalForce);
}

void DESTROY() {
}