// Copyright 2026 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_NAIVE_NAIVE_LOGGING_H_
#define NET_TOOLS_NAIVE_NAIVE_LOGGING_H_

#include "base/logging.h"
#include "net/tools/naive/naive_config.h"

namespace net {

// Mirrors NaiveConfig::min_log_level. Connection tracing uses NAIVE_LOG_INFO()
// and is emitted only when this is LOGGING_INFO.
inline logging::LogSeverity g_naive_min_log_level = logging::LOGGING_ERROR;

inline void ApplyNaiveLoggingSettings(const NaiveConfig& config) {
  g_naive_min_log_level = config.min_log_level;
  if (config.log.logging_dest != logging::LOG_NONE) {
    logging::SetMinLogLevel(config.min_log_level);
  }
}

inline bool NaiveConnectionTracingEnabled() {
  return g_naive_min_log_level <= logging::LOGGING_INFO;
}

}  // namespace net

// Naive connection/resolver tracing. Respects log-level: info enables these,
// warning/error suppress them. Chromium LOG(ERROR)/LOG(WARNING) are unaffected.
#define NAIVE_LOG_INFO() \
  LAZY_STREAM(LOG_STREAM(INFO), ::net::NaiveConnectionTracingEnabled())

#endif  // NET_TOOLS_NAIVE_NAIVE_LOGGING_H_
