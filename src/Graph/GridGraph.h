#pragma once

#include "Graph.h"
#include "../Queue/Queue.h"

#include <iostream>
#include <array>
#include <functional>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using Hazel::Queue;

// 定义一些常量，表示网格图中的不同元素
enum ElemType {
	WALL = -1, // 墙壁
	EMPTY = 0, // 空白
};

struct VertexInfo
{
	VertexInfo() = default;
	VertexInfo(int x_, int y_)
		:x(x_), y(y_) {}

	int x; // x 坐标
	int y; // y 坐标
	//int f; // f = g + h
	//int g; // 从起点到当前顶点的实际代价
	//int h; // 从当前顶点到目标顶点的估计代价
};

inline bool operator==(const VertexInfo& lhs, const VertexInfo& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const VertexInfo& lhs, const VertexInfo& rhs) { return !(lhs == rhs); }

namespace std {
	/* implement hash function so we can put VertexInfo into an unordered_set */
	template <> struct hash<VertexInfo> { // 为VertexInfo定义hash函数
		std::size_t operator()(const VertexInfo& id) const noexcept {
			// NOTE: better to use something like boost hash_combine
			return std::hash<int>()(id.x ^ (id.y << 16)); // 用x和y的异或值作为hash值
		}
	};
}

struct PQElement {
	VertexInfo loc; // 位置
	int priority; // 优先级(int型)
	// 定义一个比较运算符，用来比较两个元素的优先级
	PQElement(VertexInfo loc_, int priority_)
		: loc(loc_), priority(priority_) {}
	bool operator<(const PQElement& other) const {
		return priority > other.priority; // 注意这里是反向比较，因为std::priority_queue默认是最大堆
	}
};

//template<typename T, typename priority_t>
//struct PriorityQueue {
//	typedef std::pair<priority_t, T> PQElement;
//
//	std::priority_queue<PQElement, std::vector<PQElement>,
//		std::greater<PQElement>> elements;
//
//	inline bool empty() const {
//		return elements.empty();
//	}
//	inline void put(T item, priority_t priority) {
//		elements.emplace(priority, item);
//	}
//	T get() {
//		T best_item = elements.top().second;
//		elements.pop();
//		return best_item;
//	}
//};

class GridGraph : public virtual Graph
{
	friend GridGraph make_diagram(const int width, const int height);
	friend GridGraph make_diagram_no_path(const int width, const int height);
	friend void draw_grid(const GridGraph& grid,
		std::unordered_map<VertexInfo, int>* cost_so_far = nullptr,
		std::unordered_map<VertexInfo, VertexInfo>* came_from = nullptr,
		std::vector<VertexInfo>* path = nullptr,
		const VertexInfo* start = nullptr,
		const VertexInfo* goal = nullptr);

public:
	GridGraph() = default;
	GridGraph(int w, int h)
		: Graph(w* h, 0), width(w), height(h),
		grid(std::vector<std::vector<int>>(w, std::vector<int>(h, ElemType::EMPTY)))
	{
	}
	GridGraph(const GridGraph& rhs) = default;
	GridGraph& operator=(const GridGraph& rhs) = default;
	GridGraph(GridGraph&& rhs) noexcept = default;
	GridGraph& operator=(GridGraph&& rhs) noexcept = default;
	~GridGraph() override = default;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetValue(int x, int y) const { return grid[x][y]; }

	inline void SetGrid(int x, int y, int val) { grid[x][y] = val; }
	inline bool in_bounds(const VertexInfo& cur) const { return 0 <= cur.x && cur.x < width && 0 <= cur.y && cur.y < height; }
	inline bool passable(const VertexInfo& cur) const { return walls.find(cur) == walls.end(); }
	std::vector<VertexInfo> neighbors(const VertexInfo& cur) const;
	inline int cost(VertexInfo from_node, VertexInfo to_node) const {
		return forests.find(to_node) != forests.end() ? 5 : 1; // 如果是森林，代价为5，否则为1
	}

private:
	int width; // 网格图的列数（宽）
	int height; // 网格图的行数（高）
	std::vector<std::vector<int>> grid; // 二维数组，存储网格图的信息
	static std::array<VertexInfo, 4> DIRS; // 4个方向：上、下、左、右
	std::unordered_set<VertexInfo> walls; // 存储墙的位置坐标
	std::unordered_set<VertexInfo> forests; // 存储森林的位置坐标
};



