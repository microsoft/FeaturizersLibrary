# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Methods that help when creating a CS wrapper"""

import os
import textwrap

import CommonEnvironment

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------

def CreateCsFile(function, file_name, output_name, generate_header_func):
    """
    Loops through all of the functions provided and makes 1 C# file per function.
    """
    code = [
        generate_header_func("// "),
        GenerateMLNetWrapper(function, output_name)
    ]

    _FormatAsCSharpAndWriteFile(file_name, "".join(code))

    return 0

def GenerateMLNetWrapper(function, output_name):    
    """
    The starting to create the C# Files.
    It takes in a function from the function list and builds all the output based on that.
    """

    # should be fine to have constant
    required_namespaces = ["Microsoft.ML", "Microsoft.ML.Data", 
    "Microsoft.ML.Runtime","System","System.Linq","System.Runtime.InteropServices"]

    #should be fine to have constant
    namespace = "Microsoft.ML.Autogen"

    function_name = function["func_name"]
    variable_names = function["var_names"]
    variable_types = function["simple_var_types"]
    return_type = function["simple_return_type"]

    extension_class_name = "{0}ExtensionClass".format(function_name)
    estimator_class_name = "{0}Estimator".format(function_name)
    transformer_class_name = "{0}Transformer".format(function_name)
    column_class_name = "DataViewSchema.Column"

    # Build a list of tuples of the parameters
    # Format is [(val-a, col-a), (val-b, col-b)]
    # Used to derive all valid configurations of parameters
    variables_tuples = []
    for variable_name in variable_names:
        variables_tuples.append(("val-{0}".format(variable_name), "col-{0}".format(variable_name)))

    cur_combo = []
    all_combos = list(_BuildAllPossibleFunctionParameterPermutations(variables_tuples, 0, cur_combo))

    code = [
        _GenerateBeginningCode(required_namespaces, namespace),
        _GenerateExtensionsClass(extension_class_name, variable_names, variable_types, all_combos, function_name, column_class_name),
        _GenerateEstimatorClass(transformer_class_name, extension_class_name, variable_names, variable_types, estimator_class_name, return_type, function_name),
        _GenerateTransformer(transformer_class_name, extension_class_name, variable_names, variable_types, return_type, function_name, output_name),
        "\n}"
    ]
    
    return "".join(code)

def _FormatAsCSharpAndWriteFile(output_filename, code):
    """
    Does some simple C# Formatting
    """
    with open(output_filename,"w") as file:
        tabs = 0
        temp_tab = False
        for line in code.split("\n"):
            if line.strip().startswith("}"):
                tabs -= 1
            if "base(" in line:
                tabs += 1
                temp_tab = True
            if line.lstrip().startswith("=>"):
                tabs += 1
                temp_tab = True

            file.write(tabs * "    ")
            file.write(line.strip())
            file.write("\n")

            if line.strip().startswith("{"):
                tabs += 1
            if temp_tab:
                tabs -=1
                temp_tab = False
            
def _BuildAllPossibleFunctionParameterPermutations(parameters, cur_location, cur_combo):
    """
    Recursively builds a list of tuples of all the valid parameter values.
    It picks either a raw value or a column for each slot.
    Parameters is a list of tuples in the format [(val-a, col-a), (val-b, col-b)]
    It uses these to build a list of all the possible permutations our input can have.
    """
    # Ending conditions, once we are past the end of the list
    if cur_location >= len(parameters):
        # Turn the current combo into a tuple yield it and end the current recursion
        yield tuple(cur_combo)
    else:
        for value in parameters[cur_location]:
            # Append the next value to the temporary combo list
            # Recurses down, and when it returns it removes the current
            # value from the temporary combo list
            cur_combo.append(value)
            yield from _BuildAllPossibleFunctionParameterPermutations(parameters, cur_location + 1, cur_combo)
            cur_combo.pop()

def _GenerateBeginningCode(required_namespaces, namespace):
    """
    First method called to generate the c# wrapper code.
    This generates the using statements and the namespace declaration.
    """
    code = []
    for name in required_namespaces:
        code.append("using {0};\n".format(name))

    code.append("\n\n")
    code.append("namespace {0}\n{{".format(namespace))
    code.append("\n\n")

    return "".join(code)

