#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<unordered_set>
#include<time.h>
#include<array>
#include<functional>
#include<unordered_map>
using namespace std;


typedef pair<double, double> Point;

vector<array<int, 3>> calculateDistance(vector<Point> Points){
	vector<array<int, 3>> res;
	res.reserve(Points.size());
	for (int i = 0; i < Points.size(); ++i) {
		for (int j = 0; j < Points.size(); ++j) {
			res.push_back({ i, j, sqrt(Points[i].first * Points[j].first - Points[i].second * Points[j].second) });
		}
	}
	return res;
}



class MTS {
	size_t vertices;

	vector<array<int, 3>> input_graph;

	vector<set<pair<int, int>>> adj;
	vector<vector<int>> adjMatrix;
	vector<array<int, 3>> result;
	vector<int> father;

	bool is_MTS_completed = false;

	unordered_map<pair<int, int>*, int> weight;
public:
	MTS(size_t size, vector<array<int, 3>> input) {
		input_graph = vector<array<int, 3>>(input);
		vertices = size;
		adj = vector<set<pair<int, int>>>(size);
		//make graph
		for (auto& edge : input) {

			adj[edge[0]].insert({ edge[1], edge[2] });
			adj[edge[1]].insert({ edge[0], edge[2] });
		}
	}
	// Time complexity: O((V+E)logV)
	void Prim() {
		auto cmp = [](auto& a, auto& b) {return a[2] > b[2];  };
		priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(cmp)> Heap(cmp);
		vector<bool> visited(vertices, false);
		// initialize for the first node
		for (auto& node : adj[0]) {

			Heap.push({ 0, node.first, node.second });
			adj[node.first].erase({ 0, node.second });
		}
		// top[0] is the current node poped from heap
		// top[1] is the node that connects to top[0]
		// top[2] is the weigh
		for (int i = 1; i < vertices; ++i) {
			// get rid of unqualified edge.
			while (!Heap.empty() && visited[Heap.top()[1]]) Heap.pop();
			//get the smallest edge
	
			auto top = Heap.top();
			Heap.pop();
			//printf("%d, %d, %d\n", top[0], top[1], top[2]);
			visited[top[1]] = true;
			result.push_back(top);
			//adj[top[1]].erase({ top[0], top[2] });
			
			for (auto& edge : adj[top[1]]) {
				Heap.push({ top[1], edge.first, edge.second });
			}
		}
		is_MTS_completed = true;
	}
	
	vector<vector<int>> cluster(double threhold) {
		if (!is_MTS_completed) return {};
		
	}

	void printResult() {
		int sum = 0;
		for (auto& e : result) {
			sum += e[2];
			printf("{%d, %d, %d}\n", e[0], e[1], e[2]);
		}
		printf("total sum = %d\n", sum);
	}
};




void test1() {
	vector<array<int, 3>> test = { { 0,1,7 },{ 1,2,8 },{ 0,3,5 },{ 1,3,9 },{ 1,4,7 },
	{ 3,4,15 },{ 3,5,6 },{ 4,5,8 },{ 6,4,9 },{ 5,6,11 },{ 2,4,5 } };
	MTS newTree(7, test);
	newTree.Prim();
	newTree.printResult();
}
void test2() {
	int adjMatrix[9][9] = {
		{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 10, 0, 0, 0, 0 },
	{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};
	vector<array<int, 3>> test;
	
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < i; ++j) {
			if (adjMatrix[i][j] != 0) {
				test.push_back({ i, j, adjMatrix[i][j] });
			}
		}
	}
	MTS newTree(9, test);
	newTree.Prim();
	newTree.printResult();
}

void test3() {
	vector<array<int, 3>> test = { {0, 1, 10}, { 1,3,15 }, { 2,3,4 }, {0,3,5} };
	MTS newTree(4, test);
 	newTree.Prim();
	newTree.printResult();
}


int main() {
	clock_t startTime, endTime;

	startTime = clock();
	test1();
	printf("\n");

	test2();

	printf("\n");
	test3();
	endTime = clock();

	printf("Totle Time : %f s", (double)(endTime - startTime) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}