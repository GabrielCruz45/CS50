# a = {"hola" : 1, "como" : 2, "estas" : 3}
# a = dict(
    # hola = 1,
    # como = 2,
    # estas = 3)

keys = ['gabriel', 'girberto', 'davis', 'otildo el barbaro']
values = [69, 69, 420, 69]

a = dict(zip(keys, values))

tuplesList = [('gabz', 1), ('girberto', 2), ('davis', 3), ('otildo el barbaro', 4)]

arian = ('arian', 5)
# tuple = list(arian)

# tuplesList = tuplesList.append(arian)

# for item in tuplesList:
#     result.extend(arian)

b = dict(tuplesList)

c = dict(zip(keys, tuplesList))

print(a)
print(b)
print(c)
print(c.keys())
print(c.values())
print(c.items())
c['gabriel'].append('mom', 6)
print(c['gabriel'])
print(len(c['gabriel']))

if 'gabriel' in c: # solamente para los keyzz
    print('hola, mundo')