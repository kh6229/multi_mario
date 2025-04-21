
/**
 * Behavior for bhvSeesawPlatform.
 */

/**
 * Collision models for the different seesaw platforms.
 */
static Collision const *sSeesawPlatformCollisionModels[] = {
    bitdw_seg7_collision_0700F70C,
    bits_seg7_collision_0701ADD8,
    bits_seg7_collision_0701AE5C,
    bob_seg7_collision_bridge,
    bitfs_seg7_collision_07015928,
    rr_seg7_collision_07029750,
    rr_seg7_collision_07029858,
    vcutm_seg7_collision_0700AC44,
};

/**
 * Init function for bhvSeesawPlatform.
 */
void bhv_seesaw_platform_init(void) {
    o->collisionData = segmented_to_virtual(sSeesawPlatformCollisionModels[o->oBehParams2ndByte]);

    // The S-shaped seesaw platform in BitS is large, so increase its collision
    // distance
    if (o->oBehParams2ndByte == 2) {
        o->oCollisionDistance = 2000.0f;
    }
}

/**
 * Update function for bhvSeesawPlatform.
 */
void bhv_seesaw_platform_update(void) {
    o->oFaceAnglePitch += (s32) o->oSeesawPlatformPitchVel;

    if (absf(o->oSeesawPlatformPitchVel) > 10.0f) {
        cur_obj_play_sound_1(SOUND_ENV_BOAT_ROCKING1);
    }

    for (int i = 0; i < COOP_MARIO_STATES_MAX; i++) {
        struct MarioState * m = &gMarioStates[i];
        if (m->marioObj != NULL && m->marioObj->platform == o) {
            // Rotate toward mario
            f32 marioWeight = .15f;
            f32 pressure = marioWeight * dist_between_objects(o,m->marioObj) * coss(obj_angle_to_object(o,m->marioObj) - o->oMoveAngleYaw);
            o->oSeesawPlatformPitchVel += pressure;
        }
    }

    // Simulate a torsion spring using real world spring equation
    f32 offset = -o->oFaceAnglePitch;

    // More bouncy, more fun
    f32 strength = 0.05f;
    f32 damping = 0.1f;

    // Closely emulates the vanilla SM64 seesaw
    //f32 strength = 0.005f;
    //f32 damping = 0.5f;

    f32 f = (offset * strength) - (o->oSeesawPlatformPitchVel * damping);

    o->oSeesawPlatformPitchVel += f;

    o->oFaceAnglePitch += o->oSeesawPlatformPitchVel;
}
