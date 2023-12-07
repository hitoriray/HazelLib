#include "GridGraph.h"

std::array<VertexInfo, 4> GridGraph::DIRS = {
	/* East, West, North, South */
	VertexInfo{1, 0}, VertexInfo{-1, 0},
	VertexInfo{0, -1}, VertexInfo{0, 1}
};