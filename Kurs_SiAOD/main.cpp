//
//  main.cpp
//  Kurs_SiAOD
//
//  Created by Артем on 27.02.2018.
//  Copyright © 2018 Артем. All rights reserved.
//
#include <iostream>
using namespace std;
enum color{
    RED,BLACK
};
class Vertex {
    friend class RedBlackTree;
private:
    color color_;
    int value_;
    Vertex *left_, *right_, *parent_;
protected:
    Vertex(int,Vertex *);
    Vertex();
    int getValue(){
        return value_;
    };
    color getColor(){
        return this->color_;
    };
    
    Vertex *getLeft(){
        return left_;
    };
    Vertex *getRight(){
        return right_;
    };
    Vertex *getParent(){
        return parent_;
    };
    
    void putValue(int);
    void putColor(color newColor){
        if (this->getValue() == 5)
        {
            
        }
        color_=newColor;
    };
    
    void putLeft(Vertex *newLeft){
        left_=newLeft;
    };
    void putRight(Vertex *newRight){
        right_=newRight;
    };
    void putParent(Vertex *newParent){
        parent_=newParent;
    };
    Vertex *getGrandParent();
    Vertex *getUncle();
    void rotateLeft();
    void rotateRight();
    
};
Vertex::Vertex(int value,Vertex *parent){
    color_  = RED; //Устанавливаем всегда красный цвет
    value_  = value;
    parent_ = parent;
    left_   = NULL;
    right_  = NULL;
};
Vertex* Vertex::getGrandParent(){
    if (this->getParent() != NULL)
        return this->getParent()->getParent();
    return NULL;
};
Vertex* Vertex::getUncle(){
    Vertex *grandparent = getGrandParent();
    if ((grandparent == NULL)||(grandparent->getLeft() == NULL)||(grandparent->getRight() == NULL))//Существует ли дядя
        return NULL;
    if (grandparent->getLeft() == getParent())
        return grandparent->getRight();
    else
        return grandparent->getLeft();
};

void Vertex::rotateLeft(){
    
    Vertex *pivot = getRight();
    
    putRight(pivot->getLeft());
    if (pivot->getLeft() != NULL) {
        pivot->getLeft()->putParent(this);
    };
    pivot->putParent(this->getParent());
    if (getParent() != NULL){
        if (this == this->getParent()->getLeft()){
            this->getParent()->putLeft(pivot);
        } else{
            this->getParent()->putRight(pivot);
        }
    }
    pivot->putLeft(this);
    putParent(pivot);
}

void Vertex::rotateRight(){
    
    Vertex *pivot = getLeft();
    
    putLeft(pivot->getRight());
    if (pivot->getRight() != NULL){
        pivot->getRight()->putParent(this);
    };
    pivot->putParent(this->getParent());
    if (getParent() != NULL) {
        if (this == this->getParent()->getLeft())
            this->getParent()->putLeft(pivot);
        else
            this->getParent()->putRight(pivot);
    }
    pivot->putRight(this);
    putParent(pivot);
}

class RedBlackTree{
private:
    Vertex *roots_;
public:
    RedBlackTree() {
        roots_=NULL;
    };
    Vertex * getRoots(){
        return roots_;
    };
    void addNewVertex(int);
    void checkingRedBlackProperties(Vertex *);
    void output(Vertex *start)
    {
        if (start == NULL) {
            //cout<<"Null ";
            return;
        }
        cout <<start->getValue()<< ' ' << ((start->getColor() == RED) ? "R":"B") <<"| ";
        output(start->getLeft());
        output(start->getRight());
        
    };
};

void RedBlackTree::addNewVertex(int value){
    Vertex *parent = this->roots_;
    if (parent == NULL){
        roots_=new Vertex(value, NULL);
        checkingRedBlackProperties(roots_); //Исправление свойства №1
        return;
    }
    
    bool leftRight = false; //false -  левый поворот, true правый
    Vertex *current = parent;
    
    while (current != NULL){
        parent = current;
        if (value < parent    ->getValue()) {
            current = current ->getLeft();
            leftRight = false;
        }
        else
        {
            current = current ->getRight();
            leftRight = true;
        }
    }
    
    Vertex *newVertex = new Vertex(value, parent);
   
        if (leftRight)
            parent->putRight(newVertex);
        else
            parent->putLeft(newVertex);
    checkingRedBlackProperties(newVertex);
};

void RedBlackTree::checkingRedBlackProperties(Vertex *insertedVertex){
    if (insertedVertex ->getParent() == NULL){ //Случай 1 Корень - RED
        insertedVertex ->putColor(BLACK);
        return;
    }
    
    if ((insertedVertex ->getParent()->getColor() == BLACK)) // Случай 2 - предок текущего узла будет всегда существовать
        return;
    
    Vertex* uncle = insertedVertex->getUncle();
    
    if ((uncle != NULL) && (uncle->getColor() == RED)) { //Случай 3 и родитель и дядя Красные
        insertedVertex->getParent()->putColor(BLACK);
        uncle->putColor(BLACK);
        insertedVertex->getGrandParent()->putColor(RED);
        checkingRedBlackProperties(insertedVertex->getGrandParent());
        return;
    }

    if ((insertedVertex == insertedVertex->getParent()->getRight()) && (insertedVertex->getParent() == insertedVertex->getGrandParent()->getLeft())) { //Случай 4 Родитель красный, но дядя Черный
        
        insertedVertex->getParent()->rotateLeft();
        
        insertedVertex = insertedVertex->getLeft();
    } else if ((insertedVertex == insertedVertex->getParent()->getLeft()) && (insertedVertex->getParent() == insertedVertex->getGrandParent()->getRight())) {
        
        insertedVertex->getParent()->rotateRight();
        
        insertedVertex = insertedVertex->getRight();
    }
    //Случай 5
    insertedVertex->getParent()->putColor(BLACK);
    
    insertedVertex->getGrandParent()->putColor(RED);
    
     if ((insertedVertex == insertedVertex->getParent()->getLeft()) && (insertedVertex->getParent() == insertedVertex->getGrandParent()->getLeft())) {
        insertedVertex->getGrandParent()->rotateRight();
    } else {
        insertedVertex->getGrandParent()->rotateLeft();
    }
}
int main(int argc, const char * argv[]) {
    RedBlackTree tree1;
    int vertex[12] = {5,7,4,1,12,8,6,11,9,3,2,10};
    for (int i=0;i<12;i++){
        tree1.addNewVertex(vertex[i]);
        tree1.output(tree1.getRoots());
        cout << endl;
    }
    return 0;
};

