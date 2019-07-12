
def Policy(var_type):
    ''' 
    This is an early version of the policy. For now this should be enough, as more information comes about what 
    the functions will look like, this will be adapted to accept/reject more specific types. It returns 0 for 
    an accepted type and -1 for a rejected one.
    '''
    accepted_list = ['double', 'int32_t', 'int64_t','uint32_t','uint64_t','int', 'bool', 'float', 'char', 'vector', 'map', 'pair', 'tuple', 'string', 'void']
    ignored_list = ['const', 'signed', 'unsigned', 'std']
    
    if var_type not in accepted_list and var_type not in ignored_list:
        return False
    return True
