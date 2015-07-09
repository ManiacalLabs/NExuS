#include "NESpad.h"

#define NUMPAD_PLUS 223
#define NUMPAD_ENTER 224
#define NUMPAD_DOWN 226
#define NUMPAD_LEFT 228
#define NUMPAD_RIGHT 230
#define NUMPAD_UP 232

NESpad pad1 = NESpad(3,1,5);
NESpad pad2 = NESpad(2,0,4);

byte state1 = 0,
     last_state1 = 0,
     state2 = 0,
     last_state2 = 0;
bool state = false;

uint8_t btns[] = {
    NES_A,
    NES_B,
    NES_SELECT,
    NES_START,
    NES_UP,
    NES_DOWN,
    NES_LEFT,
    NES_RIGHT
};

char pad1_keys[] = {
    'a',
    'b',
    ' ',
    KEY_RETURN,
    KEY_UP_ARROW,
    KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,
    KEY_RIGHT_ARROW
};

char pad2_keys[] = {
    'z',
    'x',
    NUMPAD_PLUS,
    NUMPAD_ENTER,
    NUMPAD_UP,
    NUMPAD_DOWN,
    NUMPAD_LEFT,
    NUMPAD_RIGHT
};


void setup() {
    // Serial.begin(115200);
    Keyboard.begin();
}

uint8_t i = 0;
void loop() {

    state1 = pad1.buttons();
    state2 = pad2.buttons();
    // Serial.println(state1, DEC);
    // Serial.println(state2, DEC);
    // Serial.println("");

    for(i=0;i<8;i++){
        if(state1 < 255)
        {
            state = (state1 & btns[i]);
            if(state != (last_state1 & btns[i]))
            {
                if(state)
                    Keyboard.press(pad1_keys[i]);
                else
                    Keyboard.release(pad1_keys[i]);
            }
        }
        if(state2 < 255)
        {
            state = (state2 & btns[i]);
            if(state != (last_state2 & btns[i]))
            {
                if(state)
                    Keyboard.press(pad2_keys[i]);
                else
                    Keyboard.release(pad2_keys[i]);
            }
        }
    }

    if(state1 == 255 || state2 == 255){
        Keyboard.releaseAll();
    }

    last_state1 = state1;
    last_state2 = state2;
}
