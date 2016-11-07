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

        self.assertEqual(func1(), [0, 0])
        with self.assertRaises(AttributeError):
            func1('')

