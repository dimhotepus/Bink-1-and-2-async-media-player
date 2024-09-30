// binkw.cc : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
//
#include "../deps/bink/bink.h"

RADDEFSTART

#ifdef __RADMAC__
HBINK RADEXPLINK BinkMacOpen(void /*FSSpec*/* fsp, U32 flags) { return 0; }
#endif

#ifdef __RADNDS__
RADEXPFUNC HBINK RADEXPLINK BinkNDSOpen(void /*FSFileID*/* fid, U32 flags) {
  return 0;
}
#endif

void PTR4* RADEXPLINK BinkLogoAddress(void) { return 0; }

void RADEXPLINK BinkSetError(const char PTR4*) {}
char PTR4* RADEXPLINK BinkGetError(void) { return 0; }

HBINK RADEXPLINK BinkOpen(const char PTR4*, U32) { return 0; }

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

S32 RADEXPLINK BinkSetVideoOnOff(HBINK, S32) { return 0; }
S32 RADEXPLINK BinkSetSoundOnOff(HBINK, S32) { return 0; }
void RADEXPLINK BinkSetVolume(HBINK, U32, S32) {}
void RADEXPLINK BinkSetPan(HBINK, U32, S32) {}
void RADEXPLINK BinkSetMixBins(HBINK, U32, U32 PTR4*, U32) {}
void RADEXPLINK BinkSetMixBinVolumes(HBINK, U32, U32 PTR4*, S32 PTR4*, U32) {}
void RADEXPLINK BinkService(HBINK) {}

S32 RADEXPLINK BinkShouldSkip(HBINK) { return 0; }

void RADEXPLINK BinkGetPalette(void*) {}

S32 RADEXPLINK BinkControlBackgroundIO(HBINK, U32) { return 0; }

#if defined(__RADWIN__) || defined(__RADXENON__) || defined(__RADPS3__)

S32 RADEXPLINK BinkStartAsyncThread(S32, void const*) { return 0; }
S32 RADEXPLINK BinkDoFrameAsync(HBINK, U32, U32) { return 0; }
S32 RADEXPLINK BinkDoFrameAsyncWait(HBINK, S32) { return 0; }
S32 RADEXPLINK BinkRequestStopAsyncThread(S32) { return 0; }
S32 RADEXPLINK BinkWaitStopAsyncThread(S32) { return 0; }

#endif

HBINKTRACK RADEXPLINK BinkOpenTrack(HBINK, U32) { return 0; }
void RADEXPLINK BinkCloseTrack(HBINKTRACK) {}
U32 RADEXPLINK BinkGetTrackData(HBINKTRACK, void PTR4*) { return 0; }

U32 RADEXPLINK BinkGetTrackType(HBINK, U32) { return 0; }
U32 RADEXPLINK BinkGetTrackMaxSize(HBINK, U32) { return 0; }
U32 RADEXPLINK BinkGetTrackID(HBINK, U32) { return 0; }

void RADEXPLINK BinkGetSummary(HBINK, BINKSUMMARY PTR4*) {}
void RADEXPLINK BinkGetRealtime(HBINK, BINKREALTIME PTR4*, U32) {}

void RADEXPLINK BinkSetSoundTrack(U32, U32 PTR4*) {}
void RADEXPLINK BinkSetIO(BINKIOOPEN) {}
void RADEXPLINK BinkSetFrameRate(U32, U32) {}
void RADEXPLINK BinkSetSimulate(U32) {}
void RADEXPLINK BinkSetIOSize(U32) {}

S32 RADEXPLINK BinkSetSoundSystem(BINKSNDSYSOPEN, UINTa) { return 0; }
S32 RADEXPLINK BinkControlPlatformFeatures(S32, S32) { return 0; }

#ifdef __RADWIN__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenDirectSound(UINTa) { return 0; }

// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenWaveOut(UINTa) { return 0; }
#endif

#ifndef __RADMAC__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenMiles(UINTa) { return 0; }
#endif

