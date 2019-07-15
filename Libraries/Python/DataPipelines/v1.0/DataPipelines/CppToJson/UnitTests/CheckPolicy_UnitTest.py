'''Unit test for CheckPolicy.py
'''
import sys
import unittest

from DataPipelines.CppToJson import CheckPolicy

class FuncTest(unittest.TestCase):
    
    def testInt64(self):
        self.assertEqual(True, CheckPolicy.Policy("std::int64_t"))

    def testFloat(self):
        self.assertEqual(True, CheckPolicy.Policy("float32"))

    def testComplex(self):
        self.assertEqual(True, CheckPolicy.Policy("complex64"))

    def testBFloat(self):
        self.assertEqual(True, CheckPolicy.Policy("bfloat16"))

    def testBool(self):
        self.assertEqual(True, CheckPolicy.Policy("bool"))

    def testConst(self):
        self.assertEqual(True, CheckPolicy.Policy("const std::int64_t"))
    
    def testAmper(self):
        self.assertEqual(True, CheckPolicy.Policy("std::int64_t &"))

    def testStar(self):
        self.assertEqual(False, CheckPolicy.Policy("std::int64_t *"))

    def testStringArray(self):
        self.assertEqual(True, CheckPolicy.Policy("std::array<char, 3>"))
    
    def testString(self):
        self.assertEqual(True, CheckPolicy.Policy("std::string"))

    def testAnyArray(self):
        self.assertEqual(True, CheckPolicy.Policy("std::array<bool, 23>"))
        self.assertEqual(True, CheckPolicy.Policy("std::array<complex64, 1>"))

    def testAnyVector(self):
        self.assertEqual(True, CheckPolicy.Policy("std::vector<std::int32_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::vector<bfloat16>"))

    def testAnyMap(self):
        self.assertEqual(True, CheckPolicy.Policy("std::map<bool, std::int64_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::map<bool, bool>"))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::string, complex128>"))

    def testAnyOptional(self):
        self.assertEqual(True, CheckPolicy.Policy("std::optional<std::int32_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::optional<bfloat16>"))

    def testFunction(self):
        self.assertEqual(True, CheckPolicy.Policy("std::function<bfloat16(bool)>"))
        self.assertEqual(True, CheckPolicy.Policy("std::function<complex64(bool, std::string, std::int64_t)>"))
        self.assertEqual(True, CheckPolicy.Policy("std::function<std::string()>"))

    def testRecursive(self):
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<bool>, std::int64_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<std::array<bool, 3>>, std::int64_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<std::string, complex128, 3>>, std::int64_t>"))
        self.assertEqual(True, CheckPolicy.Policy("std::function<complex64(std::vector<std::map<bool, std::int32_t>>, std::string, std::int64_t)>"))

    def testInvalidRecursive(self):
        self.assertEqual(False, CheckPolicy.Policy("std::map<std::vector<std::array<std::map<std::string, 3, 3>>, std::int64_t>"))
    
    def testWrongNumberOfArguments(self):
        self.assertEqual(False, CheckPolicy.Policy("std::vector<bool, bool>"))
        self.assertEqual(False, CheckPolicy.Policy("std::map<bool, bool, bool>"))
        
    def testNoStd(self):
        self.assertEqual(False, CheckPolicy.Policy("vector<bool>"))
        self.assertEqual(False, CheckPolicy.Policy("map<string, complex128>"))
        self.assertEqual(False, CheckPolicy.Policy("int"))

    def testWrongTypes(self):
        self.assertEqual(False, CheckPolicy.Policy("T"))
        self.assertEqual(False, CheckPolicy.Policy("std::int300"))

if __name__ == '__main__':
    unittest.main()
