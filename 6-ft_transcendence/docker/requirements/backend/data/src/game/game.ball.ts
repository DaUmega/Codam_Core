import { BallMovementStatus, BallEventDelays, GameBoardDimensions, MovementSpeeds, PlayerTypes } from './game.definitions';
import { Paddle } from './game.paddle';
import { GameData } from './game.service';

export class Ball {
  positionX: number = GameBoardDimensions.BOARD_WIDTH / 2;
  positionY: number = GameBoardDimensions.BOARD_HEIGHT / 2;
  horizontalVelocity: number = Math.floor(Math.random() * 10 % 2) ? (1.0 * MovementSpeeds.BALL_SPEED) : (-1.0 * MovementSpeeds.BALL_SPEED);
  verticalVelocity: number = 0;
  ballSpeed: number = 1;
  ballRadius: number = 15;
  isSpawnLocked: Boolean = true;
  timeToUnlockSpawn: number = new Date().getTime() - BallEventDelays.POST_GOAL_DELAY;

  isCollisionWithPaddle(paddle: Paddle): boolean {
    let closestX: number = this.positionX;
    let closestY: number = this.positionY;

    if (this.positionX <= paddle.x)
      closestX = paddle.x;
    else if (this.positionX > paddle.x + paddle.width)
      closestX = paddle.x + paddle.width;

    if (this.positionY <= paddle.y)
      closestY = paddle.y;
    else if (this.positionY > paddle.y + paddle.height)
      closestY = paddle.y + paddle.height;

    const distanceX: number = this.positionX - closestX;
    const distanceY: number = this.positionY - closestY;
    const distance: number = Math.sqrt((distanceX * distanceX) + (distanceY * distanceY));

    return distance <= this.ballRadius;
  }

  update(game: GameData) {
    let currentPlayer: PlayerTypes;

    if (this.isSpawnLocked && new Date().getTime() < this.timeToUnlockSpawn) {
      return;
    }
    this.isSpawnLocked = false;

    if (game.ball.positionX + this.ballRadius < GameBoardDimensions.BOARD_WIDTH / 2)
      currentPlayer = PlayerTypes.FIRST_PLAYER;
    else
      currentPlayer = PlayerTypes.SECOND_PLAYER;

    const currentPaddle: Paddle = game.playersList[currentPlayer].paddle;

    this.positionX += this.horizontalVelocity;
    this.positionY += this.verticalVelocity;

    if (this.positionY + this.ballRadius > GameBoardDimensions.BOARD_HEIGHT || this.positionY - this.ballRadius < 0)
      this.verticalVelocity = -this.verticalVelocity;

    if (this.isCollisionWithPaddle(currentPaddle)) {
      let speed = this.ballSpeed * MovementSpeeds.BALL_SPEED;
      const collisionOffset = this.positionY - (currentPaddle.y + currentPaddle.height / 2);
      const normalizedOffset = collisionOffset / currentPaddle.height / 2;
      const angleOfReturn = Math.PI / 3 * normalizedOffset;
      const directionOfReturn = currentPaddle.x < this.positionX ? 1 : -1;

      if (speed > MovementSpeeds.BALL_MAX_SPEED)
        speed = MovementSpeeds.BALL_MAX_SPEED;

      this.horizontalVelocity = directionOfReturn * speed * Math.cos(angleOfReturn);
      this.verticalVelocity = speed * Math.sin(angleOfReturn);

      this.ballSpeed += 0.1;
    }

    if (this.positionX - this.ballRadius <= 0 || this.positionX + this.ballRadius >= GameBoardDimensions.BOARD_WIDTH)
      return BallMovementStatus.POINT_SCORED;
    return BallMovementStatus.IN_MOTION;
  }
}

