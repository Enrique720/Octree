#include "octree.h"
int main(){
    pixel_des temp = {{0, 0, 0}, {3, 3, 3}};
    plano input = {1,0,1,-2};
    if(intersect(input,temp)){
        cout<<"nice"<<endl;
    }else{
        cout<<"F"<<endl;
    }
    auto pts = getPoints(temp,input);
    sort(pts.begin(), pts.end());

    for(point pt:pts){
        cout << "Punto:";
        for(int i=0; i<3; i++)
            cout << ' ' << pt.coor[i];
        cout << '\n';
    }
}
