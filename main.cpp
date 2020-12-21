#include "src/octree.h"
#include "src/tester.h"

int main() {

    srand(time(NULL));
    CImg<unsigned char> R = load_3d("paths/p1.txt");
    cout << sizeof(R) << endl;
    //R.display();
    insert(R, "data.txt");   //Descomentar para cargar el Octree en disco 
    Octree oct("data.txt");
    tester(oct, R);

    return 0;
}