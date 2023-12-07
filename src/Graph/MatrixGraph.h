#pragma once

#include "UndirectedGraph.h"
#include "../Queue/Queue.h"

#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

#define GRAPH_INFINITY INT_MAX

using Hazel::Queue;

using Hazel::RESET;
using Hazel::RED;
using Hazel::GREEN;
using Hazel::YELLOW;
using Hazel::BLUE;
using Hazel::MAGENTA;
using Hazel::CYAN;


template <typename VertexType, typename EdgeType = int>
class MatrixGraph : public virtual UndirectedGraph<VertexType, EdgeType>
{
	using UndirectedGraph<VertexType, EdgeType>::numNodes;
	using UndirectedGraph<VertexType, EdgeType>::numEdges;
	using UndirectedGraph<VertexType, EdgeType>::vexs;
	using UndirectedGraph<VertexType, EdgeType>::Edge;
	using UndirectedGraph<VertexType, EdgeType>::Point;

	template <typename V, typename W>
	friend std::istream& operator>>(std::istream& is, MatrixGraph<V, W>& G);
	template <typename V, typename W>
	friend std::ostream& operator<<(std::ostream& os, const MatrixGraph<V, W>& G);

public:
	MatrixGraph();
	MatrixGraph(const Vector<VertexType>& vexs_,
		const Vector<Vector<EdgeType>>& arc_,
		int numNodes_, int numEdges_);
	MatrixGraph(Vector<VertexType> vexs_, Vector<VertexType> arc_);
	MatrixGraph(int numNodes_, int numEdges_ = 0);
	MatrixGraph(const MatrixGraph& rhs);
	MatrixGraph& operator=(const MatrixGraph& rhs);
	MatrixGraph(MatrixGraph&& rhs) noexcept;
	MatrixGraph& operator=(MatrixGraph&& rhs) noexcept;
	~MatrixGraph() override;

	// !无向图的基本操作
	// 创建无向网图的邻接矩阵
	void CreateGraph() override;
	// 判断是否是连通图
	inline bool isConnected() override;
	// 判断是否存在环
	inline bool hasCircle() override;
	// 判断是否为树
	inline bool isTree() override;
	// 判断两个顶点之间是否连通
	inline bool connected(VertexType v, VertexType u) override; // 根据顶点
	inline bool connected(int vInd, int uInd) override;			// 根据索引
	// 判断两个顶点之间是否有边
	inline bool hasEdge(VertexType v, VertexType u) override { return hasEdge(GetIndex(v), GetIndex(u)); }
	inline bool hasEdge(int vInd, int uInd) override { return arc[vInd][uInd] != GRAPH_INFINITY; }
	// 判断是否存在顶点
	inline bool isExist(VertexType v) override;
	// 根据顶点值寻找顶点索引
	inline int GetIndex(VertexType v) override;
	// 根据索引获取顶点值
	inline VertexType GetVertex(int ind) override { return vexs[ind]; }
	inline const VertexType& GetVertex(int ind) const override { return vexs[ind]; }
	// 修改顶点值
	inline void ModifyVertex(VertexType vertex, VertexType new_value) override;
	inline void ModifyVertex(int vInd, VertexType new_value) override;
	// 获取两顶点间的边值
	inline EdgeType GetWeight(VertexType v, VertexType u) override;
	inline EdgeType GetWeight(int vInd, int uInd) override;
	// 修改边值
	inline void ModifyWeight(VertexType v, VertexType u, EdgeType e) override;
	inline void ModifyWeight(int vInd, int uInd, EdgeType e) override;
	// 插入顶点
	inline void InsertVertex(VertexType v) override;
	// 删除顶点
	inline void RemoveVertex(VertexType v) override; // 根据顶点删除
	inline void RemoveVertex(int ind) override;		 // 根据顶点索引删除
	// 插入边
	inline void InsertEdge(VertexType v, VertexType u, EdgeType e) override;
	inline void InsertEdge(int vInd, int uInd, EdgeType e) override;
	// 删除边
	inline void RemoveEdge(VertexType v, VertexType u) override; // 根据顶点
	inline void RemoveEdge(int vInd, int uInd) override;		 // 根据索引
	// 将图以二维矩阵的形式打印出来
	inline void printMatrix();
	// 将图以坐标矩阵的形式打印出来
	inline void printCoord();

	// 获取顶点数
	using UndirectedGraph<VertexType, EdgeType>::GetNumNodes;
	// 获取边数
	using UndirectedGraph<VertexType, EdgeType>::GetNumEdges;
	// 获取顶点表
	inline Vector<VertexType> GetVexs() { return vexs; }
	// 获取邻接矩阵
	inline Vector<Vector<EdgeType>>& GetArc() { return arc; }

