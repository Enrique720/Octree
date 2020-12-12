#include "octree.h"
int main(){
    pixel_des temp = {0, 3, 0, 3, -1, 1.5};
    plano input = {1,0,0,-4};
    if(intersect(input,temp)){
        cout<<"nice"<<endl;
    }else{
        cout<<"F"<<endl;
    }
}
