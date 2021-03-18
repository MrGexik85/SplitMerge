#include <iostream>
#include <vector>

using namespace std;

// Структура для ячеек - хранит значение и опрецию с этим значением
struct Cell {
    double value;
    char action;
};

// Возвращает приоритет каждой операции
int getPriority(char action){
    switch(action){
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
    }
    return 0;
}

// могут ли две ячейки, переданные в кач-ве параметров быть слиты в одну
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

// Объединение ячеек из списка ячеек
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

// Далее идут 3 вспомогательные булевые функции определяющие является символ числом, буквой или оператором
bool isDigit(char c){
    return c >= '0' && c <= '9';
}

bool isLetter(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
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

// Функци разбивает строку на ячейки и считает значение (применяется рекурсия)
double splitAndCalculate(string str, int &index){
    vector<Cell> cells;
    while(index < str.size()){
        if(isDigit(str[index])){
            // Если встретилась цифра - считываем полностью число и следующий за ним знак операции
            int value = 0;
            do {
                int cur = str[index++] - '0';
                value = value*10 + cur;
            } while(isDigit(str[index]));
            char op = (index < str.size()) ? str[index] : ')';
            str[index] == ')' ? 0 : index++;
            Cell temp = {value, op};
            cells.push_back(temp);
            cout << "Created Cell: (" << value << "; \'" << op << "\')" << endl;
        } else if(str[index] == '('){
            // Если встретилась открывающая скобка - вызвать функцию рекурсивно и выполнить сдвиг по строке
            cout << "Enter \'(\'" << endl;
            index++;
            double value = splitAndCalculate(str, index);
            char op = (index < str.size()) ? str[index++] : ')';
            Cell temp = {value, op};
            cells.push_back(temp);
            cout << "Created Cell: (" << value << "; \'" << op << "\')" << endl;
        } else if(str[index] == ')'){
            // Если встретилась закрывающая скобка - выход из рекурсии
            cout << "Exit \')\'" << endl;
            index++;
            break;
        }
    }
    double result = merge(cells[0], 1, cells);
    return result;
}



int main(){
    string strSource;
    cin >> strSource;
    int trash = 0;
    double result = splitAndCalculate(strSource, trash);
    cout << "Finish result: " << result << endl;
    return 0;
}
