#include "../CImg.h"
#include "point.h"

using namespace cimg_library;

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

bool isColorUnique(point pi, point pf, int color, CImg<unsigned char> &image) {
    for (int i = pi.coor[0]; i < pf.coor[0]; i++) {
        for (int j = pi.coor[1]; j < pf.coor[1]; j++) {
            for (int k = pi.coor[2]; k < pf.coor[2]; k++) {
                if (color != image(j, i, k))
                    return false;
            }
        }
    }
    return true;
}
