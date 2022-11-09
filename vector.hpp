#pragma once
#include<iostream>
#include<algorithm>
#include <initializer_list>


template<typename T>
class MyVector{
    private:
    size_t size_;
    size_t capacity_;
    T* ptr_;

    void realoc(){
        capacity_*=2;
        auto temp= new T[capacity_];
        std::copy(ptr_,ptr_+size_,temp);
        delete [] ptr_;
        ptr_=temp;
       temp=nullptr;
    }

    public:
    MyVector():capacity_{100},size_{0}{ptr_=new T[capacity_];};

    MyVector(size_t value):capacity_{value},size_{0}{ptr_=new T[capacity_];}

    MyVector(const std::initializer_list<T>& in_list){
        capacity_=2*in_list.size();
        ptr_=new T[capacity_];
        size_=in_list.size();
        std::copy(in_list.begin(),in_list.end(),ptr_);
    }

    MyVector(const MyVector& other):capacity_{other.capacity_},size_{other.size_}{ptr_=new T[capacity_]; std::copy(other.ptr_,other.ptr_+size_,ptr_);}

    MyVector& operator=(const MyVector& other){
        if(&other!=this){
            delete[] ptr_;
            capacity_=other.capacity_; 
            size_=other.size_; 
            ptr_=new T[capacity_];
            std::copy(other.ptr_,other.ptr_+size_,ptr_);} 
        return *this; }

    MyVector(MyVector&& other):capacity_{other.capacity_},size_{other.size_},ptr_{other.ptr_}{other.ptr_=nullptr;}

    MyVector& operator=(MyVector&& other){
        delete[] ptr_;
        capacity_=other.capacity_;
        size_=other.size_;
        ptr_=other.ptr_;
        other.ptr_=nullptr;
        return *this;
    }

    ~MyVector(){delete [] ptr_; size_=0; capacity_=0;}

    /* Methods of the class*/
    MyVector& push_back(T value ){
        if(size_>=capacity_){ realoc(); return *this;}
        ptr_[size_++]=value;
        return *this;
    }

    MyVector& pop_back(){
        if(size_!=0){
            --size_;}
        return *this;
    }
    
    void resize(size_t value){
        if(value>size_){
            for(int i=size_;i<value;i++){
            ptr_[i]=T{};
            }
        size_=value;
        if(size_>=capacity_){realoc();}

    }}

    T &front(){return ptr_[0];}

    T &back(){return ptr_[size_-1];}

    size_t size(){return size_;}

    bool empty(){
        if(size_==0){return true;}
        else{return false;}
    }

    T& operator [](size_t value){
        if(value>=size_||value<0){
            throw std::out_of_range("Non existing index, out of range");
        }
        return ptr_[value]; 
    }

    T& at(size_t value){
        if(value>=size_||value<0){
            throw std::out_of_range("Non existing index, out of range");
        }
        return ptr_[value];

    }

    class Iterator{
        private:
            T* pt;
        public:
        Iterator(T* other):pt{other}{}

        ~Iterator(){pt=nullptr;}

        T& operator*(){return *pt;}
        T* operator->(){return pt;}


        Iterator& operator++(){++pt; return *this;}
        Iterator operator++(int){auto temp=pt; ++pt; return temp;}
        
        Iterator& operator--(){--pt; return *this;}
        Iterator operator--(int){auto temp=pt; --pt; return temp;}
        
        bool operator==(Iterator other){return other.pt==pt;}
        bool operator!=(Iterator other){return other.pt!=pt;}
        Iterator operator+(size_t value){return Iterator{pt+value};}
        Iterator operator-(size_t value){return Iterator{pt-value};}
        size_t operator-(Iterator other){return pt-other.pt;}
        

    };
    Iterator begin(){return Iterator{ptr_};}
    Iterator end(){return Iterator{ptr_+size_};}

    Iterator find(const T& element){
        for(int i=0;i<size_;i++){
            if(ptr_[i]==element){return Iterator{ptr_[i]};}
        }
        return end();
    }

    MyVector& insert(Iterator position, T value){
        if(position==end()){push_back(value); return *this;}
        auto temp_end=end();
        auto temp_behind=end()-1;
        while(temp_end!=position){
            *temp_end=*temp_behind;
            temp_end--;
            temp_behind--;}
            *position=value;
            size_++;
            return *this;
    }

    Iterator erase(Iterator location){
        if(empty()){return end();}
        auto tempL=location;
        auto tempForward=location+1;
        while(tempL!=end()){
           *tempL++=*tempForward++;
        }	
        size_--;	
        return tempL;
    }

    Iterator erase(Iterator from, Iterator to){
        if(empty()){return end();}
        if(to==end()){size_-=to-from; return to;}
        auto tempFrom=from;
        auto tempTo=to;
        while(tempTo!=end()){
            *tempFrom++=*tempTo++;
        }
        size_-=to-from;
        return tempTo;
    }

    friend std::ostream& operator<<(std::ostream& write,MyVector<T>& array){
        write<<"[ ";
        for(int i=0;i<array.size();i++){
            write<<array[i]<<" ";
        }
       write<<"]";
       return write;
    }
};