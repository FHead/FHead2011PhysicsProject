#include <vector>

#include "Code/TauHelperFunctions2.h"

class Node;
void BuildCATree(std::vector<Node *> &Nodes);
Node *FindSDNode(Node *HeadNode, double ZCut = 0.1, double Beta = 0, double R0 = 0.4);

class Node
{
public:
   FourVector P;
   Node *Child1;
   Node *Child2;
   Node *Parent;
   int N;   // multiplicity: how many nodes (including self) under this node
public:
   Node();
   Node(FourVector &p);
   Node(Node *n1, Node *n2);
   ~Node();
};


