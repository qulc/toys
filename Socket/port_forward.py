import asyncio

async def transfer(r, w, n):
    while True:
        data = await r.read(1024)
        if not data:
            return

        w.write(data)
        await w.drain()
        print(f'{n} {data}')

async def forward(reader, writer):
    cr, cw = await asyncio.open_connection('localhost', 2222)

    asyncio.create_task(transfer(reader, cw, 'Client'))
    asyncio.create_task(transfer(cr, writer, 'Server'))

async def main():
    server = await asyncio.start_server(forward, 'localhost', 5000)

    async with server:
        await server.serve_forever()

asyncio.run(main())
