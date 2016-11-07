import unittest

from decorators import retry


class TestDecorator(unittest.TestCase):
    def setUp(self):
        pass

    def test_retry(self):
        @retry()
        def func1(n=[]):
            if len(n) < 2:
                n.append(0)
                raise ValueError
            return n

        n = func1()
        self.assertEqual(n, [0, 0])

