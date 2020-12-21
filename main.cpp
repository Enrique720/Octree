#include "src/octree.h"
#include "src/tester.h"

int main() {
    
    srand(time(NULL));
    //CImg<unsigned char> R = load_3d();
    //cout << sizeof(R) << endl;
    //R.display();
    /* insert(R, "data.txt"); */  //Descomentar para cargar el Octree en disco 
    //Octree oct("data.txt");
    vector<string> files = {"paths/p1.txt","paths/p2.txt","paths/p3.txt","paths/p4.txt","paths/p5.txt"};
    for(auto file:files)
        tester(file);

    return 0;
}