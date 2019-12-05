#ifndef CWIFI_H_   /* Include guard */
#define CWIFI_H_

#include <WiFi.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define ROOT A
#define A 1
#define B 2
#define C 3

typedef struct{
    char *ipaddr;
    uint8_t father;
    uint8_t *children;
} node;

typedef struct{
    int8_t conc_b = B;
    int8_t conc_c = C;
} route_A;

typedef struct{
    int8_t conc_a = A;
    int8_t conc_c = A;
} route_B;

typedef struct{
    int8_t conc_a = A;
    int8_t conc_b = A;
} route_C;


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