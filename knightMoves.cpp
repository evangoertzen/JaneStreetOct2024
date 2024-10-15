#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int GOAL_SCORE = 2024;
int GOAL_ROW = 5;
int GOAL_COL = 5;

// to verify solution
int a=3, b=2, c=1;
vector<vector<int>> startBoard = {
        {a, b, b, c, c, c},
        {a, b, b, c, c, c},
        {a, a, b, b, c, c},
        {a, a, b, b, c, c},
        {a, a, a, b, b, c},
        {a, a, a, b, b, c}
    };

void printBoard(vector<vector<int>>& arr){
    cout<<"{";
    for(auto row: arr){
        cout<<"[";
        for( auto num: row){
            cout<<num<<", ";
        }
        cout<<"]"<<endl;
    }
    cout<<"}"<<endl;;
}

int scoreFromPath(string path){
    string el;
    vector<string> pathVect;
    stringstream ss(path);

    //get path in vect
    while(getline(ss, el, ',')){
        pathVect.push_back(el);
    }


    int score = 0;
    string curPosition;
    string prevPosition;

    int row, col;
    int prev_val = a;

    for(auto step: pathVect){
        col = step[0]-'a';
        row = 6-(step[1]-'0');


        if(startBoard[row][col] == prev_val){
            score += startBoard[row][col];
        }else{
            score = score * startBoard[row][col];
        }

        prev_val = startBoard[row][col];
    }

    return score;
}

int calcScore(int cur_row, int cur_col, int move_to_row, int move_to_col, vector<vector<int>>& arr, int cur_score){

    if(cur_score > GOAL_SCORE){
        return -1;
    }

    
    // don't allow illegal moves
    if(
        // if out of bounds
        cur_row > 5 || cur_row < 0
        || cur_col > 5 || cur_col < 0
        || move_to_row > 5 || move_to_row < 0
        || move_to_col > 5 || move_to_col < 0

        // or spot already been to
        || arr[move_to_row][move_to_col] == 0
    ){
        // cout<<"Can't go here dog"<<endl;
        return -1;
    }

    // if same letters
    if(arr[cur_row][cur_col] == arr[move_to_row][move_to_col]){
        return cur_score + arr[move_to_row][move_to_col];
    }else{ // diff letters
        return cur_score * arr[move_to_row][move_to_col];
    }

    return 1;
}

string search(string path, int cur_row, int cur_col, int cur_score, vector<vector<int>> cur_arr){


    string pos = string(1, cur_col+'a') + to_string(6-cur_row)+",";
    path = path + pos;

    // verify score is correct from path
    // if(cur_score != scoreFromPath(path)){
    //     cout<<"Discrepency in path "<<path<<endl;
    //     cout<<"cur_score = "<<cur_score<<", scoreFromPath = "<<scoreFromPath(path)<<","<<endl;
    //     exit(1);
    // }

    // if you found it return path
    if(cur_score == GOAL_SCORE && cur_col == GOAL_COL && cur_row == GOAL_ROW){
        return path;

    // if you didn't, keep looking or quit
    }else{


        // up 1 right 2
        if( int score_temp = calcScore(cur_row, cur_col, cur_row+1, cur_col+2, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row+1, cur_col+2, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // up 2 right 1
        if( int score_temp = calcScore(cur_row, cur_col, cur_row+2, cur_col+1, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row+2, cur_col+1, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // down 1 right 2
        if( int score_temp = calcScore(cur_row, cur_col, cur_row-1, cur_col+2, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row-1, cur_col+2, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // down 2 right 1
        if( int score_temp = calcScore(cur_row, cur_col, cur_row-2, cur_col+1, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row-2, cur_col+1, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // down 2 left 1
        if( int score_temp = calcScore(cur_row, cur_col, cur_row-2, cur_col-1, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row-2, cur_col-1, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // down 1 left 2
        if( int score_temp = calcScore(cur_row, cur_col, cur_row-1, cur_col-2, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row-1, cur_col-2, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // up 2 left 1
        if( int score_temp = calcScore(cur_row, cur_col, cur_row+2, cur_col-1, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row+2, cur_col-1, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // up 1 left 2
        if( int score_temp = calcScore(cur_row, cur_col, cur_row+1, cur_col-2, cur_arr, cur_score); score_temp > 0){
            vector<vector<int>> new_arr = cur_arr;
            new_arr[cur_row][cur_col] = 0;
            if(string found_path = search(path, cur_row+1, cur_col-2, score_temp, new_arr); found_path != "0"){
                return found_path;
            }
        }

        // no solution found
        return "0";
    }


}


int main(int argc, char* argv[]){

    a = stoi(argv[1]);
    b = stoi(argv[2]);
    c = stoi(argv[3]);

    cout<<"a: "<<a<<", b: "<<b<<", c: "<<c<<endl;

    vector<vector<int>> arr = {
        {a, b, b, c, c, c},
        {a, b, b, c, c, c},
        {a, a, b, b, c, c},
        {a, a, b, b, c, c},
        {a, a, a, b, b, c},
        {a, a, a, b, b, c}
    };


    int cur_row = 0;
    int cur_col = 0;

    int score = a;

    string path = search("", cur_row, cur_col, score, arr);
    // cout<<"score from path: "<<scoreFromPath("a6,c5,e4,f2,d3,e1,c2,a3,b1,d2,c4,a5,b3,d4,b5,c3,e2,c1,a2,b4,d5,e3,f1")<<endl;

    cout<<"search result: "<<path<<endl;


    //my answer: 
    // 3,2,1,
    // a1,c2,e1,f3,e5,c6,d4,e6,c5,b3,d2,b1,c3,e2,f4,d5,e3,f5,d6,e4,f6
    // a6,c5,e4,f2,d3,e1,c2,a3,b1,d2,c4,a5,b3,d4,b5,c3,e2,c1,a2,b4,d5,e3,f1,



}