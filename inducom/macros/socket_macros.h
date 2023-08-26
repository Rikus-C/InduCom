#define CREATE_AND_CONNECT_TCP_CLIENT(client, ip, port, timeout) \
  _tcpClient client; \
  ConnectToServerTCP(&client, ip, port, timeout);

#define SEND_TCP_MESSAGE_NO_RESPONSE(client, message) \
  SendMessageTCP(&client, message, false, 0);

#define SEND_TCP_MESSAGE_WITH_RESPONSE(client, message, response, timeout) \
  SendMessageTCP(&client, message, true, timeout); \
  response = client.buffer;

#define DISCONNECT_TCP_CLIENT(client) \
  DisconnectFromServerTCP(&client);
