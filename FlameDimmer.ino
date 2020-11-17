/*

using MEGA 2560
the pin that the LED is attached to uses a 22 ohm resistor used with 3x 5mm red and 2x 5mm yellow LEDs w/ 5v source
using an N type MOSFET to switch an external 5v power supply as to avoid using the Arduino's built in supply
with the intent of using this to power many dozens of LEDs over several arrays controlled by a single Arduino
*/
  // check your board's documentation, use a PWM cappable pin
const int pinPWM = 9;


// Modify these constants to change the behavior of the flame 

  // 0-255 sets the minimum brightness
const int minBrightness = 50; 

  // 0-255 sets the maximum brightness
const int maxBrightness = 255; 

  // milliseconds before a random value is pulled again controlls the fastest the light can flicker
const int minimumDelay = 80; 

  //milliseconds before a random value is pulled again controlls the slowest the light can flicker
const int maximumDelay = 190; 

  // The loop forces all values greater than the maxBrightness back down the the minimum brightness,
  // increasing this value will cause the flame to rest at minBrightness for a higher percentage of the time,
  // but also increases the odds of having higher flame intensity
  // values >126 and < 255 will increasingly cause a gradual "build up" of the flame intensity (like a flickering candle)
  // values <126 will cause a slow, soft flicker of light, increasing the rarity of max brightness events (like coals/embers)
const int oddsOfDimModifier = 180;

// These value causes the flame to decay slower, values close to 1 will vary more from cycle to cycle
// values close to zero will cause the brightness to randomize based on the oddsOfDimModifier more
// a manual value may be set if desired, I found 0.8 to be a 'happy medium'
const float minLeveling = 0.6;
const float maxLeveling = 0.8;


void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the pinPWM as an output for debugging
  pinMode(pinPWM, OUTPUT); 
}

 

void loop() {
  // initialization list for loop
  int brightness;
  int randomBrightness;
  int randomDelay;
  int pinbrightness;
  float brightnessLeveling; 
  
  brightnessLeveling = random(minLeveling, maxLeveling);
  randomBrightness = random(oddsOfDimModifier);
  randomDelay = random (minimumDelay, maximumDelay);
  brightness = randomBrightness + (brightness * brightnessLeveling);
    // checks if brightness is too high, brings it to the maximum threshold
  if (brightness > maxBrightness) {
    brightness = maxBrightness; 
  }
    // checks if brightness is too low, brings it to the minimum threshold
  if (brightness < minBrightness){
    brightness = minBrightness;
  }
  pinbrightness = (brightness);
  analogWrite(pinPWM, pinbrightness);
  delay(randomDelay);
  Serial.println(pinbrightness); // engable for debugging
}
