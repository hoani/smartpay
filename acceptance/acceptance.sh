#!/bin/bash

function test_case () {
  expected=$1
  result=$2

  if [ "$result" != "$expected" ]
  then
    echo -e "\033[31mFAIL\033[39m"
    echo -e "\t" $expected "!=" $result
    exit 1
  fi
  echo -e "\033[32mPASS\033[39m"
}

echo "Test Simple GET"
test_case "" "$(curl -X GET localhost:11337 2> /dev/null)"

echo "Test POST Terminal"
test_case "0" "$(curl -X POST -d '{"cardType": ["Visa", "MasterCard"], "TransactionType": ["Savings"]}' localhost:11337/terminals 2> /dev/null)"

echo "Test GET Terminal"
test_case '{"id":0,"cardType":["Visa","MasterCard"],"TransactionType":["Savings"]}' "$(curl -X GET localhost:11337/terminals/0 2> /dev/null)"

echo "Test POST More Terminals"
test_case "1" "$(curl -X POST -d '{"cardType": ["Visa", "MasterCard"], "TransactionType": ["Savings"]}' localhost:11337/terminals 2> /dev/null)"
test_case "2" "$(curl -X POST -d '{"cardType": ["EFTPOS"], "TransactionType": ["Cheque"]}' localhost:11337/terminals 2> /dev/null)"
test_case "3" "$(curl -X POST -d '{"cardType": ["Visa", "EFTPOS"], "TransactionType": ["Credit"]}' localhost:11337/terminals 2> /dev/null)"
test_case "4" "$(curl -X POST -d '{"cardType": ["Visa", "MasterCard", "EFTPOS"], "TransactionType": ["Savings","Credit"]}' localhost:11337/terminals 2> /dev/null)"

echo "Test GET lots of Terminals"
test_case '{"terminals":[{"id":0,"cardType":["Visa","MasterCard"],"TransactionType":["Savings"]},{"id":1,"cardType":["Visa","MasterCard"],"TransactionType":["Savings"]},{"id":2,"cardType":["EFTPOS"],"TransactionType":["Cheque"]},{"id":3,"cardType":["Visa","EFTPOS"],"TransactionType":["Credit"]},{"id":4,"cardType":["Visa","MasterCard","EFTPOS"],"TransactionType":["Savings","Credit"]}]}' "$(curl -X GET localhost:11337/terminals 2> /dev/null)"

exit 0