inline std::vector<VertexInfo> GridGraph::neighbors(const VertexInfo& cur) const
{
	std::vector<VertexInfo> results;

	for (const auto dir : DIRS) {
		VertexInfo next{ cur.x + dir.x, cur.y + dir.y };
		if (in_bounds(next) && passable(next)) // 如果在网格图内且不是墙
			results.push_back(next);
	}

	if ((cur.x + cur.y) % 2 == 0) {// 如果是偶数，反转结果
		// aesthetic improvement on square grids(方形网格的美学改进), see "Ugly paths" section for an explanation
		std::reverse(results.begin(), results.end());
	}

	return results;
}

template<typename VertexInfo>
std::unordered_map<VertexInfo, VertexInfo> breadth_first_search(const GridGraph& grid, const VertexInfo& start, const VertexInfo& goal)
{
	Queue<VertexInfo> frontier;
	frontier.push(start);
	std::unordered_map<VertexInfo, VertexInfo> came_from;
	came_from[start] = start;
	while (!frontier.empty()) {
		VertexInfo cur = frontier.front();
		frontier.pop();
		if (cur == goal)
			break;
		for (auto next : grid.neighbors(cur)) {
			if (came_from.find(next) == came_from.end()) {
				frontier.push(next);
				came_from[next] = cur;
			}
		}
	}
	return came_from;
}

template<typename VertexInfo>
void dijkstra_search(const GridGraph& grid,
	std::unordered_map<VertexInfo, VertexInfo>& came_from, std::unordered_map<VertexInfo, int>& cost_so_far,
	const VertexInfo& start, const VertexInfo& goal)
{
	//PriorityQueue<VertexInfo, int> frontier;
	std::priority_queue<PQElement> frontier;
	frontier.push(PQElement{ start, 0 });
	came_from[start] = start;
	cost_so_far[start] = 0;
	while (!frontier.empty()) {
		VertexInfo cur = frontier.top().loc;
		frontier.pop();
		if (cur == goal) break;
		for (VertexInfo next : grid.neighbors(cur)) {
			const int new_cost = cost_so_far[cur] + grid.cost(cur, next);
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				frontier.push(PQElement{ next, new_cost });
				came_from[next] = cur;
			}
		}
	}
}

