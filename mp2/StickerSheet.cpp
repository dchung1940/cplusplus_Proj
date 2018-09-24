#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max);
{
    max_= max;
    array_image[max];
    *(array_image[0]) = picture;
}

StickerSheet::StickerSheet(const StickerSheet & other	){
  array_image = NULL;
  copy_(other);
}

const StickerSheet & StickerSheet::operator (const StickerSheet & other)
{
  if (this != &other) { copy_(other); }
  return *this;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
  if (max_ > max)
  {
    max_ = max;
    array_image[max_];
  }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y)
  index = 0;
  while(*(array_image[index]) != NULL)
  {
    image++;
  }
  *(array_image[index]) = sticker;
  x[index] = x;
  y[index] = y;

)

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  x_array[index] = x;
  y_array[index] = y;
  if (index > max-1 || index<0)
  {
    return false;
  }
}

void StickerSheet::removeSticker(unsigned	index)
{
  delete *(array_image[index]);
}

Image * StickerSheet::getSticker	(	unsigned 	index	)	const
{
  if (index > max-1 || index<0)
  {
    return NULL;
  }
  else
  {
    return *(array_image[index]);
  }
}


// Image StickerSheet::render(	)	const
// {
//
// }

const Image StickerSheet::copy_(const StickerSheet & other)
{
  this.max = other.max;
  this.array_image = other.array_image;
  this.x_array = other.x_array;
  this.y_array = other.y_array;
}

StickerSheet::~StickerSheet()
{
  delete x_array;
  delete y_array;
  delete array_image;
}
