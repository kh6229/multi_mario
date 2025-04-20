#include "src/game/envfx_snow.h"

const GeoLayout raisePlatform_geo[] = {
	GEO_CULLING_RADIUS(500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, raisePlatform_raisePlatform_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
