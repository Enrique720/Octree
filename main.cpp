#include <iostream>
#include <vector>
#include "quadtree.h"
#include <bits/stdc++.h>
using namespace std;
//CImg<char> Get_Cut(p1,p2,p3,p4);


CImg<char> Binarizar(CImg<float> & img, int umbral)
{
    CImg<char> R(img.width(),img.height());
    for(int i=0;i< img.width();i++)
        for(int j=0;j< img.height();j++)
        {
            int r = img(i,j,0);
            int g = img(i,j,1);
            int b = img(i,j,2);
            if ( (r+g+b)/3 > umbral)
                R(i,j) = 255;
            else
                R(i,j) = 0;
        }
    return R;
}
//g++ main.cpp  -L/usr/X11R6/lib -lm -lpthread -lX11

CImg<float> load_3d(){
    int x = 512, y = 512, z = 40;
    CImg<char> R(x,y,z,3);
    ifstream db("db.txt");
    string filename;
    for(int k = 0; k < R.depth(); k++){
        getline(db,filename);
        string temp = "datos cerebros/paciente 1/1/" + filename;
        CImg<float> img (temp.c_str());
        for(int i = 0; i < R.height(); i++){
            for(int j = 0; j < R.width(); j++){
                R(i,j,k,0) = img(i,j,0);
                R(i,j,k,1) = img(i,j,1);
                R(i,j,k,2) = img(i,j,2);
            }
        }
    }
    return R;
}


int main(){
   
    srand(time(NULL));   
   // A.save("in.jpg");
    //CImg<float> B = A.crop(0, 0, 3, 3); 
    //CImg<char> R = Binarizar(A,40);
    load_3d().display();
   // A.display();
    //R.display();

    
    return 0;
}