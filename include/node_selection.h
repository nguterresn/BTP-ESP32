#ifndef _ND_SELECT   /* Include guard */
#define _ND_SELECT

#include <WiFi.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

/* SELECTION RELATED */
#define ROOT 0
#define IP_WIDTH 16
#define MAC_WIDTH 30
#define NUM_BANANAS 2

#define MAC_A "A4:CF:12:54:DD:D4"
#define MAC_B "3C:71:BF:EA:B6:A8"
#define MAC_C "30:AE:A4:15:1C:0C"

#define IP_A "172.20.10.1"
#define IP_B "172.20.10.2"
#define IP_C "172.20.10.3"
/*********************/

/* isto é confuso */
typedef uint8_t node;
/*node A = 0, B = 1, C = 2;*/

typedef struct {
    node A;
    node B;
    node C;
} route_t;

typedef struct {
    uint8_t ip_id;
    char macaddr[MAC_WIDTH];
    node monkey;
    node banana[NUM_BANANAS];
    route_t *route;
} node_t;


/**
 * Sets node hierarchy 
 * @father
 * @children
 * @mac_address
 * @ip_id
 * 
 * returns: 0 (false) if an error occurs
 * */
boolean NodeSetup();

/**
 * Creates Server if node has children, client if not
 * returns: 0 (false) if an error occurs
 * */
boolean CreateSocket();

#endif