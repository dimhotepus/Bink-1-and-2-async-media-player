// binkw.cc : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
//
#include "../deps/bink/bink.h"

RADDEFSTART

void RADEXPLINK BinkSetTimerRead(BINKTIMERREAD) {}

void* RADEXPLINK BinkLogoAddress(void) { return 0; }

void RADEXPLINK BinkSetError(char const*) {}
char* RADEXPLINK BinkGetError(void) { return 0; }

HBINK RADEXPLINK BinkOpen(char const*, U32) { return 0; }
HBINK RADEXPLINK BinkOpenWithOptions(char const*, BINK_OPEN_OPTIONS const*,
                                     U32) {
  return 0;
}

void RADEXPLINK BinkGetFrameBuffersInfo(HBINK, BINKFRAMEBUFFERS*) {}
void RADEXPLINK BinkRegisterFrameBuffers(HBINK, BINKFRAMEBUFFERS*) {}
S32 RADEXPLINK BinkDoFrame(HBINK) { return 0; }
S32 RADEXPLINK BinkDoFramePlane(HBINK, U32) { return 0; }
void RADEXPLINK BinkNextFrame(HBINK) {}
S32 RADEXPLINK BinkWait(HBINK) { return 0; }
void RADEXPLINK BinkClose(HBINK) {}
S32 RADEXPLINK BinkPause(HBINK, S32) { return 0; }
S32 RADEXPLINK BinkCopyToBuffer(HBINK, void*, S32, U32, U32, U32, U32) {
  return 0;
}
S32 RADEXPLINK BinkCopyToBufferRect(HBINK, void*, S32, U32, U32, U32, U32, U32,
                                    U32, U32, U32) {
  return 0;
}
S32 RADEXPLINK BinkGetRects(HBINK, U32) { return 0; }
void RADEXPLINK BinkGoto(HBINK, U32, S32) {}  // use 1 for the first frame
U32 RADEXPLINK BinkGetKeyFrame(HBINK, U32, S32) { return 0; }
void RADEXPLINK BinkFreeGlobals(void) {}
S32 RADEXPLINK BinkGetPlatformInfo(S32, void*) { return 0; }
void RADEXPLINK BinkRegisterGPUDataBuffers(HBINK, BINKGPUDATABUFFERS*) {}
S32 RADEXPLINK BinkGetGPUDataBuffersInfo(HBINK, BINKGPUDATABUFFERS*) {
  return 0;
}

S32 RADEXPLINK BinkSetVideoOnOff(HBINK, S32) { return 0; }
S32 RADEXPLINK BinkSetSoundOnOff(HBINK, S32) { return 0; }
void RADEXPLINK BinkSetVolume(HBINK, U32, S32) {}
void RADEXPLINK BinkSetPan(HBINK, U32, S32) {}
void RADEXPLINK BinkSetSpeakerVolumes(HBINK, U32, U32*, S32*, U32) {}
void RADEXPLINK BinkService(HBINK) {}

S32 RADEXPLINK BinkShouldSkip(HBINK) { return 0; }

void RADEXPLINK BinkGetPalette(void*) {}

S32 RADEXPLINK BinkControlBackgroundIO(HBINK, U32) { return 0; }

void RADEXPLINK BinkSetWillLoop(HBINK, S32) {}

#if defined(__RADWIN__) || defined(__RADXENON__) || defined(__RADPS3__)

S32 RADEXPLINK BinkStartAsyncThread(S32, void const*) { return 0; }
S32 RADEXPLINK BinkDoFrameAsync(HBINK, U32, U32) { return 0; }
S32 RADEXPLINK BinkDoFrameAsyncMulti(HBINK, U32*, S32) { return 0; }
S32 RADEXPLINK BinkDoFrameAsyncWait(HBINK, S32) { return 0; }
S32 RADEXPLINK BinkRequestStopAsyncThread(S32) { return 0; }
S32 RADEXPLINK BinkWaitStopAsyncThread(S32) { return 0; }

#endif

HBINKTRACK RADEXPLINK BinkOpenTrack(HBINK, U32) { return 0; }
void RADEXPLINK BinkCloseTrack(HBINKTRACK) {}
U32 RADEXPLINK BinkGetTrackData(HBINKTRACK, void*) { return 0; }

U32 RADEXPLINK BinkGetTrackType(HBINK, U32) { return 0; }
U32 RADEXPLINK BinkGetTrackMaxSize(HBINK, U32) { return 0; }
U32 RADEXPLINK BinkGetTrackID(HBINK, U32) { return 0; }

void RADEXPLINK BinkGetSummary(HBINK, BINKSUMMARY*) {}
void RADEXPLINK BinkGetRealtime(HBINK, BINKREALTIME*, U32) {}

void RADEXPLINK BinkSetFileOffset(U64) {}
void RADEXPLINK BinkSetSoundTrack(U32, U32*) {}
void RADEXPLINK BinkSetIO(BINKIOOPEN) {}
void RADEXPLINK BinkSetFrameRate(U32, U32) {}
void RADEXPLINK BinkSetSimulate(U32) {}
void RADEXPLINK BinkSetIOSize(U32) {}

