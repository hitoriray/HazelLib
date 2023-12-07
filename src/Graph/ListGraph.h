#pragma once

#include "DirectedGraph.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../Stack/Stack.h"
#include "../Queue/Queue.h"
#include <map>
#include <unordered_set>
#include <unordered_map>

using Hazel::Stack;
using Hazel::Queue;

template <typename VertexType, typename EdgeType = int>
class ListGraph : public virtual DirectedGraph<VertexType, EdgeType>
{
	using DirectedGraph<VertexType, EdgeType>::numNodes;
	using DirectedGraph<VertexType, EdgeType>::numEdges;
	using DirectedGraph<VertexType, EdgeType>::vexs;

	struct Node
	{
		Node() = default;
		Node(VertexType data_) : data(data_) {}
		VertexType data; // 顶点数据
	};
	// 定义Node类型的哈希函数
	struct NodeHash
	{
		std::size_t operator()(const Node* node) const {
			return std::hash<VertexType>()(node->data); // 用顶点数据作为哈希值，需要调用VertexType类型的哈希函数
		}
	};
	// 定义Node类型的相等函数
	struct NodeEqual {
		bool operator()(const Node* node1, const Node* node2) const {
			return node1->data == node2->data; // 用顶点数据判断是否相等
		}
	};
	struct Edge
	{
		Edge() = default;
		Edge(VertexType* start_, VertexType* end_, EdgeType weight_)
			: start(start_), end(end_), weight(weight_) {}
		VertexType* start; // 边的起点
		VertexType* end; // 边的终点
		EdgeType weight; // 边的权值
	};

public:
	ListGraph();
	ListGraph(const std::vector<VertexType>& vexs_, int numNodes_, int numEdges_);
	ListGraph(int numNodes_, int numEdges_);
	ListGraph(const ListGraph& rhs);
	ListGraph& operator=(const ListGraph& rhs);
	ListGraph(ListGraph&& rhs) noexcept;
	ListGraph& operator=(ListGraph&& rhs) noexcept;
	~ListGraph() override;

	inline void CreateGraph() override;
	inline void display();

	inline bool isConnected() override;
	inline bool isTree() override;
	inline bool hasCircle() override;
	inline bool connected(VertexType v, VertexType u) override;
	inline bool hasEdge(VertexType v, VertexType u) override;

	inline void InsertVertex(VertexType v) override;
	inline void InsertEdge(VertexType v, VertexType u, EdgeType e) override;
	inline void RemoveVertex(VertexType v) override;
	inline void RemoveEdge(VertexType v, VertexType u) override;
	inline void ModifyVertex(VertexType vertex, VertexType new_value) override;
	inline void ModifyWeight(VertexType v, VertexType u, EdgeType new_weight) override;
	inline EdgeType GetWeight(VertexType v, VertexType u) override;
	inline int GetIndex(VertexType v) override;
	inline bool isExist(VertexType v) override;

	void DFSTraverse() override;
	void BFSTraverse() override;
	std::vector<VertexType>& Prim() override;
	//std::vector<Edge> Kruskal() override;
	void Dijkstra(const VertexType& startVex, std::vector<int>& path, std::vector<EdgeType>& shortPathTable) override;
	void Floyd(std::vector<std::vector<int>>& path, std::vector<std::vector<EdgeType>>& shortPathTable) override;
	std::vector<VertexType> AStar(const VertexType& start, const VertexType& goal) override;

private:
	void Init() override;
	void validate(int ind) override;
	void DFS(Node* v);
	void DFS_Stack(Node* v);
	void BFS(Node* v);
	int findTailInd(const std::vector<int>& parent, int tailInd) override; // 寻找末尾顶点
	std::vector<VertexType> neighbors(const VertexType& cur) override; // 当前顶点的邻居顶点
	EdgeType cost(const VertexType& cur, const VertexType& next) override; // 当前顶点到下一个顶点的权重
	Node* findNode(const VertexType& v) const; // 寻找顶点v对应的节点
	Edge* findEdge(const VertexType& start, const VertexType& goal) const; // 寻找顶点v对应的节点

private:
	//std::vector<std::vector<Edge*>> adjList; // 用std::map实现的话可能会更好？
	std::map<Node*, std::vector<Edge*>> adjList; // 邻接表，用map存储每个节点对应的边链表
	// 用unordered_set存储已访问过的顶点，需要指定哈希函数和相等函数
	std::unordered_set<Node*, NodeHash, NodeEqual> visited;
	// 定义一个map存储每个顶点的根节点，需要指定哈希函数和相等函数（并查集）
	std::unordered_map<Node*, Node*, NodeHash, NodeEqual> parents;
};


