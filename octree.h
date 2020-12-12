//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H
#define INF 10000000
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
    CImg <unsigned char> R;
    CImg <unsigned char> FinalImg;
public:
    Octree(string _filename): filename{_filename} {
        //readRoot
        ifstream file(filename);
        file.seekg(0,ios::end);
        int amount =file.tellg()/sizeof(pixel_des);
        file.seekg((amount-1)*sizeof(pixel_des));
        file.read((char*)&root,sizeof(pixel_des));
    }
    
    void get_cut(plano &input,uint64_t pos){   
        // load nodo
        pixel_des temp;
        ifstream file(filename);
        file.seekg(pos);
        file.read((char*)&temp,sizeof(pixel_des));
        if(intersect(input, temp)){
            if(temp.isLeaf){
                /*for(){
                    for(){
                        for(){
                            
                        }
                    }
                }*/
            }else{
                for(int i=0;i<8;i++){
                    if(temp.children[i]!=-1){
                        get_cut(input,temp.children[i]);
                    }
                }
            }
        }
    }
//a,b,c,d 

    /*CImg<unsigned char> Get_Cut(point p1, point p2, point p3, point p4, string filename){
        ifstream input_file(filename, ios::binary);
        // Parse points
        CImg<unsigned char> R(w,h,1,1,0);
    }*/

};



#endif //QUADTREE_QUADTREE_H