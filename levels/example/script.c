#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/group0.h"
#include "make_const_nonconst.h"
#include "levels/example/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_example_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _example_segment_7SegmentRomStart, _example_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, example_area_1),
		MARIO_POS(0x01, 0, 3355, -592, -837),
		OBJECT(MODEL_PURPLE_SWITCH, -1187, -221, -1763, 0, 0, 0, 0x00000000, bhvCountPlate),
		OBJECT(MODEL_PURPLE_SWITCH, -676, -221, -1253, 0, 0, 0, 0x00000000, bhvCountPlate),
		OBJECT(MODEL_DOUBLE_CHERRY, 850, -276, -2175, 0, 0, 0, 0x00000000, bhvDoubleCherry),
		OBJECT(MODEL_DOUBLE_CHERRY, -2538, 1365, -2236, 0, 0, 0, 0x00000000, bhvDoubleCherry),
		OBJECT(MODEL_DOUBLE_CHERRY, 80, 2775, 5829, 0, 0, 0, 0x00000000, bhvDoubleCherry),
		OBJECT(MODEL_NONE, -235, -198, 599, 0, 0, 0, (COOP_CM_NPC << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_NONE, 2449, -501, -417, 0, 0, 0, (COOP_CM_TAKE_TURNS << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_NONE, 2449, -501, -1256, 0, 0, 0, (COOP_CM_TAKE_TURNS << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_NONE, -1190, -171, -2259, 0, 0, 0, (COOP_CM_TAKE_TURNS << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_RAISE_PLATFORM, 523, -276, 1389, 0, 0, 0, (10 << 24) | (RAISE_PLATFORM_BP_WEIGHT_PLATE << 16), bhvRaisePlatform),
		OBJECT(MODEL_RAISE_PLATFORM, -1190, 124, -2257, 0, 0, 0, (40 << 24) | (RAISE_PLATFORM_BP_COUNT_PLATE << 16), bhvRaisePlatform),
		OBJECT(MODEL_EXAMPLE_SEESAW, -1831, 621, -1124, 0, 90, 0, (8 << 16), bhvSeesawPlatform),
		OBJECT(MODEL_PURPLE_SWITCH, 523, -276, 952, 0, 0, 0, 0x00000000, bhvWeightPlate),
		TERRAIN(example_area_1_collision),
		MACRO_OBJECTS(example_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 3355, -592, -837),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};