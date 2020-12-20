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
        if(points.size()!=4)return;
        cout<<"hola"<<endl;
        double distX = abs(points[0].coor[0]-points[2].coor[0]);
        cout<<"DISTX"<<distX<<endl;
        double distY = abs(points[2].coor[1]-points[0].coor[1]);        
        cout<<"DISTY"<<distY<<endl;
        double distZ = abs(points[1].coor[2]-points[0].coor[2]);   
        cout<<"DISTZ"<<distZ<<endl;
     
        switch(reflect){
            case 0: {  //XY
                for(int i=0;i<distX;i++){
                    for(int j=0;j<distY;j++){
                        ans(points[0].coor[1]+j,points[1].coor[0]+i)=255; 
                        //ans(j,i) = R(temp.coor[0],temp.coor[1],temp.coor[2]);
                    }
                }                               
            };
            case 1:{   //YZ
                cout<<"llego1"<<endl;
                for(int i=0;i<distY;i++){
                    for(int j=0;j<distZ;j++){

                        ans(points[0].coor[1]+i,points[0].coor[2]+j)=255; 
                        //ans(j,i) = R(temp.coor[0],temp.coor[1],temp.coor[2]);
                    }
                }
            };
            case 2:{   //XZ 
                for(int i=0;i<distX;i++){
                    for(int j=0;j<distZ;j++){
                        ans(points[0].coor[2]+j,points[1].coor[0]+i)=255; 
                        //ans(j,i) = R(temp.coor[0],temp.coor[1],temp.coor[2]);
                    }
                }
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
        cout<<p1.coor[0]<<" "<<p1.coor[1]<<" "<<p1.coor[2]<<endl; 
        cout<<p2.coor[0]<<" "<<p2.coor[1]<<" "<<p2.coor[2]<<endl; 
        cout<<p3.coor[0]<<" "<<p3.coor[1]<<" "<<p3.coor[2]<<endl; 


        plano pl = getPlano(p1, p2, p3);
        cout<<pl.a<<" "<<pl.b<<" "<<pl.c<<" "<<pl.d<<endl;

        auto pts = getPoints({{0,0,0},{h,w,d}},pl);
        sort(pts.begin(), pts.end());
        if(pts.size()==6){
            pts.erase(pts.begin()+2);
            pts.erase(pts.begin()+2);
            
        }
        for(point pt:pts){
            cout << "Punto:";
            for(int i=0; i<3; i++)
                cout << ' ' << pt.coor[i];  
            cout << '\n';
        }
        double umbral = d/w *PI/4;
        cout<<"umbral: "<<umbral<<endl; 
        cout<<"angle1: "<<angle1<<endl;
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
        cout<<"REFLECT IS: "<<reflect<<endl;        
        int wf,df;
        switch (reflect){
            case 0:{
                break;
            };
            case 1: {
                wf = abs(pts[2].coor[1] - pts[1].coor[1]);
                df = abs(pts[1].coor[2] - pts[0].coor[2]);
                break;
            };
            case 2: {
                wf = abs(pts[2].coor[0] - pts[1].coor[0]);     // TODO  
                df = abs(pts[2].coor[2] - pts[1].coor[2]); 
                break;
            }
        }
        //int wf = pts[2].coor[1]-pts[1].coor[1]; //ceil(w*1.0/cos(angle2));
        //int df = pts[1].coor[2]- pts[0].coor[2]; //ceil(d*1.0/sin(angle1));

        cout << wf << ' ' << df << '\n';

        CImg<unsigned char> ans(wf,df,1,1,0);


        file.seekg(0,ios::end);
        int pos = int(file.tellg()) - int(sizeof(pixel_des));
        //get_cut(pl, pos, ans,reflect);
        cout<<"reflect is: "<<reflect<<endl; 
        return ans;
    }

};



#endif //QUADTREE_QUADTREE_H