//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H
#define INF 10000000
#define PI 3.14159265
#include "functions.h"
using namespace cimg_library;

struct plano{
    double a, b,c,d;
};

double getX(plano input,point point){
    if(input.a==0)return INF;
    return -(input.b*point.y+input.c*point.z+input.d)/input.a;
}

double getY(plano input,point point){
    if( input.b==0)return INF;
    return -(input.a*point.x+input.c*point.z+input.d)/input.b;
}
double getZ(plano input,point point){
    if(input.c==0)return INF;
    return -(input.b*point.y+input.a*point.x+input.d)/input.c;
}

bool intersect(plano input, pixel_des quad){
    point initial = {quad.xi,quad.yi,quad.zi};
    point end = {quad.xf,quad.yf,quad.zf};
    if( (input.c==0 || (getZ(input,initial)>=quad.zi) && (getZ(input,end)<=quad.zf) || 
        (getZ(input,initial)<=quad.zf) && (getZ(input,end)>=quad.zi) ) &&
        ( input.b==0|| (getY(input,initial)>=quad.yi) && (getY(input,end)<=quad.yf) || 
        (getY(input,initial)<=quad.yf) && (getY(input,end)>=quad.yi) ) &&
        (input.a==0|| (getX(input,initial)>=quad.xi) && (getX(input,end)<=quad.xf) || 
        (getX(input,initial)<=quad.xf) && (getX(input,end)>=quad.xi))  ) 
    {
        return true;
    }
    return false;
}

plano getPlano(point p1, point p2, point p3){
    plano pl;

    point v1 = p2 - p1;
    point v2 = p3 - p1;
    point cross = v1 * v2;
    point norm = cross.norm();

    pl.a = norm.x;
    pl.b = norm.y;
    pl.c = norm.z;
    pl.d = -(norm.x*p1.x + norm.y*p1.y + norm.z*p1.z);

    return pl;
}

/*bool intersectFB(plano &input, pixel_des &quad){
    for(int i = quad.xi; i < quad.xf; i++){
        for(int j = quad.ji ; j < quad.jf; j++){
            for(int k = quad.ki; k < quad.kf; k++){
                if(input.a*i + input.b*j + input.c*z + d == 0)
                    return true;
            }
        }
    }
    return false;
}*/


class Octree{
    pixel_des root;
    string filename;
    ifstream file;
    CImg <unsigned char> R;
    CImg <unsigned char> FinalImg;
public:

    Octree(string _filename): filename(_filename) {
        //readRoot
        file.open(filename);
        file.seekg(0,ios::end);
        int amount =file.tellg()/sizeof(pixel_des);
        file.seekg((amount-1)*sizeof(pixel_des));
        file.read((char*)&root,sizeof(pixel_des));
    }

    void fill(pixel_des pd, CImg<unsigned char> &ans){
        for(int j=pd.yi; j<pd.yf; j++){
            for(int k=pd.zi; k<pd.zf; k++){
                ans(j,k) = 255;
            }
        }
    }
    
    void get_cut(plano &input, uint64_t pos, CImg<unsigned char> &ans){   
        // load nodo
        pixel_des temp;
        // ifstream file(filename);
        file.seekg(pos);
        file.read((char*)&temp,sizeof(pixel_des));
        //cout << "Punto inicial: " << temp.xi << ' ' << temp.yi << ' ' << temp.zi << '\n';
        //cout << "Punto final: " << temp.xf << ' ' << temp.yf << ' ' << temp.zf << '\n';
        if(intersect(input, temp)){
            //cout << "Leaf: " << temp.isLeaf << '\n';
            if(temp.isLeaf){
                fill(temp, ans);
            }else{
                for(int i=0;i<8;i++){
                    //cout << "children " << i << ": " << i << '\n';
                    if(temp.children[i]!=-1){
                        get_cut(input, temp.children[i], ans);
                    }
                }
            }
        }
    }
//a,b,c,d 

    CImg<unsigned char> Get_Cut(double w, double h, double d, double angle1, double angle2){
        point p1 = {w/2, h/2, d/2};
        point p2 = {w/2 + cos(PI + angle1), h/2, d/2 + sin(PI + angle1)};
        point p3 = {w/2, h/2 + cos(PI + angle2), d/2 + sin(PI + angle2)};

        plano pl = getPlano(p1, p2, p3);

        int wf = 512; //ceil(w*1.0/cos(angle2));
        int df = 512; //ceil(d*1.0/sin(angle1));

        //cout << wf << ' ' << df << '\n';

        CImg<unsigned char> ans(wf,df,1,1,0);

        file.seekg(0,ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        get_cut(pl, pos, ans);

        return ans;
    }

};



#endif //QUADTREE_QUADTREE_H