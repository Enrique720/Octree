#include "octree.h"

void tester(Octree &oct, CImg<unsigned char> &R) {
    clock_t time1, time2;
    double ang1, ang2;
    cout << "Tiempo Octree  & Tiempo Cubo " << endl;
    for (int i = 0; i < 20; i++) {
        
        ang1 = (rand() % 3000) / 1000;
        ang2 = (rand() % 3000) / 1000;
        
        time1 = clock();
        CImg<unsigned char> RR = oct.Get_Cut(R.width(), R.height(), R.depth(), ang1, ang2);
        time2 = clock(); 
        cout << double(time2-time1)/CLOCKS_PER_SEC << " & ";
        
        string filename = "testImg/" + to_string(i) + ".jpg";
        //RR.save(filename.c_str());

        time1 = clock();
        CImg<unsigned char> RR2 = Get_Cut(R.width(), R.height(), R.depth(), ang1, ang2, R);
        time2 = clock();

        cout << double(time2-time1)/CLOCKS_PER_SEC << endl;
        cout << "Similitud: " << cmpImg(RR,RR2) << '\n';

        string filename2 = "testImgR/" + to_string(i) + ".jpg";
        //RR2.save(filename2.c_str());
    }
}
