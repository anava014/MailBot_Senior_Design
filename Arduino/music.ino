void liftOffMelody(){
  tone(speaker, 500);
  delay(25);
  tone(speaker, 600);
  delay(50);
  noTone(speaker);
  delay(125);
  tone(speaker, 500);
  delay(25);
  tone(speaker, 600);
  delay(50);
  noTone(speaker);
}

void bootMelody(){
  tone(speaker, 300);
  delay(25);
  tone(speaker, 400);
  delay(50);
  tone(speaker, 500);
  delay(25);
  tone(speaker, 600);
  delay(50);
  noTone(speaker);
}
