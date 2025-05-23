const Collision lll_area_1_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(16),
	COL_VERTEX(-2628, 0, 2628),
	COL_VERTEX(9628, 0, 2628),
	COL_VERTEX(9628, 0, -9628),
	COL_VERTEX(-2628, 0, -9628),
	COL_VERTEX(395, 0, 395),
	COL_VERTEX(395, 0, -395),
	COL_VERTEX(1972, 0, -395),
	COL_VERTEX(1972, 0, 395),
	COL_VERTEX(-395, 0, 395),
	COL_VERTEX(-395, 200, 395),
	COL_VERTEX(-395, 200, -395),
	COL_VERTEX(-395, 0, -395),
	COL_VERTEX(395, 200, -395),
	COL_VERTEX(395, 200, 395),
	COL_VERTEX(1972, 200, 395),
	COL_VERTEX(1972, 200, -395),
	COL_TRI_INIT(SURFACE_BURNING, 4),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 5, 6),
	COL_TRI(4, 6, 7),
	COL_TRI_INIT(SURFACE_DEFAULT, 16),
	COL_TRI(8, 9, 10),
	COL_TRI(8, 10, 11),
	COL_TRI(11, 10, 12),
	COL_TRI(11, 12, 5),
	COL_TRI(12, 13, 14),
	COL_TRI(12, 14, 15),
	COL_TRI(4, 13, 9),
	COL_TRI(4, 9, 8),
	COL_TRI(12, 10, 9),
	COL_TRI(12, 9, 13),
	COL_TRI(6, 15, 14),
	COL_TRI(6, 14, 7),
	COL_TRI(5, 12, 15),
	COL_TRI(5, 15, 6),
	COL_TRI(13, 4, 7),
	COL_TRI(13, 7, 14),
	COL_TRI_STOP(),
	COL_END()
};
