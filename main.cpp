#include "Problem.h"
using namespace std;

int totalexpanded = 0;

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

void uniformCost(priority_queue<Node, vector<Node>, decltype(&comparatorAStar)> &nodes, Node node, Problem problem) {
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

void missingTile(priority_queue<Node, vector<Node>, decltype(&comparatorAStar)> &nodes, Node node, Problem problem) {
   vector<Node> vec = expand(node, problem);
   //vector<Node> newVec;
   for (int i = 0; i < vec.size(); i++) {
       if (!problem.isVisited(vec.at(i))) { //if neighbor is not visited, compute missing tiles and push to queue in order of h(n)
           vec.at(i).cost = computeMissingTiles(vec.at(i));
           //newVec.push_back(vec.at(i));
           nodes.push(vec.at(i));
       }
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

void manhattan(priority_queue<Node, vector<Node>, decltype(&comparatorAStar)> &nodes, Node node, Problem problem) {
   vector<Node> vec = expand(node, problem);
   //vector<Node> newVec;
   for (int i = 0; i < vec.size(); i++) {
       if (!problem.isVisited(vec.at(i))) {
           vec.at(i).cost = computeManhattan(vec.at(i));
           //newVec.push_back(vec.at(i));
           nodes.push(vec.at(i));
       }
   }

   return;

}

Node generalSearch(Problem problem, int queueingFunction) {
   priority_queue<Node, vector<Node>, decltype(&comparatorAStar)> nodes(comparatorAStar);
   nodes.push(problem.initialState);
   while(!nodes.empty()) {
       Node node = nodes.top();
       problem.visit(node);
       nodes.pop();
       totalexpanded++;
      
       //testing
       cout << endl;
       cout << "The best node to expand with g(n) = " << node.depth << " and h(n) = " << node.cost << " is " << endl;
       node.print();
       cout << endl;

       if (problem.goalTest(node)) {return node;}
       if (queueingFunction == 1) {uniformCost(nodes,node,problem);}
       else if (queueingFunction == 2) {missingTile(nodes,node,problem);}
       else {manhattan(nodes,node,problem);}
   }
   cout << "Failed" << endl;
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
   const auto clkStart = std::chrono::high_resolution_clock::now();
   Node result = generalSearch(problem, func);
   const auto clkEnd = std::chrono::high_resolution_clock::now();
   //const int duration = clkStart - clkEnd;
    const std::chrono::duration<double> d = clkEnd-clkStart;

    cout << "We've reached the goal state: " << endl;
   result.print();
   cout << "at depth: " << result.depth << endl;
   cout << "Total nodes expanded: " << totalexpanded << endl;
   cout << "Time taken: " << d.count() << "s" << endl << endl;


   return 0;
}
