'''Unit test for CheckPolicy.py
'''
import sys
import unittest

from DataPipelines.CppToJson import CheckPolicy

class FuncTest(unittest.TestCase):
    
    def testInt64(self):
        self.assertEqual(True, CheckPolicy.Policy("std::int64_t", lambda type: False))

    def testFloat(self):
        self.assertEqual(True, CheckPolicy.Policy("float32", lambda type: False))

    def testComplex(self):
        self.assertEqual(True, CheckPolicy.Policy("complex64", lambda type: False))

    def testBFloat(self):
        self.assertEqual(True, CheckPolicy.Policy("bfloat16", lambda type: False))

    def testBool(self):
        self.assertEqual(True, CheckPolicy.Policy("bool", lambda type: False))

    def testConst(self):
        self.assertEqual(True, CheckPolicy.Policy("const std::int64_t", lambda type: False))
    
    def testAmper(self):
        self.assertEqual(True, CheckPolicy.Policy("std::int64_t &", lambda type: False))

    def testStar(self):
        self.assertEqual(False, CheckPolicy.Policy("std::int64_t *", lambda type: False))

    def testStringArray(self):
        self.assertEqual(True, CheckPolicy.Policy("std::array<char, 3>", lambda type: False))
    
    def testString(self):
        self.assertEqual(True, CheckPolicy.Policy("std::string", lambda type: False))

    def testAnyArray(self):
        self.assertEqual(True, CheckPolicy.Policy("std::array<bool, 23>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::array<complex64, 1>", lambda type: False))

    def testAnyVector(self):
        self.assertEqual(True, CheckPolicy.Policy("std::vector<std::int32_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::vector<bfloat16>", lambda type: False))

    def testAnyMap(self):
        self.assertEqual(True, CheckPolicy.Policy("std::map<bool, std::int64_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::map<bool, bool>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::string, complex128>", lambda type: False))

    def testAnyOptional(self):
        self.assertEqual(True, CheckPolicy.Policy("std::optional<std::int32_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::optional<bfloat16>", lambda type: False))

    def testFunction(self):
        self.assertEqual(True, CheckPolicy.Policy("std::function<bfloat16(bool)>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::function<complex64(bool, std::string, std::int64_t)>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::function<std::string()>", lambda type: False))

    def testRecursive(self):
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<bool>, std::int64_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<std::array<bool, 3>>, std::int64_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<std::string, complex128> 3>>, std::int64_t>", lambda type: False))
        self.assertEqual(True, CheckPolicy.Policy("std::function<complex64(std::vector<std::map<bool, std::int32_t>>, std::string, std::int64_t)>", lambda type: False))

    def testInvalidRecursive(self):
        self.assertEqual(False, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<std::string, 3, 3>>, std::int64_t>", lambda type: False))
    
    def testWrongNumberOfArguments(self):
        self.assertEqual(False, CheckPolicy.Policy("std::vector<bool, bool>", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("std::map<bool, bool, bool>", lambda type: False))
        
    def testNoStd(self):
        self.assertEqual(False, CheckPolicy.Policy("vector<bool>", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("map<string, complex128>", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("int", lambda type: False))

    def testWrongTypes(self):
        self.assertEqual(False, CheckPolicy.Policy("T", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("std::int300", lambda type: False))

    def testValidStruct(self):
        self.assertEqual(True, CheckPolicy.Policy("validStruct", lambda type: True))

    def testInvalidStruct(self):
        self.assertEqual(False, CheckPolicy.Policy("invalidStruct", lambda type: False))

    def testValidRecursiveStruct(self):
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<validStruct>, std::int64_t>", lambda type: True))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<validStruct1, validStruct2> 3>>, std::int64_t>", lambda type: True))
    
    def testInvalidRecursiveStruct(self):
        self.assertEqual(False, CheckPolicy.Policy("std::map<std::vector<validStruct>, std::int64_t>", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<validStruct1, validStruct2> 3>>, std::int64_t>", lambda type: False))
        self.assertEqual(False, CheckPolicy.Policy("std::vector<validStruct1, validStruct2>", lambda type: True))


if __name__ == '__main__':
    unittest.main()
