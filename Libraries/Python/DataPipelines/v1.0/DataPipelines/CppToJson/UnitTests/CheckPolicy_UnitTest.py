'''Unit test for CheckPolicy.py
'''
import sys
import unittest

from DataPipelines.CppToJson import CheckPolicy

class FuncTest(unittest.TestCase):
    def testInt(self):
        self.assertEqual(True, CheckPolicy.Policy("int"))

    def testDouble(self):
        self.assertEqual(True, CheckPolicy.Policy("double"))

    def testClass(self):
        self.assertEqual(False, CheckPolicy.Policy("class"))

    def testConst(self):
        self.assertEqual(True, CheckPolicy.Policy("const"))

    def testVector(self):
        self.assertEqual(True, CheckPolicy.Policy("vector"))

    def testT(self):
        self.assertEqual(False, CheckPolicy.Policy("T"))

if __name__ == '__main__':
    unittest.main()
