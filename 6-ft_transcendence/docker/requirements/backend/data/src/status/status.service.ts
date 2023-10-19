import { Inject, Injectable } from '@nestjs/common';
import { GameMode } from '../game/game.definitions';
import { StatusTracker } from '../game/status/game.status';
import { SocketMappingService } from '../gate/gate.service';

@Injectable()
export class StatusService {
  constructor(
    @Inject('statusGate') private readonly statusGate: SocketMappingService,
    @Inject('gameGate') private readonly gameGate: SocketMappingService,
    // @Inject('chatGate') private readonly chatGate: SocketMappingService,
    @Inject('gameStatus') private readonly gameStatus: StatusTracker,
    @Inject('matchmakingStatus') private readonly matchmakingStatus: StatusTracker,
  ){}

  async getStatus(userId: number) {
    // const chatSockets = this.chatGate.findSocketsByUserId(userId);
    const statusSockets = this.statusGate.findSocketsByUserId(userId);
    const gameMode: GameMode = this.gameStatus.getStatusByUserId(userId);
    const queueMode: GameMode = this.matchmakingStatus.getStatusByUserId(userId);
    if (gameMode !== undefined)
      return `Playing a ${gameMode} game`;
    if (queueMode !== undefined)
      return `In a queue for a ${queueMode} game`;
    // if ((await chatSockets).length > 0)
    //   return 'Online';
    if ((await statusSockets).length > 0)
      return 'Online';
    return 'Offline';
  }

  // for testing purposes
  async listConnections() {
    console.log('gameGate connections: ');
    this.gameGate.logAllSocketAssociations();
    // console.log('chatGate connections: ');
    // this.chatGate.logAllSocketAssociations();
    console.log('statusGate connections: ');
    this.statusGate.logAllSocketAssociations();
  }
}