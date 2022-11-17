//      ////      //      ////       ////      //            ////      //      //      //      //////      //////
//      //  //    //    ////       //          //          //   //     //      ////  ////      //          //  //
//      //  //    //      ////     //          //          ///////     //      //  //  //      ////        ////
//      ////      //    ////         ////      //////      //   //     //      //      //      //////      //  //
//

/*
********************************************************************************************************************* 
* This is Mateus Fernandes' attempt to code a competitive line follower code.
* It also is an branch of the code used at the indoor event, which gave me 2nd place.
* Reason why's to win the Robocore event, that will be taking place at SP.
* Good luck to me.
*********************************************************************************************************************
*/



//---------------------------------------------------------------------------------------------------------------------

#include "CodeItself6.h"

// Object to control robots functions
GeneralFunctions robotDo;
// All explanations of what each function does can be found on CodeItself.h
// All condelines can be found on CodeItself.cpp

/*
>>>>>>>>>>>>>>>     SETUP & LOOP     <<<<<<<<<<<<<<< 
*/

void setup() {
  Serial.begin(9600); //Listening port
  //robotDo.testEngines();
  robotDo.setSensors();

}

void loop() {
  //robotDo.getSensorValues();
  //robotDo.getPosition();
  robotDo.followTheWhiteLine();
}
