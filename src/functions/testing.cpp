#include "duckdb/function/function_set.hpp"
#include "duckdb/parser/parsed_data/create_scalar_function_info.hpp"
#include "functions/functions.hpp"
#include <iostream>
#include <vector>
#include "duckdb/common/types/value.hpp"
#include <chrono>

using namespace std; 
using namespace std::chrono;

namespace scrooge {

template <typename T>
void LatestSymValueFunctionImpl(duckdb::DataChunk &args, duckdb::ExpressionState &state, duckdb::Vector &result) {
    auto start = steady_clock::now(); 
    auto &input1 = args.data[0];
    auto &input2 = args.data[1];
    auto &input3 = args.data[2];

    // Initialize the result vector as a list of T
    duckdb::Vector new_vector(result.GetType());

    size_t arraySize = duckdb::ListVector::GetListSize(input3);
    std::cout << "Array size: " << arraySize << std::endl;

    // Temporary storage for the result values
    std::vector<T> values(arraySize);

    for(size_t i = 0; i < args.size(); i++) {
        auto list_value = input3.GetValue(i); // Get the list at the index i
        auto &list_elements = duckdb::ListValue::GetChildren(list_value);

        cout << input1.GetValue(i) << " " << input2.GetValue(i) << " " << input3.GetValue(i) << endl;

        for(size_t l = 0; l < arraySize; l++) {  
            if(list_elements[l].ToString() == input2.GetValue(i).ToString()) {
                values[l] = input1.GetValue(i).GetValue<T>();
            }
        }

        std::vector<duckdb::Value> value_list; 
        for (const auto &elem : values) { 
            value_list.push_back(duckdb::Value::CreateValue<T>(elem)); 
        }

        //new_vector.SetValue(i, duckdb::Value::LIST(value_list));
    }

    result.Reference(new_vector);
    auto end = steady_clock::now(); // End timing
    auto duration = duration_cast<nanoseconds>(end - start); // Calculate duration
    cout << "Function execution time: " << duration.count() << " nanoseconds" << endl;
}

void LatestSymValueFunction(duckdb::DataChunk &args, duckdb::ExpressionState &state, duckdb::Vector &result) {
    auto &input1 = args.data[0];

    switch(input1.GetType().id()) {
        case duckdb::LogicalTypeId::VARCHAR:
            LatestSymValueFunctionImpl<std::string>(args, state, result);
            break;
        case duckdb::LogicalTypeId::INTEGER:
            LatestSymValueFunctionImpl<int32_t>(args, state, result);
            break;
        case duckdb::LogicalTypeId::BIGINT:
            LatestSymValueFunctionImpl<int64_t>(args, state, result);
            break;
        case duckdb::LogicalTypeId::DOUBLE:
            LatestSymValueFunctionImpl<double>(args, state, result);
            break;
        default:
            throw duckdb::NotImplementedException("Unsupported data type for LatestSymValueFunction");
    }
}

void LatestSymValue::RegisterFunction(duckdb::Connection &conn, duckdb::Catalog &catalog) {
    // Create the scalar function set
    duckdb::ScalarFunctionSet latest_sym_value("latest_sym_value");

    // Create a lambda function that wraps the LatestSymValueFunction
    auto scalar_function = [](duckdb::DataChunk &args, duckdb::ExpressionState &state, duckdb::Vector &result) {
        LatestSymValueFunction(args, state, result);
    };

    // Add the function definitions for specific types
    latest_sym_value.AddFunction(duckdb::ScalarFunction(
        {duckdb::LogicalType::VARCHAR, duckdb::LogicalType::VARCHAR, duckdb::LogicalType::LIST(duckdb::LogicalType::VARCHAR)}, // Input types
        duckdb::LogicalType::LIST(duckdb::LogicalType::VARCHAR),   // Return type
        scalar_function
    ));
    latest_sym_value.AddFunction(duckdb::ScalarFunction(
        {duckdb::LogicalType::INTEGER, duckdb::LogicalType::VARCHAR, duckdb::LogicalType::LIST(duckdb::LogicalType::VARCHAR)}, // Input types
        duckdb::LogicalType::LIST(duckdb::LogicalType::INTEGER),   // Return type
        scalar_function
    ));
    latest_sym_value.AddFunction(duckdb::ScalarFunction(
        {duckdb::LogicalType::BIGINT, duckdb::LogicalType::VARCHAR, duckdb::LogicalType::LIST(duckdb::LogicalType::VARCHAR)}, // Input types
        duckdb::LogicalType::LIST(duckdb::LogicalType::BIGINT),   // Return type
        scalar_function
    ));
    latest_sym_value.AddFunction(duckdb::ScalarFunction(
        {duckdb::LogicalType::DOUBLE, duckdb::LogicalType::VARCHAR, duckdb::LogicalType::LIST(duckdb::LogicalType::VARCHAR)}, // Input types
        duckdb::LogicalType::LIST(duckdb::LogicalType::DOUBLE),   // Return type
        scalar_function
    ));
    duckdb::CreateScalarFunctionInfo latest_sym_value_info(latest_sym_value);
    catalog.CreateFunction(*conn.context, &latest_sym_value_info);
}

} // namespace scrooge
