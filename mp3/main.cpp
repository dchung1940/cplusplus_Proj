#include "List.h"

int main() {
      List<unsigned> list1,list2,list3;
      list1.insertBack(1);
      list1.insertBack(4);
      list1.insertBack(3);
      list1.insertBack(2);
      list1.insertBack(7);
      list1.insertBack(6);


      std::cout << list1 << std::endl;

      list1.sort();
      // List<unsigned> merged(list1, list2);
      std::cout << list1 << std::endl;
    




  return 0;
}
