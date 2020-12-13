//Name: Aastha Lamichhane
//File: main.cpp

#include <iostream>
#include <ctime>
#include "sp.h"

//===========================================================================//
//calls moveCircle for each circle
void callMoveCircle(std::vector <Circle> & c)
{
    for (int i = 0; i < c.size(); ++i)
    {
        c[i].moveCircle();
    }
    return;
}

//===========================================================================//
//prints line on the surface
void printLine(Surface & surface, int x0, int y0, int x1, int y1)
{
    surface.put_line(x0, y0, x1, y1, 255, 255, 255);
    return;
}

//===========================================================================//
//finds the coordinates and calls putLine function
void callPrintLine(Surface & surface, const QuadTreeNode *q)
{
    int minX = q->getMinX();
    int minY = q->getMinY();
    int maxX = q->getMaxX();
    int maxY = q->getMaxY();

    printLine(surface, minX, minY, maxX, minY);
    printLine(surface, minX, minY, minX, maxY);
    //printLine(surface, minX, maxY, maxX, maxY);
    //printLine(surface, maxX, minY, maxX, maxY);

    return;
}

//===========================================================================//
//prints circle on the surface
void printCircle(Surface & surface, const std::vector <Circle> & c)
{
    for (int i = 0; i < c.size(); ++i)
    {
        int r = 255, g = 0, b = 0;
        Circle temp = c[i];
        if (temp.getColor()) { r = 0; g = 255; b = 255; }
        surface.put_circle(temp.getX(), temp.getY(), temp.getR(), r, g, b);
    }

    return;
}

//===========================================================================//
//on every child node calls printCircle and printLine
void printSurface(Surface & surface, QuadTreeNode * q)
{
    if (q->getChild1() == NULL)
    {
        //print circles and line;
        printCircle(surface, q->getCircles());
        callPrintLine(surface, q);
    }
    else
    {    
        printSurface(surface, q->getChild1());
        printSurface(surface, q->getChild2());
        printSurface(surface, q->getChild3());
        printSurface(surface, q->getChild4());
    }
    
    return;
}

//===========================================================================//
//to see the collision without the use of QuadTree
void collisionWithoutQT(std::vector <Circle> & circle)
{
    for (int i = 0; i < circle.size(); ++i)
    {
        for (int j = i; j < circle.size(); ++j)
        {
            Circle fcircle = circle[i]; //first circle
            Circle scircle = circle[j]; //second circle
            //the distance between the two circles must be less than or equal to the radius of the circle for the circles to collide
            double distance = sqrt(pow((fcircle.getX() - scircle.getX()), 2) + pow((fcircle.getY() - scircle.getY()), 2));
            if (distance <= ((fcircle.getR() + scircle.getR()) * 1.0))
            {
                //they collide
                circle[i].changeColor();
                circle[j].changeColor();
            }
        }
    }
    return;
}

//===========================================================================//
int main()
{   
    srand((unsigned int) time(NULL));
    std::vector <Circle> circles;
    int n = 5000;
    Event event;
    Surface surface(W, H);
    int count = 0;
 
    //creating first circles
    for (int i = 0; i < n; ++i)
    {
        Circle circle(rand() % W, rand() % H, rand() % 10 + 5, rand() % 10 + 5, 2);
        circles.push_back(circle);
    }
    bool useQuadTree = true;
    
    while(count <= 1000)
    //while(1)
    {
        if (event.poll() && event.type() == QUIT) break;
        
        KeyPressed keypressed = get_keypressed();
        if (keypressed[RIGHTARROW]) useQuadTree = true;
        else if (keypressed[LEFTARROW]) useQuadTree = false;
        
        if (!useQuadTree)
        {
            collisionWithoutQT(circles);
            surface.lock();
            surface.fill(BLACK);
            printCircle(surface, circles);
            surface.unlock();
            surface.flip();
        }
        else
        {
            //creating the node
            QuadTree * node = new QuadTree(new QuadTreeNode(circles, 0, 0, W, H, 10, 0, 10));
            node->getRoot()->splitNode();
            node->getRoot()->getToChildForCollision();
        
            surface.lock();
            surface.fill(BLACK);
            printSurface(surface, node->getRoot());
            surface.unlock();
            surface.flip();
        }
        callMoveCircle(circles);
        ++count;
        delay(100);
    }
    
    return 0;
}
