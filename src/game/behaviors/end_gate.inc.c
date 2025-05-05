u8 mariosEnteredGate = 0;
u8 starSpawned = 0;
void bhv_end_gate_loop(void) {
    u8 miniMarioCount = 0;

    for (int i = 0; i < COOP_MARIO_STATES_MAX; i++) {
        struct MarioState * m = &gMarioStates[i];
        if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC) {
            miniMarioCount++;
            if (m->marioObj->platform == o) {
                coop_delete_mario(m);
                mariosEnteredGate++;
            }
        }
    }

    o->prevObj->oAnimState = mariosEnteredGate;

    if (miniMarioCount == 0 && o->oTimer > 90 && starSpawned == 0) {
        cur_obj_spawn_star_at_y_offset((o->oPosX + 300.0f), (o->oPosY + 300.0f), o->oPosZ, 0.0f);
        starSpawned++;
    }
}

void bhv_end_gate_init(void) {
    o->prevObj = spawn_object(o, MODEL_NUMBER, bhvWeightPlateNumber);
    o->prevObj->oPosY += 400.0f;
    o->prevObj->oAnimState = 0;
}