template<typename VertexInfo>
std::vector<VertexInfo> reconstruct_path(const VertexInfo& start, const VertexInfo& goal,
	std::unordered_map<VertexInfo, VertexInfo>& came_from)
{
	std::vector<VertexInfo> path;
	VertexInfo cur = goal;
	if (came_from.find(goal) == came_from.end()) {
		return path; // no path can be found
	}
	while (cur != start) {
		path.push_back(cur);
		cur = came_from[cur];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

inline void draw_grid(const GridGraph& grid,
	std::unordered_map<VertexInfo, int>* cost_so_far,
	std::unordered_map<VertexInfo, VertexInfo>* came_from,
	std::vector<VertexInfo>* path,
	const VertexInfo* start,
	const VertexInfo* goal)
{
	//// 定义一些颜色常量
	//const char* RESET = "\033[0m";
	//const char* RED = "\033[31m";
	//const char* GREEN = "\033[32m";
	//const char* YELLOW = "\033[33m";
	//const char* BLUE = "\033[34m";
	//const char* MAGENTA = "\033[35m";
	//const char* CYAN = "\033[36m";

	// 获取网格的行数和列数
	int rows = grid.GetHeight();
	int cols = grid.GetWidth();
	std::cout << "   "; // 输出列标签
	for (int c = 0; c < cols; c++) {
		std::cout << std::setw(2) << c;
	}
	std::cout << "\n";
	std::cout << "  +"; // 输出分隔符
	for (int c = 0; c < cols; c++) {
		std::cout << std::setw(2) << "-+";
	}
	std::cout << "\n";
	for (int r = 0; r < rows; r++) { // 遍历每一行
		std::cout << std::setw(2) << r << "|"; // 输出行标签
		for (int c = 0; c < cols; c++) { // 遍历每一列
			VertexInfo loc{ c, r }; // 获取当前位置
			if (grid.walls.count(loc)) { // 判断是否是起点、终点、路径或障碍物，并用不同的颜色输出
				std::cout << Hazel::RED << std::setw(2) << "#" << Hazel::RESET;
			}
			else if (start != nullptr && *start == loc) {
				std::cout << Hazel::GREEN << std::setw(2) << "S" << Hazel::RESET;
			}
			else if (goal != nullptr && *goal == loc) {
				std::cout << Hazel::GREEN << std::setw(2) << "G" << Hazel::RESET;
			}
			else if (cost_so_far != nullptr && cost_so_far->count(loc))
			{
				const auto cost = (*cost_so_far)[loc];
				std::cout << Hazel::BLUE << std::setw(2) << cost << Hazel::RESET;
			}
			else if (path != nullptr && std::find(path->begin(), path->end(), loc) != path->end()) {
				std::cout << Hazel::YELLOW << std::setw(2) << "*" << Hazel::RESET;
			}
			else if (came_from != nullptr && came_from->count(loc)) {
				const VertexInfo next = (*came_from)[loc];
				if (next.x == c + 1) { std::cout << Hazel::MAGENTA << std::setw(2) << " →" << Hazel::RESET; }
				else if (next.x == c - 1) { std::cout << Hazel::MAGENTA << std::setw(2) << " ←" << Hazel::RESET; }
				else if (next.y == r + 1) { std::cout << Hazel::MAGENTA << std::setw(2) << " ↓" << Hazel::RESET; }
				else if (next.y == r - 1) { std::cout << Hazel::MAGENTA << std::setw(2) << " ↑" << Hazel::RESET; }
				else { std::cout << Hazel::CYAN << std::setw(2) << "?" << Hazel::RESET; }
			}
			else { // 否则就输出一个点
				std::cout << std::setw(2) << ".";
			}
		}
		std::cout << "\n"; // 输出换行符
	}
}

inline GridGraph make_diagram(const int width, const int height)
{
	GridGraph grid(width, height); // 创建一个 width * height的网格图对象
	for (int y = 0; y < height; y++) { // 从上到下
		for (int x = 0; x < width; x++) { // 从左到右
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1
				|| (x % 2 == 0 && y % 2 == 0) || rand() % 10 == 0) { // 如果是 边界 或 偶数坐标 或 随机数为0，则设为墙壁 // NOLINT(concurrency-mt-unsafe)
				grid.walls.insert(VertexInfo{ x, y });
				grid.SetGrid(x, y, ElemType::WALL);
			}
			else { // 其他情况，设为空白
				grid.SetGrid(x, y, ElemType::EMPTY);
			}
		}
	}
	return grid; // 返回网格图对象
}

inline GridGraph make_diagram_no_path(const int width, const int height)
{
	GridGraph grid(width, height);
	const int start_wall_index = width / 2;
	for (int y = 0; y < height && start_wall_index < width; y++) {
		grid.SetGrid(start_wall_index, y, ElemType::WALL);
		grid.walls.insert(VertexInfo{ start_wall_index, y });
	}
	return grid;
}

/**
 * \brief 启发式函数
 * \param a
 * \param b
 * \return
 */
inline int heuristic(VertexInfo a, VertexInfo b) {
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template<typename Location, typename Graph>
void a_star_search
(const Graph& graph,
	const Location& start, const Location& goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, int>& cost_so_far)
{
	std::priority_queue<PQElement> frontier;
	frontier.push(PQElement{ start, 0 });
	came_from[start] = start;
	cost_so_far[start] = 0;
	while (!frontier.empty()) {
		Location current = frontier.top().loc;
		frontier.pop();
		if (current == goal) break;
		for (Location next : graph.neighbors(current)) {
			auto new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				auto priority = new_cost + heuristic(next, goal);
				frontier.push(PQElement{ next, priority });
				came_from[next] = current;
			}
		}
	}
}

//template<typename Graph>
//void a_star_search_2
//(const Graph& graph,
//	const typename Graph::Location& start,
//	const typename Graph::Location& goal,
//	const std::function<typename Graph::cost_t(typename Graph::Location a, typename Graph::Location b)>& heuristic,
//	std::unordered_map<typename Graph::Location,
//	typename Graph::Location>& came_from,
//	std::unordered_map<typename Graph::Location,
//	typename Graph::cost_t>& cost_so_far)
//{
//	typedef typename Graph::Location Location;
//	typedef typename Graph::cost_t cost_t;
//	PriorityQueue<Location, cost_t> frontier;
//	std::vector<Location> neighbors;
//	frontier.put(start, cost_t(0));
//
//	came_from[start] = start;
//	cost_so_far[start] = cost_t(0);
//
//	while (!frontier.empty()) {
//		typename Location current = frontier.get();
//
//		if (current == goal) {
//			break;
//		}
//
//		graph.get_neighbors(current, neighbors);
//		for (Location next : neighbors) {
//			cost_t new_cost = cost_so_far[current] + graph.cost(current, next);
//			if (cost_so_far.find(next) == cost_so_far.end()
//				|| new_cost < cost_so_far[next]) {
//				cost_so_far[next] = new_cost;
//				cost_t priority = new_cost + heuristic(next, goal);
//				frontier.put(next, priority);
//				came_from[next] = current;
//			}
//		}
//	}
//}