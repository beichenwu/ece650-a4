#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <cstdlib>
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

vector<vector<string>> Define_Variable_list(int n, int k){
    vector<vector<string>> tmp_list;
    vector<string> zero_vector;
    zero_vector.push_back("0");
    int bool_num =1;
    tmp_list.push_back(zero_vector);
    for (int i = 0; i < n; i++){
        vector<string> n_list;
        n_list.push_back("0");
        for(int j = 0; j <  k;j++){
            n_list.push_back(to_string(bool_num));
            bool_num++;
        }
        tmp_list.push_back(n_list);
    }

    return tmp_list;
}


string vertex_in_cover(int n, int k, vector<vector<string>> v_list){
    string tmp_string;
    for (int i = 1; i <= k; i++){
        for(int j = 1; j <= n;j++){
            tmp_string += v_list[j][i] + " ";
        }
        tmp_string += "0\n";
    }

    return tmp_string;
}


string vertex_not_twice_in_cover(int n, int k, vector<vector<string>> v_list){
    string tmp_string;
    for (int i = 1; i <=n; i++){

        for(int j = 1; j <= k; j++){
            int pq = 1;
            while(pq < j){
                tmp_string += "-"+ v_list[i][pq] + " "+ "-" + v_list[i][j];
                tmp_string += " 0\n";
                pq++;
            }

        }
    }
    return  tmp_string;
}

string vertex_not_twice_in_same_spot(int n, int k, vector<vector<string>> v_list){
    string tmp_string;
    for (int i = 1; i <=k; i++){

        for(int j = 1; j <= n; j++){
            int pq = 1;
            while(pq < j){
                tmp_string += "-"+ v_list[pq][i] + " "+ "-" + v_list[j][i];
                tmp_string += " 0\n";
                pq++;
            }

        }
    }
    return  tmp_string;
}

string edge_incident_vertex_cover(int k, vector<vector<string>> v_list, vector<vector<int> > E_List) {
    string tmp_string;
    for (int i = 0; i < E_List.size(); i++) {
        for (int j = 1; j <= k; j++) {
            tmp_string += v_list[E_List[i][0] + 1][j] + " " +  v_list[E_List[i][1] + 1][j] + " ";
        }
        tmp_string += "0\n";
    }
    return tmp_string;
}
unsigned long long choose(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

string create_first_line(int n, int k, vector<vector<int> > E_List){
    int k_2;
    int n_2;
    int number_of_bool;
    int number_of_clause;
    string tmp_string;
    number_of_bool = n * k;
    k_2 = choose(k, 2);
    n_2 = choose(n, 2);

    number_of_clause = n * k_2 + k* n_2 + E_List.size() + k;
    tmp_string = "p cnf " + to_string(number_of_bool) + " " + to_string(number_of_clause) + "\n";
    return tmp_string;

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
            int cover_size_k = 3;
            variable_string = Define_Variable_list(number, cover_size_k);
            //for(int i = 0; i < variable_string.size();i++){
                //for (int j = 0; j < variable_string[i].size();j++){
                //cout << variable_string[i][j]<<" ";
            //}
                //cout << "0 \n";
            //}

            string constrain_1 = vertex_in_cover(number, cover_size_k, variable_string);
            string constrain_2 = vertex_not_twice_in_cover(number, cover_size_k, variable_string);
            string constrain_3 = vertex_not_twice_in_same_spot(number, cover_size_k, variable_string);
            string constrain_4 = edge_incident_vertex_cover(cover_size_k, variable_string, Edge_List);
            string title = create_first_line(number, cover_size_k,Edge_List);
            Out_Put_Mini += title + constrain_1  + constrain_3 + constrain_2 + constrain_4;
            cout << Out_Put_Mini << endl;
            //Out_Put_Mini +=constrain_1 + constrain_2 + constrain_3;
            //cout << Out_Put_Mini << endl;

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