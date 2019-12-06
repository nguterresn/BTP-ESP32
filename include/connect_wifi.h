#ifndef CWIFI_H_   /* Include guard */
#define CWIFI_H_

#include <WiFi.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

/* Serial */
#define BAUD 9600

/* Cases */
#define ROOT 0
#define A 1
#define B 2
#define C 3
#define IP_WIDTH 16
#define MAC_WIDTH 30
#define NUM_BANANAS 2

typedef struct {

    char ipaddr[IP_WIDTH];
    char macaddr[MAC_WIDTH];
    uint8_t monkey;
    uint8_t banana[NUM_BANANAS];
    
} node;

typedef struct {

    uint8_t route_A;
    uint8_t route_B;
    uint8_t route_C;
    
} rout;

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