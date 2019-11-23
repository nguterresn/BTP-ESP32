#ifndef CWIFI_H_   /* Include guard */
#define CWIFI_H_

#include <WiFi.h>
#include <Arduino.h>
#include "ESP32Ping.h"

/**
 * Establish a WiFi Connection
 * return: true is success, false in case of timeout (15sec)
 * */
boolean ConnectWifi(const char* ssid, const char* pass);

/**
 * Check Available Nodes in the network
 * input: addr is the broadcast IP
 * return: true if some node is already on the network, false if not
 * */
boolean CheckNetwork(const char *addr);

/**
 * Sets network settings
 * */
boolean SetNetwork(IPAddress ip, IPAddress gateway, IPAddress subnet);

/**
 * Sets Node hierarchy
 * return: returns ip address of the node
 * */
boolean Node_Election(IPAddress gateway, IPAddress subnet, const char* broadcast);

#endif