#ifndef UI_HPP
#define UI_HPP

#include<iostream>
#include<string>
#include<fstream>
#include "graph.hpp"
using namespace std;





/*保存信息*/
void save();


void addVertex();
void addEdge();
int getNumber(int min, int max);
bool init();
void printTitle();
bool checkLessNumber(string str, int min, int max);
void queryVertex();
void getPath();
void modifyGraph();
void showAllVertex();
#endif // !UI_HPP