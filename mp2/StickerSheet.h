/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

 class StickerSheet{
 public:
   StickerSheet(const cs225::Image &picture, unsigned max);
   StickerSheet(const StickerSheet &other);
   const StickerSheet & operator=(const StickerSheet &other);
   void changeMaxStickers(unsigned max);
   int addSticker (cs225::Image &sticker, unsigned x, unsigned y);
   bool translate (unsigned index, unsigned x, unsigned y);
   void removeSticker (unsigned index);
   cs225::Image * getSticker (unsigned index) const;
   void copy_(const StickerSheet & other);
   void delete_();
   cs225::Image render() const;
   ~StickerSheet();


   unsigned max;
   cs225::Image ** array_image;
   unsigned *x_array;
   unsigned *y_array;
   cs225::Image base_picture;
 };
