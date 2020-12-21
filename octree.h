//
// Created by suro on 2020-11-13.
//

#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H
#define INF 10000000
#define PI 3.14159265
#include "functions.h"
#include <bits/stdc++.h>
using namespace cimg_library;

struct plano{
    double a, b,c,d;
};

double getX(plano input,point point){
    if(input.a==0)return INF;
    return -(input.b*point.coor[1]+input.c*point.coor[2]+input.d)/input.a;
}
//-0.283404 -0.283404 0.916168 126.78
//449,0   (x,z)

double getY(plano input,point point){
    if( input.b==0)return INF;
    return -(input.a*point.coor[0]+input.c*point.coor[2]+input.d)/input.b;
}
double getZ(plano input,point point){
    if(input.c==0)return INF;
    return -(input.b*point.coor[1]+input.a*point.coor[0]+input.d)/input.c;
}

bool intersect(plano input, pixel_des quad){
    point initial = {quad.pi.coor[0],quad.pi.coor[1],quad.pi.coor[2]};
    point end = {quad.pf.coor[0],quad.pf.coor[1],quad.pf.coor[2]};
    if( (input.c==0 || (getZ(input,initial)>=quad.pi.coor[2]) && (getZ(input,end)<=quad.pf.coor[2]) || 
        (getZ(input,initial)<=quad.pf.coor[2]) && (getZ(input,end)>=quad.pi.coor[2]) ) &&
        ( input.b==0|| (getY(input,initial)>=quad.pi.coor[1]) && (getY(input,end)<=quad.pf.coor[1]) || 
        (getY(input,initial)<=quad.pf.coor[1]) && (getY(input,end)>=quad.pi.coor[1]) ) &&
        (input.a==0|| (getX(input,initial)>=quad.pi.coor[0]) && (getX(input,end)<=quad.pf.coor[0]) || 
        (getX(input,initial)<=quad.pf.coor[0]) && (getX(input,end)>=quad.pi.coor[0]))  ) 
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

    pl.a = norm.coor[0];
    pl.b = norm.coor[1];
    pl.c = norm.coor[2];
    pl.d = -(norm.coor[0]*p1.coor[0] + norm.coor[1]*p1.coor[1] + norm.coor[2]*p1.coor[2]);

    return pl;
}

/*bool intersectFB(plano &input, pixel_des &quad){
    for(int i = quad.pi.coor[0]; i < quad.pf.coor[0]; i++){
        for(int j = quad.ji ; j < quad.jf; j++){
            for(int k = quad.ki; k < quad.kf; k++){
                if(input.a*i + input.b*j + input.c*z + d == 0)
                    return true;
            }
        }
    }
    return false;
}*/

