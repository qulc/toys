import asyncio

async def echo(reader, writer):
	data = await reader.read(1024)
	print(data)

	writer.write(data)
	await writer.drain()
	writer.close()


async def main():
	server = await asyncio.start_server(echo, '127.0.0.1', 5000)

	async with server:
		await server.serve_forever()

asyncio.run(main())
