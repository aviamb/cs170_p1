#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
   //Node constructors
   Node() {
       for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
               state[i][j] = 0;
           }
       }
       depth = 0;
   };
   Node(int r1[3], int r2[3], int r3[3], int d) {
       for (int i = 0; i < 3; i++) {
           state[0][i] = r1[i];
           state[1][i] = r2[i];
           state[2][i] = r3[i];
       }
       depth = d;
   };


   //operators
   Node& operator=(const Node rhs) {
       for (int i = 0; i < 3; i++) {
           state[0][i] = rhs.state[0][i];
           state[1][i] = rhs.state[1][i];
           state[2][i] = rhs.state[2][i];
       }

       depth = rhs.depth;
       cost = rhs.cost;

       return *this;
   }
   bool operator==(const Node& rhs) {
       for (int i = 0; i < 3; i++) {
           if (state[0][i] != rhs.state[0][i] || state[1][i] != rhs.state[1][i] || state[2][i] != rhs.state[2][i]) {
               return false;
           }
       }
       return true;
   }
   // bool operator<(const Node& rhs) {
   //     return cost < rhs.cost;
   // }


   //functions
   const bool move (int direction) {
       pair<int,int> pos = {0,0};
      
       for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
               if (state[i][j] == 0) {pos = {i,j}; break;} //note this is j,i cause axes are messed up!!!!!!!!!!!!!!!!!!!!!!!!! might cause problems with other stuff
           }
       }
      
       if (direction == 0) { //move left
           if (pos.first < 2) {return true;}
       }
       else if (direction == 1) { //move down
           if (pos.second > 0) {return true;}
       }
       else if (direction == 2) { //move right
           if (pos.first > 0) {return true;}
       }
       else { //move up
           if (pos.second < 2) {return true;}
       }
       return false;
   }
   void transform(int direction) {
       pair<int,int> pos = {0,0};
      
       for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
               if (state[i][j] == 0) {pos = {i,j}; break;}
           }
       }
      
       if (direction == 0) { //move left
           int temp = state[pos.first + 1][pos.second];
           state[pos.first+1][pos.second] = 0;
           state[pos.first][pos.second] = temp;
       }
       else if (direction == 1) { //move down
           int temp = state[pos.first][pos.second-1];
           state[pos.first][pos.second-1] = 0;
           state[pos.first][pos.second] = temp;
       }
       else if (direction == 2) { //move right
           int temp = state[pos.first-1][pos.second];
           state[pos.first-1][pos.second] = 0;
           state[pos.first][pos.second] = temp;
       }
       else { //move up
           int temp = state[pos.first][pos.second+1];
           state[pos.first][pos.second+1] = 0;
           state[pos.first][pos.second] = temp;
       }
       return;
   }
   void print(){
       for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
               cout << state[i][j] << " ";
           }
           cout << endl;
       }
   }


   //member variables
   int state[3][3];
   int depth = 0;
   int cost = 0;
};

// bool comparator(const Node&lhs, const Node& rhs) {
//    return lhs.cost > rhs.cost;
// }

bool comparatorAStar(const Node&lhs, const Node& rhs) {
   return (lhs.cost + lhs.depth) > (rhs.cost + rhs.depth);
}

#endif