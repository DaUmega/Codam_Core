import { GameMode, PaddleDirections, PlayerTypes, GameBoardDimensions, MovementSpeeds, StandardSizes, BallMovementStatus, BallEventDelays } from './game.definitions';
import { Inject, Injectable } from '@nestjs/common'
import { Server, Socket } from 'socket.io'
import { SocketMappingService } from '../gate/gate.service'
import { StatusTracker } from '../game/status/game.status'
import { UsersService } from '../users/users.service'
import { MatchmakingService } from './matchmaking.service'
import { Ball } from './game.ball'
import { Player } from './game.player'
import { MatchesService } from '../matches/matches.service'

export class GameData {
    gameId: number;
    playersList: Player[] = []
    mode: GameMode = GameMode.STANDARD
    pointsNeededToWin: number = 1
    isGameDone: Boolean = false
    score: number[] = [0, 0]
    ball: Ball
    server: Server

    emitToRoom(path: string, payload: any) {
        this.server.to(`game_${this.gameId}`).emit(path, payload);
    }
}

export class CurrentGameState {
    score: number[] = [0, 0];
    leftPaddleCoords: number[] = [0, GameBoardDimensions.BOARD_HEIGHT / 2];
    rightPaddleCoords: number[] = [GameBoardDimensions.BOARD_WIDTH, GameBoardDimensions.BOARD_HEIGHT / 2];
    ballCoords: number[] = [GameBoardDimensions.BOARD_WIDTH / 2, GameBoardDimensions.BOARD_HEIGHT / 2];
    leftPaddleHeight: number = StandardSizes.PADDLE_HEIGHT;
    leftPaddleWidth: number = StandardSizes.PADDLE_WIDTH;
    rightPaddleHeight: number = StandardSizes.PADDLE_HEIGHT;
    rightPaddleWidth: number = StandardSizes.PADDLE_WIDTH;
    ballRadius: number = StandardSizes.BALL_DIAMETER;

    constructor(score: number[], leftPaddleCoords: number[], rightPaddleCoords: number[], ballCoords: number[]) {
        this.score = score;
        this.leftPaddleCoords = leftPaddleCoords;
        this.rightPaddleCoords = rightPaddleCoords;
        this.ballCoords = ballCoords;
    }
}

@Injectable()
export class GameService {
    constructor(private readonly usersService: UsersService,
            @Inject('gameGate') private readonly gate: SocketMappingService,
            @Inject('gameStatus') private readonly gameStatus: StatusTracker,
            private readonly matchesService: MatchesService
    ) {}

    private games: GameData[] = [];
    private gamesPlayed: number = 0;
    private server: Server;

    setSocket(socket: Server) {
        this.server = socket;
    }

    async updateGames() {
        if (!this.games?.length) {
            return;
        }

        for (const currentGame of this.games) {
            await this.updateSingleGame(currentGame);
        }

        this.clearCompletedGames();
    }

    private async updateSingleGame(game: GameData) {
        const ball: Ball = game.ball;

        this.updatePaddlesStatus(game);

        if (ball.update(game) === BallMovementStatus.POINT_SCORED) {
            await this.pointScored(game);
        }

        this.updateGameData(game);
    }


    private updatePaddlesStatus(game: GameData) {
        for (let playerNbr = 0; playerNbr < 2; playerNbr++) {
            const player:Player = game.playersList[playerNbr];
            player.paddle.update(player, playerNbr, game.mode);
        }
    }
    
    private async pointScored(game: GameData) {
        const ball = game.ball;

        ball.isSpawnLocked = true;
        ball.timeToUnlockSpawn = new Date().getTime() + BallEventDelays.POST_GOAL_DELAY;

        const { scoringPlayer, losingPlayer } = this.determineScoringPlayer(ball);

        game.score[scoringPlayer]++;

        if (game.score[scoringPlayer] === game.pointsNeededToWin) {
            await this.handleGameEnd(game, scoringPlayer, losingPlayer);
        }

        this.resetBallPositionAndVelocity(ball);
    }

