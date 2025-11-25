#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "z64player.h"

extern FloorType sPlayerFloorType;

RECOMP_HOOK ("func_808373F8") void InfiniteHops(PlayState* play, Player* this, u16 sfxId) {
    f32 speed;
    f32 speedXZ;
    
    // // Make it so holding A stops hops counter from decreasing by raising it
    // if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->cur.button, BTN_A)){
    //     this->remainingHopsCounter++;
    // }
    // if (this->remainingHopsCounter > 5){
    //     this->remainingHopsCounter = 5;
    // }

    //Raise minimum hopping speed
    if (this->speedXZ < 8.0f) {
        this->speedXZ = 8.0f;
    }
    
}

Player* gPlayer;
// Allows Player to use floor switches as Deku.
RECOMP_HOOK ("Player_Init") void SavePlayerForDekuSwitches(Actor* thisx, PlayState* play) {
    gPlayer = (Player*)thisx;
    recomp_printf("floor type %d\n", sPlayerFloorType);
}

RECOMP_HOOK_RETURN ("Player_Init") void DekuSwitches(PlayState* play, Player* this, u16 sfxId) {
    if (gPlayer->transformation == PLAYER_FORM_DEKU) {
        gPlayer->actor.flags |= ACTOR_FLAG_CAN_PRESS_SWITCHES;
    }
}

#include "overlays/actors/ovl_En_Torch2/z_en_torch2.h"
// The same as above, but for the deku elegy statue.
RECOMP_HOOK ("EnTorch2_Init") void ElegySwitches(Actor* thisx, PlayState* play) {
    EnTorch2* this = (EnTorch2*)thisx;
    
    if (this->actor.params == TORCH2_PARAM_DEKU) {
        this->actor.flags |= ACTOR_FLAG_CAN_PRESS_SWITCHES;
    }
}

// Start of swimming hell.

void func_80834140(PlayState* play, Player* this, PlayerAnimationHeader* anim);
void func_808345C8(void);
void func_8083B8D0(PlayState* play, Player* this);
s32 func_808373F8(PlayState* play, Player* this, u16 sfxId);
void func_80169EFC(PlayState* this);
void func_8083B930(PlayState* play, Player* this);
void func_8083B32C(PlayState* play, Player* this, f32 arg2);
void Player_SetupTurnInPlace(PlayState* play, Player* this, s16 yaw);
void Player_Action_33(Player* this, PlayState* play);
void Player_Action_49(Player* this, PlayState* play);
void Player_Action_28(Player* this, PlayState* play);
void Player_Action_WaitForPutAway(Player* this, PlayState* play);
s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3);
void Player_Action_1(Player* this, PlayState* play);
void Player_Action_43(Player* this, PlayState* play);
void Player_Action_61(Player* this, PlayState* play);
void Player_Action_54(Player* this, PlayState* play);
void Player_Action_62(Player* this, PlayState* play);
void Player_Action_57(Player* this, PlayState* play);
void Player_Action_58(Player* this, PlayState* play);
void Player_Action_59(Player* this, PlayState* play);
void Player_Action_60(Player* this, PlayState* play);
void Player_Action_55(Player* this, PlayState* play);
void Player_Action_25(Player* this, PlayState* play);
void Player_Action_27(Player* this, PlayState* play);
void Player_Action_96(Player* this, PlayState* play);
void Player_Action_82(Player* this, PlayState* play);
void Player_Action_83(Player* this, PlayState* play);
s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3);
void Player_Action_56(Player* this, PlayState* play);
s32 func_808381F8(PlayState* play, Player* this);
s32 func_80835428(PlayState* play, Player* this);
void func_8082DC64(PlayState* play, Player* this);
s32 func_80837730(PlayState* play, Player* this, f32 arg2, s32 scale);
void Player_Anim_PlayOnceMorph(PlayState* play, Player* this, PlayerAnimationHeader* anim);
f32 sControlStickMagnitude;
FloorProperty sPrevFloorProperty;
f32 sPlayerYDistToFloor;
Input* sPlayerControlInput;
void func_80834D50(PlayState* play, Player* this, PlayerAnimationHeader* anim, f32 speed, u16 sfxId);
void func_808373A4(PlayState* play, Player* this);
void Player_AnimSfx_PlayVoice(Player* this, u16 sfxId);
void Player_StopHorizontalMovement(Player* this);
void func_8082DD2C(PlayState* play, Player* this);
f32 func_80835CD8(PlayState* play, Player* this, Vec3f* arg2, Vec3f* pos, CollisionPoly** outPoly, s32* outBgId);
void func_80834DB8(Player* this, PlayerAnimationHeader* anim, f32 speed, PlayState* play);
s32 func_80837DEC(Player* this, PlayState* play);
void Player_Anim_PlayLoop(PlayState* play, Player* this, PlayerAnimationHeader* anim);
void Player_Action_CsAction(Player* this, PlayState* play);
void Player_Anim_PlayOnce(PlayState* play, Player* this, PlayerAnimationHeader* anim);
u32 sPlayerTouchedWallFlags;
void func_8082DAD4(Player* this);