def _GenerateExtensionsClass(extension_class_name, variable_names, variable_types, all_combos, function_name, column_class_name):
    """
    This generates the catalog extensions class and the appropriate
    extension methods.
    """
    extension_class_name = extension_class_name
    variable_names = variable_names
    variable_types = variable_types
    # Initial class declaration for the Extensions class.
    # Extension classes must be their own static class
    code = ["public static class {0}\n{{".format(extension_class_name)]
    
    # Insert Transform Parameters Class
    code.append(_GenerateParametersClass())

    # TODO: Currently its hard coded to the TransformersCatalog, we will
    # probably want to change that so our generated wrappers are 
    # separated and wont have naming conflicts
    # Use all possible variable combinations and build extention methods
    for combo in all_combos:
        code.append(_GenerateExtentionMethod(combo, variable_names,variable_types, function_name, column_class_name))
    
    code.append("\n}")

    return "".join(code)

def _GenerateExtentionMethod(combo, variable_names, variable_types, function_name, column_class_name):
    """
    Generates the catalog extensions methods to hook into the ML.NET catalogs
    """
    variable_names = variable_names
    variable_types = variable_types
    function_name = function_name
    code = [
        "\n\npublic static {function_name}Estimator {function_name}(this TransformsCatalog catalog".format(
            function_name = function_name
        )
    ]
    for index in range(len(combo)):
        if combo[index].startswith("col"):
            code.append(", {0} {1}".format(column_class_name, variable_names[index]))
        else:
            code.append(", {0} {1}".format(variable_types[index], variable_names[index]))
    # All extensions have an output column
    code.append(", string outputColumn)")
    
    # Second half of extention method
    code.append("\n=> {function_name}Estimator.Create(CatalogUtils.GetEnvironment(catalog)".format(
        function_name = function_name)
    )
    for index in range(len(combo)):
        code.append(", {0}".format(variable_names[index]))
    code.append(", outputColumn);")

    return "".join(code)

def _GenerateParametersClass():
    """
    The TransformParameter class is the class used to get the data either as a 
    raw value or from a column.
    """
    # Generate class definition and value getter
    code = textwrap.dedent(
        """
        
        public class TransformParameter<T>
        {
            private readonly T _rawValue;
            public readonly DataViewSchema.Column? Column;
            
            public T GetValue(DataViewRow row)
            {
                if (Column.HasValue)
                {
                    var column = row.Schema[Column.Value.Name];
                    var getter = row.GetGetter<T>(column);
                    T value = default;
                    getter(ref value);
                    return value;
                }
                else
                {
                    return _rawValue;
                }
            }

            public TransformParameter(T value)
            {
                _rawValue = value;
                Column = null;
            }
                
            public TransformParameter(DataViewSchema.Column column)
            {
                _rawValue = default;
                Column = column;
            }

        }""")
    return code

def _GenerateEstimatorClass(transformer_class_name, extension_class_name, variable_names, variable_types, estimator_class_name, return_type, function_name):
    """
    This generates the ML.NET C# estimator class
    """
    # Class declaration for estimator class
    code = ["\n\npublic class {0} : IEstimator<{1}>\n{{".format(estimator_class_name, transformer_class_name)]
    # TODO: again assumes all columns are strings. Will need to fix
    for variable_type, varible_name in zip(variable_types, variable_names):
        code.append("\nprivate {0}.TransformParameter<{1}>  _{2} = default;".format(extension_class_name, variable_type, varible_name))
    
    # All estimators need to have this reference
    code.extend (
        [
            "\nprivate string _outputColumn = default;",
            "\n\nprivate readonly IHost _host;",

            _GenerateGetParameterType(),
            _GenerateGetParameterClassType(function_name),
            _GenerateEstimatorCreateMethod(variable_names, estimator_class_name, function_name),
            _GenerateEstimatorConstructor(estimator_class_name, variable_types, variable_names, extension_class_name),
            _GenerateFitMethod(transformer_class_name, variable_names),
            _GenerateOutputSchema(return_type),

            #End of estimator
            "\n}"
        ]
    )

    return "".join(code)

