import { User } from '../users/entities/user.entity';
import { StandardSizes, GameBoardDimensions, PaddleDirections, PlayerTypes } from './game.definitions';
import { Paddle } from './game.paddle';

export class Player {
  userId: number;
  wins: number = 0;
  losses: number = 0;
  name: string;
  paddle: Paddle = new Paddle();
  Up: boolean = false;
  Down: boolean = false;
  Left: boolean = false;
  Right: boolean = false;

  constructor(playerData: User, side: PlayerTypes) {
    this.userId = playerData.id;
    this.name = playerData.nickname;
    this.setPosition(side);
  }

  private setPosition(side: PlayerTypes): void {
    const centerY = GameBoardDimensions.BOARD_HEIGHT / 2 - StandardSizes.PADDLE_HEIGHT / 2;
    if (side === PlayerTypes.FIRST_PLAYER) {
      this.paddle.x = 0;
      this.paddle.y = centerY;
    } else {
      this.paddle.x = GameBoardDimensions.BOARD_WIDTH - StandardSizes.PADDLE_WIDTH;
      this.paddle.y = centerY;
    }
  }

  private setInput(input: PaddleDirections, value: boolean): void {
    switch(input) {
      case PaddleDirections.MOVE_DOWN: this.Down = value; break;
      case PaddleDirections.MOVE_UP: this.Up = value; break;
      case PaddleDirections.MOVE_LEFT: this.Left = value; break;
      case PaddleDirections.MOVE_RIGHT: this.Right = value; break;
    }
  }

  activateDirections(input: PaddleDirections): void {
    this.setInput(input, true);
  }

  deactivateDirections(input: PaddleDirections): void {
    this.setInput(input, false);
  }

  resetDirections(): void {
    this.Down = false;
    this.Left = false;
    this.Right = false;
    this.Up = false;
  }
}
