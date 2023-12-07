#pragma once

#include "Graph.h"
#include "../Vector/Vector.h"
#include <vector> // AStar中的vector替换不了

using Hazel::Vector;

template <typename VertexType, typename EdgeType = int>
class UndirectedGraph : public virtual Graph {
protected:
	struct Edge { // 边：起始点、终止点、权值
		Edge() : beginVex(VertexType()), endVex(VertexType()), beginInd(0), endInd(0), weight(0) {}
		Edge(VertexType beginVex_, VertexType endVex_,
			int beginInd_, int endInd_, EdgeType w)
			: beginVex(beginVex_), endVex(endVex_),
			beginInd(beginInd_), endInd(endInd_), weight(w) {}
		VertexType beginVex, endVex; // 起始顶点和终止顶点
		int beginInd, endInd; // 起始顶点和终止顶点的下标索引
		EdgeType weight; // 边上的权值
	};
	struct Point { // 点：坐标
		Point() = default;
		Point(int x_, int y_) : x(x_), y(y_) {}
		int x, y;
	};

	Vector<VertexType> vexs; // 顶点表

public:
	UndirectedGraph() = default;
	UndirectedGraph(const Vector<VertexType>& vexs_, int numNodes_, int numEdges_)
		: Graph(numNodes_, numEdges_), vexs(vexs_) {}
	UndirectedGraph(int numNodes_, int numEdges_)
		: Graph(numNodes_, numEdges_) {}
	UndirectedGraph(const UndirectedGraph& rhs) = default;
	UndirectedGraph& operator=(const UndirectedGraph& rhs) = default;
	UndirectedGraph(UndirectedGraph&& rhs) noexcept = default;
	UndirectedGraph& operator=(UndirectedGraph&& rhs) noexcept = default;
	~UndirectedGraph() override {}

	virtual Vector<VertexType> GetVertexTable() { return vexs; }

	virtual void CreateGraph() = 0;
	virtual bool isConnected() = 0;
	virtual bool isTree() = 0;
	virtual bool hasCircle() = 0;
	virtual bool connected(VertexType v, VertexType u) = 0;
	virtual bool connected(int vInd, int uInd) = 0;
	virtual bool hasEdge(VertexType v, VertexType u) = 0;
	virtual bool hasEdge(int vInd, int uInd) = 0;
	virtual bool isExist(VertexType v) = 0;
	virtual int GetIndex(VertexType v) = 0;
	virtual VertexType GetVertex(int ind) = 0;
	virtual const VertexType& GetVertex(int ind) const = 0;
	virtual void ModifyVertex(VertexType vertex, VertexType new_value) = 0;
	virtual void ModifyVertex(int vInd, VertexType new_value) = 0;
	virtual EdgeType GetWeight(VertexType v, VertexType u) = 0;
	virtual EdgeType GetWeight(int vInd, int uInd) = 0;
	virtual void ModifyWeight(VertexType v, VertexType u, EdgeType e) = 0;
	virtual void ModifyWeight(int vInd, int uInd, EdgeType e) = 0;
	virtual void InsertVertex(VertexType v) = 0;
	virtual void RemoveVertex(VertexType v) = 0;
	virtual void RemoveVertex(int ind) = 0;
	virtual void InsertEdge(VertexType v, VertexType u, EdgeType e) = 0;
	virtual void InsertEdge(int vInd, int uInd, EdgeType e) = 0;
	virtual void RemoveEdge(VertexType v, VertexType u) = 0;
	virtual void RemoveEdge(int vInd, int uInd) = 0;

	// 算法：
	virtual void DFSTraverse() = 0;
	virtual void BFSTraverse() = 0;
	virtual Vector<VertexType> Prim() = 0;
	virtual Vector<Edge> Kruskal() = 0;
	virtual void Dijkstra(const VertexType& startVex, Vector<int>& path, Vector<EdgeType>& shortPathTable) = 0;
	virtual void Dijkstra(int startInd, Vector<int>& path, Vector<EdgeType>& shortPathTable) = 0;
	virtual void Floyd(Vector<Vector<int>>& path, Vector<Vector<EdgeType>>& shortPathTable) = 0;
	virtual std::vector<VertexType> AStar(const VertexType& start, const VertexType& goal) = 0;

private:
	virtual void Init() = 0;
	virtual void validate(int ind) = 0; // 证实ind下标索引的顶点是否存在于顶点表中
	virtual void DFS(int startInd) = 0;
	virtual void BFS(int startInd) = 0;
	virtual int findTailInd(const Vector<int>& parent, int tailInd) = 0; // 寻找末尾顶点
	virtual Vector<VertexType> neighbors(const VertexType& cur) = 0; // 当前顶点的邻居顶点
	virtual EdgeType cost(const VertexType& cur, const VertexType& next) = 0; // 当前顶点到下一个顶点的权重
};