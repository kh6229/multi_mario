#include "types.h"
#include "mario_coop.h"
#include "level_update.h"
#include "object_helpers.h"
#include "model_ids.h"
#include "mario.h"
#include "object_list_processor.h"
#include "behavior_data.h"
#include "engine/math_util.h"
#include "game_init.h"
#include "camera.h"
/*

mario_coop.c

This file is responsible for handling multiple active Marios at once.
Check mario_coop.h for configuration.

*/

int gCoopActiveMarios = 1;
int gCoopActiveControllableMarios = 1;
int gCoopActiveMarioIndex = 0;

/* 
Spawns a Mario at the specified position with a specific player ID.
Returns the MarioState of the spawned Mario, NULL if the ID is already used.
*/
struct MarioState * coop_spawn_mario_with_id(Vec3f pos, int marioID, int control_mode) {
    if (gMarioStates[marioID].marioObj != NULL) {return NULL;} // Slot already used

    gCoopActiveMarios++;
    if (IS_CONTROLLABLE(control_mode)) {
        gCoopActiveControllableMarios --;
    }

    init_mario_from_save_file(&gMarioStates[marioID],marioID);
    gMarioStates[marioID].marioObj = spawn_object(gMarioState->marioObj, MODEL_MARIO, bhvMario);
    gMarioStates[marioID].marioObj->oPlayerID = marioID;
    init_mario(&gMarioStates[marioID]);
    gMarioStates[marioID].controlMode = control_mode;
    vec3f_copy(gMarioStates[marioID].pos, pos);
    return &gMarioStates[marioID];
}

/*
Spawns a Mario at the specified position using any empty ID.
Returns the MarioState of the spawned Mario, NULL if Mario count is maxed out.
*/
struct MarioState * coop_spawn_mario(Vec3f pos, int control_mode) {
    for (int i = 0; i < COOP_MARIO_STATES_MAX; i ++) {
        // Search for a uninitialized mario
        if (gMarioStates[i].marioObj == NULL) {
            return coop_spawn_mario_with_id(pos,i,control_mode);
        }
    }

    return NULL; // Returns NULL if Marios are maxed out
}

/*
Sets the next Mario with control mode COOP_CM_TAKE_TURNS in line as the primary controller.
*/
void coop_give_control_to_next(void) {
    do {
        gCoopActiveMarioIndex++;
        if (gCoopActiveMarioIndex >= COOP_MARIO_STATES_MAX) {
            gCoopActiveMarioIndex = 0;
        }
    } while(gMarioStates[gCoopActiveMarioIndex].marioObj == NULL || !IS_CONTROLLABLE(gMarioStates[gCoopActiveMarioIndex].controlMode));

    gMarioState=&gMarioStates[gCoopActiveMarioIndex];
    gMarioObject=gMarioStates[gCoopActiveMarioIndex].marioObj;

    #ifdef COOP_SNAPPY_SWAP_CAMERA
        reset_camera(gCurrentArea->camera);
    #endif
}


/*
Deletes the Mario
*/
int coop_delete_mario(struct MarioState * m) {
    if (m->marioObj == NULL || m->isDead) {return TRUE;} // Already deleted

    if (m != gMarioState) {
        // marioObj is safely unplugged from MarioState when object is unloaded in unload_deactivated_objects_in_list() in object_list_processor.c
        obj_mark_for_deletion(m->marioObj);
        gCoopActiveMarios--;
        if (IS_CONTROLLABLE(m->controlMode)) {
            gCoopActiveControllableMarios --;
        }
    }
    if (gCoopActiveMarios == 0) {
        return FALSE; // Returns FALSE (Game Over) when every Mario is dead.
    }
    #ifdef COOP_MAIN_MARIO_MUST_LIVE
    if (m==gMarioState) {
        m->isDead = TRUE;
        return FALSE; // Returns FALSE (Game Over) when primary Mario has died.
    }
    #else 
    if (m == gMarioState) {
        m->isDead = TRUE;
        coop_give_control_to_next();
        reset_camera(gCurrentArea->camera);
    }
    #endif

    return TRUE;
}

void coop_npc_behavior(struct MarioState * m) {
    // Sample NPC function that makes Mario jump around like an idiot.

    m->input |= INPUT_NONZERO_ANALOG; // Allows him to move

    m->intendedMag = 32.0f; // Always holding

    if (gGlobalTimer % 15 == 0) {
        m->intendedYaw = random_u16(); // Random direction every half second
    }
    if (random_u16()%20==0) {
        m->input |= (INPUT_A_DOWN|INPUT_A_PRESSED); // 1/20 chance every frame to press A
    }
    if (random_u16()%50==0) {
        m->input |= (INPUT_B_DOWN|INPUT_B_PRESSED); // 1/50 chance every frame to press B
    }
    if (random_u16()%100==0) {
        m->input |= (INPUT_Z_DOWN|INPUT_Z_PRESSED); // 1/100 chance every frame to press Z
    }
}

// Don't call this function yourself, used for level transitions
void coop_reset_state(void) {
    gCoopActiveMarios = 1;
    gCoopActiveControllableMarios = 1;
    gCoopActiveMarioIndex = 0;
    gMarioState = &gMarioStates[0];
    for (int i = 0; i < COOP_MARIO_STATES_MAX; i ++) {
        gMarioStates[i].marioObj = NULL;
        gMarioStates[i].isDead = FALSE;
    }
}

// Don't call this function yourself, used for Mario touching other Marios O////O 
void coop_mario_collision(struct MarioState * m) {
    for (int i = 0; i < COOP_MARIO_STATES_MAX; i ++) {
        if (&gMarioStates[i] == m) {continue;}

        Vec3f diff;
        vec3_diff(diff, gMarioStates[i].pos, m->pos);
        f32 distSquared = sqr(diff[0]) + sqr(diff[1]) + sqr(diff[2]);

        if (distSquared < sqr(COOP_MARIO_HITBOX_SIZE)) {
            f32 pressure = sqrtf(sqr(COOP_MARIO_HITBOX_SIZE)-distSquared)/4.f;

            vec3f_normalize(diff);
            vec3_scale_dest(diff,diff,-pressure);

            vec3f_sum(m->pos,m->pos,diff);
            vec3_scale_dest(diff,diff,-1.0f);
            vec3f_sum(gMarioStates[i].pos,gMarioStates[i].pos,diff);
        }
    }
}