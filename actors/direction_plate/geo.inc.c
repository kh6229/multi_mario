#include "src/game/envfx_snow.h"

const GeoLayout direction_plate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, direction_plate_Direction_Plate_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
