

#include "CImg.h"
#include <iostream>
#include <fstream>
#include <tuple>
using namespace cimg_library;
using namespace std;

struct point{
    double x, y, z;    
};

struct pixel_des{
    double xi, xf, yi, yf, zi, zf;
    bool isLeaf;
    int64_t children[8];
};

bool isColorUnique(int xi, int yi, int zi, int xf, int yf, int zf, int color, CImg<unsigned char> &image){
    for(int i=xi; i<xf; i++){
        for(int j=yi; j<yf; j++){
            for(int k=zi; k<zf; k++){
                if(color != image(j,i,k))
                return false;
            }
        }
    }
    return true;
}

int64_t insert(int xi, int yi, int zi, int xf, int yf, int zf, CImg<unsigned char> &image, 
    ofstream &output_file){
    int color = image(yi,xi,zi);
    bool unique = isColorUnique(xi,yi,zi,xf,yf,zf,color,image);
    pixel_des pd = {xi,xf,yi,yf,zi,zf,false};
    int64_t size = output_file.tellp();
    if(unique){
        if(color == 255){
            pd.isLeaf = true;
            output_file.write((char*)&pd, sizeof(pixel_des));
            return size;
        }
        return -1;
    } else {
        int mx = (xf+xi)/2;
        int my = (yf+yi)/2;
        int mz = (zf+zi)/2;
        if(xi!=mx && yi!=my && zi!=mz) pd.children[0] = insert(xi,yi,zi,mx,my,mz,image,output_file);
        if(xi!=mx && yi!=my && mz!=zf) pd.children[1] = insert(xi,yi,mz,mx,my,zf,image,output_file);
        if(xi!=mx && my!=yf && zi!=mz) pd.children[2] = insert(xi,my,zi,mx,yf,mz,image,output_file);
        if(xi!=mx && my!=yf && mz!=zf) pd.children[3] = insert(xi,my,mz,mx,yf,zf,image,output_file);
        if(mx!=xf && yi!=my && zi!=mz) pd.children[4] = insert(mx,yi,zi,xf,my,mz,image,output_file);
        if(mx!=xf && yi!=my && mz!=zf) pd.children[5] = insert(mx,yi,mz,xf,my,zf,image,output_file);
        if(mx!=xf && my!=yf && zi!=mz) pd.children[6] = insert(mx,my,zi,xf,yf,mz,image,output_file);
        if(mx!=xf && my!=yf && mz!=zf) pd.children[7] = insert(mx,my,mz,xf,yf,zf,image,output_file);
        output_file.write((char*)&pd, sizeof(pixel_des));
        return size;
    }
}

void insert(CImg<unsigned char> &image, string filename){
    int w = image.width();
    int h = image.height();
    int d = image.depth();
    ofstream output_file(filename, ios::binary | ios::trunc);
    insert(0,0,0,h,w,d,image,output_file);
}

CImg<unsigned char> reconstruir(int w, int h, int d, string filename){
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<unsigned char> R(w,h,d,1,0); 
    while(input_file.read((char*)&pd, sizeof(pixel_des))){
        for(int i=pd.xi; i<pd.xf; i++){
            for(int j=pd.yi; j<pd.yf; j++){
                for(int k=pd.zi; k<pd.zf; k++){
                    R(j,i,k) = 255;
                }
            }
        }
    }
    return R;
}