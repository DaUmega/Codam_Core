export enum GameMode {
  STANDARD = 'Standard',
  OPEN_MOVE = 'OpenMove',
  NO_MATCH = 'NoMatch',
  AWAITING_QUEUE = 'AwaitingQueue',
  AWAITING_GAME_START = 'AwaitingGameStart',
}

export enum PaddleDirections {
  MOVE_UP = 'ArrowUp',
  MOVE_DOWN = 'ArrowDown',
  MOVE_LEFT = 'ArrowLeft',
  MOVE_RIGHT = 'ArrowRight',
}

export enum PlayerTypes {
  FIRST_PLAYER,
  SECOND_PLAYER,
}

export enum GameBoardDimensions {
  BOARD_WIDTH = 1400,
  BOARD_HEIGHT = 800,
}

export enum MovementSpeeds {
  PADDLE_SPEED = 3,
  BALL_SPEED = 4.8,
  BALL_MAX_SPEED = 18,
}

export enum StandardSizes {
  PADDLE_WIDTH = 24,
  PADDLE_HEIGHT = 120,
  BALL_DIAMETER = 24,
}

export enum BallMovementStatus {
  IN_MOTION,
  POINT_SCORED,
}

export enum BallEventDelays {
  POST_GOAL_DELAY = 2400,
}
