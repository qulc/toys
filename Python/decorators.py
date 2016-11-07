from functools import wraps


def retry(attempt=3):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kw):
            att = 0
            last_except = None
            while att < attempt:
                try:
                    return func(*args, **kw)
                except Exception as e:
                    att += 1
                    last_except = e
            else:
                raise last_except
        return wrapper
    return decorator