def _GenerateEstimatorCreateMethod(variable_names, estimator_class_name, function_name):
    """
    Generates the Create method for the estimator class
    """
    #create method signature
    code = [
        "\npublic static {function_name}Estimator Create(IHostEnvironment env".format(
            function_name = function_name
        )
    ]
    for var in variable_names:
        code.append(", object {0}".format(var))

    code.append(", string outputColumn)\n{")
    
    # create parameter objects
    for var in variable_names:
        code.extend(
            [
                "\n\nvar {0}Param = new object[] {{ {0} }};".format(var),
                "\nvar {0}Type = GetParameterClassType({0});".format(var),
                "\nvar {0}Instance = Activator.CreateInstance({0}Type, {0}Param);".format(var)
            ]
        )

    # create estimator object
    code.append("\n\nvar param = new object[] { env")
    for var in variable_names:
        code.append(", {0}Instance".format(var))
    code.extend(
        [
            ", outputColumn };",
            "\nvar estimator = Activator.CreateInstance(typeof({0}), param);".format(estimator_class_name),

            # create return statement
            "\n\nreturn ({0})estimator;\n}}".format(estimator_class_name)
        ]
    )

    return "".join(code)

def _GenerateGetParameterClassType(function_name):
    """
    This class is used to get the type of the ParametersClass so that ML.NET can use
    Reflection to instantiate the correct generic object type. 
    """
    code = textwrap.dedent(
        """
        private static Type GetParameterClassType(object obj)
        {{
            var type = GetParameterType(obj);
            return typeof({function_name}ExtensionClass.TransformParameter<>).MakeGenericType(type);
        }}
        """
    ).format(
            function_name = function_name
        )
    return code

def _GenerateGetParameterType():
    """
    This class is used to get the datatype of the function so that ML.NET can use
    Reflection to instantiate the correct generic object type. 
    """
    code = textwrap.dedent(
        """
        private static Type GetParameterType(object obj)
        {
            if (obj.GetType() == typeof(DataViewSchema.Column))
            {
                return ((DataViewSchema.Column)obj).Type.RawType;
            }
            else
            {
                return obj.GetType();
            }
        } 
        """
    )
    return code
    
def _GenerateEstimatorConstructor(estimator_class_name, variable_types, variable_names, extension_class_name):
    """
    Generates the consructor for the estimator class.
    """
    code = ["\n\npublic {0}(IHostEnvironment env".format(estimator_class_name)]
    # Generate the Constructor parameters
    for variable_type, variable_name in zip(variable_types, variable_names):
        code.append(", {0}.TransformParameter<{1}> {2}".format(extension_class_name, variable_type, variable_name))
    code.extend(
        [
            ", string outputColumn",
            ")\n{"
        ]
    )
    
    # Generate assigning the values in the constructor
    for variable_name in variable_names:
        code.append("\n_{0} = {0};".format(variable_name))
    
    # Add assignments that are always required
    code.extend(
        [
            "\n_outputColumn = outputColumn;",
            "\n_host = env.Register(nameof({0}));".format(estimator_class_name),
            "\n}"
        ]
    )

    return "".join(code)

def _GenerateFitMethod(transformer_class_name, variable_names):
    """
    Generates the Fit method. ML.NET calls this when it is ready to transform data.
    """
    code = [
        "\n\npublic {0} Fit(IDataView input)".format(transformer_class_name),
        "\n{",
        "\nreturn new {0}(_host".format(transformer_class_name)
    ]
    for variable_name in variable_names:
        code.append(", _{0}".format(variable_name))
    code.extend(
        [
            ", _outputColumn);",
            "\n}"
        ]
    )

    return "".join(code)
    
