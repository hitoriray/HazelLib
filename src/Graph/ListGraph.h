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
		VertexType data; // ��������
	};
	// ����Node���͵Ĺ�ϣ����
	struct NodeHash
	{
		std::size_t operator()(const Node* node) const {
			return std::hash<VertexType>()(node->data); // �ö���������Ϊ��ϣֵ����Ҫ����VertexType���͵Ĺ�ϣ����
		}
	};
	// ����Node���͵���Ⱥ���
	struct NodeEqual {
		bool operator()(const Node* node1, const Node* node2) const {
			return node1->data == node2->data; // �ö��������ж��Ƿ����
		}
	};
	struct Edge
	{
		Edge() = default;
		Edge(VertexType* start_, VertexType* end_, EdgeType weight_)
			: start(start_), end(end_), weight(weight_) {}
		VertexType* start; // �ߵ����
		VertexType* end; // �ߵ��յ�
		EdgeType weight; // �ߵ�Ȩֵ
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
	int findTailInd(const std::vector<int>& parent, int tailInd) override; // Ѱ��ĩβ����
	std::vector<VertexType> neighbors(const VertexType& cur) override; // ��ǰ������ھӶ���
	EdgeType cost(const VertexType& cur, const VertexType& next) override; // ��ǰ���㵽��һ�������Ȩ��
	Node* findNode(const VertexType& v) const; // Ѱ�Ҷ���v��Ӧ�Ľڵ�
	Edge* findEdge(const VertexType& start, const VertexType& goal) const; // Ѱ�Ҷ���v��Ӧ�Ľڵ�

private:
	//std::vector<std::vector<Edge*>> adjList; // ��std::mapʵ�ֵĻ����ܻ���ã�
	std::map<Node*, std::vector<Edge*>> adjList; // �ڽӱ���map�洢ÿ���ڵ��Ӧ�ı�����
	// ��unordered_set�洢�ѷ��ʹ��Ķ��㣬��Ҫָ����ϣ��������Ⱥ���
	std::unordered_set<Node*, NodeHash, NodeEqual> visited;
	// ����һ��map�洢ÿ������ĸ��ڵ㣬��Ҫָ����ϣ��������Ⱥ��������鼯��
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
		delete it->first; // �ͷŽڵ�
		for (auto e : it->second) {
			delete e; // �ͷű�
		}
		it->second.clear(); // �������
	}
	adjList.clear(); // ���map
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
		std::cin >> from >> to >> weight; // �����(vi,vj)�ϵ�Ȩ
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
	visited.clear(); // ���visited����
	if (vexs.empty()) return true;
	DFS(&vexs[0]); // �ӵ�һ�����㿪ʼDFS����
	for (auto v : vexs) // ����visited���飬����Ƿ����еĶ��㶼�����ʹ�
		if (visited.count(v) == 0) return false; // �����δ�����ʹ��Ķ��㣬˵��������ͨͼ������false
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
			if (visited.count(v) == 0) return false; // ������ڶ���δ�����ʹ���������
	}
	return true;
}

