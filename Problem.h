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
        string s;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += to_string(n.state[i][j]);
            }
        }

        visited[s] = true;
   }

   bool isVisited(Node n) {
     string s;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += to_string(n.state[i][j]);
            }
        }

    return (visited.find(s) != visited.end());
   }


   //member variables
   Node initialState;
   unordered_map<string, bool> visited; 
};


#endif