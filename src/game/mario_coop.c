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
struct MarioState * coop_spawn_mario_with_id(Vec3f pos, int marioID, int control_mode, ModelID32 model, s16 yaw) {
    if (gMarioStates[marioID].marioObj != NULL) {return NULL;} // Slot already used

    gCoopActiveMarios++;
    if (IS_CONTROLLABLE(control_mode)) {
        gCoopActiveControllableMarios --;
    }

    init_mario_from_save_file(&gMarioStates[marioID],marioID);
    gMarioStates[marioID].marioObj = spawn_object(gMarioState->marioObj, model, bhvMario);
    gMarioStates[marioID].marioObj->oPlayerID = marioID;
    gMarioStates[marioID].marioObj->oFlags |= OBJ_FLAG_IS_A_MARIO;
    init_mario(&gMarioStates[marioID]);
    gMarioStates[marioID].controlMode = control_mode;
    vec3f_copy(gMarioStates[marioID].pos, pos);

    if (gMarioStates[marioID].controlMode == COOP_CM_NPC) {
        gMarioStates[marioID].health = 0x110;
    }

    gMarioStates[marioID].faceAngle[1] = yaw;

    return &gMarioStates[marioID];
}

/*
Spawns a Mario at the specified position using any empty ID.
Returns the MarioState of the spawned Mario, NULL if Mario count is maxed out.
*/
struct MarioState * coop_spawn_mario(Vec3f pos, int control_mode, ModelID32 model, s16 yaw) {
    for (int i = 0; i < COOP_MARIO_STATES_MAX; i ++) {
        // Search for a uninitialized mario
        if (gMarioStates[i].marioObj == NULL) {
            return coop_spawn_mario_with_id(pos,i,control_mode, model, yaw);
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
    } while(gMarioStates[gCoopActiveMarioIndex].marioObj == NULL || gCoopActiveMarioIndex > 1);

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

void coop_npc_walking(struct MarioState * m) {
    if (m->floor != SURFACE_DEFAULT) { // If floor isn't default...
        switch (m->floor->type) {      // Decide which way to turn based on floor type
            case SURFACE_NOISE_DEFAULT:
                m->npcState = NPC_FLOOR_TURN_LEFT;
                break;
            
            case SURFACE_HARD:
                m->npcState = NPC_FLOOR_TURN_RIGHT;
                break;

            case SURFACE_HARD_SLIPPERY:
                m->npcState = NPC_FLOOR_TURN_AROUND;
                break;

            default:
                break;
        }
    }
    
    if (m->wall != NULL) {
        s16 jump_height = 150;
        if (m->wall->upperY <= (m->floor->upperY + jump_height)) { // If the height of the wall is shorter than
            m->npcState = NPC_STATE_JUMP;                          // the jump height, then jump. Else start turning
        } else {
            m->npcState = NPC_STATE_WALL_TURN;
        }
    }
    
    m->input |= INPUT_NONZERO_ANALOG; // Allows him to move
    m->intendedMag = 8.0f; // Always going slow
}

void coop_npc_wall_turn(struct MarioState * m) {
    m->input |= INPUT_NONZERO_ANALOG;
    m->faceAngle[1] += 0x8000;
    m->intendedYaw = m->faceAngle[1];
    m->npcState = NPC_STATE_WALKING;
}

void coop_npc_floor_turn(struct MarioState * m, int ct) {
    m->input |= INPUT_NONZERO_ANALOG; // Allows him to move
    if (m->turnCooldown == 0) {
        for (int i = 0; i < ct; i++) {
            m->faceAngle[1] += 0x2000;
            m->intendedYaw = m->faceAngle[1];
        }
        m->turnCooldown = 30;
    }
    m->npcState = NPC_STATE_WALKING;
}

void coop_npc_jump(struct MarioState * m) {
    m->input |= INPUT_NONZERO_ANALOG; // Allows him to move
    m->input |= INPUT_A_PRESSED; // Allows him to jump
    m->intendedMag = 15.0f; // Go faster when jumping to avoid ledge grabs

    if (m->jumpTimer < 7) { // Hold A for 7 frames
        m->input |= INPUT_A_DOWN;
        m->jumpTimer++;
    } else {
        m->input ^= INPUT_A_DOWN; // Let go of A after 7 frames
        m->jumpTimer = 0;

        if (m->wall != NULL) { // If we still hit a wall, turn around. Else continue walking
            m->npcState = NPC_STATE_WALL_TURN;
        } else {
            m->npcState = NPC_STATE_WALKING;
        }
    }
}

void coop_npc_standing(struct MarioState * m) {
    m->intendedYaw = m->faceAngle[1];
    struct Object * button = cur_obj_nearest_object_with_behavior(bhvMiniMarioButton);
    if (button != NULL) {
        if (button->oButtonPressed > 0) {
            m->npcState = NPC_STATE_WALKING;
        }
    } else {
        m->npcState = NPC_STATE_WALKING;
    }
}

void coop_npc_behavior(struct MarioState * m) {
    if (m->turnCooldown > 0) { // Subtract the turn cooldown
        m->turnCooldown--;
    }

    if (m->wallCooldown > 0) { // Subtract the wall turn cooldown
        m->wallCooldown--;
    }

    switch (m->npcState) {
        case NPC_STATE_STANDING:
            coop_npc_standing(m);
            break;
        
        case NPC_STATE_WALKING:
            coop_npc_walking(m);
            break;

        case NPC_STATE_WALL_TURN:
            coop_npc_wall_turn(m);
            break;

        case NPC_FLOOR_TURN_LEFT:
            coop_npc_floor_turn(m, 2);
            break;

        case NPC_FLOOR_TURN_RIGHT:
            coop_npc_floor_turn(m, 6);
            break;

        case NPC_FLOOR_TURN_AROUND:
            coop_npc_floor_turn(m, 4);
            break;

        case NPC_STATE_JUMP:
            coop_npc_jump(m);
            break;
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
        if (&gMarioStates[i] == m || &gMarioStates[i].marioObj == NULL) {continue;}

        Vec3f diff;
        vec3_diff(diff, gMarioStates[i].pos, m->pos);
        f32 distSquared = sqr(diff[0]) + sqr(diff[1]) + sqr(diff[2]);

        if (distSquared < sqr(COOP_MARIO_HITBOX_SIZE)) {
            
            if (m->controlMode == COOP_CM_NPC) {
                m->npcState = NPC_STATE_WALL_TURN;
            } else {
                f32 pressure = sqrtf(sqr(COOP_MARIO_HITBOX_SIZE)-distSquared)/4.f;

                vec3f_normalize(diff);
                vec3_scale_dest(diff,diff,-pressure);

                vec3f_sum(m->pos,m->pos,diff);
                vec3_scale_dest(diff,diff,-1.0f);
                vec3f_sum(gMarioStates[i].pos,gMarioStates[i].pos,diff);
            }
        }
    }
}