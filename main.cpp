#include <iostream>
#include <vector>

using namespace std;

struct Cell {
    double value;
    char action;
};

int getPriority(char action){
    switch(action){
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
    }
    return 0;
}

bool canMergeCells(Cell leftCell, Cell rightCell){
    return getPriority(leftCell.action) >= getPriority(rightCell.action);
}

void mergeCells(Cell &leftCell, Cell &rightCell){
    switch (leftCell.action)
    {
        case '*':
            leftCell.value *= rightCell.value;
            break;
        case '/':
            leftCell.value /= rightCell.value;
            break;
        case '+':
            leftCell.value += rightCell.value;
            break;
        case '-':
            leftCell.value -= rightCell.value;
            break;
    }
    leftCell.action = rightCell.action;
}

double merge(Cell &current, int index, vector<Cell> &vector, bool MergeOneOnly = false){
    while(index < vector.size()){
        Cell next = vector[index++];
        while(!canMergeCells(current, next)){
            merge(next, index, vector, true);
        }
        mergeCells(current, next);
        if(MergeOneOnly){
            return current.value;
        }
    }
    return current.value;
}

bool isOperator(char c){
    switch (c)
    {
        case '*':
        case '/':
        case '+':
        case '-': return true; 
        default:
            return false;
    }
}

double splitAndCalculate(string str, int &index){
    vector<Cell> cells;
    int index_start = 0;
    int index_end = 0;
    while(index < str.size() && str[index] != ')'){
        if(str[index] == '('){ // Если встретилась открывающаяся скобка
            index++;
            double value = splitAndCalculate(str.substr(index), index);
            char action;
            if(index < str.size()){
                action = str[++index];
            } else {
                action = ')';
            }
            Cell cur = {value, action};
            cells.push_back(cur);    
        } else if(isOperator(str[index])){ // если встретился оператор
            // Отрезать число, создать ячейку
        } else { // Если встретилась цифра
            index_end++;
            index++;
        }
    }
    return merge(cells[0], 1, cells);
}

int main(){
    vector<Cell> listCells;
    string strSource = "5+(10-2021)*3";
    Cell left = {11, '-'};
    Cell right = {10, '*'};
    Cell left1 = {5, ')'};
    listCells.push_back(left);
    listCells.push_back(right);
    listCells.push_back(left1);
    int index_start = 5;
    int index_end = 8;
    cout << atof(strSource.substr(index_start, index_end-index_start+1).c_str()) + 5 << endl;
    return 0;
}