vector<point> getPoints(pixel_des pd, plano pl){
    vector<point> pts;

    double nx, ny, nz;

    if(getX(pl,{0,pd.pi.coor[1],pd.pi.coor[2]}) != INF){
        nx = (-pl.d - pl.b*pd.pi.coor[1] - pl.c*pd.pi.coor[2]) / pl.a;
        if(nx>=pd.pi.coor[0] && nx<=pd.pf.coor[0]) pts.push_back({nx,pd.pi.coor[1],pd.pi.coor[2]});
    }
    if(getX(pl,{0,pd.pi.coor[1],pd.pf.coor[2]}) != INF){
        nx = (-pl.d - pl.b*pd.pi.coor[1] - pl.c*pd.pf.coor[2]) / pl.a;
        if(nx>=pd.pi.coor[0] && nx<=pd.pf.coor[0]) pts.push_back({nx,pd.pi.coor[1],pd.pf.coor[2]});
    }
    if(getX(pl,{0,pd.pf.coor[1],pd.pi.coor[2]}) != INF){
        nx = (-pl.d - pl.b*pd.pf.coor[1] - pl.c*pd.pi.coor[2]) / pl.a;
        if(nx>=pd.pi.coor[0] && nx<=pd.pf.coor[0]) pts.push_back({nx,pd.pf.coor[1],pd.pi.coor[2]});
    }
    if(getX(pl,{0,pd.pf.coor[1],pd.pf.coor[2]}) != INF){
        nx = (-pl.d - pl.b*pd.pf.coor[1] - pl.c*pd.pf.coor[2]) / pl.a;
        if(nx>=pd.pi.coor[0] && nx<=pd.pf.coor[0]) pts.push_back({nx,pd.pf.coor[1],pd.pf.coor[2]});
    }

    if(getY(pl,{pd.pi.coor[0],0,pd.pi.coor[2]}) != INF){
        ny = (-pl.d - pl.a*pd.pi.coor[0] - pl.c*pd.pi.coor[2]) / pl.b;
        if(ny>=pd.pi.coor[1] && ny<=pd.pf.coor[1]) pts.push_back({pd.pi.coor[0],ny,pd.pi.coor[2]});
    }
    if(getY(pl,{pd.pi.coor[0],0,pd.pf.coor[2]}) != INF){
        ny = (-pl.d - pl.a*pd.pi.coor[0] - pl.c*pd.pf.coor[2]) / pl.b;
        if(ny>=pd.pi.coor[1] && ny<=pd.pf.coor[1]) pts.push_back({pd.pi.coor[0],ny,pd.pf.coor[2]});
    }
    if(getY(pl,{pd.pf.coor[0],0,pd.pi.coor[2]}) != INF){
        ny = (-pl.d - pl.a*pd.pf.coor[0] - pl.c*pd.pi.coor[2]) / pl.b;
        if(ny>=pd.pi.coor[1] && ny<=pd.pf.coor[1]) pts.push_back({pd.pf.coor[0],ny,pd.pi.coor[2]});
    }
    if(getY(pl,{pd.pf.coor[0],0,pd.pf.coor[2]}) != INF){
        ny = (-pl.d - pl.a*pd.pf.coor[0] - pl.c*pd.pf.coor[2]) / pl.b;
        if(ny>=pd.pi.coor[1] && ny<=pd.pf.coor[1]) pts.push_back({pd.pf.coor[0],ny,pd.pf.coor[2]});
    }

    if(getZ(pl,{pd.pi.coor[0],pd.pi.coor[1],0}) != INF){
        nz = (-pl.d - pl.a*pd.pi.coor[0] - pl.b*pd.pi.coor[1]) / pl.c;
        if(nz>=pd.pi.coor[2] && nz<=pd.pf.coor[2]) pts.push_back({pd.pi.coor[0],pd.pi.coor[1],nz});
    }
    if(getZ(pl,{pd.pi.coor[0],pd.pf.coor[1],0}) != INF){
        nz = (-pl.d - pl.a*pd.pi.coor[0] - pl.b*pd.pf.coor[1]) / pl.c;
        if(nz>=pd.pi.coor[2] && nz<=pd.pf.coor[2]) pts.push_back({pd.pi.coor[0],pd.pf.coor[1],nz});
    }
    if(getZ(pl,{pd.pf.coor[0],pd.pi.coor[1],0}) != INF){
        nz = (-pl.d - pl.a*pd.pf.coor[0] - pl.b*pd.pi.coor[1]) / pl.c;
        if(nz>=pd.pi.coor[2] && nz<=pd.pf.coor[2]) pts.push_back({pd.pf.coor[0],pd.pi.coor[1],nz});
    }
    if(getZ(pl,{pd.pf.coor[0],pd.pf.coor[1],0}) != INF){
        nz = (-pl.d - pl.a*pd.pf.coor[0] - pl.b*pd.pf.coor[1]) / pl.c;
        if(nz>=pd.pi.coor[2] && nz<=pd.pf.coor[2]) pts.push_back({pd.pf.coor[0],pd.pf.coor[1],nz});
    }
    
    return pts;
}


class Octree{
    pixel_des root;
    string filename;
    ifstream file;
public:

    Octree(string _filename): filename(_filename) {
        //readRoot
        file.open(filename);
        file.seekg(0,ios::end);
        int amount =file.tellg()/sizeof(pixel_des);
        file.seekg((amount-1)*sizeof(pixel_des));
        file.read((char*)&root,sizeof(pixel_des));
    }

