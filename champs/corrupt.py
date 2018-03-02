import sys
import random

N_TRUNC = 30
N_REPLACE = 1500
N_REMOVE = 1500
N_ADD = 1500

def random_n(n):
    return random.randint(0, n - 1) == 0

def trunc_file(fread):
    n = random.randint(0, len(fread) - 1)
    return fread[0:n]

def random_char():
    c = random.randint(32, 135)
    c = c if c < 127 else 10
    return chr(c)

def corrupt_file(fread):
    arr = list(fread)
    arr_len = len(arr)
    i = 0
    while i < arr_len:
        if random_n(N_REPLACE):
            arr[i] = random_char()
        elif random_n(N_REMOVE):
            del(arr[i])
            arr_len -= 1
            continue
        elif random_n(N_ADD):
            arr.insert(i, random_char())
            arr_len += 1
        i += 1
    return ''.join(arr)

def corrupt(file):
    try:
        with open(file, 'r') as f:
            fread = f.read()
    except OSError as ose:
        print('error: ' + format(ose))
        return 
    if random_n(N_TRUNC):
        fwrite = trunc_file(fread)
    else:
        fwrite = corrupt_file(fread)
    try:
        with open(file, 'w') as f:
            f.write(fwrite)
    except OSError as ose:
        print('error read(): ' + format(ose))
        return
    print('file \'{}\' corrupted'.format(file))

def main():
    random.seed()
    if len(sys.argv) < 2:
        print('missing arguments')
        exit()
    for i in range(1, len(sys.argv)):
        corrupt(sys.argv[i])


if __name__ == '__main__':
    main()
