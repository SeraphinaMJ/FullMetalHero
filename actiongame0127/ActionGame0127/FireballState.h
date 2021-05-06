#ifndef FIREBALLSTATE_H
#define FIREBALLSTATE_H

typedef struct State State;

void MakeFireballPhaseOneState(State* pResult);
void FireballState_PhaseOneStart(State* pState);
void FireballState_PhaseOneUpdate(State* pState, float dt);
void FireballState_PhaseOneEnd(State* pState);

void MakeFireballPhaseTwoState(State* pResult);
void FireballState_PhaseTwoStart(State* pState);
void FireballState_PhaseTwoUpdate(State* pState, float dt);
void FireballState_PhaseTwoEnd(State* pState);

#endif