export enum GameBoardDimensions {
    BOARD_WIDTH = 1400,
    BOARD_HEIGHT = 800,
}

export enum StandardSizes {
    PADDLE_WIDTH = 24,
    PADDLE_HEIGHT = 120,
    BALL_DIAMETER = 24,
}

export enum GameMode {
    STANDARD = 'Standard',
    OPEN_MOVE = 'OpenMove',
    NO_MATCH = 'NoMatch',
    AWAITING_QUEUE = 'AwaitingQueue',
    AWAITING_GAME_START = 'AwaitingGameStart',
}

export class CurrentGameState {
    score:number[] = [0, 0];
    leftPaddleCoords: number[] = [0, GameBoardDimensions.BOARD_HEIGHT / 2];
    leftPaddleHeight: number = StandardSizes.PADDLE_HEIGHT;
    leftPaddleWidth: number = StandardSizes.PADDLE_WIDTH;
    rightPaddleCoords: number[] = [GameBoardDimensions.BOARD_WIDTH, GameBoardDimensions.BOARD_HEIGHT / 2];
    rightPaddleHeight: number = StandardSizes.PADDLE_HEIGHT;
    rightPaddleWidth: number = StandardSizes.PADDLE_WIDTH;
    ballCoords: number[] = [GameBoardDimensions.BOARD_WIDTH / 2, GameBoardDimensions.BOARD_HEIGHT / 2];
    ballRadius: number = StandardSizes.BALL_DIAMETER;
}
