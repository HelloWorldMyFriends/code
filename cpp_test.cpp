#include <iostream>
#include <memory>
using namespace std;
int main(){
    unique_ptr<int> ptr(new int(5));
    int* ptr2 = new int(5);
    cout << *ptr << endl;
    return 0;
}