// Copyright (c) 2021 Alastair F. Donaldson
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

#include <iostream>
#include <utility>
#include <vector>

#include "tools/fuzz/fuzz.h"

int main(int argc, const char** argv) {
  if (argc != 1) {
    std::cerr << argv[0] << " takes no arguments." << std::endl;
    exit(1);
  }

  std::vector<std::string> spirv_filenames = {
      "binarysearch_bw.frag.spv",
      "binarysearch_bw-O.frag.spv",
      "binarysearch_bw-Os.frag.spv",
      "binarysearch_tree.frag.spv",
      "binarysearch_tree-O.frag.spv",
      "binarysearch_tree-Os.frag.spv",
      "bubblesort_flag_intfunctions.frag.spv",
      "bubblesort_flag_intfunctions-O.frag.spv",
      "bubblesort_flag_intfunctions-Os.frag.spv",
      "colorgrid_modulo.frag.spv",
      "colorgrid_modulo_intfunctions.frag.spv",
      "colorgrid_modulo_intfunctions-O.frag.spv",
      "colorgrid_modulo_intfunctions-Os.frag.spv",
      "colorgrid_modulo-O.frag.spv",
      "colorgrid_modulo-Os.frag.spv",
      "householder_lattice.frag.spv",
      "householder_lattice-O.frag.spv",
      "householder_lattice-Os.frag.spv",
      "mandelbrot_fixed_point.frag.spv",
      "mandelbrot_fixed_point-O.frag.spv",
      "mandelbrot_fixed_point-Os.frag.spv",
      "mandelbrot_zoom.frag.spv",
      "mandelbrot_zoom_intfunctions.frag.spv",
      "mandelbrot_zoom_intfunctions-O.frag.spv",
      "mandelbrot_zoom_intfunctions-Os.frag.spv",
      "mandelbrot_zoom-O.frag.spv",
      "mandelbrot_zoom-Os.frag.spv",
      "matrices_many_loops.frag.spv",
      "matrices_many_loops-O.frag.spv",
      "matrices_many_loops-Os.frag.spv",
      "matrices_smart_loops.frag.spv",
      "matrices_smart_loops-O.frag.spv",
      "matrices_smart_loops-Os.frag.spv",
      "mergesort_mosaic.frag.spv",
      "mergesort_mosaic-O.frag.spv",
      "mergesort_mosaic-Os.frag.spv",
      "muller.frag.spv",
      "muller-O.frag.spv",
      "muller-Os.frag.spv",
      "prefix_sum_checkers.frag.spv",
      "prefix_sum_checkers-O.frag.spv",
      "prefix_sum_checkers-Os.frag.spv",
      "prefix_sum.frag.spv",
      "prefix_sum_intfunctions.frag.spv",
      "prefix_sum_intfunctions-O.frag.spv",
      "prefix_sum_intfunctions-Os.frag.spv",
      "prefix_sum-O.frag.spv",
      "prefix_sum-Os.frag.spv",
      "quicksort_palette.frag.spv",
      "quicksort_palette-O.frag.spv",
      "quicksort_palette-Os.frag.spv",
      "selection_sort_struct.frag.spv",
      "selection_sort_struct-O.frag.spv",
      "selection_sort_struct-Os.frag.spv",
      "squares.frag.spv",
      "squares_intfunctions.frag.spv",
      "squares_intfunctions-O.frag.spv",
      "squares_intfunctions-Os.frag.spv",
      "squares-O.frag.spv",
      "squares-Os.frag.spv",
      "stable_bifurcation.frag.spv",
      "stable_bifurcation-O.frag.spv",
      "stable_bifurcation-Os.frag.spv",
      "stable_binarysearch_tree.frag.spv",
      "stable_binarysearch_tree-O.frag.spv",
      "stable_binarysearch_tree-Os.frag.spv",
      "stable_bubblesort_flag.frag.spv",
      "stable_bubblesort_flag-O.frag.spv",
      "stable_bubblesort_flag-Os.frag.spv",
      "stable_collatz.frag.spv",
      "stable_collatz-O.frag.spv",
      "stable_collatz-Os.frag.spv",
      "stable_colorgrid_modulo.frag.spv",
      "stable_colorgrid_modulo-O.frag.spv",
      "stable_colorgrid_modulo-Os.frag.spv",
      "stable_logicops.frag.spv",
      "stable_logicops-O.frag.spv",
      "stable_logicops-Os.frag.spv",
      "stable_maze.frag.spv",
      "stable_maze-O.frag.spv",
      "stable_maze-Os.frag.spv",
      "stable_mergesort.frag.spv",
      "stable_mergesort-O.frag.spv",
      "stable_mergesort-Os.frag.spv",
      "stable_orbit.frag.spv",
      "stable_orbit-O.frag.spv",
      "stable_orbit-Os.frag.spv",
      "stable_pillars.frag.spv",
      "stable_pillars-O.frag.spv",
      "stable_pillars-Os.frag.spv",
      "stable_quicksort.frag.spv",
      "stable_quicksort-O.frag.spv",
      "stable_quicksort-Os.frag.spv",
      "stable_rects.frag.spv",
      "stable_rects-O.frag.spv",
      "stable_rects-Os.frag.spv",
      "stable_triangle.frag.spv",
      "stable_triangle-O.frag.spv",
      "stable_triangle-Os.frag.spv",
      "trigonometric_strip.frag.spv",
      "trigonometric_strip-O.frag.spv",
      "trigonometric_strip-Os.frag.spv",
      "truthtable.frag.spv",
      "truthtable-O.frag.spv",
      "truthtable-Os.frag.spv"};

  size_t num_errors = 0;
  for (size_t index = 0;
       index < std::min(static_cast<size_t>(2), spirv_filenames.size());
       index++) {
    auto spirv_filename = spirv_filenames[index];
    std::cerr << index << "/" << spirv_filenames.size() << ": "
              << spirv_filename << std::endl;
    std::string output_filename = "out" + spirv_filename;
    std::string seed_argument = "--seed=" + std::to_string(index);
    std::vector<const char*> main_helper_args = {argv[0],
                                                 spirv_filename.c_str(),
                                                 "-o",
                                                 output_filename.c_str(),
                                                 seed_argument.c_str(),
                                                 "--donors=donors.txt"};
    if (0 !=
        spvtools::fuzz::MainHelper(static_cast<int>(main_helper_args.size()),
                                   main_helper_args.data())) {
      num_errors++;
    }
  }
  if (num_errors > 0) {
    std::cerr << num_errors << " invocation(s) of the fuzzer failed."
              << std::endl;
    return 1;
  }
  return 0;
}