def _GenerateOutputSchema(return_type):
    """
    Determines which new column[s] will be added to the DataView after the transformation is finished.
    ML.NET uses this for schema propagation.
    """
    # TODO: Currently VectorKind is hard coded to Scalar. Works only for primitive types
    code = textwrap.dedent(
        """

        public SchemaShape GetOutputSchema(SchemaShape inputSchema)
        {{
            var columns = inputSchema.ToDictionary(x => x.Name);
            SchemaShape.Column col;

            col = new SchemaShape.Column(_outputColumn, SchemaShape.Column.VectorKind.Scalar,
            ColumnTypeExtensions.PrimitiveTypeFromType(typeof({return_type})), false, null);
            
            columns[_outputColumn] = col;
            return new SchemaShape(columns.Values);
        }}
        """
    ).format(return_type = return_type)
    return code

def _GenerateTransformer(transformer_class_name, extension_class_name, variable_names, variable_types, return_type, function_name, output_name):
    """
    The transformer is what actually does the transformation in ML.NET.
    This is where our DLL will be called.
    """
    code = [
        "\n\npublic class {0} : RowToRowTransformerBase".format(transformer_class_name),
        "\n{"
    ]
    
    # Generate private members
    for variable_type, varible_name in zip(variable_types, variable_names):
        code.append("\nprivate {0}.TransformParameter<{1}> _{2} = default;".format(extension_class_name, variable_type, varible_name))

    # Always has an output column
    code.extend( 
        [
            "\nprivate string _outputColumn = default;",
            _GenerateTransformerConstructor(transformer_class_name, extension_class_name, variable_names, variable_types),
            _GenerateMapper(transformer_class_name, return_type, variable_names, variable_types, extension_class_name, function_name, output_name),

            # TODO: Row Mapper and Save model are static for now
            "\n\nprotected override IRowMapper MakeRowMapper(DataViewSchema schema) => new Mapper(this, schema);",
            "\n\nprotected override void SaveModel(ModelSaveContext ctx)\n{",
            "\nthrow new NotImplementedException();\n}"  ,
            "\n}" 
        ]
    )
    return "".join(code)         
    
def _GenerateTransformerConstructor(transformer_class_name, extension_class_name, variable_names, variable_types):
    """
    Constructor for the Transformer. It has one input parameter per input to the
    function we will call in the DLL.
    """
    code = ["\n\npublic {0}(IHost host".format(transformer_class_name)]
    
    for variable_type, variable_name in zip(variable_types, variable_names):
        code.append(", {0}.TransformParameter<{1}> {2}".format(extension_class_name, variable_type, variable_name))
    
    code.extend(
        [
            ", string outputColumn) :",
            "\nbase(host.Register(nameof({0})))".format(transformer_class_name),
            "\n{"
        ]
    )

    for variable_name in variable_names:
        code.append("\n_{0} = {0};".format(variable_name))
    code.extend(
        [
            "\n_outputColumn = outputColumn;",
            "\n}"
        ]
    )

    return "".join(code)

def _GenerateMapper(transformer_class_name, return_type, variable_names, variable_types, extension_class_name, function_name, output_name):
    """
    The mapper is called by the transformer when we actually do the transformation.
    """
    code = [
        "\n\nprotected class Mapper : MapperBase",
        "\n{",
        "\nprivate readonly {0} _parent;".format(transformer_class_name),
        
        _GenerateDllImports(function_name, variable_names, variable_types, return_type, output_name),
        _GenerateMapperConstructor(transformer_class_name),
        _GenerateOutputColumns(return_type),
        _GenerateMakePrivateGetter(return_type, variable_names, function_name),
        _GenerateMakeProtectedGetter(),
        _GenerateDepencencies(variable_names),

        # TODO: This will need to change once we allow saving of the model
        "\n\nprotected override void SaveModel(ModelSaveContext ctx)\n{",
        "\nthrow new NotImplementedException();\n}",
        "\n}"
    ]       

    return "".join(code)

