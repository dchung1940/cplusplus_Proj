#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double increment)
{
  hue_ = 35;
  increment_ = increment;
  saturation_ = 0;
  alpha_ = 0;
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue_,increment_,saturation_);
  if(x %2 ==0)
  {
  hue_ += increment_; if(hue_> 100) {hue_-=65;};
  saturation_ +=.1;
  alpha_ += .1;
  if(saturation_ == 1)
  {
    saturation_ = 0;
    alpha_ = 0;
  }
  return pixel;
  }
  else
  {
    return pixel;
  }
}
