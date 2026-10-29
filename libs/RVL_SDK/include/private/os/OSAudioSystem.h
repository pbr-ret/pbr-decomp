#ifndef PRIVATE_OS_AUDIO_SYSTEM_H
#define PRIVATE_OS_AUDIO_SYSTEM_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void __AIClockInit(BOOL compatB);
void __OSInitAudioSystem(void);
void __OSStopAudioSystem(void);

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_OS_AUDIO_SYSTEM_H