#ifdef __RADMAC__
// don't call directly
BINKSNDOPEN RADEXPLINK BinkOpenSoundManager(UINTa param) { return 0; }
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
RADEXPFUNC BINKSNDOPEN RADEXPLINK BinkOpenPSPSound(U32 param) { return 0; }
#endif

#ifdef __RADNDS__
// don't call directly
RADEXPFUNC BINKSNDOPEN RADEXPLINK BinkOpenNDSSound(U32 param) { return 0; }
#endif

#if defined(__RADXBOX__) || defined(__RADWIN__)
RADEXPFUNC S32 RADEXPLINK BinkDX8SurfaceType(void*) { return 0; }
#endif

#if defined(__RADXENON__) || defined(__RADWIN__)
RADEXPFUNC S32 RADEXPLINK BinkDX9SurfaceType(void*) { return 0; }
#endif

// The BinkBuffer API isn't implemented on DOS, or any of the consoles
#if !defined(__RADDOS__) && !defined(__RADXBOX__) && !defined(__RADNGC__) && \
    !defined(__RADNDS__)

#ifdef __RADMAC__

// #include <windows.h>
// #include <palettes.h>
// #include <qdoffscreen.h>

RADEXPFUNC HBINKBUFFER RADEXPLINK BinkBufferOpen(void* /*WindowPtr*/ wnd,
                                                 U32 width, U32 height,
                                                 U32 bufferflags) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkGDSurfaceType(void* /*GDHandle*/ gd) {
  return 0;
};
RADEXPFUNC S32 RADEXPLINK BinkIsSoftwareCursor(void* /*GDHandle*/ gd) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkCheckCursor(void* /*WindowPtr*/ wp, S32 x, S32 y,
                                          S32 w, S32 h) {
  return 0;
}

#else

RADEXPFUNC HBINKBUFFER RADEXPLINK BinkBufferOpen(void* /*HWND*/, U32, U32,
                                                 U32) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkBufferSetHWND(HBINKBUFFER, void* /*HWND*/) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkDDSurfaceType(void PTR4*) { return 0; }
RADEXPFUNC S32 RADEXPLINK BinkIsSoftwareCursor(void PTR4*, void* /*HCURSOR*/) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkCheckCursor(void* /*HWND*/, S32, S32, S32, S32) {
  return 0;
}
RADEXPFUNC S32 RADEXPLINK BinkBufferSetDirectDraw(void PTR4*, void PTR4*) {
  return 0;
}

#endif

RADEXPFUNC void RADEXPLINK BinkBufferClose(HBINKBUFFER) {}
RADEXPFUNC S32 RADEXPLINK BinkBufferLock(HBINKBUFFER) { return 0; }
RADEXPFUNC S32 RADEXPLINK BinkBufferUnlock(HBINKBUFFER) { return 0; };
RADEXPFUNC void RADEXPLINK BinkBufferSetResolution(S32, S32, S32) {}
RADEXPFUNC void RADEXPLINK BinkBufferCheckWinPos(HBINKBUFFER, S32 PTR4*,
                                                 S32 PTR4*) {}
RADEXPFUNC S32 RADEXPLINK BinkBufferSetOffset(HBINKBUFFER, S32, S32) {
  return 0;
}
RADEXPFUNC void RADEXPLINK BinkBufferBlit(HBINKBUFFER, BINKRECT PTR4*, U32) {}
RADEXPFUNC S32 RADEXPLINK BinkBufferSetScale(HBINKBUFFER, U32, U32) {
  return 0;
}
RADEXPFUNC char PTR4* RADEXPLINK BinkBufferGetDescription(HBINKBUFFER) {
  return 0;
}
RADEXPFUNC char PTR4* RADEXPLINK BinkBufferGetError() { return 0; }
RADEXPFUNC void RADEXPLINK BinkRestoreCursor(S32) {}
RADEXPFUNC S32 RADEXPLINK BinkBufferClear(HBINKBUFFER, U32) { return 0; }

#endif

RADEXPFUNC void RADEXPLINK BinkSetMemory(BINKMEMALLOC, BINKMEMFREE) {}

RADDEFEND