import random
import string
import sys


def revtext(text: str) -> str:
    return ' '.join(revword(w) for w in text.split())


def revword(w: str) -> str:
    bits = w.split('-')
    if len(bits) > 1:
        return '-'.join(revword(bit) for bit in bits)

    skip_start = skip_end = 1
    if w.endswith(tuple(string.punctuation)):
        skip_end += 1

    if len(w) - skip_start - skip_end < 2:
        return w

    return w[:skip_start] + revchars(w[skip_start:-skip_end]) + w[-skip_end:]


def revchars(s: str) -> str:
    chars = list(s)
    random.shuffle(chars)
    return ''.join(chars)


if __name__ == '__main__':
    for line in sys.stdin:
        print(revtext(line))
