'''Unit test for CppToJson.py
'''
import sys
import json
import unittest
import textwrap

from DataPipelines import CppToJson

class FuncTest(unittest.TestCase):

    def test_add_func(self):
        s = textwrap.dedent('''
            int add(int a, int b){
                return a+b;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = CppToJson.ObtainFunctions(s)
        
        self.assertEqual(func_list[0]['func_name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int', 'int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int', 'int'])

        self.assertEqual(func_list[1]['func_name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        
    def test_vector_func(self):
        s = textwrap.dedent('''
            #include <vector>
            std::vector<int> counting(std::vector<float> v, float x){
                std::vector<int>ret;
                for(int i = 0; i < v.size(); i++){
                    if(v[i]==x)
                        ret.push_back(i);
                }
                return ret;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = CppToJson.ObtainFunctions(s)
        
        self.assertEqual(func_list[0]['func_name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<int>')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<int>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<float>', 'float'])

        self.assertEqual(func_list[1]['func_name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])


    def test_vector_using_std_func(self):
        s = textwrap.dedent('''
            #include <vector>
            using namespace std;
            vector<int> counting(vector<float> v, float x){
                vector<int>ret;for(int i = 0; i < v.size(); i++){
                    if(v[i]==x)
                        ret.push_back(i);
                }
                return ret;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = CppToJson.ObtainFunctions(s)

        self.assertEqual(func_list[0]['func_name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'vector<int>')
        self.assertEqual(func_list[0]['simple_return_type'], 'vector<int>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['vector<float>', 'float'])

        self.assertEqual(func_list[1]['func_name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])


    def test_vector_map(self):
        s = textwrap.dedent('''
            #include <vector>
            #include <map>
            using namespace std;
            vector<vector<int>> counting(vector<map<float,int>> v, float x){
                vector<vector<int>>ret;
                for(int i=0; i<v.size(); i++){
                    if(v[i][x])ret.push_back({1, 2, 3, 4});
                }
                return ret;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = CppToJson.ObtainFunctions(s)
        
        self.assertEqual(func_list[0]['func_name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'vector<vector<int> >')
        self.assertEqual(func_list[0]['simple_return_type'], 'vector<vector<int> >')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['vector<map<float, int> >', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['vector<map<float, int> >', 'float'])

        self.assertEqual(func_list[1]['func_name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])


if __name__ == '__main__':
    unittest.main()
