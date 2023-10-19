import { Inject, Injectable } from '@nestjs/common';
import { GameService } from './game.service';
import { GameMode } from './game.definitions';
import { StatusTracker } from './status/game.status';

@Injectable()
export class MatchmakingService {
    private queueStandard = new Set<number>();
    private queueOpenMove = new Set<number>();

    constructor(
        private readonly gameService: GameService,
        @Inject('matchmakingStatus') private readonly matchmakingStatus: StatusTracker
    ) {}

    getUserQueueStatus(userId: number): GameMode {
      if (this.queueStandard.has(userId)) {
          return GameMode.STANDARD;
      } else if (this.queueOpenMove.has(userId)) {
          return GameMode.OPEN_MOVE;
      } else {
          return GameMode.AWAITING_QUEUE;
      }
    }
  

    addPlayerToQueue(mode: GameMode, userId: number): void {
      this.removeUserFromQueue(userId);
      const queue = this.getQueue(mode);
      queue?.add(userId);
      this.matchmakingStatus.setStatusByUserId(userId, mode);
  }

  removeUserFromQueue(userId: number): void {
      this.queueStandard.delete(userId);
      this.queueOpenMove.delete(userId);
      this.matchmakingStatus.removeStatusByUserId(userId);
  }

  private getQueue(mode: GameMode): Set<number> | null {
      switch (mode) {
          case GameMode.STANDARD:
              return this.queueStandard;
          case GameMode.OPEN_MOVE:
              return this.queueOpenMove;
          default:
              return null;
      }
  }

  private attemptMatchmaking(queue: Set<number>, mode: GameMode): void {
      if (queue.size < 2) return;

      const [player1, player2] = [...queue].slice(-2);
      this.gameService.initGame(player1, player2, mode);
      this.matchmakingStatus.removeStatusByUserId(player1);
      this.matchmakingStatus.removeStatusByUserId(player2);
      
      queue.delete(player1);
      queue.delete(player2);
  }

  checkForMatches(): void {
      this.attemptMatchmaking(this.queueStandard, GameMode.STANDARD);
      this.attemptMatchmaking(this.queueOpenMove, GameMode.OPEN_MOVE);
  }
}
