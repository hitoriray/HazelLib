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

	// !����ͼ�Ļ�������
	// ����������ͼ���ڽӾ���
	void CreateGraph() override;
	// �ж��Ƿ�����ͨͼ
	inline bool isConnected() override;
	// �ж��Ƿ���ڻ�
	inline bool hasCircle() override;
	// �ж��Ƿ�Ϊ��
	inline bool isTree() override;
	// �ж���������֮���Ƿ���ͨ
	inline bool connected(VertexType v, VertexType u) override; // ���ݶ���
	inline bool connected(int vInd, int uInd) override;			// ��������
	// �ж���������֮���Ƿ��б�
	inline bool hasEdge(VertexType v, VertexType u) override { return hasEdge(GetIndex(v), GetIndex(u)); }
	inline bool hasEdge(int vInd, int uInd) override { return arc[vInd][uInd] != GRAPH_INFINITY; }
	// �ж��Ƿ���ڶ���
	inline bool isExist(VertexType v) override;
	// ���ݶ���ֵѰ�Ҷ�������
	inline int GetIndex(VertexType v) override;
	// ����������ȡ����ֵ
	inline VertexType GetVertex(int ind) override { return vexs[ind]; }
	inline const VertexType& GetVertex(int ind) const override { return vexs[ind]; }
	// �޸Ķ���ֵ
	inline void ModifyVertex(VertexType vertex, VertexType new_value) override;
	inline void ModifyVertex(int vInd, VertexType new_value) override;
	// ��ȡ�������ı�ֵ
	inline EdgeType GetWeight(VertexType v, VertexType u) override;
	inline EdgeType GetWeight(int vInd, int uInd) override;
	// �޸ı�ֵ
	inline void ModifyWeight(VertexType v, VertexType u, EdgeType e) override;
	inline void ModifyWeight(int vInd, int uInd, EdgeType e) override;
	// ���붥��
	inline void InsertVertex(VertexType v) override;
	// ɾ������
	inline void RemoveVertex(VertexType v) override; // ���ݶ���ɾ��
	inline void RemoveVertex(int ind) override;		 // ���ݶ�������ɾ��
	// �����
	inline void InsertEdge(VertexType v, VertexType u, EdgeType e) override;
	inline void InsertEdge(int vInd, int uInd, EdgeType e) override;
	// ɾ����
	inline void RemoveEdge(VertexType v, VertexType u) override; // ���ݶ���
	inline void RemoveEdge(int vInd, int uInd) override;		 // ��������
	// ��ͼ�Զ�ά�������ʽ��ӡ����
	inline void printMatrix();
	// ��ͼ������������ʽ��ӡ����
	inline void printCoord();

	// ��ȡ������
	using UndirectedGraph<VertexType, EdgeType>::GetNumNodes;
	// ��ȡ����
	using UndirectedGraph<VertexType, EdgeType>::GetNumEdges;
	// ��ȡ�����
	inline Vector<VertexType> GetVexs() { return vexs; }
	// ��ȡ�ڽӾ���
	inline Vector<Vector<EdgeType>>& GetArc() { return arc; }

	// !�㷨��
	// �ڽӾ������ȱ�������
	inline void DFSTraverse() override;
	// �ڽӾ���Ĺ�ȱ����㷨
	inline void BFSTraverse() override;
	// Prim �㷨
	inline Vector<VertexType> Prim() override;
	// Kruskal �㷨
	inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Edge> Kruskal() override;
	// Dijkstra �㷨
	inline void Dijkstra(int startInd, Vector<int>& path, Vector<EdgeType>& shortPathTable) override;
	inline void Dijkstra(const VertexType& startVex, Vector<int>& path, Vector<EdgeType>& shortPathTable) override;
	// Floyd�㷨������ͼG�и�����v�����ඥ��w�����·��P[v][w]����Ȩ����D[v][w]��
	inline void Floyd(Vector<Vector<int>>& path, Vector<Vector<EdgeType>>& shortPathTable) override;
	// A*�㷨���޷�ʹ��Hazel::Vector�滻std::vector��
	inline std::vector<VertexType> AStar(const VertexType& start, const VertexType& goal) override;
	// ��ӡ·��
	inline void PrintPath(const Vector<VertexType>& path, const Vector<EdgeType>& shortPathTable = 0);

	// !���������
	MatrixGraph& operator*=(const MatrixGraph& rhs);
	MatrixGraph operator*(const MatrixGraph& rhs);


