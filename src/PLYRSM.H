#ifndef PLYRSM_H
#define PLYRSM_H

#include "events.h"
#include "types.h"
#include "model.h"

avatarStates checkIdleNext(Avatar *, avatarEvents, UINT16);
void update(Avatar *, avatarEvents, UINT16);

#endif
