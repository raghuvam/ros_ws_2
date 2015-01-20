#include <stdio.h>
#include <iostream>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

namespace IPNC {

int s;

int SendData(int SocketId, char *dataBuf, int dataSize)
{
  int actDataSize = 0;

  while (dataSize > 0)
  {
    actDataSize = send(SocketId, dataBuf, dataSize, 0);
    //cout << " IPNC_Client: Send Data " << actDataSize << " (" << dataSize << ")" << endl;
    if (actDataSize <= 0)
      break;
    dataBuf += actDataSize;
    dataSize -= actDataSize;
  }

  if (dataSize > 0)
  {
    cout << " IPNC_Client: Failed to send the data" << endl;
    return (-1);
  }

  return (0);
}

int RecvData(int SocketId, char *dataBuf, int dataSize)
{
  int actDataSize = 0;

  while (dataSize > 0)
  {
    actDataSize = recv(SocketId, dataBuf, dataSize, 0);
    //cout << " IPNC_Client: Received Data " << actDataSize << " (" << dataSize << ")" << endl;
    if (actDataSize <= 0)
      break;
    dataBuf += actDataSize;
    dataSize -= actDataSize;
  }

  if (dataSize > 0)
  {
    cout << " IPNC_Client: Failed to receive the data" << endl;
    return (-1);
  }

  return (0);
}

void closeIPNC()
{
  close(IPNC::s);
}

int capture(const char *IPaddress, int PortNo, char *image)
{
  struct sockaddr_in server;

  server.sin_addr.s_addr = inet_addr(IPaddress);
  server.sin_family = AF_INET;
  server.sin_port = htons(PortNo);

  //Send and receive data
  int dataSize = 20;
  int sendData[5], recvData[5];

  sendData[0] = 4;
 
  //Create a socket
  if((IPNC::s = socket(AF_INET , SOCK_STREAM , 0 )) == -1)
  {
    cout << "Could not create socket " << endl;
    return 1;
  }
  cout << "Socket created" << endl;

  //Connect to remote server
  if (connect(IPNC::s , (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    cout << "Connect error " << endl;
    return 1;
  }
  cout << "Connected to server" << endl;

  //Send command to the server
  if (IPNC::SendData(IPNC::s, (char *)sendData, dataSize) == 0)
  {
     do
     {
       //Receive a reply from the server
       if (IPNC::RecvData(IPNC::s, (char *)recvData, dataSize) == 0)
       {
        if (recvData[0] == 1 and recvData[1] != -1)
         {
           char *buf = new char[recvData[1]];
           if (IPNC::RecvData(IPNC::s, buf, recvData[1]) == 0)
           {
	     memcpy(image, buf, recvData[1]);
             image += recvData[1];
             cout << "Receiving Raw Image : " << recvData[1] << endl;
           }
           else
             break;
           delete[] buf;
         }
         else
           break;
       }
       else
         break;
     }
     while(1);

  }
  if (IPNC::s)
  {
    close(IPNC::s);
    cout << "Close Connection" << endl;
  }
  
  return 0;
}

}
