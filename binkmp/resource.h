// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

// Company long name.
#define WB_VER_COMPANY_NAME_STR "The WhiteBox Authors"

// Compane short name.
#define WB_VER_COMPANY_SHORT_NAME_INFO_STR "WhiteBox"

// Copyright.
#define WB_VER_LEGALCOPYRIGHT_STR \
  "Copyright " WB_VER_COMPANY_NAME_STR ". All rights reserved."

#ifndef WB_STRINGIFY_WORKER
// Stringify worker.
#define WB_STRINGIFY_WORKER(text) #text
#endif

#ifndef WB_STRINGIFY
// Stringify.
#define WB_STRINGIFY(text) WB_STRINGIFY_WORKER(text)
#endif

// clang-format off

// Product version header.
#define WB_VER_PRODUCT_VERSION_HEADER 0,1,0,0  // NOLINT Version

// Product version info.
#define WB_VER_PRODUCT_VERSION_INFO   0.1.0.0  // NOLINT Version

// clang-format on

// Product version info as string.
#define WB_VER_PRODUCT_VERSION_INFO_STR \
  WB_STRINGIFY(WB_VER_PRODUCT_VERSION_INFO)

// File version header.
#define WB_VER_FILEVERSION_HEADER WB_VER_PRODUCT_VERSION_HEADER

// File version info.
#define WB_VER_FILEVERSION_INFO WB_VER_PRODUCT_VERSION_INFO

// File version info string.
#define WB_VER_FILEVERSION_INFO_STR WB_STRINGIFY(WB_VER_FILEVERSION_INFO)

// All file flags mask.
#define WB_VER_FFI_FILEFLAGSMASK VS_FFI_FILEFLAGSMASK

// Debug flag.
#define WB_VER_FF_DEBUG VS_FF_DEBUG

#ifndef _DEBUG
// Release file flags.
#define WB_VER_FILEFLAGS 0
#else
// Debug file flags.
#define WB_VER_FILEFLAGS WB_VER_FF_DEBUG
#endif

// App long product name.
#define WB_APP_VER_PRODUCT_NAME_STR "WhiteBox Games Collection"

// App file version header.
#define WB_APP_VER_FILE_VERSION_HEADER WB_VER_PRODUCT_VERSION_HEADER

// App file version info.
#define WB_APP_VER_FILE_VERSION_INFO WB_VER_PRODUCT_VERSION_INFO

// App file version as string.
#define WB_APP_VER_FILE_VERSION_INFO_STR \
  WB_STRINGIFY(WB_APP_VER_FILE_VERSION_INFO)

// App file description.
#define WB_APP_VER_FILE_DESCRIPTION_STR "Bink© media player wrapper"

#ifdef _WIN32
// App file internal name.  Should be the original filename, without
// extension.
#define WB_APP_VER_INTERNAL_NAME_STR "binkmp"

// App file original name.  This information enables an application to
// determine whether a file has been renamed by a user.
#define WB_APP_VER_ORIGINAL_NAME_STR WB_APP_VER_INTERNAL_NAME_STR ".dll"
#endif  // _WIN32

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE 101
#define _APS_NEXT_COMMAND_VALUE 40001
#define _APS_NEXT_CONTROL_VALUE 1001
#define _APS_NEXT_SYMED_VALUE 101
#endif
#endif
