// Display a message on the LED matrix and "send" morse code value via onboard LED and active buzzer
#include <Arduino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix; 

//-----------------------------------
// FUNCTION DECLARATIONS

// Function to display a specific string (non-scrolling)
void displayStr(String);

// "Send" character as morse code
void sendCharacter(String);

//-----------------------------------
// Globals
int buzzerPin = 5;  // Pin Active buzzer is connected to on the Ditital PWM
int dot = 50;       // Length of morse code "Dot"
int dash = dot * 3; // Length of morse code "Dash"
int del = dot;      // Delay between dots/dashes
String alphanumericString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?!.,;:+-/=";
int morseCodes[46][6] = {
  {dot, dash, 0, 0, 0},               // A
  {dash, dot, dot, dot, 0, 0},        // B
  {dash, dot, dash, dot, 0, 0},       // C
  {dash, dot, dot, 0, 0, 0},          // D
  {dot, 0, 0, 0, 0, 0},               // E
  {dot, dot, dash, dot, 0, 0},        // F
  {dash, dash, dot, 0, 0, 0},         // G
  {dot, dot, dot, dot, 0, 0},         // H
  {dot, dot, 0, 0, 0, 0},             // I
  {dot, dash, dash, dash, 0, 0},      // J
  {dash, dot, dash, 0, 0, 0},         // K
  {dot, dash, dot, dot, 0, 0},        // L
  {dash, dash, 0, 0, 0, 0},           // M
  {dash, dot, 0, 0, 0, 0},            // N
  {dash, dash, dash, 0, 0, 0},        // O
  {dot, dash, dash, dot, 0, 0},       // P
  {dash, dash, dot, dash, 0, 0},      // Q
  {dot, dash, dot, 0, 0, 0},          // R
  {dot, dot, dot, 0, 0, 0},           // S
  {dash, 0, 0, 0, 0, 0},              // T
  {dot, dot, dash, 0, 0, 0},          // U
  {dot, dot, dot, dash, 0, 0},        // V
  {dot, dash, dash, 0, 0, 0},         // W
  {dash, dot, dot, dash, 0, 0},       // X
  {dash, dot, dash, dash, 0, 0},      // Y
  {dash, dash, dot, dot, 0, 0},       // Z
  {dash, dash, dash, dash, dash, 0},  // 0
  {dot, dash, dash, dash, dash, 0},   // 1
  {dot, dot, dash, dash, dash, 0},    // 2
  {dot, dot, dot, dash, dash, 0},     // 3
  {dot, dot, dot, dot, dash, 0},      // 4
  {dot, dot, dot, dot, dot, 0},       // 5
  {dash, dot, dot, dot, dot, 0},      // 6
  {dash, dash, dot, dot, dot, 0},     // 7
  {dash, dash, dash, dot, dot, 0},    // 8
  {dash, dash, dash, dash, dot, 0},   // 9
  {dot, dot, dash, dash, dot, dot},   // ?
  {dash, dot, dash, dot, dash, dash}, // !
  {dot, dash, dot, dash, dot, dash},  // .
  {dash, dash, dot, dot, dash, dash}, // ,
  {dash, dot, dash, dot, dash, dot},  // ;
  {dash, dash, dash, dot, dot, dot},  // :
  {dot, dash, dot, dash, dot, 0},     // +
  {dash, dot, dot, dot, dot, dash},   // -
  {dash, dot, dot, dash, dot, 0},     // /
  {dash, dot, dot, dot, dash, 0}      // =
};

//-----------------------------------
// Initialization
void setup() {
    // Lnitialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Initialize the LED matrix
  Serial.begin(115200);
  matrix.begin();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  // add some static text
  // will only show "UNO" (not enough space on the display)
  const char text[] = "Hi";
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();

  // Initialize active buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer

  delay(2000);  // Wait before going to main program (loop)

  displayStr("");   // Clear the display
  digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
}

//-----------------------------------
// Main
void loop() {
  String myMessage = String("It is as easy as 1 2 3"); // Message to send
  for (int i = 0; i < myMessage.length(); i++){
    String currentChar = String(myMessage.substring(i,i+1));
    currentChar.toUpperCase();
    if (currentChar != " "){    // If not a space between words
      displayStr(currentChar);
      sendCharacter(currentChar);
      displayStr(" ");
      delay(dot * 3); // Delay between letters
    } else {  // If it is a space between words
      displayStr(" ");
      delay(dot * 7); 
    }
  }
  // Clear the display after processing the entire message and pause before repeating
  displayStr("");
  delay(1000);
}

//-----------------------------------
// FUNCTION DEFINITIONS

// Display a message on the LED matrix
void displayStr(String message){
  matrix.beginDraw();
  matrix.clear();
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(message);
  matrix.endText();
  matrix.endDraw();
  return;
}

// "Send" a morse code character
void sendCharacter(String mcChar){
  mcChar.toUpperCase(); // Make sure character is upper case and convert to String
  int mcIndex = alphanumericString.indexOf(mcChar); // Find the index of the character in the morseCodes array
  for (int i = 0; i < 5; i++){
    int dotOrDash = morseCodes[mcIndex][i];
    if (dotOrDash <= 0) {return;}
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    digitalWrite(buzzerPin, HIGH);    // turn on the buzzer
    delay(dotOrDash);                 // wait for dot or dash length
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(buzzerPin, LOW);     // turn off the buzzer
    delay(del);                       // delay between dots and dashes 
  }
  return;
}