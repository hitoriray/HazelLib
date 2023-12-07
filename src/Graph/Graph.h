#pragma once

#include "../Log/Log.h"

class Graph {
public:
	Graph() : numNodes(0), numEdges(0) {}
	Graph(int numNodes_, int numEdges_)
		: numNodes(numNodes_), numEdges(numEdges_) {}
	Graph(const Graph& rhs) = default;
	Graph& operator=(const Graph& rhs) = default;
	Graph(Graph&& rhs) noexcept = default;
	Graph& operator=(Graph&& rhs) noexcept = default;
	virtual ~Graph() = default;

	virtual int GetNumNodes() const { return numNodes; }
	virtual int GetNumEdges() const { return numEdges; }

protected:
	int numNodes, numEdges; // 顶点数和边数
};