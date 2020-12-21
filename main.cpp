#include <iostream>
#include <vector>
#include "octree.h"
#include <bits/stdc++.h>
using namespace std;


CImg<unsigned char> Binarizar(CImg<float> & img, int umbral) {
    CImg<unsigned char> R(img.width(),img.height());
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

CImg<unsigned char> load_3d(){
    int x = 512, y = 512, z = 40;
    CImg<unsigned char> R(x,y,z,1);
    ifstream db("db.txt");
    string filename;
    for(int k = 0; k < R.depth(); k++){
        getline(db,filename);
        string temp = "datos cerebros/paciente 1/1/" + filename;
        CImg<float> tmp(temp.c_str());
        CImg<unsigned char> img = Binarizar(tmp, 122);
        for(int i = 0; i < R.height(); i++){
            for(int j = 0; j < R.width(); j++){
                R(i,j,k) = img(i,j);
            }
        }
    }
    return R;
}

void tester(Octree& oct, CImg<unsigned char> &R){
    double ang1, ang2;
    for(int i = 0 ; i < 20; i++){   
        ang1 = (rand()%3000)/1000;
        ang2 = (rand()%3000)/1000;
        CImg<unsigned char> RR = oct.Get_Cut(R.width(), R.height(), R.depth(),  ang1,ang2);         
        //RR.display();
        string filename = "testImg/" +  to_string(i);
        
        filename += ".jpg"; 
        RR.save(filename.c_str()); 
        CImg<unsigned char> RR2 = Get_Cut(R.width(), R.height(), R.depth(),  ang1,ang2,R);         
        string filename2 = "testImgR/" +  to_string(i)+".jpg";

        RR2.save(filename2.c_str());
    }
}


int main(){
    
    srand(time(NULL));   
    //A.save("in.jpg");
    //CImg<float> B = A.crop(0, 0, 3, 3); 
    /*CImg<float> A("datos cerebros/paciente 1/1/Paciente1CC-27-10-1988- CT from 18-01-2011 S0 I0.BMP");
    CImg<unsigned char> R = Binarizar(A,40);
    A.display();
    R.display();
    R.save("out.png");*/
    CImg<unsigned char> R = load_3d();
    cout << sizeof(R) << endl;
    R.display();
    //insert(R, "data.txt");

    Octree oct("data.txt");
    //CImg<unsigned char> RR = oct.Get_Cut(R.width(), R.height(), R.depth(),  0.3,0.3);         
    //RR.display();
    tester(oct,R);
    /*CImg<unsigned char> RR = oct.Get_Cut(R.width(), R.height(), R.depth(),  1,0.3);         
    RR.display(); */

    //CImg<unsigned char> RR2 = Get_Cut(R.width(), R.height(), R.depth(),  0.3,0.3,R);         
    //RR2.display();
    /*CImg<unsigned char> RR = reconstruir(R.width(), R.height(), R.depth(), "data.txt");
    RR.display();*/

    
    //A.display();
    //R.display();

    
    return 0;
}