Vec3f D_8085D154 = { 0.0f, 0.0f, 100.0f };

extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_down;
extern PlayerAnimationHeader gPlayerAnim_link_normal_jump;
extern PlayerAnimationHeader gPlayerAnim_link_normal_run_jump;
extern PlayerAnimationHeader gPlayerAnim_link_normal_run_jump_water_fall;
extern PlayerAnimationHeader gPlayerAnim_link_normal_landing_wait;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_deep_start;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_get;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_deep_end;
extern PlayerAnimationHeader gPlayerAnim_link_normal_250jump_start;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_swim_15step_up;
extern PlayerAnimationHeader gPlayerAnim_link_normal_150step_up;
extern PlayerAnimationHeader gPlayerAnim_link_normal_100step_up;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_wait2swim_wait;
extern PlayerAnimationHeader gPlayerAnim_link_swimer_land2swim_wait;

// RECOMP_HOOK ("Player_Action_25") void Player_Action_25print(Player* this, PlayState* play) {
//     recomp_printf("PA25\n");
// }

// RECOMP_HOOK ("Player_Action_27") void Player_Action_27print(Player* this, PlayState* play) {
//     recomp_printf("PA27\n");
// }

// RECOMP_HOOK ("Player_Action_28") void Player_Action_28print(Player* this, PlayState* play) {
//     recomp_printf("PA28\n");
// }

// RECOMP_HOOK ("Player_Action_82") void Player_Action_82print(Player* this, PlayState* play) {
//     recomp_printf("PA82\n");
// }

// RECOMP_HOOK ("Player_Action_83") void Player_Action_83print(Player* this, PlayState* play) {
//     recomp_printf("PA83\n");
// }

// RECOMP_HOOK ("Player_Action_96") void Player_Action_96print(Player* this, PlayState* play) {
//     recomp_printf("PA96\n");
// }

// RECOMP_HOOK ("Player_Action_54") void Player_Action_54print(Player* this, PlayState* play) {
//     recomp_printf("PA54 god i hope im swimming rn\n");
// }

typedef struct {
    /* 0x0 */ PlayerAnimationHeader* unk_0;
    /* 0x4 */ PlayerAnimationHeader* unk_4;
    /* 0x8 */ PlayerAnimationHeader* unk_8;
} struct_8085C2A4; // size = 0xC

extern struct_8085C2A4 D_8085C2A4[];

