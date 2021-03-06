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

#include <cassert>

#include "source/fuzz/random_generator.h"
#include "source/util/make_unique.h"

typedef uint32_t (*uint32_generator_t)(uint32_t);
typedef uint64_t (*uint64_generator_t)(uint64_t);
typedef double (*double_generator_t)();

namespace {

class RandomGeneratorFromCallbacks : public spvtools::fuzz::RandomGenerator {
 public:
  RandomGeneratorFromCallbacks(uint32_generator_t uint32_t_generator,
                               uint64_generator_t uint64_t_generator,
                               double_generator_t double_generator)
      : uint32_t_generator_(uint32_t_generator),
        uint64_t_generator_(uint64_t_generator),
        double_generator_(double_generator){

        };

  ~RandomGeneratorFromCallbacks() override = default;

  uint32_t RandomUint32(uint32_t bound) override {
    return uint32_t_generator_(bound);
  }

  uint64_t RandomUint64(uint64_t bound) override {
    return uint64_t_generator_(bound);
  }

  uint32_t RandomPercentage() override { return RandomUint32(101); }

  bool RandomBool() override { return RandomUint32(1); }

  double RandomDouble() override { return double_generator_(); }

 private:
  uint32_generator_t uint32_t_generator_;
  uint64_generator_t uint64_t_generator_;
  double_generator_t double_generator_;
};

}

extern "C" {
int run_spirv_fuzz(int argc, const char** argv, uint32_generator_t uint32_t_generator, uint64_generator_t uint64_generator, double_generator_t double_generator) {
  return spvtools::fuzz::MainHelper(argc, argv, spvtools::MakeUnique<RandomGeneratorFromCallbacks>(uint32_t_generator, uint64_generator, double_generator));
}

}
