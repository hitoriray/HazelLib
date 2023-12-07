#include "../Graph/MatrixGraph.h"
#include "../Graph/GridGraph.h"
#include "../Graph/ListGraph.h"

void testMatrixGraph()
{
	MatrixGraph<char> mg;
	mg.InsertVertex('A');
	mg.InsertVertex('B');
	mg.InsertVertex('C');
	mg.InsertVertex('D');
	mg.InsertEdge('A', 'B', 10);
	mg.InsertEdge('B', 'D', 5);
	mg.InsertEdge('B', 'C', 9);
	mg.InsertEdge('C', 'D', 14);

	std::cout << Hazel::GREEN << "Test Start...\n" << RESET;
	std::cout << "vertex number: " << mg.GetNumNodes() << std::endl;
	std::cout << "edge number: " << mg.GetNumEdges() << std::endl;

	std::cout << "Matrix: \n";
	mg.printMatrix();
	std::cout << std::endl;

	std::cout << "breadth first search: \n";
	mg.BFSTraverse();
	std::cout << std::endl;

	std::cout << "depth first search: \n";
	mg.DFSTraverse();
	std::cout << std::endl;

	std::cout << "Prim:\n";
	auto prim_path = mg.Prim();
	std::cout << std::endl;

	std::cout << "Kruskal:\n";
	const auto kruskal_path = mg.Kruskal();
	std::cout << "the minimum spanning tree: \n";
	std::cout << kruskal_path.back().endVex << std::endl;

	std::cout << "Dijkstra:\n";
	Vector<int> d_path;
	Vector<int> d_short_path_table;
	mg.Dijkstra(0, d_path, d_short_path_table);
	std::cout << std::endl;

	std::cout << "Floyd:\n";
	Vector<Vector<int>> f_path;
	Vector<Vector<int>> f_short_path_table;
	mg.Floyd(f_path, f_short_path_table);
	std::cout << std::endl;

	std::cout << RED << "A Star Search incompatible with Adjacency-Matrix graphs at present.\n" << RESET;
#ifdef A_STAR_ADJMAT_GRAPH
	std::cout << "a star search: \n";
	const std::vector<char> a_star_path = mg.AStar('A', 'D');
	for(int i = 0; i < a_star_path.size() - 1; i++) std::cout << a_star_path[i] << " -> ";
	std::cout << a_star_path.back() << std::endl;
#endif

	std::cout << "A connect with D ? " << (mg.connected('A', 'D') == true ? "true" : " false");

	std::cout << GREEN << "\n\nTest over...\n" << RESET;
}

void testListGraph()
{
	//ListGraph<char> lg;
	//lg.CreateGraph();
}

void testGridGraph()
{
	GridGraph grid = make_diagram(30, 15);
	draw_grid(grid);
	std::cout << "\n\n";
	VertexInfo start{ 3, 3 }, goal{ 17, 7 };

	auto bfs_came_from = breadth_first_search(grid, start, goal);
	draw_grid(grid, nullptr, &bfs_came_from, nullptr, &start, &goal);

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
	draw_grid(grid, nullptr, &came_from, &path, &start, &goal);
	std::cout << '\n';
	draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}

int main1234(int argc, char const* argv[])
{
	//testMatrixGraph();
	//testListGraph();
	testGridGraph();

	return 0;
}

