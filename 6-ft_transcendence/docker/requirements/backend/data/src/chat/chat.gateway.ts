import { forwardRef, Inject } from "@nestjs/common"
import {
  OnGatewayDisconnect,
  OnGatewayConnection,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets'
import { Server, Socket } from 'socket.io'
import { ChatService } from './chat.service'
import { MessageDto } from "./dto/message.dto"

@WebSocketGateway({
  cors: {
    origin: '*',
  },
  namespace: '/chat'
})

export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect{

  @WebSocketServer()
  server: Server

  constructor(
    @Inject(forwardRef(() => ChatService))
    private readonly chatService: ChatService,
  ) {}

  handleConnection(client: Socket) {
    console.log(`Client connected: ${client.id}`)
  }

  handleDisconnect(client: Socket) {
    // remove client from all the rooms
    client.rooms.forEach(room => {
      client.leave(room);
    });

    console.log(`Client disconnected: ${client.id}`)
  }

  // MESSAGES
  @SubscribeMessage('sendMessage')
  async sendMessage(client: Socket, data: MessageDto) {
    client.join(String(data.channelId))
    console.log('sendMessage() called with data:', data)
    const response = await this.chatService.addMessageToChat(data.channelId, data)
    // send message to channel
    this.server.emit('receiveMessage', { channelId: data.channelId, message: response })
    client.leave(String(data.channelId))
  }

  @SubscribeMessage('sendPM')
  async sendPM(client: Socket, data: any) {
    console.log('sendPM() called with data:', data)
    this.server.emit('receivePM', data)
  }

  // Handle when a client joins a room.
  @SubscribeMessage('joinRoom')
  joinRoom(client: Socket, room: string) {
    console.log('joinRoom() called with room:', room)
    client.join(room)
    // TODO add relation
    this.server.to(room).emit('userJoined', room)
  }

  // Handle when a client leaves a room.
  @SubscribeMessage('leaveRoom')
  handleLeaveRoom(client: Socket, data: { id: string; userId: string }) {
    try {
      if (data.id) {
        this.server.to(data.id).emit('userLeft', data.userId)
        client.leave(data.id)
        // TODO delete relation
        console.log('handleLeaveRoom() called with id and userId:', data.id, data.userId)
      }
    } catch (error) {
      console.error('Error in handleLeaveRoom():', error);
    }
  }

}
