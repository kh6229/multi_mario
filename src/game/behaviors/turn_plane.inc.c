void bhv_direction_plate_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oDirectionPlateCooldown = 0;
            o->oAction = 1;
            break;
        case 1:
            if (o->oDirectionPlateCooldown > 0) {
                o->oDirectionPlateCooldown--;
            }    

            if (cur_obj_is_mario_ground_pounding_platform() && o->oDirectionPlateCooldown == 0) {
                o->oFaceAngleYaw += 0x4000;
                o->oDirectionPlateCooldown = 30;
            }
    }
    
}

void bhv_jump_plane_loop(void) {
    switch (o->oAction) {
        case 0: 
            o->oAction = 1;
            break;
        
        case 1:
            if (o->oJumpPlaneType == JUMP_PLANE_TYPE_PURPLE_SWITCH) {
                struct Object * switchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
                if (switchObj != NULL && switchObj->oAction == PURPLE_SWITCH_ACT_TICKING) {
                    cur_obj_become_tangible();
                    cur_obj_enable_rendering();
                    load_object_collision_model();
                } else {
                    cur_obj_become_intangible();
                    cur_obj_disable_rendering();
                }
            } else {
                load_object_collision_model();
            }
            break;
    }
}

void bhv_jump_plane_init(void) {
    o->oJumpPlaneType = o->oBehParams2ndByte;
    o->oAction = 1;
}

void bhv_turn_plane_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 5) {
                for (u8 i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                    struct MarioState * m = &gMarioStates[i];
                    if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC) {
                        o->oTurnPlaneMiniMarioCount++;
                    }
                }
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTurnPlaneType == TURN_PLANE_TYPE_PURPLE_SWITCH) {
                struct Object *switchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
                if (switchObj != NULL && switchObj->oAction == PURPLE_SWITCH_ACT_TICKING) {
                    cur_obj_become_tangible();
                    cur_obj_enable_rendering();
                    load_object_collision_model();
                } else {
                    cur_obj_become_intangible();
                    cur_obj_disable_rendering();
                }
            } else {
                load_object_collision_model();
            }

            if (o->oTurnPlaneType != TURN_PLANE_TYPE_STAY) {
                if (o->oTurnPlaneMariosTurned >= o->oTurnPlaneMiniMarioCount) {
                    switch (o->oTurnPlaneType) {
                        case TURN_PLANE_TYPE_180:
                            o->oTurnPlaneYaw += 0x8000;
                            break;

                        case TURN_PLANE_TYPE_DELETE:
                            obj_mark_for_deletion(o);
                            break;
                    }
                }
                
                for (u8 i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                    struct MarioState * m = &gMarioStates[i];
                    if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC && m->marioObj->platform == o && o->oTurnPlaneCooldown == 0) {
                        o->oTurnPlaneMariosTurned++;
                        o->oTurnPlaneCooldown = 30;
                    }
                }

                if (o->oTurnPlaneCooldown > 0) {
                    o->oTurnPlaneCooldown--;
                }

            }
            break;
    }
    //o->prevObj->oAnimState = o->oTurnPlaneMariosTurned;
}

void bhv_turn_plane_init(void) {
    //o->prevObj = spawn_object(o,MODEL_NUMBER,bhvWeightPlateNumber);
    //o->prevObj->oPosY += 400.0f;
    //o->prevObj->oAnimState = 0;

    o->oTurnPlaneType         = o->oBehParams2ndByte;
    o->oTurnPlaneYaw          = GET_BPARAM34(o->oBehParams);
    o->oTurnPlaneMariosTurned = 0;
    o->oTurnPlaneMiniMarioCount = 0;
    o->oTurnPlaneCooldown = 0;
    o->oAction = 0;
}