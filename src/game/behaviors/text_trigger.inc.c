void bhv_text_trigger_loop(void) {
    struct MarioState * m = &gMarioStates[0];
    if (is_point_close_to_object(m->marioObj, o->oPosX, o->oPosY, o->oPosZ, 400)) {
        gTextIsRendering = o->oBehParams2ndByte;
    }

    o->oFaceAngleYaw += 0x200;
}