#ifndef CWIFI_H_   /* Include guard */
#define CWIFI_H_

#include <WiFi.h>
#include <Arduino.h>
#include "ESP32Ping.h"

boolean ConnectWifi();

boolean CheckNetwork(const char *addr);

boolean SetNetwork(IPAddress ip, IPAddress gateway, IPAddress subnet);

#endif