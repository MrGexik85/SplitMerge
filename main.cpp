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

double splitAndCalculate(string str, int &offset){
    int index = 0;
    vector<Cell> cells;
    int index_start = 0;
    int index_end = 0;
    while(index < str.size()){
        if(str[index] == '('){ // Если встретилась открывающаяся скобка
            int off = 0;
            cout << "(" << endl;
            index++;
            double value = splitAndCalculate(str.substr(index), off);
            index += off;
            if(index < str.size()){
                Cell temp = {value, str[index]};
                cout << "Created cell: Cell{" << temp.value << ", " << "\'" << temp.action << "\'}" << endl;
                cells.push_back(temp);
                index++;
            } else {
                Cell temp = {value, ')'};
                cout << "Created cell: Cell{" << temp.value << ", " << "\'" << temp.action << "\'}" << endl;
                cells.push_back(temp);
                break;
            }
            index_start = index;
            index_end = index;
        } else if(isOperator(str[index])){ // если встретился оператор
            double value = atof(str.substr(index_start, index_end-index_start+1).c_str());
            char action = str[index];
            index++;
            index_start = index;
            index_end = index;
            Cell temp = {value, action};
            cout << "Created cell: Cell{" << value << ", " << "\'" << action << "\'}" << endl;
            cells.push_back(temp);
        } else if(str[index] == ')') { // Если встретилась закрывающаяся скобка
            double value = atof(str.substr(index_start, index_end-index_start).c_str());
            char action = ')';
            Cell temp = {value, action};
            cout << "Created cell: Cell{" << value << ", " << "\'" << action << "\'}" << endl;
            cells.push_back(temp);
            offset = index+1;
            break;
        } else { // Если встретилась цифра
            index_end++;
            index++;
            if(index == str.size()){
                double value = atof(str.substr(index_start, index_end-index_start+1).c_str());
                Cell temp = {value, ')'};
                cout << "Created cell: Cell{" << temp.value << ", " << "\'" << temp.action << "\'}" << endl;
                cells.push_back(temp);
            }
        }
    }
    double result = merge(cells[0], 1, cells);
    return result;
}



int main(){
    string strSource = "3+5*(1+3)";
    int trash = 0;
    double result = splitAndCalculate(strSource, trash);
    cout << "Finish result: " << result << endl;
    return 0;
}
