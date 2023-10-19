import { Injectable } from '@nestjs/common';
import { GameMode } from '../game.definitions';

@Injectable()
export class StatusTracker {

  private	data = new Map <number, GameMode>();

  removeStatusByUserId(userId: number): void {
    this.data.delete(userId);
  }

  setStatusByUserId(userId: number, mode: GameMode): void {
    this.data.set(userId, mode);
  }
  
  getStatusByUserId(userId: number): GameMode | undefined {
    return this.data.get(userId);
  }
}
