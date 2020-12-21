#include <iostream>
#include <vector>
#include "octree.h"
#include <bits/stdc++.h>

using namespace std;

CImg<unsigned char> Binarizar(CImg<float> &img, int umbral) {
    CImg<unsigned char> R(img.width(), img.height());
    for (int i = 0; i < img.width(); i++)
        for (int j = 0; j < img.height(); j++) {
            int r = img(i, j, 0);
            int g = img(i, j, 1);
            int b = img(i, j, 2);
            if ((r + g + b) / 3 > umbral)
                R(i, j) = 255;
            else
                R(i, j) = 0;
        }
    return R;
}

//g++ main.cpp  -L/usr/X11R6/lib -lm -lpthread -lX11

CImg<unsigned char> load_3d() {
    int x = 512, y = 512, z = 40;
    CImg<unsigned char> R(x, y, z, 1);
    ifstream db("db.txt");
    string filename;
    for (int k = 0; k < R.depth(); k++) {
        getline(db, filename);
        string temp = "datos cerebros/paciente 1/1/" + filename;
        CImg<float> tmp(temp.c_str());
        CImg<unsigned char> img = Binarizar(tmp, 122);
        for (int i = 0; i < R.height(); i++) {
            for (int j = 0; j < R.width(); j++) {
                R(i, j, k) = img(i, j);
            }
        }
    }
    return R;
}

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

int main() {

    srand(time(NULL));

    CImg<unsigned char> R = load_3d();
    cout << sizeof(R) << endl;
    R.display();
    /* insert(R, "data.txt"); */  //Descomentar para cargar el Octree en disco 
    Octree oct("data.txt");
    tester(oct, R);

    return 0;
}