const Collision turn_plane_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(3),
	COL_VERTEX(100, 0, 100),
	COL_VERTEX(-100, 0, -100),
	COL_VERTEX(-100, 0, 100),
	COL_TRI_INIT(SURFACE_DEFAULT, 1),
	COL_TRI(0, 1, 2),
	COL_TRI_STOP(),
	COL_END()
};
