Vtx turn_plane_Turn_Plane_mesh_layer_1_vtx_cull[8] = {
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx turn_plane_Turn_Plane_mesh_layer_1_vtx_0[3] = {
	{{ {100, 0, 100}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-100, 0, -100}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {-100, 0, 100}, 0, {-16, 1008}, {0, 127, 0, 255} }},
};

Gfx turn_plane_Turn_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(turn_plane_Turn_Plane_mesh_layer_1_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};


Gfx mat_turn_plane_f3dlite_material[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_turn_plane_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx turn_plane_Turn_Plane_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(turn_plane_Turn_Plane_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_turn_plane_f3dlite_material),
	gsSPDisplayList(turn_plane_Turn_Plane_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_turn_plane_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

