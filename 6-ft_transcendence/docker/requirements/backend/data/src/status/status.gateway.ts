import {
    WebSocketGateway,
    OnGatewayInit,
    OnGatewayConnection,
    OnGatewayDisconnect
  } from '@nestjs/websockets';
  import { Inject, Logger } from '@nestjs/common';
  import { Socket, Server } from 'socket.io';
  import { SocketMappingService } from '../gate/gate.service';
  import axios from 'axios'
  
  @WebSocketGateway({
    cors: {
      origin: '*',
    },
    namespace: '/status',
    secure: true
  })
  export class StatusGateway implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect {
    private readonly logger = new Logger(StatusGateway.name);
    private server: Server;

    constructor (
      @Inject('statusGate') private gate: SocketMappingService,
    ){}
      
      
    afterInit(server: Server) {
      this.server = server;
    }
  
    async handleConnection(client: Socket) {
      try {
        const response = await axios.get('https://api.intra.42.fr/v2/me', {
          headers: {
            'Content-Type': 'application/json',
          },
      });
      const userId = response.data.id;
      this.logger.log(`User ID from Gateway: ${userId}`);
      this.gate.associateUserWithSocket(userId, client)
      } catch (error) {
        this.logger.error("Failed to get userId in Status.gateway:", error);
        client.disconnect(true);
      }
    }
  
    handleDisconnect(client: Socket) {
      this.gate.dissociateUserFromSocket(client);
    }
  }