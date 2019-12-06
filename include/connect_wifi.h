#ifndef CWIFI_H_   /* Include guard */
#define CWIFI_H_

#include <WiFi.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define SSID "Nuno Guterres"
#define PASS "nuno12345"

/**
 * Establish a WiFi Connection
 * return: true is success, false in case of timeout (15sec)
 * */
boolean ConnectWifi(const char* ssid, const char* pass);

/**
 * Sets network settings
 * */
boolean SetAddress(IPAddress ip, IPAddress gateway, IPAddress subnet);

#endif