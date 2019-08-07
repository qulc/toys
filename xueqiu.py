import aiohttp
from models import Stock


headers = {
	'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3861.0 Safari/537.36 Edg/77.0.230.2'
}
session = aiohttp.ClientSession(headers=headers)

url = 'https://stock.xueqiu.com/v5/stock/quote.json'


async def get_stock_info(symbol):
    await session.get('https://xueqiu.com/')

    async with session.get(url, params={'symbol': symbol}) as response:
        result = await response.json()

    quote = result['data']['quote']
    # keys = ['symbol', 'name', 'current', 'high', 'low', 'open', 'market_capital', 'amount']
    stock = Stock(symbol=quote['symbol'], name=quote['name'], current=quote['current'], open_price=quote['open'])
    return stock

