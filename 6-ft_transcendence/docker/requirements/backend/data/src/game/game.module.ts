import { Module } from '@nestjs/common'
import { GateModule } from '../gate/gate.module'
import { SocketMappingService } from '../gate/gate.service'
import { GameController } from './game.controller'
import { GameService } from './game.service'
import { GameGateway } from './game.gateway'
import { MatchmakingService } from './matchmaking.service'
import { UsersService } from '../users/users.service'
import { Repository } from 'typeorm';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from '../users/entities/user.entity';
import { GameStatusTrackerModule } from './status/game.status.module'
import { MatchesService } from '../matches/matches.service'
import { Match } from '../matches/entities/match.entity'

@Module({
    imports: [
        GateModule,
        GameStatusTrackerModule,
        TypeOrmModule.forFeature([User, Repository]),
        TypeOrmModule.forFeature([Match, Repository]),
    ],
    controllers: [GameController],
    providers: [
        UsersService,
        GameController,
        GameService,
        GameGateway,
        SocketMappingService,
        MatchmakingService,
        MatchesService
    ],
    exports: [GameController, GameService, MatchmakingService]
})
export class GameModule {}
