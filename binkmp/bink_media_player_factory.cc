// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#include "bink_media_player_factory.h"

#include "bink_media_player.h"
#include "ibink_media_player.h"

namespace bink {
const char* SetupBinkSoundSystem(BinkSoundOutputSystem sound_system,
#if defined(__RADWIN__) || defined(__RADLINUX__)
                                 void* sound_system_parameter
#endif
                                 ) noexcept {
  switch (sound_system) {
    case BinkSoundOutputSystem::Unknown:
      return "Bink Sound System not set.";

#ifdef __RADWIN__
    case BinkSoundOutputSystem::DirectSound:
      return BinkSoundUseDirectSound(sound_system_parameter)
                 ? nullptr
                 : "Bink Sound System not set to Direct Sound.";
#endif

#ifndef __RADMAC__
    case BinkSoundOutputSystem::Miles:
      return BinkSoundUseMiles(sound_system_parameter)
                 ? nullptr
                 : "Bink Sound System not set to Miles Sound System.";
#endif

#ifdef __RADLINUX__
    case BinkSoundOutputSystem::SdlMixer:
      return BinkSoundUseSDLMixer() ? nullptr
             : "Bink Sound System not set to SDL_mixer."
#endif

#ifdef __RADMAC__
                 // clang-format off
    case BinkSoundOutputSystem::SoundManager:
      return BinkSoundUseSoundManager() ? nullptr
            : "Bink Sound System not set to MacOS Sound Manager.";
      // clang-format on
#endif

    default:
      return "Bink Sound System is set to unknown value.";
  }
}

CreateResult<IBinkMediaPlayer> BinkMediaPlayerFactory::Create(
    const BinkMediaPlayerSettings& settings) {
  const char* setup_error {
    SetupBinkSoundSystem(settings.sound_output_system,
#if defined(__RADWIN__)
                         settings.miles_driver_or_direct_sound
#elif defined(__RADLINUX__)
                         settings.miles_driver
#endif
    )
  };
  if (setup_error) return CreateResult<IBinkMediaPlayer>{setup_error};

  auto player = std::make_unique<BinkMediaPlayer>(settings);
  return player->IsOpened() && player->UpdateWindowPos()
             ? CreateResult<IBinkMediaPlayer>{std::move(player)}
             : CreateResult<IBinkMediaPlayer>{player->GetLastError()};
}
}  // namespace bink