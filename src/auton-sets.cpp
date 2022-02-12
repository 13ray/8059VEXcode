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
  waitBase(1500);

  // right neutral mogo
  baseTurn(306, FMG_TURN_KP, FMG_TURN_KD); // face mogo
  waitBase(8000);

  baseMove(36, FMG_KP, FMG_KD); // go to mogo
  waitBase(8000);

  liftPos = 0;
  waitLift();
  baseMove(14, FMG_KP-0.03, FMG_KD); // intake right neutral
  waitBase(5000);
  wait(200, msec);

  // scoring neutral and red mogos
  liftPos = 2;
  waitLift();
  baseTurn(312.5, FMGS_TURN_KP+0.02, 0); //face platform
  waitBase(8000);
  wait(500, msec);

  baseCorrection = 0;
  baseMove(56.5, FMGS_KP, FMGS_KD); //go to platform
  waitBase(8500);
  resetRot();
  baseCorrection = 0.1;

  liftPos = 1;
  waitLift();
  frontMOG(t); // score
  wait(150, msec);

  // tall neutral mogo
  baseTurn(312, 1, 0);
  waitBase(3000);
  baseMove(-25, DEFAULT_KP, DEFAULT_KD); // move away from platform
  waitBase(6000);

  liftPos = 0;
  frontMOG(f);

  baseTurn(241, 1, 0); // face mogo
  waitBase(5000);

  baseCorrection = 0;
  baseMove(-24.5, DEFAULT_KP - 0.075, DEFAULT_KD); // intake mogo
  waitBase(8000);
  twoBar(t);
  resetRot();
  baseCorrection = 0.1;
  baseTurn(241, 1, 0);
  waitBase(5000);

  // left red mogo
  baseMove(-48, BMG_KP, BMG_KD);
  waitBase(9000);
  resetRot();

  printf("face mogo\n\n\n");
  baseTurn(32, BMG_TURN_KP, BMG_TURN_KD); // face mogo
  waitBase(5000);
  resetRot();

  printf("intake mogo]n\n\n");
  baseMove(10, BMG_KP, 0); // intake mogo
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
  baseMove(25, FMG_KP - 0.03, FMG_KD); // intake left neutral
  waitBase(5000);

  liftPos = 5;
  waitLift();

  baseTurn(280, MGS_TURN_KP, MGS_TURN_KD);
  waitBase(5000);
  baseMove(35, MGS_KP, MGS_KD);
  waitBase(10000);

}

void test() {

  resetCoords(0, 0, 0);
  // baseMove(24, DEFAULT_KP, DEFAULT_KD);
  // waitBase(5000);

  task liftTask(Lift);
  liftPos = 1;
  waitLift();
  baseMove(10, DEFAULT_KP, DEFAULT_KD);
  waitBase(5000);                                                                                                                                                                                                                                                                                                                                                               
}