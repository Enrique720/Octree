//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "CImg.h"
#include <fstream>
#include <tuple>

using namespace cimg_library;
using namespace std;

struct pixel_des{
    unsigned short xi, xf, yi, yf, zi, zf;
    unsigned char r,g,b;
};

bool isColorUnique(int xi, int yi, int zi, int xf, int yf, int zf, int umbral,
    tuple<int,int,int> &rgb, CImg<float> &image){
    int color = image(yi,xi);
    int r = 0, g = 0, b = 0;
    int n = (xf-xi) * (yf-yi) * (zf-zi);
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            for(int k=zi; k<zf; k++){
                r += image(j,i,k,0);
                g += image(j,i,k,1);
                b += image(j,i,k,2);
            }
        }
    }
    r /= n, g /= n, b /= n;
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            for(int k=zi; k<zf; k++){
                if(abs(image(j,i,k,0)-r) > umbral || abs(image(j,i,k,1)-g) > umbral
                   || abs(image(j,i,k,2)-b) > umbral)
                    return false;
            }
        }
    }
    rgb = {r,g,b};
    return true;
}

void insert(int xi, int yi, int zi, int xf, int yf, int zf, int umbral, 
    CImg<float> &image, ofstream &output_file){
    
    tuple<int,int,int> rgb;
    bool unique = isColorUnique(xi,yi,zi,xf,yf,zf,umbral,rgb,image);
    if(unique){
        pixel_des pd = {xi,xf,yi,yf,zi,zf,get<0>(rgb),get<1>(rgb),get<2>(rgb)};
        output_file.write((char*)&pd, sizeof(pixel_des));
    } else {
        int mx = (xf+xi)/2;
        int my = (yf+yi)/2;
        int mz = (zf+zi)/2;
        if(xi!=mx && yi!=my && zi!=mz) insert(xi,yi,zi,mx,my,mz,umbral,image,output_file);
        if(xi!=mx && yi!=my && mz!=zf) insert(xi,yi,mz,mx,my,zf,umbral,image,output_file);
        if(xi!=mx && my!=yf && zi!=mz) insert(xi,my,zi,mx,yf,mz,umbral,image,output_file);
        if(xi!=mx && my!=yf && mz!=zf) insert(xi,my,mz,mx,yf,zf,umbral,image,output_file);
        if(mx!=xf && yi!=my && zi!=mz) insert(mx,yi,zi,xf,my,mz,umbral,image,output_file);
        if(mx!=xf && yi!=my && mz!=zf) insert(mx,yi,mz,xf,my,zf,umbral,image,output_file);
        if(mx!=xf && my!=yf && zi!=mz) insert(mx,my,zi,xf,yf,mz,umbral,image,output_file);
        if(mx!=xf && my!=yf && mz!=zf) insert(mx,my,mz,xf,yf,zf,umbral,image,output_file);
    }
}


void insert(CImg<float> &image, int umbral, string filename){
    int w = image.width();
    int h = image.height();
    int d = image.depth();
    ofstream output_file(filename, ios::binary | ios::trunc);
    insert(0,0,0,h,w,d,umbral,image,output_file);
}


CImg<float> reconstruir(int w, int h, int d, string filename){
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<float> R(w,h,d,3); 
    while(input_file.read((char*)&pd, sizeof(pixel_des))){
        for(int i=pd.xi; i<pd.xf; i++){
            for(int j=pd.yi; j<pd.yf; j++){
                for(int k=pd.zi; k<pd.zf; k++){
                    R(j,i,k,0) = pd.r;
                    R(j,i,k,1) = pd.g;
                    R(j,i,k,2) = pd.b;
                }
            }
        }
    }
    return R;
}


#endif //QUADTREE_QUADTREE_H