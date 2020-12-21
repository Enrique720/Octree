#include "octree.h"

void tester(Octree &oct, CImg<unsigned char> &R) {
    double ang1, ang2;
    for (int i = 0; i < 20; i++) {
        ang1 = (rand() % 3000) / 1000;
        ang2 = (rand() % 3000) / 1000;
        CImg<unsigned char> RR = oct.Get_Cut(R.width(), R.height(), R.depth(), ang1, ang2);
        string filename = "testImg/" + to_string(i);
        filename += ".jpg";
        RR.save(filename.c_str());
        CImg<unsigned char> RR2 = Get_Cut(R.width(), R.height(), R.depth(), ang1, ang2, R);
        string filename2 = "testImgR/" + to_string(i) + ".jpg";
        RR2.save(filename2.c_str());
    }
}
