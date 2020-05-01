/***************************************************

  NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!

***************************************************
  64x32 RGB LED Matrix - 4mm pitch
* ****************************************************
  testshapes demo for RGBmatrixPanel library.
  Demonstrates the drawing abilities of the RGBmatrixPanel library.
  For 32x64 RGB LED matrix.

  @author lg.gang(lg.gang@qq.com)
  @version  V1.0
  @date  2016-9-6

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
  All above must be included in any redistribution
* ****************************************************/
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11
#define OE  9
#define LAT 10

#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);


float  floatTemperature = 0;
String receivedChars; 
String dataTemperature, dataHeight;

void setup() {
  Serial.begin(9600);
  delay(1000);
  matrix.begin();

}

void loop() {
  if (Serial.available() > 0) {
        receivedChars = Serial.readString();
        dataTemperature = receivedChars[0] + receivedChars[1] +"."+ receivedChars[2];
        dataHeight = receivedChars[3] +receivedChars[4] + receivedChars[5]; 
                
  }


  matrix.setTextSize(1);  //1=8 2=14 3=21
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves


  matrix.fillScreen(matrix.Color333(0, 0, 0));
  template_function();
  printTemp(dataTemperature);
  printHeight(dataHeight);

  delay(3000);
  
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  template_function();
  printTemp("37.8");
  printHeight("168");

  delay(3000);

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  template_function();
  printTemp("38.3");
  printHeight("163");

  delay(3000);
 

}



void printTemp(String temperature){
  matrix.setCursor(39, 0);
  uint8_t w = 0;
  floatTemperature =  temperature.toFloat();
//  floatTemperature = atof(temperature);
//  Serial.println(floatTemperature);
  
  for (w = 0; w < 4; w++) {

    if(floatTemperature>38){
      matrix.setTextColor(matrix.Color333(7, 0, 0));  //red
      }
    else if(floatTemperature>37.5){
      matrix.setTextColor(matrix.Color333(4, 7, 0));  //yellow
      }
    else {matrix.setTextColor(matrix.Color333(0, 7, 0));}  //green
 

    matrix.print(temperature[w]);
  }
}
void printHeight(String height){
  matrix.setCursor(39, 8);
  uint8_t w = 0;
  for (w = 0; w < 3; w++) {
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print(height[w]);
  }
}


void template_function() {
  uint8_t w = 0;
  char *str = "Temp :";
  matrix.setCursor(3, 0);
  for (w = 0; w < 6; w++) {
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(str[w]);
  }

  w = 0;
  char *str_2 = "Hght :";
  matrix.setCursor(3, 8);
  for (w = 0; w < 6; w++) {
    //    matrix.setTextColor(Wheel(w));
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print(str_2[w]);
  }
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if (WheelPos < 8) {
    return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if (WheelPos < 16) {
    WheelPos -= 8;
    return matrix.Color333(0, 7 - WheelPos, WheelPos);
  } else {
    WheelPos -= 16;
    return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}
