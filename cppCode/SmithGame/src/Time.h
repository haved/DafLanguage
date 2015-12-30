#pragma once

#include <stdint.h>

void UpdateDeltaTime();
void UpdateIngameTime();

float    GetDeltaTime();
uint32_t GetDeltaMillis();
uint32_t GetCurrentMillis();
float    GetCurrentSeconds();
uint32_t GetIngameMillis();
float    GetIngameSeconds();
