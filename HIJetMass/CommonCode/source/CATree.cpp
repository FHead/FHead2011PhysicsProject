#include <algorithm>

#include "include/CATree.h"

Node::Node()
   : P(0, 0, 0, 0), Child1(NULL), Child2(NULL), Parent(NULL), N(1)
{
}
   
Node::Node(FourVector &p)
   : P(p), Child1(NULL), Child2(NULL), Parent(NULL), N(1)
{
}

Node::Node(Node *n1, Node *n2)
   : P(0, 0, 0, 0), Child1(NULL), Child2(NULL), Parent(NULL), N(1)
{
   if(n1 == NULL || n2 == NULL)
      return;

   P = n1->P + n2->P;
   Child1 = n1;
   Child2 = n2;
   Child1->Parent = this;
   Child2->Parent = this;
   N = n1->N + n2->N + 1;

   if(Child1->P.GetPT() < Child2->P.GetPT())
      std::swap(Child1, Child2);
}

Node::~Node()
{
   if(Child1 != NULL)   delete Child1;
   if(Child2 != NULL)   delete Child2;

   Child1 = NULL;
   Child2 = NULL;
}

void BuildCATree(std::vector<Node *> &Nodes)
{
   while(Nodes.size() > 1)
   {
      int IndexL = 0, IndexR = 1;
      double BestDistance = -1;

      for(int i = 0; i < (int)Nodes.size() - 1; i++)
      {
         for(int j = i + 1; j < (int)Nodes.size(); j++)
         {
            double Distance = GetDR(Nodes[i]->P, Nodes[j]->P);

            if(Distance < BestDistance || BestDistance < 0)
            {
               IndexL = i;
               IndexR = j;
               BestDistance = Distance;
            }
         }
      }

      if(IndexR < IndexL)   // just in case
         std::swap(IndexL, IndexR);

      // Now make a new node
      Node *NewNode = new Node(Nodes[IndexL], Nodes[IndexR]);
      Nodes[IndexL] = NewNode;
      Nodes.erase(Nodes.begin() + IndexR);
   }
}


