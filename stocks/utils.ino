void stop() {
  digitalWrite(LED_BUILTIN, HIGH);
  while (true);
}

void fatalError(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printStatusMessageOnLCD(format, args);
  printFatalError();
  stop();

  va_end(args);
}