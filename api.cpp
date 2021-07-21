#include <emscripten/bind.h>
#include "pblib/pb2cnf.h"

using namespace PBLib;
using namespace emscripten;

PB2CNF inst;

std::vector<int32_t> arrToVecI32(val arr) {
  return vecFromJSArray<int32_t>(arr);
}

std::vector<int64_t> arrToVecI64(val arr) {
  std::vector<double> doubleWeights = vecFromJSArray<double>(arr);
  std::vector<int64_t> weights(doubleWeights.begin(), doubleWeights.end());
  return weights;
}

void appendFormula(val formulaArr, std::vector<std::vector<int32_t>>& formula) {
  for (std::vector<int32_t> clause : formula) {
    val clauseArr = val::array();
    for (int32_t lit : clause) {
      clauseArr.call<void>("push", val(lit));
    }
    formulaArr.call<void>("push", clauseArr);
  }
}

int32_t encodeAtMostK(val literalsArr, double k, val formulaArr, int32_t firstAuxiliaryVariable) {
  std::vector<int32_t> literals = arrToVecI32(literalsArr);
  std::vector<std::vector<int32_t>> formula;
  firstAuxiliaryVariable = 1 + inst.encodeAtMostK(literals, (int64_t) k, formula, firstAuxiliaryVariable);
  appendFormula(formulaArr, formula);
  return firstAuxiliaryVariable;
}

int32_t encodeAtLeastK(val literalsArr, double k, val formulaArr, int32_t firstAuxiliaryVariable) {
  std::vector<int32_t> literals = arrToVecI32(literalsArr);
  std::vector<std::vector<int32_t>> formula;
  firstAuxiliaryVariable = 1 + inst.encodeAtLeastK(literals, (int64_t) k, formula, firstAuxiliaryVariable);
  appendFormula(formulaArr, formula);
  return firstAuxiliaryVariable;
}

int32_t encodeLeq(val weightsArr, val literalsArr, double leq, val formulaArr, int32_t firstAuxiliaryVariable) {
  std::vector<int64_t> weights = arrToVecI64(weightsArr);
  std::vector<int32_t> literals = arrToVecI32(literalsArr);
  std::vector<std::vector<int32_t>> formula;
  firstAuxiliaryVariable = 1 + inst.encodeLeq(weights, literals, (int64_t) leq, formula, firstAuxiliaryVariable);
  appendFormula(formulaArr, formula);
  return firstAuxiliaryVariable;
}

int32_t encodeGeq(val weightsArr, val literalsArr, double geq, val formulaArr, int32_t firstAuxiliaryVariable) {
  std::vector<int64_t> weights = arrToVecI64(weightsArr);
  std::vector<int32_t> literals = arrToVecI32(literalsArr);
  std::vector<std::vector<int32_t>> formula;
  firstAuxiliaryVariable = 1 + inst.encodeGeq(weights, literals, (int64_t) geq, formula, firstAuxiliaryVariable);
  appendFormula(formulaArr, formula);
  return firstAuxiliaryVariable;
}

int32_t encodeBoth(val weightsArr, val literalsArr, double leq, double geq, val formulaArr, int32_t firstAuxiliaryVariable) {
  std::vector<int64_t> weights = arrToVecI64(weightsArr);
  std::vector<int32_t> literals = arrToVecI32(literalsArr);
  std::vector<std::vector<int32_t>> formula;
  firstAuxiliaryVariable = 1 + inst.encodeBoth(weights, literals, (int64_t) leq, (int64_t) geq, formula, firstAuxiliaryVariable);
  appendFormula(formulaArr, formula);
  return firstAuxiliaryVariable;
}

// Binding code
EMSCRIPTEN_BINDINGS(pb2cnf) {
  function("encodeAtMostK", &encodeAtMostK);
  function("encodeAtLeastK", &encodeAtLeastK);
  function("encodeLeq", &encodeLeq);
  function("encodeGeq", &encodeGeq);
  function("encodeBoth", &encodeBoth);
}
