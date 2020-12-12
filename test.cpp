#include "octree.h"
int main(){
    pixel_des temp = {0, 6, 0, 6, 0, 6};
    plano input = {2,3,0,2};
    if(intersect(input,temp)){
        cout<<"nice"<<endl;
    }else{
        cout<<"F"<<endl;
    }
}
