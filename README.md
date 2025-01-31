# Scrooge McDuck: Latest Symbol Value Function

This repository extends **Scrooge McDuck**, a DuckDB extension for financial data analysis, by introducing the **`latest_sym_value`** function. This new function is designed to extract the latest corresponding value from a **list column** based on a given symbol. Additionally, unit tests have been implemented to ensure correctness and reliability.

## 📌 **Overview**
Scrooge McDuck is a **DuckDB extension** that facilitates financial data analysis by providing specialized functions for handling time-series data. This enhancement introduces **`latest_sym_value`**, which helps users retrieve the most recent value for a symbol from a list column.

## 🚀 **Features**
- Supports multiple data types: **VARCHAR, INTEGER, BIGINT, DOUBLE**
- Efficiently processes **list values** using DuckDB’s vectorized execution model
- Measures execution time for performance insights
- Fully integrated with **DuckDB's Scalar Function API**
- Includes **unit tests** to verify correctness across various input scenarios

## 📖 **Function Details**
### `latest_sym_value(input1, input2, input3) → LIST`
**Parameters:**
- `input1`: The list of values (e.g., price, quantity, etc.)
- `input2`: The target symbol to match
- `input3`: The list of corresponding symbols

**Returns:**
- A **list** containing the latest value(s) corresponding to `input2` from `input1`

**Example Query:**
```sql
SELECT latest_sym_value(price, 'AAPL', symbol_list)
FROM market_data;
```

## ⚙️ **Installation & Usage**
To use this function, ensure you have Scrooge McDuck installed. Then, load the extension:
```sql
LOAD 'build/release/scrooge.duckdb_extension';
```

## 🧪 **Unit Testing**
Unit tests have been implemented to validate the function’s behavior. The tests cover:
- **Different data types** (VARCHAR, INTEGER, BIGINT, DOUBLE)
- **Edge cases** (empty lists, unmatched symbols)
- **Performance benchmarks**

To run the tests:
```bash
./run_tests.sh
```

## 🛠 **Future Improvements**
- Optimize performance for large datasets
- Enable parallel execution
- Extend functionality for real-time financial data

## 👨‍💻 **Author**
Developed by **Benyamin Plaksienko** as an enhancement to the Scrooge McDuck DuckDB extension. Contributions and feedback are welcome!

---

**Filename:** `README.md`

