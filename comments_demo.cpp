#include <iostream>
#include "comments_demo.h"

using namespace std;

int Util::sum(int a, int b) {
  return a + b;
}

int main(int argc, char** argv) {
  Util util;
  cout << "sum of 44 and 77 is: " << util.sum(44, 77) << endl;
}
