// g++ CK530.cpp -o runthis -L. -lSDKDLL to compile (use .dll not .lib)
#include "SDKDLL.h"
#include <iostream>
#include <stdbool.h> 
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include <cmath>

using namespace std;

/**
 * lights a specified column of switches with a specified colour 
*/
void lightColumn(int col, DEVICE_INDEX kb, int r, int g, int b)
{
    int NUM_ROWS = 6;

    for (int i = 0; i < NUM_ROWS; i++)
    {
        SetLedColor(i, col, r, g, b, kb);
    }
}

/**
 * row and col are coordinates of centre of outwards radiating effect. 
 * 
*/
void radiateOutwards(int row, int col, int r, int g, int b, DEVICE_INDEX kb)
{
    int num_keys_lighted;
    int radius = 0;

    do
    {
        num_keys_lighted = 0;
        radius++;
        
        for (int i = -radius; i < radius + 1; i++)
        {
            for (int j = -radius; j < radius + 1; j++)
            {
                if (i == 0 && j == 0) continue;
                
                float distance = pow(i*i + j*j, 0.5);

                if (distance > radius - 1  && SetLedColor(row + i, col + j, r, g, b, kb)) num_keys_lighted++;
            }
        }

        SetFullLedColor(0, 0, 0, kb);
    }
    
    while (num_keys_lighted > 0);

}


void musicEffects(DEVICE_INDEX kb)
{
    int num_vals = 0;
    float total_val = 0;
    float average = 0;
    int NUM_COLS = 18;
    int NUM_ROWS = 6;
    int MAX_RGB = 255;
    srand(time(0));

    while (true)
    {
        float volume = GetNowVolumePeekValue();
        if (volume == 0) continue;
        num_vals++;
        total_val += volume;
        average = total_val/num_vals;
        //cout << volume << ", " << average << endl;

        int r = rand() % MAX_RGB; int g = rand() % MAX_RGB; int b = rand() % MAX_RGB;

        if (volume >= 2.5*average)
        {
            int row = rand() % NUM_ROWS; int col = rand() % NUM_COLS;
            radiateOutwards(row, col, r, g, b ,kb);
        }

        else if (volume >= 1.9*average)
        {
            SetFullLedColor(r, g, b, kb);
            Sleep(150);
        }

        else if (volume >= 1.1*average)
        {
            int col = rand() % NUM_COLS;
            lightColumn(col, kb, r, g, b);
            lightColumn(NUM_COLS - col - 1, kb, r, g, b);
            Sleep(100);
        }

        SetFullLedColor(0, 0, 0, kb);
    }   
}

void displayVolume()
{
    while (true)
    {
        cout << GetNowVolumePeekValue() << endl;
    }
}

int main()
{
    //displayVolume();
    //radiateOutwards(3, 6, 25, 56, 190, DEV_CK530);
    musicEffects(DEV_CK530);



    return 0;
}