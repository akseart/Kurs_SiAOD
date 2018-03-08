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
    Vertex(){
        
    };
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
    if (grandparent == NULL)
        return NULL; // No grandpar ent means no uncle
    if (grandparent->getParent() == grandparent->getLeft())
        return grandparent->getRight();
    else
        return grandparent->getLeft();
};
void Vertex::rotateLeft(){
    Vertex *pivot = getRight();
    
    pivot->putParent(getParent()); /* при этом, возможно, pivot становится корнем дерева */
    if (getParent() != NULL) {
        if (getParent()->getLeft() == this)
            getParent()->putLeft(pivot);
        else
            getParent()->putRight(pivot);
    }
    putRight(pivot->getLeft());
    if (pivot->getLeft() != NULL)
        pivot->getLeft()->putParent(this);
    
    putParent(pivot);
    putLeft(this);
}
void Vertex::rotateRight(){
    
    Vertex *pivot = getLeft();
    
    pivot->putParent(getParent()); /* при этом, возможно, pivot становится корнем дерева */
    if (getParent() != NULL) {
        if (getParent()->getLeft() == this)
            getParent()->putLeft(pivot);
        else
            getParent()->putRight(pivot);
    }
    
    putLeft(pivot->getRight());
    if (pivot->getRight() != NULL)
        pivot->getRight()->putParent(this);
    
    putParent(pivot);
    pivot->putRight(this);
}

class RedBlackTree : private Vertex{
private:
    Vertex *roots_;
public:
    RedBlackTree() {
        roots_=NULL;
    };
    void addNewVertex(int);
    void checkingRedBlackProperties(Vertex *);
    void deleteVertex(int);
};
void RedBlackTree::addNewVertex(int value){
    Vertex *parent = this->roots_;
    bool lefrRight = false;
    if (parent != NULL){
        if (value<parent    ->getValue()) {
            parent = parent ->getLeft();
            lefrRight = false;
        }
        else
        {
            parent = parent->getRight();
            lefrRight = true;
        }
    }
    Vertex *newVertex = new Vertex(value, parent);
    if (parent == NULL){
        roots_=newVertex;
    }
    else{
        if (lefrRight)
            parent->putRight(newVertex);
        else
            parent->putLeft(newVertex);
    }
    checkingRedBlackProperties(newVertex);
};
void RedBlackTree::checkingRedBlackProperties(Vertex *insertedVertex){
    
    if (insertedVertex->getParent() == NULL){ //Когда вставили корень
        insertedVertex->putColor(BLACK);
        return;
    }
    if (insertedVertex ->getParent()->getColor() == BLACK)
        return;
    Vertex* uncle = insertedVertex->getUncle();
    
    if ((uncle != NULL) && (uncle->getColor() == RED)) {
        insertedVertex->getParent()->putColor(BLACK);
        uncle->putColor(BLACK);
        insertedVertex->getGrandParent()->putColor(RED);
        checkingRedBlackProperties(insertedVertex->getGrandParent());
    }
    if ((insertedVertex == insertedVertex->getParent()->getRight()) && (insertedVertex->getParent() == insertedVertex->getGrandParent()->getLeft())) {
        insertedVertex->getParent()->rotateLeft();
        insertedVertex = insertedVertex->getLeft();
    } else if ((insertedVertex == insertedVertex->getParent()->getLeft()) && (insertedVertex->getParent() == insertedVertex->getGrandParent()->getRight())) {
        insertedVertex->getParent()->rotateRight();
        insertedVertex = insertedVertex->getRight();
    }
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
    for (int i=0;i<12;i++)
        tree1.addNewVertex(vertex[i]);
    return 0;
};

