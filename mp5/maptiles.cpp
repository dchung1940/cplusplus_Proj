/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * curr_image = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector<Point<3>> vect_points;
    map<Point<3>,TileImage*> map_tiles; // dictionary for finding given tileImage
    for(unsigned i=0; i< theTiles.size(); i++)
    {
      Point<3> point = convertToXYZ(theTiles[i].getAverageColor());
      vect_points.push_back(point);
      map_tiles.insert({point,&theTiles[i]});
    }
    KDTree<3> kd(vect_points);
    for(int i=0; i<theSource.getRows(); i++)
    {
      for(int j=0; j<theSource.getColumns(); j++)
      {
        Point<3> point = convertToXYZ(theSource.getRegionColor(i,j));
        // kd.findNearestNeighbor(point);
        curr_image->setTile(i,j,map_tiles[kd.findNearestNeighbor(point)]);
      }
    }

    return curr_image;
}