/**
 * \brief Ӧ�û����ǳ�Ҫ������֮���ٻ����޸�
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
		if (visited.count(v) == 0) return false; // ������ڶ���δ�����ʹ�����û�л�
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
	v->data = new_value; // �޸Ķ�������ݳ�Ա(��Ϊ�����޸���v��data������v��ʱ��һ���µļ�)
	// �����ڽӱ��еļ���ֵ
	adjList[v] = adjList[v]; // ��ԭ���ļ���Ӧ��ֵ�����µļ�
	adjList.erase(v); // ɾ��ԭ���ļ�
	for (auto& p : adjList) { // �����ڽӱ��е�ÿ����ֵ��
		for (Edge* e : p.second) { // ����ÿ������Ӧ�ı�����
			if (e->start == v || e->end == v) { // ����ߵ������յ���Ҫ�޸ĵĶ���
				e->start = v; // ���±ߵ����Ϊ�µĶ���ָ��
				e->end = v; // ���±ߵ��յ�Ϊ�µĶ���ָ��
			}
		}
	}
	// ���²��鼯�еĸ��ڵ�
	parents[v] = parents[v]; // ��ԭ���ļ���Ӧ��ֵ�����µļ�
	parents.erase(v); // ɾ��ԭ���ļ�
	for (auto& p : parents) { // �������鼯�е�ÿ����ֵ��
		if (p.second == v) { // ���ĳ������Ӧ�ĸ��ڵ���Ҫ�޸ĵĶ���
			p.second = v; // ���¸��ڵ�Ϊ�µĶ���ָ��
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
			// �����ڽӱ��е�ֵ
			adjList[start] = adjList[start]; // ��ԭ���ļ���Ӧ��ֵ�����µļ�
			adjList.erase(start); // ɾ��ԭ���ļ�
			break; // ����ѭ��
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
	Node* node = new Node(v); // �����½ڵ�
	std::vector<Edge*> list; // ����������
	adjList.insert(std::make_pair(node, list)); // �����ڽӱ���
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::RemoveVertex(VertexType v)
{
	validate(GetIndex(v)); // ��鶥���Ƿ����
	Node* node = findNode(v); // ���ҽڵ�
	if (node == nullptr) return; // ����ڵ㲻���ڣ�����
	adjList.erase(node); // ���ڽӱ���ɾ���ڵ�
	--numNodes;
	for (auto it = adjList.begin(); it != adjList.end(); ++it) {
		for (auto e : it->second) {
			if (e->start == node || e->end == node) { // ����ߵ����(���Ӧ���ǲ������ˣ���Ϊ�������Ѿ�ɾ����)���յ��Ǹýڵ�
				//it->second->remove(e);
				it->second.erase(remove(it->second.begin(), it->second.end(), e), it->second.end()); // ��������ɾ����
				delete e; // �ͷű�
				--numEdges;
			}
		}
	}
	delete node; // �ͷŽڵ�
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::InsertEdge(VertexType v, VertexType u, EdgeType e)
{
	validate(GetIndex(v)); validate(GetIndex(u)); // ��鶥���Ƿ����
	Node* start = findNode(v); // �������
	Node* end = findNode(u); // �����յ�
	if (start == nullptr || end == nullptr) return; // ��������յ㲻���ڣ�����
	Edge* edge = new Edge(start, end, e); // �����±�
	adjList[start].push_back(edge); // ���±߲�������Ӧ��������
	++numEdges;
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::RemoveEdge(VertexType v, VertexType u)
{
	validate(GetIndex(v)); validate(GetIndex(u)); // ��鶥���Ƿ����
	Edge* edge = findEdge(v, u); // ���ұ�
	if (edge == nullptr) return;
	Node* start = findNode(v); // �������
	delete edge; // �ͷű�
	adjList[start].erase(remove(adjList[start].begin(), adjList[start].end(), edge), adjList[start].end()); // ��������ɾ����
	delete start;
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::DFSTraverse()
{
	for (auto v : vexs) // ��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
		if (visited.count(v) == 0)
			DFS(v);
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::BFSTraverse()
{
	for (auto v : vexs) // ��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
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
	// ������ǰ����������ڽӱ�
	for (Edge* e : adjList[v]) {
		Node* u = e->end; // ��ȡ�ڽӱߵ��յ�
		if (visited.count(u) == 0) // ����ڽӵ�δ�����ʹ�����ݹ����
			DFS(u);
	}
}

template <typename VertexType, typename EdgeType>
void ListGraph<VertexType, EdgeType>::DFS_Stack(Node* v)
{
	Stack<Node*> st;
	st.push(v); // ����ʼ������ջ
	visited.insert(v); // �����Ϊ�ѷ���
	while (!st.empty()) {
		Node* u = st.top(); // ����ջ��Ԫ��
		st.pop();
		std::cout << u->data << " "; // ��ӡ��ǰ����
		for (Edge* e : adjList[u]) { // ������ǰ����������ڽӱ�
			Node* w = e->end; // ��ȡ�ڽӱߵ��յ�
			if (visited.count(w) == 0) { // ����ڽӵ�δ�����ʹ�������ջ�����Ϊ�ѷ���
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
		std::cout << u->data << " "; // ��ӡ��ǰ����
		for (Edge* e : adjList[u]) { // ������ǰ����������ڽӱ�
			Node* w = e->end; // ��ȡ�ڽӱߵ��յ�
			if (visited.count(w) == 0) { // ����ڽӵ�δ�����ʹ�������Ӳ����Ϊ�ѷ���
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
		if (it->first->data == v) { // ����ҵ�ƥ������ݣ����ض�Ӧ�Ľڵ�ָ��
			return it->first;
		}
	}
	return nullptr; // ���򷵻ؿ�ָ��
}

template <typename VertexType, typename EdgeType>
typename ListGraph<VertexType, EdgeType>::Edge* ListGraph<VertexType, EdgeType>::findEdge(const VertexType& start,
	const VertexType& goal) const
{
	for (Edge* e : adjList[start])
		if (*e->end == goal) // ����ҵ�ƥ������ݣ����ض�Ӧ�ı�ָ��
			return e;
	return nullptr;  // ���򷵻ؿ�ָ��
}

