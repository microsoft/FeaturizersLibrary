'''Unit test for CppToJson.py
'''
import sys
import json
import unittest
import textwrap

from DataPipelines import CppToJson

class FuncTest(unittest.TestCase):

    def test_add_func(self):
        s = textwrap.dedent('''\
            int add(int a, int b){
                return a+b;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int', 'int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int', 'int'])
        self.assertEqual(func_list[0]['definition_line'], 1)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 4)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])


    def test_vector_func(self):
        s = textwrap.dedent('''\
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
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<int>')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<int>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 10)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 1)


    def test_vector_using_std_func(self):
        s = textwrap.dedent('''\
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
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'vector<int>')
        self.assertEqual(func_list[0]['simple_return_type'], 'vector<int>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['vector<float>', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 3)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 10)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 1)

    def test_vector_map(self):
        s = textwrap.dedent('''\
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
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'vector<vector<int> >')
        self.assertEqual(func_list[0]['simple_return_type'], 'vector<vector<int> >')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['vector<map<float, int> >', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['vector<map<float, int> >', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 4)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 2)

    def test_many_arguments(self):
        s = textwrap.dedent('''\
            int two(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
                int k, int l, int m, int n, int o, int p, int q, int r, int s, int t, int u,
                int v, int w, int x, int y, int z){

                return 2;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'two')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int'])
        self.assertEqual(func_list[0]['definition_line'], 1)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 7)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_many_arguments_ref(self):
        s = textwrap.dedent('''\
            int two(int **a, int **b, int **c, int **d, int **e, int **f, int **g, int **h,
                int **i, int **j, int **k, int **l, int **m, int **n, int **o, int **p, int **q,
                int **r, int **s, int **t, int **u, int **v, int **w, int **x, int **y, int **z){

                return 2;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'two')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **', 'int **'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int', 'int'])
        self.assertEqual(func_list[0]['definition_line'], 1)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 7)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_const_ret(self):
        s = textwrap.dedent('''\
            const float square(float x){
                const float ret = x*x;
                return ret;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'square')
        self.assertEqual(func_list[0]['raw_return_type'], 'const float')
        self.assertEqual(func_list[0]['simple_return_type'], 'float')
        self.assertEqual(func_list[0]['var_names'], ['x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['float'])
        self.assertEqual(func_list[0]['definition_line'], 1)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 5)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_const_arg(self):
        s = textwrap.dedent('''\
            float sum(const float x, const int y){
                return x+y;
            }
            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'sum')
        self.assertEqual(func_list[0]['raw_return_type'], 'float')
        self.assertEqual(func_list[0]['simple_return_type'], 'float')
        self.assertEqual(func_list[0]['var_names'], ['x', 'y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['const float', 'const int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['float', 'int'])
        self.assertEqual(func_list[0]['definition_line'], 1)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 4)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_map_vec_ref(self):
        s = textwrap.dedent( '''\
            #include <vector>
            #include <map>

            using namespace std;

            vector<map<int, float>> * nonsense(vector<int> &v, map<bool, bool>* mp){
                vector<map<int, float>> *ret = new vector<map<int, float>>;
                return ret;
            }

            int main(){
                return 0;
            }
        ''')
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'nonsense')
        self.assertEqual(func_list[0]['raw_return_type'], 'vector<map<int, float> > *')
        self.assertEqual(func_list[0]['simple_return_type'], 'vector<map<int, float> >')
        self.assertEqual(func_list[0]['var_names'], ['v', 'mp'])
        self.assertEqual(func_list[0]['raw_var_types'], ['vector<int> &', 'map<bool, bool> *'])
        self.assertEqual(func_list[0]['simple_var_types'], ['vector<int>', 'map<bool, bool>'])
        self.assertEqual(func_list[0]['definition_line'], 6)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 2)

    def test_struct_unsupported(self):
        was_called = False

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>

            struct x{
                int a, b;
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x *go(int y){
                x *ret = NULL;
                return ret;
            }

            int main(){
                return 0;
            }
        ''')
        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal was_called
            was_called = True

            unsupported_list = [
                [textwrap.dedent("""\
                The struct x is not supported:
                \t- Invalid var a of type int.
                \t- Invalid var b of type int.
                """), None, 4],
                [textwrap.dedent("""\
                The function go is not supported:
                \t- Invalid argument y of type int.
                \t- Invalid return type x.
                """), None, 9],
                [textwrap.dedent("""\
                The function main is not supported:
                \t- Invalid return type int.
                """), None, 14]
            ]

            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------

        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))


        self.assertEqual(was_called, True)

        self.assertEqual(func_list, [])
        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 2)

    def test_struct_supported(self):

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>

            struct x{
                int a, b;
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x *go(int y){
                x *ret = NULL;
                return ret;
            }

            int main(){
                return 0;
            }

            struct y{
                int a, b;
                y(y &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };
        ''')

        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x *')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int'])
        self.assertEqual(func_list[0]['definition_line'], 9)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 14)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list[0]['name'], 'x')
        self.assertEqual(obj_type_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(obj_type_list[0]['raw_var_types'], ['int', 'int'])
        self.assertEqual(obj_type_list[0]['simple_var_types'], ['int', 'int'])
        self.assertEqual(obj_type_list[0]['definition_line'], 4)

        self.assertEqual(len(obj_type_list[0]['constructor_list']), 1)
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['var_names'], ['other'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['raw_var_types'], ['x &&'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['simple_var_types'], ['x'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['definition_line'], 6)

        self.assertEqual(len(include_list), 2)


    def test_class_unsupported(self):
        was_called = False

        s = textwrap.dedent('''\
            class Point{
                public:
                    int x, y;
                    Point() {}
                    Point(int a, int b){
                        x=a;
                        y=b;
                    }
            };

            Point operator+ (const Point& a, const Point& b) {
                Point ret;
                ret.x = a.x + b.x;
                ret.y = a.y + b.y;
                return ret;
            }

            int main(){
                return 0;
            }
        ''')
        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal was_called
            was_called = True

            unsupported_list = [
                [textwrap.dedent("""\
                The struct Point is not supported:
                \t- Invalid var x of type int.
                \t- Invalid var y of type int.
                \t- Invalid type int on constructor argument.
                \t- Invalid type int on constructor argument.
                \t- Struct doesn't have a move constructor.
                """), None, 1],
                [textwrap.dedent("""\
                The function operator+ is not supported:
                \t- Invalid argument a of type Point.
                \t- Invalid argument b of type Point.
                \t- Invalid return type Point.
                """), None, 11],
                [textwrap.dedent("""\
                The function main is not supported:
                \t- Invalid return type int.
                """), None, 18]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))

        self.assertEqual(was_called, True)

        self.assertEqual(func_list, [])
        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_declaration(self):
        s = textwrap.dedent('''\
            int add(int a, int b);

            int add(int a, int b){
                return a+b;
            }
            int main(){
                return 0;
            }
        ''')


        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int', 'int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int', 'int'])
        self.assertEqual(func_list[0]['definition_line'], 3)
        self.assertEqual(func_list[0]['declaration_line'], 1)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 6)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_namespace_declaration(self):
        s = textwrap.dedent('''\
            namespace DataPipelines {
                namespace Arithmetic {
                    void thisGuy(int *x);
                }
            }

            void DataPipelines::Arithmetic::thisGuy(int *x){
                (*x)++;
            }

            int main(){
                return 0;
            }
        ''')


        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'DataPipelines::Arithmetic::thisGuy')
        self.assertEqual(func_list[0]['raw_return_type'], 'void')
        self.assertEqual(func_list[0]['simple_return_type'], 'void')
        self.assertEqual(func_list[0]['var_names'], ['x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int *'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int'])
        self.assertEqual(func_list[0]['definition_line'], 7)
        self.assertEqual(func_list[0]['declaration_line'], 3)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(include_list, [])

    def test_namespace_func(self):
        s = textwrap.dedent('''\
            #include <stdint.h>

            /* Defined in enclosed namespace */
            namespace DataPipelines {
                namespace Arithmetic {
                    int64_t Add(const int64_t a, const int64_t b) { return a + b; }
                }
            }
        ''')


        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, None, lambda type: True))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, None, lambda type: True))

        self.assertEqual(func_list[0]['name'], 'DataPipelines::Arithmetic::Add')
        self.assertEqual(func_list[0]['raw_return_type'], 'int64_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'int64_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['const int64_t', 'const int64_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int64_t', 'int64_t'])
        self.assertEqual(func_list[0]['definition_line'], 6)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 1)

    def test_namespace_unsupported(self):
        was_called = False

        s = textwrap.dedent('''\
            #include <stdint.h>

            /* Defined in enclosed namespace */
            namespace DataPipelines {
                namespace Arithmetic {
                    struct MyStruct {
                        int64_t a;
                        int64_t b;
                        MyStruct(int64_t _a = 0, int64_t _b = 0) : a(_a), b(_b) {}
                    };
                    MyStruct Add(const MyStruct& s1, const MyStruct& s2) {
                        return MyStruct(s1.a + s2.a, s1.b + s2.b);
                    }
                }
            }
        ''')


        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal was_called
            was_called = True

            unsupported_list = [
                [textwrap.dedent("""\
                The struct DataPipelines::Arithmetic::MyStruct is not supported:
                \t- Invalid var a of type int64_t.
                \t- Invalid var b of type int64_t.
                \t- Invalid type int64_t on constructor argument.
                \t- Invalid type int64_t on constructor argument.
                \t- Struct doesn't have a move constructor.
                """), None, 6],
                [textwrap.dedent("""\
                The function DataPipelines::Arithmetic::Add is not supported:
                \t- Invalid argument s1 of type DataPipelines::Arithmetic::MyStruct.
                \t- Invalid argument s2 of type DataPipelines::Arithmetic::MyStruct.
                \t- Invalid return type DataPipelines::Arithmetic::MyStruct.
                """), None, 11]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type: False))

        self.assertEqual(was_called, True)

        self.assertEqual(func_list, [])
        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 1)

    def test_func_unsupported(self):
        was_called = False

        s = textwrap.dedent('''\
            #include <utility>
            struct x{
                int a, b;
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            int go(x ya){
                return 2;
            }
            
            int main(){
                return 0;
            }
        ''')


        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal was_called
            was_called = True
            
            unsupported_list = [
                [textwrap.dedent("""\
                The function go is not supported:
                \t- Invalid argument ya of type x.
                """), None, 7]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type):
            if var_type == "int":
               return True
            return False

        # ----------------------------------------------------------------------

        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))

        self.assertEqual(was_called, True)
        
        self.assertEqual(func_list[0]['name'], 'main')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], [])
        self.assertEqual(func_list[0]['raw_var_types'], [])
        self.assertEqual(func_list[0]['simple_var_types'], [])
        self.assertEqual(func_list[0]['definition_line'], 11)
        self.assertEqual(func_list[0]['declaration_line'], None)
        
        self.assertEqual(obj_type_list, [])
        self.assertEqual(len(include_list), 1)

    def test_func_supported(self):

        s = textwrap.dedent('''\
            #include <utility>
            #include <cstdio>
            
            struct x{
                int a, b;
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x *go(int y){
                x *ret = NULL;
                return ret;
            }

            int main(){
                return 0;
            }
        ''')


        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            self.assertTrue(False)

        # ----------------------------------------------------------------------
        def Policy(var_type):
            if var_type == "int":
               return True
            return False

        # ----------------------------------------------------------------------

        func_list = self._GetFuncList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))
        obj_type_list = self._GetObjList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))
        include_list = self._GetIncludeList(CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy))

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x *')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['int'])
        self.assertEqual(func_list[0]['simple_var_types'], ['int'])
        self.assertEqual(func_list[0]['definition_line'], 9)
        self.assertEqual(func_list[0]['declaration_line'], None)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 14)
        self.assertEqual(func_list[1]['declaration_line'], None)

        self.assertEqual(obj_type_list[0]['name'], 'x')
        self.assertEqual(obj_type_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(obj_type_list[0]['raw_var_types'], ['int', 'int'])
        self.assertEqual(obj_type_list[0]['simple_var_types'], ['int', 'int'])
        self.assertEqual(obj_type_list[0]['definition_line'], 4)

        self.assertEqual(len(obj_type_list[0]['constructor_list']), 1)
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['var_names'], ['other'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['raw_var_types'], ['x &&'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['simple_var_types'], ['x'])
        self.assertEqual(obj_type_list[0]['constructor_list'][0]['definition_line'], 6)

        self.assertEqual(len(include_list), 2)


    def _GetFuncList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['function_list']
    def _GetObjList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['object_type_list']

    def _GetIncludeList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['include_list']

if __name__ == '__main__':
    unittest.main()
