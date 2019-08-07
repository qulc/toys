from aiohttp import web
from xueqiu import get_stock_info


def handler(request):
    return web.Response(text='Hello Terminal Stock')


async def stock_handler(request):
    symbol = request.match_info.get('symbol')
    if not symbol:
        return web.Response(text='Not symbol')

    stock = await get_stock_info(symbol)
    return web.Response(text=str(stock))


app = web.Application()
app.add_routes([
    web.get('/', handler),
    web.get('/{symbol}', stock_handler)
])


if __name__ == '__main__':
    web.run_app(app)

