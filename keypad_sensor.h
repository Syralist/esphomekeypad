#include "esphome.h"
#include "Keypad.h"

class KeypadSensor : public Component, public Sensor {

    public:

    static const byte n_rows = 4;
    static const byte n_cols = 3;

    bool keyPublished = false;

    static const unsigned int resetTime = 500;
    unsigned int lastPublish = 0;
    
    char keys[n_rows][n_cols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };
    
    byte colPins[n_cols] = {D3, D2, D1};
    byte rowPins[n_rows] = {D7, D6, D5, D4};
    
    Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

    void setup() override {
    // This will be called by App.setup()
    }
    void loop() override {
    // This will be called by App.loop()
        char myKey = myKeypad.getKey();
        if (myKey != NO_KEY){
            int key = myKey - 48;
            publish_state(key);
            keyPublished = true;
            lastPublish = millis();
        }
        else{
            if (keyPublished && (millis() - lastPublish) >= resetTime){
                publish_state(NAN);
                keyPublished = false;
            }
        }

    }
};