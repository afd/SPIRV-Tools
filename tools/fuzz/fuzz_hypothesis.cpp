// Copyright (c) 2021 Imperial College London
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "tools/fuzz/fuzz.h"

#include "source/fuzz/pseudo_random_generator.h"
#include "source/fuzz/random_generator.h"
#include "source/util/make_unique.h"

typedef uint32_t (*uint32_generator_t)(uint32_t, uint32_t*);
typedef uint32_t (*uint64_generator_t)(uint64_t, uint64_t*);
typedef uint32_t (*double_generator_t)(double*);

namespace {

class RandomGeneratorFromCallbacks : public spvtools::fuzz::RandomGenerator {
 public:
  RandomGeneratorFromCallbacks(uint32_generator_t uint32_t_generator,
                               uint64_generator_t uint64_t_generator,
                               double_generator_t double_generator)
      : uint32_t_generator_(uint32_t_generator),
        uint64_t_generator_(uint64_t_generator),
        double_generator_(double_generator),
        fallback(nullptr){

        };

  ~RandomGeneratorFromCallbacks() override = default;

  uint32_t RandomUint32(uint32_t bound) override {
    if (fallback != nullptr) {
      return fallback->RandomUint32(bound);
    }
    uint32_t result;
    if (uint32_t_generator_(bound, &result)) {
      return result;
    }
    InitializeFallback();
    return RandomUint32(bound);
  }

  uint64_t RandomUint64(uint64_t bound) override {
    if (fallback != nullptr) {
      return fallback->RandomUint64(bound);
    }
    uint64_t result;
    if (uint64_t_generator_(bound, &result)) {
      return result;
    }
    InitializeFallback();
    return RandomUint64(bound);
  }

  uint32_t RandomPercentage() override { return RandomUint32(101); }

  bool RandomBool() override { return RandomUint32(1); }

  double RandomDouble() override {
    if (fallback != nullptr) {
      return fallback->RandomDouble();
    }
    double result;
    if (double_generator_(&result)) {
      return result;
    }
    InitializeFallback();
    return RandomDouble();
  }

  bool IsExhausted() const override { return fallback != nullptr; }

 private:
  void InitializeFallback() {
    fallback = spvtools::MakeUnique<spvtools::fuzz::PseudoRandomGenerator>(0);
  }
  uint32_generator_t uint32_t_generator_;
  uint64_generator_t uint64_t_generator_;
  double_generator_t double_generator_;
  std::unique_ptr<spvtools::fuzz::RandomGenerator> fallback;
};
}  // namespace

extern "C" {
int run_spirv_fuzz(int argc, const char** argv,
                   uint32_generator_t uint32_t_generator,
                   uint64_generator_t uint64_generator,
                   double_generator_t double_generator) {
  return spvtools::fuzz::MainHelper(
      argc, argv,
      spvtools::MakeUnique<RandomGeneratorFromCallbacks>(
          uint32_t_generator, uint64_generator, double_generator));
}
}
