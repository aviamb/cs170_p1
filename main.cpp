#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;


//global variables


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


vector<Node> expand(Node node, Problem problem) {
   vector<Node> vec;


   for (int i = 0; i < 4; i++) {
       if (node.move(i)) {
           Node n = node;
           n.transform(i);
           n.depth = node.depth + 1;
           vec.push_back(n);
       }
   }
   return vec;
}


void uniformCost(queue<Node> &nodes, Node node, Problem problem) {
   vector<Node> vec = expand(node, problem);
   for (int i = 0; i < vec.size(); i++) {
       if (!problem.isVisited(vec.at(i))) {nodes.push(vec.at(i));}
   }
   return;
}


int computeMissingTiles(Node n) {
   int cnt = 0;
   int g1[3] = {1,2,3};
   int g2[3] = {4,5,6};
   int g3[3] = {7,8,0};
      
   Node g = Node(g1,g2,g3,0);
  
   for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
           if (n.state[i][j] != g.state[i][j]) cnt++;
       }
   }
   return cnt;
}


bool comparator(const Node&lhs, const Node& rhs) {
   return lhs.cost > rhs.cost;
}


void missingTile(queue<Node> &nodes, Node node, Problem problem) {
   vector<Node> vec = expand(node, problem);
   vector<Node> newVec;
   for (int i = 0; i < vec.size(); i++) {
       if (!problem.isVisited(vec.at(i))) { //if neighbor is not visited, compute missing tiles and push to queue in order of h(n)
           vec.at(i).cost = computeMissingTiles(vec.at(i));
           newVec.push_back(vec.at(i));
       }
   }


   sort(newVec.begin(), newVec.end(),comparator);
  
   for (int i = 0; i < newVec.size(); i++) {
       nodes.push(newVec.at(i));
   }


   return;
}


int computeManhattan(Node n) {
   int cnt = 0;
  
   int g1[3] = {1,2,3};
   int g2[3] = {4,5,6};
   int g3[3] = {7,8,0};
      
   Node g = Node(g1,g2,g3,0);


   for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
           if (n.state[i][j] != g.state[i][j]) {
               if (n.state[i][j] != 0) {
                   int row = (n.state[i][j] - 1) / 3;
                   int col = (n.state[i][j] - 1) % 3;
                   cnt += abs(i - row) + abs(j - col);
               }
           }
       }
   }
   return cnt;
}


void manhattan(queue<Node> &nodes, Node node, Problem problem) {
   vector<Node> vec = expand(node, problem);
   vector<Node> newVec;
   for (int i = 0; i < vec.size(); i++) {
       if (!problem.isVisited(vec.at(i))) {
           vec.at(i).cost = computeManhattan(vec.at(i));
           newVec.push_back(vec.at(i));
       }
   }


   sort(newVec.begin(), newVec.end(),comparator);
  
   for (int i = 0; i < newVec.size(); i++) {
       nodes.push(newVec.at(i));
   }


   return;


}


Node generalSearch(Problem problem, int queueingFunction) {
   queue<Node> nodes;
   nodes.push(problem.initialState);
   while(!nodes.empty()) {
       Node node = nodes.front();
       problem.visit(node);
       nodes.pop();
      
       //testing
       cout << endl;
       node.print();
       cout << "depth: " << node.depth << endl;
       cout << "cost: " << node.cost << endl;




       if (problem.goalTest(node)) {return node;}
       if (queueingFunction == 1) {uniformCost(nodes,node,problem);}
       else if (queueingFunction == 2) {missingTile(nodes,node,problem);}
       else {manhattan(nodes,node,problem);}
   }
}


int main() {


   //input handling
       //initial state input
   int r1[3], r2[3], r3[3];
   cout << "Enter the first row, separated by spaces (e.g. 1 2 3): " << endl;
   for (int i = 0; i < 3; i++) {
       cin >> r1[i];
   }
   cout << "Enter the second row: " << endl;
   for (int i = 0; i < 3; i++) {
       cin >> r2[i];
   }
   cout << "Enter the third row: " << endl;
   for (int i = 0; i < 3; i++) {
       cin >> r3[i];
   }
       //queueing function input
   int func = 0;
   cout << endl << "Enter algorithm preference: " << endl;
   cout << "1. Uniform Cost Search" << endl << "2. Missing Tile Heuristic" << endl << "3. Manhattan Heuristic" << endl;
   cin >> func;
   cout << endl << endl;


   //initializations
   Problem problem(r1,r2,r3);


   //search call
   Node result = generalSearch(problem, func);
   result.print();
   cout << endl << endl << "depth: " << result.depth << endl;


   return 0;
}
