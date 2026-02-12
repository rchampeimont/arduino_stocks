void stop() {
  digitalWrite(LED_BUILTIN, HIGH);
  while (true);
}

void fatalError(String s) {
  printStatusMessageOnLCD(s);
  printFatalError();
  stop();
}