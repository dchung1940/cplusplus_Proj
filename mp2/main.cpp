#include "Image.h"
#include "StickerSheet.h"

int main() {
   cs225::Image base_image;
   base_image.readFromFile("goku.png");
   StickerSheet goku = StickerSheet(base_image,3);
   cs225::Image png1,png2,png3;
   png1.readFromFile("Basketball.png");
   png2.readFromFile("Wade.png");
   png3.readFromFile("Volleyball.png");
   png2.scale(1.5);
   png3.scale(2.3);

   goku.addSticker(png1,20,500);
   goku.addSticker(png2,500,550);
   goku.addSticker(png3,780,1020);

   goku.render().writeToFile("myImage.png");



  return 0;
}
