#include <stdio.h>
#include <stdint.h>
#include <map>
#include <vector>
#include <list>
#include <array>
#include <IPAddress.h>

#define NET "sdis_network"
#define PASS "sdis_password"

#define ROOT 0
#define N_NODES 3
#define MAC_WIDTH 30
#define PORT 6535

#define MONKEY 0

#define FROM 0
#define MESSAGE 1
#define TO 2

typedef enum node {root, node_a, node_b, node_c, no_node} node;

typedef enum instruc {LED, HELLO, RECONF} instruc;

typedef enum ret_t {KEEP, FOWARD, IGNORE, ERROR, EMPTY} ret_t;
