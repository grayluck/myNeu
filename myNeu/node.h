
#ifndef _NODE_H_
#define _NODE_H_

#include "layer.h"

class Node
{
public:
	Layer* bel;
	Node* conn[];
	Node(Layer* fa);
	void fullConn(Layer nxt);
};

#endif
