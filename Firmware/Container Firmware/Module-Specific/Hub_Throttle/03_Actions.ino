//|-------------------|
//|      Actions      |
//|-------------------|

void Throttle_Action() {
  if (Throttle[0] & 1) {
    throttle_pcont = true;
  } else {
    throttle_pcont = false;
  }
  if (Throttle[0] & 2) {
    throttle = 0;
  }
  mySimpit.send(THROTTLE_MESSAGE, throttle);
}
