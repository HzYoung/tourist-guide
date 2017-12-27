#ifndef GRAPH
#define GRAPH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using std::cerr;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::queue;
using std::stack;
const int INF = 2000000000;

struct Vertex {
	int id;
	string name;
	string detail;
	Vertex(){}
	Vertex(int id,string name,string detail):id(id),name(name),detail(detail){}
};
enum RoadType{motor_way,foot_way};
struct Edge {
	int from, to, len;
	string direction;
	RoadType road;
	Edge(){}
	Edge(int from,int to,int len,string dir,RoadType road):from(from),to(to),len(len),direction(dir),road(road){}
};
class graph {
private:
	vector<Vertex> vertexList;
	vector<Edge> edgeList;
	vector<int> firstEdge; //某个点x的第一条弧
	vector<int> nextEdge; //与某条边x同一顶点的下一条弧
public:
	graph();
	/*operation of vertex*/
	// 一开始图为空，需要先调用addVertex添加新景点
	void addVertex(string name, string detail);
	// 用上述候选景点作例子，程序一开始时调用addVertex(“行政楼”, “…”); addVertex(“公共教学楼”, “…”);
	// 之后行政楼对应的id为0，公共教学楼对应的id为1，id每次自加1
	int getVertexIdByName(string name);
	string getVertexNameById(int vertex_id);
	string getDetail(int vertex_id);
	vector<string> showAll(); //返回所有景点的名称列表

	/*operation of edge*/
	void addEdge(int from, int to, int len, string direction, RoadType road);
	//如添加一条从第5个景点到第7个景点的西南方向长度为500米的人行路，调用
	//addEdge(5, 7, 500, “西南”, foot_way)

	vector<Edge> getPath(int start, int end, RoadType road);
	friend istream& operator >> (istream &in, graph &g);
	friend ostream& operator << (ostream &out, const graph &g);
};
#endif // !GRAPH