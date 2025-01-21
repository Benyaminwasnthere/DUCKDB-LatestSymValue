import duckdb
import os

# Path to your custom DuckDB extension file (replace with actual path)
#extension_path = '/home/k8/Documents/Scrooge-McDuck/build/release/extension/scrooge/scrooge.duckdb_extension'  # or .dylib/.dll depending on your platform
extension_path = 'extension/scrooge/scrooge.duckdb_extension' 
# Check if the file exists
if not os.path.isfile(extension_path):
    print(f"File not found: {extension_path}")
else:
    # Connect to DuckDB with the setting in the connection string
    con = duckdb.connect(database=':memory:', read_only=False, config={'allow_unsigned_extensions': 'true', 'allow_extensions_metadata_mismatch': 'true'})

    try:
        # Load the custom extension
        con.execute(f"SELECT extension_name, extension_version, installed_from, install_mode FROM duckdb_extensions();")
        con.execute(f"LOAD 'scrooge';")
        #con.execute(f"INSTALL '{extension_path}';")
        con.execute(f"SELECT extension_name, extension_version, installed_from, install_mode FROM duckdb_extensions();")
        print(con.fetchall())
        print("Extension loaded successfully.")
        result = con.execute("SELECT latest_sym_value(ask_quantity,symbol,ARRAY['ZNU2','TNZ1','ZBH2']) FROM 'dato.csv' order by nanotime;").fetchone()

        print(result)


    except Exception as e:
        print(f"Failed to load extension: {e}")

