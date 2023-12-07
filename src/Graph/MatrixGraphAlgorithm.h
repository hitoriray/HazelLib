#pragma once

//#include "MatrixGraph.h"


#include "../Vector/Vector.h"

#define GRAPH_INFINITY INT_MAX

template <typename VertexType, typename EdgeType = int>
class MatrixGraph;

namespace Hazel
{
	template <typename VertexType, typename EdgeType = int>
	Vector<VertexType> Prim(const MatrixGraph<VertexType, EdgeType>& matrix)
	{
		int numNodes = matrix.GetNumNodes();
		int numEdges = matrix.GetEdges();
		auto& vexs = matrix.GetVexs();
		auto& arc = matrix.GetArc();
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

}