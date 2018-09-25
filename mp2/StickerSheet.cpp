#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet(const cs225::Image &picture, unsigned max_)
{
    max= max_;
    array_image = new cs225::Image*[max];
    x_array = new unsigned[max];
    y_array = new unsigned[max];
    base_picture = picture;
    for (unsigned i = 0 ; i<max; i++)
    {
      array_image[i] = NULL;
    }
}

StickerSheet::StickerSheet(const StickerSheet & other	){
  copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
  if (this != &other) {
    delete_();
    copy_(other); }
  return *this;
}

void StickerSheet::changeMaxStickers (unsigned max_)
{
  unsigned * xmax_ = new unsigned[max_];
  unsigned * ymax_ = new unsigned[max_];
  cs225::Image ** array_image_max = new cs225::Image*[max_];
if (max_ > max)
{
  for (unsigned i = 0; i<max_; i++)
  {
    if (i <max)
    {
    if(array_image[i] != NULL && i < max)
    {
    xmax_[i] = x_array[i];
    ymax_[i] = y_array[i];
    array_image_max[i] = new cs225::Image;
    *array_image_max[i] = *array_image[i];
    }
    else{
      array_image_max[i] = NULL;
    }
  }
  else{
    array_image_max[i] = NULL;
  }
}
}
else
{
  for (unsigned i=0; i<max_; i++)
  {
    if(array_image[i] != NULL)
    {
    xmax_[i] = x_array[i];
    ymax_[i] = y_array[i];
    array_image_max[i] = new cs225::Image;
    *array_image_max[i] = *array_image[i];
    }
    else{
      array_image_max[i] = NULL;
    }
  }
}
delete_();
x_array=xmax_;
y_array=ymax_;
array_image = array_image_max;
max = max_;
}

int StickerSheet::addSticker(cs225::Image & sticker, unsigned x, unsigned y)
{

  int index = -1;
  for (unsigned i=0; i<max; i++)
  {
    if (array_image[i] == NULL)
    {
      array_image[i] = new cs225::Image();
      *array_image[i] = sticker;
      x_array[i] = x;
      y_array[i] = y;
      index = i;
      i = max;
    }
  }



  if (index == -1 )
  {
    return -1;
  }
  else
  {
    return index;
  }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
if (index < max && array_image[index] != NULL)
{
  x_array[index] = x;
  y_array[index] = y;
  return true;
}
else
{
  return false;
}
}

void StickerSheet::removeSticker(unsigned	index)
{
  if(index<max && array_image[index] != NULL)
  {
    delete array_image[index];
    array_image[index] = NULL;
  }
}

cs225::Image * StickerSheet::getSticker	(	unsigned 	index	)	const
{
  return array_image[index];
}


cs225::Image StickerSheet::render() const
{
  cs225::Image pic = base_picture;

  int x_diff = 0;
  int y_diff = 0;
  double factor =0;
  for(unsigned i=0; i<max; i++)
  {
    if (array_image[i] !=NULL){
      int xtemp = (*array_image[i]).width()+x_array[i] - base_picture.width();
      int ytemp = (*array_image[i]).height()+y_array[i] - base_picture.height();
      if(x_diff < xtemp)
      {
        x_diff = xtemp;
      }
      if(y_diff < ytemp)
      {
        y_diff = ytemp;
      }
    }
  }


  if(x_diff>y_diff)
  {
    factor = double((x_diff + base_picture.width()))/base_picture.width();
  }
  else
  {
    factor = double((y_diff + base_picture.height()))/base_picture.height();
  }
pic.scale(factor);



  for(unsigned i = 0; i<max; i++)
  {
    if(array_image[i] != NULL){
    unsigned x_val = x_array[i];
    unsigned y_val = y_array[i];
    cs225::Image sticker = *array_image[i];
    // if (x_val +sticker.width()> pic.width()){
    //   pic.scale(x_val+sticker.width(),pic.height());
    // }
    // if (y_val +sticker.height()>pic.height())
    // {
    //   pic.scale(pic.width(),y_val+sticker.height());
    //  }



    for(unsigned i =0; i < sticker.width(); i++){
      for(unsigned j = 0; j < sticker.height(); j++){
          cs225::HSLAPixel & base_pixel = pic.getPixel(x_val+i,j+y_val);
          cs225::HSLAPixel & sticker_pixel = sticker.getPixel(i,j);
          if(sticker_pixel.a != 0){
            base_pixel.h = sticker_pixel.h;
            base_pixel.s = sticker_pixel.s;
            base_pixel.l = sticker_pixel.l;
            base_pixel.a = sticker_pixel.a;
          }
        }
      }
    }
  }
  return pic;
}

void StickerSheet::copy_(const StickerSheet & other)
{
  x_array = new unsigned[other.max];
  y_array = new unsigned[other.max];
  array_image = new cs225::Image*[other.max];
  base_picture = other.base_picture;
  max = other.max;

  for(unsigned i = 0; i <max; i++){
    if(other.array_image[i] != NULL)
  {
    x_array[i]= other.x_array[i];
    y_array[i]= other.y_array[i];
    array_image[i] = new cs225::Image;
    *array_image[i] = *other.array_image[i];
  }
  else{
    array_image[i] = NULL;
  }
  }
}

void StickerSheet::delete_()
{
  delete [] x_array;
  delete [] y_array;
  for (unsigned i = 0; i<max;i++)
  {
    delete array_image[i];
  }
  delete [] array_image;
}

StickerSheet::~StickerSheet()
{
  delete_();
}
