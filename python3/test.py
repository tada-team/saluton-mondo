import random
import time
import unittest

from python3.revert import revtext


class TestRevert(unittest.TestCase):
    def test_revtext_not_changed(self):
        random.seed(time.time())
        self.assertEqual(revtext('а'), 'а')
        self.assertEqual(revtext('бы'), 'бы')
        self.assertEqual(revtext('это'), 'это')
        self.assertEqual(revtext('это!'), 'это!')
        self.assertEqual(revtext('что-то'), 'что-то')

    def test_revtext_shuffled(self):
        random.seed(1)
        self.assertEqual(revtext('123456789'), '158742639')
        self.assertEqual(revtext('каокй-то'), 'какой-то')
        self.assertEqual(revtext('удивительное рядом!'), 'уьевтоднииле рядом!')


if __name__ == '__main__':
    unittest.main()
