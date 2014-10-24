
#include "node.h"

Node::Node(Layer* bel)
{
	this->bel = bel;
	// ans Ϊ-1 ��ʾ�ýڵ㲻���������
	this->ans = -1;
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
		Edge* e = new Edge(this, node);
		out.push_back(e);
		node->in.push_back(e);
	}
}

void Node::addIn(Node* node)
{
	in.push_back(new Edge(node, this));
}
