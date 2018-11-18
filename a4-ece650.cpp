#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <minisat/core/Solver.h>
#include "minisat/core/SolverTypes.h"
#include "vsover.h"


using namespace std;


vector<vector<int> > Create_Node_list(int NumberofVertices, vector<vector<int> >& Edge_List){  //Define an array to store all node information
    vector<vector<int> > Vertex_Vector;
    for(int i = 0; i < NumberofVertices; i++){  //For Loop to create an array has size equal to number of Vertices
        vector<int> Vertex;                    //Set vector for each vertex
        Vertex.push_back(i);                   //Set the name for each Vertex
        Vertex.push_back(-1);                   //Set the parts for 0(For None)
        Vertex.push_back(0);                   //Set the Node Status(0 for searched and 1 for searched)
        Vertex_Vector.push_back(Vertex);       //Create the Vector
    }
    Edge_List.clear();                         //Reset Edge List
    return  Vertex_Vector;
}

int Read_Number_Of_Vertices(string User_Input){                //Define an function to analyze the user input and return number of vertices
    int Number_Of_vertices;                                    //Create a variable to store the number of vertices
    int String_Index;                                          //a variable to find where the space from the input
    int String_Length;                                         //a variable to store the length of string
    String_Index = User_Input.find(" ");                       //Locate the position of " "
    String_Length = User_Input.length();                       //The length of the string
    istringstream(User_Input.substr(String_Index+1, String_Length-String_Index)) >> Number_Of_vertices;     //Read the string and get the number of vertex
    return  Number_Of_vertices;
}


vector<string> String_Split(string String_Input, string Deliminator){           //A Function split a string and return a vector
    int String_Index = 0;                                                       //Initialized the String Index
    vector<string> Splited_String;                                              //Initialized the Vector
    string Sub_String;                                                          //Initialized the substring
    string String_For_Split = String_Input;                                     //Record the string for split
    while(String_Index != -1){                                                  //Stop the loop if deliminator is not found
        String_Index = String_For_Split.find(Deliminator);
        Sub_String = String_For_Split.substr(0,String_Index);                   //Find the substring
        Splited_String.push_back(Sub_String);                                   //Added the substring to vector
        String_For_Split.erase(0, String_Index+1);                              //Re-size the string
    }
    return Splited_String;
}

vector<vector<int> > Read_Edge_list(string User_Input, vector<vector<int> > VerticesVector){                  //Define an function to analyze the user input and return array of edge
    int String_Index1;
    int String_Index2;                                                                                      //a variable to find where the space from the input
    int Edge_Number;                                                                                        //a variable to store the number of edge
    int Node_Length = VerticesVector.size();
    string Edge_String = User_Input;                                                                        //Local String to store the user input
    vector<string> Tmp_Edge_List = String_Split(Edge_String, "<");                                          //Store the string in a temporary vector
    Edge_Number = Tmp_Edge_List.size();                                                                     //Determine the length of the edge list
    vector<vector<int> > Edge_List;                                                                         //Initialized Pointer for 2D Edge_list
    for(int i=0; i < Edge_Number; i++){
        if(i >=1) {                                                                                        //Loop Start from 1(Since index 0 is "E {"
            vector<int> Edge_Pair;
            String_Index1 = Tmp_Edge_List[i].find(",");                                                    //Substring to find the vertex number
            String_Index2 = Tmp_Edge_List[i].find(">");
            int tmp_int;
            istringstream(Tmp_Edge_List[i].substr(0, String_Index1)) >> tmp_int;
            Edge_Pair.push_back(tmp_int);
            istringstream(Tmp_Edge_List[i].substr(String_Index1+1, (String_Index2-String_Index1-1))) >> tmp_int;
            Edge_Pair.push_back(tmp_int);
            Edge_List.push_back(Edge_Pair);                                                                //A Function is needed to validate the edge list
        }
    }
    for(int i = 0; i < Edge_List.size(); i++){                                                             //Error Check
        if(Edge_List[i][0]> (Node_Length-1) || Edge_List[i][1]> (Node_Length-1) ){
            cerr << "Error: Edge List contains nodes beyond the node list" << endl;
            break;
        }
    }
    return Edge_List;
}

int main() {
    string User_Input;                                             //Assign an empty string to read user input
    vector<vector<int> > VerticesVector;                           //Assign an pointer refer to vertices array
    vector<vector<int> > Edge_List;                                //Assign an empty vector to store the edge
    string Out_Put_Mini;
    vector<vector<string>> variable_string;
    while(true) {                                                  //Main loop of the file

        getline(cin, User_Input);                                 //Take system standard input
        if (User_Input == "") {                                      //Exit the program if user input empty string
            break;
        } else if (User_Input.substr(0, 1) == "V") {                    //For the case the user input vertices
            int Number_Of_Vertices;                                //Create a variable to store the number of vertices
            Number_Of_Vertices = Read_Number_Of_Vertices(User_Input);
            VerticesVector = Create_Node_list(Number_Of_Vertices, Edge_List);                     //Create the node list

        } else if (User_Input.substr(0, 1) == "E") {                    //For the case the user input edge set
            Out_Put_Mini = "";
            Edge_List = Read_Edge_list(User_Input, VerticesVector);
            int number = VerticesVector.size();
            //Solver
            for(int k = 0; k < number; k++){
                try {
                    Solver s(number, k, Edge_List);
                    if (s.solve()) {
                        auto solution = s.get_solution();
                        string tmp_out;
                        for (int i = 0; i < solution.size(); i++){
                            if(solution[i] == 1){
                                tmp_out += to_string(i) + " ";
                            }
                        }
                        tmp_out.pop_back();
                        cout<<tmp_out<<endl;
                        break;
                    }
                } catch(std::exception const& ex) {
                    std::clog << "Failed parsing because: " << ex.what() << std::endl;
                    return 1;
                }
            }

        }
    }

    return 0;


}

//for(int i = 0; i < variable_string.size();i++){
    //for (int j = 0; j < variable_string[i].size();j++){
        //cout << variable_string[i][j]<<" ";
    //}
    //cout << "0 \n";
//}