private:
	inline void Init() override;
	inline void validate(int ind) override; // ֤ʵind�±������Ķ����Ƿ�����ڶ������

	inline void DFS(int startInd) override;


	inline void BFS(int startInd) override;

	// ���������
	inline int CountEdges();

	inline int findTailInd(const Vector<int>& parent, int tailInd) override; // Ѱ��ĩβ����

	inline Vector<VertexType> neighbors(const VertexType& cur) override; // ��ǰ������ھӶ���
	inline EdgeType cost(const VertexType& cur, const VertexType& next) override; // ��ǰ���㵽��һ�����Ȩ��
	inline EdgeType heuristic(const VertexType& a, const VertexType& b); // ���������������a�͵�b֮��������پ��룩

	inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Point> adjToCoord(); // �ڽӾ���ת��Ϊ�������

private:
	Vector<Vector<EdgeType>> arc; // �ڽӾ���
	Vector<Point> coord; // �������
	Vector<bool> visited; // ���ʱ�־������
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
	for (int i = 0; i < numNodes; i++) // ���붥����Ϣ,���������
		std::cin >> vexs[i];
	for (int i = 0; i < numNodes; i++) // �ڽӾ����ʼ������GRAPH_INFINITY����ʾ�������
		for (int j = 0; j < numNodes; j++)
			arc[i][j] = GRAPH_INFINITY;
	std::cout << YELLOW << "[WARNING]" << " If there is no weight, please enter 0.\n" << RESET;
	for (int k = 0; k < numEdges; k++) // ����numEdges���ߣ������ڽӾ���
	{
		std::cout << "Please input vi, vj and the weight on edge(vi, vj)[" << k + 1 << "]:\n";
		VertexType i, j;
		EdgeType w;
		std::cin >> i >> j >> w; // �����(vi,vj)�ϵ�ȨEdgeType
		int ind1 = GetIndex(i), ind2 = GetIndex(j);
		validate(ind1); validate(ind2);
		arc[ind1][ind2] = arc[ind2][ind1] = w;
	}
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::isConnected()
{
	visited = Vector<bool>(numNodes, false); // ��ʼ��visited����
	DFS(0); // �ӵ�һ�����㿪ʼDFS����
	for (int i = 0; i < numNodes; i++) // ����visited���飬����Ƿ����еĶ��㶼�����ʹ�
		if (!visited[i]) return false; // �����δ�����ʹ��Ķ��㣬˵��������ͨͼ������false
	return true; // ���򷵻�true
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
	int count = 0; // ����һ����������¼����Ԫ�صĸ���
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			if (arc[i][j] != GRAPH_INFINITY) { // ������ڱ�
				if (i == j) return false; // ���Ԫ�������Խ����ϣ�˵�����Ի�������false
				if (i < j) count++; // ���Ԫ���������ǲ��֣��ۼӱ���
			}
		}
	}
	if (count == numNodes - 1) return true; // �������Ԫ�صĸ������ڶ�������һ��˵����һ����������true
	return false;
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::connected(VertexType v, VertexType u)
{
	connected(GetIndex(v), GetIndex(u));
	return false; // ���벻��ִ�е����ֻ��Ϊ�������������ľ���
}