    void fill(CImg<unsigned char> &ans,vector<point>points,int reflect){  
        cout<<"------------------"<<endl;
        for( auto it: points){
            cout<<it.coor[0]<<" "<<it.coor[1]<<" "<<it.coor[2]<<" "<<endl;
        }
        int distXmin,distZmin,distYmin;
        distXmin=distZmin=distYmin=1000;
        int distXmax=0,distYmax=0,distZmax=0;
        for(auto it:points){
            distXmin=min(distXmin,int(it.coor[0]));
            distYmin=min(distYmin,int(it.coor[1]));
            distZmin=min(distZmin,int( it.coor[2]));
            distXmax = max(distXmax,int(it.coor[0]));
            distYmax = max(distYmax,int(it.coor[1]));
            distZmax = max(distZmax,int(it.coor[2]));
        }
        int distX = (abs(distXmax-distXmin));
        int distY = (abs(distYmax-distYmin));        
        int distZ = (abs(distZmax-distZmin));   
     
        switch(reflect){
            case 0: {  //XY
                for(int i=0;i<distX;i++){
                    for(int j=0;j<distY;j++){
                        ans(distXmin+i,distYmin+j)=255; 
                    }
                }    
                break;                           
            };
            case 1:{   //YZ
                for(int i=0;i<distY;i++){
                    for(int j=0;j<min(distZ,39-distZmin);j++){
                        ans(distYmin+i,distZmin+j)=255; 
                    }
                }
                break; 
            };
            case 2:{   //XZ 
                for(int i=0;i<distX;i++){
                    for(int j=0;j<min(distZ,39-distZmin);j++){
                        ans(distXmin+i,distZmin+j )=255; 
                    }
                }
                break; 
            }
        }
        
    }
    
    void get_cut(plano &input, uint64_t pos, CImg<unsigned char> &ans,int &reflect){   
        pixel_des temp;
        file.seekg(pos);
        file.read((char*)&temp,sizeof(pixel_des));
        if(intersect(input, temp)){
            //cout << "Leaf: " << temp.isLeaf << '\n';
            if(temp.isLeaf){
                auto pts = getPoints({temp.pi,temp.pf},input);
                if(pts.size()==6){
                    pts.erase(pts.begin()+2);
                    pts.erase(pts.begin()+2);
                }
                fill(ans,pts,reflect);
            }else{
                for(int i=0;i<8;i++){
                    //cout << "children " << i << ": " << i << '\n';
                    if(temp.children[i]!=-1){
                        get_cut(input, temp.children[i], ans,reflect);
                    }
                }
            }
        }
    }
//a,b,c,d 

