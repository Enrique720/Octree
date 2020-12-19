

#include "CImg.h"
#include <iostream>
#include <fstream>
#include <tuple>
using namespace cimg_library;
using namespace std;

struct point{
    double coor[3];

    point operator+(const point &pd){
        point res;
        for(int i=0; i<3; i++){
            res.coor[i] = coor[i] + pd.coor[i];
        }
        return res;
    }

    point operator-(const point &pd){
        point res;
        for(int i=0; i<3; i++){
            res.coor[i] = coor[i] - pd.coor[i];
        }
        return res;
    }

    point operator*(const point &pd){
        point res;
        res.coor[0] = coor[1]*pd.coor[2] - coor[2]*pd.coor[1];
        res.coor[1] = coor[2]*pd.coor[0] - coor[0]*pd.coor[2];
        res.coor[2] = coor[0]*pd.coor[1] - coor[1]*pd.coor[0];
        return res;
    }

    bool operator<(const point &pd){
        return (coor[0]*coor[0]+coor[1]*coor[1]+coor[2]*coor[2]) < 
                (pd.coor[0]*pd.coor[0]+pd.coor[1]*pd.coor[1]+pd.coor[2]*pd.coor[2]);
    }

    point norm(){
        point res;
        double sum = 0;
        for(int i=0; i<3; i++){
            sum += coor[i]*coor[i];
        }
        double div = sqrt(sum);
        for(int i=0; i<3; i++){
            res.coor[i] = coor[i]/div;
        }
        return res;
    }
};

struct pixel_des{
    point pi, pf;
    bool isLeaf;
    int64_t children[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
};

bool isColorUnique(point pi, point pf, int color, CImg<unsigned char> &image){
    for(int i=pi.coor[0]; i<pf.coor[0]; i++){
        for(int j=pi.coor[1]; j<pf.coor[1]; j++){
            for(int k=pi.coor[2]; k<pf.coor[2]; k++){
                if(color != image(j,i,k))
                return false;
            }
        }
    }
    return true;
}

int64_t insert(point pi, point pf, CImg<unsigned char> &image, ofstream &output_file){
    int color = image(pi.coor[1],pi.coor[0],pi.coor[2]);
    bool unique = isColorUnique(pi,pf,color,image);
    pixel_des pd = {pi,pf,false};
    if(unique){
        if(color == 255){
            output_file.seekp(0,ios::end);
            int64_t size = output_file.tellp();
            pd.isLeaf = true;
            output_file.write((char*)&pd, sizeof(pixel_des));
            return size;
        }
    } else {
        int xi = pi.coor[0]; int yi = pi.coor[1]; int zi = pi.coor[2];
        int xf = pf.coor[0]; int yf = pf.coor[1]; int zf = pf.coor[2];
        int mx = (xf+xi)/2;
        int my = (yf+yi)/2;
        int mz = (zf+zi)/2;
        if(xi!=mx && yi!=my && zi!=mz) pd.children[0] = insert({xi,yi,zi},{mx,my,mz},image,output_file);
        if(xi!=mx && yi!=my && mz!=zf) pd.children[1] = insert({xi,yi,mz},{mx,my,zf},image,output_file);
        if(xi!=mx && my!=yf && zi!=mz) pd.children[2] = insert({xi,my,zi},{mx,yf,mz},image,output_file);
        if(xi!=mx && my!=yf && mz!=zf) pd.children[3] = insert({xi,my,mz},{mx,yf,zf},image,output_file);
        if(mx!=xf && yi!=my && zi!=mz) pd.children[4] = insert({mx,yi,zi},{xf,my,mz},image,output_file);
        if(mx!=xf && yi!=my && mz!=zf) pd.children[5] = insert({mx,yi,mz},{xf,my,zf},image,output_file);
        if(mx!=xf && my!=yf && zi!=mz) pd.children[6] = insert({mx,my,zi},{xf,yf,mz},image,output_file);
        if(mx!=xf && my!=yf && mz!=zf) pd.children[7] = insert({mx,my,mz},{xf,yf,zf},image,output_file);
        output_file.seekp(0,ios::end);
        int64_t size = output_file.tellp();
        output_file.write((char*)&pd, sizeof(pixel_des));
        return size;
    }
    return -1;
}

void insert(CImg<unsigned char> &image, string filename){
    int w = image.width();
    int h = image.height();
    int d = image.depth();
    ofstream output_file(filename, ios::binary | ios::trunc);
    insert({0,0,0},{h,w,d},image,output_file);
}

CImg<unsigned char> reconstruir(int w, int h, int d, string filename){
    ifstream input_file(filename, ios::binary);
    pixel_des pd;
    CImg<unsigned char> R(w,h,d,1,0); 
    while(input_file.read((char*)&pd, sizeof(pixel_des))){
        for(int i=pd.pi.coor[0]; i<pd.pf.coor[0]; i++){
            for(int j=pd.pi.coor[1]; j<pd.pf.coor[1]; j++){
                for(int k=pd.pi.coor[2]; k<pd.pf.coor[2]; k++){
                    R(j,i,k) = 255;
                }
            }
        }
    }
    return R;
}