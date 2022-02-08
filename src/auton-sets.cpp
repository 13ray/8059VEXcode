#include "vex.h"

void skills() {
  task controlTask(Control);
  task odomTask(Odometry);

  resetCoords(0, 0, 0);

  // right red mogo
  baseMove(4, DEFAULT_KP, DEFAULT_KD); // intake right red
  waitBase(800);

  task liftTask(Lift);
  liftPos = 5;
  waitLift();

  baseMove(-14, DEFAULT_KP, DEFAULT_KD); // reverse
  waitBase(800);

  // right neutral mogo
  baseTurn(309, FMG_TURN_KP, FMG_TURN_KD); // face mogo
  waitBase(6000);

  baseMove(36, FMG_KP, FMG_KD); // go to mogo
  waitBase(8000);

  liftPos = 0;
  waitLift();
  baseMove(14, FMG_KP - 0.03, FMG_KD); // intake right neutral
  waitBase(5000);
  resetRot();

  // scoring neutral and red mogos
  liftPos = 2;
  wait(500, msec);
  baseMove(60, FMGS_KP, FMGS_KD); // 33 original
  waitBase(25000);
  resetRot();

  liftPos = 1;
  waitLift();
  frontMOG(t); // score
  wait(150, msec);

  // tall neutral mogo
  baseMove(-21, DEFAULT_KP, DEFAULT_KD); // move away from platform
  waitBase(8000);

  liftPos = 0;
  frontMOG(f);
  baseTurn(245, 1, 0); // face mogo
  waitBase(5000);

  baseMove(-23, DEFAULT_KP - 0.06, DEFAULT_KD); // intake mogo
  waitBase(10000);
  twoBar(t);
  resetRot();

  // left red mogo
  baseMove(-47, BMG_KP, BMG_KD);
  waitBase(15000);
  resetRot();
  wait(500, msec);

  baseTurn(16, BMG_TURN_KP, BMG_TURN_KD); // face mogo
  waitBase(5000);
  resetRot();
  wait(500, msec);

  baseMove(18, BMG_KP - 0.03, 0); // intake mogo
  waitBase(5000);

  // left neutral mogo
  liftPos = 5;
  waitLift();

  baseTurn(280, BMGFR_TURN_KP, BMGFR_TURN_KD);
  waitBase(5000);
}

void test() {
  task controlTask(Control);
  task odomTask(Odometry);

  resetCoords(0, 0, 0);
  baseMove(24, DEFAULT_KP, DEFAULT_KD);
  waitBase(5000);

  // baseTurn(90, FMG_TURN_KP, FMG_TURN_KD);
  // waitBase(5000);
}