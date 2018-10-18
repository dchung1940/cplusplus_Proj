#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = nullptr;

}

ImageTraversal::Iterator::Iterator(ImageTraversal & t, double tolerance_, PNG some_pic){
  std::cout<<"constructor"<<std::endl;
  current = t.peek();
  tolerance = tolerance_;
  traversal = &t;
  picture = some_pic;
  visited[picture.width()][picture.height()] = {false};
  std::cout<<"end"<<std::endl;

  // for(int i; i<picture.height(); i++)
  // {
  //   for(int j; j<picture.width(); j++)
  //   {
  //     visited[i][j] = false;
  //   }
  // }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //traversal->add(Point(x,y));
  std::cout<<"lol"<<std::endl;
  if(!traversal->empty())
  {
    Point curr= traversal->peek();
    unsigned curr_x = curr.x;
    unsigned curr_y = curr.y;
    visited[curr_x][curr_y] = true;
    HSLAPixel &h = picture.getPixel(curr_x,curr_y);
    curr_x ++;
    HSLAPixel &c = picture.getPixel(curr_x,curr_y);
    double limit_ = calculateDelta(h,c);
    if(visited[curr_x][curr_y]==false && limit_<tolerance && curr_x>=0 && curr_y>=0)
    {
      traversal->add(Point(curr_x,curr_y));
      visited[curr_x][curr_y] = true;
    }

    curr_x --;
    curr_y ++;
    c = picture.getPixel(curr_x,curr_y);
    limit_ = calculateDelta(h,c);
    if(visited[curr_x][curr_y] == false && limit_<tolerance && curr_x>=0 && curr_y>=0)
    {
      traversal->add(Point(curr_x,curr_y));
      visited[curr_x][curr_y] = true;
    }
    curr_y --;
    curr_x --;
    c = picture.getPixel(curr_x,curr_y);
    limit_ = calculateDelta(h,c);
    if(visited[curr_x][curr_y] ==false &&limit_<tolerance && curr_x>=0 && curr_y>=0)
    {
      traversal->add(Point(curr_x,curr_y));
      visited[curr_x][curr_y] = true;
    }

    curr_x ++;
    curr_y --;
    c = picture.getPixel(curr_x,curr_y);
    limit_ = calculateDelta(h,c);
    if(visited[curr_x][curr_y] ==false &&limit_<tolerance && curr_x>=0 && curr_y>=0){
      traversal->add(Point(curr_x,curr_y));
      visited[curr_x][curr_y] = false;
    }

  }
return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if(traversal == NULL){thisEmpty = true;}
  if(other.traversal == NULL) {otherEmpty = true;}

  if(!thisEmpty){ thisEmpty = traversal->empty(); }
  if(!otherEmpty){ otherEmpty = other.traversal->empty();}

  if(thisEmpty && otherEmpty) return false;
  else if ((!thisEmpty)&&(!otherEmpty))
  return (traversal != other.traversal);
  else return true;
}
