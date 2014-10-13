
#ifndef _NODE_H_
#define _NODE_H_

class Node;

#include "layer.h"
#include <vector>

using namespace std;

class Edge
{
public:
	Node* st, * en;
	double w;
	Edge(Node* st, Node* en);
};

class Node
{
public:
	Layer* bel;
	vector<Edge*> in;
	vector<Edge*> out;
	Node(Layer* fa);
	void fullConn(Layer* nxt);
	void addIn(Node* node);
	double y, delta, ans;
};

#endif
