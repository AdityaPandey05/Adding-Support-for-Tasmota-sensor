#include <Wire.h> 

#define NEWSENSOR_I2C_ADDRESS 0x40 
void Xsns99_Init(void) {
  Wire.begin(); 
  AddLog_P2(LOG_LEVEL_DEBUG, PSTR("XSNS:99 Sensor initialized"));
}

bool Xsns99_Read(void) {
  Wire.beginTransmission(NEWSENSOR_I2C_ADDRESS);
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.requestFrom(NEWSENSOR_I2C_ADDRESS, 2);
  
  if (Wire.available() == 2) {
    int data = Wire.read() << 8 | Wire.read(); 
    
    char payload[16];
    snprintf(payload, sizeof(payload), "{\"Sensor\":%d}", data);
    MqttPublishPrefixTopic_P(RESULT_OR_TELE, PSTR("SENSOR"), payload);
    return true;
  }
  return false;
}
