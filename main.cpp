#include "src/octree.h"
#include "src/tester.h"

int main() {
    
    srand(time(NULL));

    vector<string> files = {"paths/p1.txt","paths/p2.txt","paths/p3.txt","paths/p4.txt","paths/p5.txt"};
    for(auto file:files)
        tester(file);

    return 0;
}