#include "vex.h"

void skills() {

  // right red mogo
  baseMove(4, DEFAULT_KP, DEFAULT_KD); // intake right red
  waitBase(800);

  task liftTask(Lift);
  liftPos = 5;
  waitLift();

  baseMove(-13, DEFAULT_KP, DEFAULT_KD); // reverse
  waitBase(800);

  // right neutral mogo
  baseTurn(302, FMG_TURN_KP, FMG_TURN_KD); // face mogo
  waitBase(5000);

  baseMove(36, FMG_KP, FMG_KD); // go to mogo
  waitBase(8000);

  liftPos = 0;
  waitLift();
  baseMove(14, FMG_KP - 0.03, FMG_KD); // intake right neutral
  waitBase(5000);

  // scoring neutral and red mogos
  liftPos = 2;
  wait(500, msec);
  baseTurn(311, FMGS_TURN_KP, FMGS_TURN_KD); //face platform
  waitBase(5000);

  baseMove(56.5, FMGS_KP, FMGS_KD); //go to platform
  waitBase(10000);
  resetRot();

  liftPos = 1;
  waitLift();
  frontMOG(t); // score
  wait(150, msec);

  // tall neutral mogo
  baseMove(-23.5, DEFAULT_KP, DEFAULT_KD); // move away from platform
  waitBase(8000);

  liftPos = 0;
  frontMOG(f);
  baseTurn(243, 1, 0); // face mogo
  waitBase(5000);

  baseMove(-24, DEFAULT_KP - 0.07, DEFAULT_KD); // intake mogo
  waitBase(10000);
  twoBar(t);
  resetRot();

  // left red mogo
  baseMove(-49, BMG_KP, BMG_KD);
  waitBase(15000);
  resetRot();
  wait(1000, msec);

  baseTurn(33, BMG_TURN_KP, BMG_TURN_KD); // face mogo
  waitBase(5000);
  resetRot();
  wait(1000, msec);

  baseMove(15, BMG_KP+0.1, 0); // intake mogo
  waitBase(3500);
  wait(1000, msec);

  // left neutral mogo
  // liftPos = 5;
  // waitLift();

  // baseTurn(280, BMGFR_TURN_KP, BMGFR_TURN_KD);
  // waitBase(5000);

  // liftPos = 0;
  // waitLift();
  // baseMove(14, FMG_KP - 0.03, FMG_KD); // intake left neutral
  // waitBase(5000);

  // liftPos = 5;
  // wait(500, msec);
  // baseTurn(230, BMGFR_TURN_KP, BMGFR_TURN_KD);
  // waitBase(5000);

}

void test() {
  liftPos = 5;
  waitLift();

  resetCoords(0, 0, 0);
  // baseMove(24, DEFAULT_KP, DEFAULT_KD);
  // waitBase(5000);

  baseTurn(90, FMG_TURN_KP, FMG_TURN_KD);
  waitBase(5000);
}