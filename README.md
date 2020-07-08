## API

### Querying Terminals

Query a terminal
```
GET /terminals/1
```

```json
{
  "id": 1,
  "cardType": [ "Visa", "EFTPOS" ],
  "TransactionType": [ "Cheque", "Savings" ]
}
```

Query all terminals
```
GET /terminals
```

```json
{
  "terminals":
  [
    {
      "id": 0,
      "cardType": [ "Visa", "MasterCard", "EFTPOS" ],
      "TransactionType": [ "Cheque", "Savings", "Credit" ]
    },
    {
      "id": 1,
      "cardType": [ "Visa", "EFTPOS" ],
      "TransactionType": [ "Cheque", "Savings" ]
    },
    //...
  ]
}
```

### Adding a Terminal

Query a terminal
```
GET /terminals/1
```

```json
{
  "id": 1,
  "cardType": [ "Visa", "EFTPOS" ],
  "TransactionType": [ "Cheque", "Savings" ]
}
```

## Interacting with CURL

```bash
curl -X GET -H "Accept: application/json" localhost:8888/terminals
```

```bash
curl -X POST -H "Accept: application/json" --data '{"cardType": ["visa", "MasterCard"], "TransactionType": ["Cheque"]}' localhost:8888/terminals
```

## Dependencies

### Cmake
https://cmake.org/install/

### Libmicrohttpd

On Mac:
```bash
brew install libmicrohttpd
```

On Ubuntu:
```bash
sudo apt install libmicrohttpd
```

On Windows:
???

## Build

### From Command Line

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### VSCode

Install the CMake Tools extension and use the little blue bar at the bottom of the window ;)
