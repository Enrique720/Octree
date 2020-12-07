#include <iostream>
#include <vector>
#include "quadtree.h"

using namespace std;


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


int main(){
    CImg<float> A("img3.jpg");
    A.save("in.jpg");
    //CImg<float> B = A.crop(0, 0, 3, 3); 
    //CImg<char> R = Binarizar(A,40);

    A.display();
    //R.display();

    insert(A, 50, "output.txt");
    CImg<float> F = reconstruir(A.width(),A.height(),"output.txt");
    F.display();
    F.save("out.jpg");

    return 1;
}