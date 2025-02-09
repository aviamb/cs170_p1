#include <iostream>
using namespace std;


//global variables


struct Node {
    //Node constructors
    Node();
    Node(int r1[3], int r2[3], int r3[3]) {
        for (int i = 0; i < 3; i++) {
            state[0][i] = r1[i];
            state[1][i] = r2[i];
            state[2][i] = r3[i];
        }
    };


    //member variables
    int state[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
};


struct Problem {
    //Problem Constructor
    Problem();
    Problem(int r1[3], int r2[3], int r3[3]) {
        int g1[3] = {1,2,3};
        int g2[3] = {4,5,6};
        int g3[3] = {7,8,0};
       
        initialState = Node(r1,r2,r3);
        goalState = Node(g1,g2,g3);     //goal state is always the same
    };
   
    //member variables
    Node initialState;
    Node goalState;
};


Node generalSearch(Problem problem) {
   
    return;
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


    //initializations
    Problem problem(r1,r2,r3);


    //search call
    generalSearch(problem);


    return 0;
}




