// Project:   Alpha 5 LED Config
// creator:   Carlos Ruiz
// Date:      8/30/2023

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define BOLT_PIN        6 
#define LIGHTS_PIN      3

// How many NeoPixels are attached to the Arduino?
#define BOLT_NUMPIXELS 39 // Lighting bolt leds
#define LIGHTS_NUMPIXELS 8 // All the other chest leds

//Custom color definition
#define YELLOW 128,128,0
#define OLYELLER 255,80,0
#define RED 200, 0, 0
#define WHITE 95,80,25

// Custom wait time
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

// Define 2 seprate LED strings
Adafruit_NeoPixel Bolt(BOLT_NUMPIXELS, BOLT_PIN, NEO_GRB);
Adafruit_NeoPixel Lights(LIGHTS_NUMPIXELS, LIGHTS_PIN, NEO_GRB);


void setup() {  
  Bolt.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Lights.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

// 2D array for lighting bolt LED strip 
uint16_t bolt_arr[12][2] = {{35,4},   // Top of Lighting Bolt
                            {31,4}, 
                            {27,4}, 
                            {23,4},
                            {20,3},
                            {17,3},
                            {14,3},
                            {10,4},
                            {6,4},
                            {3,3},
                            {1,2},
                            {0,1}};   // LED index, Num LEDS per row
  
// Loop varibales to slow down other chest LEDs
uint16_t loop_count = 0;
uint16_t index = 0;
uint16_t bot_light_index = 0;;

void loop() {

  if (loop_count > 0){  // to slow down other leds in increments of lightning bolt flashes increase this
    
    loop_count = 0;     // reset buffer after overflow   
    
    if(index > 2){      // index is used to iterate from top to bottom of chest
      index = 0;        // reset buffer
    }
    
    switch (index){
      case 0:
        Lights.clear();
        Lights.setPixelColor(index, Lights.Color(OLYELLER));
        Lights.setPixelColor(index + 3, Lights.Color(WHITE));
        break;
      case 1:
        Lights.clear();
        Lights.setPixelColor(index, Lights.Color(RED));
        Lights.setPixelColor(index + 3, Lights.Color(RED));
        break;
      case 2:
        Lights.clear();
        Lights.setPixelColor(index, Lights.Color(OLYELLER));
        Lights.setPixelColor(index + 3, Lights.Color(OLYELLER));
        break;
    }

    // Alternate Bottom Lights 6 and 7 between Red, White     
    if(bot_light_index & index == 0 ){
      Lights.setPixelColor(6, Lights.Color(RED));
      Lights.setPixelColor(7, Lights.Color(RED));
    }

    if(bot_light_index & index==1 ){
      Lights.setPixelColor(6, Lights.Color(OLYELLER));
      Lights.setPixelColor(7, Lights.Color(OLYELLER));
    }

    if(bot_light_index & index==2 ){
      Lights.setPixelColor(6, Lights.Color(WHITE));
      Lights.setPixelColor(7, Lights.Color(WHITE));
    }
    
    Lights.show();
    bot_light_index ^= 1;
    index++;
    
  }

  loop_count++;

  for (uint16_t i = 0; i < sizeof(bolt_arr)/sizeof(bolt_arr[0]); i++){
    
    Bolt.clear();

    for (uint16_t z = 0; z < (bolt_arr[i][1]); z++){
      Bolt.setPixelColor(bolt_arr[i][0] + z, Bolt.Color(YELLOW));
    }

    Bolt.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop

  }

}

