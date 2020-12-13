//Name: Aastha Lamichhane
//File: Header file of simplified project (sp.h)

#ifndef SP_H
#define SP_H
#include <vector>
#include <fstream>
#include <iostream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

//===========================================================================//
//===========================================================================//
class Circle
{
  public:
    Circle(int x_, int y_, int dx_, int dy_, int r_ = 1, bool color_ = false)
        : x(x_), y(y_), dx(dx_), dy(dy_), color(color_), r(r_)
    {};
    ~Circle() {};
    int getX() const;
    int getY() const;
    int getDx() const;
    int getDy() const;
    int getR() const;
    bool getColor() const;
    void changeColor();
    void setX(int);
    void setY(int);
    void setDx(int);
    void setDy(int);
    //void printCircle(Surface &surface);
    void moveCircle();
  private:
    int x, y, dx, dy; //they should be random.
    int r;
    bool color; //toogle color with different boolean value.
};


//===========================================================================//
//===========================================================================//
class QuadTreeNode
{
  public:
    QuadTreeNode(std::vector <Circle> circles_, int minX_, int minY_, int maxX_, int maxY_, int maxDepth_, int depth_, int t_ = 8, QuadTreeNode * parent_ = NULL, QuadTreeNode * child1_ = NULL, QuadTreeNode * child2_ = NULL, QuadTreeNode * child3_ = NULL, QuadTreeNode * child4_ = NULL)
        : circles(circles_), minX(minX_), minY(minY_), maxX(maxX_), maxY(maxY_),  t(t_), depth(depth_), maxDepth(maxDepth_), parent(parent_), child1(child1_), child2(child2_), child3(child3_), child4(child4_)
    {}; 
    ~QuadTreeNode() {};
    std::vector <Circle> & getCircles();
    QuadTreeNode * getParent() const;
    QuadTreeNode * getChild1() const;
    QuadTreeNode * getChild2() const;
    QuadTreeNode * getChild3() const;
    QuadTreeNode * getChild4() const;
    int getMinX() const;
    int getMinY() const;
    int getMaxX() const;
    int getMaxY() const;
    int getT() const;
    int getDepth() const;
    int getMaxDepth() const;
    void setChild1(QuadTreeNode * c);
    void setChild2(QuadTreeNode * c);
    void setChild3(QuadTreeNode * c);
    void setChild4(QuadTreeNode * c);
    void setCircles(std::vector <Circle> &c);
    void checkCollision();
    void getToChildForCollision();
    void splitNode();
    void split();
    bool recurSplitNode();
    std::vector <Circle> seperateCircles(int, int, int, int);
  private:
    std::vector <Circle> circles;
    QuadTreeNode * parent, * child1, * child2, * child3, * child4;
    int minX, minY, maxX, maxY;
    int t;
    int depth, maxDepth;
};

//===========================================================================//
//===========================================================================//
class QuadTree
{
  public:
    QuadTree(QuadTreeNode * root_)
        : root(root_)
    {};
    ~QuadTree() {};
    QuadTreeNode * getRoot() const;
  private:
    QuadTreeNode * root;
};

//===========================================================================//
//===========================================================================//
#endif
