from qr import *

input = "01ICCOLO01121047415001<<<<<<<<<<9210181M3110278COL1030432234<2PEPITO<PEREZ<<DIOMEDES<DANIEL<<<<"
output = "1030432234"

def test(func, input, expected):
    result, output = func(input, expected)
    status = "ok" if result else "fail"
    print("  %s: %s (output: \"%s\", expected: \"%s\")" % (func.__name__, status, output, expected))
    return result

def test_dni(raw,expected):
    result = qr_dni_get(raw)
    return result == expected, result

if __name__ == '__main__':
    print("Parsing tests...")
    test(test_dni, input, output)
