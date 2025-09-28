import sympy

message = [42750, 225049, 67011, 9062, 263924, 83744, 10951, 156009,
174373, 125655, 207173, 200947, 227576, 183598, 148747, 211083,
225049, 218587, 191754, 164498, 225049, 171200, 193625, 99766,
94020, 223044, 38895, 74666, 48846, 219950, 139957, 77545,
171672, 165278, 150326, 262673, 164498, 142355, 77545, 171672,
255299, 5768, 264753, 75667, 261607, 31371, 164498, 140654,
244325, 140696, 40948, 179472, 168428, 34824, 32543, 30633,
104926, 190298, 148747, 132510, 42607, 232272, 42721, 188452,
239228, 50536, 216512, 139240, 78779, 166647, 100152, 261607,
121165]

"""other_factor = 0
for i in range (1, 1001):
    y = 266473 / i
    if y.is_integer():
        other_factor = int(y)
    modu = 266473 % i
    if (modu == 0) and (sympy.isprime(other_factor) and sympy.isprime(i)):
        print(other_factor)
        print(i)
        break"""
d = 0
while True:
    check = 17*d%44238
    if check == 1:
        print(d)
        break
    d += 1

dec = []
for index, item in enumerate(message):
    dec.append(item**10409%266473)

print(dec)

for i in dec:
    print(i.to_bytes(2, 'big'))



