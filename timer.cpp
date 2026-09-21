void initializeTimer(void)
{
  // see requirements for the function from SpedenSpelit.h
  noInterrupts();          // keskeytykset pois päältä

  TCCR1A = 0;              // tyhjätään ohjaus rekisterit
  TCCR1B = 0;
  TCNT1  = 0;              // nollataan laskuri

  // asetetaan rekisteri 1 Hz taajuuteen 16 MHz:illä
  // 16MHz / (esiskaalaaja * haluttu taajuus)
  // (16,000,000 / (1024 * 1)) - 1 = 15624
  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);  // CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // esiskaalaaja -> 1024
  //TIMSK1 |= (1 << OCIE1A); // Timer1 enable <- tämä pitää disablettaa sitten jossain kun peli loppuu -> TIMSK1 &= ~(1 << OCIE1A);

  interrupts();             // keskeytykset päälle
}
int i = 0;
ISR(TIMER1_COMPA_vect)
{
  i++;
  Serial.println(i);
  
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
}