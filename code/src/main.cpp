/*
  SmartMatrix Features Demo - Louis Beaudoin (Pixelmatix)
  This example code is released into the public domain

  (New in SmartMatrix Library 4.0) To update a SmartMatrix Library sketch to use Adafruit_GFX compatible layers:

  - Make sure you have the Adafruit_GFX Library installed in Arduino (you can use Arduino Library Manager)
  - add `#define USE_ADAFRUIT_GFX_LAYERS` at top of sketch (this is needed for any sketch to tell SmartMatrix Library that Adafruit_GFX is present, not just this sketch)
    - Add this *before* #include <SmartMatrix.h>
    - Check the documentation Wiki for more details on why you may or may not want to use these layers
*/
#include <libraries.h>

#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth = 64;       // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight = 16;      // Set to the height of your display
const uint8_t kRefreshDepth = 48;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t kPanelType = SMARTMATRIX_HUB75_16ROW_MOD8SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);

//SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

//#ifdef USE_ADAFRUIT_GFX_LAYERS
  // there's not enough allocated memory to hold the long strings used by this sketch by default, this increases the memory, but it may not be large enough
  //SMARTMATRIX_ALLOCATE_GFX_MONO_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, 6*1024, 1, COLOR_DEPTH, kScrollingLayerOptions);
//#else
  SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
//#endif

//SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);

// the setup() method runs once, when the sketch starts

const int defaultBrightness = (4*255)/100;
//const int defaultBrightness = (15*255)/100;       // dim: 15% brightness
const int defaultScrollOffset = 4;

void setup() {

  Serial.begin(115200);
  //matrix.addLayer(&backgroundLayer); 
  matrix.addLayer(&scrollingLayer); 
  //matrix.addLayer(&indexedLayer); 
  matrix.begin(); 
  matrix.setBrightness(defaultBrightness);
  scrollingLayer.setOffsetFromTop(defaultScrollOffset);
  //backgroundLayer.enableColorCorrection(true);


  //backgroundLayer.fillScreen(defaultBackgroundColor);
  scrollingLayer.setFont(font8x13);
  //scrollingLayer.setColor({255,255,255});
  //backgroundLayer.swapBuffers();
  //scrollingLayer.start("The LED Individuals",10);
}


void loop() {

  scrollingLayer.setMode(wrapForward);
  scrollingLayer.start("THE LED INDIVIDUALS",1);
  //backgroundLayer.swapBuffers();
  //scrollingLayer.start("The LED Individuals",1);
  delay(9000);
}