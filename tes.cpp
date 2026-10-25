#include <iostream>
using namespace std;



int main() {
    int stok = 10;
    int *ptr = &stok;
    int salinan = *ptr;
    salinan = 99;
    cout << stok;
    return 0;
}