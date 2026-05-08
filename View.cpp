#include <iostream>
#include "View.h"

using namespace std;

View::View()
{
    this->size = 11;
    this->scale = 2;
    this->origin = Point2D();
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
    out_x = (int)(location.x - origin.x)/scale;
    out_y = (int)(location.y - origin.y)/scale;

    if(out_x >= 0 && out_x < size && out_y >= 0 && out_y < size)
    {
        return true;
    }
    else
    {
        cout << "An object is outside the display" << endl;
    }
    return false;
}

void View::Clear()
{
    for(int x = 0; x<size; x++)
    {
        for(int y = 0; y<size; y++)
        {
            this->grid[x][y][0] = '.';
            this->grid[x][y][1] =' ';
        }
    }
}

void View::Plot(GameObject *ptr)
{
    int x, y;

    if(GetSubscripts(x, y, ptr->GetLocation()))
    {
        if(grid[x][y][0] == '.')
        {
            ptr->DrawSelf(grid[x][y]);
        }
        else
        {
            grid[x][y][0] = '*';
            grid[x][y][1] = ' ';
        }
    }
}

void View::Draw()
{
    int scaler_y = 0;
    int scaler_x = 0;
    for(int y = size-1; y>=0; y--)
    {
        if(y%2 == 0)
        {
            scaler_y = y * scale;
            if(scaler_y < 10)
            {
                cout << scaler_y << " ";
            }
            else
            {
                cout << scaler_y;
            }
        }
        else
        {
            cout << "  ";
        }
            for(int x = 0; x<size; x++)
            {
                cout << this->grid[x][y][0];
                cout << this->grid[x][y][1];
            }
            cout << endl;
    }
    cout << "  ";
    for(int x = 0; x<size; x++)
    {
        if(x % 2 == 0)
        {
            scaler_x = x * scale;
            if(scaler_x < 10)
            {
                cout << scaler_x << " ";
            }
            else
            {
                cout << scaler_x;
            }
        }
        else
        {
            cout << "  ";
        }
    }
    cout << endl;
}