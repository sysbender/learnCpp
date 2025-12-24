#include <iostream>

int main()
{

    int x[5] = {1, 2, 3, 4, 5};
    int y[5] = {1, 2, 3, 4, 5};

    std::cout << "hello world!" << std::endl;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "[" << x[i] << "," << y[i] << "]" << std::endl;
    }
    return 0;
}