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
int Command_counter;
char RcvChar;
String data[10];
String InData;
boolean commandReceived = false;

float  floatTemperature = 0;
String receivedString;
char charReceived[8];
String dataTemperature, dataHeight;
float dataTemperatureFloat;
String dataTemperatureString;
void setup() {
  Serial.begin(9600);
  //  Serial1.begin(9600);
  //  delay(1000);
  matrix.begin();

}

void loop() {

  commandReceived = false;
  Command_counter = 0;
  
  int buffersize = 0;

  while (Serial.available() > 1)
  {
    command();        //讀取指令
    buffersize++;
//    Serial.println(data[0]);
//    Serial.println(data[1]);
    dataTemperature = data[0];
    dataTemperatureFloat = dataTemperature.toFloat();
    dataTemperatureString = String(dataTemperatureFloat);
    dataHeight      = data[1];

  }


//    Serial.print("Data Temperature: ");
//    Serial.println(dataTemperatureString);
//    Serial.print("Data Height: ");
//    Serial.println(dataHeight);




  //  Serial.println("Testing");
  //  Serial.println(dataTemperature);
  //  Serial.println(dataHeight);
  //  Serial.println("Endtesting");

  //  dataTemperature = InData[0] + InData[1] + InData[2


  //  if (Serial.available() > 0) {
  //        receivedString = Serial.readString();
  //        Serial.println(receivedString);
  //        receivedString.toCharArray(charReceived, 9);
  //        Serial.println(charReceived);
  //        dataTemperature = char(charReceived[0]) + char(charReceived[1]) + char(charReceived[2]) + char(charReceived[3]);
  //        dataHeight = char(charReceived[5]) + char(charReceived[6]) + char(charReceived[7]);
  //        Serial.println(dataTemperature);
  //        Serial.println(dataHeight);
  //
  //
  //
  //    }
  matrix.setTextSize(1);  //1=8 2=14 3=21
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  template_function();
  printTemp(dataTemperatureString);
  printHeight(dataHeight);
    if (commandReceived == true)
  {
//          process();
    cleardata();
  }
//  delay(500);
}



void printTemp(String temperature) {
//  matrix.setTextSize(2);
  matrix.setCursor(18, 8);
  uint8_t w = 0;
  floatTemperature =  temperature.toFloat();
  //  floatTemperature = atof(temperature);
  //  Serial.println(floatTemperature);

  for (w = 0; w < 6; w++) {

    if (floatTemperature > 37.5) {
      matrix.setTextColor(matrix.Color333(7, 0, 0));  //red, according to cdc, 37.5 is the limit to fever
    }
//    else if (floatTemperature > 37.5) {
//      matrix.setTextColor(matrix.Color333(4, 7, 0));  //yellow
//    }
    else {
      matrix.setTextColor(matrix.Color333(0, 7, 0)); //green
    }
    matrix.print(temperature[w]);
    }
//    matrix.setTextSize(1);
}
void printHeight(String height) {
  matrix.setCursor(24, 24);
  uint8_t w = 0;
  for (w = 0; w < 3; w++) {
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print(height[w]);
  }
}

void template_function() {
  uint8_t w = 0;
  char *str = "Temp:";
  matrix.setCursor(3, 0);
  for (w = 0; w < 5; w++) {
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(str[w]);
  }

   w = 0;
  char *str_2 = "Height:";
  matrix.setCursor(3, 16);
  for (w = 0; w <7 ; w++) {
    //    matrix.setTextColor(Wheel(w));
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print(str_2[w]);
  }
  w = 0 ;
    char *str_3 = "C";
  matrix.setCursor(58, 8);
  for (w = 0; w < 1; w++) {
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(str_3[w]);
  }

   w = 0 ;
    char *str_5 = ".";
  matrix.setCursor(53, 3);
  for (w = 0; w < 1; w++) {
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(str_5[w]);
  }


  

  w = 0;
  char *str_4 = "cm";
  matrix.setCursor(53, 24);
  for (w = 0; w < 2; w++) {
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print(str_4[w]);
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

void cleardata() {
  for (int i = 0; i < 10; i++) {
    data[i] = "";
  }

}