template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::ListGraph()
	: DirectedGraph<VertexType, EdgeType>(), adjList()
{
	std::cout << "Default Ctor!\n";
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::ListGraph(const std::vector<VertexType>& vexs_, int numNodes_, int numEdges_)
	: DirectedGraph<VertexType, EdgeType>(vexs_, numNodes_, numEdges_)
{
	std::cout << "Ctor(1)\n";
	adjList.resize(numNodes_);
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::ListGraph(int numNodes_, int numEdges_)
	: DirectedGraph<VertexType, EdgeType>(numNodes_, numEdges_)
{
	std::cout << "Ctor(2)\n";
	adjList.resize(numNodes_);
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::ListGraph(const ListGraph& rhs)
	: DirectedGraph<VertexType, EdgeType>(rhs), adjList(rhs.adjList)
{
	std::cout << "Copy Ctor!\n";
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>& ListGraph<VertexType, EdgeType>::operator=(const ListGraph& rhs)
{
	std::cout << "Copy Assignment!" << std::endl;
	if (this != &rhs) {
		vexs = rhs.vexs;
		numNodes = rhs.numNodes;
		numEdges = rhs.numEdges;
		adjList = rhs.adjList;
	}
	return *this;
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::ListGraph(ListGraph&& rhs) noexcept
	: DirectedGraph<VertexType, EdgeType>(std::move(vexs), std::move(rhs.numNodes), std::move(rhs.numEdges))
{
	std::cout << "Move Ctor!\n";
	std::swap(adjList, rhs.adjList);
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>& ListGraph<VertexType, EdgeType>::operator=(ListGraph&& rhs) noexcept
{
	std::cout << "Move Assignment!" << std::endl;
	if (this != &rhs)
	{
		std::swap(vexs, rhs.vexs);
		std::swap(numNodes, rhs.numNodes);
		std::swap(numEdges, rhs.numEdges);
		std::swap(adjList, rhs.adjList);
	}
	return *this;
}

template <typename VertexType, typename EdgeType>
ListGraph<VertexType, EdgeType>::~ListGraph()
{
	std::cout << "Dtor!" << std::endl;
	for (auto it = adjList.begin(); it != adjList.end(); ++it) {
		delete it->first; // 释放节点
		for (auto e : it->second) {
			delete e; // 释放边
		}
		it->second.clear(); // 清空链表
	}
	adjList.clear(); // 清空map
}


template <typename VertexType, typename EdgeType>
inline void ListGraph<VertexType, EdgeType>::CreateGraph()
{
	printf("Please input numNodes and numEdges:\n");
	std::cin >> numNodes >> numEdges;
	std::cout << "Please input " << numNodes << " vertexes:\n";
	for (int i = 0; i < numNodes; i++) {
		std::cin >> vexs[i];
		adjList.insert(std::make_pair(new Node(vexs[i]), std::vector<Edge*>()));
	}
	for (int k = 0; k < numNodes; k++) {
		std::cout << "Please input vi, vj and the weight on edge(vi, vj)[" << k + 1 << "]:\n";
		VertexType from, to;
		EdgeType weight;
		std::cin >> from >> to >> weight; // 输入边(vi,vj)上的权
		int from_ind = GetIndex(from), to_ind = GetIndex(to);
		validate(from_ind); validate(to_ind);
		Node* start = findNode(from), end = findNode(to);
		if (start == nullptr || end == nullptr) return;
		Edge* edge = new Edge(start, end, weight);
		adjList[start].push_back(edge);
	}
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::display()
{
	std::cout << "The undirected graph has " << numNodes << " vertexes and " << numEdges << " edges.\n";
	std::cout << "The vertexes are:\n";
	for (int i = 0; i < numNodes; i++)
		std::cout << vexs[i] << " ";
	std::cout << std::endl;
	std::cout << "The edges are:\n";
	for (int i = 0; i < numNodes; i++) {
		for (auto e : adjList[i])
			std::cout << "(" << e->start->data << ", " << e->end->data << ") " << e->weight;
		std::cout << std::endl;
	}
}

template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::isConnected()
{
	visited.clear(); // 清空visited数组
	if (vexs.empty()) return true;
	DFS(&vexs[0]); // 从第一个顶点开始DFS遍历
	for (auto v : vexs) // 遍历visited数组，检查是否所有的顶点都被访问过
		if (visited.count(v) == 0) return false; // 如果有未被访问过的顶点，说明不是连通图，返回false
	return true;
}

template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::isTree()
{
	visited.clear();
	if (vexs.empty()) return true;
	DFS(&vexs[0]);
	if (numEdges == numNodes - 1) {
		for (auto v : vexs)
			if (visited.count(v) == 0) return false; // 如果存在顶点未被访问过，则不是树
	}
	return true;
}

/**
 * \brief 应该还不是充要条件，之后再回来修改
 * \return
 */
template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::hasCircle()
{
	visited.clear();
	if (vexs.empty()) return true;
	DFS(&vexs[0]);
	if (numEdges <= numNodes - 1) return false;
	for (auto v : vexs)
		if (visited.count(v) == 0) return false; // 如果存在顶点未被访问过，则没有环
	return true;
}

template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::connected(VertexType v, VertexType u)
{
	return false;
}

template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::hasEdge(VertexType v, VertexType u)
{
	return false;
}

template <typename VertexType, typename EdgeType>
bool ListGraph<VertexType, EdgeType>::isExist(VertexType v)
{
	return GetIndex(v) != -1;
}

template <typename VertexType, typename EdgeType>
int ListGraph<VertexType, EdgeType>::GetIndex(VertexType v)
{
	for (int i = 0; i < numNodes; i++)
		if (vexs[i] == v)
			return i;
	return -1;
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::ModifyVertex(VertexType vertex, VertexType new_value)
{
	int index = GetIndex(vertex);
	validate(index);
	Node* v = findNode(vertex);
	if (v == nullptr) return;
	v->data = new_value; // 修改顶点的数据成员(因为这里修改了v的data，所以v此时是一个新的键)
	// 更新邻接表中的键和值
	adjList[v] = adjList[v]; // 把原来的键对应的值赋给新的键
	adjList.erase(v); // 删除原来的键
	for (auto& p : adjList) { // 遍历邻接表中的每个键值对
		for (Edge* e : p.second) { // 遍历每个键对应的边向量
			if (e->start == v || e->end == v) { // 如果边的起点或终点是要修改的顶点
				e->start = v; // 更新边的起点为新的顶点指针
				e->end = v; // 更新边的终点为新的顶点指针
			}
		}
	}
	// 更新并查集中的父节点
	parents[v] = parents[v]; // 把原来的键对应的值赋给新的键
	parents.erase(v); // 删除原来的键
	for (auto& p : parents) { // 遍历并查集中的每个键值对
		if (p.second == v) { // 如果某个键对应的父节点是要修改的顶点
			p.second = v; // 更新父节点为新的顶点指针
		}
	}
}

template <typename VertexType, typename EdgeType>
EdgeType ListGraph<VertexType, EdgeType>::GetWeight(VertexType v, VertexType u)
{
	Node* start = findNode(v);
	Node* goal = findNode(u);
	if (start == nullptr || goal == nullptr) return EdgeType();
	for (Edge* e : adjList[start])
		if (e->end == goal)
			return e->weight;
	return EdgeType();
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::ModifyWeight(VertexType v, VertexType u, EdgeType new_weight)
{
	Node* start = findNode(v);
	Node* goal = findNode(u);
	if (start == nullptr || goal == nullptr) return;
	for (Edge* e : adjList[start]) {
		if (e->end == goal) {
			e->weight = new_weight;
			// 更新邻接表中的值
			adjList[start] = adjList[start]; // 把原来的键对应的值赋给新的键
			adjList.erase(start); // 删除原来的键
			break; // 跳出循环
		}
	}
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::InsertVertex(VertexType v)
{
	if (GetIndex(v) != -1)
		return;
	vexs.push_back(v);
	++numNodes;
	Node* node = new Node(v); // 创建新节点
	std::vector<Edge*> list; // 创建空链表
	adjList.insert(std::make_pair(node, list)); // 插入邻接表中
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::RemoveVertex(VertexType v)
{
	validate(GetIndex(v)); // 检查顶点是否存在
	Node* node = findNode(v); // 查找节点
	if (node == nullptr) return; // 如果节点不存在，返回
	adjList.erase(node); // 从邻接表中删除节点
	--numNodes;
	for (auto it = adjList.begin(); it != adjList.end(); ++it) {
		for (auto e : it->second) {
			if (e->start == node || e->end == node) { // 如果边的起点(起点应该是不可能了，因为在上面已经删掉了)或终点是该节点
				//it->second->remove(e);
				it->second.erase(remove(it->second.begin(), it->second.end(), e), it->second.end()); // 从链表中删除边
				delete e; // 释放边
				--numEdges;
			}
		}
	}
	delete node; // 释放节点
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::InsertEdge(VertexType v, VertexType u, EdgeType e)
{
	validate(GetIndex(v)); validate(GetIndex(u)); // 检查顶点是否存在
	Node* start = findNode(v); // 查找起点
	Node* end = findNode(u); // 查找终点
	if (start == nullptr || end == nullptr) return; // 如果起点或终点不存在，返回
	Edge* edge = new Edge(start, end, e); // 创建新边
	adjList[start].push_back(edge); // 将新边插入起点对应的链表中
	++numEdges;
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::RemoveEdge(VertexType v, VertexType u)
{
	validate(GetIndex(v)); validate(GetIndex(u)); // 检查顶点是否存在
	Edge* edge = findEdge(v, u); // 查找边
	if (edge == nullptr) return;
	Node* start = findNode(v); // 查找起点
	delete edge; // 释放边
	adjList[start].erase(remove(adjList[start].begin(), adjList[start].end(), edge), adjList[start].end()); // 从链表中删除边
	delete start;
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::DFSTraverse()
{
	for (auto v : vexs) // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
		if (visited.count(v) == 0)
			DFS(v);
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::BFSTraverse()
{
	for (auto v : vexs) // 对未访问过的顶点调用DFS，若是连通图，只会执行一次
		if (visited.count(v) == 0)
			DFS(v);
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType>& ListGraph<VertexType, EdgeType>::Prim()
{
	return {};
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::Dijkstra(const VertexType& startVex, std::vector<int>& path,
	std::vector<EdgeType>& shortPathTable)
{
	return {};
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::Floyd(std::vector<std::vector<int>>& path,
	std::vector<std::vector<EdgeType>>& shortPathTable)
{
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> ListGraph<VertexType, EdgeType>::AStar(const VertexType& start, const VertexType& goal)
{
	return {};
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::Init()
{
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::validate(int ind)
{
	if (ind < 0 || ind >= numNodes)
		throw std::out_of_range("Index out of range or could not find the vertex!");
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::DFS(Node* v)
{
	std::cout << v->data << " ";
	visited.insert(v);
	// 遍历当前顶点的所有邻接边
	for (Edge* e : adjList[v]) {
		Node* u = e->end; // 获取邻接边的终点
		if (visited.count(u) == 0) // 如果邻接点未被访问过，则递归访问
			DFS(u);
	}
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::DFS_Stack(Node* v)
{
	Stack<Node*> st;
	st.push(v); // 将起始顶点入栈
	visited.insert(v); // 并标记为已访问
	while (!st.empty()) {
		Node* u = st.top(); // 弹出栈顶元素
		st.pop();
		std::cout << u->data << " "; // 打印当前顶点
		for (Edge* e : adjList[u]) { // 遍历当前顶点的所有邻接边
			Node* w = e->end; // 获取邻接边的终点
			if (visited.count(w) == 0) { // 如果邻接点未被访问过，则入栈并标记为已访问
				st.push(w);
				visited.insert(w);
			}
		}
	}
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::BFS(Node* v)
{
	Queue<Node*> que;
	que.push(v);
	visited.insert(v);
	while (!que.empty()) {
		Node* u = que.front();
		que.pop();
		std::cout << u->data << " "; // 打印当前顶点
		for (Edge* e : adjList[u]) { // 遍历当前顶点的所有邻接边
			Node* w = e->end; // 获取邻接边的终点
			if (visited.count(w) == 0) { // 如果邻接点未被访问过，则入队并标记为已访问
				que.push(w);
				visited.insert(w);
			}
		}
	}
}

template <typename VertexType, typename EdgeType>
int ListGraph<VertexType, EdgeType>::findTailInd(const std::vector<int>& parent, int tailInd)
{
	return 0;
}

template <typename VertexType, typename EdgeType>
std::vector<VertexType> ListGraph<VertexType, EdgeType>::neighbors(const VertexType& cur)
{
	return {};
}

template <typename VertexType, typename EdgeType>
EdgeType ListGraph<VertexType, EdgeType>::cost(const VertexType& cur, const VertexType& next)
{
	return EdgeType();
}

template <typename VertexType, typename EdgeType>
typename ListGraph<VertexType, EdgeType>::Node* ListGraph<VertexType, EdgeType>::findNode(const VertexType& v) const
{
	//validate(GetIndex(v));
	for (auto it = adjList.begin(); it != adjList.end(); ++it) {
		if (it->first->data == v) { // 如果找到匹配的数据，返回对应的节点指针
			return it->first;
		}
	}
	return nullptr; // 否则返回空指针
}

template <typename VertexType, typename EdgeType>
typename ListGraph<VertexType, EdgeType>::Edge* ListGraph<VertexType, EdgeType>::findEdge(const VertexType& start,
	const VertexType& goal) const
{
	for (Edge* e : adjList[start])
		if (*e->end == goal) // 如果找到匹配的数据，返回对应的边指针
			return e;
	return nullptr;  // 否则返回空指针
}

