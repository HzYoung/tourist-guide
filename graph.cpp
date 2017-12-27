#include "graph.hpp"

graph::graph() = default;
void graph::addVertex(string name, string detail) {
	Vertex v(vertexList.size(),name,detail);
	vertexList.push_back(v);
	firstEdge.push_back(-1);
}
int graph::getVertexIdByName(string name) {
	for (auto v : vertexList) {
		if (v.name == name) return v.id;
	}
	cerr << "can't find a vertex named" << name << endl;
	return 0;
}
string graph::getVertexNameById(int vertex_id) {
	if (vertex_id < 0 || vertex_id >= vertexList.size()) {
		cerr << vertex_id << "is invalid vertex id" << endl;
		return "";
	}
	return vertexList[vertex_id].name;
}
string graph::getDetail(int vertex_id) {
	if (vertex_id < 0 || vertex_id >= vertexList.size()) {
		cerr << vertex_id << "is invalid vertex id" << endl;
		return "";
	}
	return vertexList[vertex_id].detail;
}
vector<string> graph::showAll() {
	vector<string> list;
	for (auto v : vertexList) list.push_back(v.name);
	return list;
}

void graph::addEdge(int from, int to, int len, string direction, RoadType road) {
	Edge e(from, to, len, direction, road);
	edgeList.push_back(e);
	nextEdge.push_back(-1);
	nextEdge[firstEdge[from]] = edgeList.size() - 1;
	firstEdge[from] = edgeList.size() - 1;
}
//如添加一条从第5个景点到第7个景点的西南方向长度为500米的人行路，调用
//addEdge(5, 7, 500, “西南”, foot_way)

vector<Edge> graph::getPath(int start, int end, RoadType road) {
	queue <int> Q;
	vector<int> pre; // 记录  经由哪一条边到达x点
	int *dis = new int[vertexList.size()];
	int *vis = new int[vertexList.size()];
	for (int i = 0; i < vertexList.size(); ++i) dis[i] = INF, vis[i] = 0;
	dis[start] = 0; Q.push(start); vis[start] = 1;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); vis[u] = 0;
		for (int t = firstEdge[u]; t != -1; t = nextEdge[t]) {
			int l = dis[u] + edgeList[t].len;
			if (dis[edgeList[t].to] > l) {
				dis[edgeList[t].to] = l;
				pre[edgeList[t].to] = t;
				if (!vis[edgeList[t].to] && edgeList[t].to != end) {
					vis[edgeList[t].to] = 1;
					Q.push(edgeList[t].to);
				}
			}
		}
	}
	
	//get path
	stack<int> st;
	int tp = end;
	while (tp != start) {
		st.push(pre[tp]);
		tp = edgeList[pre[tp]].from;
	}
	vector <Edge> res;
	while (!st.empty()) {
		res.push_back(edgeList[st.top()]);
		st.pop();
	}
	return res;
}
istream& operator >> (istream &in, graph &g) {
	int n;
	in >> n;
	while(n--) {
		int id; string name, detail;
		in >> id >> name >> detail;
		Vertex v(id, name, detail);
		g.vertexList.push_back(v);
	}

	in >> n;
	while(n--) {
		int from, to, len; string dir; int road;
		in >> from >> to >> len >> dir >> road;
		Edge e(from, to, len, dir, RoadType(road));
		g.edgeList.push_back(e);
	}

	in >> n;
	while (n--) {
		int t;
		in >> t;
		g.firstEdge.push_back(t);
	}

	in >> n;
	while (n--) {
		int t;
		in >> t;
		g.nextEdge.push_back(t);
	}
	return in;
}


ostream& operator << (ostream &out, const graph &g) {
	out << g.vertexList.size() << endl;
	for (auto v : g.vertexList) {
		out << v.id << " " << v.name << " " << v.detail << endl;
	}
	
	out << g.edgeList.size() << endl;
	for (auto e : g.edgeList) {
		out << e.from << " " << e.to << " " << e.len << endl;
		out << e.direction << " " << e.road<<endl;
	}

	out << g.firstEdge.size() << endl;
	for (auto e : g.firstEdge) {
		out << e <<" ";
	}
	out << endl;

	out << g.nextEdge.size() << endl;
	for (auto e : g.nextEdge) {
		out << e << " ";
	}
	out << endl;

	return out;
}