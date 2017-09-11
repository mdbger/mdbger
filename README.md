# mdbger
A C/C++ memory debugger

This project includes 10 parts:

Main modules:

1. memory logger: this module records memory activity and generate a log
2. memory cache: this module converts the small dataset into the B+ tree.
3. memory store: this module saves cache into database periodically or when cache is full
4. memory debugger server: this module is a dameon and reads data from memory store by request
5. memory debugger client: this module is a client to send debug commands 

Misc modules:

6. format converter: convert data between 3 different format: log, data records and json
7. stacktrace hash: To not save the whole call stacktrace, a stacktrace hash will be created to do the mapping. 
8. debug command parser
9. memory hook
10. 
