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
	vector<int> firstEdge; //ĳ����x�ĵ�һ����
	vector<int> nextEdge; //��ĳ����xͬһ�������һ����
public:
	graph();
	/*operation of vertex*/
	// һ��ʼͼΪ�գ���Ҫ�ȵ���addVertex����¾���
	void addVertex(string name, string detail);
	// ��������ѡ���������ӣ�����һ��ʼʱ����addVertex(������¥��, ������); addVertex(��������ѧ¥��, ������);
	// ֮������¥��Ӧ��idΪ0��������ѧ¥��Ӧ��idΪ1��idÿ���Լ�1
	int getVertexIdByName(string name);
	string getVertexNameById(int vertex_id);
	string getDetail(int vertex_id);
	vector<string> showAll(); //�������о���������б�

	/*operation of edge*/
	void addEdge(int from, int to, int len, string direction, RoadType road);
	//�����һ���ӵ�5�����㵽��7����������Ϸ��򳤶�Ϊ500�׵�����·������
	//addEdge(5, 7, 500, �����ϡ�, foot_way)

	vector<Edge> getPath(int start, int end, RoadType road);
	friend istream& operator >> (istream &in, graph &g);
	friend ostream& operator << (ostream &out, const graph &g);
};
#endif // !GRAPH
