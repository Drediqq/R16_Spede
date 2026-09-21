void checkGame(byte nbrOfButtonPush)
{
  // see requirements for the function from SpedenSpelit.h
}

void initializeGame()
{
  litCount = 0;
  matchedCount = 0;
  buttonNumber = -1;
  newTimerInterrupt = false;
  randomSeed(analogRead(A1));
}

void startTheGame()
{
  //valoshow pitää jotenki lopettaa joko täs tai sitte sielä ite valoshowssa
  //gameOn = true; // jos halutaan se näin ratkasta esimerkiks
  initializeGame();
  initializeTimer();
  TIMSK1 |= (1 << OCIE1A);

}