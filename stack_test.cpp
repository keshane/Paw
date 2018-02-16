#include <string>
#include <iostream>
#include <stack>
void DIE(char const *message) {
    std::cout << message << std::endl;
}

typedef struct Coordinate {
    int a;
    int b;
} Coordiinate;

class Stack_Alloc {
    private:
        std::stack<Coordinate> coord_stack;
        int grid[9][9];
    public:
        Stack_Alloc();

};

Stack_Alloc::Stack_Alloc() {
    grid[0][0] = 3;
}


int main(int argc, char *argv[]) {
    Stack_Alloc my_class;
    
    std::cout << "Thank you for playing today\n";
}
