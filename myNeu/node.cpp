
#include "node.h"

Node::Node(Layer* bel)
{
	this->bel = bel;
}

Edge::Edge(Node* st, Node* en)
{
	this->st = st;
	this->en = en;
	w = (float)rand() / RAND_MAX / 100.0;
}

void Node::fullConn(Layer* nxt)
{
	for(int i = 0; i < nxt->node.size(); ++i)
	{
		Node* node = nxt->node[i];
		out.push_back(new Edge(this, node));
		node->in.push_back(new Edge(node, this));
	}
}

void Node::addIn(Node* node)
{
	in.push_back(new Edge(node, this));
}
