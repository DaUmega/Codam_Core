import { 
  SubscribeMessage, 
  WebSocketGateway, 
  OnGatewayInit, 
  OnGatewayConnection, 
  OnGatewayDisconnect 
} from '@nestjs/websockets';
import { Socket, Server } from 'socket.io';
import { Inject } from '@nestjs/common';

import { GameService } from './game.service';
import { SocketMappingService } from '../gate/gate.service';
import { MatchmakingService } from './matchmaking.service';

@WebSocketGateway({
  cors: { origin: '*' },
  namespace: '/gamescreen'
})
export class GameGateway implements OnGatewayConnection, OnGatewayInit, OnGatewayDisconnect {

  private static readonly FPS_INTERVAL: number = 1000 / 60;
  private static readonly MATCH_CHECK_INTERVAL: number = 1000 * 0.5;

  private server: Server;

  constructor (
    private readonly gameService: GameService,
    private readonly matchmakingService: MatchmakingService,
    @Inject('gameGate') private readonly gate: SocketMappingService,
  ) {}

  afterInit(server: Server): void {
    this.server = server;
    this.gameService.setSocket(this.server);
    this.setupIntervals();
  }

  async handleConnection(client: Socket): Promise<void> {}

  async handleDisconnect(client: Socket): Promise<void> {
    await this.processUserDisconnection(client);
  }

  @SubscribeMessage('CheckGameStatus')
  async checkGameStatus(client: Socket): Promise<void> {
    const userId = await this.gate.findUserIdBySocket(client);
    if (userId) {
      this.gameService.checkIfPlaying(userId, client, this.matchmakingService);
    }
  }

  @SubscribeMessage('QueueForGame')
  async queueForGame(client: Socket, payload: any): Promise<void> {
    const userId = await this.gate.findUserIdBySocket(client);
    if (userId) {
      this.matchmakingService.addPlayerToQueue(payload.gameMode, userId);
    }
  }

  @SubscribeMessage('UpdatePaddleInput')
  async updatePlayerPaddleInput(client: any, payload: any): Promise<void> {
    const userId = await this.gate.findUserIdBySocket(client);
    if (userId) {
      this.gameService.updatePlayerPaddleInput(userId, payload.gameId, payload.key, payload.enabled);
    }
  }

  @SubscribeMessage('sendUserIdToGameRoom')
  async setUserId(client: any, userId: number): Promise<void> {
    this.gate.associateUserWithSocket(userId, client);
    this.gameService.sendUserToGameRoom(userId);
  }

  private setupIntervals(): void {
    setInterval(() => this.matchmakingService.checkForMatches(), GameGateway.MATCH_CHECK_INTERVAL);
    setInterval(() => this.gameService.updateGames(), GameGateway.FPS_INTERVAL);
  }

  private async processUserDisconnection(client: Socket): Promise<void> {
    const userId = await this.gate.findUserIdBySocket(client);
    if (!userId) return;

    const sockets = await this.gate.findSocketsByUserId(userId);
    if (sockets.length === 1) {
      this.matchmakingService.removeUserFromQueue(userId);
    }
    this.gameService.resetUserDirections(userId);
    this.gate.dissociateUserFromSocket(client);

    client.rooms.forEach(room => client.leave(room));
  }
}
