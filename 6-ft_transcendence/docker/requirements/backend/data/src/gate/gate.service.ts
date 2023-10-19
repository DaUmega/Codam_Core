import { Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';

@Injectable()
export class SocketMappingService {
  constructor(){}
  private userBySocket: Map<Socket, number> = new Map();

  associateUserWithSocket(userId: number, sock: Socket) {
    this.userBySocket.set(sock, userId);
  }

  dissociateUserFromSocket(sock: Socket) {
    this.userBySocket.delete(sock);
  }

  findSocketsByUserId(userId: number): Socket[] {
    return [...this.userBySocket.entries()]
      .filter(([_, id]) => id === userId)
      .map(([socket, _]) => socket);
  }

  findUserIdBySocket(socket: Socket): number | undefined {
    return this.userBySocket.get(socket);
  }

  logAllSocketAssociations() {
    this.userBySocket.forEach((value, key) => 
      console.log(`userId: ${value}, socket: ${key}`)
    );
  }
}