    CImg<unsigned char> Get_Cut(double w, double h, double d, double angle1, double angle2){
        //obtenemos los puntos y el plano que intersectan con el poliedro
        point p1 = {w/2, h/2, d/2};
        point p2 = {w/2 + cos(PI + angle1), h/2, d/2 + sin(PI + angle1)};
        point p3 = {w/2, h/2 + cos(PI + angle2), d/2 + sin(PI + angle2)};
        plano pl = getPlano(p1, p2, p3);

        auto pts = getPoints({{0,0,0},{h,w,d}},pl);
        //se obtiene el plano por el cual vamos a hacer la reflexion.
        double umbral = d/w *PI/4;
        int reflect=1;
        if(angle1<=umbral && angle2<=umbral ){
            reflect=0;
        }else if(angle1>umbral && angle2< umbral) {
            reflect=1; 
        }else if(angle1<umbral && angle2>umbral) {
            reflect=2;
        }else if(angle1>angle2){
            reflect=1;
        }else{
            reflect=2;
        }
        int wf=1000,df=1000,wfmax=0,dfmax=0;
        //se crea la imagen con respecto a la reflexion
        auto points = getPoints({{0,0,0},{h,w,d}},pl);
        int distXmin,distZmin,distYmin;
        distXmin=distZmin=distYmin=1000;
        int distXmax=0,distYmax=0,distZmax=0;
        for(auto it:points){
            cout<<"point:"<<it.coor[0]<<" "<<it.coor[1]<<" "<<it.coor[2]<<endl;
            distXmin=min(distXmin,int(it.coor[0]));
            distYmin=min(distYmin,int(it.coor[1]));
            distZmin=min(distZmin,int( it.coor[2]));
            distXmax = max(distXmax,int(it.coor[0]));
            distYmax = max(distYmax,int(it.coor[1]));
            distZmax = max(distZmax,int(it.coor[2]));
        }
        int distX = (abs(distXmax-distXmin));
        int distY = (abs(distYmax-distYmin));        
        int distZ = (abs(distZmax-distZmin));   
        
        switch (reflect){
            case 0:{
                wf = distX;
                df = distY;
                break;
            };
            case 1: {
                wf = distY;
                df = distZ;
                break;
            };
            case 2: {

                wf = distX;
                df = distZ;
                break;
            }
        }
        CImg<unsigned char> ans(wf,df,1,1,0);
        //se llama a la funcion que realiza todo el pintado de la nueva imagen
        file.seekg(0,ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        get_cut(pl, pos, ans,reflect);
        return ans;
    }

};

CImg<unsigned char> Get_Cut(double w, double h, double d, double angle1, double angle2,CImg<unsigned char> &InitImage){
        point p1 = {w/2, h/2, d/2};
        point p2 = {w/2 + cos(PI + angle1), h/2, d/2 + sin(PI + angle1)};
        point p3 = {w/2, h/2 + cos(PI + angle2), d/2 + sin(PI + angle2)};
        plano pl = getPlano(p1, p2, p3);

        auto pts = getPoints({{0,0,0},{h,w,d}},pl);
        //se obtiene el plano por el cual vamos a hacer la reflexion.
        double umbral = d/w *PI/4;
        int reflect=1;
        if(angle1<=umbral && angle2<=umbral ){
            reflect=0;
        }else if(angle1>umbral && angle2< umbral) {
            reflect=1; 
        }else if(angle1<umbral && angle2>umbral) {
            reflect=2;
        }else if(angle1>angle2){
            reflect=1;
        }else{
            reflect=2;
        }
        int wf=1000,df=1000,wfmax=0,dfmax=0;
        //se crea la imagen con respecto a la reflexion
        auto points = getPoints({{0,0,0},{h,w,d}},pl);
        int distXmin,distZmin,distYmin;
        distXmin=distZmin=distYmin=1000;
        int distXmax=0,distYmax=0,distZmax=0;
        for(auto it:points){
            cout<<"point:"<<it.coor[0]<<" "<<it.coor[1]<<" "<<it.coor[2]<<endl;
            distXmin=min(distXmin,int(ceil(it.coor[0])));
            distYmin=min(distYmin,int(ceil(it.coor[1])));
            distZmin=min(distZmin,int(ceil( it.coor[2])));
            distXmax = max(distXmax,int(ceil(it.coor[0])));
            distYmax = max(distYmax,int(ceil(it.coor[1])));
            distZmax = max(distZmax,int(ceil(it.coor[2])));
        }
        int distX = (abs(distXmax-distXmin));
        int distY = (abs(distYmax-distYmin));        
        int distZ = (abs(distZmax-distZmin));   
        
        switch (reflect){
            case 0:{
                wf = distX;
                df = distY;
                break;
            };
            case 1: {
                wf = distY;
                df = distZ;
                break;
            };
            case 2: {

                wf = distX;
                df = distZ;
                break;
            }
        }
        cout<<" --------"<<endl;
        cout<<wf<<" "<<df<<endl; 
        CImg<unsigned char> ans(wf,df,1,1,0);
        cout<<reflect<<endl;
        cout<<"plano es: "<< pl.a<<" "<<pl.b <<" "<<pl.c<<" "<<pl.d<<endl;
        switch(reflect){
            case 0: {  //XY
                for(int i=0;i<distX;i++){
                    for(int j=0;j<distY;j++){
                        cout<<distXmin+i<<"  "<<distYmin+j<<endl;
                        cout<<int(getZ(pl,{distXmin+i,distZmin+j,0}))<<endl;
                        InitImage(distXmin+i,distYmin+j,ceil(getZ(pl,{distXmin+i,distYmin+j,0})));
                        cout<<"hola"<<endl;
                        ans(distXmin+i,distYmin+j)=InitImage(distXmin+i,distYmin+j,ceil(getZ(pl,{distXmin+i,distYmin+j,0}))); 
                    }
                }    
                break;                           
            };
            case 1:{   //YZ
                for(int i=0;i<distY;i++){
                    for(int j=0;j<min(distZ,39-distZmin);j++){
                        ans(distYmin+i,distZmin+j)=InitImage(ceil(getX(pl,{0,distYmin+i,distZmin+j})),distYmin+i,distZmin+j); 
                    }
                }
                break; 
            };
            case 2:{   //XZ 
                for(int i=0;i<distX;i++){
                    for(int j=0;j<min(distZ,39-distZmin);j++){
                        //cout<<distXmin+i<<"  "<<distZmin+j<<endl;
                        //cout<<int(getY(pl,{distXmin+i,0,distZmin+j}))<<endl;
                        int y =max(0, int(ceil(getY(pl,{distXmin+i,0,distZmin+j}))));
                        
                        //ans(distXmin+i,distZmin+j )=InitImage(distXmin+i,ceil(getY(pl,{distXmin+i,0,distZmin+j})),distZmin+j); 
                        ans(distXmin+i,distZmin+j )=InitImage(distXmin+i,y,distZmin+j); 

                    }//449 0 
                }
                break; 
            }
        }
        //ans.display();
        //cout<<reflect<<endl;
        return ans;

        
}

#endif //QUADTREE_QUADTREE_H