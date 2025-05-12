#include "src/game/envfx_snow.h"

const GeoLayout blue_block_Switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blue_block_Switch_Option_1_mesh_layer_5_mat_override_f3dlite_material_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout blue_block_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(0, geo_switch_blue_block),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, blue_block_Switch_Option_1_mesh_layer_5),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, blue_block_Switch_opt1),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