    private determineScoringPlayer(ball: Ball): { scoringPlayer: PlayerTypes, losingPlayer: PlayerTypes } {
        if (ball.positionX - ball.ballRadius <= 0) {
            return {
                scoringPlayer: PlayerTypes.SECOND_PLAYER,
                losingPlayer: PlayerTypes.FIRST_PLAYER,
            };
        }
        return {
            scoringPlayer: PlayerTypes.FIRST_PLAYER,
            losingPlayer: PlayerTypes.SECOND_PLAYER,
        };
    }

    private async handleGameEnd(game: GameData, scoringPlayer: PlayerTypes, losingPlayer: PlayerTypes) {
        const winningPlayer: Player = game.playersList[scoringPlayer];
        const loserPlayer: Player = game.playersList[losingPlayer];

        game.isGameDone = true;
        game.emitToRoom('Winner', winningPlayer.name);

        const createMatchDto = {
            playerOneId: winningPlayer.userId,
            playerTwoId: loserPlayer.userId,
            winnerId: winningPlayer.userId,
        };

        try {
            const createdMatch = await this.matchesService.createMatch(createMatchDto);
        } catch (error) {
            console.error('Error creating match:', error);
        }
    }

    private resetBallPositionAndVelocity(ball: Ball) {
        ball.positionX = GameBoardDimensions.BOARD_WIDTH / 2;
        ball.positionY = GameBoardDimensions.BOARD_HEIGHT / 2;
        ball.horizontalVelocity = (Math.floor(Math.random() * 100) % 2) ? (1.0 * MovementSpeeds.BALL_SPEED) : (-1.0 * MovementSpeeds.BALL_SPEED);
        ball.verticalVelocity = 0.0;
        ball.ballSpeed = 1;
    }

    async initGame(player1Id: number, player2Id: number, mode: GameMode) {
        const [dataPlayer1, dataPlayer2] = await Promise.all([
            this.usersService.findById(player1Id),
            this.usersService.findById(player2Id)
        ]);

        const newGame = new GameData();
        newGame.gameId = this.gamesPlayed;
        newGame.playersList.push(new Player(dataPlayer1, PlayerTypes.FIRST_PLAYER));
        newGame.playersList.push(new Player(dataPlayer2, PlayerTypes.SECOND_PLAYER));
        newGame.ball = new Ball();
        newGame.mode = mode;
        newGame.server = this.server;

        this.gameStatus.setStatusByUserId(player1Id, mode);
        this.gameStatus.setStatusByUserId(player2Id, mode);

        this.games.push(newGame);
        this.gamesPlayed++;

        await Promise.all([
            this.sendUserToGameSocketRoom(dataPlayer1.id, newGame.gameId),
            this.sendUserToGameSocketRoom(dataPlayer2.id, newGame.gameId)
        ]);

        const { gameId } = newGame;
        const { nickname: namePlayer1 } = dataPlayer1;
        const { nickname: namePlayer2 } = dataPlayer2;

        this.server.emit('initGame', {
            gameId,
            player1: player1Id, namePlayer1,
            player2: player2Id, namePlayer2
        });

        return newGame;
    }

    private async clearCompletedGames() {
        const unfinishedGames = [];
        
        for (const game of this.games) {
            if (game.isGameDone) {
                const playerPromises = game.playersList.map(async player => {
                    const userId = player.userId;
                    this.gameStatus.removeStatusByUserId(userId);
    
                    const sockets: Socket[] = await this.gate.findSocketsByUserId(userId);
                    const socketPromises = sockets.map(socket => this.removeUserFromGameRoom(userId, socket));
                    await Promise.all(socketPromises);
                });
                await Promise.all(playerPromises);
            } else {
                unfinishedGames.push(game);
            }
        }
        
        this.games = unfinishedGames;
    }

