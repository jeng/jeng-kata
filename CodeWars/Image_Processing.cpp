 #include <vector>
 #include <algorithm>
 #include <math.h>
 using namespace std;

 typedef unsigned char u8;

 u8 adj(float f){
   if (f > 0xff)
     return 0xff;
   else if (f > 0)
     return f;
   else 
     return 0; 
 }

 class Pixel {
 public:
   float red;
   float green;
   float blue;

   Pixel(): red(0), green(0), blue(0) {}
   Pixel(float red, float green, float blue) : red(red), green(green), blue(blue) {}

 };


 class Image {
 public:
   vector<Pixel> data;
   int width;
   int height;
  
   Image(const vector<u8> &imageData, int height, int width):
     data(width*height),
     height(height),
     width(width)
     {
      
       int i = 0;
       for(unsigned long colorCount = 0; colorCount <= imageData.size(); colorCount++){
         if (colorCount != 0 && colorCount % 3 == 0){       
           data[i++] = Pixel(imageData[colorCount-3],
                             imageData[colorCount-2],
                             imageData[colorCount-1]);
         }
       }
     }
 
   Pixel at(int x, int y){
     if (y >= height) y = height-1;
     if (y < 0) y = 0;
     if (x >= width) x = width-1;
     if (x < 0) x = 0;
     return data[y * width + x];
   }

   Pixel convolution(int x, int y, vector<vector<float>> &weights){   

     int mid = weights.size()/2;
     int start_x = x - mid;
     x = start_x;
     y = y - mid;
    
     float result = 0;
     float r = 0;
     float g = 0;
     float b = 0;
     for(auto v : weights){
       for(auto w : v){
         auto color = this->at(x, y);
         r += color.red * w;
         g += color.green * w;
         b += color.blue * w;
         x++;
       }
       x = start_x;
       y++;
     }
  
     return Pixel(r,g,b);
   }

 };


 vector <u8> processImage (const vector <u8> &imageData, int height, int width, vector <vector <float>> weights) {
   auto img = Image(imageData, height, width);
  
   auto result = vector<u8>();
   for(int y = 0; y < height; y++)
     for(int x = 0; x < width; x++){
       auto p = img.convolution(x, y, weights);     
       result.push_back(adj(p.red));
       result.push_back(adj(p.green));
       result.push_back(adj(p.blue));
     }

   return result;
 }

