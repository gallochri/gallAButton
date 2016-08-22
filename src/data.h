#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <FS.h>

void setupSPIFFS();
String formatBytes(size_t bytes);

#endif // DATA_H
