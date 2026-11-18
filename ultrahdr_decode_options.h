/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <functional>
#include <utility>

namespace ultrahdr {
struct DecodeOptions {
  const std::function<bool()>* cancelled = nullptr;
  int threads = 0;
};

inline thread_local DecodeOptions decode_options;

class DecodeOptionsScope {
 public:
  DecodeOptionsScope(const std::function<bool()>& cancelled, int threads)
      : previous_(std::exchange(decode_options, {&cancelled, threads})) {}
  ~DecodeOptionsScope() { decode_options = previous_; }
  DecodeOptionsScope(const DecodeOptionsScope&) = delete;
  DecodeOptionsScope& operator=(const DecodeOptionsScope&) = delete;

 private:
  const DecodeOptions previous_;
};
}  // namespace ultrahdr
