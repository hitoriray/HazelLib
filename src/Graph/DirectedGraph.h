#pragma once

#include "Graph.h"
#include "../Vector/Vector.h"

using Hazel::Vector;

template <typename VertexType, typename EdgeType = int>
class DirectedGraph : public virtual Graph {
protected:
	struct Edge { // �ߣ���ʼ�㡢��ֹ�㡢Ȩֵ
		VertexType beginVex, endVex; // ��ʼ�������ֹ����
		int beginInd, endInd; // ��ʼ�������ֹ������±�����
		EdgeType weight; // ���ϵ�Ȩֵ

		Edge() : beginVex(VertexType()), endVex(VertexType()), beginInd(0), endInd(0), weight(0) {}
		Edge(VertexType beginVex_, VertexType endVex_,
			int beginInd_, int endInd_, EdgeType w)
			: beginVex(beginVex_), endVex(endVex_),
			beginInd(beginInd_), endInd(endInd_), weight(w) {}
	};

	Vector<VertexType> vexs; // �����

public:
	DirectedGraph() = default;
	DirectedGraph(const Vector<VertexType>& vexs_, int numNodes_, int numEdges_)
		: Graph(numNodes_, numEdges_), vexs(vexs_) {}
	DirectedGraph(int numNodes_, int numEdges_)
		: Graph(numNodes_, numEdges_) {}
	DirectedGraph(const DirectedGraph& rhs) = default;
	DirectedGraph& operator=(const DirectedGraph& rhs) = default;
	DirectedGraph(DirectedGraph&& rhs) noexcept = default;
	DirectedGraph& operator=(DirectedGraph&& rhs) noexcept = default;
	~DirectedGraph() override {}

	virtual Vector<VertexType> GetVertexTable() { return vexs; }

	virtual void CreateGraph() = 0;
	virtual bool isConnected() = 0;
	virtual bool isTree() = 0;
	virtual bool hasCircle() = 0;
	virtual bool connected(VertexType v, VertexType u) = 0;
	virtual bool hasEdge(VertexType v, VertexType u) = 0;
	virtual bool isExist(VertexType v) = 0;
	virtual int GetIndex(VertexType v) = 0;
	virtual void ModifyVertex(VertexType vertex, VertexType new_value) = 0;
	virtual EdgeType GetWeight(VertexType v, VertexType u) = 0;
	virtual void ModifyWeight(VertexType v, VertexType u, EdgeType e) = 0;
	virtual void InsertVertex(VertexType v) = 0;
	virtual void RemoveVertex(VertexType v) = 0;
	virtual void InsertEdge(VertexType v, VertexType u, EdgeType e) = 0;
	virtual void RemoveEdge(VertexType v, VertexType u) = 0;

	// �㷨��
	virtual void DFSTraverse() = 0;
	virtual void BFSTraverse() = 0;
	virtual Vector<VertexType>& Prim() = 0;
	//virtual Vector<Edge> Kruskal() = 0;
	virtual void Dijkstra(const VertexType& startVex, Vector<int>& path, Vector<EdgeType>& shortPathTable) = 0;
	virtual void Floyd(Vector<Vector<int>>& path, Vector<Vector<EdgeType>>& shortPathTable) = 0;
	//virtual std::vector<VertexType> AStar(const VertexType& start, const VertexType& goal) = 0;

private:
	virtual void Init() = 0;
	virtual void validate(int ind) = 0;
	//virtual void DFS(int startInd) = 0;
	//virtual void BFS(int startInd) = 0;
	virtual int findTailInd(const Vector<int>& parent, int tailInd) = 0; // Ѱ��ĩβ����
	virtual Vector<VertexType> neighbors(const VertexType& cur) = 0; // ��ǰ������ھӶ���
	virtual EdgeType cost(const VertexType& cur, const VertexType& next) = 0; // ��ǰ���㵽��һ�������Ȩ��
};