	// !算法：
	// 邻接矩阵的深度遍历操作
	inline void DFSTraverse() override;
	// 邻接矩阵的广度遍历算法
	inline void BFSTraverse() override;
	// Prim 算法
	inline Vector<VertexType> Prim() override;
	// Kruskal 算法
	inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Edge> Kruskal() override;
	// Dijkstra 算法
	inline void Dijkstra(int startInd, Vector<int>& path, Vector<EdgeType>& shortPathTable) override;
	inline void Dijkstra(const VertexType& startVex, Vector<int>& path, Vector<EdgeType>& shortPathTable) override;
	// Floyd算法【求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]】
	inline void Floyd(Vector<Vector<int>>& path, Vector<Vector<EdgeType>>& shortPathTable) override;
	// A*算法（无法使用Hazel::Vector替换std::vector）
	inline std::vector<VertexType> AStar(const VertexType& start, const VertexType& goal) override;
	// 打印路径
	inline void PrintPath(const Vector<VertexType>& path, const Vector<EdgeType>& shortPathTable = 0);

	// !重载运算符
	MatrixGraph& operator*=(const MatrixGraph& rhs);
	MatrixGraph operator*(const MatrixGraph& rhs);


private:
	inline void Init() override;
	inline void validate(int ind) override; // 证实ind下标索引的顶点是否存在于顶点表中

	inline void DFS(int startInd) override;


	inline void BFS(int startInd) override;

	// 计算出边数
	inline int CountEdges();

	inline int findTailInd(const Vector<int>& parent, int tailInd) override; // 寻找末尾顶点

	inline Vector<VertexType> neighbors(const VertexType& cur) override; // 当前顶点的邻居顶点
	inline EdgeType cost(const VertexType& cur, const VertexType& next) override; // 当前顶点到下一顶点的权重
	inline EdgeType heuristic(const VertexType& a, const VertexType& b); // 启发函数（计算点a和点b之间的曼哈顿距离）

	inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Point> adjToCoord(); // 邻接矩阵转换为坐标矩阵

private:
	Vector<Vector<EdgeType>> arc; // 邻接矩阵
	Vector<Point> coord; // 坐标矩阵
	Vector<bool> visited; // 访问标志的数组
};

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph()
	: UndirectedGraph<VertexType, EdgeType>(),
	arc(Vector<Vector<EdgeType>>()), coord(Vector<Point>()), visited(Vector<bool>())
{
	std::cout << "Default Ctor!" << std::endl;
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph(const Vector<VertexType>& vexs_,
	const Vector<Vector<EdgeType>>& arc_,
	int numNodes_, int numEdges_)
	: UndirectedGraph<VertexType, EdgeType>(vexs_, numNodes_, numEdges_),
	arc(arc_), coord(Vector<Point>(numNodes_)), visited(Vector<bool>(numNodes_))
{
	std::cout << "Ctor(1) with vexs, arc, numNodes and numEdges." << std::endl;
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph(Vector<VertexType> vexs_, Vector<VertexType> arc_)
	: UndirectedGraph<VertexType, EdgeType>(vexs_, vexs_.size(), EdgeType()),
	arc(arc_), coord(Vector<Point>(vexs_.size())), visited(Vector<bool>(vexs_.size()))
{
	std::cout << "Ctor(2) with vexs and arc." << std::endl;
	numEdges = CountEdges();
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph(int numNodes_, int numEdges_)
	: UndirectedGraph<VertexType, EdgeType>(Vector<VertexType>(numNodes_), numNodes_, numEdges_),
	arc(Vector<Vector<EdgeType>>(numNodes_, Vector<EdgeType>(numNodes_))),
	coord(Vector<Point>(numNodes_)), visited(Vector<bool>(numNodes_))
{
	std::cout << "Ctor(3) with numNodes and vexs." << std::endl;
	VertexType value;
	printf("Please input %d vertexes:\n", numNodes_);
	for (int i = 0; std::cin >> value && i < numNodes_; i++)
		vexs.push_back(value);
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph(const MatrixGraph& rhs)
	: UndirectedGraph<VertexType, EdgeType>(rhs.vexs, rhs.numNodes, rhs.numEdges),
	arc(rhs.arc), coord(rhs.coord), visited(rhs.visited)
{
	std::cout << "Copy Ctor!" << std::endl;
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>& MatrixGraph<VertexType, EdgeType>::operator=(const MatrixGraph& rhs)
{
	std::cout << "Copy Assignment!" << std::endl;
	if (this != &rhs) {
		vexs = rhs.vexs;
		numNodes = rhs.numNodes;
		numEdges = rhs.numEdges;
		arc = rhs.arc;
		coord = rhs.coord;
		visited = rhs.visited;
	}
	return *this;
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::MatrixGraph(MatrixGraph&& rhs) noexcept
	: UndirectedGraph<VertexType, EdgeType>(std::move(rhs.vexs), std::move(rhs.numNodes), std::move(rhs.numEdges))
{
	std::cout << "Move Ctor!" << std::endl;
	// Swap the data members with the source object
	std::swap(arc, rhs.arc);
	std::swap(coord, rhs.coord);
	std::swap(visited, rhs.visited);
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>& MatrixGraph<VertexType, EdgeType>::operator=(MatrixGraph&& rhs) noexcept
{
	if (this != &rhs) {
		std::cout << "Move Assignment!" << std::endl;
		// Swap the data members with the source object
		std::swap(vexs, rhs.vexs);
		std::swap(numNodes, rhs.numNodes);
		std::swap(numEdges, rhs.numEdges);
		std::swap(arc, rhs.arc);
		std::swap(coord, rhs.coord);
		std::swap(visited, rhs.visited);
	}
	return *this;
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>::~MatrixGraph()
{
	std::cout << "Dtor!" << std::endl;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::CreateGraph()
{
	printf("Please input numNodes and numEdges:\n");
	std::cin >> numNodes >> numEdges;
	vexs = Vector<VertexType>(numNodes);
	arc = Vector<Vector<EdgeType>>(numNodes, Vector<EdgeType>(numNodes));
	Init();
	std::cout << "Please input " << numNodes << " vertexes:\n";
	for (int i = 0; i < numNodes; i++) // 读入顶点信息,建立顶点表
		std::cin >> vexs[i];
	for (int i = 0; i < numNodes; i++) // 邻接矩阵初始化，用GRAPH_INFINITY来表示正无穷∞
		for (int j = 0; j < numNodes; j++)
			arc[i][j] = GRAPH_INFINITY;
	std::cout << YELLOW << "[WARNING]" << " If there is no weight, please enter 0.\n" << RESET;
	for (int k = 0; k < numEdges; k++) // 读入numEdges条边，建立邻接矩阵
	{
		std::cout << "Please input vi, vj and the weight on edge(vi, vj)[" << k + 1 << "]:\n";
		VertexType i, j;
		EdgeType w;
		std::cin >> i >> j >> w; // 输入边(vi,vj)上的权EdgeType
		int ind1 = GetIndex(i), ind2 = GetIndex(j);
		validate(ind1); validate(ind2);
		arc[ind1][ind2] = arc[ind2][ind1] = w;
	}
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::isConnected()
{
	visited = Vector<bool>(numNodes, false); // 初始化visited数组
	DFS(0); // 从第一个顶点开始DFS遍历
	for (int i = 0; i < numNodes; i++) // 遍历visited数组，检查是否所有的顶点都被访问过
		if (!visited[i]) return false; // 如果有未被访问过的顶点，说明不是连通图，返回false
	return true; // 否则返回true
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::hasCircle()
{
	for (int i = 0; i < numNodes; i++)
		if (arc[i][i] != GRAPH_INFINITY)
			return true;
	return false;
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::isTree()
{
	int count = 0; // 定义一个变量，记录非零元素的个数
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (arc[i][j] != GRAPH_INFINITY) { // 如果存在边
				if (i == j) return false; // 如果元素在主对角线上，说明有自环，返回false
				if (i < j) count++; // 如果元素在上三角部分，累加边数
			}
		}
	}
	if (count == numNodes - 1) return true; // 如果非零元素的个数等于顶点数减一，说明是一棵树，返回true
	return false;
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::connected(VertexType v, VertexType u)
{
	connected(GetIndex(v), GetIndex(u));
	return false; // 代码不会执行到这里，只是为了消除编译器的警告
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::connected(int vInd, int uInd)
{
	validate(vInd);
	validate(uInd);
	visited = Vector<bool>(numNodes, false); // 初始化visited数组
	DFS(vInd); // 从v开始DFS遍历
	if (visited[uInd]) return true;  // 如果u被访问过，说明v和u相连通，返回true
	return false; // 否则返回false
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::isExist(VertexType v)
{
	for (int i = 0; i < numNodes; i++)
		if (vexs[i] == v)
			return true;
	return false;
}

template <typename VertexType, typename EdgeType>
inline int MatrixGraph<VertexType, EdgeType>::GetIndex(VertexType v)
{
	for (int i = 0; i < numNodes; i++)
		if (vexs[i] == v)
			return i;
	return -1;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::ModifyVertex(VertexType vertex, VertexType new_value)
{
	ModifyVertex(GetIndex(vertex), new_value);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::ModifyVertex(int vInd, VertexType new_value)
{
	validate(vInd);
	vexs[vInd] = new_value;
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::GetWeight(VertexType v, VertexType u)
{
	GetWeight(GetIndex(v), GetIndex(u));
	return GRAPH_INFINITY; // 代码不会执行到这里，只是为了消除编译器的警告
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::GetWeight(int vInd, int uInd)
{
	validate(vInd);
	validate(uInd);
	return arc[vInd][uInd];
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::ModifyWeight(VertexType v, VertexType u, EdgeType e)
{
	ModifyWeight(GetIndex(v), GetIndex(u), e);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::ModifyWeight(int vInd, int uInd, EdgeType e)
{
	validate(vInd);
	validate(uInd);
	arc[vInd][uInd] = arc[uInd][vInd] = e; // 无向图，需要改两个值
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::InsertVertex(VertexType v)
{
	// 如果这个点已经存在于顶点表中，则不添加
	if (GetIndex(v) != -1)
		return;
	// v不存在于顶点表中，可以添加
	/* 更新顶点表 */
	vexs.push_back(v);
	++numNodes;
	/* 更新邻接矩阵 */
	arc.push_back(Vector<int>(numNodes, GRAPH_INFINITY)); // 在邻接矩阵最后一行后面新增一行，并用GRAPH_INFINITY初始化边值
	for (int i = 0; i < numNodes - 1; i++)              // 在邻接矩阵除最后一行外的每一行的最后面新增一条边（GRAPH_INFINITY）
		arc[i].push_back(GRAPH_INFINITY);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::RemoveVertex(VertexType v)
{
	RemoveVertex(GetIndex(v));
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::RemoveVertex(int ind)
{
	validate(ind);
	/* 更新顶点表 */
	vexs.erase(vexs.begin() + ind);
	/* 更新邻接矩阵 */
	int removedEdges = 0; // 记录与要删除的那个顶点的相关联的边
	for (int i = 0; i < numNodes; i++)
		if (arc[i][ind] != GRAPH_INFINITY)
			removedEdges++;
	for (int j = 0; j < numNodes; j++)
		if (arc[ind][j] != GRAPH_INFINITY)
			removedEdges++;
	arc.erase(arc.begin() + ind);
	for (int i = 0; i < numNodes; i++)
		arc[i].erase(arc[i].begin() + ind);
	--numNodes;
	numEdges -= removedEdges;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::InsertEdge(VertexType v, VertexType u, EdgeType e)
{
	InsertEdge(GetIndex(v), GetIndex(u), e);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::InsertEdge(int vInd, int uInd, EdgeType e)
{
	validate(vInd);
	validate(uInd);
	if (arc[vInd][uInd] != GRAPH_INFINITY) {
		std::cout << "This edge already exists! If you want to modify this edge, you should call modified functions!\n";
		std::abort();
	}
	/* 更新邻接矩阵 */
	arc[vInd][uInd] = arc[uInd][vInd] = e;
	++numEdges;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::RemoveEdge(VertexType v, VertexType u)
{
	RemoveEdge(GetIndex(v), GetIndex(u));
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::RemoveEdge(int vInd, int uInd)
{
	validate(vInd);
	validate(uInd);
	arc[vInd][uInd] = arc[uInd][vInd] = GRAPH_INFINITY;
	--numEdges;
}

template <typename VertexType, typename EdgeType>
int MatrixGraph<VertexType, EdgeType>::CountEdges()
{
	int count = 0;
	for (int i = 0; i < numNodes; i++)
		for (int j = 0; i < numNodes; j++)
			if (arc[i][j] != GRAPH_INFINITY)
				count++;
	numEdges = count;
	return count;
}

template <typename VertexType, typename EdgeType>
void MatrixGraph<VertexType, EdgeType>::printMatrix()
{
	std::cout << GREEN << "[Matrix] Vertex table:\n" << RESET;
	for (int i = 0; i < numNodes; i++)
		std::cout << vexs[i] << " ";
	std::cout << std::endl;
	std::cout << GREEN << "[Matrix] Adjacency matrix:\n" << RESET;
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (arc[i][j] == GRAPH_INFINITY)
				std::cout << RED << std::setw(5) << "NULL" << RESET;
			else
				std::cout << std::setw(5) << arc[i][j];
		}
		std::cout << "\n";
	}
}

template <typename VertexType, typename EdgeType>
void MatrixGraph<VertexType, EdgeType>::printCoord()
{
	coord.clear(); // 清空坐标表
	coord = adjToCoord(); // 将邻接矩阵转换为坐标表
	std::cout << "[Coord]: Vertex table:\n";
	for (int i = 0; i < numNodes; i++)
		std::cout << vexs[i] << " ";
	std::cout << std::endl;
	std::cout << "[Coord]: Coordinate table:\n";
	for (int i = 0; i < numNodes; i++)
		std::cout << "(" << coord[i].x << ", " << coord[i].y << ") ";
	std::cout << std::endl;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::DFSTraverse()
{
	visited = Vector<bool>(numNodes, false); // 初始所有顶点状态都是未访问过状态
	for (int i = 0; i < numNodes; i++) // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
		if (!visited[i])
			DFS(i);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::BFSTraverse()
{
	visited = Vector<bool>(numNodes, false); // 初始所有顶点状态都是未访问过状态
	for (int i = 0; i < numNodes; i++) // 对每一个未访问过的顶点做循环
		if (!visited[i])
			BFS(i);
}

template <typename VertexType, typename EdgeType>
inline Vector<VertexType> MatrixGraph<VertexType, EdgeType>::Prim()
{
	Vector<VertexType> vertexs(numNodes); // 保存相关顶点（已选顶点）
	Vector<bool> used(numNodes, false); // 已选顶点集
	Vector<int> adj_vex(numNodes); // 保存相关顶点下标
	Vector<EdgeType> low_cost(numEdges, GRAPH_INFINITY); // 保存相关顶点间边的权值
	low_cost[0] = 0; // 初始化第一个权值为0，即v0加入生成树
	/* low_cost的值为0，在这里就是此下标的顶点已经加入生成树 */
	adj_vex[0] = 0; // 初始化第一个顶点下标为0
	vertexs[0] = vexs[0]; // 初始化第一个顶点
	for (int i = 1; i < numNodes && arc[0][i] != GRAPH_INFINITY; i++) { // 循环除下标为0外并且与v0有边的全部顶点
		low_cost[i] = arc[0][i]; // 将v0顶点与之有边的权值存入数组
		adj_vex[i] = 0; //初始化都为v0的下标
		vertexs[i] = vexs[0]; // 初始化都为v0的值
	}
	int ind = -1; // 保存最小权值的下标
	for (int i = 0; i < numNodes; i++) {
		int min = GRAPH_INFINITY; // 初始化最小权值为∞
		for (int j = 1; j < numNodes; j++) {
			if (low_cost[j] != 0 && low_cost[j] < min) { // 如果权值不为0且权值小于min
				min = low_cost[j]; // 则让当前权值成为最小值
				ind = j; // 将当前最小值的下标存入ind
			}
		}
		std::cout << "[index]: (" << adj_vex[ind] << ", " << ind << ")\n"; // 打印当前顶点边中权值最小的边
		std::cout << "[vertex]: (" << vertexs[ind] << "->" << vexs[ind] << ")\n";
		low_cost[ind] = 0; // 将当前顶点的权值设置为0,表示此顶点已经完成任务
		for (int j = 1; j < numNodes; j++) {
			if (low_cost[j] != 0 && arc[ind][j] < low_cost[j]) { // 如果下标为ind顶点各边权值小于此前这些顶点未被加入生成树权值
				low_cost[j] = arc[ind][j]; // 将较小的权值存入low_cost相应位置
				adj_vex[j] = ind; // 将下标为ind的顶点存入adj_vex
				vertexs[j] = vexs[ind]; // 将下标为ind的顶点的值存入vertexs
			}
		}
	}
	return vertexs;
}

template <typename VertexType, typename EdgeType>
inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Edge> MatrixGraph<VertexType, EdgeType>::Kruskal()
{
	Vector<Edge> edges; // 定义边集数组
	for (int i = 0; i < numNodes - 1; i++)
		for (int j = i + 1; j < numNodes; j++)
			if (arc[i][j] != GRAPH_INFINITY)
				edges.push_back(Edge(vexs[i], vexs[j], i, j, arc[i][j]));
	std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2)
		{
			return e1.weight < e2.weight;
		});
	std::cout << GREEN << "[Kruskal] After sorting:\n" << RESET;
	for (int i = 0; i < numEdges; i++) {
		std::cout << "[index] (" << edges[i].beginInd << ", " << edges[i].endInd << "): " << edges[i].weight << "\n";
		std::cout << "[vertex] " << edges[i].beginVex << "->" << edges[i].endVex << " : " << edges[i].weight << "\n";
	}
	// 打印最小生成树
	Vector<int> parent(numNodes, 0); // 定义一数组用来判断边与边是否形成环路。初始化数组值为0
	std::cout << GREEN << "[Kruskal] Print the minimum spanning tree:\n" << RESET;
	for (int i = 0; i < numEdges; i++) {
		const int n = findTailInd(parent, edges[i].beginInd);
		const int m = findTailInd(parent, edges[i].endInd);
		if (n != m) { // 假如n与m不等，说明此边没有与现有的生成树形成环路
			parent[n] = m; // 将此边的结尾顶点放入下标为起点的parent中，表示此顶点已经在生成树集合中
			std::cout << "[index] (" << edges[i].beginInd << ", " << edges[i].endInd << "): " << edges[i].weight << "\n";
			std::cout << "[vertex] " << edges[i].beginVex << "->" << edges[i].endVex << " : " << edges[i].weight << "\n";
		}
	}
	return edges;
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::Dijkstra(const VertexType& startVex, Vector<int>& path, Vector<EdgeType>& shortPathTable)
{
	Dijkstra(GetIndex(startVex), path, shortPathTable);
}

/**
 * @brief Dijkstra最短路径
 *
 * @tparam VertexType
 * @param startInd 起始顶点的下标(start vertex)。即计算"v(startInd)"到其它顶点的最短路径。
 * @param path  path[i]的值是"v(startInd)"到"v(i)"的最短路径所经历的全部顶点中，位于"v(i)"之前的那个顶点下标。
 * @param shortPathTable shortPathTable[i]是"v(startInd)"到"v(i)"的最短路径的长度。
 */
template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::Dijkstra(int startInd, Vector<int>& path, Vector<EdgeType>& shortPathTable)
{
	// 如果传进来的参数没有初始化
	if (path.size() <= numNodes || shortPathTable.size() <= numNodes) {
		path = Vector<int>(numNodes);
		shortPathTable = Vector<EdgeType>(numNodes);
	}
	validate(startInd);
	Vector<bool> final(numNodes, false); // final[i]表示求得顶点v(startInd)至v(i)的最短路径
	for (int i = 0; i < numNodes; i++) {
		path[i] = -1; // 初始化路径数组均为-1
		shortPathTable[i] = arc[startInd][i]; // 将与v0点有连线的顶点加上权值
	}
	shortPathTable[startInd] = 0;// v0至v0路径为0
	final[startInd] = true; // v0至v0不需要求路径
	int ind;
	/* 开始主循环，每次求得v0到某个v顶点的最短路径 */
	for (int i = 1; i < numNodes; i++) {
		int min = GRAPH_INFINITY; // 当前所知离v0顶点的最近距离
		for (int j = 0; j < numNodes; j++) { // 寻找离v0最近的顶点
			if (!final[j] && shortPathTable[j] < min) {
				min = shortPathTable[j]; // v(j)离v0顶点更近
				ind = j; // 记录v(j)下标
			}
		}
		final[ind] = true;// 标记v(j)为已经获取到最短路径
		/* 修正当前最短路径和前驱顶点 */
		for (int j = 0; j < numNodes; j++) {
			/* 如果经过顶点v(ind)的路径比现在这条路径的长度短的话 */
			EdgeType tmp = arc[ind][j] == GRAPH_INFINITY ? GRAPH_INFINITY : min + arc[ind][j]; // 防止溢出
			if (!final[j] && (tmp < shortPathTable[j])) { // 说明找到了更短的路径，修改shortPathTable[j]和path[j]
				shortPathTable[j] = tmp; // 修改当前路径长度
				path[j] = ind;
			}
		}
	}
	/* 打印Dijkstra最短路径的结果 */
	std::cout << GREEN << "[Dijkstra] Start vertex: " << vexs[startInd] << "\n" << RESET;
	for (int i = 0; i < numNodes; i++)
		std::cout << CYAN << "[Dijkstra] shortest distance (" << vexs[startInd] << ", " << vexs[i] << ") = " << shortPathTable[i] << "\n" << RESET;

	/*for (int i = 0; i < numNodes; ++i) {
		if (i == startInd) continue;
		std::cout << "[Dijkstra] shortest distance (" << vexs[startInd] << ", " << vexs[i] << ") = " << shortPathTable[i] << "\n";
		std::cout << "[Dijkstra] Path: " << vexs[startInd];
		int k = i;
		while (path[k] != -1) {
			std::cout << "->" << vexs[k];
			k = path[k];
		}
		std::cout << "->" << vexs[i] << "\n";
	}*/
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::Floyd(Vector<Vector<int>>& path, Vector<Vector<EdgeType>>& shortPathTable)
{
	// 如果传进来的参数不符合要求
	if (path.size() <= numNodes || shortPathTable.size() <= numNodes) {
		path = Vector<Vector<int>>(numNodes, Vector<int>(numNodes));
		shortPathTable = Vector<Vector<EdgeType>>(numNodes, Vector<EdgeType>(numNodes));
	}
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			shortPathTable[i][j] = arc[i][j]; // shortPathTable[i][j]值即为对应点间的权值
			path[i][j] = j; // 初始化path
		}
	}
	for (int k = 0; k < numNodes; k++) {
		for (int i = 0; i < numNodes; i++) {
			for (int j = 0; j < numNodes; j++) {
				EdgeType tmp = shortPathTable[i][k] == GRAPH_INFINITY || shortPathTable[k][j] == GRAPH_INFINITY
					? GRAPH_INFINITY
					: shortPathTable[i][k] + shortPathTable[k][j];
				if (shortPathTable[i][j] > tmp) { // 如果经过下标为k顶点路径比原两点间路径更短
					shortPathTable[i][j] = tmp; // 将当前两点间权值设为更小的一个
					path[i][j] = path[i][k]; // 路径设置为经过下标为k的顶点下标
				}
			}
		}
	}
	/* 打印Floyd最短路径的结果 */
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (shortPathTable[i][j] == GRAPH_INFINITY)
				std::cout << RED << "[Floyd] shortest distance (" << vexs[i] << ", " << vexs[j] << ") = " << "NULL\n" << RESET;
			else {
				std::cout << GREEN << "[Floyd] shortest distance (" << vexs[i] << ", " << vexs[j] << ") = " << shortPathTable[i][j] << "\n" << RESET;
				int k = path[i][j];
				std::cout << CYAN << "[Floyd] " << "path: " << vexs[i];
				while (k != j) {
					std::cout << "->" << vexs[k];
					k = path[k][j];
				}
				std::cout << "->" << vexs[j] << "\n" << RESET;
			}
		}
	}
}

template <typename VertexType, typename EdgeType>
inline std::vector<VertexType> MatrixGraph<VertexType, EdgeType>::AStar(const VertexType& start, const VertexType& goal)
{
	std::priority_queue <
		std::pair<VertexType, EdgeType>,
		std::vector<std::pair<VertexType, EdgeType>>,
		std::greater<std::pair<VertexType, EdgeType>> > frontier; // 创建一个优先队列，存储节点和代价
	frontier.push(std::make_pair(start, 0)); // 将起点和代价0插入到优先队列中
	std::unordered_map<VertexType, VertexType> came_from; // 创建一个哈希表，存储每个节点的前驱
	std::unordered_map<VertexType, EdgeType> cost_so_far; // 创建一个哈希表，存储代价
	came_from[start] = start; // 将起始节点的前驱设为它自己
	cost_so_far[start] = 0; // 将起始节点的代价设为0
	while (!frontier.empty()) { // 当优先队列不为空时
		auto current = frontier.top(); // 取出优先队列中的队首节点
		frontier.pop(); // 将队首节点出队
		if (current.first == goal) break; // 如果当前节点是目标节点，就提前结束循环
		for (auto next : neighbors(current.first)) { // 遍历当前节点的邻居节点
			EdgeType new_cost = cost_so_far[current.first] + cost(current.first, next); // 计算从起始节点到邻居节点的新代价
			// error: "contains": 不是 "std::unordered_map<VertexType,EdgeType,std::hash<VertexType>,std::equal_to<VertexType>,std::allocator<std::pair<const VertexType,EdgeType>>>" 的成员
			// ReSharper disable once CppUseAssociativeContains
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) { // 如果邻居节点没有被访问过，或者新的代价更小
				cost_so_far[next] = new_cost; // 更新邻居节点的代价
				EdgeType priority = new_cost + heuristic(goal, next); // 计算邻居节点的优先级
				frontier.push(std::make_pair(next, priority)); // 将邻居节点和优先级插入到优先队列中
				came_from[next] = current.first; // 更新邻居节点的前驱
			}
		}
	}
	/* 根据came_from哈希表，从目标节点回溯到起始节点，构造出一条路径，并将其存储在path列表中 */
	std::vector<VertexType> path;
	VertexType cur = goal; // 从目标节点开始
	while (cur != start) { // 当当前节点不是起始节点时
		path.push_back(cur); // 将当前节点加入路径
		cur = came_from[cur]; // 将当前节点更新为其前驱节点
	}
	path.push_back(start); // 将起始节点加入路径（可选）
	std::reverse(path.begin(), path.end()); // 将路径反转（可选）
	return path;
}

template <typename VertexType, typename EdgeType>
void MatrixGraph<VertexType, EdgeType>::PrintPath(const Vector<VertexType>& path,
	const Vector<EdgeType>& shortPathTable)
{

}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType>& MatrixGraph<VertexType, EdgeType>::operator*=(const MatrixGraph& rhs)
{
	if (this->numNodes == rhs.numNodes) // 可以相乘
		*this = *this * rhs;
	return *this; // 如果不能相乘，则返回自身
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType> MatrixGraph<VertexType, EdgeType>::operator*(const MatrixGraph& rhs)
{
	if (this->numNodes != rhs.numNodes) // 顶点个数不同，不能进行相乘
	{
		std::cout << "The number of vertexes is different. Cannot be multiplied!\n";
		return MatrixGraph();
	}
	// 可以相乘
	MatrixGraph<VertexType, EdgeType> result;
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			int sum = 0; // 计算结果矩阵中的元素值
			for (int k = 0; k < numNodes; k++) // 遍历第一个矩阵的每一列和第二个矩阵的每一行
				sum += this->arc[i][k] * rhs.arc[k][j]; // 累加乘积
			result.arc[i][j] = sum;
		}
	}
	return result;
}

template <typename VertexType, typename EdgeType>
void MatrixGraph<VertexType, EdgeType>::Init()
{
	if (!coord.empty() && !visited.empty()) {
		coord.clear();
		visited.clear();
		return;
	}
	coord = Vector<Point>(numNodes);
	visited = Vector<bool>(numNodes);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::validate(int ind)
{
	if (ind < 0 || ind >= numNodes)
		throw std::out_of_range("Index out of range or could not find the vertex!");
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::DFS(int startInd)
{
	validate(startInd);
	visited[startInd] = true; // 将当前顶点标记为已访问
	//std::cout << vexs[startInd] << " "; // 打印顶点（也可以做其他操作）
	for (int i = 0; i < numNodes; i++) // 对未访问的邻接顶点递归调用
		if (arc[startInd][i] != GRAPH_INFINITY && !visited[i])
			DFS(i);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::BFS(int startInd)
{
	validate(startInd);
	Queue<int> q;
	visited[startInd] = true; // 设置当前顶点访问过
	std::cout << vexs[startInd] << " "; // 打印顶点（也可以做其他操作）
	q.push(startInd); // 将此顶点入队列
	while (!q.empty()) {
		int ind = q.front(); // 将队首元素出列，并将其索引值赋值给ind
		q.pop();
		for (int i = 0; i < numNodes; i++)
			if (arc[ind][i] != GRAPH_INFINITY && !visited[i]) {
				visited[i] = true;
				std::cout << vexs[i] << " "; // 打印顶点（也可以做其他操作）
				q.push(i);
			}
	}
}

template <typename VertexType, typename EdgeType>
inline int MatrixGraph<VertexType, EdgeType>::findTailInd(const Vector<int>& parent, int ind)
{
	while (parent[ind] > 0)
		ind = parent[ind];
	return ind;
}

template <typename VertexType, typename EdgeType>
inline Vector<VertexType> MatrixGraph<VertexType, EdgeType>::neighbors(const VertexType& cur)
{
	int ind = GetIndex(cur);
	if (ind == -1) {
		std::cout << "Could not find the vertex!" << std::endl;
		std::abort();
	}
	Vector<VertexType> result;
	for (int i = 0; i < numNodes && i != ind; i++) // 遍历当前节点的邻居节点
		if (arc[ind][i] != GRAPH_INFINITY) // 如果当前节点和邻居节点之间有边
			result.push_back(vexs[i]); // 将邻居节点加入到结果列表中
	return result;
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::cost(const VertexType& cur, const VertexType& next)
{
	int curInd = GetIndex(cur), nextInd = GetIndex(next);
	validate(curInd);
	validate(nextInd);
	return arc[curInd][nextInd]; // 返回邻接矩阵中对应位置的元素值
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::heuristic(const VertexType& a, const VertexType& b)
{
	// 计算a和b之间的曼哈顿距离
	int aInd = GetIndex(a), bInd = GetIndex(b);
	validate(aInd);
	validate(bInd);
	coord.clear();
	coord = adjToCoord(); // 将邻接矩阵转换为坐标矩阵
	Point aCoord = coord[aInd], bCoord = coord[bInd]; // 获取a和b的坐标
	return std::abs(aCoord.x - bCoord.x) + std::abs(aCoord.y - bCoord.y); // 返回曼哈顿距离
}

template <typename VertexType, typename EdgeType>
inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Point> MatrixGraph<VertexType, EdgeType>::adjToCoord()
{
	Vector<Point> coordMatrix(numNodes);
	//初始化坐标矩阵的第一个元素为(0,0)
	coordMatrix[0] = Point(0, 0);
	Queue<int> que; // 创建一个队列，用于广度优先搜索
	visited = Vector<bool>(numNodes, false);
	// 将第一个顶点入队，并标记为已访问
	que.push(0);
	visited[0] = true;
	while (!que.empty()) {
		int curInd = que.front();
		que.pop();
		// 遍历邻接矩阵的当前行，找到与当前顶点相邻的顶点
		for (int i = 0; i < numNodes; i++) {
			//如果存在边，并且没有访问过
			if (arc[curInd][i] != GRAPH_INFINITY && !visited[i]) {
				//将该顶点入队，并标记为已访问
				que.push(i);
				visited[i] = true;
				//根据当前顶点的坐标和边的方向，计算该顶点的坐标
				//这里假设边只有水平或垂直方向，并且长度为1
				if (curInd < i) { //如果边是向右或向下的
					coordMatrix[i].x = coordMatrix[curInd].x + (i - curInd) / numNodes; //横坐标加上行差
					coordMatrix[i].y = coordMatrix[curInd].y + (i - curInd) % numNodes; //纵坐标加上列差
				}
				else { //如果边是向左或向上的
					coordMatrix[i].x = coordMatrix[curInd].x - (curInd - i) / numNodes; //横坐标减去行差
					coordMatrix[i].y = coordMatrix[curInd].y - (curInd - i) % numNodes; //纵坐标减去列差
				}
			}
		}
	}
	return coordMatrix;
}

/* 友元函数 */
template <typename V, typename W>
std::istream& operator>>(std::istream& is, MatrixGraph<V, W>& G)
{
	for (int i = 0; i < G.numNodes; i++)
		for (int j = 0; j < G.numNodes; j++)
			is >> G.arc[i][j];
	return is;
}

template <typename V, typename W>
std::ostream& operator<<(std::ostream& os, const MatrixGraph<V, W>& G)
{
	os << "[UndirectedGraph]: Adjacency Matrix:\n";
	for (int i = 0; i < G.numNodes; i++) {
		for (int j = 0; j < G.numNodes; j++)
			os << G.arc[i][j] << " ";
		os << "\n";
	}
	return os;
}
