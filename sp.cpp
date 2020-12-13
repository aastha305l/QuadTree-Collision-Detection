//Name: Aastha Lamichhane
//File: cpp file for simplified project (sp.cpp)

#include "sp.h"
#include <cmath>

//======================================================================//
//all get requests
int Circle::getX() const { return this->x; }
int Circle::getY() const { return this->y; }
int Circle::getDx() const { return this->dx; }
int Circle::getDy() const { return this->dy; }
int Circle::getR() const { return this->r; }
bool Circle::getColor() const { return this->color; }

std::vector <Circle> & QuadTreeNode::getCircles() { return circles; }
QuadTreeNode * QuadTreeNode::getParent() const { return this->parent; }
QuadTreeNode * QuadTreeNode::getChild1() const { return this->child1; }
QuadTreeNode * QuadTreeNode::getChild2() const { return this->child2; }
QuadTreeNode * QuadTreeNode::getChild3() const { return this->child3; }
QuadTreeNode * QuadTreeNode::getChild4() const { return this->child4; }
int QuadTreeNode::getMinX() const { return this->minX; }
int QuadTreeNode::getMinY() const { return this->minY; }
int QuadTreeNode::getMaxX() const { return this->maxX; }
int QuadTreeNode::getMaxY() const { return this->maxY; }
int QuadTreeNode::getT() const { return this->t; }
int QuadTreeNode::getDepth() const { return this->depth; }
int QuadTreeNode::getMaxDepth() const { return this->maxDepth; }

QuadTreeNode * QuadTree::getRoot() const { return this->root; }


//======================================================================//
//ALL SET REQUESTS
void Circle::changeColor() { color = (color) ? false : true; }
void Circle::setX(int x) { this->x = x; }
void Circle::setY(int y) { this->y = y; }
void Circle::setDx(int dx) { this->dx = dx; }
void Circle::setDy(int dy) { this->dy = dy; }

void QuadTreeNode::setChild1(QuadTreeNode * c) { child1 = c; }
void QuadTreeNode::setChild2(QuadTreeNode * c) { child2 = c; }
void QuadTreeNode::setChild3(QuadTreeNode * c) { child3 = c; }
void QuadTreeNode::setChild4(QuadTreeNode * c) { child4 = c; }
void QuadTreeNode::setCircles(std::vector <Circle> &c) { this->circles = c; }


//======================================================================//
void Circle::moveCircle()
{
    if (this->getX() + this->getDx() >= W) this->setDx(this->getDx() * -1);
    else if (this->getX() + this->getDx() <= 0) this->setDx(this->getDx() * -1);
    if (this->getY() + this->getDy() >= H) this->setDy(this->getDy() * -1);
    else if (this->getY() + this->getDy() <= 0) this->setDy(this->getDy() * -1);

    this->setX(this->getX() + this->getDx());
    this->setY(this->getY() + this->getDy());
     
    return;
}


void QuadTreeNode::checkCollision()
{
    int length = this->getCircles().size();
    for (int i = 0; i < length; ++i)
    {
        for (int j = i; j < length; ++j)
        {
            //the distance between the two circles must be less than or equal to the radius of the circle for the circles to collide
            double distance = sqrt(pow((this->circles[i].getX() - this->circles[j].getX()), 2) + pow((this->circles[i].getY() - this->circles[j].getY()), 2));
            if (distance <= ((this->circles[i].getR() + this->circles[j].getR()) * 1.0))
            {
                //they collide
                this->circles[i].changeColor();
                this->circles[j].changeColor();
            }
        }
    }
    
    return;
}

void QuadTreeNode::getToChildForCollision()
{
    if(this->getChild1() == NULL)
    {
        //if there is no child, then that means the circles are on parents, so check whenever the child is NULL
        //also, we can just check the first child.
        this->checkCollision();
    }
    else
    {
        this->getChild1()->getToChildForCollision();
        this->getChild2()->getToChildForCollision();
        this->getChild3()->getToChildForCollision();
        this->getChild4()->getToChildForCollision();
    }
    
    return;
}

//seperates circles from the parent to the given child
std::vector <Circle> QuadTreeNode::seperateCircles(int minX, int minY, int maxX, int maxY)
{
    std::vector <Circle> temp;
    for (int i = 0; i < this->getCircles().size(); ++i)
    {
        Circle tempC = this->circles[i];
        if (tempC.getX() <= maxX && tempC.getX() > minX &&
            tempC.getY() <= maxY && tempC.getY() > minY)
        {
            temp.push_back(tempC);
        }
    }
    
    return temp;
}

//splits a node into four child
void QuadTreeNode::split()
{
    /* window is splitted in this way
      -------------------
      |        |        |
      | Child1 | Child2 |
      |        |        |
      -------------------
      |        |        |
      | Child3 | Child4 |
      |        |        |
      -------------------
     */
    //common variables:
    int minX, minY, maxX, maxY;
    int maxDepth = this->maxDepth - 1;
    int depth = this->depth + 1;
    int t = this->t;
    
    //child1:
    minX = this->minX;
    minY = this->minY;
    maxX = (this->maxX + this->minX) / 2;
    maxY = (this->maxY + this->minY) / 2;
    QuadTreeNode * child1 = new QuadTreeNode(this->seperateCircles(minX, minY, maxX, maxY), minX, minY, maxX, maxY, maxDepth, depth, t, this);
    
    //child2:
    minX = (this->maxX + this->minX) / 2;
    minY = this->minY;
    maxX = this->maxX;
    maxY = (this->maxY + this->minY) / 2;
    QuadTreeNode * child2 = new QuadTreeNode(this->seperateCircles(minX, minY, maxX, maxY), minX, minY, maxX, maxY, maxDepth, depth, t, this);
    
    //child3:
    minX = this->minX;
    minY = (this->maxY + this->minY) / 2;
    maxX = (this->maxX + this->minX) / 2;
    maxY = this->maxY;
    QuadTreeNode * child3 = new QuadTreeNode(this->seperateCircles(minX, minY, maxX, maxY), minX, minY, maxX, maxY, maxDepth, depth, t, this);
    
    //child4:
    minX = (this->maxX + this->minX) / 2;
    minY = (this->maxY + this->minY) / 2;
    maxX = this->maxX;
    maxY = this->maxY;
    QuadTreeNode * child4 = new QuadTreeNode(this->seperateCircles(minX, minY, maxX, maxY), minX, minY, maxX, maxY, maxDepth, depth, t, this);
    
    this->setChild1(child1);
    this->setChild2(child2);
    this->setChild3(child3);
    this->setChild4(child4);
    
    return;
}

//if the node needs to split then calls split functions and returns true
bool QuadTreeNode::recurSplitNode()
{
    if (this->getCircles().size() >= this->getT() && this->maxDepth > 0)
    {
        this->split();
        return true;
    }
    
    return false;
}

//if a node got splitted then checks if the child of the nodes need to be splitted or not - recursive
void QuadTreeNode::splitNode()
{
    if (this->recurSplitNode())
    {
        this->getChild1()->splitNode();
        this->getChild2()->splitNode();
        this->getChild3()->splitNode();
        this->getChild4()->splitNode();
    }
    
    return;
}


