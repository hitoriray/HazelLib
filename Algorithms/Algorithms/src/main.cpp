#include "Graph/MatrixGraph.h"
#include "Graph/GridGraph.h"

int main(int argc, char const* argv[])
{
	/*UndirectedGraph<char>* g = new MatrixGraph<char>(4, 0);
	MatrixGraph<std::string> g2;
	Graph& g_ref = *g;*/

	GridGraph grid = make_diagram(30, 15);
	draw_grid(grid);
	std::cout << "\n\n";
	VertexInfo start{3, 3}, goal{17, 7};

	/*auto parents = breadth_first_search(grid, start, goal);
	draw_grid(grid, &start, &goal, &parents);*/

	std::unordered_map<VertexInfo, VertexInfo> came_from;
	std::unordered_map<VertexInfo, int> cost_so_far;
	dijkstra_search(grid, came_from, cost_so_far, start, goal);

	std::cout << "\nGrid graph with all path:\n";
	draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);

	std::cout << "\nGrid graph with min path:\n";
	std::vector<VertexInfo> path = reconstruct_path(start, goal, came_from);
	draw_grid(grid, nullptr, &came_from, &path, &start, &goal);

	std::cout << "\nGrid graph with cost:\n";
	draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);

	/*std::cout << "Grid graph with no path:\n";
	GridGraph grid2 = make_diagram_no_path(30, 15);
	start = { 5,5 };
	goal = { 25, 8 };
	came_from.clear();
	cost_so_far.clear();
	dijkstra_search(grid2, came_from, cost_so_far, start, goal);
	draw_grid(grid2, nullptr, &came_from, nullptr, &start, &goal);*/
	// reconstruct_path(start, goal, came_from) returns an empty vector

	std::cout << "\nA Star:\n";
	came_from.clear();
	cost_so_far.clear();
	a_star_search(grid, start, goal, came_from, cost_so_far);
	draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
	std::cout << '\n';
	path = reconstruct_path(start, goal, came_from);
	draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
	std::cout << '\n';
	draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);

	return 0;
}

