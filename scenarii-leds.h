/*********************************************************************************
 Scénarii de base d'animation d'une zone
 Sur la base des exemples de cet article
 https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 Modifiés par Pierre-Gilles Levallois pour correspondre aux besoins d'animation 
 par zones. 
**********************************************************************************/


/*********************************************************************************
	Push modification to Leds Strips.
**********************************************************************************/
void showStrip() {
  // FastLED
  FastLED.show();
}

/*********************************************************************************
	Input a value 0 to 255 to get a color value.
	The colours are a transition r - g - b - back to r.
**********************************************************************************/
CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/*********************************************************************************
	Gives a random color.
**********************************************************************************/
CRGB randomColor(){
  return Wheel(random(256)); 
}

/*********************************************************************************
	Changes all LEDS to given color
**********************************************************************************/
void allColor(CRGB c, int NumZone){
  for(int i = 0; i < NUM_LEDS[NumZone]; i++){
    setPixel(i, c, NumZone);
  }
  showStrip();
}

/*********************************************************************************
	Changes all LEDS to a random color
**********************************************************************************/
void allRandom(int NumZone){
  for(int i=0; i<NUM_LEDS[NumZone]; i++){
  	setPixel(i, randomColor(), NumZone);
  }
  showStrip(); 
}

/*********************************************************************************
   ColorWipe : Allumer toutes les leds une à une sur toute la longueur du ruban
   dans l'ordre et avec une coleur unique, mais choisi au hasard.
 *********************************************************************************/
void colorWipe(CRGB c, int SpeedDelay, int NumZone) {
  // Choix d'une couleur aléatoire
  for (uint16_t i = 0; i < NUM_LEDS[NumZone]; i++) {
    setPixel(i, c, NumZone);
    showStrip();
    delay(SpeedDelay);
  }
}

/*********************************************************************************
	Random disolve colors
**********************************************************************************/
void disolve(int simultaneous, int cycles, int SpeedDelay, int NumZone){
  for(int i=0; i<cycles; i++){
    for(int j=0; j<simultaneous; j++){
      int idx = random(NUM_LEDS[NumZone]);
      setPixel(idx, CRGB::Black, NumZone);
    }
    showStrip();
    delay(SpeedDelay);
  }

  allColor(CRGB::Black, NumZone);
}

/*********************************************************************************
	Flashes given color
	If c==NULL, random color flash
**********************************************************************************/
void flash(CRGB c, int count, int speedDelay, int NumZone){
  for(int i=0; i<count; i++){
    if(c){
      allColor(c, NumZone);
    }
    else{
      allColor(randomColor(), NumZone);
    }
    delay(speedDelay);
    allColor(CRGB::Black, NumZone);
    delay(speedDelay);
  }
}

/*********************************************************************************
   SnowSparkle : Allumer toutes les leds ave une couleur choisie, puis faire
   scintiller des leds au hasard dans la zone.
 *********************************************************************************/
void SnowSparkle(CRGB c, int SparkleDelay, int SpeedDelay, int NumZone) {
  c.r *= 0.5;
  c.g *= 0.5;
  c.b *= 0.5;
  // red = byte(int(c.r * 0.5));
  // green = byte(int(c.g * 0.5));
  // blue = byte(int(c.b * 0.5));
  allColor(c, NumZone);
  // Choisir un pixel au hasard
  int Pixel = random(NUM_LEDS[NumZone]);
  setPixel(Pixel, CRGB::White, NumZone);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel, c, NumZone);
  showStrip();
  delay(SpeedDelay);
}


/*
   Cyclon

  void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay, int NumZone) {

  for (int i = 0; i < NUM_LEDS[NumZone] - EyeSize - 2; i++) {
    setAll(0, 0, 0, NumZone);
    setPixel(i, red / 10, green / 10, blue / 10, NumZone);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue, NumZone);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10, NumZone);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for (int i = NUM_LEDS[NumZone] - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0, NumZone);
    setPixel(i, red / 10, green / 10, blue / 10, NumZone);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue, NumZone);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10, NumZone);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);
  }
*/

/** 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
FAST-LEDS NATIVES SCENARII
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Flashes given color
// If c==NULL, random color flash
void flash(CRGB c, int count, int speed){
  for(int i=0; i<count; i++){
    if(c){
      allColor(c);
    }
    else{
      allColor(randomColor());
    }
    delay(speed);
    allColor(CRGB::Black);
    delay(speed);
  }
}

// Wipes color from end to end
void colorWipe(CRGB c, int speed, int direction){
  for(int i=0; i<NUM_LEDS; i++){
    if(direction == FORWARD){
      leds[i] = c;
    }
    else{
      leds[NUM_LEDS-1-i] = c;
    }
    showStrip();
    delay(speed);
  }
}

// Rainbow colors that slowly cycle across LEDs
void rainbow(int cycles, int speed){ // TODO direction
  if(cycles == 0){
    for(int i=0; i< NUM_LEDS; i++) {
      leds[i] = Wheel(((i * 256 / NUM_LEDS)) & 255);
    }
    showStrip();
  }
  else{
    for(int j=0; j<256*cycles; j++) {
      for(int i=0; i< NUM_LEDS; i++) {
        leds[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      }
      showStrip();
      delay(speed);
    }
  }
}

// Theater-style crawling lights
void theaterChase(CRGB c, int cycles, int speed){ // TODO direction

  for (int j=0; j<cycles; j++) {  
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        int pos = i+q;
        leds[pos] = c;    //turn every third pixel on
      }
      showStrip();

      delay(speed);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = CRGB::Black;        //turn every third pixel off
      }
    }
  }
}

// Theater-style crawling lights with rainbow effect
void theaterChaseRainbow(int cycles, int speed){ // TODO direction, duration
  for (int j=0; j < 256 * cycles; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        int pos = i+q;
        leds[pos] = Wheel( (i+j) % 255);    //turn every third pixel on
      }
      showStrip();

      delay(speed);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = CRGB::Black;  //turn every third pixel off
      }
    }
  }
}

// Random flashes of lightning
void lightning(CRGB c, int simultaneous, int cycles, int speed){
  int flashes[simultaneous];

  for(int i=0; i<cycles; i++){
    for(int j=0; j<simultaneous; j++){
      int idx = random(NUM_LEDS);
      flashes[j] = idx;
      leds[idx] = c ? c : randomColor();
    }
    showStrip();
    delay(speed);
    for(int s=0; s<simultaneous; s++){
      leds[flashes[s]] = CRGB::Black;
    }
    delay(speed);
  }
}

// Sliding bar across LEDs
void cylon(CRGB c, int width, int speed){
  // First slide the leds in one direction
  for(int i = 0; i <= NUM_LEDS-width; i++) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }

    showStrip();

    // now that we've shown the leds, reset to black for next loop
    for(int j=0; j<5; j++){
      leds[i+j] = CRGB::Black;
    }
    delay(speed);
  }

  // Now go in the other direction.  
  for(int i = NUM_LEDS-width; i >= 0; i--) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }
    showStrip();
    for(int j=0; j<width; j++){
      leds[i+j] = CRGB::Black;
    }

    delay(speed);
  }
}

// Display alternating stripes
void stripes(CRGB c1, CRGB c2, int width){
  for(int i=0; i<NUM_LEDS; i++){
    if(i % (width * 2) < width){
      leds[i] = c1;
    }
    else{
      leds[i] = c2;
    } 
  }
  showStrip();
}

// Theater-style crawling of stripes
void stripesChase(CRGB c1, CRGB c2, int width, int cycles, int speed){ // TODO direction

}

*/
