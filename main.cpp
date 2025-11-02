#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "matrix.h"
#include "rgb_matrix.h"
#include "bw_matrix.h"

template <class T>
void select_operations(T *mt)
{
    int goback=false,color_choice,border_width;
    const string OUTPUT_IMAGE_PATH="output\\output.png";
    std::vector<int> color={0,0,0};
    while(true)
    {
        int opt,val;

        if(goback)
        break;
        
        std::cout<<"Select options\n";
        std::cout<<"1.Rotate 90 degree left\n2.Rotate 90 degree right\n3.rotate 180 degree\n4.save image\n5.horizontal_flip\n6.vertical_flip\n7.Contrast\n8.Display\n9.Go back\n10.add border\n";
        std::cin>>opt;
        switch(opt)
        {
            case 1:mt->rotate_left();
                   break;
            case 2:mt->rotate_left();
                   mt->rotate_left();
                   mt->rotate_left();
                   break;
            case 3:mt->rotate_left();
                   mt->rotate_left();
                   break;
            case 4:mt->save_image(OUTPUT_IMAGE_PATH);
                   break;
            case 5:mt->horizontal_flip();
                   break;
            case 6:mt->vertical_flip();
                   break;
            case 7:std::cout<<"Enter the value between(-100 to +100)\n";
                   std::cin>>val;
                   mt->contrast(val);
                   break;
            case 8:mt->display();
                   break;
            case 9:goback=true;
                   break;
            case 10:std::cout<<"Enter the border width\n";
                    std::cin>>border_width;
                    std::cout<<"Enter color\n1.Red\n2.Green\n3.Blue\n";
                    std::cin>>color_choice;
                    if(color_choice==1)
                     color[0]=255;
                    else if(color_choice==2)
                     color[1]=255;
                    else if(color_choice==3)
                     color[1]=255;

                    mt->border(border_width,color);
                    break;
            
            default: std::cout<<"Invalid input\n";
        }
    }
}

int main()
{
    const string INPUT_IMAGE_PATH="input\\cat.png";
    try
    {
          while(true)
            {
                int opt;
                RGBMatrix rgb;
                BWMatrix bw;
                std::cout<<"Select Options\n";
                std::cout<<"1.Read COLOR Image\n2.Read Black and white image\n";
                std::cin>>opt;
                switch(opt)
                {
                    case 1:rgb.readImage(INPUT_IMAGE_PATH);
                        select_operations(&rgb);
                        break;
                    case 2:bw.readImage(INPUT_IMAGE_PATH);
                        select_operations(&bw);
                        break;
                    default: std::cout<<"Invalid selection\n";
                }
            }
    }
    catch(...)
    {
        std::cout<<"Some error occured\n";
    }
    return 0;
}