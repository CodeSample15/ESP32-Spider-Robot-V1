#pragma once

/*
  Creating custom callbacks for NimBLE to call

  Lots of this was pulled from here: https://github.com/h2zero/NimBLE-Arduino/blob/master/examples/NimBLE_Server/NimBLE_Server.ino
*/

class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
      Serial.printf("Client address: %s\n", connInfo.getAddress().toString().c_str());

      /**
        *  We can use the connection handle here to ask for different connection parameters.
        *  Args: connection handle, min connection interval, max connection interval
        *  latency, supervision timeout.
        *  Units; Min/Max Intervals: 1.25 millisecond increments.
        *  Latency: number of intervals allowed to skip.
        *  Timeout: 10 millisecond increments.
        */
      pServer->updateConnParams(connInfo.getConnHandle(), 24, 48, 0, 180);
  }

  void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
      Serial.printf("Client disconnected - start advertising\n");
      NimBLEDevice::startAdvertising();
  }
} serverCallbacks;

/** Handler class for characteristic actions */
class CharacteristicCallbacks : public NimBLECharacteristicCallbacks {
  SpiderBot* robot;

  CharacteristicCallbacks(SpiderBot* robot) {
    this->robot = robot;
  }

  void onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
      Serial.printf("%s : onRead(), value: %s\n",
                    pCharacteristic->getUUID().toString().c_str(),
                    pCharacteristic->getValue().c_str());
  }

  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
      Serial.printf("%s : onWrite(), value: %s\n",
                    pCharacteristic->getUUID().toString().c_str(),
                    pCharacteristic->getValue().c_str());

      String charUUID = pCharacteristic->getUUID().toString();
      if(charUUID == "FL")
        robot->getFrontLeft()->setConfig((LEG_CONFIG) pCharacteristic->getValue() );
      else if(charUUID == "FR")
        robot->getFrontRight()->setConfig((LEG_CONFIG) pCharacteristic->getValue() );
      else if(charUUID == "BL")
        robot->getBackLeft()->setConfig((LEG_CONFIG) pCharacteristic->getValue() );
      else if(charUUID == "BR")
        robot->getBackRight()->setConfig((LEG_CONFIG) pCharacteristic->getValue() );
  }
};