#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  PNG* input_photo = new PNG();
  input_photo-> readFromFile(inputFile);

  PNG* output_photo = new PNG(input_photo->width() , input_photo->height());

  for (unsigned x = 0; x < input_photo->width(); x++) {
    for (unsigned y = 0; y < input_photo->height(); y++) {
      output_photo->getPixel(x,y) = input_photo -> getPixel(input_photo ->width() - x-1, input_photo -> height()-1- y);

    }
  }
  output_photo -> writeToFile(outputFile);
  delete input_photo;
  delete output_photo;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);

  for (unsigned x = 0; x <png.width()/4; x++) {
    for (unsigned y = 0; y <png.height()/4; y++) {
      HSLAPixel & png_pixel = png.getPixel(x,y);
      png_pixel.h = 50;
      png_pixel.s = .2;
      png_pixel.l = .2;
      png_pixel.a = .2;

    }
  }
  for (unsigned x = png.width()/4; x <png.width()/2; x++) {
    for (unsigned y = png.height()/4; y <png.height()/2; y++) {
      HSLAPixel & png_pixel = png.getPixel(x,y);
      png_pixel.h = 125;
      png_pixel.s = .1;
      png_pixel.l = .1;
      png_pixel.a = .1;
    }
  }
  for (unsigned x = png.width()/2; x <png.width()/4*3; x++) {
    for (unsigned y = png.height()/2; y <png.height()/4*3; y++) {
      HSLAPixel & png_pixel = png.getPixel(x,y);
      png_pixel.h = 116;
      png_pixel.s = .5;
      png_pixel.l = .5;
      png_pixel.a = .5;
    }
  }
  for (unsigned x = png.width()/2; x <png.width()/4*3; x++) {
    for (unsigned y = png.height()/4; y <png.height()/2; y++) {
        HSLAPixel & png_pixel = png.getPixel(x,y);
        png_pixel.h = 296;
        png_pixel.s = .5;
        png_pixel.l = .5;
        png_pixel.a = .5;
      }

  }
  for (unsigned x = (png.width()/4)*3; x <png.width(); x++) {
    for (unsigned y = (png.height()/4)*3; y <png.height(); y++) {
      HSLAPixel & png_pixel = png.getPixel(x,y);
      png_pixel.h = 250;
      png_pixel.s = .9;
      png_pixel.l = .9;
      png_pixel.a = .9;
    }
  }


  return png;
}
