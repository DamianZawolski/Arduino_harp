// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "79f6306f-8295-4c94-98a1-edd6612d9ce9";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password


String tekst_IOT;
int wybrana_glosnosc;
int wybrana_tonacja;
int wybrany_instrument;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(tekst_IOT, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(wybrana_glosnosc, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(wybrana_tonacja, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(wybrany_instrument, READ, 1 * SECONDS, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
