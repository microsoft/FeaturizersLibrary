'''Integration tests for CppToJson.py
'''
import sys
import os
import json
import unittest
import CommonEnvironment

from DataPipelines import CppToJson


# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------


class FileTest(unittest.TestCase):
    '''
        The purpose of this function is to verify the file-based capabilities of the ObtainFunctions method. It will make sure
        that the files are being opened and the information inside is being correctly processed.
    '''
    def test_basic_file(self):
        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "basicFunc.cpp"), None, lambda type: True)

        self.assertEqual(func_list[0], {'func_name': 'add', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': ['a', 'b'], 'raw_var_types': ['int', 'int'], 'simple_var_types': ['int', 'int']})
        self.assertEqual(func_list[1], {'func_name': 'sub', 'raw_return_type': 'float', 'simple_return_type': 'float', 'var_names': ['a', 'b'], 'raw_var_types': ['float', 'float'], 'simple_var_types': ['float', 'float']})
        self.assertEqual(func_list[2], {'func_name': 'isPos', 'raw_return_type': 'bool', 'simple_return_type': 'bool', 'var_names': ['x'], 'raw_var_types': ['bool'], 'simple_var_types': ['bool']})
        self.assertEqual(func_list[3], {'func_name': 'three', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})
        self.assertEqual(func_list[4], {'func_name': 'nothing', 'raw_return_type': 'void', 'simple_return_type': 'void', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})
        self.assertEqual(func_list[5], {'func_name': 'main', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})

    def test_medium_file(self):
        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "mediumFunc.cpp"), None, lambda type: True)

        self.assertEqual(func_list[0], {'func_name': 'add', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': ['a', 'b'], 'raw_var_types': ['float', 'int'], 'simple_var_types': ['float', 'int']})
        self.assertEqual(func_list[1], {'func_name': 'mult', 'raw_return_type': 'float', 'simple_return_type': 'float', 'var_names': ['a', 'b', 'signal'], 'raw_var_types': ['int', 'float', 'bool'], 'simple_var_types': ['int', 'float', 'bool']})
        self.assertEqual(func_list[2], {'func_name': 'toUp', 'raw_return_type': 'std::string', 'simple_return_type': 'std::string', 'var_names': ['s'], 'raw_var_types': ['std::string'], 'simple_var_types': ['std::string']})
        self.assertEqual(func_list[3], {'func_name': 'fat', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': ['curr', 'at'], 'raw_var_types': ['int', 'int'], 'simple_var_types': ['int', 'int']})
        self.assertEqual(func_list[4], {'func_name': 'main', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})


    def test_hard_file(self):
        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "hardFunc.cpp"), None, lambda type: True)

        self.assertEqual(func_list[0], {'func_name': 'add', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': ['a'], 'raw_var_types': ['int'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[1], {'func_name': 'main', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})
        self.assertEqual(func_list[2], {'func_name': 'bubbleSort', 'raw_return_type': 'vector<int>', 'simple_return_type': 'vector<int>', 'var_names': ['v'], 'raw_var_types': ['vector<int>'], 'simple_var_types': ['vector<int>']})
        self.assertEqual(func_list[3], {'func_name': 'sizeOfMap', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': ['mp'], 'raw_var_types': ['map<int, bool>'], 'simple_var_types': ['map<int, bool>']})
        self.assertEqual(func_list[4], {'func_name': 'keys', 'raw_return_type': 'vector<int>', 'simple_return_type': 'vector<int>', 'var_names': ['mp'], 'raw_var_types': ['map<int, int>'], 'simple_var_types': ['map<int, int>']})
        self.assertEqual(func_list[5], {'func_name': 'goCount', 'raw_return_type': 'map<float, int>', 'simple_return_type': 'map<float, int>', 'var_names': ['v', 'signal'], 'raw_var_types': ['vector<float>', 'bool'], 'simple_var_types': ['vector<float>', 'bool']})


    def test_convoluted_file(self):
        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "convolutedFunc.cpp"), None, lambda type: True)

        self.assertEqual(func_list[0], {'func_name': 'matrix', 'raw_return_type': 'vector<vector<int> >', 'simple_return_type': 'vector<vector<int> >', 'var_names': ['n'], 'raw_var_types': ['int'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[1], {'func_name': 'nonsense', 'raw_return_type': 'map<map<int, vector<bool> >, vector<float> >', 'simple_return_type': 'map<map<int, vector<bool> >, vector<float> >', 'var_names': ['n'], 'raw_var_types': ['int'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[2], {'func_name': 'vectorLine', 'raw_return_type': 'vector<vector<vector<vector<float> > > >', 'simple_return_type': 'vector<vector<vector<vector<float> > > >', 'var_names': ['mp'], 'raw_var_types': ['map<bool, int>'], 'simple_var_types': ['map<bool, int>']})
        self.assertEqual(func_list[3], {'func_name': 'countVector', 'raw_return_type': 'map<int, int>', 'simple_return_type': 'map<int, int>', 'var_names': ['v'], 'raw_var_types': ['vector<vector<int> >'], 'simple_var_types': ['vector<vector<int> >']})
        self.assertEqual(func_list[4], {'func_name': 'main', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})

    def test_mix_file(self):
        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "mixFunc.cpp"), None, lambda type: True)

        self.assertEqual(func_list[0], {'func_name': 'nonsense', 'raw_return_type': 'vector<map<int, float> > *', 'simple_return_type': 'vector<map<int, float> >', 'var_names': ['v', 'mp'], 'raw_var_types': ['vector<int> &', 'map<bool, bool> *'], 'simple_var_types': ['vector<int>', 'map<bool, bool>']})
        self.assertEqual(func_list[1], {'func_name': 'address', 'raw_return_type': 'vector<int> &', 'simple_return_type': 'vector<int>', 'var_names': ['v'], 'raw_var_types': ['vector<int> &'], 'simple_var_types': ['vector<int>']})
        self.assertEqual(func_list[2], {'func_name': 'even', 'raw_return_type': 'map<int, vector<bool> > **', 'simple_return_type': 'map<int, vector<bool> >', 'var_names': ['n'], 'raw_var_types': ['int'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[3], {'func_name': 'dereference', 'raw_return_type': 'int **********', 'simple_return_type': 'int', 'var_names': ['ref'], 'raw_var_types': ['int ***********'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[4], {'func_name': 'constDereference', 'raw_return_type': 'const int **********', 'simple_return_type': 'int', 'var_names': ['ref'], 'raw_var_types': ['const int ***********'], 'simple_var_types': ['int']})
        self.assertEqual(func_list[5], {'func_name': 'main', 'raw_return_type': 'int', 'simple_return_type': 'int', 'var_names': [], 'raw_var_types': [], 'simple_var_types': []})

    def test_class_file_unsupported(self):
        called_count = 0

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(func, line):
            nonlocal called_count
            called_count += 1
            self.assertTrue([func, line] in [['operator+', 15], ['sum', 22], ['go', 26], ['main', 34]])

        # ----------------------------------------------------------------------

        func_list = CppToJson.ObtainFunctions(os.path.join(_script_dir, "classFunc.cpp"), onUnsupportedFunc, lambda type: False)

        self.assertEqual(called_count, 4)

        self.assertEqual(func_list, [])


if __name__ == '__main__':
    unittest.main()
