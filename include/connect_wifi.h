<<<<<<< HEAD
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

=======
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

>>>>>>> 98cd8e5f5df86b6a18005cde16f02048bea3ac0a
#endif