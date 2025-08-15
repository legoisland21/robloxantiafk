#include "autocontroller.h"
#include <iostream>
#include <random>
using namespace std;

random_device dev;
mt19937 rng(dev());
int payload, time_hold, delay;
Controller control;

void centerCursorInWindow(HWND hwnd) {
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        int centerX = (rect.left + rect.right) / 2;
        int centerY = (rect.top + rect.bottom) / 2;
        SetCursorPos(centerX, centerY);
    }
}

void strokeKey(WORD character, int delay) {
    control.sendRawKeyDown(MapVirtualKeyA(character, MAPVK_VK_TO_VSC));
    Sleep(delay);
    control.sendRawKeyUp(MapVirtualKeyA(character, MAPVK_VK_TO_VSC));
}

int main() {
    HWND hwnd = FindWindowA(NULL, "Roblox");
    if(!hwnd) {
        MessageBoxA(NULL, "Could not find Roblox, is Roblox running?", "ERROR", MB_ICONERROR);
        return 1;
    }\
    
    cout << "Enter delay: ";
    cin >> delay;
    cout << endl;
    cout << "Roblox window found" << endl;
    printf("HWND id is %p \n", hwnd);
    cout << "Setting Roblox as foreground window" << endl;
    SetForegroundWindow(hwnd);
    cout << "Focusing Roblox" << endl;
    SetFocus(hwnd);
    centerCursorInWindow(hwnd);

    MSG msg = {0};
    while(true) {
        uniform_int_distribution<mt19937::result_type> payload_random(0,6);
        payload = payload_random(rng);
        if(payload > 0 && payload < 4) { uniform_int_distribution<mt19937::result_type> random_delay(5,500); time_hold = random_delay(rng); }
        if(payload == 0) strokeKey('W', time_hold);
        else if(payload == 1) strokeKey('A', time_hold);
        else if(payload == 2) strokeKey('S', time_hold);
        else if(payload == 3) strokeKey('D', time_hold);
        else if(payload == 4) strokeKey(VK_SPACE, time_hold);
        else if(payload == 5) control.scrollVertical(3);
        else if(payload == 6) control.scrollVertical(-3);
        Sleep(delay);
    }
    return 0;
}
