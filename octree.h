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
        // load nodo
        pixel_des temp;
        // ifstream file(filename);
        file.seekg(pos);
        file.read((char*)&temp,sizeof(pixel_des));
        //cout << "Punto inicial: " << temp.pi.coor[0] << ' ' << temp.pi.coor[1] << ' ' << temp.pi.coor[2] << '\n';
        //cout << "Punto final: " << temp.pf.coor[0] << ' ' << temp.pf.coor[1] << ' ' << temp.pf.coor[2] << '\n';
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
        point p1 = {w/2, h/2, d/2};
        point p2 = {w/2 + cos(PI + angle1), h/2, d/2 + sin(PI + angle1)};
        point p3 = {w/2, h/2 + cos(PI + angle2), d/2 + sin(PI + angle2)};
        plano pl = getPlano(p1, p2, p3);

        auto pts = getPoints({{0,0,0},{h,w,d}},pl);
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
        switch (reflect){
            case 0:{
                for(auto it:pts){
                    if (wf>it.coor[0])wf=it.coor[0];
                    if (wfmax<it.coor[0])wfmax =it.coor[0];
                    if (df>it.coor[1])df=it.coor[1];
                    if (dfmax<it.coor[1])dfmax=it.coor[1];
                }
                wf = wfmax-wf;
                df = dfmax-df;
                break;
            };
            case 1: {
                for(auto it:pts){
                    if (wf>it.coor[1])wf=it.coor[1];
                    if (wfmax<it.coor[1])wfmax =it.coor[1];
                    if (df>it.coor[2])df=it.coor[2];
                    if (dfmax<it.coor[2])dfmax=it.coor[2];
                }
                wf = wfmax-wf;
                df = dfmax-df;
                break;
            };
            case 2: {
                for(auto it:pts){
                    if (wf>it.coor[0])wf=it.coor[0];
                    if (wfmax<it.coor[0])wfmax =it.coor[0];
                    if (df>it.coor[2])df=it.coor[2];
                    if (dfmax<it.coor[2])dfmax=it.coor[2];
                }
                wf = wfmax-wf;
                df = dfmax-df;
                break;
            }
        }
        CImg<unsigned char> ans(wf,df,1,1,0);


        file.seekg(0,ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        get_cut(pl, pos, ans,reflect);
        return ans;
    }

};



#endif //QUADTREE_QUADTREE_H