    private updateGameData(game: GameData) {
        const player1 = game.playersList[PlayerTypes.FIRST_PLAYER];
        const player2 = game.playersList[PlayerTypes.SECOND_PLAYER];

        const toSend = new CurrentGameState(
            game.score,
            [player1.paddle.x, player1.paddle.y],
            [player2.paddle.x, player2.paddle.y],
            [game.ball.positionX, game.ball.positionY]
        );

        if (!game.isGameDone) {
            game.emitToRoom('GameState', toSend);
        }
    }

    
    updatePlayerPaddleInput(playerId: number, gameId: number, direction: PaddleDirections, isActive: boolean): void {
        const game = this.getGameById(gameId);
    
        if (!game) return;
    
        for (const player of game.playersList) {
            if (player.userId === playerId) {
                isActive ? player.activateDirections(direction) : player.deactivateDirections(direction);
                break;
            }
        }
    }

    checkIfPlaying(userId: number, client: Socket, matchmakingService: MatchmakingService) {
        const gameIndex: number = this.getGameByUser(userId);

        if (gameIndex === -1) {
            this.emitNoActiveGameStatus(userId, client, matchmakingService);
            return;
        }

        this.emitActiveGameStatus(gameIndex, client);
    }

    private emitNoActiveGameStatus(userId: number, client: Socket, matchmakingService: MatchmakingService) {
        const mode: GameMode = matchmakingService.getUserQueueStatus(userId);
        const inQueue = mode !== GameMode.AWAITING_QUEUE;

        client.emit('GameStatus', {
            alreadyInGame: false,
            alreadyInQueue: inQueue,
            gameId: -1,
            gameMode: mode,
            namePlayer1: '',
            namePlayer2: ''
        });
    }

    private emitActiveGameStatus(gameIndex: number, client: Socket) {
        const game: GameData = this.games[gameIndex];

        client.emit('GameStatus', {
            alreadyInGame: true,
            alreadyInQueue: false,
            gameId: game.gameId,
            gameMode: game.mode,
            namePlayer1: game.playersList[0].name,
            namePlayer2: game.playersList[1].name
        });

        client.join(`game_${game.gameId}`);
    }

    private getGameByUser(userId: number) {
        for (let index = 0; index < this.games.length; index++) {
            const game: GameData = this.games[index];

            for (let playerIndex = 0; playerIndex < game.playersList.length; playerIndex++) {
                const player: Player = game.playersList[playerIndex];
                
                if (player.userId === userId)
                    return (index);
            }
        }
        return (-1);
    }

    private getGameById(gameId: number) {
        for (let index = 0; index < this.games.length; index++) {
            const game = this.games[index];
            if (game.gameId === gameId)
                return (game);
        }
        return (null);
    }

    async sendUserToGameSocketRoom(userId: number, gameId: number) {
        const	userSockets = await this.gate.findSocketsByUserId(userId);

        for (let index = 0; index < userSockets.length; index++) {
            userSockets[index].join(`game_${gameId}`);
        }
    }

    async sendUserToGameRoom(userId: number) {
        const gameIndex: number = this.getGameByUser(userId);

        if (gameIndex === -1)
            return ;
        
        await this.sendUserToGameSocketRoom(userId, this.games[gameIndex].gameId);
    }

    removeUserFromGameRoom(userId: number, userSocket: Socket) {
        const gameIndex: number = this.getGameByUser(userId);
        
        if (gameIndex === -1)
            return ;
        const game: GameData = this.games[gameIndex];
        userSocket.leave(`game_${game.gameId}`);
    }

    resetUserDirections(userId: number) {
        const gameIndex = this.getGameByUser(userId);

        if (gameIndex === -1)
            return ;
        const game = this.games[gameIndex];
        if (game.playersList[0].userId === userId)
            game.playersList[0].resetDirections();
        else
            game.playersList[1].resetDirections();
    }
}