// Big thing related to Deku / Goron Voiding in water. Patched currently in a way that prevents Deku from voiding if hops reach 0.
// where the FUCK is the function preventing him from swimming when entering water?????
RECOMP_PATCH void func_8083BB4C(PlayState* play, Player* this) {
    f32 sp1C = this->actor.depthInWater - this->ageProperties->unk_2C;

    if (sp1C < 0.0f) {
        this->underwaterTimer = 0;
        if ((this->transformation == PLAYER_FORM_ZORA) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            this->currentBoots = PLAYER_BOOTS_ZORA_LAND;
        }
        Audio_SetBaseFilter(0);
    } else {
        Audio_SetBaseFilter(0x20);
        if ((this->transformation == PLAYER_FORM_ZORA) || (sp1C < 10.0f)) {
            this->underwaterTimer = 0;
        } else if (this->underwaterTimer < 300) {
            this->underwaterTimer++;
        }
    }

    if ((this->actor.parent == NULL) && (Player_Action_33 != this->actionFunc) &&
        (Player_Action_49 != this->actionFunc) &&
        ((Player_Action_28 != this->actionFunc) || (this->actor.velocity.y < -2.0f))) {
        if (this->ageProperties->unk_2C < this->actor.depthInWater) {
            if (this->transformation == PLAYER_FORM_GORON) {
                // # Death Function.
                func_80834140(play, this, &gPlayerAnim_link_swimer_swim_down);
                // # Checks for Deku Mask, and allows Link to spawn as Human if you have it & assumedly die.
                func_808345C8();
                func_8083B8D0(play, this);
            } else if (this->transformation == PLAYER_FORM_DEKU) {
                // # If hops not zero, go to Deku Hopping function.
                if (this->remainingHopsCounter != 0) {
                    func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);} 
                    else {
                    if ((play->sceneId == SCENE_20SICHITAI) && (this->unk_3CF == 0)) {
                        if (CHECK_EVENTINF(EVENTINF_50)) {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 2);
                        } else {
                            play->nextEntrance = ENTRANCE(TOURIST_INFORMATION, 1);
                        }
                        // play->transitionTrigger = TRANS_TRIGGER_START;
                        // play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
                        // this->stateFlags1 |= PLAYER_STATE1_200;
                        // Audio_PlaySfx(NA_SE_SY_DEKUNUTS_JUMP_FAILED);
                    } else if ((this->unk_3CF == 0) &&
                               ((play->sceneId == SCENE_30GYOSON) || (play->sceneId == SCENE_31MISAKI) ||
                                (play->sceneId == SCENE_TORIDE))) {
                        // func_80169EFC(play);
                        // func_808345C8();
                    } //else {
                    //     Player_SetAction(play, this, Player_Action_1, 0);
                    //     this->stateFlags1 |= PLAYER_STATE1_20000000;
                    // }
                    func_8083B8D0(play, this);
                    if ((this->actor.depthInWater - this->ageProperties->unk_2C)) {
                        Player_SetAction(play, this, Player_Action_54, 0);
                        Player_Anim_PlayOnceMorph(play, this,
                                      (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)
                                          ? &gPlayerAnim_link_swimer_wait2swim_wait
                                          : &gPlayerAnim_link_swimer_land2swim_wait);
                        (this->stateFlags1 & PLAYER_STATE1_8000000);
                    }
                }
            } else if (!(this->stateFlags1 & PLAYER_STATE1_8000000) ||
                        (((this->currentBoots < PLAYER_BOOTS_ZORA_UNDERWATER) ||
                          !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) &&
                         (Player_Action_43 != this->actionFunc) && (Player_Action_61 != this->actionFunc) &&
                         (Player_Action_62 != this->actionFunc) && (Player_Action_54 != this->actionFunc) &&
                         (Player_Action_57 != this->actionFunc) && (Player_Action_58 != this->actionFunc) &&
                         (Player_Action_59 != this->actionFunc) && (Player_Action_60 != this->actionFunc) &&
                       (Player_Action_55 != this->actionFunc) && (Player_Action_56 != this->actionFunc))) {
              func_8083B930(play, this);
             }
         } else if ((this->stateFlags1 & PLAYER_STATE1_8000000) &&
                    (this->actor.depthInWater < this->ageProperties->unk_24) &&
                    (((Player_Action_56 != this->actionFunc) && !(this->stateFlags3 & PLAYER_STATE3_8000)) ||
                     (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND))) {
             if (this->skelAnime.movementFlags == 0) {
                 Player_SetupTurnInPlace(play, this, this->actor.shape.rot.y);
            }
            func_8083B32C(play, this, this->actor.velocity.y);
        }
    }
}

//# Patches this function to only start the hops if A is held. Others needed too.

RECOMP_PATCH s32 func_80850854(PlayState* play, Player* this) {

    if ((this->transformation == PLAYER_FORM_DEKU) && (this->remainingHopsCounter != 0) &&
        (gSaveContext.save.saveInfo.playerData.health != 0) && (sControlStickMagnitude != 0.0f) &&
        (CHECK_BTN_ANY(CONTROLLER1(&play->state)->cur.button, BTN_A))) {
        func_808373F8(play, this, 0);
        return true;
    }
    return false;
}
// Main function that handles hopping. When this is prevented, Deku can swim IF spawning in the swimming state. Going into water normally breaks.

