#include <arrow/api.h>
#include <arrow/type.h>
#include <memory>

using namespace std;

class ArrowWrapper {
public:
  explicit ArrowWrapper(shared_ptr<arrow::Array>& array);

  shared_ptr<arrow::DataType> getType();

private:
  shared_ptr<arrow::Array> array;
};