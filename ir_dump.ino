//*********************************************************************************************************
// IR_DUMP dumps infrared (IR) codes  from infrared remote controls to the serial console.
// The wiring definded in this script is for a  M5Stack atom lite microcontroller based on a ESP32 pico. 
// The atom lite provides a grove connector where the M5Stack Mini Infrared Emitter & Receiver Unit can be connected without soldering or using breadboards
// Please adapt the scrip for your controller and IR setup
//*********************************************************************************************************
//
// Internal wiring scheme for a M5Stack atom lite controller with M5Stack Mini Infrared Emitter & Receiver Unit:
// see (https://docs.m5stack.com/#/en/core/atom_lite?id=schematic) as reference.
//
//   ______________________________________________________________
//   |                              M5Stack                        |
//   |                             atom lite                       |
//   |||  <-RESET                                                  |
//   |||   Button         --------------------------------         |
//   |                    |                               |        |
//   |                    |          User Button          |        |
//   |                    |             GPIO39            |        |
//   |                    |                               |        |
//   |                    |       ____________________    |        |
//   |                    |       |  Multi-color LED  |   |        |
//   |                    |       |  SK6812 - 3525    |   |        |
//   |                    |       |     GPIO27        |   |        |
//   |                    |       _____________________   |        |
//   |                    |--------------------------------        |
//   | __________________________         _______________________  |
//   | |    USB-C (USB 2 UART)   |       |Grove 4-Pin connector |  |  
//   | |UART GPIO3(RX),GPIO1(TX) |       | GND|5V|GPIO26|GPIO32 |  |
//   | __________________________|       |______________________|  |
//   |_____________________________________________________________|
//                ||                               ||
//                ||  USB cable                    || 4 pin grove connector (comes with IR unit)
//                ||                               ||
//        --------------------           --------------------------------
//       |  Your computer     |          |      M5stack                  |
//       | Termial emulation  |          | Mini Infrared Emitter &       | 
//       |                    |          |     Receiver Unit             |
//       |   (115200,8,n,1    |          |  (IR emmiter)   (IR receiver) |
//       ----------------------          _________________________________
//
//
//



// first release on 12/2020
// Version 002 , Dec.11 2020
//


// THE SOFTWARE IS PROVIDED "AS IS" FOR PRIVATE USE ONLY, IT IS NOT FOR COMMERCIAL USE IN WHOLE OR PART OR CONCEPT.
// FOR PERSONAL USE IT IS SUPPLIED WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR
// OR COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//
//



//**************************************************************************************************
//                                           LIBRARIES                                             *
//**************************************************************************************************
#include <Arduino.h>
#include <IRremote.h>  // IRremote lib (https://github.com/z3t0/Arduino-IRremote) 



//**************************************************************************************************
//                                           PIN MAPPING                                           *
//**************************************************************************************************
//GPIO1     Atom lite internal USB UART converter TXD
//GPIO3     Atom lite internal USB UART converter RXD
//GPIO26    Atom lite grove connector Pin 3 -> M5Stack IR Sender and Receiver Unit infrared trasmit(TX)
//GPIO32    Atom lite grove connector Pin 3 -> M5Stack IR Sender and Receiver Unit infrared receive(RX)
 // M5 atom lite grove connector, which connects the external m5 IR unit uses GPIO32 for IR receive and GPIO26 for IR trasmit

int SERIAL_RX=3;
int SERIAL_TX=1;
int RECV_PIN = 32;
IRrecv irrecv(RECV_PIN);



//**************************************************************************************************
//                                      GLOBAL VARIABLES                                           *
//**************************************************************************************************

decode_results results;


//**************************************************************************************************
//                                           S E T U P                                             *
//**************************************************************************************************
void setup() {
  Serial.begin(115200, SERIAL_8N1, SERIAL_RX, SERIAL_TX); // M5 atom lite internal UART ot USB brige uses RXD PIN=3 TXD PIN=1
  delay(500);
  Serial.println();
  Serial.println("IR dump tool");
  Serial.println("Align your remote towards the IR sensor and push one button a time.");
  irrecv.enableIRIn();
  Serial.println("IR Receiver ready");
}
//**************************************************************************************************
//                                            L O O P                                              *
//**************************************************************************************************
void loop() {
  if (irrecv.decode(&results)) {
       Serial.print("IR protocol: ");
       if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.print(" IR code: ");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive new value from the lib
  }
  delay(500);
}
