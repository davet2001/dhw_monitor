/**
 *  Header file for ESPHome to enable drawing of gradient coloured water tanks
 *  on colour LCD displays.
 * 
 *  Dave T 2/10/2021
 */ 
#ifndef _DHWMONITOR_H
#define _DHWMONITOR_H  // Header file guard.

#ifdef EMULATED_ESPHOME

#include <stdio.h>
#include <iostream>
#include "emulated_color.h"
#include "emulated_display_buffer.h"

#else

#include "esphome/components/display/display_buffer.h"

#endif // EMULATED_ESPHOME

/**
 * Takes a temperature in degC and returns a colour indicating how hot.
 * Colours vary between blue to red defined by constants.
 */
Color temp_to_color(float temp)
{
    const Color COLD_COLOUR = Color(56, 85, 255);
    const Color HOT_COLOUR = Color(209, 0, 23);
    const float COLD_TEMP = 30;
    const float HOT_TEMP = 50;

    float prop = (temp - COLD_TEMP) / (HOT_TEMP-COLD_TEMP);
    if (prop > 1)
        prop = 1;
    else if (prop < 0)
        prop = 0;
    //printf(" prop=%3.1f\n", prop);

    return Color(
        COLD_COLOUR.r + prop * (HOT_COLOUR.r - COLD_COLOUR.r),
        COLD_COLOUR.g + prop * (HOT_COLOUR.g - COLD_COLOUR.g),
        COLD_COLOUR.b + prop * (HOT_COLOUR.b - COLD_COLOUR.b)
    );
}

#ifdef EMULATED_ESPHOME
/***
 * Draw a vertical sausage shaped tank on the screen, coloured by temperature.
 * @param x      Top left x coordinate
 * @param y      Top left y coordinate
 * @param width  The width of the tank to draw in pixels.
 * @param height The height of the tank to draw in pixels.
 * @param temps  An array of floating point values containg the vertically sequenced
 *               temperatures, starting at the top, descending.
 * @param count  The number of elements in the 'temps' array.
 */
void draw_tank(ESPHomeEmulatedDisplay it, int x, int y, int width, int height, const float temps[], int count)
//void draw_tank(DisplayBuffer it, int x, int y, int width, int height, const float temps[], int count)
{
    assert(count > 1);

    float r = (float)width/2;
    float w, x1, x2, l;
    // Draw out a tank a line at a time.
    for (int i=0; i<height; i++)
    {
        // calculate the start and finish x coordinates of each line.
        if (i<r) // top semicircle
        {
            w = sqrt(2*r*i - i*i);
            //printf("x=%3.1f\n", r-x);
        }
        else if (i<(height-r)) //middle straight section
        {
            w = r;
        }
        else // bottom semicircle
        {
            l = (height - i);
            w = sqrt(2*r*l - l*l);
            //printf("x=%3.1f\n", r-l);
        }
        x1 = int(r - w);
        x2 = int(r + w);
        int i1 = i * (count-1)/ height;
        int i2 = i1+1;

        // Calculate interpolated temperature at this height.
        float temp1 = temps[i1];
        float temp2 = temps[i2];
        int h1 = i1 * (float)height/(count-1);
        int h2 = i2 * (float)height/(count-1);
        float temp = temp1 + (temp2-temp1) * (float)(i-h1)/(float)(h2-h1);
        //printf("t1=%3.1f, t2=%3.1f, temp=%3.1f i1=%d i2=%d h1=%d h2=%d", temp1, temp2, temp, i1, i2, h1, h2);
        // convert temperature to a color
        Color c = temp_to_color(temp);
        it.line(x + x1, y + i, x + x2, y + i, c); 
    }
}
#endif // EMULATED_ESPHOME
#endif // _DHWMONITOR_H 
