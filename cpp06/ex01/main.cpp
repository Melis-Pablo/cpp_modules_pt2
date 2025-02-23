#include <iostream>
#include <cstring>
#include "Serializer.hpp"
#include <string>

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Test utility functions
void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED)
              << testName << ": "
              << (success ? "PASS" : "FAIL")
              << RESET << std::endl;
}

void printSubHeader(const std::string& header) {
    std::cout << CYAN << "--- " << header << " ---" << RESET << std::endl;
}

int main() {
    // PDF/Project Specific Tests
    {
        printHeader("Basic Serialization Tests");

        char str[] = "test";
        Data original = {42, str};
        uintptr_t serialized = Serializer::serialize(&original);
        Data* deserialized = Serializer::deserialize(serialized);

        // Test pointer equality
        printTestResult("Pointer preservation", &original == deserialized);

        // Test data integrity
        bool dataIntact = (original.value == deserialized->value &&
                          strcmp(original.str, deserialized->str) == 0);
        printTestResult("Data integrity", dataIntact);
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        // Null pointer test
        printSubHeader("Null Pointer Test");
        Data* nullPtr = NULL;
        uintptr_t serializedNull = Serializer::serialize(nullPtr);
        Data* deserializedNull = Serializer::deserialize(serializedNull);
        printTestResult("Null pointer preservation", deserializedNull == NULL);

        // Multiple serialization/deserialization
        printSubHeader("Multiple Conversions Test");
        char str[] = "test2";
        Data data = {24, str};
        uintptr_t ser1 = Serializer::serialize(&data);
        uintptr_t ser2 = Serializer::serialize(&data);
        Data* deser1 = Serializer::deserialize(ser1);
        Data* deser2 = Serializer::deserialize(ser2);

        printTestResult("Multiple serializations equality", ser1 == ser2);
        printTestResult("Multiple deserializations equality", deser1 == deser2);
        printTestResult("Original pointer preservation", deser1 == &data);
    }

    // Array Tests
    {
        printHeader("Array Tests");

        // Test with array of Data
        char str1[] = "one";
        char str2[] = "two";
        char str3[] = "three";
        Data dataArray[3] = {
            {1, str1},
            {2, str2},
            {3, str3}
        };

        uintptr_t serializedArray[3];
        Data* deserializedArray[3];

        for (int i = 0; i < 3; i++) {
            serializedArray[i] = Serializer::serialize(&dataArray[i]);
            deserializedArray[i] = Serializer::deserialize(serializedArray[i]);
        }

        bool arrayPointersCorrect = true;
        bool arrayDataIntact = true;

        for (int i = 0; i < 3; i++) {
            if (&dataArray[i] != deserializedArray[i])
                arrayPointersCorrect = false;
            if (dataArray[i].value != deserializedArray[i]->value ||
                strcmp(dataArray[i].str, deserializedArray[i]->str) != 0)
                arrayDataIntact = false;
        }

        printTestResult("Array pointer preservation", arrayPointersCorrect);
        printTestResult("Array data integrity", arrayDataIntact);
    }

    // Memory Address Tests
    {
        printHeader("Memory Address Tests");

        char str[] = "address_test";
        Data data = {100, str};
        uintptr_t serialized = Serializer::serialize(&data);

        // Test if serialized value matches actual address
        std::cout << BLUE << "Original address: " << (void*)&data << RESET << std::endl;
        std::cout << BLUE << "Serialized value: " << "0x" << std::hex << serialized << RESET << std::endl;

        Data* deserialized = Serializer::deserialize(serialized);
        std::cout << BLUE << "Deserialized address: " << (void*)deserialized << RESET << std::endl;

        printTestResult("Address value preservation",
                       reinterpret_cast<uintptr_t>(&data) == serialized);
    }

    return 0;
}