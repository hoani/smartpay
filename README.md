## Incomplete Tasks

* Unit testing of `API` was lighter than I would have liked
* Took a few shortcuts with `microhttpd` which I suspect might have some memory repercussions, but I'm not sure
* The `parser` is very rigid, it would be nice to use a library like `json-c` instead
* Ideally, the `store` module would be a dynamically allocated linked-list
* Add `DELETE` support - there is some consideration in `store` for this, but it's primitive
* Add `PUT` for update support

## API

### Querying Terminals - IMPLEMENTED

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

### Adding a Terminal - IMPLEMENTED

To Add a terminal
```
POST /terminals '{"cardType": ["visa", "MasterCard"], "TransactionType": ["Cheque"]}'
```

The result will be the terminal id:
```json
0
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

## Acceptance Testing

Acceptance tests are run as a bash script. In one terminal execute the program:
```bash
./build/App
```

In another terminal, execute the tests:
```bash
./acceptance/acceptance.sh
```

## Unit Tests

Unit tests can be run after a build:
```bash
./build/test/tests/Test
```


