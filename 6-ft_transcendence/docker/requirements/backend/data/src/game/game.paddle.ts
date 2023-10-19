import { StandardSizes, GameMode, GameBoardDimensions, MovementSpeeds, PlayerTypes } from './game.definitions';
import { Player } from './game.player';

export class Paddle {
  x: number = 0;
  y: number = 0;
  width: number = StandardSizes.PADDLE_WIDTH;
  height: number = StandardSizes.PADDLE_HEIGHT;
  acceleration: number = 1;

  update(player: Player, side: PlayerTypes, mode: GameMode): void {
    this.updateVerticalPosition(player);
    if (mode === GameMode.OPEN_MOVE) {
      this.updateHorizontalPosition(player, side);
    }
  }

  private updateVerticalPosition(player: Player): void {
    const paddleMovement: number = this.acceleration * MovementSpeeds.PADDLE_SPEED;

    if (player.Up) this.y -= paddleMovement;
    if (player.Down) this.y += paddleMovement;

    this.y = this.clamp(this.y, 0, GameBoardDimensions.BOARD_HEIGHT - this.height);
  }

  private updateHorizontalPosition(player: Player, side: PlayerTypes): void {
    const paddleMovement: number = this.acceleration * MovementSpeeds.PADDLE_SPEED;

    if (player.Left) this.x -= paddleMovement;
    if (player.Right) this.x += paddleMovement;

    if (side === PlayerTypes.FIRST_PLAYER) {
      const maxX = GameBoardDimensions.BOARD_WIDTH / 2 - this.width - StandardSizes.PADDLE_WIDTH * 5;
      this.x = this.clamp(this.x, 0, maxX);
    } else if (side === PlayerTypes.SECOND_PLAYER) {
      const minX = GameBoardDimensions.BOARD_WIDTH / 2 + StandardSizes.PADDLE_WIDTH * 5;
      this.x = this.clamp(this.x, minX, GameBoardDimensions.BOARD_WIDTH - this.width);
    }
  }

  private clamp(value: number, min: number, max: number): number {
    return Math.max(min, Math.min(value, max));
  }
}
