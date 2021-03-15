#include "esphome.h"
#include "Keypad.h"

class KeypadTextSensor : public Component, public TextSensor {

    public:

    std::string keysequenz;

    static const byte n_rows = 4;
    static const byte n_cols = 3;

    static const unsigned int resetTime = 300;
    unsigned int resetCounter = 0;
    bool keyPressed = false;
    
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
            if (myKey == '#'){
                publish_state(keysequenz);
                keysequenz.clear();
                resetCounter = 0;
                keyPressed = false;
            }
            else if (myKey == '*'){
                keysequenz.clear();
                publish_state(keysequenz);
                resetCounter = 0;
                keyPressed = false;
            }
            else {
                keysequenz.push_back(myKey);
                keyPressed = true;
            }
        }
        if (keyPressed){
            resetCounter++;
        }
        if (resetCounter >= resetTime){
            keysequenz.clear();
            publish_state(keysequenz);
            resetCounter = 0;
            keyPressed = false;
        }
    }
};