void bhv_text_trigger_loop(void) {
    struct MarioState * m = &gMarioStates[0];
    f32 dist = lateral_dist_between_objects(o, m->marioObj);

    if (dist < 800) {
        if (dist < 400 ) {
            gTextIsRendering = o->oBehParams2ndByte;
        } else {
            gTextIsRendering = 0;
        }
    }

    o->oFaceAngleYaw += 0x200;
}