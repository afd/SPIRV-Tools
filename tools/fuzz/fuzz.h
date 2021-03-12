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

#ifndef TOOLS_FUZZ_FUZZ_H
#define TOOLS_FUZZ_FUZZ_H

#include <memory>

namespace spvtools {
namespace fuzz {

int MainHelper(int argc, const char** argv);

}  // namespace fuzz
}  // namespace spvtools

#endif  // TOOLS_FUZZ_FUZZ_H
