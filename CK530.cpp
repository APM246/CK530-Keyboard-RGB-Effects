// g++ CK530.cpp -o runthis -L. -lSDKDLL to compile (use .dll not .lib)
#include "SDKDLL.h"
#include <iostream>
#include <stdbool.h> 
using namespace std;

int main()
{
    DEVICE_INDEX kb = DEV_CK530;
    bool isConnected = IsDevicePlug(kb);
    
    if (!isConnected)
    {
        cout << "Keyboard is not connected" << endl;
    }

    //SwitchLedEffect(EFF_OFF, kb);
    //SetLedColor(3, 10, 20, 20, 200, kb);

    /*
    If volume above 0.48 for too long, revert to green. Use variable and compare 
    */
    while (true)
    {
        float volume = GetNowVolumePeekValue();
        
        if (volume <= 0.2) SetFullLedColor(0,0,0,kb);
        
        else if (volume > 0.48)
        {
            SetFullLedColor(255, 0, 0, kb);
        }

        else 
        {
            SetFullLedColor(0,255,0,kb);
        }
    }

   return 0;
}