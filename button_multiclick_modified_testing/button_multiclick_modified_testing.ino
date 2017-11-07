
// -------- clickButton.h --------

#define CLICKBTN_PULLUP HIGH

class ClickButton
{
  public:
    ClickButton(uint8_t buttonPin);
    ClickButton(uint8_t buttonPin, boolean active);
    ClickButton(uint8_t buttonPin, boolean active, boolean internalPullup);
    void Update();
    int clicks;                   // button click counts to return
    int longPress;                //long pressing click count
    boolean depressed;            // the currently debounced button (press) state (presumably it is not sad :)
    boolean quickPressed;         //for quick simgle press detection
    long quickDebounceTime;
    long debounceTime;
    long multiclickTime;
    long longClickTime;
  private:
    boolean _quickState;
    uint8_t _pin;                 // Arduino pin connected to the button
    boolean _activeHigh;          // Type of button: Active-low = 0 or active-high = 1
    boolean _btnState;            // Current appearant button state
    boolean _lastState;           // previous button reading
    int _clickCount;              // Number of button clicks within multiclickTime milliseconds
    long _lastBounceTime;         // the last time the button input pin was toggled, due to noise or a press
};

// -------- end clickButton.h --------


// -------- clickButton.cpp --------

ClickButton::ClickButton(uint8_t buttonPin)
{
  _quickState    = 0;
  _pin           = buttonPin;
  _activeHigh    = LOW;           // Assume active-low button
  _btnState      = !_activeHigh;  // initial button state in active-high logic
  _lastState     = _btnState;
  _clickCount    = 0;
  clicks         = 0;
  longPress      = 0;
  quickPressed   = 0;         //for quick simgle press detection
  quickDebounceTime  = 50;
  depressed      = false;
  _lastBounceTime = 0;
  debounceTime   = 20;            // Debounce timer in ms
  multiclickTime = 250;           // Time limit for multi clicks
  longClickTime  = 1000;          // time until long clicks register
  pinMode(_pin, INPUT);
}


ClickButton::ClickButton(uint8_t buttonPin, boolean activeType)
{
  _quickState    = 0;
  _pin           = buttonPin;
  _activeHigh    = activeType;
  _btnState      = !_activeHigh;  // initial button state in active-high logic
  _lastState     = _btnState;
  _clickCount    = 0;
  clicks         = 0;
  quickPressed   = 0;         //for quick simgle press detection
  quickDebounceTime  = 50;
  longPress      = 0;
  depressed      = 0;
  _lastBounceTime = 0;
  debounceTime   = 20;            // Debounce timer in ms
  multiclickTime = 250;           // Time limit for multi clicks
  longClickTime  = 1000;          // time until long clicks register
  pinMode(_pin, INPUT);
}

ClickButton::ClickButton(uint8_t buttonPin, boolean activeType, boolean internalPullup)
{
  _quickState    = 0;
  _pin           = buttonPin;
  _activeHigh    = activeType;
  _btnState      = !_activeHigh;  // initial button state in active-high logic
  _lastState     = _btnState;
  _clickCount    = 0;
  clicks         = 0;
  longPress      = 0;
  quickPressed   = 0;         //for quick simgle press detection
  quickDebounceTime  = 50;
  depressed      = 0;
  _lastBounceTime = 0;
  debounceTime   = 20;            // Debounce timer in ms
  multiclickTime = 250;           // Time limit for multi clicks
  longClickTime  = 1000;          // time until "long" click register

  // Turn on internal pullup resistor if applicable
  if (_activeHigh == LOW && internalPullup == CLICKBTN_PULLUP)
    pinMode(_pin, INPUT_PULLUP);
  else
    pinMode(_pin, INPUT);
}



void ClickButton::Update()
{
  long now = (long)millis();      // get current time
  _btnState = digitalRead(_pin);  // current appearant button state

  // Make the button logic active-high in code
  if (!_activeHigh) _btnState = !_btnState;

  // If the switch changed, due to noise or a button press, reset the debounce timer
  if (_btnState != _lastState) _lastBounceTime = now;


  // debounce the button (Check if a stable, changed state has occured)
  if (now - _lastBounceTime > debounceTime && _btnState != depressed)
  {
    depressed = _btnState;
    if (depressed) _clickCount++;
    longPress = 0;
  }
  quickPressed = 0;
  if ((now - _lastBounceTime) > quickDebounceTime) {
    if (_btnState != _quickState) {
      _quickState = _btnState;

      if (_quickState != _activeHigh) {
        quickPressed = 1;
      }
    }
  }

  // If the button released state is stable, report nr of clicks and start new cycle
  if (!depressed && (now - _lastBounceTime) > multiclickTime)
  {
    // positive count for released buttons
    clicks = _clickCount;
    _clickCount = 0;
  }

  // Check for "long click"
  if (depressed && (now - _lastBounceTime > longClickTime))
  {
    // negative count for long clicks
    if (clicks < 0) {
      longPress = clicks;
    }
    clicks = 0 - _clickCount;
    _clickCount = 0;
  }


  _lastState = _btnState;
}

// -------- end clickButton.cpp --------


/* ClickButton library demo

  OUtput a message on Serial according to different clicks on one button.

  Short clicks:

    Single click -
    Double click -
    Triple click -

  Long clicks (hold button for one second or longer on last click):

    Single-click -
    Double-click -
    Triple-click -

  2010, 2013 raron

  GNU GPLv3 license
*/


// the Button
const int buttonPin1 = A2;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);


void setup()
{
  Serial.begin(115200);

  // Setup button timers (all in milliseconds / ms)
  // (These are default if not set, but changeable for convenience)
  button1.debounceTime   = 20;   // Debounce timer in ms
  button1.multiclickTime = 250;  // Time limit for multi clicks
  button1.longClickTime  = 1000; // time until "held-down clicks" register
}


void loop()
{
  // Update button state
  button1.Update();

  // Save click codes in LEDfunction, as click codes are reset at next Update()

  //if (button1.longPress) Serial.println(button1.longPress);
  if (button1.clicks){
    Serial.print("down ");
    Serial.println(button1.clicks);
  }


  if (button1.quickPressed) Serial.println("quick pressed");

  if (button1.longPress){
    
    Serial.print("hold ");
    Serial.println(button1.longPress);
  }



  //delay(5);

}
