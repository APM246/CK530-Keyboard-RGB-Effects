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

using namespace std;

void displayFPS(DEVICE_INDEX kb) 
{
    ifstream file("HardwareMonitoring.hml", ios::in);
    Sleep(7000);
    /*file.seekg(70, ios::end);
    //char c;
    //file.get(c);
    std::getline(file, line);

    char temp[400];
    while (!file.eof()) {
        file.getline(temp, 400);
    }

    cout << temp << endl;*/

    if (file.is_open())
    {
        string temp;
        // skip past pointless lines 
        for (int i = 0; i < 4; i++) std::getline(file, temp);

        while (true) {
            std::getline(file, temp);
            std::stringstream ss(temp);
            std::vector<string> result;

            while( ss.good() )
            {
                string substr;
                getline( ss, substr, ',');
                result.push_back( substr );
            }

            int fps = stoi(result[result.size() - 1]);
            int tens = fps%10;
            int ones = fps - 10*tens;
            for (int i = 0; i < 9000; i++) {
                SetLedColor(1, tens, 0, 255, 0, kb);
                SetLedColor(1, ones, 0, 255, 0, kb);
            }

        }
    }
  
    else cout << "file could not be opened" << endl;    

    file.close();
}

void lightColumn(int col, DEVICE_INDEX kb, int r, int g, int b)
{
    int NUM_ROWS = 6;

    for (int i = 0; i < NUM_ROWS; i++)
    {
        SetLedColor(i, col, r, g, b, kb);
    }
}

void musicEffects(DEVICE_INDEX kb)
{
    int NUM_COLS = 18;
    int MAX_RGB = 255;
    srand(time(0));

    while (true)
    {
        float volume = GetNowVolumePeekValue();

        if (volume >= 0.48)
        {
            int r = rand() % MAX_RGB; int g = rand() % MAX_RGB; int b = rand() % MAX_RGB;
            SetFullLedColor(r, g, b, kb);
            Sleep(200);
        }

        else if (volume > 0.38)
        {
            int col = rand() % NUM_COLS;
            int r = rand() % MAX_RGB; int g = rand() % MAX_RGB; int b = rand() % MAX_RGB;
            lightColumn(col, kb, r, g, b);
            lightColumn(NUM_COLS - col - 1, kb, r, g, b);
            Sleep(200);
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
    musicEffects(DEV_CK530);

    return 0;
}