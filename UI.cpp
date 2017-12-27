#include "UI.hpp"

graph grh;


void printTitle() {
	for (int i = 0; i < 20; ++i) cout << "-";
	cout << "中山大学东校区景点游览";
	for (int i = 0; i < 20; ++i) cout << "-";
	cout << endl;
}

void save() {
    ofstream OUT("graph.txt", ios::out);
    OUT << grh;
}

bool init() {
    printTitle();
	cout << "[1]  查阅景点信息" << endl
		 << "[2]  景点问路查询" << endl
		 << "[3]  修改地图（需要管理员权限）" << endl
         << "[4]  退出程序" << endl;
	int opt = getNumber(1, 4);
	switch (opt)
	{
	case 1:queryVertex(); break;
	case 2:getPath(); break;
    case 3:modifyGraph(); break;
	case 4: save(); return false;
	default:
		break;
	}
	return true;
}


void modifyGraph() {
    printTitle();
    for (;;) {
        cout << "[1]  修建景点" << endl
		 << "[2]  修路" << endl
		 << "[3]  返回" << endl;
	    int opt = getNumber(1, 3);
        switch (opt) {
            case 1: addVertex(); break;
            case 2: addEdge(); break;
            case 3: return;
        }
    }
}


void addVertex() {
    int n = grh.showAll().size();
    cout << "当前景点总数：" << n << endl;
    cout << "请输入新景点名:" << endl;
    string name;
    cin >> name;
    string detail;
    cout << "请输入景点描述:" << endl;
    cin >> detail; 
    grh.addVertex(name, detail);
    cout << "新景点 " << name << " 获得代号: " << n << endl; 
}

void addEdge() {
    showAllVertex();
    int n = grh.showAll().size();
    cout << "请输入起点的代号。" << endl;
    int start = getNumber(0, n - 1);
    cout << "请输入终点的代号。" << endl;
    int end = getNumber(0, n - 1);
    if (start == end) {
        cout << "起点与终点相同！" << endl;
        return;
    }

    cout << "请输入距离。" << endl;
    int dist = getNumber(1, 10000);
    cout << "请输入方向。" << endl;
    string direction;
    cin >> direction;
    cout << "请选择出行方式" << endl;
    cout << "[0] 开车" << endl;
    cout << "[1] 步行" << endl;
    cout << "[2] 两者皆可" << endl;
    int road = getNumber(0, 2);
    if (road != 2) grh.addEdge(start, end, dist, direction, RoadType(road));
    else {
        grh.addEdge(start, end, dist, direction, RoadType(0));
        grh.addEdge(start, end, dist, direction, RoadType(1));
    }
}
void showAllVertex() {
    vector<string> names = grh.showAll();
    cout << endl << "景点列表:" << endl;
    for (int i = 0; i < names.size(); i++) {
        cout << "[" << i << "] " << names[i] << endl;
    }
    cout << endl;
}


void queryVertex() {
    showAllVertex();
    if (grh.showAll().empty()) {
        cout << "地图为空！" << endl;
        return;
    }
    cout << "请输入你要查询的景点的代号进行查询。" << endl;
    int v = getNumber(0, grh.showAll().size() - 1);
    cout << grh.getDetail(v) << endl;
}

void getPath() {
    showAllVertex();
    if (grh.showAll().empty()) {
        cout << "地图为空！" << endl;
        return;
    }
    int n = grh.showAll().size();
    cout << "请输入起点的代号。" << endl;
    int start = getNumber(0, n - 1);
    cout << "请输入终点的代号。" << endl;
    int end = getNumber(0, n - 1);
    if (start == end) {
        cout << "起点与终点相同！" << endl;
        return;
    }
    cout << "请选择出行方式" << endl;
    cout << "[0] 开车" << endl;
    cout << "[1] 步行" << endl;
    int road = getNumber(0, 1);
    vector<Edge> edges = grh.getPath(start, end, RoadType(road));
    for (int i = 0; i < edges.size(); i++) {
        Edge edge = edges[i];
        cout << "从 " << grh.getVertexNameById(edge.from) << " 沿" << edge.direction 
             << "方向 " << (road ? "行走" : "行驶") << edge.len << "米到达 " 
             << grh.getVertexNameById(edge.to)  << endl;
    }
}

int getNumber(int min, int max) {
	string opt;
	cout << "请输入" << min << "-" << max << "的数字" << endl;
	cin >> opt;
	while (!checkLessNumber(opt, min, max)) {
		cout << "输入错误！请输入" << min << "-" << max << "的数字" << endl;
		cin >> opt;
	}
	int num = 0;
	for (int i = 0; i < opt.size(); ++i) {
		num = num * 10 + opt[i] - '0';
	}
	return num;
}

bool checkLessNumber(string str, int min, int max) {
	int len = 0, tp = max;
	while (tp > 0) ++len, tp /= 10;
	if (str.size() > len) return false;
	int num = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i])) return false;
		num = num * 10 + str[i] - '0';
	}
	if (num <= max && num >= min) return true;
	else return false;
}