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

}