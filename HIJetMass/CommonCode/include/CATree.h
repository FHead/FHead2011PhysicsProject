#include <vector>

#include "Code/TauHelperFunctions2.h"

class Node;
void BuildCATree(std::vector<Node *> &Nodes);

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


