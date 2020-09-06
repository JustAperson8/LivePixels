#include <iostream>
#include <LivePixels/math.hpp>
#include <LivePixels/SDFs.hpp>
#include <LivePixels/Ray.hpp>
#include <cmath>
#include <vector>

using lp::angleToRadian;
using std::sin;
using std::cos;
using Qtr = lp::Quaternion<float>;

int main(int argc, char **argv)
{
    std::cout << lp::Quaternion<float> (0, 1, 1, 0).normal() << std::endl;
    return 0;
}
