a={'d':1, 'e': [2,']
import copy
def repl(a):
    for k, v in a.items():
        if isinstance(v, dict):
            repl(v)
        else:
            if isinstance(v, str) and v[0] == '@':
                a[k] = [2,3]
print(a)
b = copy.deepcopy(a)
repl(b)
print(a)
print(b)