def _GenerateDllImports(function_name, variable_names, variable_types, return_type, output_name):
    """
    This generates the DLL import statments based on the function name and wrapper dll name.
    """
    code = [
        "\n\n[DllImport(\"{output_name}.dll\", EntryPoint = \"{function_name}Proxy\")]".format(
            output_name = output_name,
            function_name = function_name
        )
    ]

    code.append(
        "\nextern static {return_type} {function_name}(".format(
            return_type = return_type,
            function_name = function_name
        )
    )

    length = len(variable_names)

    for index in range(length):
        code.append(
            "{0} {1}{2}".format(
                variable_types[index],
                variable_names[index],
                ", " if index != length - 1 else ""
            )
        )

    code.append(');')

    return "".join(code)

def _GenerateMapperConstructor(transformer_class_name):
    """
    Public constructor generation for the mapper.
    """
    code = [
        "\n\npublic Mapper({0} parent, DataViewSchema inputSchema) :".format(transformer_class_name),
        "\nbase(parent.Host.Register(nameof(Mapper)), inputSchema, parent)",
        "\n{\n_parent = parent;\n}"
    ]

    return "".join(code)

def _GenerateOutputColumns(return_type):
    """
    This method in ML.NET determins the new output columns. Similar to the _GenerateOutputSchema
    """
    # TODO: this works for primitive types. Will need to revisit onces we do more complex types.
    # TODO: This works for 1 output column. Will need to revisit when we have multiple output column.
    code = [
        "\n\nprotected override DataViewSchema.DetachedColumn[] GetOutputColumnsCore()",
        "\n{",
        "\nvar output = new DataViewSchema.DetachedColumn(_parent._outputColumn,",
        "\nColumnTypeExtensions.PrimitiveTypeFromType(typeof({0})));".format(return_type),
        "\nreturn new DataViewSchema.DetachedColumn[] { output };",
        "\n}"
    ]

    return "".join(code)

def _GenerateMakePrivateGetter(return_type, variable_names, function_name):    
    """
    Internal helper method to actually get the data. It calls the DLL and passes the correct data to it.
    It then returns that value back to ML.NET.
    """
    code = [
        "\n\nprivate Delegate MakeGetter(DataViewRow input, int iinfo)",
        "\n{",
        "\nValueGetter<{0}> result = (ref {0} dst) =>".format(return_type),
        "\n{"
    ]
    
    # generate holders for intermediate values
    for variable_name in variable_names:
        code.append("\nvar {0}Val =  _parent._{0}.GetValue(input);".format(variable_name))
    
    code.append(
        "\ndst = {function_name}(".format(
            function_name = function_name
        )
    )

    length = len(variable_names)
    for index in range(length):
        code.append(
            "{0}Val{1}".format(
                variable_names[index],
                ", " if index != length - 1 else ""
            )
        )
        
    code.extend(
        [
            ');',
            "\n};",
            "\n\nreturn result;\n}"
        ]
    )

    return "".join(code)

def _GenerateMakeProtectedGetter():
    """
    Called when ML.NET is ready for the lazy data to be evaluated and to actually get the evaluated results.
    """
    code = textwrap.dedent(
        """

        protected override Delegate MakeGetter(DataViewRow input, int iinfo, Func<int, bool> activeOutput, out Action disposer)
        {
            disposer = null;
            return MakeGetter(input, iinfo);
        }"""
    )

    return code

def _GenerateDepencencies(variable_names):
    """
    Determines what input columns are needed based on the parameters and which parameters
    are coming from columns vs raw values.
    """
    code = [
        "\n\nprotected override Func<int, bool> GetDependenciesCore(Func<int, bool> activeOutput)",
        "\n{",
        "\nvar active = new bool[InputSchema.Count];",
        "\nfor (int i = 0; i < InputSchema.Count; i++)",
        "\n{"
    ]
    
    # Generate if statements for checking active columns
    for variable_name in variable_names:
        code.extend(
            [
                "\nif (_parent._{0}.Column.HasValue && InputSchema[i].Name.Equals(_parent._{0}.Column.Value.Name))".format(variable_name),
                "\n{",
                "\nactive[i] = true;",
                "\n}"
            ]
        )

    code.extend(
        [
            "\n}",
            "\n\nreturn col => active[col];",
            "\n}"
        ]
    )

    return "".join(code)
