import duckdb

# Connect to an in-memory DuckDB database with the required configuration
con = duckdb.connect(':memory:', config={'allow_unsigned_extensions': 'true'})

# Set the configuration for allowing extensions with metadata mismatch
con.execute("SET allow_extensions_metadata_mismatch=true;")

# Install the 'scrooge' extension
con.execute("INSTALL '/home/k8/Documents/Scrooge-McDuck/build/release/extension/scrooge/scrooge.duckdb_extension';")

# Load the CSV file into DuckDB and execute the query
result = con.execute("SELECT latest_sym_value(ask_quantity,symbol,ARRAY['ZNU2','TNZ1','ZBH2']) FROM 'dato.csv' order by nanotime;").fetchone()

print(result)

#close
con.close()