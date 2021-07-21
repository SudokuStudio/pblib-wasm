#include <emscripten/bind.h>
#include "pblib/pb2cnf.h"

using namespace PBLib;
using namespace emscripten;

PB2CNF inst;

std::vector<std::vector<int32_t>> encodeBoth(const std::vector<double>& weights, const std::vector<int32_t>& literals, double leq, double geq, int32_t firstAuxiliaryVariable)
{
  std::vector<int64_t> weights64(weights.begin(), weights.end());
  std::vector<std::vector<int32_t>> formula;
  inst.encodeBoth(weights64, literals, (int64_t) leq, (int64_t) geq, formula, firstAuxiliaryVariable);
  return formula;
}

// Binding code
EMSCRIPTEN_BINDINGS(pb2cnf) {
  register_vector<double>("VectorDouble");
  register_vector<int32_t>("VectorInt32");
  register_vector<std::vector<int32_t>>("VectorVectorInt32");

  function("encodeBoth", &encodeBoth);
}
