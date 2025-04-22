void bhv_coop_spawn_mario(void) {
    coop_spawn_mario(&o->oPosVec,o->oBehParams2ndByte);
}

struct ObjectHitbox sDoubleCherryHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 64,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

// Behavior: bhvDoubleCherry
// Model ID: MODEL_DOUBLE_CHERRY
void bhv_coop_double_cherry(void) {
    switch(o->oAction) {
        case 0:
        obj_set_hitbox(o, &sDoubleCherryHitbox);
            o->oAction = 1;
            break;
        case 1:
            o->oFaceAngleYaw += 0x400;
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                // Infect the touching Mario so that he still moves if the primary Mario is switched
                gMarioState->controlMode = COOP_CM_ALL_ACTIVE;

                create_sound_spawner(SOUND_MENU_EXIT_PIPE);
                spawn_mist_particles_variable(0, 0, 50.0f);
                coop_spawn_mario(&o->oPosVec,COOP_CM_ALL_ACTIVE);
                obj_mark_for_deletion(o);
            }
            o->oInteractStatus = 0;
            break;
    }
}

// Behavior: bhvWeightPlate
// Model ID: MODEL_PURPLE_SWITCH
void bhv_coop_weight_plate(void) {
    s32 oldMarioCt = o->oPressurePlateStatus;
    switch(o->oAction) {
        case 0: // init
            o->prevObj = spawn_object(o,MODEL_NUMBER,bhvWeightPlateNumber);
            o->prevObj->oPosY += 400.0f;
            o->prevObj->oAnimState = 0;
            o->oAction = 1;
            break;
        case 1:;
            int marioct = 0;
            f32 yscale = 1.5f;
            for (int i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                struct MarioState * m = &gMarioStates[i];
                if (m->marioObj != NULL && m->marioObj->platform == o) {
                    marioct++;
                    yscale *= .7f;
                }
            }
            if (marioct>9) {
                marioct=9;
            }
            o->prevObj->oAnimState = marioct;
            o->oPressurePlateStatus = marioct;
            o->header.gfx.scale[1] = approach_f32_asymptotic(o->header.gfx.scale[1],yscale,.1f);
            break;
    }
    if (oldMarioCt != o->oPressurePlateStatus) {
        cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
    }
}

// Behavior: bhvWeightPlate
// Model ID: MODEL_PURPLE_SWITCH
void bhv_coop_count_plate(void) {
    f32 targetYScale = 1.5f;
    // Collisions are managed by the bhv_coop_raise_platform
    if (o->oPressurePlateStatus == 1) {
        targetYScale = 0.2f;
    }

    o->header.gfx.scale[1] = approach_f32(o->header.gfx.scale[1],targetYScale,.3f,.3f);
}

// Behavior: bhvRaisePlatform
// Model ID: MODEL_RAISE_PLATFORM

// This object's default model is a square platform, but it can work with any sort of vertical raising mechanism- like a gate, for example.

// BEHAVIOR PARAMATER 1: Height * 10
// BEHAVIOR PAREMETER 2: Condition
void bhv_coop_raise_platform(void) {
    f32 height = GET_BPARAM1(o->oBehParams) * 10.0f;
    switch(o->oBehParams2ndByte) {
        /*
        Weight plate raise platform rises by height * amount of Marios on the nearest weight plate.
        */
        case RAISE_PLATFORM_BP_WEIGHT_PLATE:;
            struct Object * nearest_weight_plate = cur_obj_nearest_object_with_behavior(bhvWeightPlate);

            if (nearest_weight_plate != NULL) {
                height *= nearest_weight_plate->oPressurePlateStatus;
                o->oPosY = approach_f32_asymptotic(o->oPosY,o->oHomeY+height,.1f);
            }
            break;
        /*
        */
        case RAISE_PLATFORM_BP_COUNT_PLATE:;
            uintptr_t *behaviorAddr = segmented_to_virtual(bhvCountPlate);
            struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
            struct Object *obj = (struct Object *) listHead->next;
        
            u8 close_gate = FALSE;
            // Iterate through every pressure plate
            while (obj != (struct Object *) listHead) {
                if (obj->behavior == behaviorAddr
                    && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
                    && obj != o
                ) {
                    u8 someone_is_on_this_platform = FALSE;

                    s32 oldPressurePlateStatus = obj->oPressurePlateStatus;
                    obj->oPressurePlateStatus = 0;
                    for (int i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                        struct MarioState * m = &gMarioStates[i];
                        if (m->marioObj != NULL && m->marioObj->platform == obj) {
                            someone_is_on_this_platform = TRUE;
                            obj->oPressurePlateStatus = 1;
                        }
                    }
                    if (oldPressurePlateStatus != obj->oPressurePlateStatus) {
                        play_sound(SOUND_GENERAL2_PURPLE_SWITCH, gGlobalSoundSource);
                    }

                    if (!someone_is_on_this_platform) {
                        close_gate = TRUE;
                    }
                }
        
                obj = (struct Object *) obj->header.next;
            }

            if (close_gate) {
                height = 0.0f;
            }
            o->oPosY = approach_f32(o->oPosY,o->oHomeY+height,10.f,10.f);

            break;
    }
}