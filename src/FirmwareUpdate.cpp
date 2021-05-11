#include "PN5180_Firmware.h"
#include "Firmware.h"

#ifdef ESP32
    #define PN5180_RST_PIN      22
    #define PN5180_BUSY_PIN     33
    #define PN5180_REQ_PIN      2
    #define PN5180_NSS_PIN      15

    #define HOST_MOSI_PIN       13
    #define HOST_MISO_PIN       12
    #define HOST_SCK_PIN        14
#else
    #define PN5180_RST_PIN      PB1
    #define PN5180_BUSY_PIN     PB7
    #define PN5180_REQ_PIN      PA1
    #define PN5180_NSS_PIN      PB0

    #define HOST_MOSI_PIN       PA7
    #define HOST_MISO_PIN       PA6
    #define HOST_SCK_PIN        PA5
#endif

PN5180_Firmware Pn5180(PN5180_RST_PIN, PN5180_BUSY_PIN, PN5180_REQ_PIN, PN5180_NSS_PIN, HOST_MOSI_PIN, HOST_MISO_PIN, HOST_SCK_PIN);

void setup()
{
    Serial.begin(115200L);

    Pn5180.Begin();
}

void loop()
{
    Serial.println("Press any key to update PN5180 firmware.");
    Serial.flush();

    while (!Serial.available());
    while (Serial.available()) {
        Serial.read();  
    }

    Serial.flush();
    Pn5180.End();
    Serial.end();

    Serial.begin(115200L);
    Pn5180.Begin();

    if (Pn5180.DoUpdateFirmware((uint8_t*)PN5180_FIRMWARE, PN5180_FIRMWARE_SIZE)) {
        Serial.println("[Info] Update successful.\n");
    } else {
        Serial.println("[Error] Update failed.\n");
    }
}
