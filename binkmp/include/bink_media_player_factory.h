// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_FACTORY_H_
#define BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_FACTORY_H_

#include <memory>

#include "bink_base.h"
#include "bink_media_player_settings.h"
#include "ibink_media_player.h"

namespace bink {

/**
 * @brief Bink media player factory.
 */
class BINK_ATTRIBUTE_API BinkMediaPlayerFactory {
 public:
  /**
   * @brief Creates Bink media player.
   * @param settings Bink media player settings.
   * @return Either Bink media player or error description.
   */
  static CreateResult<IBinkMediaPlayer> Create(
      const BinkMediaPlayerSettings& settings);

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(BinkMediaPlayerFactory);

 private:
  BinkMediaPlayerFactory() = delete;
};

}  // namespace bink

#endif  // !BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_FACTORY_H_