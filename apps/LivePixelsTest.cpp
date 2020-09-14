#include <iostream>
#include <LivePixels/math.hpp>
#include <LivePixels/SDFs.hpp>
#include <LivePixels/Ray.hpp>
#include <stack>
#include <cmath>
#include <vector>

using lp::angleToRadian;
using std::sin;
using std::cos;
using Qtr = lp::Quaternion<float>;


int main(int argc, char **argv)
{
    std::stack<char> queue;
    std::string string;
    std::cin >> string;
    for (char i: string)
        queue.push(i);
    while (!queue.empty())
    {
        std::cout << queue.top();
        queue.pop();
    }
    return 0;
}
