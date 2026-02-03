#include <Adafruit_PWMServoDriver.h>
#include <NimBLEDevice.h>

#include "SpiderBot.h"
#include "BLECallbacks.h"

#define BLE_IDENTIFIER_UUID "deb3b3b5-0145-4428-94d4-512440fb021e"
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

static NimBLEServer* pServer;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
SpiderBot robot = SpiderBot(&pwm);
CharacteristicCallbacks charCallback(&robot);

void ble_setup();

void setup() {
  Serial.begin(9600);

  pwm.begin();

  //setup from Adafruit's example code
  pwm.setOscillatorFrequency(27000000); //I need an oscilloscope to set this correctly apparently (?????) buut I don't have one so we're leaving it to default and praying :)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //run all of the ble setup
  ble_setup();

  delay(10);
}

void loop() {
  
}

void ble_setup() {
  //BLE setup
  NimBLEDevice::init("AlfurBLE");

  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(&serverCallbacks);

  //RAW service (setting raw values for arm locations)
  NimBLEService*        pIdentService = pServer->createService(BLE_IDENTIFIER_UUID); //for desktop app to find the service (reuse for the app to find multiple robots)

  NimBLEService*        pRawService = pServer->createService("RAWS");
  NimBLECharacteristic* pFrontLeftCharacteristic = pRawService->createCharacteristic("FL");
  NimBLECharacteristic* pFrontRightCharacteristic = pRawService->createCharacteristic("FR");
  NimBLECharacteristic* pBackLeftCharacteristic = pRawService->createCharacteristic("BL");
  NimBLECharacteristic* pBackRightCharacteristic = pRawService->createCharacteristic("BR");

  //default position for robot (Basically the equivalent of a t-pose for animation rigs: all neutral/central positions)
  pFrontLeftCharacteristic->setValue  ((LEG_CONFIG){0.0, 0.0, 0.0});
  pFrontRightCharacteristic->setValue ((LEG_CONFIG){0.0, 0.0, 0.0});
  pBackLeftCharacteristic->setValue   ((LEG_CONFIG){0.0, 0.0, 0.0});
  pBackRightCharacteristic->setValue  ((LEG_CONFIG){0.0, 0.0, 0.0});

  pFrontLeftCharacteristic->setCallbacks    (&charCallback);
  pFrontRightCharacteristic->setCallbacks   (&charCallback);
  pBackLeftCharacteristic->setCallbacks     (&charCallback);
  pBackRightCharacteristic->setCallbacks    (&charCallback);

  //start services
  pIdentService->start();
  pRawService->start();

  //create and start advertising instance
  NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->setName("Alfur");
  pAdvertising->addServiceUUID(pIdentService->getUUID());
  pAdvertising->addServiceUUID(pRawService->getUUID());

  pAdvertising->enableScanResponse(false);
  pAdvertising->start();

  Serial.println("BLE Advertising");
}
