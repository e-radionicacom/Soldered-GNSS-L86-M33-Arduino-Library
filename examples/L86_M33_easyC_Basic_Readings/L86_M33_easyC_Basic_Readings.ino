/**
 **************************************************
 *
 * @file        L86_M33_easyC_Basic_Readings.ino
 * @brief       This code will try to read GNSS Latitude, Longitude, Time, Date, Speed and Altitude and display it on
 *the Serial monitor at 115200 baud. To successfuly run the sketch, connect the GNSS module to one of the Dasduino
 *boards via easyC, upload the code and open the serial monitor at 115200 bauds to see the data.
 *
 *              For best results, GNSS module must be outside!
 *
 *              Soldered L86-M33 GNSS easyC Breakout: www.solde.red/333213
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 *
 * @authors     robert@soldered.com
 ***************************************************/

#include "GNSS-L86-M33-SOLDERED.h"

// Create the GNSS object
GNSS gnss;

// The default I2C address is 0x30
// You may change the address via the switches on the front of the board
// In this table, 'x' represents a switch toggled 'UP'
// Address | 1 | 2 | 3 |
// 0x30    |   |   |   |
// 0x31    |   |   | x |
// 0x32    |   | x |   |
// 0x33    |   | x | x |
// 0x34    | x |   |   |
// 0x35    | x |   | x |
// 0x36    | x | x |   |
// 0x37    | x | x | x |

void setup()
{
    // Enable Serial output
    Serial.begin(115200);

    // To use a custom I2C address, use begin(0x34), for example
    if (!gnss.begin())
    {
        Serial.println("GNSS not found!");
        while (true)
        {
            delay(100);
        }
    }

    Serial.println("GNSS initialized!");
}

void loop()
{
    // Wait while the GNSS module has not yet read any useful data
    // Code will halt here until first good Latitude and Longitude data is read and stored
    // Depending on your antenna, it could take a couple seconds
    while (!gnss.GNSSAvailable())
    {
        delay(1);
    }

    // Get all available data
    // Note the data types
    float lat = gnss.getLatitude();
    float lng = gnss.getLongitude();
    uint16_t year = gnss.getYear();
    uint8_t month = gnss.getMonth();
    uint8_t day = gnss.getDay();
    uint8_t hour = gnss.getHour();
    uint8_t minute = gnss.getMinute();
    uint8_t seconds = gnss.getSeconds();

    // Print location data
    Serial.print("Latitude: ");
    Serial.println(lat, 6);
    Serial.print("Longitude: ");
    Serial.println(lng, 6);

    // Print time
    char timeBuf[10];
    sprintf(timeBuf, "%02d:%02d:%02d", hour, minute, seconds);
    Serial.print("Time: ");
    Serial.println(timeBuf);

    // Print date
    Serial.print("Date: ");
    Serial.print(day);
    Serial.print("/");
    Serial.print(month);
    Serial.print("/");
    Serial.println(year);

    // Pprint a newline and wait a bit before the next output
    Serial.println();
    delay(1000);
}