S32 RADEXPLINK BinkSetSoundSystem(BINKSNDSYSOPEN, UINTa) { return 0; }
S32 RADEXPLINK BinkSetSoundSystem2(BINKSNDSYSOPEN2, UINTa, UINTa) { return 0; }

S32 RADEXPLINK BinkControlPlatformFeatures(S32, S32) { return 0; }

#ifdef __RADWIN__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenDirectSound(UINTa) { return 0; }

// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenWaveOut(UINTa) { return 0; }
#endif

// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenXAudio2(UINTa param) { return 0; }

#ifndef __RADMAC__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenMiles(UINTa) { return 0; }
#endif

#ifdef __RADMAC__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenSoundManager(UINTa param) { return 0; }

// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenRADSS(UINTa param) { return 0; }
#endif

#ifdef __RADLINUX__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenSDLMixer(UINTa param) { return 0; }
#endif

#if defined(__RADNGC__) || defined(__RADWII__)
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenAX(U32 param) { return 0; }

// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenMusyXSound(U32 param) { return 0; }
#endif

#ifdef __RADPS2__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenRAD_IOP(U32 param) { return 0; }
#endif

#ifdef __RADPS3__
void RADEXPLINK BinkFreeGlobals(void) {}

BINKSNDOPEN RADEXPLINK BinkOpenLibAudio(U32 param) { return 0; }
#endif

#ifdef __RADPSP__
BINKSNDOPEN RADEXPLINK BinkOpenPSPSound(U32 param) { return 0; }
#endif

#ifdef __RADNDS__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenNDSSound(U32 param) { return 0; }
#endif

#if defined(__RADXBOX__) || defined(__RADWIN__)
S32 RADEXPLINK BinkDX8SurfaceType(void*) { return 0; }
#endif

#if defined(__RADXENON__) || defined(__RADWIN__)
S32 RADEXPLINK BinkDX9SurfaceType(void*) { return 0; }
#endif

// The BinkBuffer API isn't implemented on DOS, or any of the consoles
#if !defined(__RADDOS__) && !defined(__RADXBOX__) && !defined(__RADNGC__) && \
    !defined(__RADNDS__)

#ifdef __RADMAC__

// #include <windows.h>
// #include <palettes.h>
// #include <qdoffscreen.h>

HBINKBUFFER RADEXPLINK BinkBufferOpen(void* /*WindowPtr*/ wnd, U32 width,
                                      U32 height, U32 bufferflags) {
  return 0;
}
S32 RADEXPLINK BinkGDSurfaceType(void* /*GDHandle*/ gd) { return 0; };
S32 RADEXPLINK BinkIsSoftwareCursor(void* /*GDHandle*/ gd) { return 0; }
S32 RADEXPLINK BinkCheckCursor(void* /*WindowPtr*/ wp, S32 x, S32 y, S32 w,
                               S32 h) {
  return 0;
}

#else

HBINKBUFFER RADEXPLINK BinkBufferOpen(void* /*HWND*/, U32, U32, U32) {
  return 0;
}
S32 RADEXPLINK BinkBufferSetHWND(HBINKBUFFER, void* /*HWND*/) { return 0; }
S32 RADEXPLINK BinkDDSurfaceType(void*) { return 0; }
S32 RADEXPLINK BinkIsSoftwareCursor(void*, void* /*HCURSOR*/) { return 0; }
S32 RADEXPLINK BinkCheckCursor(void* /*HWND*/, S32, S32, S32, S32) { return 0; }
S32 RADEXPLINK BinkBufferSetDirectDraw(void*, void*) { return 0; }

#endif

void RADEXPLINK BinkBufferClose(HBINKBUFFER) {}
S32 RADEXPLINK BinkBufferLock(HBINKBUFFER) { return 0; }
S32 RADEXPLINK BinkBufferUnlock(HBINKBUFFER) { return 0; };
void RADEXPLINK BinkBufferSetResolution(S32, S32, S32) {}
void RADEXPLINK BinkBufferCheckWinPos(HBINKBUFFER, S32*, S32*) {}
S32 RADEXPLINK BinkBufferSetOffset(HBINKBUFFER, S32, S32) { return 0; }
void RADEXPLINK BinkBufferBlit(HBINKBUFFER, BINKRECT*, U32) {}
S32 RADEXPLINK BinkBufferSetScale(HBINKBUFFER, U32, U32) { return 0; }
char* RADEXPLINK BinkBufferGetDescription(HBINKBUFFER) { return 0; }
char* RADEXPLINK BinkBufferGetError() { return 0; }
void RADEXPLINK BinkRestoreCursor(S32) {}
S32 RADEXPLINK BinkBufferClear(HBINKBUFFER, U32) { return 0; }

#endif

void RADEXPLINK BinkSetMemory(BINKMEMALLOC, BINKMEMFREE) {}
void RADEXPLINK BinkUseTelemetry(void*) {}
void RADEXPLINK BinkUseTmLite(void*) {}

RADDEFEND