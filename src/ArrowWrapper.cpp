#include "ArrowWrapper.hpp"
#include <arrow/type.h>
#include <memory>

ArrowWrapper::ArrowWrapper(shared_ptr<arrow::Array>& array): array(std::move(array)) {}

shared_ptr<arrow::DataType> ArrowWrapper::getType() {
  return array->type();
}