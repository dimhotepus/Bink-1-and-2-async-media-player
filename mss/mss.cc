﻿// mss.cc : Defines the exported functions for the DLL application.
//

#include "../deps/miles/include/mss.h"

#ifdef __cplusplus
extern "C" {
#endif

DXDEC HPROVIDER AILCALL RIB_alloc_provider_handle(long) { return 0; }
DXDEC void AILCALL RIB_free_provider_handle(HPROVIDER) {}

DXDEC HPROVIDER AILCALL RIB_load_provider_library(C8 const *) { return 0; }
DXDEC void AILCALL RIB_free_provider_library(HPROVIDER) {}

DXDEC RIBRESULT AILCALL RIB_register_interface(HPROVIDER, C8 const *, S32,
                                               RIB_INTERFACE_ENTRY const *) {
  return 0;
}

DXDEC RIBRESULT AILCALL RIB_unregister_interface(HPROVIDER, C8 const *, S32,
                                                 RIB_INTERFACE_ENTRY const *) {
  return 0;
}

DXDEC RIBRESULT AILCALL RIB_request_interface(HPROVIDER, C8 const *, S32,
                                              RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC RIBRESULT AILCALL RIB_request_interface_entry(HPROVIDER, C8 const *,
                                                    RIB_ENTRY_TYPE, C8 const *,
                                                    UINTa *) {
  return 0;
}

DXDEC S32 AILCALL RIB_enumerate_interface(HPROVIDER, C8 *, RIB_ENTRY_TYPE,
                                          HMSSENUM *, RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL RIB_enumerate_providers(C8 *, HMSSENUM *, HPROVIDER *) {
  return 0;
}

DXDEC C8 *AILCALL RIB_type_string(void const *, RIB_DATA_SUBTYPE) { return 0; }

DXDEC HPROVIDER AILCALL RIB_find_file_provider(C8 const *, C8 const *,
                                               C8 const *) {
  return 0;
}

DXDEC HPROVIDER AILCALL RIB_find_provider(C8 const *, C8 const *,
                                          void const *) {
  return 0;
}

//
// Static library definitions
//

#ifdef IS_STATIC
#define RIB_MAIN_NAME(name) name##_RIB_Main

DXDEC S32 AILCALL RIB_MAIN_NAME(SRS)(HPROVIDER provider_handle, U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(DTS)(HPROVIDER provider_handle, U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(DolbySurround)(HPROVIDER provider_handle,
                                               U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(MP3Dec)(HPROVIDER provider_handle,
                                        U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(OggDec)(HPROVIDER provider_handle,
                                        U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(SpxDec)(HPROVIDER provider_handle,
                                        U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(SpxEnc)(HPROVIDER provider_handle,
                                        U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(Voice)(HPROVIDER provider_handle, U32 up_down) {
}
DXDEC S32 AILCALL RIB_MAIN_NAME(SpxVoice)(HPROVIDER provider_handle,
                                          U32 up_down) {}
DXDEC S32 AILCALL RIB_MAIN_NAME(DSP)(HPROVIDER provider_handle, U32 up_down) {}

#else
DXDEC S32 AILCALL RIB_Main(HPROVIDER, U32) { return 0; }
#endif

DXDEC HPROVIDER AILCALL RIB_load_static_provider_library(RIB_MAIN_FUNC,
                                                         char *) {
  return 0;
}

DXDEC HPROVIDER AILCALL RIB_find_files_provider(C8 const *, C8 const *,
                                                C8 const *, C8 const *,
                                                C8 const *) {
  return 0;
}

DXDEC HPROVIDER AILCALL RIB_find_file_dec_provider(C8 const *, C8 const *, U32,
                                                   C8 const *, C8 const *) {
  return 0;
}

DXDEC S32 AILCALL RIB_load_application_providers(C8 const *) { return 0; }

DXDEC void AILCALL RIB_set_provider_user_data(HPROVIDER, U32, SINTa) {}

DXDEC SINTa AILCALL RIB_provider_user_data(HPROVIDER, U32) { return 0; }

DXDEC void AILCALL RIB_set_provider_system_data(HPROVIDER, U32, SINTa) {}

DXDEC SINTa AILCALL RIB_provider_system_data(HPROVIDER, U32) { return 0; }

DXDEC C8 *AILCALL RIB_error(void) { return 0; }

#if defined(IS_WINDOWS) || defined(IS_MAC) || defined(IS_LINUX) || \
    defined(IS_XBOX) || defined(IS_XENON) || defined(IS_PS3) ||    \
    defined(IS_PS2) || defined(IS_WII)

DXDEC U32 AILCALL AIL_get_timer_highest_delay(void) { return 0; }

DXDEC void AILCALL AIL_serve(void) {}

#endif

#ifdef IS_WIN32API

#ifdef NTAPI
HANDLE hAppThread;
#endif

#endif

//
// Background flag for timers
//

volatile S32 AIL_bkgnd_flag;

//
// Global preference array
//

SINTa AIL_preference[N_PREFS];

//
// DIG_DRIVER list
//

HDIGDRIVER DIG_first;

//
// MDI_DRIVER list
//

HMDIDRIVER MDI_first;

S32 AILCALLBACK SP_ASI_DECODER_callback(UINTa, void *, S32, S32) { return 0; }

DXDEC void *AILCALL AIL_mem_alloc_lock(UINTa) { return 0; }
DXDEC void AILCALL AIL_mem_free_lock(void *) {}

DXDEC S32 AILCALL AIL_file_error(void) { return 0; }

DXDEC S32 AILCALL AIL_file_size(char const *) { return 0; }

DXDEC void *AILCALL AIL_file_read(char const *, void *) { return 0; }

DXDEC S32 AILCALL AIL_file_write(char const *, void const *, U32) { return 0; }

DXDEC S32 AILCALL AIL_WAV_file_write(char const *, void const *, U32, S32,
                                     S32) {
  return 0;
}

DXDEC S32 AILCALL AIL_file_append(char const *, void const *, U32) { return 0; }

#ifndef IS_DOS

DXDEC AILMEMALLOCCB AILCALL AIL_mem_use_malloc(AILMEMALLOCCB) { return 0; }
DXDEC AILMEMFREECB AILCALL AIL_mem_use_free(AILMEMFREECB) { return 0; }

#endif

#ifdef ON_MAC_USE_FSS

DXDEC S32 AILCALL AIL_file_fss_size(FSSpec const *filename) {}

DXDEC void *AILCALL AIL_file_fss_read(FSSpec const *filename, void *dest) {}

DXDEC S32 AILCALL AIL_file_fss_write(FSSpec const *filename, void const *buf,
                                     U32 len) {}

DXDEC S32 AILCALL AIL_file_fss_attrib_write(FSSpec const *filename,
                                            void const *buf, U32 len, U32 type,
                                            U32 creator) {}

DXDEC S32 AILCALL AIL_WAV_file_fss_write(FSSpec const *filename,
                                         void const *buf, U32 len, S32 rate,
                                         S32 format) {}

#endif

//
// Compiler-independent CRTL helper functions for PS2
// Exported here for use in demo programs as well as MSS itself
//

DXDEC C8 *AILCALL AIL_ftoa(F32) { return 0; }

//
// High-level support services
//

#ifndef IS_DOS

DXDEC S32 AILCALL AIL_startup(void) { return 0; }

DXDEC SINTa AILCALL AIL_get_preference(U32) { return 0; }

#endif

DXDEC void AILCALL AIL_shutdown(void) {}

DXDEC SINTa AILCALL AIL_set_preference(U32, SINTa) { return 0; }

DXDEC char *AILCALL AIL_last_error(void) { return 0; }

DXDEC void AILCALL AIL_set_error(char const *) {}

//
// Low-level support services
//

DXDEC void
#if !defined(IS_MAC) && !defined(IS_LINUX) && !defined(IS_PS2) && \
    !defined(IS_PS3) && !defined(IS_WII)
    __cdecl
#endif
    AIL_debug_printf(C8 const *, ...) {
}

#ifdef IS_X86

DXDEC U32 AILCALL AIL_MMX_available(void) { return 0; }

#endif

DXDEC void AILCALL AIL_lock(void) {}
DXDEC void AILCALL AIL_unlock(void) {}

#if defined(IS_WIN32API) || defined(IS_MAC) || defined(IS_LINUX)

DXDEC void AILCALL AIL_lock_mutex(void) {}
DXDEC void AILCALL AIL_unlock_mutex(void) {}

#endif

DXDEC void AILCALL AIL_delay(S32) {}

DXDEC S32 AILCALL AIL_background(void) { return 0; }

#ifndef IS_DOS

DXDEC AILTRACECB AILCALL AIL_register_trace_callback(AILTRACECB, S32) {
  return 0;
}

#endif

//
// Process services
//

DXDEC HTIMER AILCALL AIL_register_timer(AILTIMERCB) { return 0; }

DXDEC UINTa AILCALL AIL_set_timer_user(HTIMER, UINTa) { return 0; }

DXDEC void AILCALL AIL_set_timer_period(HTIMER, U32) {}

DXDEC void AILCALL AIL_set_timer_frequency(HTIMER, U32) {}

DXDEC void AILCALL AIL_set_timer_divisor(HTIMER, U32) {}

DXDEC void AILCALL AIL_start_timer(HTIMER) {}
DXDEC void AILCALL AIL_start_all_timers(void) {}

DXDEC void AILCALL AIL_stop_timer(HTIMER) {}
DXDEC void AILCALL AIL_stop_all_timers(void) {}

DXDEC void AILCALL AIL_release_timer_handle(HTIMER) {}
DXDEC void AILCALL AIL_release_all_timers(void) {}

#ifdef IS_WIN32

/*
#ifndef __RADINDLL__

// static function that handles shutdown
int __cdecl MSS_auto_cleanup(void) {}

#ifdef _MSC_VER
// on MSVC, automatically register a cleanup function
#define AIL_startup() (MSS_auto_cleanup(),AIL_startup())
#endif

#endif
*/

DXDEC HWND AILCALL AIL_HWND(void) { return 0; }

#else
#ifdef IS_MAC
#if defined(__PROCESSES__)
DXDEC ProcessSerialNumber AIL_Process(void) {}
#endif
#endif
#endif

//
// high-level digital services
//

DXDEC HDIGDRIVER AILCALL AIL_open_digital_driver(U32, S32, S32, U32) {
  return 0;
}

DXDEC void AILCALL AIL_close_digital_driver(HDIGDRIVER) {}

#ifdef IS_LINUX

DXDEC S32 AILCALL AIL_digital_handle_release(HDIGDRIVER drvr) { return 0; }

DXDEC S32 AILCALL AIL_digital_handle_reacquire(HDIGDRIVER drvr) { return 0; }
#else

#ifdef IS_WINDOWS

DXDEC S32 AILCALL AIL_digital_handle_release(HDIGDRIVER) { return 0; }

DXDEC S32 AILCALL AIL_digital_handle_reacquire(HDIGDRIVER) { return 0; }

#else

#ifdef IS_MAC

#if defined(__RESOURCES__)

typedef MSS_STRUCT MSS_VersionType_ { Str255 version_name; }
MSS_VersionType;

#define AIL_MSS_version(str, len)                                      \
  {                                                                    \
    long _res = HOpenResFile(0, 0, "\p" MSSDLLNAME, fsRdPerm) {}       \
    if (_res == -1) {                                                  \
      str[0] = 0;                                                      \
    } else {                                                           \
      Handle _H;                                                       \
      short _Err;                                                      \
      long _cur = CurResFile() {}                                      \
      UseResFile(_res) {}                                              \
      _H = GetResource('vers', 2) {}                                   \
      _Err = ResError() {}                                             \
      if ((_Err != noErr) || (_H == 0)) {                              \
        str[0] = 0;                                                    \
        UseResFile(_cur) {}                                            \
        CloseResFile(_res) {}                                          \
      } else {                                                         \
        if (GetHandleSize(_H) == 0) {                                  \
          str[0] = 0;                                                  \
          UseResFile(_cur) {}                                          \
          CloseResFile(_res) {}                                        \
        } else {                                                       \
          MSS_VersionType *_vt = (MSS_VersionType *)*_H;               \
          if ((U32)_vt->version_name[6] > 4)                           \
            _vt->version_name[6] -= 4;                                 \
          else                                                         \
            _vt->version_name[6] = 0;                                  \
          if (((U32)len) <= ((U32)_vt->version_name[6]))               \
            _vt->version_name[6] = (U8)len - 1;                        \
          memcpy(str, _vt->version_name + 11, _vt->version_name[6]) {} \
          str[_vt->version_name[6]] = 0;                               \
          UseResFile(_cur) {}                                          \
          CloseResFile(_res) {}                                        \
        }                                                              \
        ReleaseResource(_H) {}                                         \
      }                                                                \
    }                                                                  \
  }

#endif

DXDEC S32 AILCALL AIL_digital_handle_release(HDIGDRIVER drvr) { return 0; }

DXDEC S32 AILCALL AIL_digital_handle_reacquire(HDIGDRIVER drvr) { return 0; }

#else

#ifdef IS_DOS

//
// DOS installation services
//

DXDEC IO_PARMS *AILCALL AIL_get_IO_environment(AIL_DRIVER *drvr) { return 0; }

DXDEC AIL_DRIVER *AILCALL AIL_install_driver(U8 const *driver_image,
                                             U32 n_bytes) {
  return 0;
}

DXDEC void AILCALL AIL_uninstall_driver(AIL_DRIVER *drvr) {}

DXDEC S32 AILCALL AIL_install_DIG_INI(HDIGDRIVER *dig) { return 0; }

DXDEC HDIGDRIVER AILCALL AIL_install_DIG_driver_file(char const *filename,
                                                     IO_PARMS *IO) {
  return 0;
}

DXDEC void AILCALL AIL_uninstall_DIG_driver(HDIGDRIVER dig) {}

DXDEC HDIGDRIVER AILCALL AIL_install_DIG_driver_image(void const *driver_image,
                                                      U32 size, IO_PARMS *IO) {
  return 0;
}
#endif
#endif
#endif
#endif

DXDEC char *AILCALL AIL_set_redist_directory(char const *) { return 0; }

DXDEC S32 AILCALL AIL_background_CPU_percent(void) { return 0; }

DXDEC S32 AILCALL AIL_digital_CPU_percent(HDIGDRIVER) { return 0; }

DXDEC S32 AILCALL AIL_digital_latency(HDIGDRIVER) { return 0; }

DXDEC HSAMPLE AILCALL AIL_allocate_sample_handle(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_speaker_configuration(HDIGDRIVER, MSSVECTOR3D *, S32,
                                                 F32) {}

DXDEC MSSVECTOR3D *AILCALL AIL_speaker_configuration(HDIGDRIVER, S32 *, S32 *,
                                                     F32 *, MSS_MC_SPEC *) {
  return 0;
}

DXDEC void AILCALL AIL_set_listener_relative_receiver_array(HDIGDRIVER,
                                                            MSS_RECEIVER_LIST *,
                                                            S32) {}

DXDEC MSS_RECEIVER_LIST *AILCALL
AIL_listener_relative_receiver_array(HDIGDRIVER, S32 *) {
  return 0;
}
#ifndef IS_XBOX

DXDEC void AILCALL AIL_set_speaker_reverb_levels(HDIGDRIVER, F32 *, F32 *,
                                                 MSS_SPEAKER const *, S32) {}

DXDEC S32 AILCALL AIL_speaker_reverb_levels(HDIGDRIVER, F32 **, F32 **,
                                            MSS_SPEAKER const **) {
  return 0;
}

#endif

DXDEC
S32 AILEXPORT AIL_calculate_3D_channel_levels(HDIGDRIVER,  //)
                                              F32 *, MSS_SPEAKER const **,
                                              MSSVECTOR3D *, MSSVECTOR3D *,
                                              MSSVECTOR3D *, F32, F32, F32, F32,
                                              F32, MSSVECTOR3D *, MSSVECTOR3D *,
                                              MSSVECTOR3D *, F32, MSSVECTOR3D *,
                                              F32 *) {
  return 0;
}

DXDEC void AILCALL AIL_release_sample_handle(HSAMPLE) {}

DXDEC S32 AILCALL AIL_init_sample(HSAMPLE, S32) { return 0; }

DXDEC S32 AILCALL AIL_set_sample_file(HSAMPLE, void const *, S32) { return 0; }

DXDEC S32 AILCALL AIL_set_sample_info(HSAMPLE, AILSOUNDINFO const *) {
  return 0;
}

DXDEC S32 AILCALL AIL_set_named_sample_file(HSAMPLE, C8 const *, void const *,
                                            U32, S32) {
  return 0;
}

DXDEC HPROVIDER AILCALL AIL_set_sample_processor(HSAMPLE, SAMPLESTAGE,
                                                 HPROVIDER) {
  return 0;
}

DXDEC HPROVIDER AILCALL AIL_set_digital_driver_processor(HDIGDRIVER,
                                                         DIGDRVSTAGE,
                                                         HPROVIDER) {
  return 0;
}

DXDEC HPROVIDER AILCALL AIL_sample_processor(HSAMPLE, SAMPLESTAGE) { return 0; }

DXDEC HPROVIDER AILCALL AIL_digital_driver_processor(HDIGDRIVER, DIGDRVSTAGE) {
  return 0;
}

DXDEC void AILCALL AIL_set_sample_adpcm_block_size(HSAMPLE, U32) {}

DXDEC void AILCALL AIL_set_sample_address(HSAMPLE, void const *, U32) {}

DXDEC void AILCALL AIL_start_sample(HSAMPLE) {}

DXDEC void AILCALL AIL_stop_sample(HSAMPLE) {}

DXDEC void AILCALL AIL_resume_sample(HSAMPLE) {}

DXDEC void AILCALL AIL_end_sample(HSAMPLE) {}

DXDEC void AILCALL AIL_set_sample_playback_rate(HSAMPLE, S32) {}

DXDEC void AILCALL AIL_set_sample_volume_pan(HSAMPLE, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_volume_levels(HSAMPLE, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_channel_levels(HSAMPLE, MSS_SPEAKER const *,
                                                 MSS_SPEAKER const *,
                                                 F32 const *, S32) {}

DXDEC void AILCALL AIL_set_sample_reverb_levels(HSAMPLE, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_low_pass_cut_off(HSAMPLE,
                                                   S32 /*-1 or MSS_SPEAKER*/,
                                                   F32) {}

DXDEC void AILCALL AIL_set_sample_loop_count(HSAMPLE, S32) {}

DXDEC void AILCALL AIL_set_sample_loop_block(HSAMPLE, S32, S32) {}

DXDEC S32 AILCALL AIL_sample_loop_block(HSAMPLE, S32 *, S32 *) { return 0; }

DXDEC U32 AILCALL AIL_sample_status(HSAMPLE) { return 0; }

DXDEC S32 AILCALL AIL_sample_playback_rate(HSAMPLE) { return 0; }

DXDEC void AILCALL AIL_sample_volume_pan(HSAMPLE, F32 *, F32 *) {}

DXDEC void AILCALL AIL_sample_channel_levels(HSAMPLE, MSS_SPEAKER const *,
                                             MSS_SPEAKER const *, F32 *, S32) {}

DXDEC void AILCALL AIL_sample_volume_levels(HSAMPLE, F32 *, F32 *) {}

DXDEC void AILCALL AIL_sample_reverb_levels(HSAMPLE, F32 *, F32 *) {}

DXDEC F32 AILCALL AIL_sample_low_pass_cut_off(HSAMPLE,
                                              S32 /*-1 or MSS_SPEAKER*/) {
  return 0;
}

DXDEC S32 AILCALL AIL_sample_loop_count(HSAMPLE) { return 0; }

DXDEC void AILCALL AIL_set_digital_master_volume_level(HDIGDRIVER, F32) {}

DXDEC F32 AILCALL AIL_digital_master_volume_level(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_sample_51_volume_pan(HSAMPLE, F32, F32, F32, F32,
                                                F32) {}

DXDEC void AILCALL AIL_sample_51_volume_pan(HSAMPLE, F32 *, F32 *, F32 *, F32 *,
                                            F32 *) {}

DXDEC void AILCALL AIL_set_sample_51_volume_levels(HSAMPLE, F32, F32, F32, F32,
                                                   F32, F32) {}

DXDEC void AILCALL AIL_sample_51_volume_levels(HSAMPLE, F32 *, F32 *, F32 *,
                                               F32 *, F32 *, F32 *) {}
#if !defined(IS_XBOX)

DXDEC void AILCALL AIL_set_digital_master_reverb(HDIGDRIVER, F32, F32, F32) {}

DXDEC void AILCALL AIL_digital_master_reverb(HDIGDRIVER, F32 *, F32 *, F32 *) {}

#endif

DXDEC void AILCALL AIL_set_digital_master_reverb_levels(HDIGDRIVER, F32, F32) {}

DXDEC void AILCALL AIL_digital_master_reverb_levels(HDIGDRIVER, F32 *, F32 *) {}

//
// low-level digital services
//

DXDEC S32 AILCALL AIL_minimum_sample_buffer_size(HDIGDRIVER, S32, S32) {
  return 0;
}

DXDEC S32 AILCALL AIL_sample_buffer_ready(HSAMPLE) { return 0; }

DXDEC S32 AILCALL AIL_load_sample_buffer(HSAMPLE, S32, void const *, U32) {
  return 0;
}

DXDEC void AILCALL AIL_request_EOB_ASI_reset(HSAMPLE, U32, S32) {}

DXDEC S32 AILCALL AIL_sample_buffer_info(HSAMPLE,  //)
                                         S32, U32 *, U32 *, S32 *, S32 *) {
  return 0;
}

DXDEC U32 AILCALL AIL_sample_granularity(HSAMPLE) { return 0; }

DXDEC void AILCALL AIL_set_sample_position(HSAMPLE, U32) {}

DXDEC U32 AILCALL AIL_sample_position(HSAMPLE) { return 0; }

DXDEC AILSAMPLECB AILCALL AIL_register_SOB_callback(HSAMPLE, AILSAMPLECB) {
  return 0;
}

DXDEC AILSAMPLECB AILCALL AIL_register_EOB_callback(HSAMPLE, AILSAMPLECB) {
  return 0;
}

DXDEC AILSAMPLECB AILCALL AIL_register_EOS_callback(HSAMPLE, AILSAMPLECB) {
  return 0;
}

DXDEC AILFALLOFFCB AILCALL
AIL_register_falloff_function_callback(HSAMPLE, AILFALLOFFCB) {
  return 0;
}

DXDEC void AILCALL AIL_set_sample_user_data(HSAMPLE, U32, SINTa) {}

DXDEC SINTa AILCALL AIL_sample_user_data(HSAMPLE, U32) { return 0; }

DXDEC S32 AILCALL AIL_active_sample_count(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_digital_configuration(HDIGDRIVER, S32 *, S32 *, char *) {
}

DXDEC S32 AILCALL AIL_platform_property(void *, MSS_PLATFORM_PROPERTY, void *,
                                        void const *, void *) {
  return 0;
}

#ifdef IS_WIN32API

DXDEC S32 AILCALL AIL_set_direct_buffer_control(HSAMPLE, U32) { return 0; }

DXDEC void AILCALL AIL_get_DirectSound_info(HSAMPLE, AILLPDIRECTSOUND *,
                                            AILLPDIRECTSOUNDBUFFER *) {}

#ifdef IS_WIN32
DXDEC S32 AILCALL AIL_set_DirectSound_HWND(HDIGDRIVER, HWND) { return 0; }
#endif

#endif

DXDEC void AILCALL AIL_set_sample_ms_position(HSAMPLE,  //)
                                              S32) {}

DXDEC void AILCALL AIL_sample_ms_position(HSAMPLE,  //)
                                          S32 *, S32 *) {}

//
// Digital input services
//

#if defined(IS_WINDOWS) || defined(IS_MAC) || defined(IS_LINUX) || \
    defined(IS_XBOX) || defined(IS_XENON)

DXDEC HDIGINPUT AILCALL AIL_open_input(AIL_INPUT_INFO *) { return 0; }

DXDEC void AILCALL AIL_close_input(HDIGINPUT) {}

DXDEC AIL_INPUT_INFO *AILCALL AIL_get_input_info(HDIGINPUT) { return 0; }

DXDEC S32 AILCALL AIL_set_input_state(HDIGINPUT, S32) { return 0; }
#endif

//
// High-level XMIDI services
//

DXDEC HMDIDRIVER AILCALL AIL_open_XMIDI_driver(U32) { return 0; }

DXDEC void AILCALL AIL_close_XMIDI_driver(HMDIDRIVER) {}

#if defined(IS_MAC) || defined(IS_LINUX)

DXDEC S32 AILCALL AIL_MIDI_handle_release(HMDIDRIVER mdi) {}

DXDEC S32 AILCALL AIL_MIDI_handle_reacquire(HMDIDRIVER mdi) {}

#else

#ifdef IS_WINDOWS

DXDEC S32 AILCALL AIL_midiOutOpen(HMDIDRIVER *, LPHMIDIOUT *, S32) { return 0; }

DXDEC void AILCALL AIL_midiOutClose(HMDIDRIVER) {}

DXDEC S32 AILCALL AIL_MIDI_handle_release(HMDIDRIVER) { return 0; }

DXDEC S32 AILCALL AIL_MIDI_handle_reacquire(HMDIDRIVER) { return 0; }

#else

#ifdef IS_DOS

DXDEC S32 AILCALL AIL_install_MDI_INI(HMDIDRIVER *mdi) {}

DXDEC HMDIDRIVER AILCALL AIL_install_MDI_driver_file(char const *filename,
                                                     IO_PARMS *IO) {}

DXDEC void AILCALL AIL_uninstall_MDI_driver(HMDIDRIVER mdi) {}

DXDEC HMDIDRIVER AILCALL AIL_install_MDI_driver_image(void const *driver_image,
                                                      U32 size, IO_PARMS *IO) {}

DXDEC S32 AILCALL AIL_MDI_driver_type(HMDIDRIVER mdi) {}

DXDEC void AILCALL AIL_set_GTL_filename_prefix(char const *prefix) {}

DXDEC S32 AILCALL AIL_timbre_status(HMDIDRIVER mdi, S32 bank, S32 patch) {}

DXDEC S32 AILCALL AIL_install_timbre(HMDIDRIVER mdi, S32 bank, S32 patch) {}

DXDEC void AILCALL AIL_protect_timbre(HMDIDRIVER mdi, S32 bank, S32 patch) {}

DXDEC void AILCALL AIL_unprotect_timbre(HMDIDRIVER mdi, S32 bank, S32 patch) {}

#endif

#endif

#endif

DXDEC HSEQUENCE AILCALL AIL_allocate_sequence_handle(HMDIDRIVER) { return 0; }

DXDEC void AILCALL AIL_release_sequence_handle(HSEQUENCE) {}

DXDEC S32 AILCALL AIL_init_sequence(HSEQUENCE, void const *, S32) { return 0; }

DXDEC void AILCALL AIL_start_sequence(HSEQUENCE) {}

DXDEC void AILCALL AIL_stop_sequence(HSEQUENCE) {}

DXDEC void AILCALL AIL_resume_sequence(HSEQUENCE) {}

DXDEC void AILCALL AIL_end_sequence(HSEQUENCE) {}

DXDEC void AILCALL AIL_set_sequence_tempo(HSEQUENCE, S32, S32) {}

DXDEC void AILCALL AIL_set_sequence_volume(HSEQUENCE, S32, S32) {}

DXDEC void AILCALL AIL_set_sequence_loop_count(HSEQUENCE, S32) {}

DXDEC U32 AILCALL AIL_sequence_status(HSEQUENCE) { return 0; }

DXDEC S32 AILCALL AIL_sequence_tempo(HSEQUENCE) { return 0; }

DXDEC S32 AILCALL AIL_sequence_volume(HSEQUENCE) { return 0; }

DXDEC S32 AILCALL AIL_sequence_loop_count(HSEQUENCE) { return 0; }

DXDEC void AILCALL AIL_set_XMIDI_master_volume(HMDIDRIVER, S32) {}

DXDEC S32 AILCALL AIL_XMIDI_master_volume(HMDIDRIVER) { return 0; }

//
// Low-level XMIDI services
//

DXDEC S32 AILCALL AIL_active_sequence_count(HMDIDRIVER) { return 0; }

DXDEC S32 AILCALL AIL_controller_value(HSEQUENCE, S32, S32) { return 0; }

DXDEC S32 AILCALL AIL_channel_notes(HSEQUENCE, S32) { return 0; }

DXDEC void AILCALL AIL_sequence_position(HSEQUENCE, S32 *, S32 *) {}

DXDEC void AILCALL AIL_branch_index(HSEQUENCE, U32) {}

DXDEC AILPREFIXCB AILCALL AIL_register_prefix_callback(HSEQUENCE, AILPREFIXCB) {
  return 0;
}

DXDEC AILTRIGGERCB AILCALL AIL_register_trigger_callback(HSEQUENCE,
                                                         AILTRIGGERCB) {
  return 0;
}

DXDEC AILSEQUENCECB AILCALL AIL_register_sequence_callback(HSEQUENCE,
                                                           AILSEQUENCECB) {
  return 0;
}

DXDEC AILBEATCB AILCALL AIL_register_beat_callback(HSEQUENCE, AILBEATCB) {
  return 0;
}

DXDEC AILEVENTCB AILCALL AIL_register_event_callback(HMDIDRIVER, AILEVENTCB) {
  return 0;
}

DXDEC AILTIMBRECB AILCALL AIL_register_timbre_callback(HMDIDRIVER,
                                                       AILTIMBRECB) {
  return 0;
}

DXDEC void AILCALL AIL_set_sequence_user_data(HSEQUENCE, U32, SINTa) {}

DXDEC SINTa AILCALL AIL_sequence_user_data(HSEQUENCE, U32) { return 0; }

DXDEC void AILCALL AIL_register_ICA_array(HSEQUENCE, U8 *) {}

DXDEC S32 AILCALL AIL_lock_channel(HMDIDRIVER) { return 0; }

DXDEC void AILCALL AIL_release_channel(HMDIDRIVER, S32) {}

DXDEC void AILCALL AIL_map_sequence_channel(HSEQUENCE, S32, S32) {}

DXDEC S32 AILCALL AIL_true_sequence_channel(HSEQUENCE, S32) { return 0; }

DXDEC void AILCALL AIL_send_channel_voice_message(HMDIDRIVER, HSEQUENCE, S32,
                                                  S32, S32) {}

DXDEC void AILCALL AIL_send_sysex_message(HMDIDRIVER, void const *) {}

DXDEC HWAVESYNTH AILCALL AIL_create_wave_synthesizer(HDIGDRIVER, HMDIDRIVER,
                                                     void const *, S32) {
  return 0;
}

DXDEC void AILCALL AIL_destroy_wave_synthesizer(HWAVESYNTH) {}

DXDEC void AILCALL AIL_set_sequence_ms_position(HSEQUENCE,  //)
                                                S32) {}

DXDEC void AILCALL AIL_sequence_ms_position(HSEQUENCE,  //)
                                            S32 *, S32 *) {}

#if !defined(IS_XBOX) && !defined(IS_XENON) && !defined(IS_PS2) && \
    !defined(IS_PS3) && !defined(IS_WII)

DXDEC HREDBOOK AILCALL AIL_redbook_open(U32) { return 0; }

#ifdef IS_MAC
DXDEC HREDBOOK AILCALL AIL_redbook_open_volume(char const *drive) {}
#else
DXDEC HREDBOOK AILCALL AIL_redbook_open_drive(S32) { return 0; }
#endif

DXDEC void AILCALL AIL_redbook_close(HREDBOOK) {}

DXDEC void AILCALL AIL_redbook_eject(HREDBOOK) {}

DXDEC void AILCALL AIL_redbook_retract(HREDBOOK) {}

DXDEC U32 AILCALL AIL_redbook_status(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_tracks(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_track(HREDBOOK) { return 0; }

DXDEC void AILCALL AIL_redbook_track_info(HREDBOOK, U32, U32 *, U32 *) {}

DXDEC U32 AILCALL AIL_redbook_id(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_position(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_play(HREDBOOK, U32, U32) { return 0; }

DXDEC U32 AILCALL AIL_redbook_stop(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_pause(HREDBOOK) { return 0; }

DXDEC U32 AILCALL AIL_redbook_resume(HREDBOOK) { return 0; }

DXDEC F32 AILCALL AIL_redbook_volume_level(HREDBOOK) { return 0; }

DXDEC F32 AILCALL AIL_redbook_set_volume_level(HREDBOOK, F32) { return 0; }

#endif

#ifdef IS_WIN16
#define AIL_ms_count timeGetTime
DXDEC U32 AILCALL AIL_us_count(void) { return 0; }
#else
DXDEC U32 AILCALL AIL_ms_count(void) { return 0; }
DXDEC U32 AILCALL AIL_us_count(void) { return 0; }
#endif

DXDEC HSTREAM AILCALL AIL_open_stream(HDIGDRIVER, char const *, S32) {
  return 0;
}

DXDEC void AILCALL AIL_close_stream(HSTREAM) {}

DXDEC HSAMPLE AILCALL AIL_stream_sample_handle(HSTREAM) { return 0; }

DXDEC S32 AILCALL AIL_service_stream(HSTREAM, S32) { return 0; }

DXDEC void AILCALL AIL_start_stream(HSTREAM) {}

DXDEC void AILCALL AIL_pause_stream(HSTREAM, S32) {}

DXDEC S32 AILCALL AIL_stream_loop_count(HSTREAM) { return 0; }

DXDEC void AILCALL AIL_set_stream_loop_count(HSTREAM, S32) {}

DXDEC void AILCALL AIL_set_stream_loop_block(HSTREAM, S32, S32) {}

DXDEC S32 AILCALL AIL_stream_status(HSTREAM) { return 0; }

DXDEC void AILCALL AIL_set_stream_position(HSTREAM, S32) {}

DXDEC S32 AILCALL AIL_stream_position(HSTREAM) { return 0; }

DXDEC void AILCALL AIL_stream_info(HSTREAM, S32 *, S32 *, S32 *, S32 *) {}

DXDEC AILSTREAMCB AILCALL AIL_register_stream_callback(HSTREAM, AILSTREAMCB) {
  return 0;
}

DXDEC void AILCALL AIL_auto_service_stream(HSTREAM, S32) {}

DXDEC void AILCALL AIL_set_stream_user_data(HSTREAM, U32, SINTa) {}

DXDEC SINTa AILCALL AIL_stream_user_data(HSTREAM, U32) { return 0; }

DXDEC void AILCALL AIL_set_stream_ms_position(HSTREAM, S32) {}

DXDEC void AILCALL AIL_stream_ms_position(HSTREAM,  //)
                                          S32 *, S32 *) {}

DXDEC void AILCALL AIL_set_file_callbacks(AIL_file_open_callback,
                                          AIL_file_close_callback,
                                          AIL_file_seek_callback,
                                          AIL_file_read_callback) {}

#ifdef IS_32

DXDEC void AILCALL AIL_set_file_async_callbacks(
    AIL_file_open_callback, AIL_file_close_callback, AIL_file_seek_callback,
    AIL_file_async_read_callback, AIL_file_async_status_callback) {}

#endif

//
// High-level DLS functions
//

DXDEC HDLSDEVICE AILCALL AIL_DLS_open(HMDIDRIVER, HDIGDRIVER,
#ifdef IS_STATIC
                                      AILSTATICDLS const *staticdls,
#else
                                      char const *,
#endif
                                      U32, U32, S32, S32) {
  return 0;
}

//
// Parameters for the dwFlag used in DLSClose() and flags in AIL_DLS_close
//

DXDEC void AILCALL AIL_DLS_close(HDLSDEVICE, U32) {}

DXDEC HDLSFILEID AILCALL AIL_DLS_load_file(HDLSDEVICE, char const *, U32) {
  return 0;
}

DXDEC HDLSFILEID AILCALL AIL_DLS_load_memory(HDLSDEVICE, void const *, U32) {
  return 0;
}

//
// other parameters for AIL_DLS_unload
//

DXDEC void AILCALL AIL_DLS_unload(HDLSDEVICE, HDLSFILEID) {}

DXDEC void AILCALL AIL_DLS_compact(HDLSDEVICE) {}

DXDEC void AILCALL AIL_DLS_get_info(HDLSDEVICE, AILDLSINFO *, S32 *) {}

DXDEC HSAMPLE AILCALL AIL_DLS_sample_handle(HDLSDEVICE) { return 0; }

//
// Quick-integration service functions and data types
//

DXDEC S32 AILCALL
#if defined(IS_WINDOWS) || defined(IS_MAC) || defined(IS_LINUX) || \
    defined(IS_XBOX) || defined(IS_XENON) || defined(IS_PS2) ||    \
    defined(IS_PS3) || defined(IS_WII)
AIL_quick_startup(
#else
AIL_quick_startup_with_start(void *startup,
#endif
    S32, S32, U32, S32, S32) {
  return 0;
}

DXDEC void AILCALL AIL_quick_shutdown(void) {}

DXDEC void AILCALL AIL_quick_handles(HDIGDRIVER *, HMDIDRIVER *, HDLSDEVICE *) {
}

DXDEC HAUDIO AILCALL AIL_quick_load(char const *) { return 0; }

#ifdef ON_MAC_USE_FSS
DXDEC HAUDIO AILCALL AIL_quick_fss_load(FSSpec const *filename) {}
#endif

DXDEC HAUDIO AILCALL AIL_quick_load_mem(void const *, U32) { return 0; }

DXDEC HAUDIO AILCALL AIL_quick_load_named_mem(void const *, char const *, U32) {
  return 0;
}

DXDEC HAUDIO AILCALL AIL_quick_copy(HAUDIO) { return 0; }

DXDEC void AILCALL AIL_quick_unload(HAUDIO) {}

DXDEC S32 AILCALL AIL_quick_play(HAUDIO, U32) { return 0; }

DXDEC void AILCALL AIL_quick_halt(HAUDIO) {}

DXDEC S32 AILCALL AIL_quick_status(HAUDIO) { return 0; }

DXDEC HAUDIO AILCALL AIL_quick_load_and_play(char const *, U32, S32) {
  return 0;
}

#ifdef ON_MAC_USE_FSS
DXDEC HAUDIO AILCALL AIL_quick_fss_load_and_play(FSSpec const *filename,
                                                 U32 loop_count,
                                                 S32 wait_request) {
  return 0;
}
#endif

DXDEC void AILCALL AIL_quick_set_speed(HAUDIO, S32) {}

DXDEC void AILCALL AIL_quick_set_volume(HAUDIO, F32, F32) {}

DXDEC void AILCALL AIL_quick_set_reverb_levels(HAUDIO, F32, F32) {}

DXDEC void AILCALL AIL_quick_set_low_pass_cut_off(HAUDIO, S32, F32) {}

DXDEC void AILCALL AIL_quick_set_ms_position(HAUDIO, S32) {}

DXDEC S32 AILCALL AIL_quick_ms_position(HAUDIO) { return 0; }

DXDEC S32 AILCALL AIL_quick_ms_length(HAUDIO) { return 0; }

DXDEC S32 AILCALL AIL_quick_type(HAUDIO) { return 0; }

DXDEC S32 AILCALL AIL_WAV_info(void const *, AILSOUNDINFO *) { return 0; }

DXDEC S32 AILCALL AIL_size_processed_digital_audio(U32, U32, S32,
                                                   AILMIXINFO const *) {
  return 0;
}

DXDEC S32 AILCALL AIL_process_digital_audio(void *, S32, U32, U32, S32,
                                            AILMIXINFO *) {
  return 0;
}

DXDEC S32 AILCALL AIL_compress_ASI(AILSOUNDINFO const *,  //)
                                   char const *, void **, U32 *, AILLENGTHYCB) {
  return 0;
}

DXDEC S32 AILCALL AIL_decompress_ASI(void const *,  //)
                                     U32, char const *, void **, U32 *,
                                     AILLENGTHYCB) {
  return 0;
}

DXDEC S32 AILCALL AIL_compress_ADPCM(AILSOUNDINFO const *, void **, U32 *) {
  return 0;
}

DXDEC S32 AILCALL AIL_decompress_ADPCM(AILSOUNDINFO const *, void **, U32 *) {
  return 0;
}

DXDEC S32 AILCALL AIL_compress_DLS(void const *, char const *, void **, U32 *,
                                   AILLENGTHYCB) {
  return 0;
}

DXDEC S32 AILCALL AIL_merge_DLS_with_XMI(void const *, void const *, void **,
                                         U32 *) {
  return 0;
}

DXDEC S32 AILCALL AIL_extract_DLS(void const *,  //)
                                  U32, void **, U32 *, void **, U32 *,
                                  AILLENGTHYCB) {
  return 0;
}

DXDEC S32 AILCALL AIL_filter_DLS_with_XMI(void const *, void const *, void **,
                                          U32 *, S32, AILLENGTHYCB) {
  return 0;
}

DXDEC S32 AILCALL AIL_MIDI_to_XMI(void const *, U32, void **, U32 *, S32) {
  return 0;
}

#if defined(IS_WIN32) || defined(IS_MAC)

DXDEC S32 AILCALL AIL_list_DLS(void const *, char **, U32 *, S32, C8 *) {
  return 0;
}

DXDEC S32 AILCALL AIL_list_MIDI(void const *, U32, char **, U32 *, S32) {
  return 0;
}
#endif

DXDEC S32 AILCALL AIL_file_type(void const *, U32) { return 0; }

DXDEC S32 AILCALL AIL_file_type_named(void const *, char const *, U32) {
  return 0;
}

DXDEC S32 AILCALL AIL_find_DLS(void const *, U32, void **, U32 *, void **,
                               U32 *) {
  return 0;
}

DXDEC void AILCALL AIL_inspect_MP3(MP3_INFO *, U8 *, S32) {}

DXDEC S32 AILCALL AIL_enumerate_MP3_frames(MP3_INFO *) { return 0; }

#if defined(IS_WIN32API) || defined(IS_MAC) || defined(IS_LINUX) || \
    defined(IS_DOS) || defined(IS_PS2) || defined(IS_PS3) || defined(IS_WII)

//
// Auxiliary 2D interface calls
//

DXDEC HDIGDRIVER AILCALL AIL_primary_digital_driver(HDIGDRIVER) { return 0; }

//
// 3D-related calls
//

DXDEC S32 AILCALL AIL_room_type(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_room_type(HDIGDRIVER, S32) {}

DXDEC F32 AILCALL AIL_3D_rolloff_factor(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_3D_rolloff_factor(HDIGDRIVER, F32) {}

DXDEC F32 AILCALL AIL_3D_doppler_factor(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_3D_doppler_factor(HDIGDRIVER, F32) {}

DXDEC F32 AILCALL AIL_3D_distance_factor(HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_set_3D_distance_factor(HDIGDRIVER, F32) {}

DXDEC void AILCALL AIL_set_sample_obstruction(HSAMPLE, F32) {}

DXDEC void AILCALL AIL_set_sample_occlusion(HSAMPLE, F32) {}

DXDEC void AILCALL AIL_set_sample_exclusion(HSAMPLE, F32) {}

DXDEC F32 AILCALL AIL_sample_obstruction(HSAMPLE) { return 0; }

DXDEC F32 AILCALL AIL_sample_occlusion(HSAMPLE) { return 0; }

DXDEC F32 AILCALL AIL_sample_exclusion(HSAMPLE) { return 0; }

DXDEC void AILCALL AIL_set_sample_3D_distances(HSAMPLE, F32, F32, S32) {}

DXDEC void AILCALL AIL_sample_3D_distances(HSAMPLE, F32 *, F32 *, S32 *) {}

DXDEC void AILCALL AIL_set_sample_3D_cone(HSAMPLE, F32, F32, F32) {}

DXDEC void AILCALL AIL_sample_3D_cone(HSAMPLE, F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_set_sample_3D_position(HSAMPLE, F32, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_3D_velocity(HSAMPLE, F32, F32, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_3D_velocity_vector(HSAMPLE, F32, F32, F32) {}

DXDEC void AILCALL AIL_set_sample_3D_orientation(HSAMPLE, F32, F32, F32, F32,
                                                 F32, F32) {}

DXDEC S32 AILCALL AIL_sample_3D_position(HSAMPLE, F32 *, F32 *, F32 *) {
  return 0;
}

DXDEC void AILCALL AIL_sample_3D_velocity(HSAMPLE, F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_sample_3D_orientation(HSAMPLE, F32 *, F32 *, F32 *,
                                             F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_update_sample_3D_position(HSAMPLE, F32) {}

DXDEC void AILCALL AIL_set_listener_3D_position(HDIGDRIVER, F32, F32, F32) {}

DXDEC void AILCALL AIL_set_listener_3D_velocity(HDIGDRIVER, F32, F32, F32,
                                                F32) {}

DXDEC void AILCALL AIL_set_listener_3D_velocity_vector(HDIGDRIVER, F32, F32,
                                                       F32) {}

DXDEC void AILCALL AIL_set_listener_3D_orientation(HDIGDRIVER, F32, F32, F32,
                                                   F32, F32, F32) {}

DXDEC void AILCALL AIL_listener_3D_position(HDIGDRIVER, F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_listener_3D_velocity(HDIGDRIVER, F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_listener_3D_orientation(HDIGDRIVER, F32 *, F32 *, F32 *,
                                               F32 *, F32 *, F32 *) {}

DXDEC void AILCALL AIL_update_listener_3D_position(HDIGDRIVER, F32) {}

#endif

#ifdef MSS_FLT_SUPPORTED

//
// Pipeline filter calls
//

DXDEC HPROVIDER AILCALL AIL_digital_output_filter(HDIGDRIVER) { return 0; }

DXDEC S32 AILCALL AIL_enumerate_filters(HMSSENUM *, HPROVIDER *, C8 **) {
  return 0;
}
DXDEC HDRIVERSTATE AILCALL AIL_open_filter(HPROVIDER, HDIGDRIVER) { return 0; }

DXDEC void AILCALL AIL_close_filter(HDRIVERSTATE) {}

DXDEC S32 AILCALL AIL_find_filter(C8 const *, HPROVIDER *) { return 0; }

DXDEC S32 AILCALL AIL_enumerate_filter_properties(HPROVIDER, HMSSENUM *,
                                                  RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL AIL_filter_property(HPROVIDER, C8 const *, void *,
                                      void const *, void *) {
  return 0;
}

DXDEC S32 AILCALL AIL_enumerate_output_filter_driver_properties(
    HPROVIDER, HMSSENUM *, RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL AIL_output_filter_driver_property(HDIGDRIVER, C8 const *,
                                                    void *, void const *,
                                                    void *) {
  return 0;
}

DXDEC S32 AILCALL AIL_enumerate_output_filter_sample_properties(
    HPROVIDER, HMSSENUM *, RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL AIL_enumerate_filter_sample_properties(
    HPROVIDER, HMSSENUM *, RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL AIL_enumerate_sample_stage_properties(HSAMPLE, SAMPLESTAGE,
                                                        HMSSENUM *,
                                                        RIB_INTERFACE_ENTRY *) {
  return 0;
}

DXDEC S32 AILCALL AIL_sample_stage_property(HSAMPLE, SAMPLESTAGE, C8 const *,
                                            S32, void *, void const *, void *) {
  return 0;
}

#endif

#ifndef IS_PS2

#if defined(_PUSHPOP_SUPPORTED) || PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#else
#pragma pack()
#endif

#else

DXDEC MSS_RESOURCE_POLICY AILCALL
AIL_set_scratchpad_policy(MSS_RESOURCE_POLICY policy) {}
DXDEC MSS_RESOURCE_POLICY AILCALL AIL_scratchpad_policy(void) {}

#endif

#ifndef __RADINDLL__
#ifdef FSSpec
#undef FSSpec
#endif
#endif

#ifdef __cplusplus
}
#endif
