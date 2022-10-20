#include <iostream>

#include "MyVector.hpp"
#include "Solution.hpp"

using namespace std;

int main() {
    float a[3] = { 1,2,3 };
    float b[5] = { 5,6,7,8,9 };
    vectorJS<float> num1(a, 3);
    vectorJS<float> num2(b, 5);

    Solution<float> solution;
    cout << "The mid num is: " << solution.findMedianSortedArrays(num1, num2) << endl;
    showElements(num1); //遍历输出num1的所有元素

    cin.get();

    return 0;
}