// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 25 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);

#define DELAYVAL 80 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(9600);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}


int direction = 0;
int leftLED = 0;
int rightLED = 0;




void loop() {
  // pixels.clear(); // Set all pixel colors to 'off'
  pixels.clear();
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<12; i++) { // For each pixel...
    Serial.print("index i = ");
    Serial.print(i);
    Serial.print(";   direction = ");
    Serial.println(direction);
    
      
    pixels.clear();
    //Serial.println(i);

    
    if (!direction){

      leftLED = i;
      rightLED = 24-i;
      Serial.print("leftLED: ");
      Serial.print(leftLED);
      Serial.print(" RightLED: ");
      Serial.println(rightLED);

      pixels.setPixelColor(leftLED, pixels.Color(255, 0, 0));
      pixels.setPixelColor(rightLED, pixels.Color(255, 0, 0));
      
    }
    if(direction){
      leftLED = 11-i;
      rightLED = 13+i;
      Serial.print("leftLED: ");
      Serial.print(leftLED);
      Serial.print(" RightLED: ");
      Serial.println(rightLED);
      pixels.setPixelColor(leftLED, pixels.Color(255, 0, 0));
      pixels.setPixelColor(rightLED, pixels.Color(255, 0, 0));
      
    }

    if (i == 11){direction ^= 1;}
    //Serial.println(direction);
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
