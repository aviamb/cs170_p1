#ifndef PROBLEM_H
#define PROBLEM_H

#include "Node.h"

struct Problem {
   //Problem constructors
   Problem() {
       initialState = Node();
   }
   Problem(int r1[3], int r2[3], int r3[3]) {
       initialState = Node(r1,r2,r3,0);


   };


   //functions
   const bool goalTest(Node n) {
       int g1[3] = {1,2,3};
       int g2[3] = {4,5,6};
       int g3[3] = {7,8,0};
      
       Node goal = Node(g1,g2,g3,0);
       return (n == goal);
   };
   void visit(Node n) {
       // string hash;
       // for (int i = 0; i < 3; i++) {
       //     for (int j = 0; j < 3; j++) {
       //         if (n.state[i][j] != 0) hash += to_string(n.state[i][j]);
       //     }
       // }
       // hash = to_integer(hash) % 29;


       visited.push_back(n);
   }
   bool isVisited(Node n) {
       for (int i = 0; i < visited.size(); i++) {
           if (n == visited.at(i)) return true;
       }
       return false;
   }


   //member variables
   Node initialState;
   vector<Node> visited;
   //vector<pair<int,int>> operators = {{-1,0},{0,-1},{1,0},{0,1}};
};


#endif