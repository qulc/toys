from colorama import Fore, Back, Style

wb = Back.WHITE + Fore.BLACK


def white_black(text, color=wb):
    return f'{wb}{text}{Style.RESET_ALL}'


def red(text):
    return f'{Fore.RED}{text}{Style.RESET_ALL}'


def green(text):
    return f'{Fore.GREEN}{text}{Style.RESET_ALL}'

