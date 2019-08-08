from decimal import Decimal 
from dataclasses import dataclass, field

from utils import colors


@dataclass
class Stock:
    name: str
    symbol: str
    current: Decimal
    last_close: Decimal
    market_capital: float = field(default=0)

    def change(self):
        quote = round(self.current - self.last_close, 2)
        rise = round((quote / self.last_close) * 100, 2)

        if quote <= 0:
            return colors.red(f'{quote} \t {rise}%')
      
        return colors.green(f'+{quote} \t +{rise}%')


    def __str__(self):
        name = colors.white_black(f'{self.name}({self.symbol})')
        return name + '\t' + colors.white(self.current) + '\t' + self.change() + '\n'

