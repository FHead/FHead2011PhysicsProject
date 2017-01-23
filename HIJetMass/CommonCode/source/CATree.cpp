#include <algorithm>
#include <cmath>
#include <iostream>

#include "include/CATree.h"

#include "include/BasicUtilities.h"

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
   std::vector<double> NodesEta(Nodes.size());
   std::vector<double> NodesPhi(Nodes.size());

   for(int i = 0; i < (int)Nodes.size(); i++)
   {
      NodesEta[i] = Nodes[i]->P.GetEta();
      NodesPhi[i] = Nodes[i]->P.GetPhi();
   }

   while(Nodes.size() > 1)
   {
      int IndexL = 0, IndexR = 1;
      double BestDistance = -1;

      for(int i = 0; i < (int)Nodes.size() - 1; i++)
      {
         for(int j = i + 1; j < (int)Nodes.size(); j++)
         {
            double Distance = GetDR2(NodesEta[i], NodesPhi[i], NodesEta[j], NodesPhi[j]);

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

      NodesEta[IndexL] = NewNode->P.GetEta();
      NodesPhi[IndexL] = NewNode->P.GetPhi();

      NodesEta.erase(NodesEta.begin() + IndexR);
      NodesPhi.erase(NodesPhi.begin() + IndexR);
   }
}

Node *FindSDNode(Node *HeadNode, double ZCut, double Beta, double R0)
{
   if(HeadNode == NULL)
      return NULL;

   bool Done = false;
   Node *Current = HeadNode;

   while(Done == false)
   {
      if(Current->N == 1)
         Done = true;
      else if(Current->N == 2)
      {
         // WTF!
         std::cerr << "Error!  N = " << Current->N << "!" << std::endl;
      }
      else if(Current->Child1 == NULL || Current->Child2 == NULL)
      {
         // WTF!
         std::cerr << "Error!  Child NULL while N = " << Current->N << "!" << std::endl;
      }
      else
      {
         double PT1 = Current->Child1->P.GetPT();
         double PT2 = Current->Child2->P.GetPT();
         double PTRatio = std::min(PT1, PT2) / (PT1 + PT2);

         double DR = GetDR(Current->Child1->P, Current->Child2->P);

         double Threshold = ZCut * std::pow(DR / R0, Beta);

         if(PTRatio > Threshold)
            Done = true;
         else
         {
            if(PT1 > PT2)
               Current = Current->Child1;
            else
               Current = Current->Child2;
         }
      }
   }

   return Current;
}

