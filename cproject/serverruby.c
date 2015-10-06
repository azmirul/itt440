require 'socket'

server = TCPServer.open(1025)
loop
{
	client = server.accept
	client.puts(Time.now.ctie)
	client.puts "Closing the connection. Bye!"
	client.close
}