template <typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::connected(int vInd, int uInd)
{
	validate(vInd);
	validate(uInd);
	visited = Vector<bool>(numNodes, false); // ��ʼ��visited����
	DFS(vInd); // ��v��ʼDFS����
	if (visited[uInd]) return true;  // ���u�����ʹ���˵��v��u����ͨ������true
	return false; // ���򷵻�false
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
	return GRAPH_INFINITY; // ���벻��ִ�е����ֻ��Ϊ�������������ľ���
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
	arc[vInd][uInd] = arc[uInd][vInd] = e; // ����ͼ����Ҫ������ֵ
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::InsertVertex(VertexType v)
{
	// ���������Ѿ������ڶ�����У������
	if (GetIndex(v) != -1)
		return;
	// v�������ڶ�����У��������
	/* ���¶���� */
	vexs.push_back(v);
	++numNodes;
	/* �����ڽӾ��� */
	arc.push_back(Vector<int>(numNodes, GRAPH_INFINITY)); // ���ڽӾ������һ�к�������һ�У�����GRAPH_INFINITY��ʼ����ֵ
	for (int i = 0; i < numNodes - 1; i++)              // ���ڽӾ�������һ�����ÿһ�е����������һ���ߣ�GRAPH_INFINITY��
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
	/* ���¶���� */
	vexs.erase(vexs.begin() + ind);
	/* �����ڽӾ��� */
	int removedEdges = 0; // ��¼��Ҫɾ�����Ǹ������������ı�
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
	/* �����ڽӾ��� */
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
	coord.clear(); // ��������
	coord = adjToCoord(); // ���ڽӾ���ת��Ϊ�����
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
	visited = Vector<bool>(numNodes, false); // ��ʼ���ж���״̬����δ���ʹ�״̬
	for (int i = 0; i < numNodes; i++) // ��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
		if (!visited[i])
			DFS(i);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::BFSTraverse()
{
	visited = Vector<bool>(numNodes, false); // ��ʼ���ж���״̬����δ���ʹ�״̬
	for (int i = 0; i < numNodes; i++) // ��ÿһ��δ���ʹ��Ķ�����ѭ��
		if (!visited[i])
			BFS(i);
}

template <typename VertexType, typename EdgeType>
inline Vector<VertexType> MatrixGraph<VertexType, EdgeType>::Prim()
{
	Vector<VertexType> vertexs(numNodes); // ������ض��㣨��ѡ���㣩
	Vector<bool> used(numNodes, false); // ��ѡ���㼯
	Vector<int> adj_vex(numNodes); // ������ض����±�
	Vector<EdgeType> low_cost(numEdges, GRAPH_INFINITY); // ������ض����ߵ�Ȩֵ
	low_cost[0] = 0; // ��ʼ����һ��ȨֵΪ0����v0����������
	/* low_cost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� */
	adj_vex[0] = 0; // ��ʼ����һ�������±�Ϊ0
	vertexs[0] = vexs[0]; // ��ʼ����һ������
	for (int i = 1; i < numNodes && arc[0][i] != GRAPH_INFINITY; i++) { // ѭ�����±�Ϊ0�Ⲣ����v0�бߵ�ȫ������
		low_cost[i] = arc[0][i]; // ��v0������֮�бߵ�Ȩֵ��������
		adj_vex[i] = 0; //��ʼ����Ϊv0���±�
		vertexs[i] = vexs[0]; // ��ʼ����Ϊv0��ֵ
	}
	int ind = -1; // ������СȨֵ���±�
	for (int i = 0; i < numNodes; i++) {
		int min = GRAPH_INFINITY; // ��ʼ����СȨֵΪ��
		for (int j = 1; j < numNodes; j++) {
			if (low_cost[j] != 0 && low_cost[j] < min) { // ���Ȩֵ��Ϊ0��ȨֵС��min
				min = low_cost[j]; // ���õ�ǰȨֵ��Ϊ��Сֵ
				ind = j; // ����ǰ��Сֵ���±����ind
			}
		}
		std::cout << "[index]: (" << adj_vex[ind] << ", " << ind << ")\n"; // ��ӡ��ǰ�������Ȩֵ��С�ı�
		std::cout << "[vertex]: (" << vertexs[ind] << "->" << vexs[ind] << ")\n";
		low_cost[ind] = 0; // ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ��������
		for (int j = 1; j < numNodes; j++) {
			if (low_cost[j] != 0 && arc[ind][j] < low_cost[j]) { // ����±�Ϊind�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ
				low_cost[j] = arc[ind][j]; // ����С��Ȩֵ����low_cost��Ӧλ��
				adj_vex[j] = ind; // ���±�Ϊind�Ķ������adj_vex
				vertexs[j] = vexs[ind]; // ���±�Ϊind�Ķ����ֵ����vertexs
			}
		}
	}
	return vertexs;
}

template <typename VertexType, typename EdgeType>
inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Edge> MatrixGraph<VertexType, EdgeType>::Kruskal()
{
	Vector<Edge> edges; // ����߼�����
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
	// ��ӡ��С������
	Vector<int> parent(numNodes, 0); // ����һ���������жϱ�����Ƿ��γɻ�·����ʼ������ֵΪ0
	std::cout << GREEN << "[Kruskal] Print the minimum spanning tree:\n" << RESET;
	for (int i = 0; i < numEdges; i++) {
		const int n = findTailInd(parent, edges[i].beginInd);
		const int m = findTailInd(parent, edges[i].endInd);
		if (n != m) { // ����n��m���ȣ�˵���˱�û�������е��������γɻ�·
			parent[n] = m; // ���˱ߵĽ�β��������±�Ϊ����parent�У���ʾ�˶����Ѿ���������������
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
 * @brief Dijkstra���·��
 *
 * @tparam VertexType
 * @param startInd ��ʼ������±�(start vertex)��������"v(startInd)"��������������·����
 * @param path  path[i]��ֵ��"v(startInd)"��"v(i)"�����·����������ȫ�������У�λ��"v(i)"֮ǰ���Ǹ������±ꡣ
 * @param shortPathTable shortPathTable[i]��"v(startInd)"��"v(i)"�����·���ĳ��ȡ�
 */
template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::Dijkstra(int startInd, Vector<int>& path, Vector<EdgeType>& shortPathTable)
{
	// ����������Ĳ���û�г�ʼ��
	if (path.size() <= numNodes || shortPathTable.size() <= numNodes) {
		path = Vector<int>(numNodes);
		shortPathTable = Vector<EdgeType>(numNodes);
	}
	validate(startInd);
	Vector<bool> final(numNodes, false); // final[i]��ʾ��ö���v(startInd)��v(i)�����·��
	for (int i = 0; i < numNodes; i++) {
		path[i] = -1; // ��ʼ��·�������Ϊ-1
		shortPathTable[i] = arc[startInd][i]; // ����v0�������ߵĶ������Ȩֵ
	}
	shortPathTable[startInd] = 0;// v0��v0·��Ϊ0
	final[startInd] = true; // v0��v0����Ҫ��·��
	int ind;
	/* ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·�� */
	for (int i = 1; i < numNodes; i++) {
		int min = GRAPH_INFINITY; // ��ǰ��֪��v0������������
		for (int j = 0; j < numNodes; j++) { // Ѱ����v0����Ķ���
			if (!final[j] && shortPathTable[j] < min) {
				min = shortPathTable[j]; // v(j)��v0�������
				ind = j; // ��¼v(j)�±�
			}
		}
		final[ind] = true;// ���v(j)Ϊ�Ѿ���ȡ�����·��
		/* ������ǰ���·����ǰ������ */
		for (int j = 0; j < numNodes; j++) {
			/* �����������v(ind)��·������������·���ĳ��ȶ̵Ļ� */
			EdgeType tmp = arc[ind][j] == GRAPH_INFINITY ? GRAPH_INFINITY : min + arc[ind][j]; // ��ֹ���
			if (!final[j] && (tmp < shortPathTable[j])) { // ˵���ҵ��˸��̵�·�����޸�shortPathTable[j]��path[j]
				shortPathTable[j] = tmp; // �޸ĵ�ǰ·������
				path[j] = ind;
			}
		}
	}
	/* ��ӡDijkstra���·���Ľ�� */
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
	// ����������Ĳ���������Ҫ��
	if (path.size() <= numNodes || shortPathTable.size() <= numNodes) {
		path = Vector<Vector<int>>(numNodes, Vector<int>(numNodes));
		shortPathTable = Vector<Vector<EdgeType>>(numNodes, Vector<EdgeType>(numNodes));
	}
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			shortPathTable[i][j] = arc[i][j]; // shortPathTable[i][j]ֵ��Ϊ��Ӧ����Ȩֵ
			path[i][j] = j; // ��ʼ��path
		}
	}
	for (int k = 0; k < numNodes; k++) {
		for (int i = 0; i < numNodes; i++) {
			for (int j = 0; j < numNodes; j++) {
				EdgeType tmp = shortPathTable[i][k] == GRAPH_INFINITY || shortPathTable[k][j] == GRAPH_INFINITY
					? GRAPH_INFINITY
					: shortPathTable[i][k] + shortPathTable[k][j];
				if (shortPathTable[i][j] > tmp) { // ��������±�Ϊk����·����ԭ�����·������
					shortPathTable[i][j] = tmp; // ����ǰ�����Ȩֵ��Ϊ��С��һ��
					path[i][j] = path[i][k]; // ·������Ϊ�����±�Ϊk�Ķ����±�
				}
			}
		}
	}
	/* ��ӡFloyd���·���Ľ�� */
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
		std::greater<std::pair<VertexType, EdgeType>> > frontier; // ����һ�����ȶ��У��洢�ڵ�ʹ���
	frontier.push(std::make_pair(start, 0)); // �����ʹ���0���뵽���ȶ�����
	std::unordered_map<VertexType, VertexType> came_from; // ����һ����ϣ���洢ÿ���ڵ��ǰ��
	std::unordered_map<VertexType, EdgeType> cost_so_far; // ����һ����ϣ���洢����
	came_from[start] = start; // ����ʼ�ڵ��ǰ����Ϊ���Լ�
	cost_so_far[start] = 0; // ����ʼ�ڵ�Ĵ�����Ϊ0
	while (!frontier.empty()) { // �����ȶ��в�Ϊ��ʱ
		auto current = frontier.top(); // ȡ�����ȶ����еĶ��׽ڵ�
		frontier.pop(); // �����׽ڵ����
		if (current.first == goal) break; // �����ǰ�ڵ���Ŀ��ڵ㣬����ǰ����ѭ��
		for (auto next : neighbors(current.first)) { // ������ǰ�ڵ���ھӽڵ�
			EdgeType new_cost = cost_so_far[current.first] + cost(current.first, next); // �������ʼ�ڵ㵽�ھӽڵ���´���
			// error: "contains": ���� "std::unordered_map<VertexType,EdgeType,std::hash<VertexType>,std::equal_to<VertexType>,std::allocator<std::pair<const VertexType,EdgeType>>>" �ĳ�Ա
			// ReSharper disable once CppUseAssociativeContains
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) { // ����ھӽڵ�û�б����ʹ��������µĴ��۸�С
				cost_so_far[next] = new_cost; // �����ھӽڵ�Ĵ���
				EdgeType priority = new_cost + heuristic(goal, next); // �����ھӽڵ�����ȼ�
				frontier.push(std::make_pair(next, priority)); // ���ھӽڵ�����ȼ����뵽���ȶ�����
				came_from[next] = current.first; // �����ھӽڵ��ǰ��
			}
		}
	}
	/* ����came_from��ϣ����Ŀ��ڵ���ݵ���ʼ�ڵ㣬�����һ��·����������洢��path�б��� */
	std::vector<VertexType> path;
	VertexType cur = goal; // ��Ŀ��ڵ㿪ʼ
	while (cur != start) { // ����ǰ�ڵ㲻����ʼ�ڵ�ʱ
		path.push_back(cur); // ����ǰ�ڵ����·��
		cur = came_from[cur]; // ����ǰ�ڵ����Ϊ��ǰ���ڵ�
	}
	path.push_back(start); // ����ʼ�ڵ����·������ѡ��
	std::reverse(path.begin(), path.end()); // ��·����ת����ѡ��
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
	if (this->numNodes == rhs.numNodes) // �������
		*this = *this * rhs;
	return *this; // ���������ˣ��򷵻�����
}

template <typename VertexType, typename EdgeType>
MatrixGraph<VertexType, EdgeType> MatrixGraph<VertexType, EdgeType>::operator*(const MatrixGraph& rhs)
{
	if (this->numNodes != rhs.numNodes) // ���������ͬ�����ܽ������
	{
		std::cout << "The number of vertexes is different. Cannot be multiplied!\n";
		return MatrixGraph();
	}
	// �������
	MatrixGraph<VertexType, EdgeType> result;
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			int sum = 0; // �����������е�Ԫ��ֵ
			for (int k = 0; k < numNodes; k++) // ������һ�������ÿһ�к͵ڶ��������ÿһ��
				sum += this->arc[i][k] * rhs.arc[k][j]; // �ۼӳ˻�
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
	visited[startInd] = true; // ����ǰ������Ϊ�ѷ���
	//std::cout << vexs[startInd] << " "; // ��ӡ���㣨Ҳ����������������
	for (int i = 0; i < numNodes; i++) // ��δ���ʵ��ڽӶ���ݹ����
		if (arc[startInd][i] != GRAPH_INFINITY && !visited[i])
			DFS(i);
}

template <typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::BFS(int startInd)
{
	validate(startInd);
	Queue<int> q;
	visited[startInd] = true; // ���õ�ǰ������ʹ�
	std::cout << vexs[startInd] << " "; // ��ӡ���㣨Ҳ����������������
	q.push(startInd); // ���˶��������
	while (!q.empty()) {
		int ind = q.front(); // ������Ԫ�س��У�����������ֵ��ֵ��ind
		q.pop();
		for (int i = 0; i < numNodes; i++)
			if (arc[ind][i] != GRAPH_INFINITY && !visited[i]) {
				visited[i] = true;
				std::cout << vexs[i] << " "; // ��ӡ���㣨Ҳ����������������
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
	for (int i = 0; i < numNodes && i != ind; i++) // ������ǰ�ڵ���ھӽڵ�
		if (arc[ind][i] != GRAPH_INFINITY) // �����ǰ�ڵ���ھӽڵ�֮���б�
			result.push_back(vexs[i]); // ���ھӽڵ���뵽����б���
	return result;
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::cost(const VertexType& cur, const VertexType& next)
{
	int curInd = GetIndex(cur), nextInd = GetIndex(next);
	validate(curInd);
	validate(nextInd);
	return arc[curInd][nextInd]; // �����ڽӾ����ж�Ӧλ�õ�Ԫ��ֵ
}

template <typename VertexType, typename EdgeType>
inline EdgeType MatrixGraph<VertexType, EdgeType>::heuristic(const VertexType& a, const VertexType& b)
{
	// ����a��b֮��������پ���
	int aInd = GetIndex(a), bInd = GetIndex(b);
	validate(aInd);
	validate(bInd);
	coord.clear();
	coord = adjToCoord(); // ���ڽӾ���ת��Ϊ�������
	Point aCoord = coord[aInd], bCoord = coord[bInd]; // ��ȡa��b������
	return std::abs(aCoord.x - bCoord.x) + std::abs(aCoord.y - bCoord.y); // ���������پ���
}

template <typename VertexType, typename EdgeType>
inline Vector<typename UndirectedGraph<VertexType, EdgeType>::Point> MatrixGraph<VertexType, EdgeType>::adjToCoord()
{
	Vector<Point> coordMatrix(numNodes);
	//��ʼ���������ĵ�һ��Ԫ��Ϊ(0,0)
	coordMatrix[0] = Point(0, 0);
	Queue<int> que; // ����һ�����У����ڹ����������
	visited = Vector<bool>(numNodes, false);
	// ����һ��������ӣ������Ϊ�ѷ���
	que.push(0);
	visited[0] = true;
	while (!que.empty()) {
		int curInd = que.front();
		que.pop();
		// �����ڽӾ���ĵ�ǰ�У��ҵ��뵱ǰ�������ڵĶ���
		for (int i = 0; i < numNodes; i++) {
			//������ڱߣ�����û�з��ʹ�
			if (arc[curInd][i] != GRAPH_INFINITY && !visited[i]) {
				//���ö�����ӣ������Ϊ�ѷ���
				que.push(i);
				visited[i] = true;
				//���ݵ�ǰ���������ͱߵķ��򣬼���ö��������
				//��������ֻ��ˮƽ��ֱ���򣬲��ҳ���Ϊ1
				if (curInd < i) { //����������һ����µ�
					coordMatrix[i].x = coordMatrix[curInd].x + (i - curInd) / numNodes; //����������в�
					coordMatrix[i].y = coordMatrix[curInd].y + (i - curInd) % numNodes; //����������в�
				}
				else { //���������������ϵ�
					coordMatrix[i].x = coordMatrix[curInd].x - (curInd - i) / numNodes; //�������ȥ�в�
					coordMatrix[i].y = coordMatrix[curInd].y - (curInd - i) % numNodes; //�������ȥ�в�
				}
			}
		}
	}
	return coordMatrix;
}

/* ��Ԫ���� */
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
