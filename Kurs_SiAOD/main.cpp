//
//  main.cpp
//  Kurs_SiAOD
//
//  Created by Артем on 27.02.2018.
//  Copyright © 2018 Артем. All rights reserved.
//

#include <iostream>
using namespace std;
enum color{RED,BLACK};
class Vertex {
private:
    color color_;
    int value_;
    Vertex *left_, *right_, *parent_;
public:
    Vertex(int,Vertex *);
    int getValue();
    color getColor();
    
    Vertex getLeft();
    Vertex getRight();
    Vertex getParent();
    
    void putValue(int);
    void putColor(bool);
    
    void putLeft(Vertex);
    void putRight(Vertex);
    void putParent(Vertex);
    
};
Vertex::Vertex(int value,Vertex *parent){
    color_  = RED; //Устанавливаем красный цвет
    value_  = value;
    parent_ = parent;
};

class RedBlackTree {
private:
    Vertex *roots_;
public:
    RedBlackTree() {
        roots_=NULL;
    };
    void addNewVertex(int);
    void checkingRedBlackProperties();
    void deleteVertex(int);
};
void RedBlackTree::addNewVertex(int value){
    Vertex *parent = this->roots_;
    Vertex *newVertex = new Vertex (value, NULL);
};
int main(int argc, const char * argv[]) {
    
    //std::cout << "Hello, World!\n";
    return 0;
};

