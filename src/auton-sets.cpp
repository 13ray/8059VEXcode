#include "vex.h"

void skills() {
  
  baseCorrection = 0.1;

  // right red mogo
  baseMove(4, DEFAULT_KP, DEFAULT_KD); // intake right red
  waitBase(800);

  task liftTask(Lift);
  liftPos = 5;
  waitLift();

  baseMove(-14, FMG_KP, FMG_KD); // reverse
  waitBase(2000);

  // right neutral mogo
  baseTurn(306.5, FMG_TURN_KP, FMG_TURN_KD); // face mogo
  waitBase(8000);

  baseMove(36, FMG_KP, FMG_KD); // go to mogo
  waitBase(8000);

  liftPos = 0;
  waitLift();
  baseMove(14, FMG_KP-0.03, FMG_KD); // intake right neutral
  waitBase(5000);

  // scoring neutral and red mogos
  liftPos = 2;
  waitLift();
  baseTurn(311.8, FMGS_TURN_KP+0.02, 0); //face platform
  waitBase(8000);
  wait(500, msec);

  baseMove(57, FMGS_KP, FMGS_KD); //go to platform
  waitBase(11000);
  resetRot();

  liftPos = 1;
  waitLift();
  frontMOG(t); // score
  wait(150, msec);

  // tall neutral mogo
  baseMove(-24.5, DEFAULT_KP, DEFAULT_KD); // move away from platform
  waitBase(8000);

  liftPos = 0;
  frontMOG(f);

  baseTurn(241, 1, 0); // face mogo
  waitBase(8000);

  baseCorrection = 0;
  baseMove(-24, DEFAULT_KP - 0.075, DEFAULT_KD); // intake mogo
  waitBase(10000);
  twoBar(t);
  resetRot();
  baseCorrection = 0.1;

  // left red mogo
  baseMove(-49, BMG_KP, BMG_KD);
  waitBase(9000);
  resetRot();

  printf("face mogo\n\n\n");
  baseTurn(35, BMG_TURN_KP, BMG_TURN_KD); // face mogo
  waitBase(5000);
  resetRot();

  printf("intake mogo]n\n\n");
  baseMove(9, BMG_KP, 0); // intake mogo
  waitBase(3500);

  //left neutral mogo
  liftPos = 5;
  waitLift();

  printf("face next mogo\n\n\n");
  baseTurn(265, BMGFR_TURN_KP, BMGFR_TURN_KD);
  waitBase(5000);
  wait(1000, msec);

  liftPos = 0;
  waitLift();
  baseMove(16, FMG_KP - 0.03, FMG_KD); // intake left neutral
  waitBase(5000);

  // liftPos = 5;
  // wait(500, msec);
  // baseTurn(230, BMGFR_TURN_KP, BMGFR_TURN_KD);
  // waitBase(5000);

}

void test() {
  task liftTask(Lift);
  liftPos = 5;
  waitLift();

  resetCoords(0, 0, 0);
  // baseMove(24, DEFAULT_KP, DEFAULT_KD);
  // waitBase(5000);

  baseTurn(90, FMG_TURN_KP, FMG_TURN_KD);
  waitBase(10000);
  wait(5000, msec);
}