// Patched to check if A is pressed before starting the hopping function proper.
RECOMP_PATCH s32 func_808373F8(PlayState* play, Player* this, u16 sfxId) {

    PlayerAnimationHeader* anim;
    f32 speed;
    s16 yawDiff = this->yaw - this->actor.shape.rot.y;

    // not having the stuff below here, until the deku hopping part, crashes if you try to hop.

    if ((IREG(66) / 100.0f) < this->speedXZ) {
        speed = IREG(67) / 100.0f;
    } else {
        speed = (IREG(68) / 100.0f + (IREG(69) * this->speedXZ) / 1000.0f);

        if ((this->transformation == PLAYER_FORM_DEKU) && (speed < 8.0f)) {
            speed = 8.0f;
        } else if (speed < 5.0f) {
            speed = 5.0f;
        }
    }

    if ((ABS_ALT(yawDiff) >= 0x1000) || (this->speedXZ <= 4.0f)) {
        anim = &gPlayerAnim_link_normal_jump;
    } else {
        s32 var_v1;

        if ((this->transformation != PLAYER_FORM_DEKU) &&
            ((sPrevFloorProperty == FLOOR_PROPERTY_1) || (sPrevFloorProperty == FLOOR_PROPERTY_2))) {
            if (sPrevFloorProperty == FLOOR_PROPERTY_1) {
                var_v1 = 4;
            } else {
                var_v1 = 5;
            }

            func_80834D50(play, this, D_8085C2A4[var_v1].unk_0, speed, ((var_v1 == 4) ? NA_SE_VO_LI_SWORD_N : sfxId));
            this->av2.actionVar2 = -1;
            this->stateFlags2 |= PLAYER_STATE2_80000;
            this->av1.actionVar1 = var_v1;
            return true;
        }
        anim = &gPlayerAnim_link_normal_run_jump;
    }

    // Deku hopping

if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->cur.button, BTN_A)) {
    if (this->transformation == PLAYER_FORM_DEKU) {
        speed *= 0.3f + ((5 - this->remainingHopsCounter) * 0.18f);
        if (speed < 4.0f) {
            speed = 4.0f;
        }

        if ((this->actor.depthInWater > 0.0f) && (this->remainingHopsCounter != 0)) {
            this->actor.world.pos.y += this->actor.depthInWater;
            func_80834D50(play, this, anim, speed, NA_SE_NONE);
            this->av2.actionVar2 = 1;
            this->stateFlags3 |= PLAYER_STATE3_200000;
            Player_PlaySfx(this, (NA_SE_PL_DEKUNUTS_JUMP5 + 1 - this->remainingHopsCounter));
            Player_AnimSfx_PlayVoice(this, sfxId);
            this->remainingHopsCounter--;
            if (this->remainingHopsCounter == 0) {
                this->stateFlags2 |= PLAYER_STATE2_80000;
                // Makes Deku spin on last hop.
                func_808373A4(play, this);
            }

            return true;
        }

        if (this->actor.velocity.y > 0.0f) {
            sfxId = NA_SE_NONE;
        }
    }

    func_80834D50(play, this, anim, speed, sfxId);
    this->av2.actionVar2 = 1;

    return true;
}
}
// Potential Breakthrough function. Commenting this out and building breaks falling & climbing, but allows deku to VERY BROKENLY enter water and swim 
RECOMP_PATCH void func_8083827C(Player* this, PlayState* play) {
    s32 temp_t0; // sp64
    CollisionPoly* sp60;
    s32 sp5C;
    WaterBox* waterBox;
    Vec3f sp4C;
    f32 sp48;
    f32 sp44;
    // Landing from Falling animation?
    this->fallDistance = this->fallStartHeight - (s32)this->actor.world.pos.y;
    if (!(this->stateFlags1 & (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
        ((this->stateFlags1 & PLAYER_STATE1_80000000) ||
         !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) &&
        !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        if (func_80835428(play, this)) {
            return;
        }

        if (sPrevFloorProperty == FLOOR_PROPERTY_8) {
            this->actor.world.pos.x = this->actor.prevPos.x;
            this->actor.world.pos.z = this->actor.prevPos.z;
            return;
        }

        if ((this->stateFlags3 & PLAYER_STATE3_2) || (this->skelAnime.movementFlags & ANIM_FLAG_80)) {
            return;
        }
        // 25 = Falling Normally
        // 27 = Diving (as in jumping down w/ the dive anim, not swimming and hitting A)
        // 28 = Jumping out of Water as Zora
        // 96 = Goron Rolling
        // 82 = Being frozen in Ice (what)
        // 83 = Being electrically shocked (Couldnt get to trigger, found next to 82 with "Player_Anim_PlayLoopAdjusted(play, this, &gPlayerAnim_link_normal_electric_shock);"

        if ((Player_Action_25 == this->actionFunc) || (Player_Action_27 == this->actionFunc) ||
            (Player_Action_28 == this->actionFunc) || (Player_Action_96 == this->actionFunc) ||
            (Player_Action_82 == this->actionFunc) || (Player_Action_83 == this->actionFunc)) {
            return;
        }

        if ((sPrevFloorProperty == FLOOR_PROPERTY_7) || (this->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) ||
            ((this->skelAnime.movementFlags & ANIM_FLAG_ENABLE_MOVEMENT) && func_808381F8(play, this))) {
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
            if (this->speedXZ > 0.0f) {
                Player_StopHorizontalMovement(this);
            }
            this->actor.bgCheckFlags |= BGCHECKFLAG_GROUND_TOUCH;
            return;
        }

        temp_t0 = BINANG_SUB(this->yaw, this->actor.shape.rot.y);
        Player_SetAction(play, this, Player_Action_25, 1);
        func_8082DD2C(play, this);

        // Jumping off Ledges?
        this->floorSfxOffset = this->prevFloorSfxOffset;
        if ((this->transformation != PLAYER_FORM_GORON) &&
            ((this->transformation != PLAYER_FORM_DEKU) || (this->remainingHopsCounter != 0)) &&
            (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND_LEAVE)) {
            if (!(this->stateFlags1 & PLAYER_STATE1_8000000)) {
                if ((sPrevFloorProperty != FLOOR_PROPERTY_6) && (sPrevFloorProperty != FLOOR_PROPERTY_9) &&
                    (sPlayerYDistToFloor > 20.0f) && (this->meleeWeaponState == PLAYER_MELEE_WEAPON_STATE_0)) {
                    if ((ABS_ALT(temp_t0) < 0x2000) && (this->speedXZ > 3.0f)) {
                        if (!(this->stateFlags1 & PLAYER_STATE1_CARRYING_ACTOR)) {
                            if (((this->transformation == PLAYER_FORM_ZORA) &&
                                 CHECK_BTN_ALL(sPlayerControlInput->cur.button, BTN_A)) ||
                                ((sPrevFloorProperty == FLOOR_PROPERTY_11) &&
                                 (this->transformation != PLAYER_FORM_GORON) &&
                                 (this->transformation != PLAYER_FORM_DEKU))) {

                                sp48 = func_80835CD8(play, this, &D_8085D154, &sp4C, &sp60, &sp5C);
                                sp44 = this->actor.world.pos.y;

                                if (WaterBox_GetSurface1(play, &play->colCtx, sp4C.x, sp4C.z, &sp44, &waterBox) &&
                                    ((sp44 - sp48) > 50.0f)) {
                                    func_80834DB8(this, &gPlayerAnim_link_normal_run_jump_water_fall, 6.0f, play);
                                    Player_SetAction(play, this, Player_Action_27, 0);
                                    return;
                                }
                            }
                        }
                        func_808373F8(play, this, NA_SE_VO_LI_AUTO_JUMP);
                        return;
                    }
                }
            }
        }

        // Checking if the ledge is tall enough for Player to hang from
         // Top part breaks jumps and falls. Bottom Part breaks Deku's ability to enter water and bugs his animations (WITH THE SWIMMING THING I DID EARLIER)
        if ((sPrevFloorProperty == FLOOR_PROPERTY_9) || (sPlayerYDistToFloor <= this->ageProperties->unk_34) ||
            !func_80837DEC(this, play)) {
            Player_Anim_PlayLoop(play, this, &gPlayerAnim_link_normal_landing_wait);
        }
    } else {
        this->fallStartHeight = this->actor.world.pos.y;
        this->remainingHopsCounter = 5;
    }
}