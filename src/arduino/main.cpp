#include <Arduino.h>

#include "Test.h"

Test test = Test();
void setup()
{
  test.init();
}

void loop()
{
  test.tick();
}

