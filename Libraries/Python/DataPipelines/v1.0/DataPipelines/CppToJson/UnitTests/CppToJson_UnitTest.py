'''Unit test for CppToJson.py
'''
import sys
import json
import unittest
import textwrap

from DataPipelines.CppToJson import CppToJson

class FuncTest(unittest.TestCase):

    def test_add_func(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            std::int32_t add(std::int32_t a, std::int32_t b){
                return a+b;
            }
            std::int32_t main(){
                return 0;
            }
        ''')

        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 5)
        self.assertEqual(func_list[1]['declaration_line'], 5)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)


    def test_vector_func(self):
        s = textwrap.dedent('''\
            #include <vector>
            #include <cstdint>
            std::vector<std::int32_t> counting(std::vector<float> v, float x){
                std::vector<std::int32_t>ret;
                for(std::int32_t i = 0; i < v.size(); i++){
                    if(v[i]==x)
                        ret.push_back(i);
                }
                return ret;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<std::int32_t>')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<std::int32_t>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 3)
        self.assertEqual(func_list[0]['declaration_line'], 3)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], 11)

        self.assertEqual(struct_list, [])
        # TODO: include list length diverges between OS
        # self.assertEqual(len(include_list), 2)


    def test_vector_using_std_func(self):
        s = textwrap.dedent('''\
            #include <vector>
            #include <cstdint>
            using namespace std;
            std::vector<std::int32_t> counting(std::vector<float> v, float x){
                std::vector<std::int32_t>ret;for(std::int32_t i = 0; i < v.size(); i++){
                    if(v[i]==x)
                        ret.push_back(i);
                }
                return ret;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<std::int32_t>')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<std::int32_t>')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<float>', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 4)
        self.assertEqual(func_list[0]['declaration_line'], 4)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], 11)

        self.assertEqual(struct_list, [])
        # TODO: include list length diverges between OS
        # self.assertEqual(len(include_list), 2)

    def test_vector_map(self):
        s = textwrap.dedent('''\
            #include <vector>
            #include <map>
            using namespace std;
            std::vector<std::vector<std::int32_t>> counting(std::vector<map<float,std::int32_t>> v, float x){
                std::vector<std::vector<std::int32_t>>ret;
                for(std::int32_t i=0; i<v.size(); i++){
                    if(v[i][x])ret.push_back({1, 2, 3, 4});
                }
                return ret;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'counting')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<std::vector<std::int32_t> >')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<std::vector<std::int32_t> >')
        self.assertEqual(func_list[0]['var_names'], ['v', 'x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<map<float, std::int32_t> >', 'float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<map<float, std::int32_t> >', 'float'])
        self.assertEqual(func_list[0]['definition_line'], 4)
        self.assertEqual(func_list[0]['declaration_line'], 4)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], 11)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)

    def test_many_arguments(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            std::int32_t two(std::int32_t a, std::int32_t b, std::int32_t c, std::int32_t d, std::int32_t e, std::int32_t f, std::int32_t g, std::int32_t h, std::int32_t i, std::int32_t j,
                std::int32_t k, std::int32_t l, std::int32_t m, std::int32_t n, std::int32_t o, std::int32_t p, std::int32_t q, std::int32_t r, std::int32_t s, std::int32_t t, std::int32_t u,
                std::int32_t v, std::int32_t w, std::int32_t x, std::int32_t y, std::int32_t z){

                return 2;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'two')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 8)
        self.assertEqual(func_list[1]['declaration_line'], 8)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_many_arguments_ref(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            std::int32_t two(std::int32_t &&a, std::int32_t &&b, std::int32_t &&c, std::int32_t &&d, std::int32_t &&e, std::int32_t &&f, std::int32_t &&g, std::int32_t &&h,
                std::int32_t &&i, std::int32_t &&j, std::int32_t &&k, std::int32_t &&l, std::int32_t &&m, std::int32_t &&n, std::int32_t &&o, std::int32_t &&p, std::int32_t &&q,
                std::int32_t &&r, std::int32_t &&s, std::int32_t &&t, std::int32_t &&u, std::int32_t &&v, std::int32_t &&w, std::int32_t &&x, std::int32_t &&y, std::int32_t &&z){

                return 2;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'two')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&', 'std::int32_t &&'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 8)
        self.assertEqual(func_list[1]['declaration_line'], 8)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_const_ret(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            const float square(float x){
                const float ret = x*x;
                return ret;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'square')
        self.assertEqual(func_list[0]['raw_return_type'], 'const float')
        self.assertEqual(func_list[0]['simple_return_type'], 'float')
        self.assertEqual(func_list[0]['var_names'], ['x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['float'])
        self.assertEqual(func_list[0]['simple_var_types'], ['float'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 6)
        self.assertEqual(func_list[1]['declaration_line'], 6)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_const_arg(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            float sum(const float x, const std::int32_t y){
                return x+y;
            }
            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'sum')
        self.assertEqual(func_list[0]['raw_return_type'], 'float')
        self.assertEqual(func_list[0]['simple_return_type'], 'float')
        self.assertEqual(func_list[0]['var_names'], ['x', 'y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['const float', 'const std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['float', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 2)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 5)
        self.assertEqual(func_list[1]['declaration_line'], 5)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_map_vec_ref(self):
        s = textwrap.dedent( '''\
            #include <vector>
            #include <map>

            using namespace std;

            std::vector<map<std::int32_t, float>> * nonsense(std::vector<std::int32_t> &v, map<bool, bool>* mp){
                std::vector<map<std::int32_t, float>> *ret = new std::vector<map<std::int32_t, float>>;
                return ret;
            }

            std::int32_t main(){
                return 0;
            }
        ''')
        
        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'nonsense')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::vector<map<std::int32_t, float> > *')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::vector<map<std::int32_t, float> > *')
        self.assertEqual(func_list[0]['var_names'], ['v', 'mp'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::vector<std::int32_t> &', 'map<bool, bool> *'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::vector<std::int32_t>', 'map<bool, bool> *'])
        self.assertEqual(func_list[0]['definition_line'], 6)
        self.assertEqual(func_list[0]['declaration_line'], 6)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 11)
        self.assertEqual(func_list[1]['declaration_line'], 11)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)

    def test_struct_unsupported(self):
        times_called = 0

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>

            struct x{
                std::int32_t a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x go(std::int32_t y){
                x ret = x();
                return ret;
            }

            std::int32_t main(){
                return 0;
            }
        ''')
        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The struct x is not supported:
                \t- Invalid var a of type std::int32_t.
                \t- Invalid var b of type std::int32_t.
                """), None, 5],
                [textwrap.dedent("""\
                The function go is not supported:
                \t- Invalid argument y of type std::int32_t.
                \t- Invalid return type x.
                """), None, 11],
                [textwrap.dedent("""\
                The function main is not supported:
                \t- Invalid return type std::int32_t.
                """), None, 16]
            ]

            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)


        self.assertEqual(times_called, 3)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 3)

    def test_struct_supported(self):

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>

            struct x{
                std::int32_t a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x go(std::int32_t y){
                x ret = x();
                return ret;
            }

            std::int32_t main(){
                return 0;
            }

            struct y{
                std::int32_t a, b;
                y(y &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };
        ''')

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 11)
        self.assertEqual(func_list[0]['declaration_line'], 11)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 16)
        self.assertEqual(func_list[1]['declaration_line'], 16)

        self.assertEqual(struct_list[0]['name'], 'x')
        self.assertEqual(struct_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(struct_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['definition_line'], 5)

        self.assertEqual(len(struct_list[0]['constructor_list']), 2)

        self.assertEqual(struct_list[0]['constructor_list'][0]['var_names'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['raw_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['simple_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['definition_line'], 7)

        self.assertEqual(struct_list[0]['constructor_list'][1]['var_names'], ['other'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['raw_var_types'], ['x &&'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['simple_var_types'], ['x'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['definition_line'], 8)

        self.assertEqual(len(include_list), 3)


    def test_class_unsupported(self):
        times_called = 0

        s = textwrap.dedent('''\
            #include <cstdint>
            class Point{
                public:
                    std::int32_t x, y;
                    Point() {}
                    Point(std::int32_t a, std::int32_t b){
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

            std::int32_t main(){
                return 0;
            }
        ''')
        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function operator+ is not supported:
                \t- Invalid argument a of type Point.
                \t- Invalid argument b of type Point.
                \t- Invalid return type Point.
                """), None, 12],
                [textwrap.dedent("""\
                The function main is not supported:
                \t- Invalid return type std::int32_t.
                """), None, 19]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type, verifyStruct: False)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 2)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_declaration(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            std::int32_t add(std::int32_t a, std::int32_t b);

            std::int32_t add(std::int32_t a, std::int32_t b){
                return a+b;
            }
            std::int32_t main(){
                return 0;
            }
        ''')

        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 4)
        self.assertEqual(func_list[0]['declaration_line'], 2)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 7)
        self.assertEqual(func_list[1]['declaration_line'], 7)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_namespace_declaration(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            namespace DataPipelines {
                namespace Arithmetic {
                    void thisGuy(std::int32_t *x);
                }
            }

            void DataPipelines::Arithmetic::thisGuy(std::int32_t *x){
                (*x)++;
            }

            std::int32_t main(){
                return 0;
            }
        ''')

        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'DataPipelines::Arithmetic::thisGuy')
        self.assertEqual(func_list[0]['raw_return_type'], 'void')
        self.assertEqual(func_list[0]['simple_return_type'], 'void')
        self.assertEqual(func_list[0]['var_names'], ['x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t *'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t *'])
        self.assertEqual(func_list[0]['definition_line'], 8)
        self.assertEqual(func_list[0]['declaration_line'], 4)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 12)
        self.assertEqual(func_list[1]['declaration_line'], 12)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)

    def test_namespace_func(self):
        s = textwrap.dedent('''\
            #include <stdint.h>
            #include <cstdint>

            /* Defined in enclosed namespace */
            namespace DataPipelines {
                namespace Arithmetic {
                    std::int64_t Add(const std::int64_t a, const std::int64_t b) { return a + b; }
                }
            }
        ''')

        result = CppToJson.ObtainFunctions(s, None, lambda type, verifyStruct: True)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'DataPipelines::Arithmetic::Add')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int64_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int64_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['const std::int64_t', 'const std::int64_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int64_t', 'std::int64_t'])
        self.assertEqual(func_list[0]['definition_line'], 7)
        self.assertEqual(func_list[0]['declaration_line'], 7)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)

    def test_namespace_unsupported(self):
        times_called = 0

        s = textwrap.dedent('''\
            #include <stdint.h>
            #include <cstdint>

            /* Defined in enclosed namespace */
            namespace DataPipelines {
                namespace Arithmetic {
                    struct MyStruct {
                        std::int64_t a;
                        std::int64_t b;
                        MyStruct(std::int64_t _a = 0, std::int64_t _b = 0) : a(_a), b(_b) {}
                    };
                    MyStruct Add(const MyStruct& s1, const MyStruct& s2) {
                        return MyStruct(s1.a + s2.a, s1.b + s2.b);
                    }
                }
            }
        ''')


        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The struct DataPipelines::Arithmetic::MyStruct is not supported:
                \t- Invalid var a of type std::int64_t.
                \t- Invalid var b of type std::int64_t.
                \t- Invalid type std::int64_t on constructor argument.
                \t- Invalid type std::int64_t on constructor argument.
                \t- Struct doesn't have a move constructor.
                """), None, 7],
                [textwrap.dedent("""\
                The function DataPipelines::Arithmetic::Add is not supported:
                \t- Invalid argument s1 of type DataPipelines::Arithmetic::MyStruct.
                \t- Invalid argument s2 of type DataPipelines::Arithmetic::MyStruct.
                \t- Invalid return type DataPipelines::Arithmetic::MyStruct.
                """), None, 12]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 2)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)

    def test_func_unsupported(self):
        times_called = 0

        s = textwrap.dedent('''\
            #include <utility>
            #include <cstdint>
            struct x{
                bool a, b;
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            bool go(x ya){
                return 2;
            }
            
            int main(){
                return 0;
            }
        ''')


        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function go is not supported:
                \t- Invalid argument ya of type x.
                """), None, 8]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "bool" or var_type == "int":
               return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 1)
        
        self.assertEqual(func_list[0]['name'], 'main')
        self.assertEqual(func_list[0]['raw_return_type'], 'int')
        self.assertEqual(func_list[0]['simple_return_type'], 'int')
        self.assertEqual(func_list[0]['var_names'], [])
        self.assertEqual(func_list[0]['raw_var_types'], [])
        self.assertEqual(func_list[0]['simple_var_types'], [])
        self.assertEqual(func_list[0]['definition_line'], 12)
        self.assertEqual(func_list[0]['declaration_line'], 12)
        
        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)

    def test_func_supported(self):

        s = textwrap.dedent('''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>
            
            struct x{
                bool a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };

            x go(bool y){
                x ret = x();
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
        def Policy(var_type, verifyStruct):
            if var_type == "bool" or var_type == "int" or verifyStruct(var_type):
               return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['bool'])
        self.assertEqual(func_list[0]['simple_var_types'], ['bool'])
        self.assertEqual(func_list[0]['definition_line'], 11)
        self.assertEqual(func_list[0]['declaration_line'], 11)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'int')
        self.assertEqual(func_list[1]['simple_return_type'], 'int')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 16)
        self.assertEqual(func_list[1]['declaration_line'], 16)

        self.assertEqual(struct_list[0]['name'], 'x')
        self.assertEqual(struct_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(struct_list[0]['raw_var_types'], ['bool', 'bool'])
        self.assertEqual(struct_list[0]['simple_var_types'], ['bool', 'bool'])
        self.assertEqual(struct_list[0]['definition_line'], 5)

        self.assertEqual(len(struct_list[0]['constructor_list']), 2)

        self.assertEqual(struct_list[0]['constructor_list'][0]['var_names'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['raw_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['simple_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['definition_line'], 7)

        self.assertEqual(struct_list[0]['constructor_list'][1]['var_names'], ['other'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['raw_var_types'], ['x &&'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['simple_var_types'], ['x'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['definition_line'], 8)   

        self.assertEqual(len(include_list), 3)

    def test_warning_1(self):
        times_called = 0

        s = textwrap.dedent('''\
            int main(){
                return 0;
            }
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function main is not supported:
                \t- Invalid return type int.
                """), None, 1]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type, verifyStruct: False)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 1)
        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_warning_2(self):

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            self.assertTrue(False)

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, lambda type, verifyStruct: False)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_warning_3(self):
        times_called = 0

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
            struct R{
                int x;
            };
            R func(){
                R y;
                return y;
            }
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function func is not supported:
                \t- Invalid return type R.
                """), None, 7],
                [textwrap.dedent("""\
                The struct R is not supported:
                \t- Invalid var x of type int.
                \t- Struct doesn't have a move constructor.
                """), None, 4]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 2)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_warning_4(self):
        times_called = 0

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
            struct R{
                int x;
            };
            R func(){
                R y;
                return y;
            }

            R func2(){
                R y;
                return y;
            }
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function func is not supported:
                \t- Invalid return type R.
                """), None, 7],
                [textwrap.dedent("""\
                The struct R is not supported:
                \t- Invalid var x of type int.
                \t- Struct doesn't have a move constructor.
                """), None, 4],
                [textwrap.dedent("""\
                The function func2 is not supported:
                \t- Invalid return type R.
                """), None, 12]
            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 3)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])


    def test_warning_5(self):
        times_called = 0

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
            struct R{
                int x;
            };
            R func(){
                R y;
                return y;
            }

            R func2(){
                R y;
                return y;
            }

            struct R2: public R{

            };
            
            R2 func3(){
                R2 y;
                return y;
            }

        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1
    
            unsupported_list = [
                [textwrap.dedent("""\
                The function func is not supported:
                \t- Invalid return type R.
                """), None, 7],
                [textwrap.dedent("""\
                The struct R is not supported:
                \t- Invalid var x of type int.
                \t- Struct doesn't have a move constructor.
                """), None, 4],
                [textwrap.dedent("""\
                The function func2 is not supported:
                \t- Invalid return type R.
                """), None, 12],
                [textwrap.dedent("""\
                The struct R2 is not supported:
                \t- Invalid base struct R.
                \t- Struct doesn't have a move constructor.
                """), None, 17],
                [textwrap.dedent("""\
                The function func3 is not supported:
                \t- Invalid return type R2.
                """), None, 21],

            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 5)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_warning_6(self):
        times_called = 0

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
            struct R{
                int x;
            };
            R func(){
                R y;
                return y;
            }

            R func2(){
                R y;
                return y;
            }

            struct R2: public R{

            };
            
            R2 func3(){
                R2 y;
                return y;
            }

            struct R3{
                R2 r2;
            };
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The function func is not supported:
                \t- Invalid return type R.
                """), None, 7],
                [textwrap.dedent("""\
                The struct R is not supported:
                \t- Invalid var x of type int.
                \t- Struct doesn't have a move constructor.
                """), None, 4],
                [textwrap.dedent("""\
                The function func2 is not supported:
                \t- Invalid return type R.
                """), None, 12],
                [textwrap.dedent("""\
                The struct R2 is not supported:
                \t- Invalid base struct R.
                \t- Struct doesn't have a move constructor.
                """), None, 17],
                [textwrap.dedent("""\
                The function func3 is not supported:
                \t- Invalid return type R2.
                """), None, 21],

            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 5)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_warning_7(self):
        times_called = 0

        s = textwrap.dedent('''\
            struct NeverUsed{
                int x;
            };
            struct R{
                int x;
            };
            R func(){
                R y;
                return y;
            }

            R func2(){
                R y;
                return y;
            }

            struct R2: public R{

            };
            
            R2 func3(){
                R2 y;
                return y;
            }

            struct R3{
                R2 r2;
            };

            R3 func4(){
                R3 y;
                return y;
            };
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1
            
            unsupported_list = [
                [textwrap.dedent("""\
                The function func is not supported:
                \t- Invalid return type R.
                """), None, 7],
                [textwrap.dedent("""\
                The struct R is not supported:
                \t- Invalid var x of type int.
                \t- Struct doesn't have a move constructor.
                """), None, 4],
                [textwrap.dedent("""\
                The function func2 is not supported:
                \t- Invalid return type R.
                """), None, 12],
                [textwrap.dedent("""\
                The struct R2 is not supported:
                \t- Invalid base struct R.
                \t- Struct doesn't have a move constructor.
                """), None, 17],
                [textwrap.dedent("""\
                The function func3 is not supported:
                \t- Invalid return type R2.
                """), None, 21],
                [textwrap.dedent("""\
                The struct R3 is not supported:
                \t- Invalid var r2 of type R2.
                \t- Struct doesn't have a move constructor.
                """), None, 26],
                [textwrap.dedent("""\
                The function func4 is not supported:
                \t- Invalid return type R3.
                """), None, 30]

            ]
            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------
        
        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(times_called, 7)

        self.assertEqual(func_list, [])
        self.assertEqual(struct_list, [])
        self.assertEqual(include_list, [])

    def test_alias(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            using int_t = std::int32_t;
            typedef std::int32_t i_t;

            int_t add(i_t a, int_t b){
                return a+b;
            }
            i_t main(){
                return 0;
            }
        ''')

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'add')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 5)
        self.assertEqual(func_list[0]['declaration_line'], 5)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 8)
        self.assertEqual(func_list[1]['declaration_line'], 8)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 1)
    
    def test_alias_namespace(self):
        s = textwrap.dedent('''\
            #include <cstdint>
            #include <utility>

            namespace DataPipelines {
                namespace Arithmetic {
                    struct R{
                        std::int32_t a;
                        R(){}
                        R(R && other): a(std::move(other.a)){}
                    };
                    R thisGuy(std::int32_t x);
                }
            }
            using Rx = DataPipelines::Arithmetic::R;

            Rx DataPipelines::Arithmetic::thisGuy(std::int32_t x){
                Rx y;
                return y;
            }

            std::int32_t main(){
                return 0;
            }
        ''')

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'DataPipelines::Arithmetic::thisGuy')
        self.assertEqual(func_list[0]['raw_return_type'], 'DataPipelines::Arithmetic::R')
        self.assertEqual(func_list[0]['simple_return_type'], 'DataPipelines::Arithmetic::R')
        self.assertEqual(func_list[0]['var_names'], ['x'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 16)
        self.assertEqual(func_list[0]['declaration_line'], 11)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 21)
        self.assertEqual(func_list[1]['declaration_line'], 21)

        self.assertEqual(struct_list[0]['name'], 'DataPipelines::Arithmetic::R')
        self.assertEqual(struct_list[0]['var_names'], ['a'])
        self.assertEqual(struct_list[0]['raw_var_types'], ['std::int32_t'])
        self.assertEqual(struct_list[0]['simple_var_types'], ['std::int32_t'])
        self.assertEqual(struct_list[0]['definition_line'], 6)
        self.assertEqual(struct_list[0]['base_structs'], [])

        self.assertEqual(len(struct_list[0]['constructor_list']), 2)

        self.assertEqual(struct_list[0]['constructor_list'][0]['var_names'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['raw_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['simple_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['definition_line'], 8)

        self.assertEqual(struct_list[0]['constructor_list'][1]['var_names'], ['other'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['raw_var_types'], ['DataPipelines::Arithmetic::R &&'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['simple_var_types'], ['DataPipelines::Arithmetic::R'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['definition_line'], 9)

        self.assertEqual(len(include_list), 2)

    def test_copy_constructor(self):
        times_called = 0

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>

            struct x{
                std::int32_t a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
                // Copy constructor
                x(x& other){}
            };

            x go(std::int32_t y){
                x ret = x();
                return ret;
            }

            std::int32_t main(){
                return 0;
            }

            struct y{
                std::int32_t a, b;
                y(y &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };
        ''')

        # ----------------------------------------------------------------------
        def onUnsupportedFunc(error_desc, filename, line):
            nonlocal times_called
            times_called = times_called + 1

            unsupported_list = [
                [textwrap.dedent("""\
                The struct x is not supported:
                \t- Struct has a copy constructor.
                """), None, 5],
                [textwrap.dedent("""\
                The function go is not supported:
                \t- Invalid return type x.
                """), None, 13]
            ]

            self.assertTrue([error_desc, filename, line] in unsupported_list)

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, onUnsupportedFunc, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'main')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], [])
        self.assertEqual(func_list[0]['raw_var_types'], [])
        self.assertEqual(func_list[0]['simple_var_types'], [])
        self.assertEqual(func_list[0]['definition_line'], 18)
        self.assertEqual(func_list[0]['declaration_line'], 18)

        self.assertEqual(len(include_list), 3)

        self.assertEqual(times_called, 2)

    def test_copy_constructor_deleted(self):

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>

            struct x{
                std::int32_t a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
                // Copy constructor
                x(x& other)=delete;
            };

            x go(std::int32_t y){
                x ret = x();
                return ret;
            }

            std::int32_t main(){
                return 0;
            }

            struct y{
                std::int32_t a, b;
                y(y &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };
        ''')

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 13)
        self.assertEqual(func_list[0]['declaration_line'], 13)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 18)
        self.assertEqual(func_list[1]['declaration_line'], 18)

        self.assertEqual(struct_list[0]['name'], 'x')
        self.assertEqual(struct_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(struct_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['definition_line'], 5)

        self.assertEqual(len(struct_list[0]['constructor_list']), 2)

        self.assertEqual(struct_list[0]['constructor_list'][0]['var_names'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['raw_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['simple_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['definition_line'], 7)

        self.assertEqual(struct_list[0]['constructor_list'][1]['var_names'], ['other'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['raw_var_types'], ['x &&'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['simple_var_types'], ['x'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['definition_line'], 8)

        self.assertEqual(len(include_list), 3)

    def test_operator_equal(self):

        s = textwrap.dedent( '''\
            #include <utility>
            #include <cstdio>
            #include <cstdint>

            struct x{
                std::int32_t a, b;
                x(){}
                x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
                x& operator=(x&& y){
                    return *this;
                }
            };

            x go(std::int32_t y){
                x ret = x();
                return ret;
            }

            std::int32_t main(){
                return 0;
            }

            struct y{
                std::int32_t a, b;
                y(y &&other): a(std::move(other.a)), b(std::move(other.b)){}
            };
        ''')

        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'go')
        self.assertEqual(func_list[0]['raw_return_type'], 'x')
        self.assertEqual(func_list[0]['simple_return_type'], 'x')
        self.assertEqual(func_list[0]['var_names'], ['y'])
        self.assertEqual(func_list[0]['raw_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['simple_var_types'], ['std::int32_t'])
        self.assertEqual(func_list[0]['definition_line'], 14)
        self.assertEqual(func_list[0]['declaration_line'], 14)

        self.assertEqual(func_list[1]['name'], 'main')
        self.assertEqual(func_list[1]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 19)
        self.assertEqual(func_list[1]['declaration_line'], 19)

        self.assertEqual(struct_list[0]['name'], 'x')
        self.assertEqual(struct_list[0]['var_names'], ['a', 'b'])
        self.assertEqual(struct_list[0]['raw_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['simple_var_types'], ['std::int32_t', 'std::int32_t'])
        self.assertEqual(struct_list[0]['definition_line'], 5)

        self.assertEqual(len(struct_list[0]['constructor_list']), 2)

        self.assertEqual(struct_list[0]['constructor_list'][0]['var_names'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['raw_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['simple_var_types'], [])
        self.assertEqual(struct_list[0]['constructor_list'][0]['definition_line'], 7)

        self.assertEqual(struct_list[0]['constructor_list'][1]['var_names'], ['other'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['raw_var_types'], ['x &&'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['simple_var_types'], ['x'])
        self.assertEqual(struct_list[0]['constructor_list'][1]['definition_line'], 8)

        self.assertEqual(len(include_list), 3)

    def test_namespace_alias(self):
        s = textwrap.dedent('''\
            #include <stdint.h>
            #include <cstdint>

            /* Defined in enclosed namespace */
            namespace Foo{
                using Bar = std::int32_t;
                Bar func1(){
                    return 2;
                }
            }
            namespace Baz{
                using Bar = bool;
                Bar func2(){
                    return false;
                }
            }

            namespace Foo{
                Bar func3(){
                    return 2;
                }
            }
        ''')
        # ----------------------------------------------------------------------
        def Policy(var_type, verifyStruct):
            if var_type == "std::int32_t" or var_type == "bool" or verifyStruct(var_type):
                return True
            return False

        # ----------------------------------------------------------------------

        result = CppToJson.ObtainFunctions(s, None, Policy)
        func_list = self._GetFuncList(result)
        struct_list = self._GetStructList(result)
        include_list = self._GetIncludeList(result)

        self.assertEqual(func_list[0]['name'], 'Foo::func1')
        self.assertEqual(func_list[0]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[0]['var_names'], [])
        self.assertEqual(func_list[0]['raw_var_types'], [])
        self.assertEqual(func_list[0]['simple_var_types'], [])
        self.assertEqual(func_list[0]['definition_line'], 7)
        self.assertEqual(func_list[0]['declaration_line'], 7)

        self.assertEqual(func_list[1]['name'], 'Baz::func2')
        self.assertEqual(func_list[1]['raw_return_type'], 'bool')
        self.assertEqual(func_list[1]['simple_return_type'], 'bool')
        self.assertEqual(func_list[1]['var_names'], [])
        self.assertEqual(func_list[1]['raw_var_types'], [])
        self.assertEqual(func_list[1]['simple_var_types'], [])
        self.assertEqual(func_list[1]['definition_line'], 13)
        self.assertEqual(func_list[1]['declaration_line'], 13)

        self.assertEqual(func_list[2]['name'], 'Foo::func3')
        self.assertEqual(func_list[2]['raw_return_type'], 'std::int32_t')
        self.assertEqual(func_list[2]['simple_return_type'], 'std::int32_t')
        self.assertEqual(func_list[2]['var_names'], [])
        self.assertEqual(func_list[2]['raw_var_types'], [])
        self.assertEqual(func_list[2]['simple_var_types'], [])
        self.assertEqual(func_list[2]['definition_line'], 19)
        self.assertEqual(func_list[2]['declaration_line'], 19)

        self.assertEqual(struct_list, [])
        self.assertEqual(len(include_list), 2)


    def _GetFuncList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['function_list']
    def _GetStructList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['struct_list']

    def _GetIncludeList(self, results):
        self.assertEqual(len(results), 1)
        self.assertEqual(None, list(results.keys())[0])

        return results[None]['include_list']

if __name__ == '__main__':
    unittest.main()
