/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze(){
  width_ = 0;
  height_ = 0;
  // srand(time(NULL));

}

void SquareMaze::makeMaze(int width,int height){

  width_ = width;
  height_ = height;
  maze_squares.addelements(width_*height_);

  //Creating walls
  setWall_right = vector<bool>(width_*height_,true);
  setWall_down = vector<bool>(width_*height,true);
  for (int i = 0; i<width_; i++)
  {
    for (int j = 0; j< height_; j++)
    {
      // if(j != width_-1) //No need for walls in the perimeter
      // {
      vector<int> right_{i,j,0}; // 0 bit is the right wall
      edges.push_back(right_);
      // }

      // if(i != height_ -1) // No need for walls in the perimeter
      // {
      vector<int> down_{i,j,1}; // 1 bit is the down wall
      edges.push_back(down_);
      // }
    }
  }
  // std::cout<<"1"<<std::endl;
 //deleting walls randomly
 // srand(time(NULL));
 // std::cout<<rand()<<std::endl;
  while (maze_squares.size(0) != width_*height_)
  {
    // std::cout<<maze_squares.size(0)<<std::endl;
     // std::cout<<"the union size is "<< maze_squares.size(0)<<std::endl;
    int rand_size = rand() % (edges.size());

    // std::cout<<rand_size<<std::endl;
    vector<int> temp= edges[rand_size];
    if((temp[0] == width_-1 && temp[2]==0) || (temp[1] == height_-1 && temp[2]==1))
      continue;
    // edges[rand_size] = edges[edges.size()-1];
    // edges.pop_back();
    int first_elem;
    int second_elem;
    int curr_index = width_*temp[1]+temp[0];
    if(temp[2] == 0)
    {
    // std::cout<<"1"<<std::endl;
    first_elem = maze_squares.find(curr_index);
    second_elem = maze_squares.find(curr_index+1);
    }
    else
    {
      // std::cout<<"2"<<std::endl;
    first_elem = maze_squares.find(curr_index);
    second_elem = maze_squares.find(curr_index+width_);
    }
    //Checks whether there's a cycle or not
    if (first_elem != second_elem)
    {
      // std::cout<<"3"<<std::endl;
      maze_squares.setunion(first_elem,second_elem);
      edges[rand_size] = edges[edges.size()-1];
      edges.pop_back();
      setWall(temp[0],temp[1],temp[2],false);

    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  int x_ = x;
  int y_ = y;
  int curr_index = width_*y + x;
  if(x_<0 || y_<0 || x_>= width_ || y_ >= height_)
    return false;
  if(dir == 0)
  {
    if(x_+1 < width_)
    {
     if(setWall_right[curr_index] == false)
        return true;
    }
  }
  else if(dir == 1)
  {
    if(y_+1 < height_)
    {
     if(setWall_down[curr_index] == false)
        return true;
    }
  }
  else if(dir == 2)
  {
    if(x_-1 >= 0)
    {
     if(setWall_right[curr_index -1] == false)
        return true;
    }
  }

  else if(dir == 3)
  {
    if(y_-1 >= 0)
    {
     if(setWall_down[curr_index -width_] == false)
        return true;
    }
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int curr_index = y*width_ + x;
  if(dir == 0)
  {
    setWall_right[curr_index] = exists;
  }
  if(dir == 1)
  {
    setWall_down[curr_index] = exists;
  }

}

vector<int> SquareMaze::solveMaze(){
map<int, int> path_ways;
vector<bool> visited = vector<bool>(width_*height_,false);
vector<vector<int>> count;
vector<int> init = {0,0,0}; // x, y, and index
count.push_back(init);
while(!count.empty())
{
  // int curr_index = x+width_*y;
  vector<int> temp = count.back();
  count.pop_back();
  int curr_x = temp[0];
  int curr_y = temp[1];
  int curr_index = temp[2];
  // std::cout<<curr_index<<std::endl;
  visited[curr_index] = true;
  for(int i=0; i<4; i++)
  {
    int next_cell;
    int temp_x = curr_x;
    int temp_y = curr_y;
    if(i==0)
      temp_x += 1;
    else if (i ==1)
      temp_y += 1;
    else if (i ==2)
      temp_x -= 1;
    else
      temp_y -= 1;

    next_cell = temp_x + temp_y*width_;

    if(next_cell >=0 && next_cell < width_*height_)
    {
      if(canTravel(curr_x,curr_y,i))
      {
        if(visited[next_cell] == false)
        {

          // std::cout<<"goes to "<<next_cell<<std::endl;
          path_ways[next_cell]=curr_index;
          vector<int> temp_vect = {temp_x, temp_y, next_cell};
          count.push_back(temp_vect);
          visited[next_cell] = true;
        }
      }
    }
  }
}



int max_dist = 0;
int begin = 0;
int end, end_one;
int cell_exit;
for (int i =0; i< width_; i++)
{
  end = i+(height_-1)*width_;
  end_one = end;
  int dist_counter = 0;
  while(begin != end)
  {
    dist_counter += 1;
    // std::cout<<end<<std::endl;
    end = path_ways[end];
    // std::cout<<dist_counter<<endl;
  }
  // std::cout<<"new path"<<std::endl;
  if(dist_counter>max_dist)
  {
    cell_exit = end_one;
    max_dist = dist_counter;
    // std::cout<<"hey"<<std::endl;
  }
}
// std::cout<<cell_exit<<std::endl;
stack<int> cell_stack;
cell_stack.push(cell_exit);
while(cell_exit != begin)
{
  // std::cout<<cell_exit<<std::endl;
  cell_exit = path_ways[cell_exit];
  cell_stack.push(cell_exit);
}

int temp_1 = cell_stack.top();
cell_stack.pop();
while(!cell_stack.empty())
{
  int temp_2 = cell_stack.top();
  cell_stack.pop();
  if(temp_2-temp_1 == 1)
    path_finder.push_back(0);
  else if (temp_2 - temp_1 == width_)
    path_finder.push_back(1);
  else if (temp_2 - temp_1 == -1)
    path_finder.push_back(2);
  else if (temp_2 - temp_1 == -width_)
    path_finder.push_back(3);

  temp_1 = temp_2;
}

return path_finder;

}

//thought you can't change the values inside the const function?
PNG * SquareMaze::drawMaze() const{
int new_width = width_*10+1;
int new_height = height_*10+1;
PNG* image = new PNG(new_width,new_height);
for (int j=0; j<new_height; j++)
{
  // image->getPixel(0,j)->h = 0;
  // image->getPixel(0,j)->s = 0;
  image->getPixel(0,j).l = 0;
  // image->getPixel(0,j)->a = 0;
}
for (int i=10; i<new_width; i++){
  image->getPixel(i,0).l = 0;
}
for (int x=0; x<width_; x++)
{
  for(int y=0; y<height_; y++)
  {
    int curr_index = y*width_+x;
    if(setWall_right[curr_index])
    {
      int new_x = (x+1)*10;
      for(int k=0; k<=10; k++)
      {
        int new_y = (y*10)+k;
        image->getPixel(new_x,new_y).l = 0;
      }
    }

    if(setWall_down[curr_index])
    {
      int new_y = (y+1)*10;
      for(int k=0; k<=10; k++)
      {
        int new_x = x*10+k;
        image->getPixel(new_x,new_y).l = 0;
      }
    }
  }
}

return image;
}

PNG * SquareMaze::drawMazeWithSolution(){
PNG * image = drawMaze();
int curr_x = 5;
int curr_y = 5;
for(auto itr = path_finder.begin(); itr<path_finder.end(); itr++)
{
  // std::cout<<*itr<<std::endl;
  if(*itr == 0)
  {
    for(int i=0; i<=10; i++)
    {
    image->getPixel(curr_x+i,curr_y).h = 0;
    image->getPixel(curr_x+i,curr_y).s = 1;
    image->getPixel(curr_x+i,curr_y).l = 0.5;
    image->getPixel(curr_x+i,curr_y).a = 1;
    // std::cout<<curr_x+i<<","<<curr_y<<std::endl;
    }

    curr_x += 10;
  }
  else if (*itr == 1)
  {
    for(int i=0; i<=10; i++)
    {
    image->getPixel(curr_x,curr_y+i).h = 0;
    image->getPixel(curr_x,curr_y+i).s = 1;
    image->getPixel(curr_x,curr_y+i).l = 0.5;
    image->getPixel(curr_x,curr_y+i).a = 1;
    // std::cout<<curr_x<<","<<curr_y+i<<std::endl;
    }
    curr_y += 10;
  }
  else if (*itr == 2)
  {
    for(int i=0; i<=10; i++)
    {
    image->getPixel(curr_x-i,curr_y).h = 0;
    image->getPixel(curr_x-i,curr_y).s = 1;
    image->getPixel(curr_x-i,curr_y).l = 0.5;
    image->getPixel(curr_x-i,curr_y).a = 1;
    // std::cout<<curr_x-i<<","<<curr_y<<std::endl;
    }
    curr_x -= 10;
  }
  else if (*itr == 3)
  {
    for(int i=0; i<=10; i++)
    {
    image->getPixel(curr_x,curr_y-i).h = 0;
    image->getPixel(curr_x,curr_y-i).s = 1;
    image->getPixel(curr_x,curr_y-i).l = 0.5;
    image->getPixel(curr_x,curr_y-i).a = 1;
    // std::cout<<curr_x<<","<<curr_y-i<<std::endl;

    }
    curr_y -= 10;
  }
}
  curr_x -=5;
  curr_y +=5;

  for (int i =1; i<=9; i++){
    image->getPixel(curr_x+i,curr_y).h = 1;
    image->getPixel(curr_x+i,curr_y).s = 1;
    image->getPixel(curr_x+i,curr_y).l = 1;
    image->getPixel(curr_x+i,curr_y).a = 1;
  }
return image;

}

// PNG SquareMaze::drawCreativeMaze(PNG image) const{
// int new_width = image.width();
// int new_height = image.height();
//   for (int j=0; j<new_height; j++)
//   {
//     // image->getPixel(0,j)->h = 0;
//     // image->getPixel(0,j)->s = 0;
//     image.getPixel(0,j).l = 1;
//     // image->getPixel(0,j)->a = 0;
//   }
//   for (int i=10; i<new_width; i++){
//     image.getPixel(i,0).l = 1;
//   }
//   for (int x=0; x<width_; x++)
//   {
//     for(int y=0; y<height_; y++)
//     {
//       int curr_index = y*width_+x;
//       if(setWall_right[curr_index])
//       {
//         int new_x = (x+1)*10;
//         for(int k=0; k<=10; k++)
//         {
//           int new_y = (y*10)+k;
//           image.getPixel(new_x,new_y).l = 1;
//         }
//       }
//
//       if(setWall_down[curr_index])
//       {
//         int new_y = (y+1)*10;
//         for(int k=0; k<=10; k++)
//         {
//           int new_x = x*10+k;
//           image.getPixel(new_x,new_y).l = 1;
//         }
//       }
//     }
//   }
//   return image;
//
// }
