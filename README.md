# Roman Numeral Calculator

A basic calculator library that allows users to perform calculations like the Romans did.

## User Stories
### Addition
As a Roman bookkeeper, I want to be able to add two numbers together. So that I can do my work faster with fewer mathematical errors.
### Subtraction
As a Roman bookkeeper, I want to be able to subtract one number from another. So that I can do my work faster and with fewer mathematical errors.

## Requirements
1. Roman Numeral Constraints
    1. Roman numerals consist of the following letters: I, V, X, L, C, D, and M which mean one, five, ten, fifty, hundred, five hundred and one thousand respectively.
    2. An example would be "XIV" + "LX" = "LXXIV"
    3. Numerals can be concatenated to form a larger numeral ("XX" + "II" = "XXII").
    4. If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger ("IV"
means four, "CM" means ninehundred).
    5. If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).
    6. If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)
    7. The maximum roman numeral is 3999 (MMMCMXCIX)
2. Conversion Requirements (Derived / Implementation)
    1. The application shall convert roman numeral operands to integers to perform operations.
    2. Roman numeral string parameters shall not be modified during the conversion.
    3. Invalid string parameters shall return null.
    4. Valid string parameters shall return the converted integer.
    5. Roman numerals greater than 3999 (R1.7) shall return null.

## Design Constraints
1. Ubuntu Linux 14.04
2. The C programming language
3. GNU GCC compiler tool chain 
4. GNU Make
5. Check unit testing framework ( https://libcheck.github.io/check/ )
6. git

## Development Notes
The boiler plate for this project was based on the Autotools example found on the [Check Tutorial](https://libcheck.github.io/check/doc/check_html/check_3.html#Setting-Up-the-Money-Build-Using-CMake).

If you can find a real use for this code base it's licensed under the MIT License. 
