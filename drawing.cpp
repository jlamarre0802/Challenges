#include <iostream>
#include <cmath>
#include <unistd.h>

extern "C" {
#include "gfx.h"
}

void draw_polygon(int *x, int *y, int n, bool closed = false)
{
        for (int i = 0; i < n - 1; i ++)
                gfx_line(x[i],y[i],x[i+1],y[i+1]);
        if (closed)
                gfx_line(x[0],y[0],x[n-1],y[n-1]);
}

void draw_circle(int xc, int yc, int radius)
{
        int x[18];
        int y[18];
        for (int i = 0; i < 18; i++)
        {
                double angle = i*20.0*3.14159/180.0;
                x[i] = xc + cos(angle)*radius;
                y[i] = yc + sin(angle)*radius;
        }

        draw_polygon(x, y, 18, true);
}

void draw_state_ship(int x, int y)
{
        gfx_clear();

        gfx_color(255, 0, 255);
        draw_circle(x, y, 15);
}

void draw_state_alien(int x, int y)
{


        gfx_color(255,0,0);
        draw_circle(x,y,20);
}
int main()
{
        gfx_open(800, 600, "Space Invaders");

        // start in middle of the screen
        int ax= 30;
        int ay = 50;
        int dx = 0;
        int acx = 1;
//      int dy = 1;
        int shipx = gfx_xsize() / 2;
        int shipy = 530;

        while(true)
        {

                if (gfx_event_waiting())
                {

                        int button = gfx_wait();

                        // print information about the event
                        std::cout << "got event: " << button;
                        // print character keys
                        if (button > 31 && button < 128) std::cout << " " << char(button);
                        // mouse events
                        if (button < 10) std::cout << " at pos (" << gfx_xpos() << "," << gfx_ypos() << ")";
                        std::cout << std::endl;

                        // when do we quit?
                        if (button == 'x' || button == 'q')
                                break;

                        // up arrow
//                      if (button == 65431 || button == 65362) dy--;
                        // down arrow
//                      if (button == 65433 || button == 65364) dy++;
                        // left arroow
                        if (button == 65430 || button == 65361) dx--;
                        // right arroow
                        if (button == 65432 || button == 65363) dx++;
                }
                else
                {
                        // make the aliens go across & down the screen at a constant rate
                        ax = ax + acx;
                                if ( ax < 0)
                                {
                                        ax = 20;
                                        acx = 1;
                                        ay = ay + 50;
                                }
                                if ( ax > gfx_xsize() - 20)
                                {
                                        ax = gfx_xsize() - 20;
                                        ay = ay + 50;
                                        acx = -1;
                                }
                        // move the centroids
                        shipx = shipx + dx;
                        // did we go past edge of window?
                        if (shipx > gfx_xsize()) shipx = 0;
                        if (shipx < 0) shipx = gfx_xsize();
                        // sleep 10,000 usec or 10 msec.
                        usleep(10000);

                        // update the drawing of the ship
                        draw_state_ship(shipx, shipy);

                        //Draw the aleins
                        draw_state_alien(ax,ay);
                }
        }

        return 0;
}


