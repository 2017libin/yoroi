# yoroi

reference: **Yoroi: Updatable Whitebox Cryptography**


# build
use the follow command to build the project and generate the executable **main**, the main function is included in **sample/main.c**
```bash
mkdir build
cd build 
cmake ..
make
```

# update T table
1. call the **sample_print_T_table** function in **sampel/main.c**
2. **build** the project and generate the executable **main**
3. use the follow command to update the T tables in src/T_tables.c
```bash
./main > ../src/T_tables.c
```