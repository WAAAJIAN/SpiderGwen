#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "ST3215_driver.h"
#include "leg_kinematics.h"
#include "spider.h"

// --- Shared peripheral instances ---
extern ST3215_driver servo;

uint8_t tibia_ids[NUM_LEGS] = {1, 4, 7, 10, 13, 16};
uint8_t femur_ids[NUM_LEGS] = {2, 5, 8, 11, 14, 17};
uint8_t coxa_ids[NUM_LEGS]  = {3, 6, 9, 12, 15, 18};

#endif