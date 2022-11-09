#include "vector.hpp"
#include<iostream>
#include<algorithm>
#include <initializer_list>




int main(){

    MyVector<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.pop_back();
    std::cout<<array<<std::endl;
    std::cout<<array.back()<<std::endl;
    std::cout<<*array.begin()<<std::endl;
    try
    {
    std::cout<<array.at(3);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    MyVector<int> second_array{9,8,7,6,5,4,3,2,1};
    array=second_array;
    second_array.erase(second_array.begin()+1,second_array.end()-1);
    second_array.insert(second_array.begin()+1,36);
    std::cout<<second_array<<std::endl;
    std::cout<<array<<std::endl;
    second_array.resize(9);
    std::cout<<second_array<<std::endl;




    return 0;
}