#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "CImg.h"
#include <fstream>
#include <tuple>

using namespace cimg_library;
using namespace std;

struct pixel_des{
    unsigned short xi, xf, yi, yf;
    unsigned char r,g,b;
};

bool isColorUnique(int xi, int yi, int xf, int yf, int umbral, tuple<int,int,int> &rgb,
    CImg<float> &image){
    int color = image(yi,xi);
    int r = 0, g = 0, b = 0;
    int n = (xf-xi) * (yf-yi);
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            r += image(j,i,0);
            g += image(j,i,1);
            b += image(j,i,2);
        }
    }
    r /= n, g /= n, b /= n;
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            if(abs(image(j,i,0)-r) > umbral || abs(image(j,i,1)-g) > umbral ||
                abs(image(j,i,2)-b) > umbral)
                return false;
        }
    }
    rgb = {r,g,b};
    return true;
}

void insert(int xi, int yi, int xf, int yf, int umbral, CImg<float> &image, ofstream &output_file){
    tuple<int,int,int> rgb;
    bool unique = isColorUnique(xi,yi,xf,yf,umbral,rgb,image);
    if(unique){
        pixel_des pd = {xi, xf, yi, yf, get<0>(rgb), get<1>(rgb), get<2>(rgb)};
        output_file.write((char*)&pd, sizeof(pixel_des));
    } else {
        int mx = (xf+xi)/2;
        int my = (yf+yi)/2;
        if(xi!=mx && yi!=my) insert(xi,yi,mx,my,umbral,image,output_file);
        if(mx!=xf && yi!=my) insert(mx,yi,xf,my,umbral,image,output_file);
        if(xi!=mx && my!=yf) insert(xi,my,mx,yf,umbral,image,output_file);
        if(mx!=xf && my!=yf) insert(mx,my,xf,yf,umbral,image,output_file);
    }
}


void insert(CImg<float> &image, int umbral, string filename){
    int w = image.width();
    int h = image.height();
    ofstream output_file(filename, ios::binary | ios::trunc);
    insert(0,0,h,w,umbral,image,output_file);
}


CImg<float> reconstruir(int w, int h, string filename){
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<float> R(w,h,1,3); 
    while(input_file.read((char*)&pd, sizeof(pixel_des))){
        for(int i=pd.xi;i<pd.xf;i++){
            for(int j=pd.yi;j<pd.yf;j++)
            {
                R(j,i,0) = pd.r;
                R(j,i,1) = pd.g;
                R(j,i,2) = pd.b;
            }
        }
    }
    return R;
}


#endif //QUADTREE_QUADTREE_H