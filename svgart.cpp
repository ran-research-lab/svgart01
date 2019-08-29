
#include <iostream>
#include <cstdlib>
#include <vector>

#include "simple_svg_1.0.0.hpp"
using namespace svg;

/*
If the region is wider than half the initial canvas size and the region is taller than half the initial canvas 
height: 
  Use recursion to split the region into 4 smaller regions (a vertical split and a horizontal split) with 
  the split location chosen randomly 
Else if the region is wider than half the initial canvas size: 
  Use recursion to split the region into 2 smaller regions using a vertical line with the split location 
  chosen randomly 
Else if the region is taller than half the initial canvas size:
  Use recursion to split the region into 2 smaller regions using a horizontal line with the split 
  location chosen randomly 
Else if the region is big enough to split both horizontally and vertically, and both a horizontal and vertical 
split are randomly selected: 
  Use recursion to split the region into 4 smaller regions (a vertical split and a horizontal split) with 
  the split location chosen randomly 
Else if the region is big enough to split horizontally, and a horizontal split is selected: 
  Use recursion to split the region into 2 smaller regions using a vertical line with the split location 
  chosen randomly 
Else if the region is big enough to split vertically, a vertical split is selected: 
  Use recursion to split the region into 2 smaller regions using a horizontal line with the split 
  location chosen randomly 
Else: 
  Fill the current region (randomly,
*/

std::vector<svg::Fill> allColors {Color::Red, Color::White, Color::Blue, Color::Yellow, Color::Purple,
Color::Black, Color::Brown, Color::Orange, Color::Silver, Color::Green};

svg::Fill getRandColor() {
    return allColors[rand()%allColors.size()];
}

void foo(Document &doc, int x, int y, int w, int h, int level, int maxLevel) {
    if (level < maxLevel) {
    float fx, fy;
    fx = static_cast<float>(2000 + rand()%6000)/10000;
    fy = static_cast<float>(2000 + rand()%6000)/10000;

    int nw, nh;
    nw = w * fx;
    nh = h * fy;

    std::cout << fx << " " << fy << std::endl;
    Polyline polyline_a(Stroke(.5, Color::Blue));
    Polyline polyline_b(Stroke(.5, Color::Blue));
    Polyline polyline_c(Stroke(.5, Color::Fuchsia));
    
    //if (rand() % 4 == 1)
    // svg::Fill col = getRandColor();

    if (level == maxLevel - 1) {
    doc << Rectangle(Point(x,y+nh), nw, nh, getRandColor());
    doc << Rectangle(Point(x+nw,y+nh), w-nw, nh, getRandColor());
    doc << Rectangle(Point(x+nw,y+h), w-nw, h-nh, getRandColor());
    doc << Rectangle(Point(x,y+h), nw, h-nh, getRandColor());

    }

    // polyline_a << Point(x, y + nh) << Point(x + w, y + nh);
    // polyline_b << Point(x + nw, y) << Point(x + nw, y + h);



    doc << polyline_a;
    doc << polyline_b;

    foo(doc, x, y, nw, nh, level+1, maxLevel);
    foo(doc, x + nw, y, w-nw, nh, level+1, maxLevel);
    foo(doc, x + nw, y + nh, w-nw, h-nh, level+1, maxLevel);
    foo(doc, x, y + nh, nw, h-nh, level+1, maxLevel);

    }

}

int main(){

    srand(time(NULL));
    srand(42);

    Dimensions dimensions(400, 400);
    Document doc("my_svg.svg", Layout(dimensions, Layout::BottomLeft));

    // Red image border.
    Polygon border(Stroke(1, Color::Red));
    border << Point(0, 0) << Point(dimensions.width, 0)
        << Point(dimensions.width, dimensions.height) << Point(0, dimensions.height);
    doc << border;

    // Long notation.  Local variable is created, children are added to varaible.
    // LineChart chart(5.0);


    foo(doc, 0,0, dimensions.width, dimensions.height, 0, 4);


    doc.save();
}
