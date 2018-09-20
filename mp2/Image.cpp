#include "Image.h"


cs225::Image::Image(){

}

void cs225::Image::lighten(){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.l += .1;
      if (png_pixel.l >1 )
      {
        png_pixel.l = 1;
      }
      else if (png_pixel.l <0)
      {
        png_pixel.l = 0;
      }

    }
  }
}


void cs225::Image::lighten	(double amount){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.l += amount;
      if (png_pixel.l > 1)
      {
        png_pixel.l = 1;
      }
      else if (png_pixel.l < 0)
      {
        png_pixel.l = 0;
      }
    }
  }
}

void cs225::Image::darken(){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.l -= .1;
      if (png_pixel.l >1 )
      {
        png_pixel.l = 1;
      }
      else if (png_pixel.l <0)
      {
        png_pixel.l = 0;
      }
    }
  }
}

void cs225::Image::darken(double amount){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.l -= amount;
      if (png_pixel.l > 1)
      {
        png_pixel.l = 1;
      }
      else if (png_pixel.l < 0)
      {
        png_pixel.l = 0;
      }
    }
  }
}

void cs225::Image::saturate(){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.s += .1;
      if (png_pixel.s >1 )
      {
        png_pixel.s = 1;
      }
      else if (png_pixel.s <0)
      {
        png_pixel.s = 0;
      }
    }
  }
}

void cs225::Image::saturate(double amount){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.s += amount;
      if (png_pixel.s > 1)
      {
        png_pixel.s = 1;
      }
      else if (png_pixel.s < 0)
      {
        png_pixel.s = 0;
      }
    }
  }
}

void cs225::Image::desaturate(){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.s -= .1;
      if (png_pixel.s > 1)
      {
        png_pixel.s = 1;
      }
      else if (png_pixel.s < 0)
      {
        png_pixel.s = 0;
      }
    }
  }
}

void cs225::Image::desaturate(double amount){
  for (unsigned x = 0; x <this->width(); x++) {
    for (unsigned y = 0; y <this->height(); y++) {
      HSLAPixel & png_pixel = this->getPixel(x,y);
      png_pixel.s -= amount;
      if (png_pixel.s > 1)
      {
        png_pixel.s = 1;
      }
      else if (png_pixel.s < 0)
      {
        png_pixel.s = 0;
      }
    }
  }
}

void cs225::Image::grayscale(){

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

}
void cs225::Image::rotateColor(double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.h += degrees;
      if(pixel.h>360)
      {
        while(pixel.h>360)
        {
          pixel.h -= 360;
        }
      }
      else if(pixel.h<0){
        while(0>pixel.h)
        {
          pixel.h += 360;
        }
      }
    }
  }
}

void cs225::Image::illinify(){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      if (pixel.h <113.5 || pixel.h>257.5)
      {
        pixel.h = 11;
      }
      else{
        pixel.h = 216;
      }
    }
    }
}


void cs225::Image::scale(double factor){
  PNG png = PNG(*this);
 unsigned int new_width = (this->width()) * factor;
 unsigned int new_height = (this->height()) * factor;
 resize(new_width, new_height);

  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      HSLAPixel & new_pixel = png.getPixel(x/factor,y/factor);
      pixel = new_pixel;
    }
  }
}

void cs225::Image::scale(unsigned w, unsigned h){
double factor =0.0;
if (w/this->width() > h/this->height())
{
  factor = h/this->height();
}
else
{
  factor = w/this->width();
}
  PNG png = PNG(*this);
 unsigned int new_width = (this->width()) * factor;
 unsigned int new_height = (this->height()) * factor;
 resize(new_width, new_height);

  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++){
      HSLAPixel & pixel = this->getPixel(x,y);
      HSLAPixel & new_pixel = png.getPixel(x/factor,y/factor);
      pixel = new_pixel;
    }
  }
}
